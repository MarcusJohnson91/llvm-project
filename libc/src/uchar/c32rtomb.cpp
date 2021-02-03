//===-------------------- Implementation of c32rtomb ----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "src/uchar/c32rtomb.h"

#include "src/__support/common.h"

namespace __llvm_libc {

size_t LLVM_LIBC_ENTRYPOINT(c32rtomb)(char *restrict s, char32_t c32,
                                      mbstate_t *restrict ps) {
  size_t StringSize = 0;
  if (c32 <= 0x7F) {
    StringSize = 1;
    s[0] = c32 & 0x7F;
  } else if (c32 <= 0x7FF) {
    StringSize = 2;
    s[0] = 0xC0 | (c32 & ((0x1F << 6) >> 6));
    s[1] = 0x80 | (c32 & 0x3F);
  } else if (c32 <= 0xFFFF) {
    StringSize = 3;
    s[0] = 0xE0 | (c32 & ((0x0F << 12) >> 12));
    s[1] = 0x80 | (c32 & ((0x3F << 6) >> 6));
    s[2] = 0x80 | (c32 & 0x3F);
  } else if (c32 <= 0x10FFFF) {
    StringSize = 4;
    s[0] = 0xF0 | (c32 & 0x1C0000) >> 18;
    s[1] = 0x80 | (c32 & 0x3F000) >> 12;
    s[2] = 0x80 | (c32 & 0xFC0) >> 6;
    s[3] = 0x80 | (c32 & 0x3F);
  }
  return StringSize;
}

} // namespace __llvm_libc
