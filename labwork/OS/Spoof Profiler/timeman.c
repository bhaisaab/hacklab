/* timeman.c - Time Manager, Child Process handlers.
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
