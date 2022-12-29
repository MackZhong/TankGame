#include <curses.h>
#include <string.h>

void print_in_middle(WINDOW *win, int startY, int startX, int width,
                     char *string);

int main() {
  initscr(); /* Start curses mode 		*/

  if (has_colors() == FALSE) {
    endwin();
    printf("Your terminal does not support color\n");
    return 1;
  }

  start_color(); /* Start color 			*/

  if (can_change_color() == FALSE) {
    printw("Your terminal can not change color\n");
  } else {
    init_color(COLOR_RED, 200, 0, 0);
    /* param 1     : color name
     * param 2, 3, 4 : rgb content min = 0, max = 1000 */
  }
  init_pair(1, COLOR_RED, COLOR_BLACK);

  attron(COLOR_PAIR(1));
  print_in_middle(stdscr, LINES / 2, 0, 0, "Viola !!! In color ...");
  attroff(COLOR_PAIR(1));

  /* The functions color_content() and pair_content() can be used to find the
   * color content and foreground, background combination for the pair.
   */
  short red = 0;
  short green = 0;
  short blue = 0;
  color_content(COLOR_RED, &red, &green, &blue);
  short foreground = 0;
  short background = 0;
  pair_content(1, &foreground, &background);

  getch();
  endwin();
}

void print_in_middle(WINDOW *win, int startY, int startX, int width,
                     char *string) {
  size_t length = 0;
  int xPos = 0;
  int yPos = 0;
  float temp = 0.0F;

  if (win == NULL) {
    win = stdscr;
  }
  getyx(win, yPos, xPos);
  if (startX != 0) {
    xPos = startX;
  }
  if (startY != 0) {
    yPos = startY;
  }
  if (width == 0) {
    width = 80;
  }

  length = strlen(string);
  temp = (float)(width - (int)length) / 2.0F;
  xPos = startX + (int)temp;
  mvwprintw(win, yPos, xPos, "%s", string);
  refresh();
}