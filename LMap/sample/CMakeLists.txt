cmake_minimum_required(VERSION 3.0.0)
project(lmapDemo VERSION 1.0)

include_directories(../include ../external)
add_executable(lmapDemo lmapDemo.cpp ../src/lchar.cpp ../src/lstring.cpp ../src/llist.cpp)
