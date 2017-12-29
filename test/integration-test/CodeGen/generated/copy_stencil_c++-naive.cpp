// gtclang (0.0.1-0085b07-x86_64-linux-gnu-5.4.0)
// based on LLVM/Clang (3.8.0), Dawn (0.0.1)
// Generated on 2017-12-29  12:06:58

#define GRIDTOOLS_CLANG_GENERATED 1
#define GRIDTOOLS_CLANG_HALO_EXTEND 3
#ifndef BOOST_RESULT_OF_USE_TR1
 #define BOOST_RESULT_OF_USE_TR1 1
#endif
#ifndef BOOST_NO_CXX11_DECLTYPE
 #define BOOST_NO_CXX11_DECLTYPE 1
#endif
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

namespace cxxnaive {

class copy_stencil {
 private:
  template <class DataView>
  struct ParamWrapper {
    DataView dview_;
    std::array<int, DataView::storage_info_t::ndims> offsets_;

    ParamWrapper(DataView dview, std::array<int, DataView::storage_info_t::ndims> offsets)
        : dview_(dview), offsets_(offsets) {}
  };

  struct sbase {
    virtual void run() {}

    virtual ~sbase() {}
  };
  template <class StorageType0, class StorageType1>
  struct stencil_0 : public sbase {
    // //Members
    const gridtools::clang::domain& m_dom;
    StorageType0& m_in;
    StorageType1& m_out;

   public:
    stencil_0(const gridtools::clang::domain& dom_, StorageType0& in_, StorageType1& out_)
        : m_dom(dom_), m_in(in_), m_out(out_) {}

    ~stencil_0() {}

    virtual void run() {
      gridtools::data_view<StorageType0> in = gridtools::make_host_view(m_in);
      gridtools::data_view<StorageType1> out = gridtools::make_host_view(m_out);
      for (int k = 0; k <= (m_dom.ksize() == 0 ? 0 : (m_dom.ksize() - m_dom.kplus() - 1)); ++k) {
        for (int i = m_dom.iminus(); i <= m_dom.isize() - m_dom.iplus() - 1; ++i) {
          for (int j = m_dom.jminus(); j <= m_dom.jsize() - m_dom.jplus() - 1; ++j) {
            out(i + 0, j + 0, k + 0) = in(i + 0, j + 0, k + 0);
          }
        }
      }
    }
  };
  static constexpr const char* s_name = "copy_stencil";
  sbase* m_stencil_0;

 public:
  copy_stencil(const copy_stencil&) = delete;

  // Members

  template <class StorageType1, class StorageType2>
  copy_stencil(const gridtools::clang::domain& dom, StorageType1& in, StorageType2& out)
      : m_stencil_0(new stencil_0<StorageType1, StorageType2>(dom, in, out)) {}

  void run() { m_stencil_0->run(); }
};
}  // namespace cxxnaiv
;