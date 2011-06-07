# Slash Makefile
# Authors: Rohit Yadav <rohityadav89@gmail.com> and Abhishek Kumar.
# Copyright (C) 1994 Free Software Foundation, Inc.

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# Note: Copy readline source in this directory or modify linker...

EXECUTABLES = slash
CFLAGS  = -g -I./readline/ -I.
LDFLAGS = -g -L./readline/
CC = gcc

.c.o:
	$(CC) $(CFLAGS) -c $<

all: $(EXECUTABLES)

slash: main.c
	$(CC) $(LDFLAGS) $(CFLAGS)  -o $@ main.c slash.c history.c termcolor.c

