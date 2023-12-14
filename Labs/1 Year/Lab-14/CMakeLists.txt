cmake_minimum_required(VERSION 3.0)

project(checksum)

include_directories("src/" "include/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Werror -pedantic")

set(SRC_LIST src/main.cpp src/functools.cpp src/checksum.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})
