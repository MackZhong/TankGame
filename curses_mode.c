#include <curses.h>
#include <locale.h>
#include <stdlib.h>

int main() {
  setlocale(LC_ALL, "C");

  WINDOW *win_main = initscr(); /* Start curses mode 		  */
  if (NULL == win_main) {
    printf("Init curses failed.\n");
    return -1;
  }
  printf("Curses initialized.\n");

  if (win_main != stdscr) {
    printf("Screen initialization error.\n");
    endwin();
    return -2;
  }

  clear();
  noecho();
  cbreak(); // Line buffering disabled. pass on everything
  addstr("Curses started.\n");
  printw("Input 's' to cooked mode, 'q' to quit.\n"); /* Print Hello World
                                                       */
  refresh(); /* Print it on to the real screen */

  int chr = getch();
  if ('s' == chr) {
    // get back to cooked mode (normal line buffering mode) temporarily.
    def_prog_mode(); /* Save the tty modes		  */
    endwin();        /* End curses mode temporarily	  */

    system("/bin/sh"); /* Do whatever you like in cooked mode */

    // To get back to curses mode
    reset_prog_mode(); /* Return to the previous tty mode*/
                       /* stored by def_prog_mode() 	  */

    printw("Baock curses mode.\n"); /* Back to curses use the full    */

    // refresh(); /* Do refresh() to restore the	  */
    /* Screen contents		  */
  } else if ('q' == chr) {
    printw("EXIT.\n");
  }

  refresh(); /* capabilities of curses	  */

  printw("Press any key.\n");
  getch();
  /* The curses screen is not in the same console with the program, so it SHOULD
   * add getch() before endwin() to keep the curses scheen visible!*/

  endwin(); /* End curses mode		  */
  printf("Exit curses.\n");

  return 0;
}