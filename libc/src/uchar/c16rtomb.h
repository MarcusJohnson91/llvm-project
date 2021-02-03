//===--------------- Implementation header for c16rtomb -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===--------------------------------------------------------------------===//

#ifndef LLVM_LIBC_SRC_UCHAR_C16RTOMB_H
#define LLVM_LIBC_SRC_UCHAR_C16RTOMB_H

namespace __llvm_libc {

size_t c16rtomb(char *restrict s, char16_t c16, mbstate_t *restrict ps);

} // namespace __llvm_libc

#endif // LLVM_LIBC_SRC_UCHAR_C16RTOMB_H
