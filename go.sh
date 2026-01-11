#!/bin/bash

set -euo pipefail

cmake -B build -G Ninja -DCMAKE_INSTALL_PREFIX=install -DCMAKE_BUILD_TYPE=Debug
cmake --build build
cmake --install build

cp c/install/linux/Debug/lib/liblua.so install/lib
cp c/install/linux/Debug/lib/libraylib.so install/lib/libraylib.so
cp c/install/linux/Debug/lib/libraylib.so.5.5.0 install/lib/libraylib.so.5.5.0
cp c/install/linux/Debug/lib/libraylib.so.550 install/lib/libraylib.so.550

cd executable
./go.sh