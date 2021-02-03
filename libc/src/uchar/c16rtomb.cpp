//===-------------------- Implementation of c16rtomb ----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "src/uchar/c16rtomb.h"
#include "../../include/wchar.h"

#include "src/__support/common.h"

namespace __llvm_libc {

enum UTF16Surrogates {
  HighSurrogateStart = 0xD800,
  HighSurrogateEnd = 0xDBFF,
  LowSurrogateStart = 0xDC00,
  LowSurrogateEnd = 0xDFFF,
  SurrogateShift = 2,
}

size_t
LLVM_LIBC_ENTRYPOINT(c16rtomb)(char *restrict s, char16_t c16,
                               mbstate_t *restrict ps) {
  // The c16rtomb function returns the number of bytes stored in the array
  // object (including any shift sequences). So, return the number of bytes used
  // after converting each CodePoint.

  // so decode this codeunit if it's a surrogate...
  /*
   🐳 = 0xD83D 0xDC33 in UTF-16; 0x1F433 in UTF-32
   So, first decode 0xD83D by taking the number 0x10000 and ORing 0x3FF then
   shifting by 10 with it to get 0x1F400


   */
  size_t NumCodeUnits = 0;
  if (c16 <= 0xFFFF &&
      (c16 <= 0xD7FF || c16 >= 0xE000)) { // not a Surrogate Pair
    // Record the state as non-Surrogate
    ps->CurrentState = NonSurrogate;
    if (c16 <= 0x7F) { // ASCII
      NumCodeUnits = 1;
      *s[0] = Value;
    } else if (c16 <= 0x7FF) {
      NumCodeUnits = 2;
      *s[0] = 0xC0 | ((c16 & 0x7C0) >> 6);
      *s[1] = 0x80 | (c16 & 0x3F);
    } else if (c16 <= 0xFFFF) {
      NumCodeUnits = 3;
      *s[0] = 0xE0 | ((c16 & 0xF800) >> 11);
      *s[1] = 0x80 | ((c16 & 0x7E0) >> 5);
      *s[2] = 0x80 | (c16 & 0x1F);
    }
  } else { // Surrogate Pair
    // Can not be ASCII, value must be at least 0x10000 after decoding, the
    // question is, how do we record the state in mbstate_t? we need to know
    // that this is a Surrogate Pair and the previous UTF-16 code unit was a
    // High or Low Surrogate,

    /*
     0x10FFFF = 0xDBFF 0xDFFF

     */
    if (c16 >= 0xD800 && c16 <= 0xDBFF) { // We have a High Surrogate
      NumCodeUnits = 3;
      ps->CurrentState = HighSurrogate;
      *s[0] = 0xF8 | ((c16 & 0x380) >> 7); // 0xF8 | 0x7  = 0xFF, FULL
      *s[1] = 0x80 | ((c16 & 0x7E) >> 1);  // 0x80 | 0x3F = 0xBF, FULL
      *s[2] = 0x80 | (c16 & 0x1);          // 0x80 | 0x01 = 0x81, 5 bits left
    } else if (c16 >= 0xDC00 &&
               c16 <= 0xDFFF) { // Low Surrogate, make sure the previous
                                // codeunit was a High Surrogate
      ps->CurrentState = LowSurrogate;
      if (ps->LastState == HighSurrogate) { // we're ok
        NumCodeUnits = 1;
        char16_t Value =
            (((*s[-1] & 0x1) << 10) | (c16 & 0x3FF)); // 0x400 | 0x3FF = 0x7FF
        *s[-1] = 0x80 | (Value & 0x7C0) >> 6;
        *s[0] = 0x80 | (Value & 0x3F);
      } else {
        // Error, Lone Low Surrogate, or out of order low surrogate before high
        // surrogate which may indicate the byte order needs to be swapped.
      }
    }
  }
  return NumCodeUnits;
}

} // namespace __llvm_libc
