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

include(msbuildExportPackage)

if(NOT DEFINED(dawn_DIR) AND DEFINED DAWN_ROOT)
  set(dawn_DIR "${DAWN_ROOT}/cmake")
endif()
find_package(dawn NO_MODULE REQUIRED)

msbuild_export_package(
  NAME dawn
  FOUND ${DAWN_FOUND} 
  VERSION "${DAWN_VERSION}" 
  LIBRARIES ${DAWN_STATIC_LIBRARY}
  INCLUDE_DIRS ${DAWN_INCLUDE_DIRS}
)
