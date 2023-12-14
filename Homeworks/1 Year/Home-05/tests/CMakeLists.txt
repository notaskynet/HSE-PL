cmake_minimum_required(VERSION 3.14)
project(HW-05)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(
  hello_test
    main.cpp
)
target_link_libraries(
  hello_test
  GTest::gtest_main
)

add_test(HW-05 hello_test)
include(GoogleTest)
gtest_discover_tests(hello_test)

add_custom_target(check)
add_custom_command(TARGET check
    COMMAND hello_test
)