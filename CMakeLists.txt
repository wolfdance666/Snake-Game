cmake_minimum_required(VERSION 3.1.3)

project(sneick666)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)

set(CMAKE_CXX_STANDARD 11)

add_executable(
  snake
  src/main.cpp
  src/Point.cpp
  src/Point.h
  src/Snake.cpp
  src/Snake.h
  src/Window.cpp
  src/Window.h
  )

target_include_directories(snake SYSTEM PRIVATE ${CURSES_INCLUDE_DIRS})

target_link_libraries(snake ${CURSES_LIBRARIES})

