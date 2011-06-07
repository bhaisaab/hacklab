/* Spoof, Software Profiler displays resource usage (time) of processes.
 * Copyright (C) 2009, Rohit Yadav
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.  
 */

#include "common.h"
#include "timeman.h"

/* Path of the program to profile */
char *program_path;
char *bin_name;

/*
 * Return the number of kilobytes corresponding to a number of pages PAGES.
 * (Actually, we use it to convert pages*ticks into kilobytes*ticks.)
 */
static unsigned long
ptok (unsigned long pages)
{
  static unsigned long ps = 0;
  unsigned long tmp;
  static long size = LONG_MAX;

  /* Initialization */
  if (ps == 0)
    ps = (long) getpagesize ();

  /* Conversion 1024B = 1KB */
  if (pages > (LONG_MAX / ps))
    {				/* Could overflow.  */
      tmp = pages / 1024;	/* Smaller first, */
      size = tmp * ps;		/* then larger.  */
    }
  else
    {				/* Could underflow.  */
      tmp = pages * ps;		/* Larger first, */
      size = tmp / 1024;	/* then smaller.  */
    }

  /* printf("Page Size, ps = %lu, Pages = %lu, Size = %ld\n", ps, pages, size); */

  return size;
}


static void
summarize (FILE *fp, char **program, TIMEMAN *resp)
{
  unsigned long r;		/* Elapsed real milliseconds.  */
  unsigned long v;		/* Elapsed virtual (CPU) milliseconds.  */

  if (WIFSTOPPED (resp->status))
    fprintf (fp, "Program stopped by signal %d\n",
	     WSTOPSIG (resp->status));
  else if (WIFSIGNALED (resp->status))
    fprintf (fp, "Program terminated by signal %d\n",
	     WTERMSIG (resp->status));
  else if (WIFEXITED (resp->status) && WEXITSTATUS (resp->status))
    fprintf (fp, "Program exited with non-zero status %d\n",
	     WEXITSTATUS (resp->status));

  /* Convert all times to milliseconds.  Occasionally, one of these values
     comes out as zero.  Dividing by zero causes problems, so we first
     check the time value.  If it is zero, then we take `evasive action'
     instead of calculating a value.  */

  r = resp->elapsed.tv_sec * 1000 + resp->elapsed.tv_usec / 1000;

  v = resp->ru.ru_utime.tv_sec * 1000 + resp->ru.ru_utime.TV_MSEC +
    resp->ru.ru_stime.tv_sec * 1000 + resp->ru.ru_stime.TV_MSEC;

  /* The Programed that got timed.  */
  fprintf (fp, "\nNow profiling %s\n", program[0]);

  /* Elapsed real (wall clock) time.  */
  if (resp->elapsed.tv_sec >= 3600)	/* One hour -> h:m:s.  */
    fprintf (fp, "Real Time (H:M:S) = %ld:%02ld:%02ld\n",
			 resp->elapsed.tv_sec / 3600,
			 (resp->elapsed.tv_sec % 3600) / 60,
			 resp->elapsed.tv_sec % 60);
  else
    fprintf (fp, "Real Time (M:S.MS) = %ld:%02ld.%02ld\n",	/* -> m:s.us  */
			 resp->elapsed.tv_sec / 60,
			 resp->elapsed.tv_sec % 60,
			 resp->elapsed.tv_usec / 1000 );

  /* System time */
  fprintf (fp, "System Time = %ld.%02ld\n",
		       resp->ru.ru_stime.tv_sec,
		       resp->ru.ru_stime.TV_MSEC / 10);

  /* User time */
  fprintf (fp, "User Time = %ld.%02ld\n",
		       resp->ru.ru_utime.tv_sec,
		       resp->ru.ru_utime.TV_MSEC / 10);

  /* Percent of CPU this job got.  */
  /* % cpu is (total cpu time)/(elapsed time) * 100  */
  /* Or, %CPU = CPU Ticks/Total ticks * 100 */
  if (r > 0)
    fprintf (fp, "CPU Usage = %.02f%%\n", ((float)v * 100 / r));
  else
    fprintf (fp, "CPU Usage (Unknown)%%\n");

  /* Average mem usage == data+stack+text.  */
  fprintf (fp, "Average Memory Usage(Data+Stack+Text) = %lu\n",
		       ( ptok ((UL) resp->ru.ru_idrss) +
		         ptok ((UL) resp->ru.ru_isrss) +
		         ptok ((UL) resp->ru.ru_ixrss) ));

  /* Page size.  */
  fprintf (fp, "Page Size = %ld\n", getpagesize ());

  /* Exit status.  */
  fprintf (fp, "Exit Status = %d\n", WEXITSTATUS (resp->status));

  if (ferror (fp))
    perror ("FP write error");
}

