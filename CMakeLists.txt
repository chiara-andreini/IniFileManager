cmake_minimum_required(VERSION 3.5)
project(IniFileManager)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(test)

set(SOURCE_FILES
    IniFileManager.cpp
    IniFileManager.h)


add_executable(IniFileManager main.cpp)


add_library(core ${SOURCE_FILES})


target_link_libraries(IniFileManager core)