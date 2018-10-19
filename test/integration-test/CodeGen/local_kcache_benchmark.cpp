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
#define GT_VECTOR_LIMIT_SIZE 30

#undef FUSION_MAX_VECTOR_SIZE
#undef FUSION_MAX_MAP_SIZE
#define FUSION_MAX_VECTOR_SIZE GT_VECTOR_LIMIT_SIZE
#define FUSION_MAX_MAP_SIZE FUSION_MAX_VECTOR_SIZE
#define BOOST_MPL_LIMIT_VECTOR_SIZE FUSION_MAX_VECTOR_SIZE
#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

#include <gtest/gtest.h>
#include "gridtools/clang/verify.hpp"
#include "test/integration-test/CodeGen/Macros.hpp"
#include "test/integration-test/CodeGen/Options.hpp"
#include "test/integration-test/CodeGen/generated/local_kcache_c++-naive.cpp"

#ifndef OPTBACKEND
#define OPTBACKEND gridtools
#endif

// clang-format off
#include INCLUDE_FILE(test/integration-test/CodeGen/generated/local_kcache_,OPTBACKEND.cpp)
// clang-format on

using namespace dawn;
TEST(local_kcache, test) {
  domain dom(Options::getInstance().m_size[0], Options::getInstance().m_size[1],
             Options::getInstance().m_size[2]);
  dom.set_halos(halo::value, halo::value, halo::value, halo::value, 0, 0);

  verifier verif(dom);

  meta_data_t meta_data(dom.isize(), dom.jsize(), dom.ksize() + 1);
  storage_t d_naive(meta_data, "d"), d_gt(meta_data, "d_gt"), c_gt(meta_data, "c_gt"), c_naive(meta_data, "c_naive");

  verif.fillMath(8.0, 2.0, 1.5, 1.5, 2.0, 4.0, d_naive);
  verif.fillMath(8.0, 2.0, 1.5, 1.5, 2.0, 4.0, d_gt);
  verif.fillMath(7.8, 2.0, 1.1, 1.7, 1.9, 4.1, c_gt);
  verif.fillMath(7.8, 2.0, 1.1, 1.7, 1.9, 4.1, c_naive);

  OPTBACKEND::local_kcache local_kcache_gt(dom, d_gt, c_gt);
  cxxnaive::local_kcache local_kcache_naive(dom, d_naive, c_naive);

  local_kcache_gt.run();
  local_kcache_naive.run();

  ASSERT_TRUE(verif.verify(d_gt, d_naive));
  ASSERT_TRUE(verif.verify(c_gt, c_naive));
}