cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(1008.ConstructBSTFromPreorderTraversal CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("../../CommonLib")

set(SOURCES solution.cpp)

set(HEADERS)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE gtest gtest_main CommonLib)

add_test(NAME 1008.ConstructBSTFromPreorderTraversal COMMAND ${PROJECT_NAME})
