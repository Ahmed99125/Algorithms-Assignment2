cmake_minimum_required(VERSION 3.25)
project(SkipList)

set(CMAKE_CXX_STANDARD 17)

add_executable(SkipList main.cpp SkipList.h SkipList.cpp SkipListDescendant.h SkipListDescendant.cpp Game.h Game.cpp)
