; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc < %s -mtriple=x86_64-- -mcpu=x86-64 | FileCheck %s -check-prefix=X64
; RUN: llc < %s -mtriple=i686-unknown   | FileCheck %s -check-prefix=X86

declare float @llvm.sqrt.f32(float %x);

define float @fast_recip_sqrt(float %x) {
; X64-LABEL: fast_recip_sqrt:
; X64:       # %bb.0:
; X64-NEXT:    rsqrtss %xmm0, %xmm1
; X64-NEXT:    mulss %xmm1, %xmm0
; X64-NEXT:    mulss %xmm1, %xmm0
; X64-NEXT:    addss {{.*}}(%rip), %xmm0
; X64-NEXT:    mulss {{.*}}(%rip), %xmm1
; X64-NEXT:    mulss %xmm1, %xmm0
; X64-NEXT:    retq
;
; X86-LABEL: fast_recip_sqrt:
; X86:       # %bb.0:
; X86-NEXT:    flds {{[0-9]+}}(%esp)
; X86-NEXT:    fsqrt
; X86-NEXT:    fld1
; X86-NEXT:    fdivp %st, %st(1)
; X86-NEXT:    retl
  %y = call fast float @llvm.sqrt.f32(float %x)
  %z = fdiv fast float 1.0,  %y
  ret float %z
}

declare float @llvm.fmuladd.f32(float %a, float %b, float %c);

define float @fast_fmuladd_opts(float %a , float %b , float %c) {
; X64-LABEL: fast_fmuladd_opts:
; X64:       # %bb.0:
; X64-NEXT:    mulss {{.*}}(%rip), %xmm0
; X64-NEXT:    retq
;
; X86-LABEL: fast_fmuladd_opts:
; X86:       # %bb.0:
; X86-NEXT:    flds {{[0-9]+}}(%esp)
; X86-NEXT:    fmuls {{\.LCPI.*}}
; X86-NEXT:    retl
  %res = call fast float @llvm.fmuladd.f32(float %a, float 2.0, float %a)
  ret float %res
}

; The multiply is strict.

@mul1 = common global double 0.000000e+00, align 4

define double @not_so_fast_mul_add(double %x) {
; X64-LABEL: not_so_fast_mul_add:
; X64:       # %bb.0:
; X64-NEXT:    movsd {{.*#+}} xmm1 = mem[0],zero
; X64-NEXT:    mulsd %xmm0, %xmm1
; X64-NEXT:    mulsd {{.*}}(%rip), %xmm0
; X64-NEXT:    movsd %xmm1, {{.*}}(%rip)
; X64-NEXT:    retq
;
; X86-LABEL: not_so_fast_mul_add:
; X86:       # %bb.0:
; X86-NEXT:    fldl {{[0-9]+}}(%esp)
; X86-NEXT:    fld %st(0)
; X86-NEXT:    fmull {{\.LCPI.*}}
; X86-NEXT:    fxch %st(1)
; X86-NEXT:    fmull {{\.LCPI.*}}
; X86-NEXT:    fxch %st(1)
; X86-NEXT:    fstpl mul1
; X86-NEXT:    retl
  %m = fmul double %x, 4.2
  %a = fadd fast double %m, %x
  store double %m, double* @mul1, align 4
  ret double %a
}

; The sqrt is strict.

@sqrt1 = common global float 0.000000e+00, align 4

define float @not_so_fast_recip_sqrt(float %x) {
; X64-LABEL: not_so_fast_recip_sqrt:
; X64:       # %bb.0:
; X64-NEXT:    rsqrtss %xmm0, %xmm1
; X64-NEXT:    sqrtss %xmm0, %xmm2
; X64-NEXT:    mulss %xmm1, %xmm0
; X64-NEXT:    mulss %xmm1, %xmm0
; X64-NEXT:    addss {{.*}}(%rip), %xmm0
; X64-NEXT:    mulss {{.*}}(%rip), %xmm1
; X64-NEXT:    mulss %xmm1, %xmm0
; X64-NEXT:    movss %xmm2, {{.*}}(%rip)
; X64-NEXT:    retq
;
; X86-LABEL: not_so_fast_recip_sqrt:
; X86:       # %bb.0:
; X86-NEXT:    flds {{[0-9]+}}(%esp)
; X86-NEXT:    fsqrt
; X86-NEXT:    fld1
; X86-NEXT:    fdiv %st(1), %st
; X86-NEXT:    fxch %st(1)
; X86-NEXT:    fstps sqrt1
; X86-NEXT:    retl
  %y = call float @llvm.sqrt.f32(float %x)
  %z = fdiv fast float 1.0, %y
  store float %y, float* @sqrt1, align 4
  %ret = fadd float %z , 14.5
  ret float %z
}

define float @div_arcp_by_const(half %x) {
; X64-LABEL: div_arcp_by_const:
; X64:       # %bb.0:
; X64-NEXT:    pushq %rax
; X64-NEXT:    .cfi_def_cfa_offset 16
; X64-NEXT:    movzwl %di, %edi
; X64-NEXT:    callq __gnu_h2f_ieee
; X64-NEXT:    mulss {{.*}}(%rip), %xmm0
; X64-NEXT:    callq __gnu_f2h_ieee
; X64-NEXT:    movzwl %ax, %edi
; X64-NEXT:    popq %rax
; X64-NEXT:    .cfi_def_cfa_offset 8
; X64-NEXT:    jmp __gnu_h2f_ieee@PLT # TAILCALL
;
; X86-LABEL: div_arcp_by_const:
; X86:       # %bb.0:
; X86-NEXT:    pushl %eax
; X86-NEXT:    .cfi_def_cfa_offset 8
; X86-NEXT:    movzwl {{[0-9]+}}(%esp), %eax
; X86-NEXT:    movl %eax, (%esp)
; X86-NEXT:    calll __gnu_h2f_ieee
; X86-NEXT:    fmuls {{\.LCPI.*}}
; X86-NEXT:    fstps (%esp)
; X86-NEXT:    calll __gnu_f2h_ieee
; X86-NEXT:    movzwl %ax, %eax
; X86-NEXT:    movl %eax, (%esp)
; X86-NEXT:    calll __gnu_h2f_ieee
; X86-NEXT:    popl %eax
; X86-NEXT:    .cfi_def_cfa_offset 4
; X86-NEXT:    retl
  %rcp = fdiv arcp half %x, 10.0
  %z = fpext half %rcp to float
  ret float %z
}
