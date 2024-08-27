
add_executable(a.out main.cpp)

# creating a.out with greetings library.
target_link_libraries(a.out greetings)

# optimize and warning options.
target_compile_options(a.out PUBLIC -O2 -Wall)

# C++ standalization options.
#
# option list:
#     https://cmake.org/cmake/help/git-master/prop_gbl/CMAKE_CXX_KNOWN_FEATURES.html#prop_gbl:CMAKE_CXX_KNOWN_FEATURES
#
target_compile_features(a.out PUBLIC cxx_std_11)

# macro
target_compile_definitions(a.out PUBLIC MY_ORIGINAL_MACRO_CONST=1)
