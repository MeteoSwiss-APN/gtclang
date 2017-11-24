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
##  See LICENSE.txt for details.
##
##===------------------------------------------------------------------------------------------===##

this_script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

gtclang_install_dependencies() {

  export DAWN_DIR="$CACHE_DIR/dawn"
  export DAWN_SCRIPT_DIR="$DAWN_DIR/scripts/travis"

  # Install 3rd party dependencies
  source "$DAWN_SCRIPT_DIR/install.sh"
  install_driver -i ${CACHE_DIR} -b cmake,protobuf,boost -c boost:system
}
