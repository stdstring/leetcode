cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(CommonLib CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES ListNode.cpp ListNodeUtils.cpp TreeNode.cpp TreeNodeUtils.cpp)

set(HEADERS ListNode.h ListNodeUtils.h TreeNode.h TreeNodeUtils.h)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE gtest gtest_main)
