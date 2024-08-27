toolset="scl enable llvm-toolset-7.0";

set -x

mkdir -p build
$toolsety cmake -S . -B build
$toolsety cmake --build build
