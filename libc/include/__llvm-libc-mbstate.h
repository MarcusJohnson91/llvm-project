//===-- Common definitions for LLVM-libc public header files --------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIBC___MBSTATE_H
#define LLVM_LIBC___MBSTATE_H

#if !defined(_MBSTATE_T)
#define _MBSTATE_T

typedef enum __Llvm_libc_mbstate_values {
  UTF_InvalidState = 0,
  UTF16_SurrogateOne = 1,
  UTF16_SurrogateTwo = 2,
  UTF8_CodeUnitOne = 3,
  UTF8_CodeUnitTwo = 4,
  UTF8_CodeUnitThree = 5,
  UTF8_CodeUnitFour = 6,
} __Llvm_libc_mbstate_values;

typedef struct __Llvm_libc_mbstate_t {
  uint32_t Character;
  mbstate_values CurrentState;
} __Llvm_libc_mbstate_t;

#endif

#endif // LLVM_LIBC___MBSTATE_H
