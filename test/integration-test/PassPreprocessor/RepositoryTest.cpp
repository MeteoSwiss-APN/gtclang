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

// clang-format off
#include "gridtools/clang_dsl.hpp"

using namespace gridtools::clang;

repository someglobals {
  storage global_field;
  storage other_field, third_field;
};

repository moreglobals {
  storage last_field;
};

stencil Test03{
    storage foo;
    repository moreglobals; // EXPECTED: %line%: storage last_field;

    void Do(){
        vertical_region(k_start, k_end){
            foo = last_field;
            foo[j + 1] = last_field[j - 1];
        }
    }
};

stencil Test01 {
  storage foo, bar;
  repository someglobals;

  void Do() {
    vertical_region(k_start, k_end) {
      foo[i + 1] = global_field[j - 1]; 
      bar += other_field[j - 1] + third_field[j + 1];
    }
  }
};

stencil Test02 {
  storage foo, bar;
  repository moreglobals, someglobals;
  void Do() {
    vertical_region(k_start, k_start) {
      bar = last_field[i + 1] + global_field[j + 1];
      foo = other_field;
    }
  }
};
// clang-format on
