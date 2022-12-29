# TankGame
Console tank game uses ncurses on Linux, for C learning.

1. install ncurses library.
2. #include <ncurses.h>
3. link with ncurses library.
4. In CMakeLists.txt file, use `include(FindCurses)` to find curses library and `target_link_library(appname ncurses)` to link the library.
5. In VSCode, when Debug run use F5 at external terminal, it should add environment variable `$TERM` into 'launch.json' as below:
    "env": { "TERM": "xterm" }
  the terminal type is as your wish. If not do so, the external terminal is null, and ncurses initscr() call will fail.
6. When launch the program from run icon on the statusbar use clangd, it always run in integrated terminal.
7. In ncurses, 'w-less' functions call to curses window, like `printw()`, `mvprintw()` and `refresh()`, are effect the default terminal window called `'stdscr'`, thus such windows functions call to certain curses window, like `wprintw()`, `mvwprintw()` and `wrefresh()`, should referee to the first argument `win` created by `create_newwin()`.