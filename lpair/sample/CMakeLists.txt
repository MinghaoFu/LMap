cmake_minimum_required(VERSION 3.0.0)
project(lpairDemo VERSION 1.0)

include_directories(../include ../external)
add_executable(lpairDemo lpairDemo.cpp ../src/lchar.cpp ../src/lstring.cpp ../src/llist.cpp)
