/*
***************************************************************************************
***************************************************************************************
***
***     File: os_kernel.c
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


#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include "cocoos.h"



/*********************************************************************************/
/*  void os_init()                                              *//**
*
*   Initializes the scheduler.
*
*		@return None.
*
*		@remarks \b Usage: @n Should be called early in system setup, before starting the task
*       execution
*
*
*       @code
int main(void) {
	system_init();
	os_init();
	...
}
*		@endcode
*
*		 */
/*********************************************************************************/
void os_init( void ) {
	running_tid = NO_TID;
}




void os_schedule( void ) {
	taskproctype taskproc;

    /* Find the highest prio task ready to run */
	running_tid = os_task_highest_prio_ready_task();

	if ( running_tid != NO_TID) {
        taskproc = os_task_taskproc_get( running_tid );
		taskproc();
	}
}




/*********************************************************************************/
/*  void os_start()                                              *//**
*
*   Starts the task scheduling
*
*
*		@return None.
*
*		@remarks \b Usage: @n Should be the last line of main.
*
*
*
*       @code
int main(void) {
	system_init();
	os_init();
	os_create_task( myTaskProc, 1 );
	...
	os_start();
	return 0;
}
*		@endcode
*
*/
/*********************************************************************************/
void os_start( void ) {
	enable_interrupts();
	running_tid = NO_TID;
	for (;;){
		os_schedule();
	}
}



/*********************************************************************************/
/*  void os_tick()                                              *//**
*
*   Tick function driving the kernel
*
*
*		@return None.
*
*		@remarks \b Usage: @n Should be called periodically. Preferably from the clock tick ISR.
*
*
*
*
*       @code
ISR(SIG_OVERFLOW0) {
	...
    os_tick();
}
*		@endcode
*
*/
/*********************************************************************************/
void os_tick( void ) {
    os_task_tick();
}
