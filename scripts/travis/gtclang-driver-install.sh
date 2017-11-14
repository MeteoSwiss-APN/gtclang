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

function help() {
  echo "./gtclang-driver-test [-components <comp>]"
}

#Check the number of arguments. If none are passed, print help and exit.
NUMARGS=$#
# echo -e \\n"Number of arguments: $NUMARGS"
if [ $NUMARGS -gt 1 ]; then
  help
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
source "$this_script_dir/gtclang-install.sh"
gtclang_install_dependencies $components

