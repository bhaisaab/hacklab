/*
***************************************************************************************
***************************************************************************************
***
***     File: os_task.h
***
***     Project: cocoOS
***
***     Copyright 2009, 2010 Peter Eckstrand
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


    Version: 1.2.0

    Change log:
    2009-07-06: 1.0.0: First release
	2010-03-02: 1.1.0: Added OS_SUSPEND_TASK()
	2010-04-13: 1.2.0: Modified OS_SUSPEND_TASK() to take task id as parameter. Any task
					   can suspend any other task.
					   Added OS_RESUME_TASK() that restores the state of the task to the
					   state it had when it was suspended


***************************************************************************************
*/
#ifndef OS_TASK_H__
#define OS_TASK_H__

/** @file os_task.h Task header file*/

#include "os_defines.h"

typedef struct tcb tcb;


/*********************************************************************************/
/*  OS_SUSPEND_TASK( id )                                                 *//**
*
*   Macro for suspending a task
*
*		@param id Task id of the task to suspend
*
*		@remarks If the task to suspend is the same as the current running task, the
task is immediately suspended and other tasks are scheduled to execute.
If the task to suspend is another than the current task, that task is immediately put
in pending state, and the current task continues to execute. @n \b Usage: @n
* @code

static uint8_t ledTaskId;

static int led_task(void) {
 OS_BEGIN;
  for(;;) {
	led_toggle();
	OS_WAIT_TICKS( 100 );
  }
 OS_END;
 return 0;
}


static int button_task(void) {
 OS_BEGIN;
 if ( buttonPressed ) {
   OS_SUSPEND_TASK( ledTaskId );
 }
 OS_END;
 return 0;
}


int main( void ) {
	...
	ledTaskId = os_task_create( led_task, 1 );
	os_task_create( button_task, 2 );
	...
}

 @endcode
 *******************************************************************************/
#define OS_SUSPEND_TASK( id )    OS_SUSPEND_TASK_( id )
#define OS_SUSPEND_TASK_( id )		do {\
								    os_task_suspend( id );\
                                    if ( id == running_tid ) {\
                                        OS_SCHEDULE;\
                                    }\
								} while (0)


/*********************************************************************************/
/*  OS_RESUME_TASK( id )                                                 *//**
*
*   Macro for resuming a task
*
*		@param id Task id of the task to resume
*
*		@remarks The macro has no effect if the task is not in the PENDING state @n \b Usage: @n
* @code

static uint8_t ledTaskId;

static int led_task(void) {
 OS_BEGIN;
  for(;;) {
	led_toggle();
	OS_WAIT_TICKS( 100 );
  }
 OS_END;
 return 0;
}


static int button_task(void) {
 OS_BEGIN;
 if ( button_1_Pressed ) {
   OS_SUSPEND_TASK( ledTaskId );
 }
 else if ( button_2_Pressed ){
   OS_RESUME_TASK( ledTaskId );
 }
 OS_END;
 return 0;
}


int main( void ) {
	...
	ledTaskId = os_task_create( led_task, 1 );
	os_task_create( button_task, 2 );
	...
}

 @endcode
 *******************************************************************************/
#define OS_RESUME_TASK( id )    OS_RESUME_TASK_( id )
#define OS_RESUME_TASK_( id )		do {\
								    os_task_resume( id );\
                                    if ( id == running_tid ) {\
                                        OS_SCHEDULE;\
                                    }\
								} while (0)

uint8_t os_task_create( taskproctype taskproc, uint8_t prio );
uint8_t os_task_highest_prio_ready_task( void );
void os_task_ready_set( uint8_t tid );
void os_task_pending_set( uint8_t tid );
void os_task_suspend( uint8_t tid );
void os_task_resume( uint8_t tid );
uint8_t os_task_prio_get( uint8_t tid );
taskproctype os_task_taskproc_get( uint8_t tid );
void os_task_clear_wait_queue( uint8_t tid );
void os_task_wait_time_set( uint8_t tid, uint16_t time );
void os_task_wait_event( uint8_t tid, uint8_t eventId, uint8_t waitSingleEvent );
void os_task_tick( void );
void os_task_signal_event( uint8_t evId );




#endif
