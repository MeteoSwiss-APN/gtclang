#!/bin/bash
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
##  See LICENSE.txt for details.
##
##===------------------------------------------------------------------------------------------===##

this_script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

build_dir=$(pwd)/travis_build
mkdir $build_dir

cd $build_dir


export CACHE_DIR=${build_dir}
echo " CC $CACHE_DIR "

export BOOST_VERSION=1.60.0
export GRIDTOOLS_VERSION=1.05.02
export CMAKE_VERSION=3.8.1
export PROTOBUF_VERSION=3.4.1
export CXX_COMPILER=`which g++-5`
export C_COMPILER=`which gcc-5`

bash ${this_script_dir}/gtclang-driver-test.sh
