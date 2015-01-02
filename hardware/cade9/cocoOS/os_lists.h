/*
***************************************************************************************
***************************************************************************************
***
***     File: os_list.h
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
#ifndef OS_LISTS_H
#define OS_LISTS_H

#include "os_defines.h"


void list_add(uint8_t tid,uint8_t *list);
void list_remove(uint8_t tid,uint8_t *list);
uint8_t list_tid_in_list( uint8_t tid, uint8_t *list);
uint8_t list_is_empty(uint8_t *list);
void list_move_highest_prio_to_ready(uint8_t *list);
void list_set_task_wait_event( uint8_t tid, uint8_t id, uint8_t waitSingleEvent );
void list_clear_wait_event( uint8_t tid, uint8_t id );

#endif
