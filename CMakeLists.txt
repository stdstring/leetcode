cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(LeetcodeTasks CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("external/googletest/include")
link_directories(external/googletest/bin)

enable_testing()
# Algorithms
add_subdirectory(Algorithms/0001.TwoSum bin/0001.TwoSum)
