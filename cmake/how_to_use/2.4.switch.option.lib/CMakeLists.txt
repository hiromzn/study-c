# checking version of cmake
cmake_minimum_required(VERSION 3.13)

# setting project name and language
project(test_cmake CXX)

# creating GREETINGS_BUILD_SHARED_LIBS option (default: OFF)
option(GREETINGS_BUILD_SHARED_LIBS "build greetings as a shared library" OFF)

if (GREETINGS_BUILD_SHARED_LIBS)
  add_library(greetings SHARED hello.cpp good_morning.cpp)
else()
  add_library(greetings STATIC hello.cpp good_morning.cpp)
endif()

# creating a.out from main.cpp
add_executable(a.out main.cpp)

# link a libgreegings.a when a.out is created.
target_link_libraries(a.out greetings)

