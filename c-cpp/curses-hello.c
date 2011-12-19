/*
 * Compile: gcc <file>.c -lncurses
 */
#include <ncurses.h>

int
main()
{	
  initscr();
  printw("Hello Term Folks!");
  refresh();
  getch();
  endwin();
  return 0;
}
