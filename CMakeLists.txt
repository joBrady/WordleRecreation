cmake_minimum_required(VERSION 3.23)
project(hw3)

set(CMAKE_CXX_STANDARD 14)

add_executable(hw3 Wordle.cpp Wordle.h main.cpp)
configure_file( wordList.txt wordList.txt COPYONLY)
