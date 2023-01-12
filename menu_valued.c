#include <menu.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 4

char *choices[] = {
    "Choice 1", "Choice 2", "Choice 3", "Choice 4",
    "Choice 5", "Choice 6", "Choice 7", "Exit",
};

int main() {
  ITEM **my_items;
  int c;
  MENU *my_menu;
  int n_choices, i;
  ITEM *cur_item;

  /* Initialize curses */
  initscr();
  curs_set(0);
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  /* Initialize items */
  n_choices = ARRAY_SIZE(choices);
  my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
  for (i = 0; i < n_choices; ++i)
    my_items[i] = new_item(choices[i], choices[i]);
  my_items[n_choices] = (ITEM *)NULL;

  my_menu = new_menu((ITEM **)my_items);

  /* Make the menu multi valued */
  menu_opts_off(my_menu, O_ONEVALUE);

  mvprintw(LINES - 1, 0,
           "Use <SPACE> to select or unselect an item. 'q' to Exit)");
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
    case ' ':
      menu_driver(my_menu, REQ_TOGGLE_ITEM);
      {
        char temp[200];
        ITEM **items;

        items = menu_items(my_menu);
        temp[0] = '\0';
        for (i = 0; i < item_count(my_menu); ++i)
          if (item_value(items[i]) == TRUE) {
            strcat(temp, item_name(items[i]));
            strcat(temp, " ");
          }
        move(20, 0);
        clrtoeol();
        mvaddstr(20, 0, temp);
        refresh();
      }
      break;
    }
  }

  free_item(my_items[0]);
  free_item(my_items[1]);
  free_menu(my_menu);
  endwin();
}