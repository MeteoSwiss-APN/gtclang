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

// RUN: %gtclang% %file% -fno-codegen -freport-pass-preprocessor


#include "gridtools/clang_dsl.hpp"

using namespace gridtools::clang;

stencil Test01 {
  storage foo;
  var a;

  void Do() {
    vertical_region(k_start, k_end) {
      var b = foo;
      var c = 10;
    }
    vertical_region(k_start, k_end) {
      a = foo;
      var d, e = foo;
      d = 10;
      foo = e + d;
    }
    vertical_region(k_start, k_end) {
      var b, c = foo;
      b = a;
      foo = c[i-1] + b[i+1];
    }
  }
};
