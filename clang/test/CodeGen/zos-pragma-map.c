// REQUIRES: systemz-registered-target
// RUN: %clang_cc1 %s -emit-llvm -fzos-extensions -triple s390x-none-zos -o - | FileCheck %s

// #pragma map(ident, "extname") gives ident the exact external name extname,
// like an asm label. Both pragma-before-declaration and pragma-after-
// declaration orders are honored, for functions and for data, matching
// ibm-clang. The external name string is used verbatim (the "@@..." form is
// how the system headers name the Enhanced-ASCII libc entry points).

#pragma map(before_decl, "BEFORE")
int before_decl(int);

int after_decl(int);
#pragma map(after_decl, "@@A00118")

extern int data_obj;
#pragma map(data_obj, "DOBJ")

int use(int x) { return before_decl(x) + after_decl(x) + data_obj; }

// CHECK-DAG: @DOBJ = external global i32
// CHECK-DAG: declare {{.*}}i32 @BEFORE(
// CHECK-DAG: declare {{.*}}i32 @"@@A00118"(
