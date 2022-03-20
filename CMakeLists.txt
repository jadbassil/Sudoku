cmake_minimum_required(VERSION 3.16)

project(Sudoku)
set(CMAKE_CXX_STANDARD 20)

add_library(SudukoGen src/sudoku.hpp src/sudoku.cpp)

add_executable(Sudoku src/main.cpp )

target_link_libraries(Sudoku PRIVATE SudukoGen)
