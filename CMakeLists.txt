cmake_minimum_required(VERSION 3.6)
project(algorithmsCpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#set(SOURCE_FILES main.cpp data_structures/binary_search_tree.h data_structures/red_black_bst.h)
aux_source_directory(. SOURCE_FILES)
add_executable(algorithmsCpp ${SOURCE_FILES})
