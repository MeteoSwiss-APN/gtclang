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

include(msbuildConfigureFile)
include(msbuildAddLibrary)

msbuild_configure_file(Config.h.cmake)

msbuild_add_library(
  NAME GTClangSupport
  SOURCES FileUtil.cpp
          FileUtil.h
          Logger.cpp
          Logger.h
          StringUtil.cpp
          StringUtil.h

  OBJECT
)
