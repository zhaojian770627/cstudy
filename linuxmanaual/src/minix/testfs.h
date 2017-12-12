#ifndef	__testfs_h
#define	__testfs_h

#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>  
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#define OK            0
#define BYTE            0377
#define FALSE 0

/* types */
#define time_t long

typedef unsigned char   u8_t;	   /* 8 bit type */
typedef unsigned short u16_t;	   /* 16 bit type */
typedef unsigned long  u32_t;	   /* 32 bit type */

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
typedef unsigned long block_t;	   /* block number */

#define usizeof(t) ((unsigned) sizeof(t))

/* fs  */
#define V1		   1	/* version number of V1 file systems */ 
#define V2		   2	/* version number of V2 file systems */ 
#define V3		   3	/* version number of V3 file systems */ 

#define NO_DEV                  ((mdev_t) 0)	/* absence of a device numb */

#define SUPER_SIZE      usizeof (struct super_block)  /* super_block size    */

#define SUPER_MAGIC   0x137F	/* magic number contained in super-block */
#define SUPER_V1 SUPER_MAGIC		/* V1 magic has a weird name. */
#define SUPER_V2      0x2468
#define SUPER_V2_REV  0x6824
#define SUPER_V3      0x4d5a

#define STATIC_BLOCK_SIZE	1024
#define MIN_BLOCK_SIZE		 1024
#define MAX_BLOCK_SIZE		 4096

#define NR_SUPERS          8
#define NR_INODES         64

#define V1_NR_TZONES       9	/* total # zone numbers in a V1 inode */
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

#define V2_NR_TZONES      10
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

#define V1_INODE_SIZE             usizeof (d1_inode)  /* bytes in V1 dsk ino */
#define V1_ZONE_NUM_SIZE           usizeof (zone1_t)  /* # bytes in V1 zone  */
#define V1_INODES_PER_BLOCK (STATIC_BLOCK_SIZE/V1_INODE_SIZE)
#define V1_NR_DZONES       7
#define V1_INODES_PER_BLOCK (STATIC_BLOCK_SIZE/V1_INODE_SIZE)
#define V1_INDIRECTS (STATIC_BLOCK_SIZE/V1_ZONE_NUM_SIZE) 


#define V2_NR_DZONES       7
#define V2_INODE_SIZE             usizeof (d2_inode)  /* bytes in V2 dsk ino */
#define V2_ZONE_NUM_SIZE            usizeof (zone_t)  /* # bytes in V2 zone  */
#define V2_INDIRECTS(b)   ((b)/V2_ZONE_NUM_SIZE)
#define V2_INODES_PER_BLOCK(b) ((b)/V2_INODE_SIZE)/* # V2 dsk inodes/blk */

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


int rawfd;	/* File descriptor to open device. */
char *rawdev;	/* Name of device. */

static struct super_block super;	/* Superblock of file system */
static char dirbuf[MAX_BLOCK_SIZE];	/* Scratch/Directory block. */

#define scratch dirbuf

void report(char *label);
void fatal(char *label);

#define BYTE_SWAP          0	/* tells conv2/conv4 to swap bytes */
unsigned conv2(int norm,int w);
long conv4(int norm,long x);
void readblock(moff_t blk, char *buf, int block_size);
void showsuperinfo(struct super_block * p);

bit_t alloc_bit(struct super_block *sp, int map, bit_t origin);
#endif	/* __testfs_h */
