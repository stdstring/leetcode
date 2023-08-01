cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(1031.MaxSumTwoNonOverlappingSubarrays CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES solution.cpp)

set(HEADERS)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE gtest gtest_main)

add_test(NAME 1031.MaxSumTwoNonOverlappingSubarrays COMMAND ${PROJECT_NAME})
