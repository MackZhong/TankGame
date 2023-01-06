#include <curses.h>
#include <locale.h>
#include <stdlib.h>

int main() {
  setlocale(LC_ALL, "C");

  WINDOW *winMain = initscr(); /* Start curses mode 		  */
  if (NULL == winMain) {
    printf("Init curses failed.\n");
    return -1;
  }
  printf("Curses initialized.\n");

  if (winMain != stdscr) {
    printf("Screen initialization error.\n");
    endwin();
    return -2;
  }

  // clear();
  // noecho();
  // cbreak(); // Line buffering disabled. pass on everything
  addstr("Curses started.\n");
  printw("Hello Curses !!!\n"); /* Print Hello World		  */
  refresh();                    /* Print it on to the real screen */

  // get back to cooked mode (normal line buffering mode) temporarily.
  // def_prog_mode(); /* Save the tty modes		  */
  // endwin();        /* End curses mode temporarily	  */

  // system("/bin/sh"); /* Do whatever you like in cooked mode */

  // // To get back to curses mode
  // reset_prog_mode(); /* Return to the previous tty mode*/
  //                    /* stored by def_prog_mode() 	  */
  // refresh();         /* Do refresh() to restore the	  */
  /* Screen contents		  */

  printw("Another String\n"); /* Back to curses use the full    */
  refresh();                  /* capabilities of curses	  */

  endwin(); /* End curses mode		  */

  return 0;
}