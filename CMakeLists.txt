cmake_minimum_required(VERSION 3.1.3)

project(sneick666)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

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
  src/main.cpp
  src/Point.cpp
  src/Point.h
  src/Snake.cpp
  src/Snake.h
  )

target_include_directories(snake SYSTEM PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(snake ${SFML_LIBRARIES})

add_custom_command(TARGET snake POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data
)

