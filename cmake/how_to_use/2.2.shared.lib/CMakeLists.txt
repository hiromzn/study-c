# checking version of cmake
cmake_minimum_required(VERSION 3.13)

# setting project name and language
project(test_cmake CXX)

# creating libgreegings.a from hello.cpp and good_morning.cpp
add_library(greetings SHARED hello.cpp good_morning.cpp)

# creating a.out from main.cpp
add_executable(a.out main.cpp)

# link a libgreegings.a when a.out is created.
target_link_libraries(a.out greetings)

