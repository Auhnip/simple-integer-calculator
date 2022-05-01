cmake_minimum_required(VERSION 3.0)

project(Calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Scanner STATIC token.h token.cpp scanner.h scanner.cpp)

list(APPEND _sources calculator.cpp main.cpp)

add_executable(${PROJECT_NAME} ${_sources})

target_link_libraries(${PROJECT_NAME} Scanner)