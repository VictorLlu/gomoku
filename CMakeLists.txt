cmake_minimum_required(VERSION 3.8)
project(wuziqi)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp wuziqi_ai.cpp wuziqi_ai.h basic.cpp basic.h)
add_executable(wuziqi ${SOURCE_FILES})