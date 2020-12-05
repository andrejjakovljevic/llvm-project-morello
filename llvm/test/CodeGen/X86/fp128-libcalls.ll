; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc < %s -O2 -mtriple=x86_64-linux-android \
; RUN:     -enable-legalize-types-checking | FileCheck %s
; RUN: llc < %s -O2 -mtriple=x86_64-linux-gnu \
; RUN:     -enable-legalize-types-checking | FileCheck %s
; RUN: llc < %s -O2 -mtriple=i686-linux-gnu -mattr=sse2 \
; RUN:     -enable-legalize-types-checking | FileCheck %s --check-prefix=X86

; Check all soft floating point library function calls.

@vf64 = common global double 0.000000e+00, align 8
@vf128 = common global fp128 0xL00000000000000000000000000000000, align 16

define void @Test128Add(fp128 %d1, fp128 %d2) nounwind {
; CHECK-LABEL: Test128Add:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    pushq %rax
; CHECK-NEXT:    callq __addtf3
; CHECK-NEXT:    movaps %xmm0, {{.*}}(%rip)
; CHECK-NEXT:    popq %rax
; CHECK-NEXT:    retq
;
; X86-LABEL: Test128Add:
; X86:       # %bb.0: # %entry
; X86-NEXT:    pushl %esi
; X86-NEXT:    subl $36, %esp
; X86-NEXT:    leal {{[0-9]+}}(%esp), %eax
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl %eax
; X86-NEXT:    calll __addtf3
; X86-NEXT:    addl $44, %esp
; X86-NEXT:    movl {{[0-9]+}}(%esp), %eax
; X86-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %edx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %esi
; X86-NEXT:    movl %esi, vf128+12
; X86-NEXT:    movl %edx, vf128+8
; X86-NEXT:    movl %ecx, vf128+4
; X86-NEXT:    movl %eax, vf128
; X86-NEXT:    addl $24, %esp
; X86-NEXT:    popl %esi
; X86-NEXT:    retl
entry:
  %add = fadd fp128 %d1, %d2
  store fp128 %add, fp128* @vf128, align 16
  ret void
}

define void @Test128_1Add(fp128 %d1) nounwind {
; CHECK-LABEL: Test128_1Add:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    pushq %rax
; CHECK-NEXT:    movaps %xmm0, %xmm1
; CHECK-NEXT:    movaps {{.*}}(%rip), %xmm0
; CHECK-NEXT:    callq __addtf3
; CHECK-NEXT:    movaps %xmm0, {{.*}}(%rip)
; CHECK-NEXT:    popq %rax
; CHECK-NEXT:    retq
;
; X86-LABEL: Test128_1Add:
; X86:       # %bb.0: # %entry
; X86-NEXT:    pushl %esi
; X86-NEXT:    subl $36, %esp
; X86-NEXT:    leal {{[0-9]+}}(%esp), %eax
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl vf128+12
; X86-NEXT:    pushl vf128+8
; X86-NEXT:    pushl vf128+4
; X86-NEXT:    pushl vf128
; X86-NEXT:    pushl %eax
; X86-NEXT:    calll __addtf3
; X86-NEXT:    addl $44, %esp
; X86-NEXT:    movl {{[0-9]+}}(%esp), %eax
; X86-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %edx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %esi
; X86-NEXT:    movl %esi, vf128+8
; X86-NEXT:    movl %edx, vf128+12
; X86-NEXT:    movl %eax, vf128
; X86-NEXT:    movl %ecx, vf128+4
; X86-NEXT:    addl $24, %esp
; X86-NEXT:    popl %esi
; X86-NEXT:    retl
entry:
  %0 = load fp128, fp128* @vf128, align 16
  %add = fadd fp128 %0, %d1
  store fp128 %add, fp128* @vf128, align 16
  ret void
}

