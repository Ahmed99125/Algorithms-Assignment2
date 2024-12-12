cmake_minimum_required(VERSION 3.27)
project(HashTable)

set(CMAKE_CXX_STANDARD 14)

include_directories(..)

add_executable(HashTable
        HashTable.h
        main.cpp)
