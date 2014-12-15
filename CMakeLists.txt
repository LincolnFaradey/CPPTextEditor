cmake_minimum_required(VERSION 2.8.4)
project(Text_Editor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp text_editor.cpp)
add_executable(Text_Editor ${SOURCE_FILES})