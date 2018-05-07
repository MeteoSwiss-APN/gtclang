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

#pragma once

#include "gridtools/clang/dimension.hpp"
#include "gridtools/clang/direction.hpp"
#include "gridtools/clang/interval.hpp"
#include "gridtools/clang/offset.hpp"
#include <type_traits>

namespace gridtools {

namespace clang {

/**
 * @brief Dummy 3-dimensional storage
 * @ingroup gridtools_clang
 */
struct storage {
  storage();

  template <typename T>
  storage(T...);

  storage& operator=(const storage&);
  storage& operator+=(const storage&);
  storage& operator-=(const storage&);
  storage& operator/=(const storage&);
  storage& operator*=(const storage&);

  storage& operator()(int, int, int);

  /**
   * @name 1D access
   * @{
   */
  storage& operator()(direction);
  storage& operator()(dimension);
  storage& operator()(offset);
  /** @} */

  /**
   * @name 2D access
   * @{
   */

  storage& operator()(dimension, dimension);

  storage& operator()(dimension, direction);
  storage& operator()(direction, dimension);
  storage& operator()(direction, direction);
  /** @} */

  /**
   * @name 3D access
   * @{
   */
  storage& operator()(dimension, dimension, dimension);

  storage& operator()(direction, direction, direction);
  storage& operator()(dimension, direction, direction);
  storage& operator()(direction, dimension, direction);
  storage& operator()(direction, direction, dimension);
  storage& operator()(dimension, dimension, direction);
  storage& operator()(dimension, direction, dimension);
  storage& operator()(direction, dimension, dimension);
  /** @} */

  operator double() const;
};

/**
 * @brief Dummy 1-dimensional storage
 * @ingroup gridtools_clang
 */
struct storage_i : public storage {
  storage_i();

  storage_i& operator=(const storage&);
  storage_i& operator+=(const storage&);
  storage_i& operator-=(const storage&);
  storage_i& operator/=(const storage&);
  storage_i& operator*=(const storage&);

  storage_i& operator()(int);

  /**
   * @name 1D access
   * @{
   */
  storage_i& operator()(direction);
  storage_i& operator()(dimension);
  storage_i& operator()(offset);
  /** @} */

  /**
   * @name 2D access
   * @{
   */

  storage_i& operator()(dimension, dimension);

  storage_i& operator()(dimension, direction);
  storage_i& operator()(direction, dimension);
  storage_i& operator()(direction, direction);
  /** @} */

  /**
   * @name 3D access
   * @{
   */
  storage_i& operator()(dimension, dimension, dimension);

  storage_i& operator()(direction, direction, direction);
  storage_i& operator()(dimension, direction, direction);
  storage_i& operator()(direction, dimension, direction);
  storage_i& operator()(direction, direction, dimension);
  storage_i& operator()(dimension, dimension, direction);
  storage_i& operator()(dimension, direction, dimension);
  storage_i& operator()(direction, dimension, dimension);
  /** @} */

  operator double() const;
};

/**
 * @brief Dummy 1-dimensional storage
 * @ingroup gridtools_clang
 */
struct storage_j : public storage {
  storage_j();

  storage_j& operator=(const storage&);
  storage_j& operator+=(const storage&);
  storage_j& operator-=(const storage&);
  storage_j& operator/=(const storage&);
  storage_j& operator*=(const storage&);

  storage_j& operator()(int);

  /**
   * @name 1D access
   * @{
   */
  storage_j& operator()(direction);
  storage_j& operator()(dimension);
  storage_j& operator()(offset);
  /** @} */

  /**
   * @name 2D access
   * @{
   */

  storage_j& operator()(dimension, dimension);

  storage_j& operator()(dimension, direction);
  storage_j& operator()(direction, dimension);
  storage_j& operator()(direction, direction);
  /** @} */

  /**
   * @name 3D access
   * @{
   */
  storage_j& operator()(dimension, dimension, dimension);

  storage_j& operator()(direction, direction, direction);
  storage_j& operator()(dimension, direction, direction);
  storage_j& operator()(direction, dimension, direction);
  storage_j& operator()(direction, direction, dimension);
  storage_j& operator()(dimension, dimension, direction);
  storage_j& operator()(dimension, direction, dimension);
  storage_j& operator()(direction, dimension, dimension);
  /** @} */

  operator double() const;
};

/**
 * @brief Dummy 1-dimensional storage
 * @ingroup gridtools_clang
 */
struct storage_k : public storage {
  storage_k();

