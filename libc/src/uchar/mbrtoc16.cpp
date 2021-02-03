//===-------------------- Implementation of mbrtoc16 ----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "src/uchar/mbrtoc16.h"

#include "src/__support/common.h"

namespace __llvm_libc {

size_t LLVM_LIBC_ENTRYPOINT(mbrtoc16)(char16_t *restrict pc16,
                                      const char *restrict s, size_t n,
                                      mbstate_t *restrict ps) {

  // utf-8 to utf-16

  // first check bit 1 and 1 and 2 to see if theyre leading or trailing bytes

  if (ps == 0) {
    if ((s & 0x80) == 0) {
      // ASCII
    } else if ((s & 0x80) ==) {
    }
  } else {
  }

  size_t StringSize = 0;
  char32_t Decoded = 0;

  switch (n) {
  case 1:
    Decoded = s[0] & 0x7F;
    break;
  case 2:
    Decoded |= (s[0] & 0x1F) << 6;
    Decoded |= (s[1] & 0x3F) << 0;
    break;
  case 3:
    Decoded |= (s[0] & 0x0F) << 12;
    Decoded |= (s[1] & 0x1F) << 6;
    Decoded |= (s[2] & 0x1F) << 0;
    break;
  case 4:
    Decoded |= (s[0] & 0x07) << 18;
    Decoded |= (s[1] & 0x3F) << 12;
    Decoded |= (s[2] & 0x3F) << 6;
    Decoded |= (s[3] & 0x3F) << 0;
    break;
  }

  if (Decoded <= 0xFFFF) {
    StringSize = 1;
    pc16[0] = Decoded & 0xFFFF;
  } else if (Decoded <= 0x10FFFF) {
    StringSize = 2;
    pc16[0] = 0xD800 + ((Decoded & 0xFFC00) >> 10);
    pc16[1] = 0xDC00 + (Decoded & 0x3FF);
  }
  return StringSize;
}

} // namespace __llvm_libc
