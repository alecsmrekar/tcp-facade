cmake_minimum_required(VERSION 3.17)
project(Web C)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_CXX_FLAGS "-lncurses")
#find_package(Curses REQUIRED)
#include_directories(${CURSES_INCLUDE_DIR})
add_executable(Web main.c)
#target_link_libraries(Web ${CURSES_LIBRARY})