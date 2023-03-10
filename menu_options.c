#include <menu.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 4

char *choices[] = {
    "Choice 1", "Choice 2", "Choice 3", "Choice 4",
    "Choice 5", "Choice 6", "Choice 7", "Exit",
};

void menu_func(ITEM *menu_item);

int main() {
  ITEM **my_items;
  int c;
  MENU *my_menu;
  int n_choices, i;
  ITEM *cur_item;

  /* Initialize curses */
  initscr();
  curs_set(0);
  start_color();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_MAGENTA, COLOR_BLACK);

  /* Initialize items */
  n_choices = ARRAY_SIZE(choices);
  my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
  for (i = 0; i < n_choices; ++i) {
    my_items[i] = new_item(choices[i], choices[i]);
    /* Set the user pointer */
    set_item_userptr(my_items[i], menu_func);
  }
  my_items[n_choices] = (ITEM *)NULL;
  item_opts_off(my_items[3], O_SELECTABLE);
  item_opts_off(my_items[6], O_SELECTABLE);

  /* Create menu */
  my_menu = new_menu((ITEM **)my_items);

  /* Set fore ground and back ground of the menu */
  set_menu_fore(my_menu, COLOR_PAIR(1) | A_REVERSE);
  set_menu_back(my_menu, COLOR_PAIR(2));
  set_menu_grey(my_menu, COLOR_PAIR(3));

  /* Post the menu */
  mvprintw(LINES - 3, 0, "Press <ENTER> to see the option selected");
  mvprintw(LINES - 2, 0, "Up and Down arrow keys to naviage ('q' to Exit)");
  post_menu(my_menu);
  refresh();

  while ((c = getch()) != 'q') {
    switch (c) {
    case KEY_DOWN:
      menu_driver(my_menu, REQ_DOWN_ITEM);
      break;
    case KEY_UP:
      menu_driver(my_menu, REQ_UP_ITEM);
      break;
    case 10: /* Enter */
      menu_func(current_item(my_menu));
      pos_menu_cursor(my_menu);
      break;
    }
  }

  unpost_menu(my_menu);
  for (i = 0; i < n_choices; ++i)
    free_item(my_items[i]);
  free_menu(my_menu);

  endwin();
}

void menu_func(ITEM *menu_item) {
  move(LINES - 5, 10);
  printw("Item selected is : %s", item_name(menu_item));
  clrtoeol();
}