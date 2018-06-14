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

#include <string>

#include "clang/AST/ASTFwd.h"

namespace gtclang {

/// @brief Retrieve a class name for a given cxx construct expr
///
/// @param expr               clang construct expr
///
/// @ingroup support
extern std::string getClassNameFromConstructExpr(clang::CXXConstructExpr* expr);

}