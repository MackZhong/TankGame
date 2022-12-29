#include <curses.h>

WINDOW *create_newwin(int height, int width, int yStart, int xStart);
void destroy_win(WINDOW *local_win);

int main() {
  WINDOW *my_win = NULL;
  int startX = 0;
  int startY = 0;
  int width = 10;
  int height = 3;
  int chr = 0;

  initscr();            /* Start curses mode 		*/
  cbreak();             /* Line buffering disabled, Pass on
                         * every thing to me 		*/
  keypad(stdscr, TRUE); /* I need that nifty F1 	*/

  startY = (LINES - height) / 2; /* Calculating for a center placement */
  startX = (COLS - width) / 2;   /* of the window		*/
  printw("Press F1 to exit");
  refresh();
  my_win = create_newwin(height, width, startY, startX);

  while ((chr = getch()) != KEY_F(1)) {
    mvprintw(0, 50, "Y=%02d, X=%02d", startY, startX);
    switch (chr) {
    case KEY_LEFT:
      if (startX <= 1) {
        mvaddstr(LINES - 1, 0, "Left");
        break;
      }
      destroy_win(my_win);
      my_win = create_newwin(height, width, startY, --startX);
      break;
    case KEY_RIGHT:
      if (startX >= COLS - width) {
        mvaddstr(LINES - 1, 0, "Right");
        break;
      }
      destroy_win(my_win);
      my_win = create_newwin(height, width, startY, ++startX);
      break;
    case KEY_UP:
      if (startY <= 1) {
        mvaddstr(LINES - 1, 0, "Top");
        break;
      }
      destroy_win(my_win);
      my_win = create_newwin(height, width, --startY, startX);
      break;
    case KEY_DOWN:
      if (startY >= LINES - height - 1) {
        mvaddstr(LINES - 1, 0, "Bottom");
        break;
      }
      destroy_win(my_win);
      my_win = create_newwin(height, width, ++startY, startX);
      break;
    default:
      break;
    }
  }

  endwin(); /* End curses mode		  */
  return 0;
}

WINDOW *create_newwin(int height, int width, int yStart, int xStart) {
  WINDOW *local_win = NULL;

  local_win = newwin(height, width, yStart, xStart);
  box(local_win, 0, 0); /* 0, 0 gives default characters
                         * for the vertical and horizontal
                         * lines			*/

  /*
   * mvhline(), mvvline() and mvaddch() to draw a box.
   */

  wrefresh(local_win); /* Show that box 		*/

  return local_win;
}

void destroy_win(WINDOW *local_win) {
  /* box(local_win, ' ', ' '); : This won't produce the desired
   * result of erasing the window. It will leave it's four corners
   * and so an ugly remnant of window.
   */
  wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  /* The parameters taken are
   * 1. win: the window on which to operate
   * 2. ls: character to be used for the left side of the window
   * 3. rs: character to be used for the right side of the window
   * 4. ts: character to be used for the top side of the window
   * 5. bs: character to be used for the bottom side of the window
   * 6. tl: character to be used for the top left corner of the window
   * 7. tr: character to be used for the top right corner of the window
   * 8. bl: character to be used for the bottom left corner of the window
   * 9. br: character to be used for the bottom right corner of the window
   */
  /* wborder(local_win, 'l', 'r', 't', 'b', '1', '2', '3', '4');
   * 1tt2
   * l  r
   * l  r
   * 3bb4
   */
  wrefresh(local_win);
  delwin(local_win);
}