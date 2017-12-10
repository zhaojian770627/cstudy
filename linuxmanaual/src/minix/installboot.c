/*
 * e1.c
 *
 *  Created on: Sep 21, 2016
 *      Author: root
 */
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>  
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#define BYTE            0377
#define FALSE 0


typedef unsigned char   u8_t;	   /* 8 bit type */
typedef unsigned short u16_t;	   /* 16 bit type */
typedef unsigned long  u32_t;	   /* 32 bit type */

#define MAX_BLOCK_SIZE		 4096
#define SECTOR_SIZE	512	/* Disk sector size. */
#define BOOT_MAX	64	/* Absolute maximum size of secondary boot */

#define nil 0
#define IM_NAME_MAX	63
#define A_MINHDR	32

#define A_I8086	0x04	/* intel i8086/8088 */

/* Flags */
#define A_PAL	0x02	/* page aligned executable */
#define A_NSYM	0x04	/* new style symbol table */
#define A_SEP	0x20	/* separate I/D */

/* fs  */
#define V1		   1	/* version number of V1 file systems */ 
#define V2		   2	/* version number of V2 file systems */ 
#define V3		   3	/* version number of V3 file systems */ 

#define BYTE_SWAP          0	/* tells conv2/conv4 to swap bytes */

#define NR_INODES         64
#define V2_NR_TZONES      10
#define NR_SUPERS          8
#define SUPER_MAGIC   0x137F	/* magic number contained in super-block */
#define SUPER_V1 SUPER_MAGIC		/* V1 magic has a weird name. */
#define SUPER_V2      0x2468
#define SUPER_V2_REV  0x6824
#define SUPER_V3      0x4d5a
#define MIN_BLOCK_SIZE		 1024
#define STATIC_BLOCK_SIZE	1024

#define V1_INODE_SIZE             usizeof (d1_inode)  /* bytes in V1 dsk ino */
#define V1_ZONE_NUM_SIZE           usizeof (zone1_t)  /* # bytes in V1 zone  */
#define V1_NR_DZONES       7
#define V1_NR_TZONES       9	/* total # zone numbers in a V1 inode */

#define V2_NR_DZONES       7
#define V2_INODE_SIZE             usizeof (d2_inode)  /* bytes in V2 dsk ino */


#define usizeof(t) ((unsigned) sizeof(t))

#define V1_INODES_PER_BLOCK (STATIC_BLOCK_SIZE/V1_INODE_SIZE)
#define V1_INDIRECTS (STATIC_BLOCK_SIZE/V1_ZONE_NUM_SIZE) 

#define V2_ZONE_NUM_SIZE            usizeof (zone_t)  /* # bytes in V2 zone  */
#define V2_INDIRECTS(b)   ((b)/V2_ZONE_NUM_SIZE)
#define V2_INODES_PER_BLOCK(b) ((b)/V2_INODE_SIZE)/* # V2 dsk inodes/blk */
#define	zone_shift	(super.s_log_zone_size)	/* zone to block ratio */


/* types */
#define time_t long

typedef short          mdev_t;
typedef unsigned long  mino_t;
typedef unsigned short mmode_t;
typedef unsigned long zone_t;
typedef unsigned short zone1_t;
typedef unsigned long  bit_t;	
typedef short          muid_t;
typedef char           mgid_t;
typedef short        mnlink_t;
typedef unsigned long moff_t;

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

struct inode {
  mmode_t i_mode;		/* file type, protection, etc. */
  mnlink_t i_nlinks;		/* how many links to this file */
  muid_t i_uid;			/* user id of the file's owner */
  mgid_t i_gid;			/* group number */
  moff_t i_size;		/* current file size in bytes */
  time_t i_atime;		/* time of last access (V2 only) */
  time_t i_mtime;		/* when was file data last changed */
  time_t i_ctime;		/* when was inode itself changed (V2 only)*/
  zone_t i_zone[V2_NR_TZONES]; /* zone numbers for direct, ind, and dbl ind */
  
  /* The following items are not present on the disk. */
  mdev_t i_dev;			/* which device is the inode on */
  mino_t i_num;			/* inode number on its (minor) device */
  int i_count;			/* # times inode used; 0 means slot is free */
  int i_ndzones;		/* # direct zones (Vx_NR_DZONES) */
  int i_nindirs;		/* # indirect zones per indirect block */
  struct super_block *i_sp;	/* pointer to super block for inode's device */
  char i_dirt;			/* CLEAN or DIRTY */
  char i_pipe;			/* set to I_PIPE if pipe */
  char i_mount;			/* this bit is set if file mounted on */
  char i_seek;			/* set on LSEEK, cleared on READ/WRITE */
  char i_update;		/* the ATIME, CTIME, and MTIME bits are here */
} inode[NR_INODES];

