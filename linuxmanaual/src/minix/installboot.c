/*
 * e1.c
 *
 *  Created on: Sep 21, 2016
 *      Author: root
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>  
#include <errno.h>

#define SECTOR_SIZE	512	/* Disk sector size. */

#define nil 0
#define IM_NAME_MAX	63
#define A_MINHDR	32

#define A_I8086	0x04	/* intel i8086/8088 */

/* Flags */
#define A_PAL	0x02	/* page aligned executable */
#define A_NSYM	0x04	/* new style symbol table */
#define A_SEP	0x20	/* separate I/D */

struct	exec {			/* a.out header */
  unsigned char	a_magic[2];	/* magic number */
  unsigned char	a_flags;	/* flags, see below */
  unsigned char	a_cpu;		/* cpu id */
  unsigned char	a_hdrlen;	/* length of header */
  unsigned char	a_unused;	/* reserved for future use */
  unsigned short a_version;	/* version stamp (not used at present) */
  long		a_text;		/* size of text segement in bytes */
  long		a_data;		/* size of data segment in bytes */
  long		a_bss;		/* size of bss segment in bytes */
  long		a_entry;	/* entry point */
  long		a_total;	/* total memory allocated */
  long		a_syms;		/* size of symbol table */

  /* SHORT FORM ENDS HERE */
  long		a_trsize;	/* text relocation size */
  long		a_drsize;	/* data relocation size */
  long		a_tbase;	/* text relocation base */
  long		a_dbase;	/* data relocation base */
};

#define A_MAGIC0      (unsigned char) 0x01
#define A_MAGIC1      (unsigned char) 0x03
#define BADMAG(X)     ((X).a_magic[0] != A_MAGIC0 ||(X).a_magic[1] != A_MAGIC1)

struct image_header {
	char		name[IM_NAME_MAX + 1];	/* Null terminated. */
	struct exec	process;
};

void report(char *label)
/* installboot: label: No such file or directory */
{
	fprintf(stderr, "installboot: %s: %s\n", label, strerror(errno));
}

void fatal(char *label)
{
	report(label);
	exit(1);
}

char *basename(char *name)
/* Return the last component of name, stripping trailing slashes from name.
 * Precondition: name != "/".  If name is prefixed by a label, then the
 * label is copied to the basename too.
 */
{
	static char base[IM_NAME_MAX];
	char *p, *bp= base;

	if ((p= strchr(name, ':')) != nil) {
		while (name <= p && bp < base + IM_NAME_MAX - 1)
			*bp++ = *name++;
	}
	for (;;) {
		if ((p= strrchr(name, '/')) == nil) { p= name; break; }
		if (*++p != 0) break;
		*--p= 0;
	}
	while (*p != 0 && bp < base + IM_NAME_MAX - 1) *bp++ = *p++;
	*bp= 0;
	return base;
}

void testsize()
{
  printf("unsigned char- %d\n",sizeof(unsigned char));
  printf("unsigned short- %d\n",sizeof(unsigned short));
  printf("long- %d\n",sizeof(long));
}

void bread(FILE *f, char *name, void *buf, size_t len)
/* Read len bytes.  Don't dare return without them. */
{
	if (len > 0 && fread(buf, len, 1, f) != 1) {
		if (ferror(f)) fatal(name);
		fprintf(stderr, "installboot: Unexpected EOF on %s\n", name);
		exit(1);
	}
}

void bwrite(FILE *f, char *name, void *buf, size_t len)
{
	if (len > 0 && fwrite(buf, len, 1, f) != 1) fatal(name);
}

long total_text= 0, total_data= 0, total_bss= 0;
int making_image= 0;

void read_header(int talk, char *proc, FILE *procf, struct image_header *ihdr)
/* Read the a.out header of a program and check it.  If procf happens to be
 * nil then the header is already in *image_hdr and need only be checked.
 */
{
	int n, big= 0;
	static int banner= 0;
	struct exec *phdr= &ihdr->process;

	if (procf == nil) {
		/* Header already present. */
		n= phdr->a_hdrlen;
	} else {
		memset(ihdr, 0, sizeof(*ihdr));

		/* Put the basename of proc in the header. */
		strncpy(ihdr->name, basename(proc), IM_NAME_MAX);

		/* Read the header. */
		n= fread(phdr, sizeof(char), A_MINHDR, procf);
		if (ferror(procf)) fatal(proc);
	}

	if (n < A_MINHDR || BADMAG(*phdr)) {
		fprintf(stderr, "installboot: %s is not an executable\n", proc);
		exit(1);
	}

	/* Get the rest of the exec header. */
	if (procf != nil) {
		bread(procf, proc, ((char *) phdr) + A_MINHDR,
						phdr->a_hdrlen - A_MINHDR);
	}

	if (talk && !banner) {
		printf("     text     data      bss      size\n");
		banner= 1;
	}

	if (talk) {
		printf(" %8ld %8ld %8ld %9ld  %s\n",
			phdr->a_text, phdr->a_data, phdr->a_bss,
			phdr->a_text + phdr->a_data + phdr->a_bss, proc);
	}
	total_text+= phdr->a_text;
	total_data+= phdr->a_data;
	total_bss+= phdr->a_bss;

	if (phdr->a_cpu == A_I8086) {
		long data= phdr->a_data + phdr->a_bss;

		if (!(phdr->a_flags & A_SEP)) data+= phdr->a_text;

		if (phdr->a_text >= 65536) big|= 1;
		if (data >= 65536) big|= 2;
	}
	if (big) {
		fprintf(stderr,
			"%s will crash, %s%s%s segment%s larger then 64K\n",
			proc,
			big & 1 ? "text" : "",
			big == 3 ? " and " : "",
			big & 2 ? "data" : "",
			big == 3 ? "s are" : " is");
	}
}

