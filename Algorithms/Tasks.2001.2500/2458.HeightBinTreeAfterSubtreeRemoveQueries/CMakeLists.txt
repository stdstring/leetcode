cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(2458.HeightBinTreeAfterSubtreeRemoveQueries CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("../../CommonLib")

set(SOURCES solution.cpp)

set(HEADERS)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE gtest gtest_main CommonLib)

add_test(NAME 2458.HeightBinTreeAfterSubtreeRemoveQueries COMMAND ${PROJECT_NAME})
