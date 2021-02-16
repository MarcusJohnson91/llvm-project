//===----- FormatStringParsing.h - Format String Parsing --------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This provides some shared functions between printf and scanf format string
// parsing code.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_LIB_ANALYSIS_FORMATSTRINGPARSING_H
#define LLVM_CLANG_LIB_ANALYSIS_FORMATSTRINGPARSING_H

#include "clang/AST/ASTContext.h"
#include "clang/AST/Type.h"
#include "clang/AST/FormatString.h"

namespace clang {

class LangOptions;

template <typename T>
class UpdateOnReturn {
  T &ValueToUpdate;
  const T &ValueToCopy;
public:
  UpdateOnReturn(T &valueToUpdate, const T &valueToCopy)
    : ValueToUpdate(valueToUpdate), ValueToCopy(valueToCopy) {}

  ~UpdateOnReturn() {
    ValueToUpdate = ValueToCopy;
  }
};

namespace analyze_format_string {

OptionalAmount ParseAmount(FormatStringLiteral &FSL, const unsigned Beg, const unsigned End);
OptionalAmount ParseNonPositionAmount(FormatStringLiteral &FSL, const unsigned Beg, const unsigned End,
                                      unsigned &argIndex);

OptionalAmount ParsePositionAmount(FormatStringHandler &H, FormatStringLiteral &FSL,
                                   const unsigned Start, const unsigned Beg,
                                   const unsigned End, PositionContext p);

bool ParseFieldWidth(FormatStringHandler &H,
                     FormatSpecifier &CS,
                     const unsigned Start, const unsigned Beg, const unsigned End,
                     unsigned *argIndex);

bool ParseArgPosition(FormatStringHandler &H,
                      FormatSpecifier &CS, const unsigned Start,
                      const unsigned Beg, const unsigned End);

bool ParseVectorModifier(FormatStringHandler &H,
                         FormatSpecifier &FS, const unsigned Beg, const unsigned End,
                         const LangOptions &LO);

/// Returns true if a LengthModifier was parsed and installed in the
/// FormatSpecifier& argument, and false otherwise.
bool ParseLengthModifier(FormatSpecifier &FS, const unsigned Beg, const unsigned End,
                         const LangOptions &LO, bool IsScanf = false);

/// Returns true if the invalid specifier in \p SpecifierBegin is a UTF-8
/// string; check that it won't go further than \p FmtStrEnd and write
/// up the total size in \p Len.
bool ParseUTF8InvalidSpecifier(const unsigned SpecifierBegin,
                               const unsigned FmtStrEnd, unsigned &Len);

template <typename T> class SpecifierResult {
  T FS;
  const unsigned Start;
  bool Stop;
public:
  SpecifierResult(bool stop = false)
  : Start(0), Stop(stop) {}
  SpecifierResult(const unsigned start,
                  const T &fs)
  : FS(fs), Start(start), Stop(false) {}

  unsigned getStart() const { return Start; }
  bool shouldStop() const { return Stop; }
  bool hasValue() const { return Start != 0; }
  const T &getValue() const {
    assert(hasValue());
    return FS;
  }
  const T &getValue() { return FS; }
};

} // end analyze_format_string namespace
} // end clang namespace

#endif
