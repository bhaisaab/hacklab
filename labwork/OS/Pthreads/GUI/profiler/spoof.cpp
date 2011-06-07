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

#include "spoof.h"

#include "common.h"
#include "timeman.h"

/* Path of the program to profile */
char *program_path;
char *bin_name;




#include <sys/time.h>
/* For timeval structure:
struct timeval
{
  long tv_sec;
  long tv_usec;
};
*/

/* This rusage structure measures nanoseconds instead of microseconds.  */
#if HAVE_SYS_RUSAGE_H
#include <sys/rusage.h>
#define TV_MSEC tv_nsec / 1000000
#else
#include <sys/resource.h>
#define TV_MSEC tv_usec / 1000
#endif

/* Process resource usage structure:
struct rusage
  {
    struct timeval ru_utime;	// User time used.
    struct timeval ru_stime;	//System time used.
    int ru_maxrss, ru_ixrss, ru_idrss, ru_isrss,
    ru_minflt, ru_majflt, ru_nswap, ru_inblock,
    ru_oublock, ru_msgsnd, ru_msgrcv, ru_nsignals,
    ru_nvcsw, ru_nivcsw;
  };
*/

/* Information on the resources used by a child process.  */
typedef struct
{
  int status;
  struct rusage ru;
  struct timeval start, elapsed; /* Wallclock time of process.  */
} TIMEMAN; /* Time Manager */

/* Prepare to measure a child process.  */
void timeman_start (TIMEMAN *resp);

/* Wait for and fill in data on child process PID.  */
int timeman_end (pid_t pid, TIMEMAN *resp);




#if !HAVE_WAIT3
#include <sys/times.h>
#ifndef HZ
#include <sys/param.h>
#endif
#if !defined(HZ) && defined(CLOCKS_PER_SEC)
#define HZ CLOCKS_PER_SEC
#endif
#if !defined(HZ) && defined(CLK_TCK)
#define HZ CLK_TCK
#endif
#ifndef HZ
#define HZ 60
#endif
#endif

#include "timeman.h"
#include "common.h"

/* Prepare to measure a child process.  */

void
timeman_start (TIMEMAN *resp)
{
#if _SYS_TIME_H
  gettimeofday (&resp->start, (struct timezone *) 0);
#else
  long value;
  struct tms tms;

  value = times (&tms);
  resp->start.tv_sec = value / HZ;
  resp->start.tv_usec = ( value % HZ ) * 1000000 / HZ;
#endif
}

/* Wait for and fill in data on child process PID.
   Return 0 on error, 1 if ok.  */
int
timeman_end (pid_t pid, TIMEMAN *resp)
{
  int status;

#if _SYS_TIME_H
  pid_t caught;

  /* Ignore signals, but don't ignore the children.  When wait3
     returns the child process, set the time the command finished. */
  while ((caught = wait4 (pid, &status, 0, &resp->ru)) != pid)
    {
      if (caught == -1)
        return 0;
    }

  gettimeofday (&resp->elapsed, (struct timezone *) 0);

//  if( getrusage(RUSAGE_CHILDREN, &(resp->ru)) == 0)
//     printf("rUsage got!\n");

#else  /* !_SYS_TIME_H */
  long value;
  struct tms tms;

  pid = wait (&status);
  if (pid == -1)
    return 0;

  value = times (&tms);

  memset (&resp->ru, 0, sizeof (struct rusage));

  if( getrusage(RUSAGE_CHILDREN, &(resp->ru)) == 0)
     printf("rUsage got!\n");

  resp->ru.ru_utime.tv_sec = tms.tms_cutime / HZ;
  resp->ru.ru_stime.tv_sec = tms.tms_cstime / HZ;

#if HAVE_SYS_RUSAGE_H
  printf("HAVE RUSAGE");
  resp->ru.ru_utime.tv_nsec = tms.tms_cutime % HZ * (1000000000 / HZ);
  resp->ru.ru_stime.tv_nsec = tms.tms_cstime % HZ * (1000000000 / HZ);
#else
  printf("DON't HAVE RUSAGE");
  resp->ru.ru_utime.tv_usec = tms.tms_cutime % HZ * (1000000 / HZ);
  resp->ru.ru_stime.tv_usec = tms.tms_cstime % HZ * (1000000 / HZ);
#endif

  resp->elapsed.tv_sec = value / HZ;
  resp->elapsed.tv_usec = value % HZ * (1000000 / HZ);
#endif  /* !_SYS_TIME_H */

  resp->elapsed.tv_sec -= resp->start.tv_sec;
  if (resp->elapsed.tv_usec < resp->start.tv_usec)
    {
      /* Manually carry a one from the seconds field.  */
      resp->elapsed.tv_usec += 1000000;
      --resp->elapsed.tv_sec;
    }
  resp->elapsed.tv_usec -= resp->start.tv_usec;

  resp->status = status;

  return 1;
}

/* Run the program to profile.
   Put the statistics in *RESP.  */
static void
run_program (char **program, TIMEMAN *resp)
{
  pid_t pid;  /* Pid of child.  */
  
  /* Stores func ptrs returned by signal() */
//  sighandler_t interrupt_signal, quit_signal;

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
      //printf ("Spoof: Parent's PID = %d\n", getpid());
      //printf ("Spoof: Child's PID is %d\n", pid);
      //printf ("\nForked Child Process, Intialising Program...\n\n");
      ;
  }

  /* Have signals kill the child but not self (in case child is still running).  */
//  interrupt_signal = signal (SIGINT, SIG_IGN);
//  quit_signal = signal (SIGQUIT, SIG_IGN);

  if (timeman_end (pid, resp) == 0)
    perror ("Error waiting for child process");

  /* Enable signals, in case */
//  signal (SIGINT, interrupt_signal);
//  signal (SIGQUIT, quit_signal);
}

long spoof (int argc, char* argv)
{
  TIMEMAN res;

  /* Store path of the program */
  bin_name = argv;
  program_path = argv;

  /* Run the program and store stats in res */
  run_program (&program_path, &res);

  /* Generate Stats */
  TIMEMAN *resp = &res;

  unsigned long r;		/* Elapsed real milliseconds.  */
  unsigned long time;		/* Elapsed virtual (CPU) milliseconds.  */

  r = resp->elapsed.tv_sec * 1000 + resp->elapsed.tv_usec / 1000;

  time = resp->ru.ru_utime.tv_sec * 1000 + resp->ru.ru_utime.TV_MSEC +
    resp->ru.ru_stime.tv_sec * 1000 + resp->ru.ru_stime.TV_MSEC;

long t = resp->ru.ru_stime.tv_sec +
                       resp->ru.ru_stime.TV_MSEC / 10 + resp->ru.ru_utime.tv_sec +
                       resp->ru.ru_utime.TV_MSEC / 10;

  return r;
}
