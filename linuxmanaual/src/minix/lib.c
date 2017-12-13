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



/* Allocate a bit from a bit map and return its bit number. */
bit_t alloc_bit(struct super_block *sp, int map, bit_t origin){
  block_t start_block;		/* first bit block */
  bit_t map_bits;		/* how many bits are there in the bit map? */
  unsigned bit_blocks;		/* how many blocks are there in the bit map? */
  unsigned block, word, bcount;

  if (sp->s_rd_only)
    fatal("error");

  if (map == IMAP) {
    start_block = START_BLOCK;
    map_bits = sp->s_ninodes + 1;
    bit_blocks = sp->s_imap_blocks;
  } else {
    start_block = START_BLOCK + sp->s_imap_blocks;
    map_bits = sp->s_zones - (sp->s_firstdatazone - 1);
    bit_blocks = sp->s_zmap_blocks;
  }

  /* Figure out where to start the bit search (depends on 'origin'). */
  if (origin >= map_bits) origin = 0;	/* for robustness */

  /* Locate the starting place. */
  block = origin / FS_BITS_PER_BLOCK(sp->s_block_size);
  word = (origin % FS_BITS_PER_BLOCK(sp->s_block_size)) / FS_BITCHUNK_BITS;

  return 0;
}

