set -x

rm -rf build
mkdir -p build

cmake -S . -B build -DGREETINGS_BUILD_SHARED_LIBS=ON
cmake --build build
