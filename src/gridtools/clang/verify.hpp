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

#ifndef GRIDTOOLS_CLANG_VERIFY_HPP
#define GRIDTOOLS_CLANG_VERIFY_HPP

#include "gridtools/clang_dsl.hpp"
#include <array>
#include <cmath>
#include <cstdlib>
#include <iostream>

namespace gridtools {

    namespace clang {

        class verifier {
          public:
            verifier(const domain &dom,
                double precision = std::is_same< gridtools::float_type, double >::value ? 1e-12
                                                                                        : 1e-6)
                : m_domain(dom), m_precision(precision) {}

            template < class FunctorType, class... StorageTypes >
            void for_each(FunctorType &&functor, StorageTypes &... storages) const {
                for_each_impl(std::forward< FunctorType >(functor), storages...);
            }
            template < class FunctorType, class... StorageTypes >
            void for_each_boundary(FunctorType &&functor, StorageTypes &... storages) const {
                for_each_boundary_impl(std::forward< FunctorType >(functor), storages...);
            }

            template < class ValueType, class... StorageTypes >
            void fill(ValueType value, StorageTypes &... storages) const {
                fill_impl(value, storages...);
            }

            template < class... StorageTypes >
            void fillMath(double a,
                double b,
                double c,
                double d,
                double e,
                double f,
                StorageTypes &... storages) const {
                const gridtools::float_type pi = std::atan(1.) * 4.;
                for_each(
                    [&](std::array< unsigned int, 3 > dims, int i, int j, int k) {
                        // 8,2,1.5,1.5,2,4
                        double x = i / (gridtools::float_type)dims[0];
                        double y = j / (gridtools::float_type)dims[1];
                        return k +
                               (gridtools::float_type)a *
                                   ((gridtools::float_type)b +
                                       cos(pi * (x + (gridtools::float_type)c * y)) +
                                       sin((gridtools::float_type)d * pi *
                                           (x + (gridtools::float_type)e * y))) /
                                   (gridtools::float_type)f;
                    },
                    storages...);
            }
            template < class... StorageTypes >
            void fill_random(StorageTypes &... storages) const {
                for_each(
                    [&](int, int, int) { return static_cast< double >(std::rand()) / RAND_MAX; },
                    storages...);
            }

            template < class ValueType, class... StorageTypes >
            void fill_boundaries(ValueType value, StorageTypes &... storages) const {
                boundary_fill_impl(value, storages...);
            }

            template < class StorageType1, class StorageType2 >
            bool verify(StorageType1 &storage1, StorageType2 &storage2, int max_erros = 10) const {
                using namespace gridtools;

                storage1.sync();
                storage2.sync();

                auto meta_data_1 = *storage1.get_storage_info_ptr();
                auto meta_data_2 = *storage2.get_storage_info_ptr();

                const uint_t idim1 = meta_data_1.template unaligned_dim< 0 >();
                const uint_t jdim1 = meta_data_1.template unaligned_dim< 1 >();
                const uint_t kdim1 = meta_data_1.template unaligned_dim< 2 >();

                const uint_t idim2 = meta_data_2.template unaligned_dim< 0 >();
                const uint_t jdim2 = meta_data_2.template unaligned_dim< 1 >();
                const uint_t kdim2 = meta_data_2.template unaligned_dim< 2 >();

                auto storage1_v = make_host_view(storage1);
                auto storage2_v = make_host_view(storage2);

                // Check dimensions
                auto check_dim = [&](uint_t dim1, uint_t dim2, uint_t size, const char *dimstr) {
                    if (dim1 != dim2 || dim1 < size) {
                        std::cerr << "dimension \"" << dimstr << "\" missmatch in storage pair \""
                                  << storage1.name() << "\" : \"" << storage2.name() << "\"\n";
                        std::cerr << "  " << dimstr << "-dim storage1: " << dim1 << "\n";
                        std::cerr << "  " << dimstr << "-dim storage2: " << dim2 << "\n";
                        std::cerr << "  " << dimstr << "-size domain: " << size << "\n";
                        return false;
                    }
                    return true;
                };

                check_dim(idim1, idim2, m_domain.isize(), "i");
                check_dim(jdim1, jdim2, m_domain.jsize(), "j");
                check_dim(kdim1, kdim2, m_domain.ksize(), "k");

                bool verified = true;

                for (int i = m_domain.iminus(); i < (m_domain.isize() - m_domain.iplus()); ++i)
                    for (int j = m_domain.jminus(); j < (m_domain.jsize() - m_domain.jplus()); ++j)
                        for (int k = m_domain.kminus(); k < (m_domain.ksize() - m_domain.kplus());
                             ++k) {
                            typename StorageType1::data_t value1 = storage1_v(i, j, k);
                            typename StorageType2::data_t value2 = storage2_v(i, j, k);
                            if (!compare_below_threashold(value1, value2, m_precision)) {
                                if (--max_erros >= 0) {
                                    std::cerr
                                        << "( " << i << ", " << j << ", " << k << " ) : "
                                        << " " << storage1.name() << " = " << value1 << " ; "
                                        << " " << storage2.name() << " = " << value2
                                        << "  error: " << std::fabs((value2 - value1) / (value2))
                                        << std::endl;
                                }
                                verified = false;
                            }
                        }

                return verified;
            }

          private:
            template < typename value_type >
            bool compare_below_threashold(
                value_type expected, value_type actual, value_type precision) const {
                if (std::fabs(expected) < 1e-3 && std::fabs(actual) < 1e-3) {
                    if (std::fabs(expected - actual) < precision)
                        return true;
                } else {
                    if (std::fabs((expected - actual) / (precision * expected)) < 1.0)
                        return true;
                }
                return false;
            }