define void @Test128Sub(fp128 %d1, fp128 %d2) nounwind {
; CHECK-LABEL: Test128Sub:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    pushq %rax
; CHECK-NEXT:    callq __subtf3
; CHECK-NEXT:    movaps %xmm0, {{.*}}(%rip)
; CHECK-NEXT:    popq %rax
; CHECK-NEXT:    retq
;
; X86-LABEL: Test128Sub:
; X86:       # %bb.0: # %entry
; X86-NEXT:    pushl %esi
; X86-NEXT:    subl $36, %esp
; X86-NEXT:    leal {{[0-9]+}}(%esp), %eax
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl %eax
; X86-NEXT:    calll __subtf3
; X86-NEXT:    addl $44, %esp
; X86-NEXT:    movl {{[0-9]+}}(%esp), %eax
; X86-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %edx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %esi
; X86-NEXT:    movl %esi, vf128+12
; X86-NEXT:    movl %edx, vf128+8
; X86-NEXT:    movl %ecx, vf128+4
; X86-NEXT:    movl %eax, vf128
; X86-NEXT:    addl $24, %esp
; X86-NEXT:    popl %esi
; X86-NEXT:    retl
entry:
  %sub = fsub fp128 %d1, %d2
  store fp128 %sub, fp128* @vf128, align 16
  ret void
}

define void @Test128_1Sub(fp128 %d1) nounwind {
; CHECK-LABEL: Test128_1Sub:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    pushq %rax
; CHECK-NEXT:    movaps %xmm0, %xmm1
; CHECK-NEXT:    movaps {{.*}}(%rip), %xmm0
; CHECK-NEXT:    callq __subtf3
; CHECK-NEXT:    movaps %xmm0, {{.*}}(%rip)
; CHECK-NEXT:    popq %rax
; CHECK-NEXT:    retq
;
; X86-LABEL: Test128_1Sub:
; X86:       # %bb.0: # %entry
; X86-NEXT:    pushl %esi
; X86-NEXT:    subl $36, %esp
; X86-NEXT:    leal {{[0-9]+}}(%esp), %eax
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl vf128+12
; X86-NEXT:    pushl vf128+8
; X86-NEXT:    pushl vf128+4
; X86-NEXT:    pushl vf128
; X86-NEXT:    pushl %eax
; X86-NEXT:    calll __subtf3
; X86-NEXT:    addl $44, %esp
; X86-NEXT:    movl {{[0-9]+}}(%esp), %eax
; X86-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %edx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %esi
; X86-NEXT:    movl %esi, vf128+8
; X86-NEXT:    movl %edx, vf128+12
; X86-NEXT:    movl %eax, vf128
; X86-NEXT:    movl %ecx, vf128+4
; X86-NEXT:    addl $24, %esp
; X86-NEXT:    popl %esi
; X86-NEXT:    retl
entry:
  %0 = load fp128, fp128* @vf128, align 16
  %sub = fsub fp128 %0, %d1
  store fp128 %sub, fp128* @vf128, align 16
  ret void
}

define void @Test128Mul(fp128 %d1, fp128 %d2) nounwind {
; CHECK-LABEL: Test128Mul:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    pushq %rax
; CHECK-NEXT:    callq __multf3
; CHECK-NEXT:    movaps %xmm0, {{.*}}(%rip)
; CHECK-NEXT:    popq %rax
; CHECK-NEXT:    retq
;
; X86-LABEL: Test128Mul:
; X86:       # %bb.0: # %entry
; X86-NEXT:    pushl %esi
; X86-NEXT:    subl $36, %esp
; X86-NEXT:    leal {{[0-9]+}}(%esp), %eax
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl %eax
; X86-NEXT:    calll __multf3
; X86-NEXT:    addl $44, %esp
; X86-NEXT:    movl {{[0-9]+}}(%esp), %eax
; X86-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %edx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %esi
; X86-NEXT:    movl %esi, vf128+12
; X86-NEXT:    movl %edx, vf128+8
; X86-NEXT:    movl %ecx, vf128+4
; X86-NEXT:    movl %eax, vf128
; X86-NEXT:    addl $24, %esp
; X86-NEXT:    popl %esi
; X86-NEXT:    retl
entry:
  %mul = fmul fp128 %d1, %d2
  store fp128 %mul, fp128* @vf128, align 16
  ret void
}

