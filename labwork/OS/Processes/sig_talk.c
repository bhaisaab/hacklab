/* Example of how processes can talk */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/signal.h>
#include <sys/param.h>

void sighup(int sig); /* routines child will call upon sigtrap */
void sigint(int sig);
void sigquit(int sig);

main()
{ int pid;

  /* get child process */
  
   if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }
    
   if (pid == 0)
     { /* child */
       signal(SIGHUP,sighup); /* set function calls */
       signal(SIGINT,sigint);
       signal(SIGQUIT, sigquit);
       for(;;); /* loop for ever */
     }
  else /* parent */
     {  /* pid hold id of child */
       printf("\nPARENT: sending SIGHUP\n\n");
       kill(pid,SIGHUP);
       sleep(2); /* pause for 3 secs */
       printf("\nPARENT: sending SIGINT\n\n");
       kill(pid,SIGINT);
       sleep(2); /* pause for 3 secs */
       printf("\nPARENT: sending SIGQUIT\n\n");
       kill(pid,SIGQUIT);
       sleep(2);
       for(;;);
     }
}

void sighup(int sig)
{  signal(SIGHUP,sighup); /* reset signal */
   printf("CHILD: I have received a SIGHUP\n");
}

void sigint(int sig)
{  signal(SIGINT,sigint); /* reset signal */
   printf("CHILD: I have received a SIGINT\n");
}

void sigquit(int sig)
{ printf("CHILD: PARENT Killed me!!!\n");
  exit(0);
}

