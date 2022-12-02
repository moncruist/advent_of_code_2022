cmake_minimum_required(VERSION 3.20)
project(advent_of_code_2022)

set(CMAKE_CXX_STANDARD 20)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

if(EXISTS "${CMAKE_BINARY_DIR}/conan_paths.cmake")
    include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
endif()

# enable_testing()

# find_package(GTest REQUIRED)
find_package(Boost COMPONENTS program_options REQUIRED)

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(utils)
add_subdirectory(day1)
add_subdirectory(day2)
