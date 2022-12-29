#include <ncurses.h>
#include <stdlib.h>

// ncurses terminal game
int main(void) {

  initscr(); /* Start curses mode 		  */

  raw(); /* Line buffering disabled. 	*/
  /* control characters: suspend (CTRL-Z), interrupt and quit (CTRL-C).
    In the raw() mode these characters are directly passed to the program
    without generating a signal. In the cbreak() mode these control characters
    are interpreted as any other character by the terminal driver. */
  keypad(stdscr, TRUE); /* We get F1, F2 and arrow keys etc..		*/
  noecho();             /* Don't echo() while we do getch() call. */

  //   halfdelay(1);
  /* Similar to the cbreak() mode in that characters typed are
    immediately available to program. However, it waits for 'X'
    tenths of a second for input and then returns ERR, if no
    input is available.  */

  printw("Type any character to see it in bold\n");
  int ch = getch();           /* If raw() hadn't been called
                               * we have to press enter before it
                               * gets to the program 		*/
  if (ch == KEY_F(1))         /* Without keypad enabled this will */
    printw("F1 Key pressed"); /*  not get to us either	*/
                              /* Without noecho() some ugly escape
                               * charachters might have been printed
                               * on screen			*/
  else {
    printw("The pressed key is ");
    attron(A_BOLD);
    printw("%c", ch);
    attroff(A_BOLD);
  }

  refresh(); /* Print it on to the real screen */
  getch();   /* Wait for user input */
  endwin();  /* End curses mode		  */

  return 0;
}
