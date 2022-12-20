cmake_minimum_required(VERSION 3.17)
project(AOC2022)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(${PROJECT_NAME}_dt01 src/daily_task_01.cpp)
add_executable(${PROJECT_NAME}_dt02 src/daily_task_02.cpp)
add_executable(${PROJECT_NAME}_dt03 src/daily_task_03.cpp)
add_executable(${PROJECT_NAME}_dt04 src/daily_task_04.cpp)
add_executable(${PROJECT_NAME}_dt05 src/daily_task_05.cpp)
add_executable(${PROJECT_NAME}_dt06 src/daily_task_06.cpp)
add_executable(${PROJECT_NAME}_dt07 src/daily_task_07.cpp)
add_executable(${PROJECT_NAME}_dt08 src/daily_task_08.cpp)
add_executable(${PROJECT_NAME}_dt09 src/daily_task_09.cpp)
add_executable(${PROJECT_NAME}_dt10 src/daily_task_10.cpp)
add_executable(${PROJECT_NAME}_dt11 src/daily_task_11.cpp)
add_executable(${PROJECT_NAME}_dt12 src/daily_task_12.cpp)
add_executable(${PROJECT_NAME}_dt13 src/daily_task_13.cpp)
add_executable(${PROJECT_NAME}_dt14 src/daily_task_14.cpp)
add_executable(${PROJECT_NAME}_dt15 src/daily_task_15.cpp)

add_executable(${PROJECT_NAME}_dt17 src/daily_task_17.cpp)
add_executable(${PROJECT_NAME}_dt18 src/daily_task_18.cpp)

add_executable(${PROJECT_NAME}_dt20 src/daily_task_20.cpp)