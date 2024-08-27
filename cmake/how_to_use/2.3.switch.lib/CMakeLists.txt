# checking version of cmake
cmake_minimum_required(VERSION 3.13)

# setting project name and language
project(test_cmake CXX)

# creating greegings lib from hello.cpp and good_morning.cpp.
# The type of library is specified by BUILD_SHARED_LIBS option.
add_library(greetings hello.cpp good_morning.cpp)

# creating a.out from main.cpp
add_executable(a.out main.cpp)

# link a libgreegings.a when a.out is created.
target_link_libraries(a.out greetings)

