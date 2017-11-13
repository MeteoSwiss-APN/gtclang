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

# @brief Install the GridTools libraries
#
# @param $1   Install directory
# @param $2   GridTools version triple (X.Y.Z)
# @param $3   GridTools components to build (',' separated)
function install_gridtools() {
  pushd $(pwd)
  local start_time=$(date +%s)

  if [[ $# -lt 2 ]]; then
    fatal_error "argument mistmatch: ${FUNCNAME[0]} <install_prefix> <version>"
  fi

  local install_dir=$1
  shift
  local gridtools_version=$1

  local gridtools_install_dir=$install_dir/gridtools-$gridtools_version

  abort_and_cleanup() {
    rm -rf "$gridtools_install_dir" && mkdir -p "$gridtools_install_dir" 
    fatal_error "$1"
  }

  NOTICE "${FUNCNAME[0]}: Installing gridtools $gridtools_version into \"$gridtools_install_dir\" ..."
  mkdir -p "${gridtools_install_dir}"

  echo "checking ${gridtools_install_dir}"
  if [[ "$(ls -A ${gridtools_install_dir})" != "" ]]; then
    NOTICE "${FUNCNAME[0]}: Package already installed. Skipping."
  else
    local gridtools_url="git@github.com:eth-cscs/gridtools.git"

    NOTICE "${FUNCNAME[0]}: Downloading gridtools $gridtools_url ..."
    git clone -b ${gridtools_version} ${gridtools_url} ${gridtools_install_dir} ||       \
      abort_and_cleanup "Failed to download boost from: $gridtools_url"   
    NOTICE "${FUNCNAME[0]}: Successfully downloaded $gridtools_url"
  fi
  
  local elapsed_time=$(expr $(date +%s) - $start_time)
  NOTICE $(printf "${FUNCNAME[0]}: Successfully installed gridtools $gridtools_version (took %dm %ds)\n"   \
           $(($elapsed_time%3600/60)) $(($elapsed_time%60)))

  export GRIDTOOLS_ROOT="${gridtools_install_dir}"
  popd
}
