/*
***************************************************************************************
***************************************************************************************
***
***     File: os_sem.h
***
***     Project: cocoOS
***
***     Copyright 2009 Peter Eckstrand
***
***************************************************************************************
	This file is part of cocoOS.

    cocoOS is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    cocoOS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with cocoOS.  If not, see <http://www.gnu.org/licenses/>.
***************************************************************************************


    Version: 1.0.0

    Change log:
    2009-07-06: 1.0.0 First release


***************************************************************************************
*/
#ifndef OS_SEM_H
#define OS_SEM_H

/** @file os_sem.h Semaphore header file*/

#include "cocoos.h"

/*********************************************************************************/
/*  OS_WAIT_SEM(sem)                                                 *//**
*
*   Macro for aquiring a semaphore.
*
*		@param sem Pointer to a semaphore.
*
*		@remarks \b Usage: @n
* @code
os_sem_type* mySem;
main() {
 ...
 mySem = os_create_sem( 0 );
 ...
}

static int myTask(void) {
 OS_BEGIN;
  ...
  OS_WAIT_SEM( mySem );
  ...
 OS_END;
 return 0;
}
 @endcode
 *******************************************************************************/
#define OS_WAIT_SEM(sem)    OS_WAIT_SEM_(sem)
#define OS_WAIT_SEM_(sem)		do {\
								if ( os_sem_larger_than_zero( sem )  )\
									os_sem_decrement( sem );\
								else\
								{\
									os_task_pending_set( running_tid );\
                                    list_add( running_tid, os_sem_get_wait_list( sem ) );\
									OS_SCHEDULE;\
								}\
						       } while (0)


/*********************************************************************************/
/*  OS_SIGNAL_SEM(sem)                                                 *//**
*
*   Macro for releasing a semaphore.
*
*		@param sem Pointer to a semaphore.
*
*		@remarks \b Usage: @n
* @code
os_sem_type* mySem;
main() {
 ...
 mySem = os_create_sem( 0 );
 ...
}

static int myTask(void) {
 OS_BEGIN;
  ...
  OS_SIGNAL_SEM( mySem );
  ...
 OS_END;
 return 0;
}
 @endcode
 *******************************************************************************/
#define OS_SIGNAL_SEM(sem)  OS_SIGNAL_SEM_(sem)
#define OS_SIGNAL_SEM_(sem) 	do {\
								if ( list_is_empty( os_sem_get_wait_list( sem ) ) )\
								   os_sem_increment( sem );\
								else\
								 {\
									list_move_highest_prio_to_ready( os_sem_get_wait_list( sem ) );\
									OS_SCHEDULE;\
								 }\
							   } while (0)

typedef struct sem os_sem_type;



os_sem_type* os_create_sem( uint8_t value );
uint8_t os_sem_larger_than_zero( os_sem_type *sem );
void os_sem_decrement( os_sem_type *sem );
void os_sem_increment( os_sem_type *sem );
uint8_t* os_sem_get_wait_list( os_sem_type *sem );


#endif
