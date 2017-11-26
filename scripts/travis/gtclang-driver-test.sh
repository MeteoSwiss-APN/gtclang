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
mkdir build && cd build
cmake .. -DCMAKE_CXX_COMPILER="$CXX"                                                               \
         -DCMAKE_C_COMPILER="$CC"                                                                  \
         -DCMAKE_BUILD_TYPE="$CONFIG"                                                              \
         -DGTCLANG_TESTING=ON                                                                      \
         -DGTCLANG_UNIT_TESTING=ON                                                                 \
         -DGTCLANG_INTEGRATION_TESTING=ON                                                          \
      || fatal_error "failed to configure"
make -j2 || fatal_error "failed to build"

# Run unittests
ctest -C ${CONFIG} --output-on-failure --force-new-ctest-process                                   \
     || fatal_error "failed to run tests"

# Run regression tests
bash ./gtclang-tester-no-codegen.sh --no-progressbar || fatal_error "failed to run tests"

popd
