// RUN: %clang_cc1 -w -fdump-record-layouts-simple %s > %t.layouts
// RUN: %clang_cc1 -w -fdump-record-layouts-simple %s > %t.before
// RUN: %clang_cc1 -w -DPACKED= -DALIGNED16= -fdump-record-layouts-simple -foverride-record-layout=%t.layouts %s > %t.after
// XXXAR: for some reason the order of the record dump is not the same , let's check that they contain the same lines
// RUN: sort %t.before > %t.before.sorted
// RUN: sort %t.after > %t.after.sorted
// RUN: diff -u %t.before.sorted %t.after.sorted
// RUN: diff -u %t.before %t.after
// RUN: FileCheck %s < %t.after

// If not explicitly disabled, set PACKED to the packed attribute.
#ifndef PACKED
#  define PACKED __attribute__((packed))
#endif

struct Empty1 { };
struct Empty2 { };

// CHECK: Type: struct X0
struct X0 : public Empty1 { 
  int x[6] PACKED; 
};

// CHECK: Type: struct X1
struct X1 : public X0, public Empty2 { 
  char x[13]; 
  struct X0 y; 
} PACKED;

// CHECK: Type: struct X2
struct PACKED X2 :  public X1, public X0, public Empty1 {
  short x;
  int y;
};

// CHECK: Type: struct X3
struct PACKED X3 : virtual public X1, public X0 {
  short x;
  int y;
};

// CHECK: Type: struct X4
struct PACKED X4 {
  unsigned int a : 1;
  unsigned int b : 1;
  unsigned int c : 1;
  unsigned int d : 1;
  unsigned int e : 1;
  unsigned int f : 1;
  unsigned int g : 1;
  unsigned int h : 1;
  unsigned int i : 1;
  unsigned int j : 1;
  unsigned int k : 1;
  unsigned int l : 1;
  unsigned int m : 1;
  unsigned int n : 1;
  X4();
};

// CHECK: Type: struct X5
struct PACKED X5 {
  union {
    long a;
    long b;
  };
  short l;
  short r;
};

void use_structs() {
  X0 x0s[sizeof(X0)];
  X1 x1s[sizeof(X1)];
  X2 x2s[sizeof(X2)];
  X3 x3s[sizeof(X3)];
  X4 x4s[sizeof(X4)];
  X5 x5s[sizeof(X5)];
  x4s[1].a = 1;
  x5s[1].a = 17;
}

