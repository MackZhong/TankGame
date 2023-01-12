cmake_minimum_required(VERSION 3.0.0)
project(TankGame VERSION 0.1.0)

include(CTest)
enable_testing()
include(FindCurses)

add_executable(TankGame main.c)
target_link_libraries(TankGame ncurses)

project(CursesAttr VERSION 0.1.0)
add_executable(CursesAttr curses_attr.c)
target_link_libraries(CursesAttr ncurses)

project(CursesChgat VERSION 0.1.0)
add_executable(CursesChgat curses_chgat.c)
target_link_libraries(CursesChgat ncurses)

project(CursesWin VERSION 0.1.0)
add_executable(CursesWin curses_win.c)
target_link_libraries(CursesWin ncurses)

project(CursesColor VERSION 0.1.0)
add_executable(CursesColor curses_color.c)
target_link_libraries(CursesColor ncurses)

project(CursesInterface VERSION 0.1.0)
add_executable(CursesInterface curses_interface.c)
target_link_libraries(CursesInterface ncurses)

project(CursesMouse VERSION 0.1.0)
add_executable(CursesMouse curses_mouse.c)
target_link_libraries(CursesMouse ncurses)

project(CursesScreen VERSION 0.1.0)
add_executable(CursesScreen curses_screen.c)
target_link_libraries(CursesScreen ncurses)

project(CursesMode VERSION 0.1.0)
add_executable(CursesMode curses_mode.c)
target_link_libraries(CursesMode ncurses)

project(CursesACS VERSION 0.1.0)
add_executable(CursesACS curses_acs.c)
target_link_libraries(CursesACS ncurses)

# set(LINK_DIR /usr/local/lib)
# message("Link directory: ${LINK_DIR}")
# link_directories(${LINK_DIR})
project(Panel1 VERSION 0.1.0)
add_executable(Panel1 panel_1.c)
target_link_libraries(Panel1 panel ncurses)

project(Panel2 VERSION 0.1.0)
add_executable(Panel2 panel_2.c)
target_link_libraries(Panel2 panel ncurses)

project(Panel3 VERSION 0.1.0)
add_executable(Panel3 panel_3.c)
target_link_libraries(Panel3 panel ncurses)

project(Panel4 VERSION 0.1.0)
add_executable(Panel4 panel_4.c)
target_link_libraries(Panel4 panel ncurses)

project(Menu1 VERSION 0.1.0)
add_executable(Menu1 menu_1.c)
target_link_libraries(Menu1 menu ncurses)

project(MenuWindow VERSION 0.1.0)
add_executable(MenuWindow menu_window.c)
target_link_libraries(MenuWindow menu ncurses)

project(MenuScroll VERSION 0.1.0)
add_executable(MenuScroll menu_scroll.c)
target_link_libraries(MenuScroll menu ncurses)

project(MenuColumnar VERSION 0.1.0)
add_executable(MenuColumnar menu_columnar.c)
target_link_libraries(MenuColumnar menu ncurses)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