define void @Test128_1Mul(fp128 %d1) nounwind {
; CHECK-LABEL: Test128_1Mul:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    pushq %rax
; CHECK-NEXT:    movaps %xmm0, %xmm1
; CHECK-NEXT:    movaps {{.*}}(%rip), %xmm0
; CHECK-NEXT:    callq __multf3
; CHECK-NEXT:    movaps %xmm0, {{.*}}(%rip)
; CHECK-NEXT:    popq %rax
; CHECK-NEXT:    retq
;
; X86-LABEL: Test128_1Mul:
; X86:       # %bb.0: # %entry
; X86-NEXT:    pushl %esi
; X86-NEXT:    subl $36, %esp
; X86-NEXT:    leal {{[0-9]+}}(%esp), %eax
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl vf128+12
; X86-NEXT:    pushl vf128+8
; X86-NEXT:    pushl vf128+4
; X86-NEXT:    pushl vf128
; X86-NEXT:    pushl %eax
; X86-NEXT:    calll __multf3
; X86-NEXT:    addl $44, %esp
; X86-NEXT:    movl {{[0-9]+}}(%esp), %eax
; X86-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %edx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %esi
; X86-NEXT:    movl %esi, vf128+8
; X86-NEXT:    movl %edx, vf128+12
; X86-NEXT:    movl %eax, vf128
; X86-NEXT:    movl %ecx, vf128+4
; X86-NEXT:    addl $24, %esp
; X86-NEXT:    popl %esi
; X86-NEXT:    retl
entry:
  %0 = load fp128, fp128* @vf128, align 16
  %mul = fmul fp128 %0, %d1
  store fp128 %mul, fp128* @vf128, align 16
  ret void
}

define void @Test128Div(fp128 %d1, fp128 %d2) nounwind {
; CHECK-LABEL: Test128Div:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    pushq %rax
; CHECK-NEXT:    callq __divtf3
; CHECK-NEXT:    movaps %xmm0, {{.*}}(%rip)
; CHECK-NEXT:    popq %rax
; CHECK-NEXT:    retq
;
; X86-LABEL: Test128Div:
; X86:       # %bb.0: # %entry
; X86-NEXT:    pushl %esi
; X86-NEXT:    subl $36, %esp
; X86-NEXT:    leal {{[0-9]+}}(%esp), %eax
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl %eax
; X86-NEXT:    calll __divtf3
; X86-NEXT:    addl $44, %esp
; X86-NEXT:    movl {{[0-9]+}}(%esp), %eax
; X86-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %edx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %esi
; X86-NEXT:    movl %esi, vf128+12
; X86-NEXT:    movl %edx, vf128+8
; X86-NEXT:    movl %ecx, vf128+4
; X86-NEXT:    movl %eax, vf128
; X86-NEXT:    addl $24, %esp
; X86-NEXT:    popl %esi
; X86-NEXT:    retl
entry:
  %div = fdiv fp128 %d1, %d2
  store fp128 %div, fp128* @vf128, align 16
  ret void
}

define void @Test128_1Div(fp128 %d1) nounwind {
; CHECK-LABEL: Test128_1Div:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    pushq %rax
; CHECK-NEXT:    movaps %xmm0, %xmm1
; CHECK-NEXT:    movaps {{.*}}(%rip), %xmm0
; CHECK-NEXT:    callq __divtf3
; CHECK-NEXT:    movaps %xmm0, {{.*}}(%rip)
; CHECK-NEXT:    popq %rax
; CHECK-NEXT:    retq
;
; X86-LABEL: Test128_1Div:
; X86:       # %bb.0: # %entry
; X86-NEXT:    pushl %esi
; X86-NEXT:    subl $36, %esp
; X86-NEXT:    leal {{[0-9]+}}(%esp), %eax
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl vf128+12
; X86-NEXT:    pushl vf128+8
; X86-NEXT:    pushl vf128+4
; X86-NEXT:    pushl vf128
; X86-NEXT:    pushl %eax
; X86-NEXT:    calll __divtf3
; X86-NEXT:    addl $44, %esp
; X86-NEXT:    movl {{[0-9]+}}(%esp), %eax
; X86-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %edx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %esi
; X86-NEXT:    movl %esi, vf128+8
; X86-NEXT:    movl %edx, vf128+12
; X86-NEXT:    movl %eax, vf128
; X86-NEXT:    movl %ecx, vf128+4
; X86-NEXT:    addl $24, %esp
; X86-NEXT:    popl %esi
; X86-NEXT:    retl
entry:
  %0 = load fp128, fp128* @vf128, align 16
  %div = fdiv fp128 %0, %d1
  store fp128 %div, fp128* @vf128, align 16
  ret void
}

