//===--------------------------------------------------------------------------------*- C++ -*-===//
//                         _       _
//                        | |     | |
//                    __ _| |_ ___| | __ _ _ __   __ _
//                   / _` | __/ __| |/ _` | '_ \ / _` |
//                  | (_| | || (__| | (_| | | | | (_| |
//                   \__, |\__\___|_|\__,_|_| |_|\__, | - GridTools Clang DSL
//                    __/ |                       __/ |
//                   |___/                       |___/
//
//
//  This file is distributed under the MIT License (MIT).
//  See LICENSE.txt for details.
//
//===------------------------------------------------------------------------------------------===//

#include "gridtools/clang_dsl.hpp"
using namespace gridtools::clang;

#ifndef GRIDTOOLS_CLANG_GENERATED
interval k_flat = k_start + 4;
#endif

globals {
  int var_runtime;        // == 1
  double var_default = 2.0; // == 2
  bool var_compiletime;   // == true
};

stencil copy_stencil {
  storage in, out;

  Do {
    vertical_region(k_start, k_end) {
       out = in;
    }
  }
};
