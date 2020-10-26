; NOTE: Assertions have been autogenerated by utils/update_analyze_test_checks.py
; RUN: opt -analyze -cost-model -cost-kind=code-size %s -S -o - | FileCheck %s --check-prefix=CHECK-SIZE
; RUN: opt -analyze -cost-model -cost-kind=throughput %s -S -o - | FileCheck %s --check-prefix=CHECK-THROUGHPUT

target datalayout = "e-m:e-i8:8:32-i16:16:32-i64:64-i128:128-n32:64-S128"

define i32 @trivially_free() {
; CHECK-SIZE-LABEL: 'trivially_free'
; CHECK-SIZE-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: %a0 = call i32 @llvm.annotation.i32.p0i8(i32 undef, i8* undef, i8* undef, i32 undef)
; CHECK-SIZE-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: call void @llvm.assume(i1 undef)
; CHECK-SIZE-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: call void @llvm.sideeffect()
; CHECK-SIZE-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: %a1 = call {}* @llvm.invariant.start.p0i8(i64 1, i8* undef)
; CHECK-SIZE-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: call void @llvm.invariant.end.p0i8({}* undef, i64 1, i8* undef)
; CHECK-SIZE-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: %a2 = call i8* @llvm.launder.invariant.group.p0i8(i8* undef)
; CHECK-SIZE-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: %a3 = call i8* @llvm.strip.invariant.group.p0i8(i8* undef)
; CHECK-SIZE-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: %a4 = call i1 @llvm.is.constant.i32(i32 undef)
; CHECK-SIZE-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: call void @llvm.lifetime.start.p0i8(i64 1, i8* undef)
; CHECK-SIZE-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: call void @llvm.lifetime.end.p0i8(i64 1, i8* undef)
; CHECK-SIZE-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: %a5 = call i64 @llvm.objectsize.i64.p0i8(i8* undef, i1 true, i1 true, i1 true)
; CHECK-SIZE-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: %a6 = call i8* @llvm.ptr.annotation.p0i8.p0i8(i8* undef, i8* undef, i8* undef, i32 undef, i8* undef)
; CHECK-SIZE-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: call void @llvm.var.annotation.p0i8(i8* undef, i8* undef, i8* undef, i32 undef, i8* undef)
; CHECK-SIZE-NEXT:  Cost Model: Found an estimated cost of 1 for instruction: ret i32 undef
;
; CHECK-THROUGHPUT-LABEL: 'trivially_free'
; CHECK-THROUGHPUT-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: %a0 = call i32 @llvm.annotation.i32.p0i8(i32 undef, i8* undef, i8* undef, i32 undef)
; CHECK-THROUGHPUT-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: call void @llvm.assume(i1 undef)
; CHECK-THROUGHPUT-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: call void @llvm.sideeffect()
; CHECK-THROUGHPUT-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: %a1 = call {}* @llvm.invariant.start.p0i8(i64 1, i8* undef)
; CHECK-THROUGHPUT-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: call void @llvm.invariant.end.p0i8({}* undef, i64 1, i8* undef)
; CHECK-THROUGHPUT-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: %a2 = call i8* @llvm.launder.invariant.group.p0i8(i8* undef)
; CHECK-THROUGHPUT-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: %a3 = call i8* @llvm.strip.invariant.group.p0i8(i8* undef)
; CHECK-THROUGHPUT-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: %a4 = call i1 @llvm.is.constant.i32(i32 undef)
; CHECK-THROUGHPUT-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: call void @llvm.lifetime.start.p0i8(i64 1, i8* undef)
; CHECK-THROUGHPUT-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: call void @llvm.lifetime.end.p0i8(i64 1, i8* undef)
; CHECK-THROUGHPUT-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: %a5 = call i64 @llvm.objectsize.i64.p0i8(i8* undef, i1 true, i1 true, i1 true)
; CHECK-THROUGHPUT-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: %a6 = call i8* @llvm.ptr.annotation.p0i8.p0i8(i8* undef, i8* undef, i8* undef, i32 undef, i8* undef)
; CHECK-THROUGHPUT-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: call void @llvm.var.annotation.p0i8(i8* undef, i8* undef, i8* undef, i32 undef, i8* undef)
; CHECK-THROUGHPUT-NEXT:  Cost Model: Found an estimated cost of 1 for instruction: ret i32 undef
;
  %a0 = call i32 @llvm.annotation.i32(i32 undef, i8* undef, i8* undef, i32 undef)
  call void @llvm.assume(i1 undef)
  call void @llvm.sideeffect()
  call void @llvm.dbg.declare(metadata i8** undef, metadata !0, metadata !DIExpression())
  call void @llvm.dbg.value(metadata i64 undef, i64 undef, metadata !DIExpression(), metadata !DIExpression())
  call void @llvm.dbg.label(metadata !2)
  %a1 = call {}* @llvm.invariant.start.p0i8(i64 1, i8* undef)
  call void @llvm.invariant.end.p0i8({}* undef, i64 1, i8* undef)
  %a2 = call i8* @llvm.launder.invariant.group.p0i8(i8* undef)
  %a3 = call i8* @llvm.strip.invariant.group.p0i8(i8* undef)
  %a4 = call i1 @llvm.is.constant.i32(i32 undef)
  call void @llvm.lifetime.start.p0i8(i64 1, i8* undef)
  call void @llvm.lifetime.end.p0i8(i64 1, i8* undef)
  %a5 = call i64 @llvm.objectsize.i64.p0i8(i8* undef, i1 1, i1 1, i1 1)
  %a6 = call i8* @llvm.ptr.annotation.p0i8(i8* undef, i8* undef, i8* undef, i32 undef, i8* undef)
  call void @llvm.var.annotation(i8* undef, i8* undef, i8* undef, i32 undef, i8* undef)
  ret i32 undef
}

declare i32 @llvm.annotation.i32(i32, i8*, i8*, i32)
declare void @llvm.assume(i1)
declare void @llvm.sideeffect()
declare void @llvm.dbg.declare(metadata, metadata, metadata)
declare void @llvm.dbg.value(metadata, i64, metadata, metadata)
declare void @llvm.dbg.label(metadata)
declare {}* @llvm.invariant.start.p0i8(i64, i8*)
declare void @llvm.invariant.end.p0i8({}*, i64, i8*)
declare i8* @llvm.launder.invariant.group.p0i8(i8*)
declare i8* @llvm.strip.invariant.group.p0i8(i8*)
declare i1 @llvm.is.constant.i32(i32)
declare void @llvm.lifetime.start.p0i8(i64, i8*)
declare void @llvm.lifetime.end.p0i8(i64, i8*)
declare i64 @llvm.objectsize.i64.p0i8(i8*, i1, i1, i1)
declare i8* @llvm.ptr.annotation.p0i8(i8*, i8*, i8*, i32, i8*)
declare void @llvm.var.annotation(i8*, i8*, i8*, i32, i8*)


!0 = !DILocalVariable(scope: !1)
!1 = distinct !DISubprogram(name: "dummy", line: 79, isLocal: true, isDefinition: true, virtualIndex: 6, flags: DIFlagPrototyped, isOptimized: true)
!2 = !DILabel(scope: !1, name: "label", file: !3, line: 7)
!3 = !DIFile(filename: "debug-label.c", directory: "./")
