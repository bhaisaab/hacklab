/* timeman.h - Time Manager, Child Process handlers.
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

#ifndef _TIMEMAN_H
#define _TIMEMAN_H 1

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

#endif /* _TIMEMAN_H */
