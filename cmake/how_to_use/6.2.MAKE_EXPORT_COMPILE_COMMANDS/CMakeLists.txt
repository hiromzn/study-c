# checking version of cmake
cmake_minimum_required(VERSION 3.13)

# setting project name and language
project(test_cmake CXX)

# add subdirectories
add_subdirectory(src)
add_subdirectory(test)

target_compile_options( greetings PUBLIC
  $<$<CONFIG:Release>: -O2 -g>       # Release
  $<$<CONFIG:Debug>: -g -Wall>       # Debug
)
