/*
***************************************************************************************
***************************************************************************************
***
***     File: os_task.c
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


    Version: 1.1.0

    Change log:
    2009-07-06: 1.0.0: First release
	2010-04-13: 1.1.0: os_task_create() returns the task id of the created task.
	                   A variable 'savedState' was added to the tcb structure. This is
					   used for saving the current task state when the task is suspended.
					   When the task is resumed again, the state is restored.
					   os_task_suspend( uint8_t tid ), and os_task_resume( uint8_t tid )
					   was added. Modified os_task_signal_event( uint8_t evId ) so that
					   a task that is in pending state does not get its eventQueue flags
					   cleared if an event is signaled when the task is suspended.


***************************************************************************************
*/


#include "cocoos.h"
#include "os_defines.h"
#include <stdlib.h>

typedef enum {
    RUNNING,
    WAITING_TIME,
    WAITING_EVENT,
    READY,
    PENDING
} TaskState_t;


struct tcb {
    uint8_t tid;
    uint8_t prio;
    TaskState_t state;
    TaskState_t savedState;
    uint8_t eventQueue;
    uint8_t waitSingleEvent;
    uint16_t time;
    taskproctype taskproc;
};

static tcb* task_list[ MAX_TASKS ];
static uint8_t nTasks = 0;


/************************************************************** *******************/
/*  uint8_t os_task_create( taskproctype taskproc, uint8_t prio)                                              *//**
*
*   Creates a task scheduled by the os. The task is put in the ready state.
*
*		@param taskproc Function pointer to the task procedure.
*
*		@param prio Task priority on a scale 0-255 where 0 is the highest priority.
*
*		@return Task id of the created task.
*
*		@remarks \b Usage: @n Should be called early in system setup, before starting the task
*       execution. Only one task per priority level is allowed.
*
*
*       @code
static uint8_t taskId;

int main(void) {
	system_init();
	os_init();
	taskId = os_create_task( myTaskProc, 1 );
	...
}
*		@endcode
*
*/
/*********************************************************************************/
uint8_t os_task_create( taskproctype taskproc, uint8_t prio ) {
    tcb *task = (tcb*)malloc( sizeof(tcb) );
    task->tid = nTasks;
    task->prio = prio;
    task->state = READY;
    task->eventQueue = 0;
    task->waitSingleEvent = 0;
    task->time = 0;
    task->taskproc = taskproc;
    task_list[ nTasks ] = task;
    nTasks++;
    return task->tid;
}


uint8_t os_task_highest_prio_ready_task( void ) {
    uint8_t index;
    uint8_t highest_prio_task = NO_TID;
    uint8_t highest_prio = 255;
    disable_interrupts();

    for ( index = 0; index != nTasks; ++index ) {
	    if ( task_list[ index ]->state == READY ) {
            if ( task_list[ index ]->prio < highest_prio ) {
                highest_prio = task_list[ index ]->prio;
                highest_prio_task = index;
            }
        }
    }

	enable_interrupts();
    return highest_prio_task;
}


void os_task_ready_set( uint8_t tid ) {
    task_list[ tid ]->state = READY;
}


void os_task_pending_set( uint8_t tid ) {
    task_list[ tid ]->state = PENDING;
}


void os_task_suspend( uint8_t tid ) {
    task_list[ tid ]->savedState = task_list[ tid ]->state;
    task_list[ tid ]->state = PENDING;
}


void os_task_resume( uint8_t tid ) {
	if ( task_list[ tid ]->state == PENDING ) {
		task_list[ tid ]->state = task_list[ tid ]->savedState;
	}
}


uint8_t os_task_prio_get( uint8_t tid ) {
    return task_list[ tid ]->prio;
}


taskproctype os_task_taskproc_get( uint8_t tid ) {
    return task_list[ tid ]->taskproc;
}


void os_task_clear_wait_queue( uint8_t tid ) {
    task_list[ tid ]->waitSingleEvent = 0;
    task_list[ tid ]->eventQueue = 0;
    if ( task_list[ tid ]->state == WAITING_EVENT ) {
        task_list[ tid ]->state = READY;
    }
}


void os_task_wait_time_set( uint8_t tid, uint16_t time ) {
    task_list[ tid ]->time = time;
    task_list[ tid ]->state = WAITING_TIME;
}


void os_task_wait_event( uint8_t tid, uint8_t eventId, uint8_t waitSingleEvent ) {
    task_list[ tid ]->eventQueue |= eventId;
    task_list[ tid ]->waitSingleEvent = waitSingleEvent;
    task_list[ tid ]->state = WAITING_EVENT;
}


void os_task_tick( void ) {
    uint8_t index;

    /* Search all tasks and decrement time for waiting tasks */
    for ( index = 0; index != nTasks; ++index ) {
		if ( task_list[ index ]->state == WAITING_TIME ) {

            /* Found a waiting task, is it ready? */
            if ( --task_list[ index ]->time == 0) {
			    task_list[ index ]->state = READY;
			}
		}
	}
}


void os_task_signal_event( uint8_t evId ) {
    uint8_t index;
    uint8_t taskWaitingForEvent;

    for ( index = 0; index != nTasks; index++ ) {

        taskWaitingForEvent = task_list[ index ]->eventQueue & evId;

        if (( taskWaitingForEvent ) && ( task_list[ index ]->state != PENDING )) {

            task_list[ index ]->eventQueue &= ~evId;

            if ( task_list[ index ]->waitSingleEvent || ( task_list[ index ]->eventQueue == 0 ) ) {
                os_task_clear_wait_queue( index );
            }
        }
    }
}
