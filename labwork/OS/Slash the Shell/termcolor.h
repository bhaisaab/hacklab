/****************** yLabs Original Work ***************************************
*	Title		  :	yLabs Graphics Library ANSI C VERSION
*	Author 		: ROHIT YADAV
*	Created 	: Saturday, 26 July 2008
*	Revised 	:	Sunday, 27 July 2008
*	Version 	:	0.1
*	
*	Email 		: rohityadav89@gmail.com
*
*	yLabs Graphics Library makes *NIX Terminal quite colourful
*   Copyright (C) 2008  Rohit Yadav, yLabs.
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
******************************************************************************/

#ifndef __TERMCOLOR__
#define __TERMCOLOR__ 1

#include <stdio.h>
#include <stdlib.h>
	
	//0=BLACK 1=RED 2=GREEN 3=YELLOW 4=BLUE 5=MAGENTA 6=CYAN 7=WHITE
	//30+ 90+(LIGHT)  -> FOREGROUND
	//40+ 100+(LIGHT) -> BACKGROUND
	//1 = BOLD; 0 = Normal; 4 = Underline; 5 = Blink ON  
	
int color_printf( char * , int );
int color_printf_with_bftn( char * , int , int , int , int );
int resetScreen();
int clearScreen();
int invertColor();


#endif
