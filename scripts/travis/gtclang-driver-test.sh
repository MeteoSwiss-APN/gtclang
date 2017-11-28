#!/usr/bin/env bash
##===-------------------------------------------------------------------------------*- bash -*-===##
##                         _       _
##                        | |     | |
##                    __ _| |_ ___| | __ _ _ __   __ _ 
##                   / _` | __/ __| |/ _` | '_ \ / _` |
##                  | (_| | || (__| | (_| | | | | (_| |
##                   \__, |\__\___|_|\__,_|_| |_|\__, | - GridTools Clang DSL
##                    __/ |                       __/ |
##                   |___/                       |___/
##
##
##  This file is distributed under the MIT License (MIT). 
##  See LICENSE.txt for details
##
##===------------------------------------------------------------------------------------------===##

this_script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Setup dependencies
source "$this_script_dir/gtclang-install.sh"
gtclang_install_dependencies

if [ ! -z ${CLANG_VERSION+x} ]; then
  install_driver -i "${CACHE_DIR}" -b clang
fi

export CXX=${CXX_COMPILER}
export CC=${C_COMPILER}

$CC --version
$CXX --version

# Build gtclang
pushd "$(pwd)"

cd bundle
mkdir build 
cd build

export PYTHON_DIR=/opt/python/3.5.3

cmake .. -DCMAKE_CXX_COMPILER="$CXX"                                                               \
         -DCMAKE_C_COMPILER="$CC"                                                                  \
         -DCMAKE_BUILD_TYPE="$CONFIG"                                                              \
         -DGTCLANG_TESTING=ON                                                                      \
         -DGTCLANG_UNIT_TESTING=ON                                                                 \
         -DGTCLANG_INTEGRATION_TESTING=ON                                                          \
         -DPYTHON_EXECUTABLE="$PYTHON_DIR/bin/python3"                                             \
         -DProtobuf_DIR=${build_dir}/protobuf-prefix/src/protobuf-build/lib/cmake/protobuf/        \
         -DDawn_DIR=${build_dir}/dawn-prefix/src/dawn-build/prefix/dawn/cmake/                     \
         -DGRIDTOOLS_ROOT=${build_dir}/prefix/gridtools/                                           \
      || fatal_error "failed to configure"
make -j2 || fatal_error "failed to build"

# Run unittests
ctest -V -C ${CONFIG} --output-on-failure --force-new-ctest-process                                   \
     || fatal_error "failed to run tests"

popd
