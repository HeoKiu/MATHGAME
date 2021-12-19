cmake_minimum_required(VERSION 3.2.10)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        tests
        basic.cpp
        test.cpp
        ../include/MathEquation.h
        ../include/EvaluateString.h
)
add_test(NAME check COMMAND tests)

target_include_directories (
        tests
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}../include
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

# Link against Google Test library
target_link_libraries(tests gtest_main)
target_link_libraries(tests  ${SDL2_LIBRARIES})
