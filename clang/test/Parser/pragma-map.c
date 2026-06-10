// RUN: %clang_cc1 -triple s390x-ibm-zos -fsyntax-only -verify %s

int ok1(int);
#pragma map(ok1, "OK1")

#pragma map(ok1, "OK" "1")  /* concatenated string literals are allowed */

int ok2(int);
#pragma map ok2, "OK2")   // expected-warning {{missing '(' after '#pragma map' - ignoring}}
#pragma map(, "OK2")      // expected-warning {{expected identifier in '#pragma map' - ignored}}
#pragma map(ok2 "OK2")    // expected-warning {{expected ',' in '#pragma map'}}
#pragma map(ok2, OK2)     // expected-warning {{expected string literal in '#pragma map' - ignoring}}
#pragma map(ok2, "OK2"    // expected-warning {{missing ')' after '#pragma map' - ignoring}}
#pragma map(ok2, "OK2") x // expected-warning {{extra tokens at end of '#pragma map' - ignored}}
