cmake_minimum_required(VERSION 3.12)
project(Drawer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt@5")



set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(
    SRC_LIST
    src/main.cpp
    src/MainWindow.cpp
)

include_directories("src/")

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable( ${PROJECT_NAME} ${SRC_LIST} )

target_link_libraries(${PROJECT_NAME}
  PUBLIC
   Qt5::Widgets
   Qt5::Core
)

set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC TRUE)

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)