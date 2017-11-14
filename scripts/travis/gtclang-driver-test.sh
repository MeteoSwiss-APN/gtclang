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

function help() {
  echo "./gtclang-driver-test [-components <comp>]"
}

#Check the number of arguments. If none are passed, print help and exit.
NUMARGS=$#
# echo -e \\n"Number of arguments: $NUMARGS"

if [ $NUMARGS -gt 2 ]; then
  echo "wrong number of parameters $@"
  help
  exit 1
fi

OPTS=`getopt -o c: --long components: -n 'parse-options' -- "$@"`

eval set -- "$OPTS"

components="cmake,protobuf,boost,gridtools"

while getopts "c:" opt; do
  case $opt in 
  c)
     components=$OPTARG
     ;;
  \?) #unrecognized option - show help
     echo -e \\n"Option -${BOLD}$OPTARG${NORM} not allowed."
     ;;
  esac
done

this_script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Setup dependencies
source "$this_script_dir/gtclang-install.sh"

gtclang_install_dependencies $components

if [ ! -z ${CLANG_VERSION+x} ]; then
  install_driver -i "${CACHE_DIR}" -b clang
fi

export CXX=${CXX_COMPILER}
export CC=${C_COMPILER}

$CC --version
$CXX --version

# Build gtclang
pushd "$(pwd)"

mkdir build && cd build
cmake .. -DCMAKE_CXX_COMPILER="$CXX"                                                               \
         -DCMAKE_C_COMPILER="$CC"                                                                  \
         -DCMAKE_BUILD_TYPE="$CONFIG"                                                              \
         -DBOOST_ROOT="$BOOST_ROOT"                                                                \
         -DGRIDTOOLS_ROOT="$GRIDTOOLS_ROOT"                                                        \
         -DDAWN_ROOT="$DAWN_ROOT"                                                                  \
         -DGTCLANG_TESTING=ON                                                                      \
         -DGTCLANG_UNIT_TESTING=ON                                                                 \
         -DGTCLANG_INTEGRATION_TESTING=ON                                                          \
      || fatal_error "failed to configure"
make -j2 || fatal_error "failed to build"

# Run unittests
ctest -C ${CONFIG} --output-on-failure --force-new-ctest-process                                   \
     || fatal_error "failed to run tests"

# Run regression tests
bash ./gtclang-tester-no-codegen.sh || fatal_error "failed to run tests"

popd
