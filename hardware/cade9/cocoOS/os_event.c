/*
***************************************************************************************
***************************************************************************************
***
***     File: os_event.c
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






#include <inttypes.h>
#include <stdlib.h>
#include "cocoos.h"
#include "stdarg.h"



/* Event type */
struct event {
		uint8_t id;
		uint8_t signaledByTid;
		};

/* Keeping track of number of created events */
static uint8_t nEvents = 1;


/*********************************************************************************/
/*  os_event_type* os_create_event()                                              *//**
*
*   Creates an event.
*
*		@return Returns a pointer to the created event.
*
*		@remarks \b Usage: @n An event is created by declaring a variable of type os_event_type* and then
*		assigning the os_create_event(value) return value to that variable.
*
*
*       @code
*       os_event_type* myEvent;
*       myEvent = os_create_event();
*		@endcode
*
*		 */
/*********************************************************************************/

os_event_type* os_create_event( void ) {
	os_event_type *temp_event =  malloc( sizeof( os_event_type ) );
	temp_event->id = nEvents;

	/* The events get id's 1, 2, 4, 8, 16 ... */
	nEvents *= 2;

	return temp_event;
}


void os_wait_event(uint8_t tid, os_event_type *ev, uint8_t waitSingleEvent) {
	os_task_wait_event( tid, ev->id, waitSingleEvent );
}


void os_signal_event( os_event_type *ev ) {
    os_task_signal_event( ev->id );
}


void os_event_set_signaling_tid( os_event_type *ev, uint8_t tid ) {
	ev->signaledByTid = tid;
}


/*********************************************************************************/
/*  uint8_t os_event_get_signaling_tid()                                              *//**
*
*   Gets the Task Id of the task that signaled the event.
*
*
*    @param pEv Pointer to an event
*
*    @return Id of task that signaled the event.
*
*    @remarks \b Usage: @n A task can make a call to this function when it has resumed
execution after waiting for an event to find out which other task signaled the event.
*
*
*       @code
*       OS_WAIT_SINGLE_EVENT(pEvent);
*       signalingTask = os_event_get_signaling_tid(pEvent);
*       if ( signalingTask == Task2_id ) {
*         ...
*       }
*		@endcode
*
*		 */
/*********************************************************************************/
uint8_t os_event_get_signaling_tid( os_event_type *pEv ) {
	return pEv->signaledByTid;
}


void os_wait_multiple( uint8_t waitAll, ...) {
	os_event_type *event;
	va_list args;
	va_start( args, waitAll );
	os_task_clear_wait_queue( running_tid );
	event = va_arg( args, os_event_type* );

	do {
		os_task_wait_event( running_tid, event->id, !waitAll );
		event = va_arg( args, os_event_type* );
	} while ( event != (void*)0 );

	va_end(args);
}
