add_libc_testsuite(libc_uchar_unittests)

add_libc_unittest(
  c32rtomb_test
  SUITE
    libc_uchar_unittests
  SRCS
    c32rtomb_test.cpp
  DEPENDS
    libc.src.uchar.c32rtomb
    libc.include.uchar.c32rtomb
)

add_libc_unittest(
  c16rtomb_test
  SUITE
    libc_uchar_unittests
  SRCS
    c16rtomb_test.cpp
  DEPENDS
    libc.src.uchar.c16rtomb
    libc.include.uchar.c16rtomb
)

add_libc_unittest(
  mbrtoc32_test
  SUITE
    libc_uchar_unittests
  SRCS
    mbrtoc32_test.cpp
  DEPENDS
    libc.src.uchar.mbrtoc32
    libc.include.uchar.mbrtoc32
)

add_libc_unittest(
  mbrtoc16_test
  SUITE
    libc_uchar_unittests
  SRCS
    mbrtoc16_test.cpp
  DEPENDS
    libc.src.uchar.mbrtoc16
    libc.include.uchar.mbrtoc16
)
