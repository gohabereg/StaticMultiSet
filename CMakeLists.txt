cmake_minimum_required(VERSION 3.8)
project(Lab2)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v")

set(SOURCE_FILES main.cpp StatisticMultiset.h)
add_executable(Lab2 ${SOURCE_FILES})