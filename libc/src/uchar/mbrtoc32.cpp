//===-------------------- Implementation of mbrtoc32 ----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "src/uchar/mbrtoc32.h"

#include "src/__support/common.h"

namespace __llvm_libc {

size_t LLVM_LIBC_ENTRYPOINT(mbrtoc32)(char32_t *restrict pc32,
                                      const char *restrict s, size_t n,
                                      mbstate_t *restrict ps) {
  size_t StringSize = 1;

  switch (n) {
  case 1:
    pc32[0] = s[0] & 0x7F;
    break;
  case 2:
    pc32[0] |= (s[0] & 0x1F) << 6;
    pc32[0] |= (s[1] & 0x3F) << 0;
    break;
  case 3:
    pc32[0] |= (s[0] & 0x0F) << 12;
    pc32[0] |= (s[1] & 0x1F) << 6;
    pc32[0] |= (s[2] & 0x1F) << 0;
    break;
  case 4:
    pc32[0] |= (s[0] & 0x07) << 18;
    pc32[0] |= (s[1] & 0x3F) << 12;
    pc32[0] |= (s[2] & 0x3F) << 6;
    pc32[0] |= (s[3] & 0x3F) << 0;
    break;
  }
  return StringSize;
}

} // namespace __llvm_libc
