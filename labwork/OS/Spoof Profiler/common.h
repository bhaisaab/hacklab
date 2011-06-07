/* common.h - Header file includes for Spoof profiler
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

/* STD C */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>     /* signal() etc... */
#include <string.h>     /* memset() */
#include <errno.h>
#include <limits.h>     /* LONG_MAX */

/* POSIX */
#include <sys/param.h>  /* For getpagesize, maybe.  */
#include <sys/types.h>  /* For pid_t */      
#include <sys/wait.h>   /* wait3/4() */
#include <sys/time.h>   /* timeval etc. */
#include <unistd.h>     /* fork() etc. */

#if defined(sun3) || defined(hp300) || defined(ibm032)
#define TICKS_PER_SEC 50
#endif

#if defined(mips)
#define TICKS_PER_SEC 250
#endif

#ifndef TICKS_PER_SEC
#define TICKS_PER_SEC 100
#endif

/* The number of milliseconds in one `tick' used by the `rusage' structure.  */
#define MSEC_PER_TICK (1000 / TICKS_PER_SEC)

/* Return the number of clock ticks that occur in M milliseconds.  */
#define MSEC_TO_TICKS(m) ((m) / MSEC_PER_TICK)

#define UL unsigned long

/* PAGE SIZE */
#ifdef VMS
#define getpagesize() 512
#endif

#ifdef _SC_PAGESIZE
#define getpagesize() sysconf(_SC_PAGESIZE)
#else

#ifdef EXEC_PAGESIZE
#define getpagesize() EXEC_PAGESIZE
#else
#ifdef NBPG
#define getpagesize() NBPG * CLSIZE
#ifndef CLSIZE
#define CLSIZE 1
#endif /* no CLSIZE */
#else /* no NBPG */
#ifdef NBPC
#define getpagesize() NBPC
#else /* no NBPC */
#ifdef PAGESIZE
#define getpagesize() PAGESIZE
#endif
#endif /* NBPC */
#endif /* no NBPG */
#endif /* no EXEC_PAGESIZE */
#endif /* no _SC_PAGESIZE */


/* portability declarations for GNU time */

#if __STDC__
# define PARAMS(x) x
# define PTR void *
#else
# define PARAMS(s) ()
# define PTR char *
#endif




