##===------------------------------------------------------------------------------*- CMake -*-===##
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

include(msbuildSetDownloadDir)
include(msbuildFindPackage)

# Set the default download directory (define GTCLANG_ALL_DOWNLOAD_DIR)
msbuild_set_download_dir()

set(GTCLANG_ALL_INSTALL_PREFIX "${PROJECT_BINARY_DIR}/prefix")
set(GTCLANG_ALL_PACKAGE_INFO)
set(GTCLANG_ALL_PACKAGE_CMAKE_ARGS
  "-DBUILD_SHARED_LIBS:BOOL=${BUILD_SHARED_LIBS}"
  "-DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}"
  "-DCMAKE_CXX_COMPILER:PATH=${CMAKE_CXX_COMPILER}"
  "-DCMAKE_C_COMPILER:PATH=${CMAKE_C_COMPILER}"
)
set(GTCLANG_ALL_THIRDPARTY_CMAKE_ARGS)

#
# Protobuf
#
set(protobuf_version "3.4.0")
set(protobuf_version_short "3.4")
set(protobuf_url "https://github.com/google/protobuf/archive/v${protobuf_version}.tar.gz")
set(protobuf_md5 "1d077a7d4db3d75681f5c333f2de9b1a")

msbuild_find_package(
  PACKAGE Protobuf
  PACKAGE_ARGS ${protobuf_version_short} NO_MODULE QUIET
  FORWARD_VARS Protobuf_DIR
  BUILD_VERSION ${protobuf_version}
)

#
# Boost
#
set(boost_min_version 1.58.0)
set(_v 63)
set(boost_download_version 1.${_v}.0)
set(boost_url 
    "http://sourceforge.net/projects/boost/files/boost/1.${_v}.0/boost_1_${_v}_0.tar.gz/download")
set(boost_md5 "7b493c08bc9557bbde7e29091f28b605")

msbuild_find_package(
  PACKAGE Boost
  PACKAGE_ARGS ${boost_min_version} COMPONENTS ${boost_components}
  FORWARD_VARS BOOST_ROOT Boost_LIBRARY_DIRS Boost_INCLUDE_DIRS
  BUILD_VERSION ${boost_download_version}
)

#
# LLVM/Clang
#
set(llvm_clang_version "3.8.0")
set(llvm_clang_version_short "3.8")

set(llvm_clang_url_llvm 
    "http://releases.llvm.org/${llvm_clang_version}/llvm-${llvm_clang_version}.src.tar.xz")
set(llvm_clang_md5_llvm "07a7a74f3c6bd65de4702bf941b511a0")

set(llvm_clang_url_clang 
    "http://releases.llvm.org/${llvm_clang_version}/cfe-${llvm_clang_version}.src.tar.xz")
set(llvm_clang_md5_clang "cc99e7019bb74e6459e80863606250c5")

set(llvm_clang_url_libcxx 
    "http://releases.llvm.org/${llvm_clang_version}/libcxx-${llvm_clang_version}.src.tar.xz")
set(llvm_clang_md5_libcxx "d6e0bdbbee39f7907ad74fd56d03b88a")

set(llvm_clang_url_libcxxabi 
    "http://releases.llvm.org/${llvm_clang_version}/libcxxabi-${llvm_clang_version}.src.tar.xz")
set(llvm_clang_md5_libcxxabi "bbe6b4d72c7c5978550d370af529bcf7")

msbuild_find_package(
  PACKAGE Clang
  PACKAGE_ARGS ${llvm_clang_version_short} REQUIRED
  FORWARD_VARS CLANG_ROOT LLVM_ROOT
  BUILD_VERSION ${llvm_clang_version}
  VERSION_VAR LLVM_VERSION
)

#
# GridTools
#


# Prepare and export CMake variables of the external projects
set(thirdparty_cmake_args ${GTCLANG_ALL_PACKAGE_CMAKE_ARGS} ${GTCLANG_ALL_THIRDPARTY_CMAKE_ARGS})
set(GTCLANG_ALL_CMAKE_ARGS "${thirdparty_cmake_args}" CACHE INTERNAL "CMake arguments")

dawn_report_result("Package summary" ${GTCLANG_ALL_PACKAGE_INFO})