define void @Test128Rem(fp128 %d1, fp128 %d2) nounwind {
; CHECK-LABEL: Test128Rem:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    pushq %rax
; CHECK-NEXT:    callq fmodl
; CHECK-NEXT:    movaps %xmm0, {{.*}}(%rip)
; CHECK-NEXT:    popq %rax
; CHECK-NEXT:    retq
;
; X86-LABEL: Test128Rem:
; X86:       # %bb.0: # %entry
; X86-NEXT:    pushl %esi
; X86-NEXT:    subl $36, %esp
; X86-NEXT:    leal {{[0-9]+}}(%esp), %eax
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl %eax
; X86-NEXT:    calll fmodl
; X86-NEXT:    addl $44, %esp
; X86-NEXT:    movl {{[0-9]+}}(%esp), %eax
; X86-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %edx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %esi
; X86-NEXT:    movl %esi, vf128+12
; X86-NEXT:    movl %edx, vf128+8
; X86-NEXT:    movl %ecx, vf128+4
; X86-NEXT:    movl %eax, vf128
; X86-NEXT:    addl $24, %esp
; X86-NEXT:    popl %esi
; X86-NEXT:    retl
entry:
  %div = frem fp128 %d1, %d2
  store fp128 %div, fp128* @vf128, align 16
  ret void
}

define void @Test128_1Rem(fp128 %d1) nounwind {
; CHECK-LABEL: Test128_1Rem:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    pushq %rax
; CHECK-NEXT:    movaps %xmm0, %xmm1
; CHECK-NEXT:    movaps {{.*}}(%rip), %xmm0
; CHECK-NEXT:    callq fmodl
; CHECK-NEXT:    movaps %xmm0, {{.*}}(%rip)
; CHECK-NEXT:    popq %rax
; CHECK-NEXT:    retq
;
; X86-LABEL: Test128_1Rem:
; X86:       # %bb.0: # %entry
; X86-NEXT:    pushl %esi
; X86-NEXT:    subl $36, %esp
; X86-NEXT:    leal {{[0-9]+}}(%esp), %eax
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl vf128+12
; X86-NEXT:    pushl vf128+8
; X86-NEXT:    pushl vf128+4
; X86-NEXT:    pushl vf128
; X86-NEXT:    pushl %eax
; X86-NEXT:    calll fmodl
; X86-NEXT:    addl $44, %esp
; X86-NEXT:    movl {{[0-9]+}}(%esp), %eax
; X86-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %edx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %esi
; X86-NEXT:    movl %esi, vf128+8
; X86-NEXT:    movl %edx, vf128+12
; X86-NEXT:    movl %eax, vf128
; X86-NEXT:    movl %ecx, vf128+4
; X86-NEXT:    addl $24, %esp
; X86-NEXT:    popl %esi
; X86-NEXT:    retl
entry:
  %0 = load fp128, fp128* @vf128, align 16
  %div = frem fp128 %0, %d1
  store fp128 %div, fp128* @vf128, align 16
  ret void
}

define void @Test128Sqrt(fp128 %d1) nounwind {
; CHECK-LABEL: Test128Sqrt:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    pushq %rax
; CHECK-NEXT:    callq sqrtl
; CHECK-NEXT:    movaps %xmm0, {{.*}}(%rip)
; CHECK-NEXT:    popq %rax
; CHECK-NEXT:    retq
;
; X86-LABEL: Test128Sqrt:
; X86:       # %bb.0: # %entry
; X86-NEXT:    pushl %esi
; X86-NEXT:    subl $36, %esp
; X86-NEXT:    leal {{[0-9]+}}(%esp), %eax
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl %eax
; X86-NEXT:    calll sqrtl
; X86-NEXT:    addl $28, %esp
; X86-NEXT:    movl {{[0-9]+}}(%esp), %eax
; X86-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %edx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %esi
; X86-NEXT:    movl %esi, vf128+12
; X86-NEXT:    movl %edx, vf128+8
; X86-NEXT:    movl %ecx, vf128+4
; X86-NEXT:    movl %eax, vf128
; X86-NEXT:    addl $24, %esp
; X86-NEXT:    popl %esi
; X86-NEXT:    retl
entry:
  %sqrt = call fp128 @llvm.sqrt.f128(fp128 %d1)
  store fp128 %sqrt, fp128* @vf128, align 16
  ret void
}
declare fp128 @llvm.sqrt.f128(fp128)

