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

#endif	/* __testfs_h */
