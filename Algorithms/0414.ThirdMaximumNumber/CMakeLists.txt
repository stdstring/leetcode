cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(0414.ThirdMaximumNumber CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES solution.cpp)

set(HEADERS)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE gtest gtest_main)

add_test(NAME 0414.ThirdMaximumNumber COMMAND ${PROJECT_NAME})
