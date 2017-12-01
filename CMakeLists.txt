cmake_minimum_required(VERSION 3.1.3)

project(sneick666)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
find_package(SFML REQUIRED COMPONENTS System Window Graphics)

set(CMAKE_CXX_STANDARD 11)

add_executable(
  snake
  src/FoodGenerator.cpp  
  src/FoodGenerator.h
  src/Game.cpp
  src/Game.h
  src/PlaygroundGraphicView.cpp
  src/PlaygroundGraphicView.h
  src/Playground.cpp
  src/Playground.h
  src/PlaygroundView.cpp  
  src/PlaygroundView.h
  src/main.cpp
  src/Point.cpp
  src/Point.h
  src/Snake.cpp
  src/Snake.h
  src/Window.cpp
  src/Window.h
  )

target_include_directories(snake SYSTEM PRIVATE ${CURSES_INCLUDE_DIRS} ${SFML_INCLUDE_DIR})

target_link_libraries(snake ${CURSES_LIBRARIES} ${SFML_LIBRARIES})