            template < class StorageType, class FunctorType >
            void for_each_do_it(FunctorType &&functor, StorageType &storage) const {
                using namespace gridtools;

                auto sinfo = *(storage.get_storage_info_ptr());
                auto storage_v = make_host_view(storage);
                const uint_t d1 = sinfo.template unaligned_dim< 0 >();
                const uint_t d2 = sinfo.template unaligned_dim< 1 >();
                const uint_t d3 = sinfo.template unaligned_dim< 2 >();

                for (uint_t i = 0; i < d1; ++i) {
                    for (uint_t j = 0; j < d2; ++j) {
                        for (uint_t k = 0; k < d3; ++k) {
                            storage_v(i, j, k) =
                                functor(std::array< uint_t, 3 >{d1, d2, d3}, i, j, k);
                        }
                    }
                }
                storage_v.sync();
            }

            template < class FunctorType, class StorageType >
            void for_each_impl(FunctorType &&functor, StorageType &storage) const {
                for_each_do_it(std::forward< FunctorType >(functor), storage);
            }

            template < class FunctorType, class StorageType, class... StorageTypes >
            void for_each_impl(
                FunctorType &&functor, StorageType &storage, StorageTypes &... storages) const {
                using namespace gridtools;
                for_each_do_it(std::forward< FunctorType >(functor), storage);
                for_each_impl(std::forward< FunctorType >(functor), storages...);
            }

            template < class StorageType >
            void fill_impl(typename StorageType::data_t value, StorageType &storage) const {
                using namespace gridtools;
                for_each(
                    [&](std::array< uint_t, 3 > dims, uint_t i, uint_t j, uint_t k) {
                        return value;
                    },
                    storage);
            }

            template < class StorageType, class... StorageTypes >
            void fill_impl(typename StorageType::data_t value,
                StorageType &storage,
                StorageTypes &... storages) const {
                using namespace gridtools;
                for_each(
                    [&](std::array< uint_t, 3 > dims, uint_t i, uint_t j, uint_t k) {
                        return value;
                    },
                    storage);
                fill_impl(value, storages...);
            }

            template < class StorageType, class FunctorType >
            void for_each_boundary_do_it(FunctorType &&functor, StorageType &storage) const {
                using namespace gridtools;

                auto sinfo = *(storage.get_storage_info_ptr());
                auto storage_v = make_host_view(storage);
                const uint_t start_d1 = sinfo.template total_begin< 0 >();
                const uint_t halo_d1 = decltype(sinfo)::halo_t::template at< 0 >();
                const uint_t end_d1 = sinfo.template total_end< 0 >();

                const uint_t start_d2 = sinfo.template total_begin< 1 >();
                const uint_t halo_d2 = decltype(sinfo)::halo_t::template at< 1 >();
                const uint_t end_d2 = sinfo.template total_end< 1 >();

                const uint_t d3 = sinfo.template unaligned_dim< 2 >();

                for (uint_t k = 0; k < d3; ++k) {
                    for (uint_t i = start_d1; i < halo_d1; ++i) {
                        for (uint_t j = start_d2; j < end_d2; ++j) {
                            storage_v(i, j, k) =
                                functor(std::array< uint_t, 3 >{end_d1, end_d2, d3}, i, j, k);
                        }
                    }
                    for (uint_t i = halo_d1; i < end_d1 - halo_d1; ++i) {
                        for (uint_t j = start_d2; j < halo_d2; ++j) {
                            storage_v(i, j, k) =
                                functor(std::array< uint_t, 3 >{end_d1, end_d2, d3}, i, j, k);
                        }
                        for (uint_t j = end_d2 - halo_d2; j < end_d2; ++j) {
                            storage_v(i, j, k) =
                                functor(std::array< uint_t, 3 >{end_d1, end_d2, d3}, i, j, k);
                        }
                    }
                    for (uint_t i = end_d1 - halo_d1; i < end_d1; ++i) {
                        for (uint_t j = start_d2; j < end_d2; ++j) {
                            storage_v(i, j, k) =
                                functor(std::array< uint_t, 3 >{end_d1, end_d2, d3}, i, j, k);
                        }
                    }
                }
                storage_v.sync();
            }

            template < class FunctorType, class StorageType >
            void for_each_boundary_impl(FunctorType &&functor, StorageType &storage) const {
                for_each_boundary_do_it(std::forward< FunctorType >(functor), storage);
            }

            template < class FunctorType, class StorageType, class... StorageTypes >
            void for_each_boundary_impl(
                FunctorType &&functor, StorageType &storage, StorageTypes &... storages) const {
                using namespace gridtools;
                for_each_boundary_do_it(std::forward< FunctorType >(functor), storage);
                for_each_boundary_impl(std::forward< FunctorType >(functor), storages...);
            }
            template < class StorageType >
            void boundary_fill_impl(
                typename StorageType::data_t value, StorageType &storage) const {
                using namespace gridtools;
                for_each_boundary(
                    [&](std::array< uint_t, 3 > dims, uint_t i, uint_t j, uint_t k) {
                        return value;
                    },
                    storage);
            }

            template < class StorageType, class... StorageTypes >
            void boundary_fill_impl(typename StorageType::data_t value,
                StorageType &storage,
                StorageTypes &... storages) const {
                using namespace gridtools;
                for_each_boundary(
                    [&](std::array< uint_t, 3 > dims, uint_t i, uint_t j, uint_t k) {
                        return value;
                    },
                    storage);
                boundary_fill_impl(value, storages...);
            }

          private:
            domain m_domain;
            double m_precision;
        };
    }
}

#endif
