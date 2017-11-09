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

#ifndef GTCLANG_SUPPORT_STRINGUTIL
#define GTCLANG_SUPPORT_STRINGUTIL

#include <string>
#include <vector>

namespace gtclang {

/// @brief Split a string over multiple lines
///
/// A new-line character will be inserted every `lineSize` characters. The new-line character
/// will be placed at the nearest whitespace position such that no word will be split. Every line
/// will be indented by `indentSize`.
///
/// @param str                String to split
/// @param lineSize           Size of a line (usallly terminal size)
/// @param indentSize         Each line will be indented by indentSize
/// @param indentFirstLine    Indent the first line aswell?
///
/// @ingroup support
extern std::string splitString(const std::string& str, std::size_t lineSize,
                               std::size_t indentSize = 0, bool indentFirstLine = true);

/// @brief Tokenize a string given the separation character @c delim
///
/// The tokens will be stored in a vector of strings while the original delimiter characters will be
/// dropped.
///
/// @param str       String to tokenize
/// @param delim     Delimiter character(s)
///
/// @ingroup support
extern std::vector<std::string> tokenizeString(const std::string& str, std::string delim);

/// @brief Replace the extension of a filename (if found) @param str by a new extention
///
/// @param str       Filename to replace
/// @param extension new extension to insert into the filename
///
/// @ingroup support
extern std::string replaceFilenameExt(const std::string& str, const std::string& extension);

/// @brief Return a deep copy of the string
/// @ingroup support
extern const char* copyCString(const std::string& str);

} // namespace gtclang

#endif
