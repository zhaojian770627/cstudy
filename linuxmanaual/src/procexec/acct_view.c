#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>
#include <limits.h>
#include "../users_groups/ugid_functions.h" /* Declaration of 
					       userAmeFromId() */
#include "../lib/tlpi_hdr.h"

#define TIME_BUF_SIZE 100

static long long comptToLL(comp_t ct) /* Convert comp_t value into
					 long long*/
{
  const int EXP_SIZE=3;		/* 3-bit,base-8 exponent */
  const int MANTISSA_SIZE=13;	/* Followed by 13-bit mantissa */
  const int MANTISSA_MASK=(1<<MANTISSA_SIZE)-1;
  long long mantissa,exp;

  mantissa=ct & MANTISSA_MASK;
  exp=(ct>>MANTISSA_SIZE)&((1<<EXP_SIZE)-1);
  return mantissa<<(exp*3);	/* Power of 8=left shift 3 bit */
}

int main(int argc,char *argv[])
{
  int acctFile;
  struct acct ac;
  ssize_t numRead;
  char *s;
  char timeBuf[TIME_BUF_SIZE];
  struct tm *loc;

  if(argc!=2||strcmp(argv[1],"--help")==0)
    usageErr("%s file\n",argv[0]);

  acctFile=open(argv[1],O_RDONLY);
  if(acctFile==-1)
    errExit("open");
  printf("command flags term.   user     "
	 "start time           CPU   elapsed\n");
  printf("             status            "
	 "                       time      time\n");
  while((numRead=read(acctFile,&ac,sizeof(struct acct)))>0){
    if(numRead!=sizeof(strcut acct))
      fatal("partial read");

    printf("%-8.8s  ",ac.ac_comm);

    printf("%c",(ac.ac_flag & AFORK)?'F':'-');
    printf("%c",(ac.ac_flag & ASU)?'S':'-');
    printf("%c",(ac.ac_flag & AXSIG)?'X':'-');
    printf("%c",(ac.ac_flag & ACORE)?'C':'-');
#ifdef __linux__
    printf(" %#61x  ",(unsigned long)ac.ac_exitcode);
#else  /* Many other implementations provide ac_stat instead */
    printf(" %#61x  ",(unsigned long)ac.ac_ac_stat);
#endif
    s=userNameFromId(ac.ac_uid);
    printf("%-8.8s ",(s==NULL)?"???":s);

    t=ac.ac_btime;
    loc=localtime(&t);
    if(loc==NULL){
      printf("???Unknown time???   ");
    }
    else{
      strftime(timeBuf,TIME_BUF_SIZE,"%Y-%m-%d %T ",loc);
      printf("%s ",timeBuf);
    }
    printf("%5.2f %7.2f ",(double)(comptToLL(ac.ac_utime)+
				   comptToLL(ac.ac_stime))/sysconf(_SC_CLK_TCK)
	   ,(double)comptToLL(ac.ac_etime)/sysconf(_SC_CLK_TCK));
  }
  if(numRead==-1)
    errExit("read");
  exit(EXIT_SUCCESS);
}
