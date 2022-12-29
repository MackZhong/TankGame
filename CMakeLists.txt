cmake_minimum_required(VERSION 3.0.0)
project(TankGame VERSION 0.1.0)

include(CTest)
enable_testing()
include(FindCurses)

add_executable(TankGame main.c)
target_link_libraries(TankGame ncurses)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