define void @Test128Sin(fp128 %d1) nounwind {
; CHECK-LABEL: Test128Sin:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    pushq %rax
; CHECK-NEXT:    callq sinl
; CHECK-NEXT:    movaps %xmm0, {{.*}}(%rip)
; CHECK-NEXT:    popq %rax
; CHECK-NEXT:    retq
;
; X86-LABEL: Test128Sin:
; X86:       # %bb.0: # %entry
; X86-NEXT:    pushl %esi
; X86-NEXT:    subl $36, %esp
; X86-NEXT:    leal {{[0-9]+}}(%esp), %eax
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl %eax
; X86-NEXT:    calll sinl
; X86-NEXT:    addl $28, %esp
; X86-NEXT:    movl {{[0-9]+}}(%esp), %eax
; X86-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %edx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %esi
; X86-NEXT:    movl %esi, vf128+12
; X86-NEXT:    movl %edx, vf128+8
; X86-NEXT:    movl %ecx, vf128+4
; X86-NEXT:    movl %eax, vf128
; X86-NEXT:    addl $24, %esp
; X86-NEXT:    popl %esi
; X86-NEXT:    retl
entry:
  %sqrt = call fp128 @llvm.sin.f128(fp128 %d1)
  store fp128 %sqrt, fp128* @vf128, align 16
  ret void
}
declare fp128 @llvm.sin.f128(fp128)

define void @Test128Cos(fp128 %d1) nounwind {
; CHECK-LABEL: Test128Cos:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    pushq %rax
; CHECK-NEXT:    callq cosl
; CHECK-NEXT:    movaps %xmm0, {{.*}}(%rip)
; CHECK-NEXT:    popq %rax
; CHECK-NEXT:    retq
;
; X86-LABEL: Test128Cos:
; X86:       # %bb.0: # %entry
; X86-NEXT:    pushl %esi
; X86-NEXT:    subl $36, %esp
; X86-NEXT:    leal {{[0-9]+}}(%esp), %eax
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl %eax
; X86-NEXT:    calll cosl
; X86-NEXT:    addl $28, %esp
; X86-NEXT:    movl {{[0-9]+}}(%esp), %eax
; X86-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %edx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %esi
; X86-NEXT:    movl %esi, vf128+12
; X86-NEXT:    movl %edx, vf128+8
; X86-NEXT:    movl %ecx, vf128+4
; X86-NEXT:    movl %eax, vf128
; X86-NEXT:    addl $24, %esp
; X86-NEXT:    popl %esi
; X86-NEXT:    retl
entry:
  %sqrt = call fp128 @llvm.cos.f128(fp128 %d1)
  store fp128 %sqrt, fp128* @vf128, align 16
  ret void
}
declare fp128 @llvm.cos.f128(fp128)

define void @Test128Ceil(fp128 %d1) nounwind {
; CHECK-LABEL: Test128Ceil:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    pushq %rax
; CHECK-NEXT:    callq ceill
; CHECK-NEXT:    movaps %xmm0, {{.*}}(%rip)
; CHECK-NEXT:    popq %rax
; CHECK-NEXT:    retq
;
; X86-LABEL: Test128Ceil:
; X86:       # %bb.0: # %entry
; X86-NEXT:    pushl %esi
; X86-NEXT:    subl $36, %esp
; X86-NEXT:    leal {{[0-9]+}}(%esp), %eax
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl %eax
; X86-NEXT:    calll ceill
; X86-NEXT:    addl $28, %esp
; X86-NEXT:    movl {{[0-9]+}}(%esp), %eax
; X86-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %edx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %esi
; X86-NEXT:    movl %esi, vf128+12
; X86-NEXT:    movl %edx, vf128+8
; X86-NEXT:    movl %ecx, vf128+4
; X86-NEXT:    movl %eax, vf128
; X86-NEXT:    addl $24, %esp
; X86-NEXT:    popl %esi
; X86-NEXT:    retl
entry:
  %sqrt = call fp128 @llvm.ceil.f128(fp128 %d1)
  store fp128 %sqrt, fp128* @vf128, align 16
  ret void
}
declare fp128 @llvm.ceil.f128(fp128)

