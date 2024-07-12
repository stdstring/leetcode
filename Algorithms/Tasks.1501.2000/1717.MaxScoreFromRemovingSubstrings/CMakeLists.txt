cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(1717.MaxScoreFromRemovingSubstrings CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES solution.cpp)

set(HEADERS)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE gtest gtest_main)

add_test(NAME 1717.MaxScoreFromRemovingSubstrings COMMAND ${PROJECT_NAME})
