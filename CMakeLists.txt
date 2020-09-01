cmake_minimum_required(VERSION 3.17)
project(graphs C)

set(CMAKE_C_STANDARD 99)

add_executable(graphs main.c avl_tree.h avl_node.h)

include_directories(/usr/local/include)

