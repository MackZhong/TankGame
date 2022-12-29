#include <curses.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int chr = 0;
  int prev = EOF;
  int row = 0;
  int col = 0;
  FILE *fSource = NULL;
  int yPos = 0;
  int xPos = 0;

  if (argc != 2) {
    printf("Usage: %s <a c file name>\n", argv[0]);
    return 1;
  }

  fSource = fopen(argv[1], "re");
  if (fSource == NULL) {
    perror("Cannot open input file");
    return 2;
  }

  initscr();                  /* Start curses mode */
  getmaxyx(stdscr, row, col); /* find the boundaries of the screeen */

  while ((chr = fgetc(fSource)) !=
         EOF) /* read the file till we reach the end */
  {
    getyx(stdscr, yPos, xPos); /* get the current curser position */
    if (yPos == (row - 1))     /* are we are at the end of the screen */
    {
      printw("<-Press Any Key Page Down, q to Quit ->"); /* tell the user to
                                                            press a key */
      if ('q' == getch()) {
        break;
      }
      clear();    /* clear the screen */
      move(0, 0); /* start at the beginning of the screen */
    }
    if (prev == '/' && chr == '*') /* If it is / and * then only
                                    * switch bold on */
    {
      attron(A_BOLD);            /* cut bold on */
      getyx(stdscr, yPos, xPos); /* get the current curser position */
      move(yPos, xPos - 1);      /* back up one space */
      printw("%c%c", '/', chr);  /* The actual printing is done here */
    } else {
      printw("%c", chr);
    }
    refresh();
    if (prev == '*' && chr == '/') {
      attroff(A_BOLD);
    } /* Switch it off once we got *
       * and then / */
    /*
     * attron(), attroff(), attrset()
     * attr_get(), attr_set(), attr_on(), attr_off(): These are similar to above
     * functions except that they take parameters of type attr_t.
     */

    prev = chr;
  }

  endwin(); /* End curses mode */
  int ret = fclose(fSource);

  return 0;
}