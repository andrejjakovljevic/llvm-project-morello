; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc < %s -mtriple=x86_64-apple-darwin -mattr=avx | FileCheck %s

@x = common global <8 x float> zeroinitializer, align 32
@y = common global <4 x double> zeroinitializer, align 32
@z = common global <4 x float> zeroinitializer, align 16

define void @zero128() nounwind ssp {
; CHECK-LABEL: zero128:
; CHECK:       ## BB#0:
; CHECK-NEXT:    vxorps %xmm0, %xmm0, %xmm0
; CHECK-NEXT:    movq _z@{{.*}}(%rip), %rax
; CHECK-NEXT:    vmovaps %xmm0, (%rax)
; CHECK-NEXT:    retq
; CHECK-NEXT:    ## -- End function
  store <4 x float> zeroinitializer, <4 x float>* @z, align 16
  ret void
}

define void @zero256() nounwind ssp {
; CHECK-LABEL: zero256:
; CHECK:       ## BB#0:
; CHECK-NEXT:    movq _x@{{.*}}(%rip), %rax
; CHECK-NEXT:    vxorps %xmm0, %xmm0, %xmm0
; CHECK-NEXT:    vmovaps %ymm0, (%rax)
; CHECK-NEXT:    movq _y@{{.*}}(%rip), %rax
; CHECK-NEXT:    vmovaps %ymm0, (%rax)
; CHECK-NEXT:    vzeroupper
; CHECK-NEXT:    retq
; CHECK-NEXT:    ## -- End function
  store <8 x float> zeroinitializer, <8 x float>* @x, align 32
  store <4 x double> zeroinitializer, <4 x double>* @y, align 32
  ret void
}

define void @ones([0 x float]* nocapture %RET, [0 x float]* nocapture %aFOO) nounwind {
; CHECK-LABEL: ones:
; CHECK:       ## BB#0: ## %allocas
; CHECK-NEXT:    vxorps %xmm0, %xmm0, %xmm0
; CHECK-NEXT:    vcmptrueps %ymm0, %ymm0, %ymm0
; CHECK-NEXT:    vmovaps %ymm0, (%rdi)
; CHECK-NEXT:    vzeroupper
; CHECK-NEXT:    retq
; CHECK-NEXT:    ## -- End function
allocas:
  %ptr2vec615 = bitcast [0 x float]* %RET to <8 x float>*
  store <8 x float> <float 0xFFFFFFFFE0000000, float 0xFFFFFFFFE0000000, float
0xFFFFFFFFE0000000, float 0xFFFFFFFFE0000000, float 0xFFFFFFFFE0000000, float
0xFFFFFFFFE0000000, float 0xFFFFFFFFE0000000, float 0xFFFFFFFFE0000000>, <8 x
float>* %ptr2vec615, align 32
  ret void
}

define void @ones2([0 x i32]* nocapture %RET, [0 x i32]* nocapture %aFOO) nounwind {
; CHECK-LABEL: ones2:
; CHECK:       ## BB#0: ## %allocas
; CHECK-NEXT:    vxorps %xmm0, %xmm0, %xmm0
; CHECK-NEXT:    vcmptrueps %ymm0, %ymm0, %ymm0
; CHECK-NEXT:    vmovaps %ymm0, (%rdi)
; CHECK-NEXT:    vzeroupper
; CHECK-NEXT:    retq
; CHECK-NEXT:    ## -- End function
allocas:
  %ptr2vec615 = bitcast [0 x i32]* %RET to <8 x i32>*
  store <8 x i32> <i32 -1, i32 -1, i32 -1, i32 -1, i32 -1, i32 -1, i32 -1, i32 -1>, <8 x i32>* %ptr2vec615, align 32
  ret void
}

;;; Just make sure this doesn't crash
define <4 x i64> @ISelCrash(<4 x i64> %a) nounwind uwtable readnone ssp {
; CHECK-LABEL: ISelCrash:
; CHECK:       ## BB#0:
; CHECK-NEXT:    vextractf128 $1, %ymm0, %xmm0
; CHECK-NEXT:    retq
  %shuffle = shufflevector <4 x i64> %a, <4 x i64> undef, <4 x i32> <i32 2, i32 3, i32 4, i32 4>
  ret <4 x i64> %shuffle
}

