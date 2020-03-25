; NOTE: Assertions have been autogenerated by utils/update_test_checks.py
; RUN: opt -S -codegenprepare < %s | FileCheck %s

target triple = "x86_64-unknown-linux-gnu"

define void @f1(i32 %a) {
; CHECK-LABEL: @f1(
; CHECK-NEXT:    [[FR:%.*]] = freeze i32 [[A:%.*]]
; CHECK-NEXT:    [[C:%.*]] = icmp eq i32 [[FR]], 0
; CHECK-NEXT:    br i1 [[C]], label [[A:%.*]], label [[B:%.*]]
; CHECK:       A:
; CHECK-NEXT:    call void @g1()
; CHECK-NEXT:    ret void
; CHECK:       B:
; CHECK-NEXT:    call void @g2()
; CHECK-NEXT:    ret void
;
  %c = icmp eq i32 %a, 0
  %fr = freeze i1 %c
  br i1 %fr, label %A, label %B
A:
  call void @g1()
  ret void
B:
  call void @g2()
  ret void
}

define void @f2(i32 %a) {
; CHECK-LABEL: @f2(
; CHECK-NEXT:    [[FR:%.*]] = freeze i32 [[A:%.*]]
; CHECK-NEXT:    [[C:%.*]] = icmp eq i32 0, [[FR]]
; CHECK-NEXT:    br i1 [[C]], label [[A:%.*]], label [[B:%.*]]
; CHECK:       A:
; CHECK-NEXT:    call void @g1()
; CHECK-NEXT:    ret void
; CHECK:       B:
; CHECK-NEXT:    call void @g2()
; CHECK-NEXT:    ret void
;
  %c = icmp eq i32 0, %a
  %fr = freeze i1 %c
  br i1 %fr, label %A, label %B
A:
  call void @g1()
  ret void
B:
  call void @g2()
  ret void
}

define void @f3(i32 %a) {
; CHECK-LABEL: @f3(
; CHECK-NEXT:    [[C:%.*]] = icmp eq i32 0, 1
; CHECK-NEXT:    br i1 [[C]], label [[A:%.*]], label [[B:%.*]]
; CHECK:       A:
; CHECK-NEXT:    call void @g1()
; CHECK-NEXT:    ret void
; CHECK:       B:
; CHECK-NEXT:    call void @g2()
; CHECK-NEXT:    ret void
;
  %c = icmp eq i32 0, 1
  %fr = freeze i1 %c
  br i1 %fr, label %A, label %B
A:
  call void @g1()
  ret void
B:
  call void @g2()
  ret void
}

define i1 @ptrcmp(i8* %p) {
; CHECK-LABEL: @ptrcmp(
; CHECK-NEXT:    [[FR:%.*]] = freeze i8* [[P:%.*]]
; CHECK-NEXT:    [[C:%.*]] = icmp eq i8* [[FR]], null
; CHECK-NEXT:    ret i1 [[C]]
;
  %c = icmp eq i8* %p, null
  %fr = freeze i1 %c
  ret i1 %fr
}


define i1 @fcmp(float %a) {
; CHECK-LABEL: @fcmp(
; CHECK-NEXT:    [[FR:%.*]] = freeze float [[A:%.*]]
; CHECK-NEXT:    [[C:%.*]] = fcmp oeq float [[FR]], 0.000000e+00
; CHECK-NEXT:    ret i1 [[C]]
;
  %c = fcmp oeq float %a, 0.0
  %fr = freeze i1 %c
  ret i1 %fr
}

define i1 @fcmp_nan(float %a) {
; CHECK-LABEL: @fcmp_nan(
; CHECK-NEXT:    [[C:%.*]] = fcmp nnan oeq float [[A:%.*]], 0.000000e+00
; CHECK-NEXT:    [[FR:%.*]] = freeze i1 [[C]]
; CHECK-NEXT:    ret i1 [[FR]]
;
  %c = fcmp nnan oeq float %a, 0.0
  %fr = freeze i1 %c
  ret i1 %fr
}

define void @and(i32 %flag) {
; CHECK-LABEL: @and(
; CHECK-NEXT:    [[V:%.*]] = and i32 [[FLAG:%.*]], 1
; CHECK-NEXT:    [[FR:%.*]] = freeze i32 [[V]]
; CHECK-NEXT:    [[C:%.*]] = icmp eq i32 [[FR]], 0
; CHECK-NEXT:    br i1 [[C]], label [[A:%.*]], label [[B:%.*]]
; CHECK:       A:
; CHECK-NEXT:    call void @g1()
; CHECK-NEXT:    ret void
; CHECK:       B:
; CHECK-NEXT:    call void @g2()
; CHECK-NEXT:    ret void
;
  %v = and i32 %flag, 1
  %c = icmp eq i32 %v, 0
  %fr = freeze i1 %c
  br i1 %fr, label %A, label %B
A:
  call void @g1()
  ret void
B:
  call void @g2()
  ret void
}


declare void @g1()
declare void @g2()
