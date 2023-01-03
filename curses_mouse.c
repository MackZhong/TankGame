#include <locale.h>
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
void report_choice(int mouse_x, int mouse_y, int *p_choice);

int main() {
  char *oldLocale = setlocale(LC_ALL, "");

  int chr = 0;
  int choice = 1;
  WINDOW *menu_win = NULL;
  MEVENT event;

  /* Initialize curses */
  initscr();
  clear();
  noecho();
  cbreak(); // Line buffering disabled. pass on everything

  if (has_mouse()) {
    addstr("Has Mouse");
  } else {
    addstr("No Mouse");
  }
  /* Try to put the window in the middle of screen */
  startX = (COLS - WIDTH) / 2;
  startY = (LINES - HEIGHT) / 2;

  attron(A_REVERSE);
  mvprintw(LINES - 1, 1,
           "Click on Exit to quit (Works best in a virtual console)");
  //   refresh();
  attroff(A_REVERSE);

  menu_win = newwin(HEIGHT, WIDTH, startY, startX);
  /* Get all the mouse events */
  mousemask(BUTTON1_CLICKED, NULL);
  /*
  * Name                        Description
    ---------------------------------------------------------------------
    BUTTON1_PRESSED          mouse button 1 down
    BUTTON1_RELEASED         mouse button 1 up
    BUTTON1_CLICKED          mouse button 1 clicked
    BUTTON1_DOUBLE_CLICKED   mouse button 1 double clicked
    BUTTON1_TRIPLE_CLICKED   mouse button 1 triple clicked
    BUTTON2_PRESSED          mouse button 2 down
    BUTTON2_RELEASED         mouse button 2 up
    BUTTON2_CLICKED          mouse button 2 clicked
    BUTTON2_DOUBLE_CLICKED   mouse button 2 double clicked
    BUTTON2_TRIPLE_CLICKED   mouse button 2 triple clicked
    BUTTON3_PRESSED          mouse button 3 down
    BUTTON3_RELEASED         mouse button 3 up
    BUTTON3_CLICKED          mouse button 3 clicked
    BUTTON3_DOUBLE_CLICKED   mouse button 3 double clicked
    BUTTON3_TRIPLE_CLICKED   mouse button 3 triple clicked
    BUTTON4_PRESSED          mouse button 4 down
    BUTTON4_RELEASED         mouse button 4 up
    BUTTON4_CLICKED          mouse button 4 clicked
    BUTTON4_DOUBLE_CLICKED   mouse button 4 double clicked
    BUTTON4_TRIPLE_CLICKED   mouse button 4 triple clicked
    BUTTON_SHIFT             shift was down during button state change
    BUTTON_CTRL              control was down during button state change
    BUTTON_ALT               alt was down during button state change
    ALL_MOUSE_EVENTS         report all button state changes
    REPORT_MOUSE_POSITION    report mouse movement
  */
  if (has_mouse()) {
    mvaddstr(1, 2, "Has Mouse");
  } else {
    mvaddstr(1, 2, "No Mouse");
  }

  while (1) {
    /* Print the menu */
    print_menu(menu_win, choice);
    // wrefresh(menu_win);
    refresh();
    // chr = getch(); /* I think here the focus is changed. */
    chr = wgetch(menu_win);
    mvprintw(LINES - 3, 1, "char %d('%c').", chr, chr);
    switch (chr) {
    case 27:
      mvaddstr(LINES - 4, 1, "Escape.");
      choice = -1;
      break;
    case KEY_MOUSE:
      mvaddstr(LINES - 4, 1, "Mouse clicked.");
      if (getmouse(&event) == OK) {
        /* When the user clicks left mouse button */
        if (event.bstate & BUTTON1_PRESSED) {
          report_choice(event.x + 1, event.y + 1, &choice);
          mvprintw(LINES - 1, 1,
                   "Choice made is : %d String Chosen is \"%10s\"", choice,
                   choices[choice - 1]);
        }
      }
      break;
    default:
      mvaddstr(LINES - 2, 1, "Please use mouse.");
      break;
    }
    if (choice == -1) { // Exit chosen
      break;
    }
    // refresh();
  }

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
  //   wrefresh(menu_win);
}

/* Report the choice according to mouse position */
void report_choice(int mouse_x, int mouse_y, int *p_choice) {
  int i, j, choice;

  i = startX + 2;
  j = startY + 3;

  for (choice = 0; choice < n_choices; ++choice)
    if (mouse_y == j + choice && mouse_x >= i &&
        mouse_x <= i + strlen(choices[choice])) {
      if (choice == n_choices - 1)
        *p_choice = -1;
      else
        *p_choice = choice + 1;
      break;
    }
}