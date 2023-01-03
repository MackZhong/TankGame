#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

#define WIDTH 30
#define HEIGHT 10

int startX = 0;
int startY = 0;

char *choices[] = {
    "Choice 1", "Choice 2", "Choice 3", "Choice 4", "Exit",
};
int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight);

int main() {
  WINDOW *menu_win = NULL;
  int highlight = 1;
  int choice = 0;
  int chr = 0;

  initscr();
  clear();
  noecho();
  cbreak(); /* Line buffering disabled. pass on everything */
  startX = (COLS - WIDTH) / 2;
  startY = (LINES - HEIGHT) / 2;

  menu_win = newwin(HEIGHT, WIDTH, startY, startX);
  keypad(menu_win, TRUE);
  mvprintw(0, 0,
           "Use arrow keys to go up and down, Press enter to select a choice");
  refresh();

  while (1) {
    print_menu(menu_win, highlight);
    chr = wgetch(menu_win);
    switch (chr) {
    case KEY_UP:
      if (highlight == 1) {
        highlight = n_choices;
      } else {
        --highlight;
      }
      break;
    case KEY_DOWN:
      if (highlight == n_choices) {
        highlight = 1;
      } else {
        ++highlight;
      }
      break;
    case 10: // KEY_ENTER
      choice = highlight;
      break;
    default:
      mvprintw(LINES - 1, 0,
               "Charcter pressed is = %3d Hopefully it can be printed as '%c'",
               chr, chr);
      refresh();
      break;
    }

    if (choice == n_choices) {
      break; /* User did a choice come out of the infinite loop */
    }

    mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice,
             choices[choice - 1]);
    clrtoeol();
    refresh();
  }

  endwin();
  return 0;
}

void print_menu(WINDOW *menu_win, int highlight) {
  int xPos = 2;
  int yPos = 2;
  int index = 0;

  box(menu_win, 0, 0);
  for (index = 0; index < n_choices; ++index) {
    if (highlight == index + 1) /* High light the present choice */
    {
      wattron(menu_win, A_REVERSE);
      mvwprintw(menu_win, yPos, xPos, "%s", choices[index]);
      wattroff(menu_win, A_REVERSE);
    } else {
      mvwprintw(menu_win, yPos, xPos, "%s", choices[index]);
    }
    ++yPos;
  }
  wrefresh(menu_win);
}
