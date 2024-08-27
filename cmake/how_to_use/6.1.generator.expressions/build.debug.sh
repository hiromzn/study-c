set -x

rm -rf build
mkdir -p build

cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
