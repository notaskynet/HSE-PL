cmake_minimum_required(VERSION 3.14)
project(HW-06)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  hello_test
  basic_test.cc
)

target_link_libraries(
  hello_test
  GTest::gtest_main  
)

include(GoogleTest)
gtest_discover_tests(hello_test)


add_custom_target(check)
add_custom_command(TARGET check
    COMMAND hello_test
)
add_dependencies(check
hello_test
)
