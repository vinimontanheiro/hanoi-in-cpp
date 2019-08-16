cmake_minimum_required(VERSION 3.1)
project(hanoi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(hanoi ${SOURCE_FILES} Hanoi.h Jogo.h Jogada.h GenericKeyboard.h)