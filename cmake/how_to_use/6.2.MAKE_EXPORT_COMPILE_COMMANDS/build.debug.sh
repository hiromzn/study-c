set -x

rm -rf build
mkdir -p build

#
# if CMAKE_EXPORT_COMPILE_COMMANDS is true, compile_commands.json is created in build/
#
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=true

cmake --build build
