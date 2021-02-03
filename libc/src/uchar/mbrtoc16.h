//===---------------- Implementation header for mbrtoc16 -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===---------------------------------------------------------------------===//
#ifndef LLVM_LIBC_SRC_UCHAR_MBRTOC16_H
#define LLVM_LIBC_SRC_UCHAR_MBRTOC16_H

#include "include/uchar.h"

namespace __llvm_libc {

size_t mbrtoc16(char16_t *restrict pc16, const char *restrict s, size_t n,
                mbstate_t *restrict ps);

} // namespace __llvm_libc

#endif // LLVM_LIBC_SRC_UCHAR_MBRTOC16_H
