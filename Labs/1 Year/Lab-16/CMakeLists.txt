cmake_minimum_required(VERSION 3.1)

project(server)

include_directories("src/" "include/" "pages/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Wall -Werror -pedantic")

set(
	SRC_LIST
    src/main.cpp
    src/server.cpp
    src/ssocket.cpp
    src/http_handler.cpp
)

add_executable(${PROJECT_NAME} ${SRC_LIST})
