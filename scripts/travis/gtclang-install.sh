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

# @brief Download Dawn and setup the git repository. 
#
# Note that we always fetch the master branch of your Dawn repository i.e 
# `https://github.com/<username>/dawn.git` if possible.
gtclang_get_dawn() {
  pushd $(pwd)

  fatal_error_bootstrap() {
    echo "ERROR: $1"
    exit 1
  }

  # Update the repository
  if [[ ! -z "$(ls -A ${DAWN_DIR} 2> /dev/null )" ]]; then
    # We have cached version, pull changes
    cd "${DAWN_DIR}"
    git pull origin master || fatal_error_bootstrap "failed to update master"

  else

    # Dawn does not exist, fetch it from github
    local gtclang_git_url=$(git remote get-url --push origin)
    local dawn_git_url=$(sed 's/gtclang/dawn/g' <<< "$gtclang_git_url")

    eval git ls-remote --exit-code -h "$dawn_git_url" &> /dev/null
    local ret=$?

    if [ "$ret" != "0" ]; then
      # There is no `<username>/dawn.git`, use the offcial trunk `MeteoSwiss-APN/dawn.git`
      dawn_git_url="https://github.com/MeteoSwiss-APN/dawn.git"
    fi

    echo "Cloning from $dawn_git_url"
    git clone $dawn_git_url "$DAWN_DIR" || fatal_error_bootstrap "failed to clone master"
  fi

  # Create symlinks for packages
  ln -sf "$this_script_dir/install_boost.sh" "$DAWN_SCRIPT_DIR/install_boost.sh"                   \
    || fatal_error_bootstrap "failed to create symlinks"

  ln -sf "$this_script_dir/install_gridtools.sh" "$DAWN_SCRIPT_DIR/install_gridtools.sh"               \
    || fatal_error_bootstrap "failed to create symlinks"

  popd
}

# @brief Build Dawn from source
gtclang_build_dawn() {
  pushd $(pwd)

  local dawn_install_dir="$DAWN_DIR/install"
  local dawn_build_dir="$DAWN_DIR/build"

  mkdir -p "$DAWN_DIR/build" && cd "$DAWN_DIR/build"
  cmake .. -DCMAKE_CXX_COMPILER="$CXX"                                                             \
        -DCMAKE_C_COMPILER="$CC"                                                                   \
        -DCMAKE_BUILD_TYPE="$CONFIG"                                                               \
        -DProtobuf_DIR="$Protobuf_DIR"                                                             \
        -DCMAKE_INSTALL_PREFIX="$dawn_install_dir"                                                 \
      || fatal_error "failed to configure"

  make -j2 install || fatal_error "failed to build"
  export DAWN_ROOT="$dawn_install_dir"

  popd
}

gtclang_install_dependencies() {
  export DAWN_DIR="$CACHE_DIR/dawn"
  export DAWN_SCRIPT_DIR="$DAWN_DIR/scripts/travis"

  # Fetch Dawn
  gtclang_get_dawn

  # Install 3rd party dependencies
  source "$DAWN_SCRIPT_DIR/install.sh"
  install_driver -i ${CACHE_DIR} -b cmake,protobuf,boost,gridtools -c boost:system

  # Install Dawn
  gtclang_build_dawn
}