  storage_k& operator=(const storage&);
  storage_k& operator+=(const storage&);
  storage_k& operator-=(const storage&);
  storage_k& operator/=(const storage&);
  storage_k& operator*=(const storage&);

  storage_k& operator()(int);

  /**
   * @name 1D access
   * @{
   */
  storage_k& operator()(direction);
  storage_k& operator()(dimension);
  storage_k& operator()(offset);
  /** @} */

  /**
   * @name 2D access
   * @{
   */

  storage_k& operator()(dimension, dimension);

  storage_k& operator()(dimension, direction);
  storage_k& operator()(direction, dimension);
  storage_k& operator()(direction, direction);
  /** @} */

  /**
   * @name 3D access
   * @{
   */
  storage_k& operator()(dimension, dimension, dimension);

  storage_k& operator()(direction, direction, direction);
  storage_k& operator()(dimension, direction, direction);
  storage_k& operator()(direction, dimension, direction);
  storage_k& operator()(direction, direction, dimension);
  storage_k& operator()(dimension, dimension, direction);
  storage_k& operator()(dimension, direction, dimension);
  storage_k& operator()(direction, dimension, dimension);
  /** @} */

  operator double() const;
};

/**
 * @brief Dummy 2-dimensional storage
 * @ingroup gridtools_clang
 */
struct storage_ij : public storage {
  storage_ij();

  storage_ij& operator=(const storage&);
  storage_ij& operator+=(const storage&);
  storage_ij& operator-=(const storage&);
  storage_ij& operator/=(const storage&);
  storage_ij& operator*=(const storage&);

  storage_ij& operator()(int, int);

  /**
   * @name 1D access
   * @{
   */
  storage_ij& operator()(dimension);

  storage_ij& operator()(direction);
  storage_ij& operator()(offset);
  /** @} */

  /**
   * @name 2D access
   * @{
   */

  storage_ij& operator()(dimension, dimension);

  storage_ij& operator()(dimension, direction);
  storage_ij& operator()(direction, dimension);
  storage_ij& operator()(direction, direction);
  /** @} */

  /**
   * @name 3D access
   * @{
   */
  storage_ij& operator()(dimension, dimension, dimension);

  storage_ij& operator()(direction, direction, direction);
  storage_ij& operator()(dimension, direction, direction);
  storage_ij& operator()(direction, dimension, direction);
  storage_ij& operator()(direction, direction, dimension);
  storage_ij& operator()(dimension, dimension, direction);
  storage_ij& operator()(dimension, direction, dimension);
  storage_ij& operator()(direction, dimension, dimension);
  /** @} */

  operator double() const;
};

/**
 * @brief Dummy 2-dimensional storage
 * @ingroup gridtools_clang
 */
struct storage_ik : public storage {
  storage_ik();

  storage_ik& operator=(const storage&);
  storage_ik& operator+=(const storage&);
  storage_ik& operator-=(const storage&);
  storage_ik& operator/=(const storage&);
  storage_ik& operator*=(const storage&);

  storage_ik& operator()(int, int);

  /**
   * @name 1D access
   * @{
   */
  storage_ik& operator()(dimension);

  storage_ik& operator()(direction);
  storage_ik& operator()(offset);
  /** @} */

  /**
   * @name 2D access
   * @{
   */

  storage_ik& operator()(dimension, dimension);

  storage_ik& operator()(dimension, direction);
  storage_ik& operator()(direction, dimension);
  storage_ik& operator()(direction, direction);
  /** @} */

  /**
 * @name 3D access
 * @{
 */
  storage_ik& operator()(dimension, dimension, dimension);

  storage_ik& operator()(direction, direction, direction);
  storage_ik& operator()(dimension, direction, direction);
  storage_ik& operator()(direction, dimension, direction);
  storage_ik& operator()(direction, direction, dimension);
  storage_ik& operator()(dimension, dimension, direction);
  storage_ik& operator()(dimension, direction, dimension);
  storage_ik& operator()(direction, dimension, dimension);
  /** @} */

  operator double() const;
};

/**
 * @brief Dummy 2-dimensional storage
 * @ingroup gridtools_clang
 */
struct storage_jk : public storage {
  storage_jk();

  storage_jk& operator=(const storage&);
  storage_jk& operator+=(const storage&);
  storage_jk& operator-=(const storage&);
  storage_jk& operator/=(const storage&);
  storage_jk& operator*=(const storage&);

  storage_jk& operator()(int, int);

  /**
   * @name 1D access
   * @{
   */
  storage_jk& operator()(dimension);

