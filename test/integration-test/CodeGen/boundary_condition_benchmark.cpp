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
#define GRIDTOOLS_CLANG_GENERATED 1
#define GRIDTOOLS_CLANG_HALO_EXTEND 3
#include "gridtools/clang/verify.hpp"
#include "test/integration-test/CodeGen/Options.hpp"
#include "test/integration-test/CodeGen/generated/boundary_condition_c++-naive.cpp"
#include "test/integration-test/CodeGen/generated/boundary_condition_gridtools.cpp"
#include <gtest/gtest.h>

#ifdef __CUDACC__
#include <boundary-conditions/apply_gpu.hpp>
#else
#include <boundary-conditions/apply.hpp>
#endif

using namespace dawn;
TEST(split_stencil, test) {
  domain dom(Options::getInstance().m_size[0], Options::getInstance().m_size[1],
             Options::getInstance().m_size[2]);
  dom.set_halos(GRIDTOOLS_CLANG_HALO_EXTEND, GRIDTOOLS_CLANG_HALO_EXTEND,
                GRIDTOOLS_CLANG_HALO_EXTEND, GRIDTOOLS_CLANG_HALO_EXTEND, 0, 0);
  verifier verif(dom);

  meta_data_t meta_data(dom.isize(), dom.jsize(), dom.ksize() + 1);
  storage_t in_naive(meta_data, "in-naive"), in_gt(meta_data, "in-gt"), out_gt(meta_data, "out-gt"),
      out_naive(meta_data, "out-naive");

  verif.fillMath(8.0, 2.0, 1.5, 1.5, 2.0, 4.0, in_naive, in_gt);
  verif.fill_boundaries(10, in_naive);
  verif.fill(-1.0, out_gt, out_naive);

  gridtools::split_stencil copy_gt(dom, in_gt, out_gt);
  cxxnaive::split_stencil copy_naive(dom, in_naive, out_naive);

  copy_gt.run();
  copy_naive.run();

  ASSERT_TRUE(verif.verify(out_gt, out_naive));
  ASSERT_TRUE(verif.verify(in_gt, in_naive));
}
