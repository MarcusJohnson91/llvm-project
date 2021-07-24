/* RUN: %clang_cc1 -fsyntax-only -verify -triple i386-apple-darwin9 -Wformat-non-iso -std=c89 %s
 */

int printf(const char *restrict, ...);
int scanf(const char *restrict, ...);
int wprintf(const wchar_t *restrict, ...);
int wscanf(const wchar_t *restrict, ...);

void foo(char **sp, float *fp, int *ip) {
  scanf("%as", sp); /* expected-warning{{'a' length modifier is not supported by ISO C}} */
  scanf("%a[abc]", sp); /* expected-warning{{'a' length modifier is not supported by ISO C}} */
  wscanf(L"%as", sp);   /* expected-warning{{'a' length modifier is not supported by ISO C}} */
  wscanf(L"%a[abc]", sp); /* expected-warning{{'a' length modifier is not supported by ISO C}} */

  /* TODO: Warn that the 'a' conversion specifier is a C99 feature. */
  scanf("%a", fp);
  scanf("%afoobar", fp);
  printf("%a", 1.0);
  printf("%as", 1.0);
  printf("%aS", 1.0);
  printf("%a[", 1.0);
  printf("%afoo", 1.0);

  wscanf(L"%a", fp);
  wscanf(L"%afoobar", fp);
  wprintf(L"%a", 1.0);
  wprintf(L"%as", 1.0);
  wprintf(L"%aS", 1.0);
  wprintf(L"%a[", 1.0);
  wprintf(L"%afoo", 1.0);

  scanf("%da", ip);

  wscanf("%da", ip);

  /* Test argument type check for the 'a' length modifier. */
  scanf("%as", fp); /* expected-warning{{format specifies type 'char **' but the argument has type 'float *'}}
                       expected-warning{{'a' length modifier is not supported by ISO C}} */
  scanf("%aS", fp); /* expected-warning{{format specifies type 'wchar_t **' (aka 'int **') but the argument has type 'float *'}}
                       expected-warning{{'a' length modifier is not supported by ISO C}}
                       expected-warning{{'S' conversion specifier is not supported by ISO C}} */
  scanf("%a[abc]", fp); /* expected-warning{{format specifies type 'char **' but the argument has type 'float *'}}
                           expected-warning{{'a' length modifier is not supported by ISO C}} */

  wscanf(L"%as", fp);     /* expected-warning{{format specifies type 'char **' but the argument has type 'float *'}}
                           expected-warning{{'a' length modifier is not supported by ISO C}} */
  wscanf(L"%aS", fp);     /* expected-warning{{format specifies type 'wchar_t **' (aka 'int **') but the argument has type 'float *'}}
                           expected-warning{{'a' length modifier is not supported by ISO C}}
                           expected-warning{{'S' conversion specifier is not supported by ISO C}} */
  wscanf(L"%a[abc]", fp); /* expected-warning{{format specifies type 'char **' but the argument has type 'float *'}}
                           expected-warning{{'a' length modifier is not supported by ISO C}} */
}
