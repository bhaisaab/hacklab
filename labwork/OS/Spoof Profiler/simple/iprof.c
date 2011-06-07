/* STD C */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>     /* signal() etc... */
#include <string.h>     /* memset() */
#include <errno.h>
#include <time.h>


/* POSIX */
#include <sys/types.h>  /* For pid_t */      
#include <sys/wait.h>   /* wait3/4() */
#include <sys/time.h>   /* timeval etc. */
#include <sys/times.h>
#include <unistd.h>     /* fork() etc. */

#define HZ (CLOCKS_PER_SEC * 10)

int
main(int argc, char* argv[])
{

  char *program = argv[1];

  pid_t pid;  /* Pid of child.  */
  int status;
  
  clock_t c_t1, c_t2;
  clock_t real, sys, usr;
  struct tms tms_t1, tms_t2;

  pid = fork ();  /* Run "Program" as child process.  */
  
  c_t1 = times (&tms_t1);

  switch (pid)
  {
    case -1: 
      perror ("cannot fork"); exit(1); break;

    case 0:       
      /* execvp(char*, char**) runs programs as separate process, 
         is a POSIX system routine */
      execvp (argv[1], argv);
      fprintf (stderr, "cannot run %s\n", program);
      /* Check if errno is ENOENT: No such file or directory */
      /* 17: (EEXIST) File Exists, 10: (ENOENT) No child process*/
      /* _exit closes any open file descriptor, pid etc. */
      _exit (errno == ENOENT ? 2 : 17); break;
    
    default:
      //printf ("Spoof: Child's PID = %d\n", getpid());
      //printf ("Spoof: Parent's PID is %d\n", getppid());
      pid = wait(&status); // waiting for child process(es) to end

      c_t2 = times (&tms_t2);

      real = c_t2 - c_t1;
      sys = (tms_t2.tms_cstime - tms_t1.tms_cstime);
      usr = (tms_t2.tms_cutime - tms_t1.tms_cutime);

      printf("\nProfiling %s...\nGenerating Report...\n", program);

      printf("Real time = %ld.%ld\n", real / HZ, real % HZ * (1000000 / HZ));
      printf("System Time = %0.2f\n", (float) sys / HZ );
      printf("User Time = %0.2f\n", (float) usr / HZ);
      printf("CPU Usage = %.02f%%\n", (float) (usr+sys) * 100 / real );
      printf("Value returned by child process = %d\n", status);
  }

  return 0;

}