struct super_block {
  mino_t s_ninodes;		/* # usable inodes on the minor device */
  zone1_t  s_nzones;		/* total device size, including bit maps etc */
  short s_imap_blocks;		/* # of blocks used by inode bit map */
  short s_zmap_blocks;		/* # of blocks used by zone bit map */
  zone1_t s_firstdatazone;	/* number of first data zone */
  short s_log_zone_size;	/* log2 of blocks/zone */
  short s_pad;			/* try to avoid compiler-dependent padding */
  moff_t s_max_size;		/* maximum file size on this device */
  zone_t s_zones;		/* number of zones (replaces s_nzones in V2) */
  short s_magic;		/* magic number to recognize super-blocks */

  /* The following items are valid on disk only for V3 and above */

  /* The block size in bytes. Minimum MIN_BLOCK SIZE. SECTOR_SIZE
   * multiple. If V1 or V2 filesystem, this should be
   * initialised to STATIC_BLOCK_SIZE. Maximum MAX_BLOCK_SIZE.
   */
  short s_pad2;			/* try to avoid compiler-dependent padding */
  unsigned short s_block_size;	/* block size in bytes. */
  char s_disk_version;		/* filesystem format sub-version */

  /* The following items are only used when the super_block is in memory. */
  struct inode *s_isup;		/* inode for root dir of mounted file sys */
  struct inode *s_imount;	/* inode mounted on */
  unsigned s_inodes_per_block;	/* precalculated from magic number */
  mdev_t s_dev;			/* whose super block is this? */
  int s_rd_only;		/* set to 1 iff file sys mounted read only */
  int s_native;			/* set to 1 iff not byte swapped file system */
  int s_version;		/* file system version, zero means bad magic */
  int s_ndzones;		/* # direct zones in an inode */
  int s_nindirs;		/* # indirect zones per indirect block */
  bit_t s_isearch;		/* inodes below this bit number are in use */
  bit_t s_zsearch;		/* all zones below this bit number are in use*/
} super_block[NR_SUPERS];

/* Declaration of the V1 inode as it is on the disk (not in core). */
typedef struct {		/* V1.x disk inode */
  mmode_t d1_mode;		/* file type, protection, etc. */
  muid_t d1_uid;			/* user id of the file's owner */
  moff_t d1_size;		/* current file size in bytes */
  time_t d1_mtime;		/* when was file data last changed */
  u8_t d1_gid;			/* group number */
  u8_t d1_nlinks;		/* how many links to this file */
  u16_t d1_zone[V1_NR_TZONES];	/* block nums for direct, ind, and dbl ind */
} d1_inode;

/* Declaration of the V2 inode as it is on the disk (not in core). */
typedef struct {		/* V2.x disk inode */
  mmode_t d2_mode;		/* file type, protection, etc. */
  u16_t d2_nlinks;		/* how many links to this file. HACK! */
  muid_t d2_uid;			/* user id of the file's owner. */
  u16_t d2_gid;			/* group number HACK! */
  moff_t d2_size;		/* current file size in bytes */
  time_t d2_atime;		/* when was file data last accessed */
  time_t d2_mtime;		/* when was file data last changed */
  time_t d2_ctime;		/* when was inode data last changed */
  zone_t d2_zone[V2_NR_TZONES];	/* block nums for direct, ind, and dbl ind */
} d2_inode;

static struct super_block super;	/* Superblock of file system */

#define A_MAGIC0      (unsigned char) 0x01
#define A_MAGIC1      (unsigned char) 0x03
#define BADMAG(X)     ((X).a_magic[0] != A_MAGIC0 ||(X).a_magic[1] != A_MAGIC1)

/* File system parameters. */
static unsigned nr_dzones;	/* Fill these in after reading superblock. */
static unsigned nr_indirects;
static unsigned inodes_per_block;
static int block_size;

struct image_header {
	char		name[IM_NAME_MAX + 1];	/* Null terminated. */
	struct exec	process;
};


/*===========================================================================*
 *				conv2					     *
 *===========================================================================*/
unsigned conv2(norm, w)
int norm;			/* TRUE if no swap, FALSE for byte swap */
int w;				/* promotion of 16-bit word to be swapped */
{
/* Possibly swap a 16-bit word between 8086 and 68000 byte order. */
  if (norm) return( (unsigned) w & 0xFFFF);
  return( ((w&BYTE) << 8) | ( (w>>8) & BYTE));
}

/*===========================================================================*
 *				conv4					     *
 *===========================================================================*/
long conv4(norm, x)
int norm;			/* TRUE if no swap, FALSE for byte swap */
long x;				/* 32-bit long to be byte swapped */
{
/* Possibly swap a 32-bit long between 8086 and 68000 byte order. */
  unsigned lo, hi;
  long l;
  
  if (norm) return(x);			/* byte order was already ok */
  lo = conv2(FALSE, (int) x & 0xFFFF);	/* low-order half, byte swapped */
  hi = conv2(FALSE, (int) (x>>16) & 0xFFFF);	/* high-order half, swapped */
  l = ( (long) lo <<16) | hi;
  return(l);
}

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
  printf("off_t- %d\n",sizeof(off_t));
  printf("inode size -%d\n",sizeof(struct inode));
  printf("super_block size -%d\n",sizeof(struct super_block));
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



