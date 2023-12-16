cmake_minimum_required(VERSION 3.1.0)
project(test VERSION 1.0)

aux_source_directory(. DIR_CONTAINER_SRCS)
add_executable(test ${DIR_CONTAINER_SRCS})
add_library(container STATIC ${DIR_CONTAINER_SRCS})
