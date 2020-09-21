; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc -fast-isel-sink-local-values -O0 -mtriple=x86_64-unknown-linux-gnu -o - %s | FileCheck %s -check-prefix=X640
; RUN: llc -fast-isel-sink-local-values -O0 -mtriple=i686-unknown             -o - %s | FileCheck %s -check-prefix=6860
; RUN: llc -fast-isel-sink-local-values     -mtriple=x86_64-unknown-linux-gnu -o - %s | FileCheck %s -check-prefix=X64
; RUN: llc -fast-isel-sink-local-values     -mtriple=i686-unknown             -o - %s | FileCheck %s -check-prefix=686

@var_22 = external global i16, align 2
@var_27 = external global i16, align 2

define void @foo() {
; X640-LABEL: foo:
; X640:       # %bb.0: # %bb
; X640-NEXT:    movzwl var_22, %eax
; X640-NEXT:    movzwl var_27, %ecx
; X640-NEXT:    xorl %ecx, %eax
; X640-NEXT:    movzwl var_27, %ecx
; X640-NEXT:    xorl %ecx, %eax
; X640-NEXT:    cltq
; X640-NEXT:    movq %rax, -{{[0-9]+}}(%rsp)
; X640-NEXT:    movzwl var_22, %eax
; X640-NEXT:    movzwl var_27, %ecx
; X640-NEXT:    xorl %ecx, %eax
; X640-NEXT:    movzwl var_27, %ecx
; X640-NEXT:    xorl %ecx, %eax
; X640-NEXT:    cltq
; X640-NEXT:    movzwl var_27, %ecx
; X640-NEXT:    subl $16610, %ecx # imm = 0x40E2
; X640-NEXT:    movl %ecx, %ecx
; X640-NEXT:    # kill: def $rcx killed $ecx
; X640-NEXT:    # kill: def $cl killed $rcx
; X640-NEXT:    sarq %cl, %rax
; X640-NEXT:    movb %al, %cl
; X640-NEXT:    # implicit-def: $rax
; X640-NEXT:    movb %cl, (%rax)
; X640-NEXT:    retq
;
; 6860-LABEL: foo:
; 6860:       # %bb.0: # %bb
; 6860-NEXT:    pushl %ebp
; 6860-NEXT:    .cfi_def_cfa_offset 8
; 6860-NEXT:    .cfi_offset %ebp, -8
; 6860-NEXT:    movl %esp, %ebp
; 6860-NEXT:    .cfi_def_cfa_register %ebp
; 6860-NEXT:    andl $-8, %esp
; 6860-NEXT:    subl $24, %esp
; 6860-NEXT:    movw var_22, %dx
; 6860-NEXT:    movzwl var_27, %ecx
; 6860-NEXT:    movw %cx, %ax
; 6860-NEXT:    xorw %ax, %dx
; 6860-NEXT:    # implicit-def: $eax
; 6860-NEXT:    movw %dx, %ax
; 6860-NEXT:    xorl %ecx, %eax
; 6860-NEXT:    # kill: def $ax killed $ax killed $eax
; 6860-NEXT:    movzwl %ax, %eax
; 6860-NEXT:    movl %eax, {{[0-9]+}}(%esp)
; 6860-NEXT:    movl $0, {{[0-9]+}}(%esp)
; 6860-NEXT:    movw var_22, %dx
; 6860-NEXT:    movzwl var_27, %eax
; 6860-NEXT:    movw %ax, %cx
; 6860-NEXT:    xorw %cx, %dx
; 6860-NEXT:    # implicit-def: $ecx
; 6860-NEXT:    movw %dx, %cx
; 6860-NEXT:    xorl %eax, %ecx
; 6860-NEXT:    # kill: def $cx killed $cx killed $ecx
; 6860-NEXT:    movzwl %cx, %edx
; 6860-NEXT:    movb %al, %cl
; 6860-NEXT:    addb $30, %cl
; 6860-NEXT:    movb %cl, {{[-0-9]+}}(%e{{[sb]}}p) # 1-byte Spill
; 6860-NEXT:    xorl %eax, %eax
; 6860-NEXT:    shrdl %cl, %eax, %edx
; 6860-NEXT:    movb {{[-0-9]+}}(%e{{[sb]}}p), %cl # 1-byte Reload
; 6860-NEXT:    movl %edx, {{[-0-9]+}}(%e{{[sb]}}p) # 4-byte Spill
; 6860-NEXT:    testb $32, %cl
; 6860-NEXT:    movl %eax, {{[-0-9]+}}(%e{{[sb]}}p) # 4-byte Spill
; 6860-NEXT:    jne .LBB0_2
; 6860-NEXT:  # %bb.1: # %bb
; 6860-NEXT:    movl {{[-0-9]+}}(%e{{[sb]}}p), %eax # 4-byte Reload
; 6860-NEXT:    movl %eax, {{[-0-9]+}}(%e{{[sb]}}p) # 4-byte Spill
; 6860-NEXT:  .LBB0_2: # %bb
; 6860-NEXT:    movl {{[-0-9]+}}(%e{{[sb]}}p), %eax # 4-byte Reload
; 6860-NEXT:    movb %al, %cl
; 6860-NEXT:    # implicit-def: $eax
; 6860-NEXT:    movb %cl, (%eax)
; 6860-NEXT:    movl %ebp, %esp
; 6860-NEXT:    popl %ebp
; 6860-NEXT:    .cfi_def_cfa %esp, 4
; 6860-NEXT:    retl
;
; X64-LABEL: foo:
; X64:       # %bb.0: # %bb
; X64-NEXT:    movzwl {{.*}}(%rip), %ecx
; X64-NEXT:    movzwl {{.*}}(%rip), %eax
; X64-NEXT:    xorw %cx, %ax
; X64-NEXT:    xorl %ecx, %eax
; X64-NEXT:    movzwl %ax, %eax
; X64-NEXT:    movq %rax, -{{[0-9]+}}(%rsp)
; X64-NEXT:    addb $30, %cl
; X64-NEXT:    # kill: def $cl killed $cl killed $ecx
; X64-NEXT:    shrq %cl, %rax
; X64-NEXT:    movb %al, (%rax)
; X64-NEXT:    retq
;
; 686-LABEL: foo:
; 686:       # %bb.0: # %bb
; 686-NEXT:    pushl %ebp
; 686-NEXT:    .cfi_def_cfa_offset 8
; 686-NEXT:    .cfi_offset %ebp, -8
; 686-NEXT:    movl %esp, %ebp
; 686-NEXT:    .cfi_def_cfa_register %ebp
; 686-NEXT:    andl $-8, %esp
; 686-NEXT:    subl $8, %esp
; 686-NEXT:    movzwl var_27, %ecx
; 686-NEXT:    movzwl var_22, %eax
; 686-NEXT:    xorw %cx, %ax
; 686-NEXT:    xorl %ecx, %eax
; 686-NEXT:    movzwl %ax, %eax
; 686-NEXT:    movl %eax, (%esp)
; 686-NEXT:    movl $0, {{[0-9]+}}(%esp)
; 686-NEXT:    addb $30, %cl
; 686-NEXT:    xorl %edx, %edx
; 686-NEXT:    shrdl %cl, %edx, %eax
; 686-NEXT:    testb $32, %cl
; 686-NEXT:    jne .LBB0_2
; 686-NEXT:  # %bb.1: # %bb
; 686-NEXT:    movl %eax, %edx
; 686-NEXT:  .LBB0_2: # %bb
; 686-NEXT:    movb %dl, (%eax)
; 686-NEXT:    movl %ebp, %esp
; 686-NEXT:    popl %ebp
; 686-NEXT:    .cfi_def_cfa %esp, 4
; 686-NEXT:    retl
bb:
  %tmp = alloca i64, align 8
  %tmp1 = load i16, i16* @var_22, align 2
  %tmp2 = zext i16 %tmp1 to i32
  %tmp3 = load i16, i16* @var_27, align 2
  %tmp4 = zext i16 %tmp3 to i32
  %tmp5 = xor i32 %tmp2, %tmp4
  %tmp6 = load i16, i16* @var_27, align 2
  %tmp7 = zext i16 %tmp6 to i32
  %tmp8 = xor i32 %tmp5, %tmp7
  %tmp9 = sext i32 %tmp8 to i64
  store i64 %tmp9, i64* %tmp, align 8
  %tmp10 = load i16, i16* @var_22, align 2
  %tmp11 = zext i16 %tmp10 to i32
  %tmp12 = load i16, i16* @var_27, align 2
  %tmp13 = zext i16 %tmp12 to i32
  %tmp14 = xor i32 %tmp11, %tmp13
  %tmp15 = load i16, i16* @var_27, align 2
  %tmp16 = zext i16 %tmp15 to i32
  %tmp17 = xor i32 %tmp14, %tmp16
  %tmp18 = sext i32 %tmp17 to i64
  %tmp19 = load i16, i16* @var_27, align 2
  %tmp20 = zext i16 %tmp19 to i32
  %tmp21 = sub nsw i32 %tmp20, 16610
  %tmp22 = zext i32 %tmp21 to i64
  %tmp23 = ashr i64 %tmp18, %tmp22
  %tmp24 = trunc i64 %tmp23 to i8
  store i8 %tmp24, i8* undef, align 1
  ret void
}
