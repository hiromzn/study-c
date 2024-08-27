set -x

rm -rf build
mkdir -p build

cmake -S . -B build -DBUILD_SHARED_LIBS=ON
cmake --build build
