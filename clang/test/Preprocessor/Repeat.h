/* RUN: %clang_cc1 -triple x86_64-unknown-unknown -pedantic -std=gnu89 -fsyntax-only -verify
 */

#define IdentifierTest Identifier#Test
#repeat 3 IdentifierTest

// expected: IdentifierTest IdentifierTest IdentifierTest

