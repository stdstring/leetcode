cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(1957.DeleteCharsToMakeFancyString CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES solution.cpp)

set(HEADERS)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE gtest gtest_main)

add_test(NAME 1957.DeleteCharsToMakeFancyString COMMAND ${PROJECT_NAME})