  storage_jk& operator()(direction);
  storage_jk& operator()(offset);
  /** @} */

  /**
   * @name 2D access
   * @{
   */

  storage_jk& operator()(dimension, dimension);

  storage_jk& operator()(dimension, direction);
  storage_jk& operator()(direction, dimension);
  storage_jk& operator()(direction, direction);
  /** @} */

  /**
 * @name 3D access
 * @{
 */
  storage_jk& operator()(dimension, dimension, dimension);

  storage_jk& operator()(direction, direction, direction);
  storage_jk& operator()(dimension, direction, direction);
  storage_jk& operator()(direction, dimension, direction);
  storage_jk& operator()(direction, direction, dimension);
  storage_jk& operator()(dimension, dimension, direction);
  storage_jk& operator()(dimension, direction, dimension);
  storage_jk& operator()(direction, dimension, dimension);
  /** @} */

  operator double() const;
};

/**
 * @brief Dummy 3-dimensional storage
 * @ingroup gridtools_clang
 */
struct storage_ijk {
  storage_ijk();

  template <typename T>
  storage_ijk(T...);

  storage_ijk& operator=(const storage&);
  storage_ijk& operator+=(const storage&);
  storage_ijk& operator-=(const storage&);
  storage_ijk& operator/=(const storage&);
  storage_ijk& operator*=(const storage&);

  storage_ijk& operator()(int, int, int);

  /**
   * @name 1D access
   * @{
   */
  storage_ijk& operator()(direction);
  storage_ijk& operator()(dimension);
  storage_ijk& operator()(offset);
  /** @} */

  /**
   * @name 2D access
   * @{
   */

  storage_ijk& operator()(dimension, dimension);

  storage_ijk& operator()(dimension, direction);
  storage_ijk& operator()(direction, dimension);
  storage_ijk& operator()(direction, direction);
  /** @} */

  /**
   * @name 3D access
   * @{
   */
  storage_ijk& operator()(dimension, dimension, dimension);

  storage_ijk& operator()(direction, direction, direction);
  storage_ijk& operator()(dimension, direction, direction);
  storage_ijk& operator()(direction, dimension, direction);
  storage_ijk& operator()(direction, direction, dimension);
  storage_ijk& operator()(dimension, dimension, direction);
  storage_ijk& operator()(dimension, direction, dimension);
  storage_ijk& operator()(direction, dimension, dimension);
  /** @} */

  operator double() const;
};

struct var {
  var();

  template <typename T>
  var(T...);

  var& operator=(const var&);
  var& operator+=(const var&);
  var& operator-=(const var&);
  var& operator/=(const var&);
  var& operator*=(const var&);

  /**
   * @name 1D access
   * @{
   */
  var& operator()(direction);
  var& operator()(dimension);
  var& operator()(offset);
  /** @} */

  /**
   * @name 2D access
   * @{
   */
  var& operator()(dimension, dimension);

  var& operator()(dimension, direction);
  var& operator()(direction, dimension);
  var& operator()(direction, direction);
  /** @} */

  /**
   * @name 3D access
   * @{
   */
  var& operator()(dimension, dimension, dimension);

  var& operator()(direction, direction, direction);
  var& operator()(dimension, direction, direction);
  var& operator()(direction, dimension, direction);
  var& operator()(direction, direction, dimension);
  var& operator()(dimension, dimension, direction);
  var& operator()(dimension, direction, dimension);
  var& operator()(direction, dimension, dimension);
  /** @} */

  operator double() const;
};

#ifndef GRIDTOOLS_CLANG_META_DATA_T_DEFINED
struct meta_data {
  template <typename T>
  meta_data(T...);
};
using meta_data_t = meta_data;
using meta_data_ijk_t = meta_data;
using meta_data_ij_t = meta_data;
using meta_data_j_t = meta_data;
using meta_data_j_t = meta_data;
using meta_data_k_t = meta_data;
using meta_data_scalar_t = meta_data;
#endif

#ifndef GRIDTOOLS_CLANG_STORAGE_T_DEFINED
using storage_t = storage;
using storage_ijk_t = storage_ijk;
using storage_ij_t = storage_ij;
using storage_i_t = storage_i;
using storage_j_t = storage_j;
using storage_k_t = storage_k;
using storage_scalar_t = storage;
#endif

#ifdef GRIDTOOLS_CLANG_GENERATED
using ::gridtools::make_host_view;
#else
template <typename T>
storage_t make_host_view(T...);
#endif
}
}
