cmake_minimum_required(VERSION 3.17)

project(oop_exercise_04)

set(SOURCE lab4.cpp)
set(EXEC lab4)

add_definitions(-std=c++17 -pedantic -Wall -Werror)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(${EXEC} ${SOURCE})
