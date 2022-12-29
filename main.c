#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

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

  int row = 0;
  int col = 0;                /* to store the number of rows and *
                               * the number of columns of the screen */
  getmaxyx(stdscr, row, col); /* get the number of rows and columns */
  char mesg[] = "Just a string";
  mvaddstr(row / 2, (col - strlen(mesg)) / 2, mesg);
  /* Move and put a character string into a given window. */
  /*
   mvaddstr(),mvwaddstr() and waddstr(),
   addnstr(): Puts at most n characters into the screen. If n is negative, then
    the entire string will be added.
  */

  printw("Type any character to see it in bold\n");
  int chr = getch();          /* If raw() hadn't been called
                               * we have to press enter before it
                               * gets to the program 		*/
  if (chr == KEY_F(1))        /* Without keypad enabled this will */
    printw("F1 Key pressed"); /*  not get to us either	*/
                              /* Without noecho() some ugly escape
                               * characters might have been printed
                               * on screen			*/
  else {
    printw("The pressed key is ");
    /*
     mvprintw(), wprintw() and mvwprintw() --> printf()
     vwprintw(), vw_printw() --> vprintf()
    */
    attron(A_BOLD);
    /*
    A_NORMAL    Normal display(no highlight)
    A_STANDOUT  Best highlighting mode of the terminal.
    A_UNDERLINE Underlining
    A_REVERSE   Reverse video
    A_BLINK     Blinking
    A_DIM       Half bright
    A_BOLD      Extra bright or bold
    A_PROTECT   Protected mode
    A_INVIS     Invisible or blank mode
    A_ALTCHARSET Alternate character set
    A_CHARTEXT  Bit-mask to extract a character
    COLOR_PAIR(n) Color-pair number n
    */

    // printw("%c", ch);
    mvaddch(10, 10, chr); /* Move the cursor to a given point, and then print a
                             character. */
    /*
     addch(): put a single character into the current cursor location and
         advance the position of the cursor.
     waddch() and mvwaddch()
    */

    attroff(A_BOLD);
  }

  refresh(); /* Print it on to the real screen */
  getch();   /* Wait for user input */
  /*
   scanw(), mvscanw(), wscanw() and mvwscanw() --> scanf()
   vwscanw() --> vscanf()
   getstr(), wgetstr(), wgetnstr() and mv version: Get strings from the
   terminal. In essence, this function performs the same task as would be
   achieved by a series of calls to getch() until a newline, carriage return, or
   end-of-file is received.
  */

  endwin(); /* End curses mode		  */

  return 0;
}
