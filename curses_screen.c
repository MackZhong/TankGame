#include <ncurses.h>

#define WIDTH 30
#define HEIGHT 10

int startX = 0;
int startY = 0;

char *const choices[] = {
    "Choice 1", "Choice 2", "Choice 3", "Choice 4", "Exit",
};

const int n_choices = sizeof(choices) / sizeof(char *);

void print_menu(WINDOW *menu_win, int highlight);

int main() {

  int chr = 0;
  int choice = 1;
  WINDOW *menu_win = NULL;
  MEVENT event;

  /* Initialize curses */
  initscr();
  clear();
  noecho();
  cbreak(); // Line buffering disabled. pass on everything

  curs_set(0);
  /*
   * This function can be used to make the cursor invisible. The parameter to
   * this function should be:
   * 0 : invisible
   * 1 : normal
   * 2 : very visible / blink
   */

  /* Try to put the window in the middle of screen */
  startX = (COLS - WIDTH) / 2;
  startY = (LINES - HEIGHT) / 2;

  menu_win = newwin(HEIGHT, WIDTH, startY, startX);
  /* Get all the mouse events */

  int xPos = 0;
  int yPos = 0;
  getyx(stdscr, yPos, xPos);
  /*
   * Macro used to find out the present cursor co-ordinates.
   * Don't have to pass the address of the variables.
   */
  mvprintw(0, 0, "Last Cursor position: y = %d, x = %d", yPos, xPos);
  getparyx(menu_win, yPos, xPos);
  mvprintw(1, 0, "Window part position: y = %d, x = %d", yPos, xPos);
  getbegyx(menu_win, yPos, xPos);
  mvprintw(2, 0, "Window begin position: y = %d, x = %d", yPos, xPos);
  getmaxyx(menu_win, yPos, xPos);
  mvprintw(3, 0, "Window max position: y = %d, x = %d", yPos, xPos);
  getyx(stdscr, yPos, xPos);
  mvprintw(4, 0, "Last Cursor position: y = %d, x = %d", yPos, xPos);

  while (1) {
    /* Print the menu */
    print_menu(menu_win, choice);
    refresh();
    chr = wgetch(menu_win);
    mvprintw(LINES - 3, 1, "char %d('%c').", chr, chr);
    switch (chr) {
    case 27:
      mvaddstr(LINES - 4, 1, "Escape.");
      choice = -1;
      break;
    default:
      mvaddstr(LINES - 2, 1, "Please use mouse.");
      break;
    }
    if (choice == -1) { // Exit chosen
      break;
    }
  }

  scr_dump("screen.dump");
  /*
   * used to dump the screen contents to a file given as an argument.
   * Later it can be restored by scr_restore function.
   * To store and restore windows, the functions putwin() and getwin() can be
   * used. The function copywin() can be used to copy a window completely onto
   * another window.
   */
  FILE *windowDump = fopen("window.dump", "w");
  putwin(menu_win, windowDump);
  fclose(windowDump);

  endwin();
  return 0;
}

void print_menu(WINDOW *menu_win, int highlight) {
  int x, y, i;

  x = 2;
  y = 2;
  box(menu_win, 0, 0);
  for (i = 0; i < n_choices; ++i) {
    if (highlight == i + 1) {
      wattron(menu_win, A_REVERSE);
      mvwprintw(menu_win, y, x, "%s", choices[i]);
      wattroff(menu_win, A_REVERSE);
    } else
      mvwprintw(menu_win, y, x, "%s", choices[i]);
    ++y;
  }
}
