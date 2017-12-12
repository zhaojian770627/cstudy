#include "testfs.h"

void report(char *label)
/* installboot: label: No such file or directory */
{
	fprintf(stderr, "testfs: %s: %s\n", label, strerror(errno));
}

void fatal(char *label)
{
	report(label);
	exit(1);
}

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

void readblock(moff_t blk, char *buf, int block_size)
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
