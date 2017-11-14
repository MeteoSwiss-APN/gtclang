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
  local gridtools_branch=$1
  local gridtools_install_dir=$install_dir/gridtools-$gridtools_branch

  local boost_install_dir=`find $install_dir -name boost-[[:digit:]]* -type d`

  abort_and_cleanup() {
    rm -rf "$gridtools_install_dir" && mkdir -p "$gridtools_install_dir" 
    fatal_error "$1"
  }

  NOTICE "${FUNCNAME[0]}: Installing gridtools $gridtools_branch into \"$gridtools_install_dir\" ..."
  mkdir -p "${gridtools_install_dir}"

  NOTICE "${FUNCNAME[0]}: checking ${gridtools_install_dir}"
  if [[ "$(ls -A ${gridtools_install_dir})" != "" ]]; then
    NOTICE "${FUNCNAME[0]}: Package already installed. Skipping."
  else
    local gridtools_url="git@github.com:eth-cscs/gridtools.git"

    NOTICE "${FUNCNAME[0]}: Downloading gridtools $gridtools_url ; branch: ${gridtools_branch} ..."
    git clone -b ${gridtools_branch} ${gridtools_url} ${gridtools_install_dir} ||       \
      abort_and_cleanup "Failed to download gridtools from: $gridtools_url"   
    NOTICE "${FUNCNAME[0]}: Successfully downloaded $gridtools_url"
    
    cd ${gridtools_install_dir}
    mkdir build 
    cd build
    cmake .. -DBoost_NO_BOOST_CMAKE="true" \
             -DCMAKE_BUILD_TYPE:STRING="Release" \
             -DBUILD_SHARED_LIBS:BOOL=ON \
             -DUSE_GPU:BOOL=OFF \
             -DGCL_ONLY:BOOL=OFF \
             -DCMAKE_CXX_COMPILER="${CXX}" \
             -DUSE_MPI:BOOL=OFF \
             -DSINGLE_PRECISION:BOOL=OFF \
             -DENABLE_PERFORMANCE_METERS:BOOL=ON \
             -DSTRUCTURED_GRIDS:BOOL=ON \
             -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
             -DBOOST_ROOT=$boost_install_dir \
             -DDISABLE_TESTING:BOOL=ON       

    make install -j2
  fi
  
  local elapsed_time=$(expr $(date +%s) - $start_time)
  NOTICE $(printf "${FUNCNAME[0]}: Successfully installed gridtools $gridtools_branch (took %dm %ds)\n"   \
           $(($elapsed_time%3600/60)) $(($elapsed_time%60)))

  export GRIDTOOLS_ROOT="${gridtools_install_dir}"
  popd
}
