cmake_minimum_required(VERSION 3.12)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
  longNumberLib
  VERSION 1.0
  DESCRIPTION
    "Library for long numbers, that exceed limited 64-bit words. Supports numbers to 2048 bits"
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

add_subdirectory(./src)

# target_include_directories(longNumberLib PRIVATE .)
# set_target_properties(longNumberLib PROPERTIES VERSION ${PROJECT_VERSION})