;;; Don't crash on movd
define <8 x i32> @VMOVZQI2PQI([0 x float]* nocapture %aFOO) nounwind {
; CHECK-LABEL: VMOVZQI2PQI:
; CHECK:       ## BB#0:
; CHECK-NEXT:    vmovd {{.*#+}} xmm0 = mem[0],zero,zero,zero
; CHECK-NEXT:    vpshufd {{.*#+}} xmm0 = xmm0[0,0,1,1]
; CHECK-NEXT:    retq
; CHECK-NEXT:    ## -- End function
  %ptrcast.i33.i = bitcast [0 x float]* %aFOO to i32*
  %val.i34.i = load i32, i32* %ptrcast.i33.i, align 4
  %ptroffset.i22.i992 = getelementptr [0 x float], [0 x float]* %aFOO, i64 0, i64 1
  %ptrcast.i23.i = bitcast float* %ptroffset.i22.i992 to i32*
  %val.i24.i = load i32, i32* %ptrcast.i23.i, align 4
  %updatedret.i30.i = insertelement <8 x i32> undef, i32 %val.i34.i, i32 1
  ret <8 x i32> %updatedret.i30.i
}

;;;; Don't crash on fneg
; rdar://10566486
define <16 x float> @fneg(<16 x float> %a) nounwind {
; CHECK-LABEL: fneg:
; CHECK:       ## BB#0:
; CHECK-NEXT:    vmovaps {{.*#+}} ymm2 = [-0.000000e+00,-0.000000e+00,-0.000000e+00,-0.000000e+00,-0.000000e+00,-0.000000e+00,-0.000000e+00,-0.000000e+00]
; CHECK-NEXT:    vxorps %ymm2, %ymm0, %ymm0
; CHECK-NEXT:    vxorps %ymm2, %ymm1, %ymm1
; CHECK-NEXT:    retq
; CHECK-NEXT:    ## -- End function
  %1 = fsub <16 x float> <float -0.000000e+00, float -0.000000e+00, float -0.000000e+00, float -0.000000e+00, float -0.000000e+00, float -0.000000e+00, float -0.000000e+00, float -0.000000e+00, float -0.000000e+00, float -0.000000e+00, float -0.000000e+00, float -0.000000e+00, float -0.000000e+00, float -0.000000e+00, float -0.000000e+00, float -0.000000e+00>, %a
  ret <16 x float> %1
}

;;; Don't crash on build vector
define <16 x i16> @build_vec_16x16(i16 %a) nounwind readonly {
; CHECK-LABEL: build_vec_16x16:
; CHECK:       ## BB#0:
; CHECK-NEXT:    movzwl %di, %eax
; CHECK-NEXT:    vmovd %eax, %xmm0
; CHECK-NEXT:    retq
; CHECK-NEXT:    ## -- End function
  %res = insertelement <16 x i16> <i16 undef, i16 0, i16 0, i16 0, i16 0, i16 0, i16 0, i16 0, i16 0, i16 0, i16 0, i16 0, i16 0, i16 0, i16 0, i16 0>, i16 %a, i32 0
  ret <16 x i16> %res
}

;;; Check that VMOVPQIto64rr generates the assembly string "vmovq".  Previously
;;; an incorrect mnemonic of "movd" was printed for this instruction.
define i64 @VMOVPQIto64rr(<2 x i64> %a) {
; CHECK-LABEL: VMOVPQIto64rr:
; CHECK:       ## BB#0:
; CHECK-NEXT:    vmovq %xmm0, %rax
; CHECK-NEXT:    retq
  %vecext.i = extractelement <2 x i64> %a, i32 0
  ret i64 %vecext.i
}

; PR22685
define <8 x float> @mov00_8f32(float* %ptr) {
; CHECK-LABEL: mov00_8f32:
; CHECK:       ## BB#0:
; CHECK-NEXT:    vmovss {{.*#+}} xmm0 = mem[0],zero,zero,zero
; CHECK-NEXT:    retq
  %val = load float, float* %ptr
  %vec = insertelement <8 x float> zeroinitializer, float %val, i32 0
  ret <8 x float> %vec
}
