/*
***************************************************************************************
***************************************************************************************
***
***     File: os_defines.h
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
#ifndef _os_defs
#define _os_defs

#include <avr/interrupt.h>
#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif

#define MAX_TASKS 6
#define NO_TID	255

#define enable_interrupts()		sei()
#define disable_interrupts()	cli()

typedef uint8_t		Bool;



typedef int (*taskproctype) (void);





#endif
