/*
***************************************************************************************
***************************************************************************************
***
***     File: os_sem.c
***
***     Project: cocoOS
***
***     Author: Peter Eckstrand
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
#include "os_sem.h"

struct sem {
		uint8_t value;
		uint8_t waiting_tasks[ MAX_TASKS ];
		};





/*********************************************************************************/
/*  os_sem_type* os_create_sem()                                              *//**
*
*   Creates and initializes a new semaphore.
*
*		@param value Initial value of the semaphore value.
*
*		@return Returns a pointer to the created semaphore.
*
*		@remarks \b Usage: @n A semaphore is created by declaring a variable of type os_sem_type* and then
*		assigning the os_create_sem(value) return value to that variable.
*
*
*       @code
*       os_sem_type* mySem;
*       mySem = os_create_sem(0);
*		@endcode
*
*		 */
/*********************************************************************************/
os_sem_type* os_create_sem( uint8_t value ) {
   uint8_t i;

   /* Allocate memory */
   os_sem_type *temp = malloc( sizeof( os_sem_type ) );

   /* Initialize the value and the waiting list */
   temp->value = value;
   i = MAX_TASKS;
   do {
	--i;
    temp->waiting_tasks[ i ] = NO_TID;

   } while ( i != 0 );

   return temp;
}



uint8_t os_sem_larger_than_zero( os_sem_type *sem) {
    return ( sem->value > 0 );
}


void os_sem_decrement( os_sem_type *sem ) {
    --sem->value;
}


void os_sem_increment( os_sem_type *sem ) {
    ++sem->value;
}


uint8_t *os_sem_get_wait_list( os_sem_type *sem ) {
    return sem->waiting_tasks;
}
