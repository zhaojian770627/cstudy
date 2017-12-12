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

#define NR_SUPERS          8
#define NR_INODES         64
#define V2_NR_TZONES      10


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


void report(char *label);
void fatal(char *label);

#endif	/* __testfs_h */