int rawfd;	/* File descriptor to open device. */
char *rawdev;	/* Name of device. */

void readblock(off_t blk, char *buf, int block_size)
/* For rawfs, so that it can read blocks. */
{
	int n;

	if (lseek(rawfd, blk * block_size, SEEK_SET) < 0
		|| (n= read(rawfd, buf, block_size)) < 0
	) fatal(rawdev);

	if (n < block_size) {
		fprintf(stderr, "installboot: Unexpected EOF on %s\n", rawdev);
		exit(1);
	}
}

enum howto { FS, BOOT };

static char dirbuf[MAX_BLOCK_SIZE];	/* Scratch/Directory block. */
#define scratch dirbuf

void showsuperinfo(struct super_block * p){
  printf("------------------super----------------------\n");
  printf("i节点个数:%ld\n",p->s_ninodes);
  printf("total device size(not used):%d\n",p->s_nzones);
  printf("i节点位图块的个数:%d\n",p->s_imap_blocks);
  printf("区段位图块的个数:%d\n",p->s_zmap_blocks);
  printf("第一个数据区段:%d\n",p->s_firstdatazone);
  printf("块数或区段:%d\n",p->s_log_zone_size);
  printf("填充位:%d\n",p->s_pad);
  printf("最大文件尺寸:%lu\n",p->s_max_size);
  printf("区段数:%ld\n",p->s_zones);
  printf("模数:%X\n",p->s_magic);
  printf("填充位2:%d\n",p->s_pad2);  
  printf("块大小:%d\n",p->s_block_size);
  printf("文件系统版本号:%d\n",p->s_disk_version);
}

off_t r_super(int *bs){
  /* Initialize variables, return size of file system in blocks,
   * (zero on error).
   */
  /* Read superblock. (The superblock is always at 1kB offset,
   * that's why we lie to readblock and say the block size is 1024
   * and we want block number 1 (the 'second block', at offset 1kB).)
   */
  readblock(1, scratch, 1024);

  memcpy(&super, scratch, sizeof(super));
  showsuperinfo(&super);
  /* Is it really a MINIX file system ? */
  if (super.s_magic == SUPER_V2 || super.s_magic == SUPER_V3) {
    if(super.s_magic == SUPER_V2)
      super.s_block_size = 1024;
    *bs = block_size = super.s_block_size;
    if(block_size < MIN_BLOCK_SIZE ||
       block_size > MAX_BLOCK_SIZE) {
      return 0;
    }
    nr_dzones= V2_NR_DZONES;
    nr_indirects= V2_INDIRECTS(block_size);
    inodes_per_block= V2_INODES_PER_BLOCK(block_size);
    return (off_t) super.s_zones << zone_shift;
  } else
    if (super.s_magic == SUPER_V1) {
      *bs = block_size = 1024;
      nr_dzones= V1_NR_DZONES;
      nr_indirects= V1_INDIRECTS;
      inodes_per_block= V1_INODES_PER_BLOCK;
      return (off_t) super.s_nzones << zone_shift;
    } else {
      /* Filesystem not recognized as Minix. */
      return 0;
    }
}

int initsuper(struct super_block * sp){
  int magic;
  int version, native, r; 
  magic = sp->s_magic;		/* determines file system type */

  /* Get file system version and type. */
  if (magic == SUPER_MAGIC || magic == conv2(BYTE_SWAP, SUPER_MAGIC)) {
    version = V1;
    native  = (magic == SUPER_MAGIC);
  } else if (magic == SUPER_V2 || magic == conv2(BYTE_SWAP, SUPER_V2)) {
    version = V2;
    native  = (magic == SUPER_V2);
  } else if (magic == SUPER_V3) {
    version = V3;
    native = 1;
  } else {
    return(EINVAL);
  }
  printf("version %d\n",version);

}

/* Install bootblock on the bootsector of device with the disk addresses to
 * bootcode patched into the data segment of bootblock.  "How" tells if there
 * should or shoudn't be a file system on the disk.  The images in the imagev
 * vector are added to the end of the device.
 */
void make_bootable(enum howto how, char *device, char *bootblock,
		   char *bootcode, char **imagev){
  char buf[MAX_BLOCK_SIZE + 256], *adrp, *parmp;
  struct fileaddr {
    off_t	address;
    int	count;
  } bootaddr[BOOT_MAX + 1], *bap= bootaddr;
  off_t addr, fssize, pos, len;
  int block_size = 0;

  /* Open device and set variables for readblock. */
  if ((rawfd= open(rawdev= device, O_RDWR)) < 0) fatal(device);
  /* Read and check the superblock. */
  fssize= r_super(&block_size);

  initsuper(&super);


}

int main(int argc, char *argv[]) {
  char image[50]="zj.img";
  char device[50]="/dev/loop0";
  char *procv[2]={"/home/zj/git/os/minix/zj",0};
  testsize();  
  //make_image(image,procv);
  // extract_image(image);
  make_bootable(FS,device,image,image,procv);
  exit(EXIT_SUCCESS);
}