define void @Test128Floor(fp128 %d1) nounwind {
; CHECK-LABEL: Test128Floor:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    pushq %rax
; CHECK-NEXT:    callq floorl
; CHECK-NEXT:    movaps %xmm0, {{.*}}(%rip)
; CHECK-NEXT:    popq %rax
; CHECK-NEXT:    retq
;
; X86-LABEL: Test128Floor:
; X86:       # %bb.0: # %entry
; X86-NEXT:    pushl %esi
; X86-NEXT:    subl $36, %esp
; X86-NEXT:    leal {{[0-9]+}}(%esp), %eax
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl %eax
; X86-NEXT:    calll floorl
; X86-NEXT:    addl $28, %esp
; X86-NEXT:    movl {{[0-9]+}}(%esp), %eax
; X86-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %edx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %esi
; X86-NEXT:    movl %esi, vf128+12
; X86-NEXT:    movl %edx, vf128+8
; X86-NEXT:    movl %ecx, vf128+4
; X86-NEXT:    movl %eax, vf128
; X86-NEXT:    addl $24, %esp
; X86-NEXT:    popl %esi
; X86-NEXT:    retl
entry:
  %sqrt = call fp128 @llvm.floor.f128(fp128 %d1)
  store fp128 %sqrt, fp128* @vf128, align 16
  ret void
}
declare fp128 @llvm.floor.f128(fp128)

define void @Test128Trunc(fp128 %d1) nounwind {
; CHECK-LABEL: Test128Trunc:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    pushq %rax
; CHECK-NEXT:    callq truncl
; CHECK-NEXT:    movaps %xmm0, {{.*}}(%rip)
; CHECK-NEXT:    popq %rax
; CHECK-NEXT:    retq
;
; X86-LABEL: Test128Trunc:
; X86:       # %bb.0: # %entry
; X86-NEXT:    pushl %esi
; X86-NEXT:    subl $36, %esp
; X86-NEXT:    leal {{[0-9]+}}(%esp), %eax
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl %eax
; X86-NEXT:    calll truncl
; X86-NEXT:    addl $28, %esp
; X86-NEXT:    movl {{[0-9]+}}(%esp), %eax
; X86-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %edx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %esi
; X86-NEXT:    movl %esi, vf128+12
; X86-NEXT:    movl %edx, vf128+8
; X86-NEXT:    movl %ecx, vf128+4
; X86-NEXT:    movl %eax, vf128
; X86-NEXT:    addl $24, %esp
; X86-NEXT:    popl %esi
; X86-NEXT:    retl
entry:
  %sqrt = call fp128 @llvm.trunc.f128(fp128 %d1)
  store fp128 %sqrt, fp128* @vf128, align 16
  ret void
}
declare fp128 @llvm.trunc.f128(fp128)

define void @Test128Nearbyint(fp128 %d1) nounwind {
; CHECK-LABEL: Test128Nearbyint:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    pushq %rax
; CHECK-NEXT:    callq nearbyintl
; CHECK-NEXT:    movaps %xmm0, {{.*}}(%rip)
; CHECK-NEXT:    popq %rax
; CHECK-NEXT:    retq
;
; X86-LABEL: Test128Nearbyint:
; X86:       # %bb.0: # %entry
; X86-NEXT:    pushl %esi
; X86-NEXT:    subl $36, %esp
; X86-NEXT:    leal {{[0-9]+}}(%esp), %eax
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl %eax
; X86-NEXT:    calll nearbyintl
; X86-NEXT:    addl $28, %esp
; X86-NEXT:    movl {{[0-9]+}}(%esp), %eax
; X86-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %edx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %esi
; X86-NEXT:    movl %esi, vf128+12
; X86-NEXT:    movl %edx, vf128+8
; X86-NEXT:    movl %ecx, vf128+4
; X86-NEXT:    movl %eax, vf128
; X86-NEXT:    addl $24, %esp
; X86-NEXT:    popl %esi
; X86-NEXT:    retl
entry:
  %sqrt = call fp128 @llvm.nearbyint.f128(fp128 %d1)
  store fp128 %sqrt, fp128* @vf128, align 16
  ret void
}
declare fp128 @llvm.nearbyint.f128(fp128)

