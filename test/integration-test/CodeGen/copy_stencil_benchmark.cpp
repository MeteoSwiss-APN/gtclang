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
#define GT_VECTOR_LIMIT_SIZE 30

#undef FUSION_MAX_VECTOR_SIZE
#undef FUSION_MAX_MAP_SIZE
#define FUSION_MAX_VECTOR_SIZE GT_VECTOR_LIMIT_SIZE
#define FUSION_MAX_MAP_SIZE FUSION_MAX_VECTOR_SIZE
#define BOOST_MPL_LIMIT_VECTOR_SIZE FUSION_MAX_VECTOR_SIZE
#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

#include "gridtools/clang/verify.hpp"
#include "test/integration-test/CodeGen/Options.hpp"
#include "test/integration-test/CodeGen/generated/copy_stencil_c++-naive.cpp"
#include "test/integration-test/CodeGen/generated/copy_stencil_gridtools.cpp"
#include <gtest/gtest.h>

using namespace dawn;
TEST(copy_stencil, test) {
  domain dom(Options::getInstance().m_size[0], Options::getInstance().m_size[1],
             Options::getInstance().m_size[2]);
  verifier verif(dom);

  meta_data_t meta_data(dom.isize(), dom.jsize(), dom.ksize() + 1);
  storage_t in(meta_data, "in"), out_gt(meta_data, "out-gt"), out_naive(meta_data, "out-naive");

  verif.fillMath(8.0, 2.0, 1.5, 1.5, 2.0, 4.0, in);
  verif.fill(-1.0, out_gt, out_naive);

  gridtools::copy_stencil copy_gt(dom, in, out_gt);
  cxxnaive::copy_stencil copy_naive(dom, in, out_naive);

  copy_gt.run();
  copy_naive.run();

  ASSERT_TRUE(verif.verify(out_gt, out_naive));
}
