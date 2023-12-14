# envoirenment variables
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")

project(RLE)
add_executable(
    RLE
    main.cpp
    RLE.hpp
)

list(APPEND COV_GCNO_GCDA ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/RLE.dir/main.cpp.gcno)
list(APPEND COV_GCNO_GCDA ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/RLE.dir/main.cpp.gcda)
add_custom_target(coverage
    COMMAND mkdir -p coverage
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
add_custom_command(TARGET coverage
    COMMAND RLE
    COMMAND lcov --directory ./src --capture --output-file ./coverage.info
    COMMAND lcov --remove ./coverage.info -o filtered.info 'bits/*' 'googlemock/*' '/usr/*' 'src/main.cpp'
    COMMAND genhtml -o coverage filtered.info
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
add_dependencies(coverage RLE)
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
    coverage
    coverage.info
    ${COV_GCNO_GCDA}
)
