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

stencil copy_stencil {
  storage in, lap, out;

  Do {
    vertical_region(k_start, k_flat) {
       lap = in[j-1];
    }
    vertical_region(k_flat+2, k_end) {
       lap = in(i+1);
    }
    vertical_region(k_start, k_end) {
       out = lap[i+1] + lap[i-1] + lap[j+1] + lap[j-1];
    }
  }
};
