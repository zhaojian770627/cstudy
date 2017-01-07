#include <sys/wait.h>
#include <sched.h>
#include <time.h>
#include <sys/times.h>
#include "../../time/curr_time.h"
#include "../../lib/tlpi_hdr.h"

int main(int argc,char *argv[])
{
  pid_t childPid=0;		/* PID of waited for chid */
  int j,num;
  int max,min;
  struct tms t;
  struct sched_param sp;
  long clktck=0;
  int count=0;
  clktck=(int)sysconf(_SC_CLK_TCK);

  sp.sched_priority=36;
  if(sched_setscheduler(0,SCHED_FIFO,&sp)==-1)
    errExit("sched_setscheduler");

  min=sched_get_priority_min(SCHED_FIFO);
  max=sched_get_priority_max(SCHED_FIFO);

  printf("max:%d min:%d\n",min,max);
  printf("CLOCKS_PER_SEC:%d\n",CLOCKS_PER_SEC);
  printf("clktck:%d\n",clktck);



  /* Modify  */
  switch(childPid=fork()){
  case -1:
    errExit("fork");
  case 0:			/* Child sleeps for a whiile thenexits */
    printf("child\n");
  default:			/* Parent just continues around loop */
    break;
  }

  clock_t begin=times(&t);
  clock_t end=times(&t);
  double diff=0;  

  int total=0;
  alarm(10);

  for(;;)
    {
      end=times(&t);
      diff=(double)(end-begin);
      count=count+diff;
      
      if(count>=2500000)
	{
	  printf("Flag:%d PID:%d CPU:%d\n",childPid,getpid(),total);
	  total=total+count;
	  count=0;
	  begin=times(&t);
	}

      if(total>=10000000)
	{
	  sched_yield();
	  total=0;
	}
    }  
  exit(EXIT_SUCCESS);
}
