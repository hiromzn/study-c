# checking version of cmake
# cmake_minimum_required(VERSION 3.13)

# setting project name and language
project(test_cmake CXX)

# creating a.out from main.cpp and hello.cpp
add_executable(a.out main.cpp hello.cpp)
