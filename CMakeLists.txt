cmake_minimum_required(VERSION 3.17)
project(AOC2022)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(${PROJECT_NAME}_dt01 src/daily_task_01.cpp)