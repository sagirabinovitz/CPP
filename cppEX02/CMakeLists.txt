cmake_minimum_required(VERSION 3.24)
project(cppEX02)

set(CMAKE_CXX_STANDARD 11)

add_executable(cppEX02 main.cpp DirectedGraph.cpp DirectedGraph.h Omsterdam.cpp Omsterdam.h Edge.h FileNotFound.h)
