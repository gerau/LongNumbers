cmake_minimum_required(VERSION 3.14)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
  longNumberLib
  VERSION 1.0
  DESCRIPTION
    "Library for long unsigned numbers, that exceed limited 64-bit words. Supports numbers to 2048 bits"
)

add_subdirectory(./src)

# enable_testing() add_subdirectory(./tests)
