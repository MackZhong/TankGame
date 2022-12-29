#include <ncurses.h>
#include <stdlib.h>

// ncurses terminal game
int main(void) {

  initscr();                   /* Start curses mode 		  */
  printw("Hello ncurses !!!"); /* Print Hello World		  */
  refresh();                   /* Print it on to the real screen */
  getch();                     /* Wait for user input */
  endwin();                    /* End curses mode		  */

  return 0;
}
