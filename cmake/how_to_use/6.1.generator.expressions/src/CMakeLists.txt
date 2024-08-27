add_library( greetings
  SHARED
    hello.cpp
    good_morning.cpp
)

# specifying an include directory of a greeting library.
# PROJECT_SOURCE_DIR is an absolute root directory of this project.
target_include_directories( greetings
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)