/*
signal(int sig, *fun())
SIG_IGN
    -- a pointer to system ignore function SIG_IGN() which will disregard the sig action
SIG_DFL
    -- a pointer to a system default function SID_DFL(), which will terminate the process upon receipt of sig.

SIGINT 2 interrupt (#defined)

SIGQUIT 3 quit (#defined) 
*/

/* Run the program to profile.
   Put the statistics in *RESP.  */
static void
run_program (char **program, TIMEMAN *resp)
{
  pid_t pid;  /* Pid of child.  */
  
  /* Stores func ptrs returned by signal() */
  sighandler_t interrupt_signal, quit_signal; 

  /* Start profiling */
  timeman_start (resp);

  pid = fork ();  /* Run "Program" as child process.  */

  switch (pid)
  {
    case -1: 
      perror ("cannot fork"); exit(1); break;

    case 0:       
      /* execvp(char*, char**) runs programs as separate process, 
         is a POSIX system routine */
      execvp (program[0], program);
      fprintf (stderr, "cannot run %s\n", program[0]);
      /* Check if errno is ENOENT: No such file or directory */
      /* 17: (EEXIST) File Exists, 10: (ENOENT) No child process*/
      /* _exit closes any open file descriptor, pid etc. */
      _exit (errno == ENOENT ? 2 : 17); break;
    
    default:
      printf ("Spoof: Parent's PID = %d\n", getpid());
      printf ("Spoof: Child's PID is %d\n", pid);
      printf ("\nForked Child Process, Intialising Program...\n\n");
  }

  /* Have signals kill the child but not self (in case child is still running).  */
  interrupt_signal = signal (SIGINT, SIG_IGN);
  quit_signal = signal (SIGQUIT, SIG_IGN);

  if (timeman_end (pid, resp) == 0)
    perror ("Error waiting for child process");

  /* Enable signals, in case */
  signal (SIGINT, interrupt_signal);
  signal (SIGQUIT, quit_signal);

}

int
main (int argc, char* argv[])
{
  TIMEMAN res;
  FILE *outfp;
  outfp = stdout;

  /* Store path of the program */
  bin_name = argv[0];
  program_path = argv[1];

  /* Run the program and store stats in res */
  run_program (&program_path, &res);

  /* Generate Stats */
  summarize (outfp, &program_path, &res);
  fflush (outfp);

  if (WIFSTOPPED (res.status))
    exit (WSTOPSIG (res.status));
  else if (WIFSIGNALED (res.status))
    exit (WTERMSIG (res.status));
  else if (WIFEXITED (res.status))
    exit (WEXITSTATUS (res.status));

  return 0;
}

/*
From man pages:

WIFSTOPPED(status)
    returns true if the child process was stopped by delivery of a signal; this is only possible if the call was done using WUNTRACED or when the child is being traced (see ptrace(2)). 

WSTOPSIG(status)
    returns the number of the signal which caused the child to stop. This macro should only be employed if WIFSTOPPED returned true. 

WIFSIGNALED(status)
    returns true if the child process was terminated by a signal. 
WTERMSIG(status)
    returns the number of the signal that caused the child process to terminate. This macro should only be employed if WIFSIGNALED returned true. 

WIFEXITED(status)
    returns true if the child terminated normally, that is, by calling exit(3) or _exit(2), or by returning from main(). 
WEXITSTATUS(status)
    returns the exit status of the child. This consists of the least significant 16-8 bits of the status argument that the child specified in a call to exit() or _exit() or as the argument for a return statement in main(). This macro should only be employed if WIFEXITED returned true. 
 
*/

