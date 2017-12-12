#include "testfs.h"

void showsize()
{
  printf("unsigned char- %d\n",sizeof(unsigned char));
  printf("unsigned short- %d\n",sizeof(unsigned short));
  printf("long- %d\n",sizeof(long));
  printf("off_t- %d\n",sizeof(off_t));
  printf("inode size -%d\n",sizeof(struct inode));
  printf("super_block size -%d\n",sizeof(struct super_block));
}

int initsuper(struct super_block *sp){
  mdev_t dev;
  int magic;
  int version, native, r;

  sp->s_dev = NO_DEV;		/* restore later */
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

  /* If the super block has the wrong byte order, swap the fields; the magic
   * number doesn't need conversion. */
  sp->s_ninodes =       conv4(native, sp->s_ninodes);
  sp->s_nzones =        conv2(native, (int) sp->s_nzones);
  sp->s_imap_blocks =   conv2(native, (int) sp->s_imap_blocks);
  sp->s_zmap_blocks =   conv2(native, (int) sp->s_zmap_blocks);
  sp->s_firstdatazone = conv2(native, (int) sp->s_firstdatazone);
  sp->s_log_zone_size = conv2(native, (int) sp->s_log_zone_size);
  sp->s_max_size =      conv4(native, sp->s_max_size);
  sp->s_zones =         conv4(native, sp->s_zones);

  /* In V1, the device size was kept in a short, s_nzones, which limited
   * devices to 32K zones.  For V2, it was decided to keep the size as a
   * long.  However, just changing s_nzones to a long would not work, since
   * then the position of s_magic in the super block would not be the same
   * in V1 and V2 file systems, and there would be no way to tell whether
   * a newly mounted file system was V1 or V2.  The solution was to introduce
   * a new variable, s_zones, and copy the size there.
   *
   * Calculate some other numbers that depend on the version here too, to
   * hide some of the differences.
   */
  if (version == V1) {
    sp->s_block_size = STATIC_BLOCK_SIZE;
    sp->s_zones = sp->s_nzones;	/* only V1 needs this copy */
    sp->s_inodes_per_block = V1_INODES_PER_BLOCK;
    sp->s_ndzones = V1_NR_DZONES;
    sp->s_nindirs = V1_INDIRECTS;
  } else {
    if (version == V2)
      sp->s_block_size = STATIC_BLOCK_SIZE;
    if (sp->s_block_size < MIN_BLOCK_SIZE)
      return EINVAL;
    sp->s_inodes_per_block = V2_INODES_PER_BLOCK(sp->s_block_size);
    sp->s_ndzones = V2_NR_DZONES;
    sp->s_nindirs = V2_INDIRECTS(sp->s_block_size);
  }

  if (sp->s_block_size < MIN_BLOCK_SIZE) {
    return EINVAL;
  }
  if (sp->s_block_size > MAX_BLOCK_SIZE) {
    printf("Filesystem block size is %d kB; maximum filesystem\n"
	   "block size is %d kB. This limit can be increased by recompiling.\n",
	   sp->s_block_size/1024, MAX_BLOCK_SIZE/1024);
    return EINVAL;
  }
  if ((sp->s_block_size % 512) != 0) {
    return EINVAL;
  }
  if (SUPER_SIZE > sp->s_block_size) {
    return EINVAL;
  }
  if ((sp->s_block_size % V2_INODE_SIZE) != 0 ||
      (sp->s_block_size % V1_INODE_SIZE) != 0) {
    return EINVAL;
  }

  sp->s_isearch = 0;		/* inode searches initially start at 0 */
  sp->s_zsearch = 0;		/* zone searches initially start at 0 */
  sp->s_version = version;
  sp->s_native  = native;

  /* Make a few basic checks to see if super block looks reasonable. */
  if (sp->s_imap_blocks < 1 || sp->s_zmap_blocks < 1
      || sp->s_ninodes < 1 || sp->s_zones < 1
      || (unsigned) sp->s_log_zone_size > 4) {
    printf("not enough imap or zone map blocks, \n");
    printf("or not enough inodes, or not enough zones, "
	   "or zone size too large\n");
    return(EINVAL);
  }
  sp->s_dev = dev;		/* restore device number */
  return(OK);
}

void getsuper(char *device){
  /* Open device and set variables for readblock. */
  if ((rawfd= open(rawdev= device, O_RDWR)) < 0) fatal(device);

  /* Initialize variables, return size of file system in blocks,
   * (zero on error).
   */
  /* Read superblock. (The superblock is always at 1kB offset,
   * that's why we lie to readblock and say the block size is 1024
   * and we want block number 1 (the 'second block', at offset 1kB).)
   */
  readblock(1, scratch, 1024);
  memcpy(&super, scratch, sizeof(super));
  initsuper(&super);
  showsuperinfo(&super);

}


int main(int argc, char *argv[]) {
  char image[50]="zj.img";
  char device[50]="/dev/loop0";
  char *procv[2]={"/home/zj/git/os/minix/zj",0};
  showsize();  
  getsuper(device); 
  exit(EXIT_SUCCESS);
}

