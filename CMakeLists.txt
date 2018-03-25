cmake_minimum_required(VERSION 3.9)
project(cpp_utility)

set(CMAKE_CXX_STANDARD 11)

add_executable(cpp_utility main.cpp WrapStdQueue.cpp WrapStdQueue.h UnitTestDriver.cpp UnitTestDriver.h CircularCharQueue.cpp CircularCharQueue.h BitManipulation.cpp BitManipulation.h ThreadExample.cpp ThreadExample.h)