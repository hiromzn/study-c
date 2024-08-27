
add_executable(a.out main.cpp)

# creating a.out with greetings library.
target_link_libraries(a.out greetings)

# optimize and warning options.
target_compile_options(a.out PUBLIC
  # ビルドタイプによって変更する
  $<$<CONFIG:Release>: -O2 -g>       # Release
  $<$<CONFIG:Debug>: -g -Wall>       # Debug
)
# ----------
# sample:
# ----------
#
#  $<$<CONFIG:RelWithDebgInfo>: ...>  # RelWithDebInfo
#
#   # OSに応じて変更する
#   $<$<PLATFORM_ID:Darwin>: ...>   # Mac
#   $<$<PLATFORM_ID:Linux>: ...>    # Linux
#   $<$<PLATFORM_ID:Windows>: ...>  # Windows
#
#   # コンパイラによって変更する
#   $<$<CXX_COMPILER_ID:MSVC>: ...>      # MSVC
#   $<$<CXX_COMPILER_ID:GNU>: ...>       # GCC
#   $<$<CXX_COMPILER_ID:Clang>: ...>     # LLVM Clang
#   $<$<CXX_COMPILER_ID:Intel>: ...>     # Intel classic
#   $<$<CXX_COMPILER_ID:IntelLLVM>: ...> # Intel one-API
#   )
# target_compile_definitions(a.out PUBLIC
#   $<$<NOT:$<CONFIG:Debug>>: ...>     # Debugビルド以外
#   )


# C++ standalization options.
#
# option list:
#     https://cmake.org/cmake/help/git-master/prop_gbl/CMAKE_CXX_KNOWN_FEATURES.html#prop_gbl:CMAKE_CXX_KNOWN_FEATURES
#
target_compile_features(a.out PUBLIC cxx_std_11)

# macro
target_compile_definitions(a.out PUBLIC MY_ORIGINAL_MACRO_CONST=1)
