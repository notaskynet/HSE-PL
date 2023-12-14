cmake_minimum_required(VERSION 3.12)

project(keygen VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt@5")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

include_directories(include src)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(keygen
    src/keygen.cpp
    src/main.cpp
)

target_link_libraries(keygen Qt5::Widgets)

set_target_properties(keygen PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)