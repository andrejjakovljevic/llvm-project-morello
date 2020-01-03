; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc -mtriple=i686-unknown-linux-gnu < %s | FileCheck %s --check-prefixes=CHECK,X86
; RUN: llc -mtriple=x86_64-unknown-linux-gnu < %s | FileCheck %s --check-prefixes=CHECK,X64

; Fold
;   ~(X - 1)
; To
;   - X
;
; This needs to be a backend-level fold because only by now pointers
; are just registers; in middle-end IR this can only be done via @llvm.ptrmask()
; intrinsic which is not sufficiently widely-spread yet.
;
; https://bugs.llvm.org/show_bug.cgi?id=44448

; The basic positive tests

define i32 @t0_32(i32 %alignment) nounwind {
; X86-LABEL: t0_32:
; X86:       # %bb.0:
; X86-NEXT:    xorl %eax, %eax
; X86-NEXT:    subl {{[0-9]+}}(%esp), %eax
; X86-NEXT:    retl
;
; X64-LABEL: t0_32:
; X64:       # %bb.0:
; X64-NEXT:    movl %edi, %eax
; X64-NEXT:    negl %eax
; X64-NEXT:    retq
  %mask = add i32 %alignment, -1
  %invmask = xor i32 %mask, -1
  ret i32 %invmask
}
define i64 @t1_64(i64 %alignment) nounwind {
; X86-LABEL: t1_64:
; X86:       # %bb.0:
; X86-NEXT:    xorl %edx, %edx
; X86-NEXT:    xorl %eax, %eax
; X86-NEXT:    subl {{[0-9]+}}(%esp), %eax
; X86-NEXT:    sbbl {{[0-9]+}}(%esp), %edx
; X86-NEXT:    retl
;
; X64-LABEL: t1_64:
; X64:       # %bb.0:
; X64-NEXT:    movq %rdi, %rax
; X64-NEXT:    negq %rax
; X64-NEXT:    retq
  %mask = add i64 %alignment, -1
  %invmask = xor i64 %mask, -1
  ret i64 %invmask
}

; Extra use test

define i32 @t2_extrause(i32 %alignment, i32* %mask_storage) nounwind {
; X86-LABEL: t2_extrause:
; X86:       # %bb.0:
; X86-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %eax
; X86-NEXT:    leal -1(%eax), %edx
; X86-NEXT:    movl %edx, (%ecx)
; X86-NEXT:    negl %eax
; X86-NEXT:    retl
;
; X64-LABEL: t2_extrause:
; X64:       # %bb.0:
; X64-NEXT:    movl %edi, %eax
; X64-NEXT:    leal -1(%rax), %ecx
; X64-NEXT:    movl %ecx, (%rsi)
; X64-NEXT:    negl %eax
; X64-NEXT:    # kill: def $eax killed $eax killed $rax
; X64-NEXT:    retq
  %mask = add i32 %alignment, -1
  store i32 %mask, i32* %mask_storage
  %invmask = xor i32 %mask, -1
  ret i32 %invmask
}

; Negative tests

define i32 @n3_not_dec(i32 %alignment) nounwind {
; X86-LABEL: n3_not_dec:
; X86:       # %bb.0:
; X86-NEXT:    movl {{[0-9]+}}(%esp), %eax
; X86-NEXT:    incl %eax
; X86-NEXT:    notl %eax
; X86-NEXT:    retl
;
; X64-LABEL: n3_not_dec:
; X64:       # %bb.0:
; X64-NEXT:    # kill: def $edi killed $edi def $rdi
; X64-NEXT:    leal 1(%rdi), %eax
; X64-NEXT:    notl %eax
; X64-NEXT:    retq
  %mask = add i32 %alignment, 1 ; not -1
  %invmask = xor i32 %mask, -1
  ret i32 %invmask
}

define i32 @n4_not_not(i32 %alignment) nounwind {
; X86-LABEL: n4_not_not:
; X86:       # %bb.0:
; X86-NEXT:    movl {{[0-9]+}}(%esp), %eax
; X86-NEXT:    decl %eax
; X86-NEXT:    xorl $1, %eax
; X86-NEXT:    retl
;
; X64-LABEL: n4_not_not:
; X64:       # %bb.0:
; X64-NEXT:    # kill: def $edi killed $edi def $rdi
; X64-NEXT:    leal -1(%rdi), %eax
; X64-NEXT:    xorl $1, %eax
; X64-NEXT:    retq
  %mask = add i32 %alignment, -1
  %invmask = xor i32 %mask, 1 ; not -1
  ret i32 %invmask
}
