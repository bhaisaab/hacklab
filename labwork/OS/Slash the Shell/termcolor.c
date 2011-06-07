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

#include "termcolor.h"

/*enum COLOR = {BLACK=0,RED,GREEN,YELLOW,BLUE,MAGENTA,CYAN,WHITE,RESET};*/

int invertColor()
{
	printf("\e[7m]");
	return 0;
}

// *** clearScreen ***
int clearScreen()
{
	printf("\x1B[2J");			//ESC[2J   Clear screen and home cursor
	printf("\x1B[u");			//ESC[u    Return to saved cursor position
	printf("\x1B[0;0H");		//ESC[#;#H Moves cusor to line #, column #
	return 0;
}

// *** reset ***
int resetScreen()
{
	printf("\x1B[00m");
	return 0;
}

int color_printf( char *s , int foreground)
{
	printf("\x1B[%dm",foreground);
	printf("%s", s);
	resetScreen();
	return 0;
}

int color_printf_with_bftn( char *s , int foreground, int background, int tab, int nl)
{
	while(nl)
	{ printf("\n"); nl--; }
	while(tab)
	{ printf("\t"); tab--; }
	printf("\x1B[%d;%dm",foreground ,background);
	printf("%s", s);
	resetScreen();
	return 0;
}

/********************************************************   
 ******** WARNING:  ORIGINAL WORK by ROHIT YADAV ********  
 ******** Using ESCAPE CODES for *NIX like OS 	 ********  
 ******** Tested successfully on Linux , Mac OSX ********  
 ******** Copyright 2008 Rohit Yadav, yLabs. 	 ********   
 ********************************************************/
/*---------> End Of File<--------*/