define void @Test128Rint(fp128 %d1) nounwind {
; CHECK-LABEL: Test128Rint:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    pushq %rax
; CHECK-NEXT:    callq rintl
; CHECK-NEXT:    movaps %xmm0, {{.*}}(%rip)
; CHECK-NEXT:    popq %rax
; CHECK-NEXT:    retq
;
; X86-LABEL: Test128Rint:
; X86:       # %bb.0: # %entry
; X86-NEXT:    pushl %esi
; X86-NEXT:    subl $36, %esp
; X86-NEXT:    leal {{[0-9]+}}(%esp), %eax
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl %eax
; X86-NEXT:    calll rintl
; X86-NEXT:    addl $28, %esp
; X86-NEXT:    movl {{[0-9]+}}(%esp), %eax
; X86-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %edx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %esi
; X86-NEXT:    movl %esi, vf128+12
; X86-NEXT:    movl %edx, vf128+8
; X86-NEXT:    movl %ecx, vf128+4
; X86-NEXT:    movl %eax, vf128
; X86-NEXT:    addl $24, %esp
; X86-NEXT:    popl %esi
; X86-NEXT:    retl
entry:
  %sqrt = call fp128 @llvm.rint.f128(fp128 %d1)
  store fp128 %sqrt, fp128* @vf128, align 16
  ret void
}
declare fp128 @llvm.rint.f128(fp128)

define void @Test128Round(fp128 %d1) nounwind {
; CHECK-LABEL: Test128Round:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    pushq %rax
; CHECK-NEXT:    callq roundl
; CHECK-NEXT:    movaps %xmm0, {{.*}}(%rip)
; CHECK-NEXT:    popq %rax
; CHECK-NEXT:    retq
;
; X86-LABEL: Test128Round:
; X86:       # %bb.0: # %entry
; X86-NEXT:    pushl %esi
; X86-NEXT:    subl $36, %esp
; X86-NEXT:    leal {{[0-9]+}}(%esp), %eax
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl %eax
; X86-NEXT:    calll roundl
; X86-NEXT:    addl $28, %esp
; X86-NEXT:    movl {{[0-9]+}}(%esp), %eax
; X86-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %edx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %esi
; X86-NEXT:    movl %esi, vf128+12
; X86-NEXT:    movl %edx, vf128+8
; X86-NEXT:    movl %ecx, vf128+4
; X86-NEXT:    movl %eax, vf128
; X86-NEXT:    addl $24, %esp
; X86-NEXT:    popl %esi
; X86-NEXT:    retl
entry:
  %sqrt = call fp128 @llvm.round.f128(fp128 %d1)
  store fp128 %sqrt, fp128* @vf128, align 16
  ret void
}
declare fp128 @llvm.round.f128(fp128)

define fp128 @Test128FMA(fp128 %a, fp128 %b, fp128 %c) nounwind {
; CHECK-LABEL: Test128FMA:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    jmp fmal@PLT # TAILCALL
;
; X86-LABEL: Test128FMA:
; X86:       # %bb.0: # %entry
; X86-NEXT:    pushl %edi
; X86-NEXT:    pushl %esi
; X86-NEXT:    subl $20, %esp
; X86-NEXT:    movl {{[0-9]+}}(%esp), %esi
; X86-NEXT:    subl $12, %esp
; X86-NEXT:    leal {{[0-9]+}}(%esp), %eax
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl {{[0-9]+}}(%esp)
; X86-NEXT:    pushl %eax
; X86-NEXT:    calll fmal
; X86-NEXT:    addl $60, %esp
; X86-NEXT:    movl (%esp), %eax
; X86-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %edx
; X86-NEXT:    movl {{[0-9]+}}(%esp), %edi
; X86-NEXT:    movl %edi, 12(%esi)
; X86-NEXT:    movl %edx, 8(%esi)
; X86-NEXT:    movl %ecx, 4(%esi)
; X86-NEXT:    movl %eax, (%esi)
; X86-NEXT:    movl %esi, %eax
; X86-NEXT:    addl $20, %esp
; X86-NEXT:    popl %esi
; X86-NEXT:    popl %edi
; X86-NEXT:    retl $4
entry:
  %call = call fp128 @llvm.fma.f128(fp128 %a, fp128 %b, fp128 %c)
  ret fp128 %call
}
declare fp128 @llvm.fma.f128(fp128, fp128, fp128)