void padimage(char *image, FILE *imagef, int n)
/* Add n zeros to image to pad it to a sector boundary. */
{
	while (n > 0) {
		if (putc(0, imagef) == EOF) fatal(image);
		n--;
	}
}

#define align(n)	(((n) + ((SECTOR_SIZE) - 1)) & ~((SECTOR_SIZE) - 1))

void copyexec(char *proc, FILE *procf, char *image, FILE *imagef, long n)
/* Copy n bytes from proc to image padded to fill a sector. */
{
	int pad, c;

	/* Compute number of padding bytes. */
	pad= align(n) - n;

	while (n > 0) {
		if ((c= getc(procf)) == EOF) {
			if (ferror(procf)) fatal(proc);
			fprintf(stderr,	"installboot: premature EOF on %s\n",
									proc);
			exit(1);
		}
		if (putc(c, imagef) == EOF) fatal(image);
		n--;
	}
	padimage(image, imagef, pad);
}

void make_image(char *image, char **procv){
  char *proc,*file;
  int procn;
  struct image_header ihdr;
  struct stat st;
  struct exec phdr;
  FILE *imagef, *procf;

  printf("image:%s\n",image);

  making_image= 1;

  if ((imagef= fopen(image, "w")) == nil) fatal(image);

  for (procn= 0; (proc= *procv++) != nil; procn++) {
    if ((file= strchr(proc, ':')) != nil) 
      file++; 
    else 
      file= proc;
    printf("procv:%s\n",proc);
    if (stat(file, &st) < 0
	|| (errno= EISDIR, !S_ISREG(st.st_mode))
	|| (procf= fopen(file, "r")) == nil
	)
      fatal(proc) ;

    /* Read a.out header. */
    read_header(1, proc, procf, &ihdr);

    /* Scratch. */
    phdr= ihdr.process;

    /* The symbol table is always stripped off. */
    ihdr.process.a_syms= 0;
    ihdr.process.a_flags &= ~A_NSYM;

    /* Write header padded to fill a sector */
    bwrite(imagef, image, &ihdr, sizeof(ihdr));

    padimage(image, imagef, SECTOR_SIZE - sizeof(ihdr));

    /* A page aligned executable needs the header in text. */
    if (phdr.a_flags & A_PAL) {
      rewind(procf);
      phdr.a_text+= phdr.a_hdrlen;
    }

    /* Copy text and data of proc to image. */
    if (phdr.a_flags & A_SEP) {
      /* Separate I&D: pad text & data separately. */

      copyexec(proc, procf, image, imagef, phdr.a_text);
      copyexec(proc, procf, image, imagef, phdr.a_data);
    } else {
      /* Common I&D: keep text and data together. */

      copyexec(proc, procf, image, imagef,
	       phdr.a_text + phdr.a_data);
    }

    (void) fclose(procf);
  }

  if (fclose(imagef) == EOF) fatal(image);

  printf("   ------   ------   ------   -------\n");
  printf(" %8ld %8ld %8ld %9ld  total\n",
	 total_text, total_data, total_bss,
	 total_text + total_data + total_bss);
}

void extractexec(FILE *imagef, char *image, FILE *procf, char *proc,
						long count, off_t *alen)
/* Copy a segment of an executable.  It is padded to a sector in image. */
{
	char buf[SECTOR_SIZE];

	while (count > 0) {
		bread(imagef, image, buf, sizeof(buf));
		*alen-= sizeof(buf);

		bwrite(procf, proc, buf,
			count < sizeof(buf) ? (size_t) count : sizeof(buf));
		count-= sizeof(buf);
	}
}

void extract_image(char *image)
/* Extract the executables from an image. */
{
  FILE *imagef, *procf;
  off_t len;
  struct stat st;
  struct image_header ihdr;
  struct exec phdr;
  char buf[SECTOR_SIZE];

  if (stat(image, &st) < 0) fatal(image);

  /* Size of the image. */
  len= S_ISREG(st.st_mode) ? st.st_size : -1;

  if ((imagef= fopen(image, "r")) == nil) fatal(image);

  while (len != 0) {
    /* Extract a program, first sector is an extended header. */
    bread(imagef, image, buf, sizeof(buf));
    len-= sizeof(buf);

    memcpy(&ihdr, buf, sizeof(ihdr));
    phdr= ihdr.process;

    /* Check header. */
    read_header(1, ihdr.name, nil, &ihdr);

    if ((procf= fopen(ihdr.name, "w")) == nil) fatal(ihdr.name);

    if (phdr.a_flags & A_PAL) {
      /* A page aligned process contains a header in text. */
      phdr.a_text+= phdr.a_hdrlen;
    } else {
      bwrite(procf, ihdr.name, &ihdr.process, phdr.a_hdrlen);
    }

    /* Extract text and data segments. */
    if (phdr.a_flags & A_SEP) {
      extractexec(imagef, image, procf, ihdr.name,
		  phdr.a_text, &len);
      extractexec(imagef, image, procf, ihdr.name,
		  phdr.a_data, &len);
    } else {
      extractexec(imagef, image, procf, ihdr.name,
		  phdr.a_text + phdr.a_data, &len);
    }

    if (fclose(procf) == EOF) fatal(ihdr.name);
  }
}

enum howto { FS, BOOT };

void make_bootable(enum howto how, char *device, char *bootblock,
		   char *bootcode, char **imagev){
}

int main(int argc, char *argv[]) {
  char image[50]="zj.img";
  char *procv[2]={"/home/zj/git/os/minix/zj",0};
  testsize();  
  //make_image(image,procv);
  // extract_image(image);
  make_bootable(FS,"/dev/fd0",image,image,procv);
  exit(EXIT_SUCCESS);
}
