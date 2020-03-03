// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py
// RUN: %clang_cc1 -triple thumbv8.1m.main-arm-none-eabi -target-feature +mve -mfloat-abi hard -fallow-half-arguments-and-returns -O0 -disable-O0-optnone -S -emit-llvm -o - %s | opt -S -mem2reg | FileCheck %s
// RUN: %clang_cc1 -triple thumbv8.1m.main-arm-none-eabi -target-feature +mve -mfloat-abi hard -fallow-half-arguments-and-returns -O0 -disable-O0-optnone -DPOLYMORPHIC -S -emit-llvm -o - %s | opt -S -mem2reg | FileCheck %s

#include <arm_mve.h>

// CHECK-LABEL: @test_vshlcq_s8(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* [[B:%.*]], align 4
// CHECK-NEXT:    [[TMP1:%.*]] = call { i32, <16 x i8> } @llvm.arm.mve.vshlc.v16i8(<16 x i8> [[A:%.*]], i32 [[TMP0]], i32 18)
// CHECK-NEXT:    [[TMP2:%.*]] = extractvalue { i32, <16 x i8> } [[TMP1]], 0
// CHECK-NEXT:    store i32 [[TMP2]], i32* [[B]], align 4
// CHECK-NEXT:    [[TMP3:%.*]] = extractvalue { i32, <16 x i8> } [[TMP1]], 1
// CHECK-NEXT:    ret <16 x i8> [[TMP3]]
//
int8x16_t test_vshlcq_s8(int8x16_t a, uint32_t *b) {
#ifdef POLYMORPHIC
  return vshlcq(a, b, 18);
#else  /* POLYMORPHIC */
  return vshlcq_s8(a, b, 18);
#endif /* POLYMORPHIC */
}

// CHECK-LABEL: @test_vshlcq_s16(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* [[B:%.*]], align 4
// CHECK-NEXT:    [[TMP1:%.*]] = call { i32, <8 x i16> } @llvm.arm.mve.vshlc.v8i16(<8 x i16> [[A:%.*]], i32 [[TMP0]], i32 16)
// CHECK-NEXT:    [[TMP2:%.*]] = extractvalue { i32, <8 x i16> } [[TMP1]], 0
// CHECK-NEXT:    store i32 [[TMP2]], i32* [[B]], align 4
// CHECK-NEXT:    [[TMP3:%.*]] = extractvalue { i32, <8 x i16> } [[TMP1]], 1
// CHECK-NEXT:    ret <8 x i16> [[TMP3]]
//
int16x8_t test_vshlcq_s16(int16x8_t a, uint32_t *b) {
#ifdef POLYMORPHIC
  return vshlcq(a, b, 16);
#else  /* POLYMORPHIC */
  return vshlcq_s16(a, b, 16);
#endif /* POLYMORPHIC */
}

// CHECK-LABEL: @test_vshlcq_s32(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* [[B:%.*]], align 4
// CHECK-NEXT:    [[TMP1:%.*]] = call { i32, <4 x i32> } @llvm.arm.mve.vshlc.v4i32(<4 x i32> [[A:%.*]], i32 [[TMP0]], i32 4)
// CHECK-NEXT:    [[TMP2:%.*]] = extractvalue { i32, <4 x i32> } [[TMP1]], 0
// CHECK-NEXT:    store i32 [[TMP2]], i32* [[B]], align 4
// CHECK-NEXT:    [[TMP3:%.*]] = extractvalue { i32, <4 x i32> } [[TMP1]], 1
// CHECK-NEXT:    ret <4 x i32> [[TMP3]]
//
int32x4_t test_vshlcq_s32(int32x4_t a, uint32_t *b) {
#ifdef POLYMORPHIC
  return vshlcq(a, b, 4);
#else  /* POLYMORPHIC */
  return vshlcq_s32(a, b, 4);
#endif /* POLYMORPHIC */
}

// CHECK-LABEL: @test_vshlcq_u8(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* [[B:%.*]], align 4
// CHECK-NEXT:    [[TMP1:%.*]] = call { i32, <16 x i8> } @llvm.arm.mve.vshlc.v16i8(<16 x i8> [[A:%.*]], i32 [[TMP0]], i32 17)
// CHECK-NEXT:    [[TMP2:%.*]] = extractvalue { i32, <16 x i8> } [[TMP1]], 0
// CHECK-NEXT:    store i32 [[TMP2]], i32* [[B]], align 4
// CHECK-NEXT:    [[TMP3:%.*]] = extractvalue { i32, <16 x i8> } [[TMP1]], 1
// CHECK-NEXT:    ret <16 x i8> [[TMP3]]
//
uint8x16_t test_vshlcq_u8(uint8x16_t a, uint32_t *b) {
#ifdef POLYMORPHIC
  return vshlcq(a, b, 17);
#else  /* POLYMORPHIC */
  return vshlcq_u8(a, b, 17);
#endif /* POLYMORPHIC */
}

// CHECK-LABEL: @test_vshlcq_u16(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* [[B:%.*]], align 4
// CHECK-NEXT:    [[TMP1:%.*]] = call { i32, <8 x i16> } @llvm.arm.mve.vshlc.v8i16(<8 x i16> [[A:%.*]], i32 [[TMP0]], i32 17)
// CHECK-NEXT:    [[TMP2:%.*]] = extractvalue { i32, <8 x i16> } [[TMP1]], 0
// CHECK-NEXT:    store i32 [[TMP2]], i32* [[B]], align 4
// CHECK-NEXT:    [[TMP3:%.*]] = extractvalue { i32, <8 x i16> } [[TMP1]], 1
// CHECK-NEXT:    ret <8 x i16> [[TMP3]]
//
uint16x8_t test_vshlcq_u16(uint16x8_t a, uint32_t *b) {
#ifdef POLYMORPHIC
  return vshlcq(a, b, 17);
#else  /* POLYMORPHIC */
  return vshlcq_u16(a, b, 17);
#endif /* POLYMORPHIC */
}

// CHECK-LABEL: @test_vshlcq_u32(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* [[B:%.*]], align 4
// CHECK-NEXT:    [[TMP1:%.*]] = call { i32, <4 x i32> } @llvm.arm.mve.vshlc.v4i32(<4 x i32> [[A:%.*]], i32 [[TMP0]], i32 20)
// CHECK-NEXT:    [[TMP2:%.*]] = extractvalue { i32, <4 x i32> } [[TMP1]], 0
// CHECK-NEXT:    store i32 [[TMP2]], i32* [[B]], align 4
// CHECK-NEXT:    [[TMP3:%.*]] = extractvalue { i32, <4 x i32> } [[TMP1]], 1
// CHECK-NEXT:    ret <4 x i32> [[TMP3]]
//
uint32x4_t test_vshlcq_u32(uint32x4_t a, uint32_t *b) {
#ifdef POLYMORPHIC
  return vshlcq(a, b, 20);
#else  /* POLYMORPHIC */
  return vshlcq_u32(a, b, 20);
#endif /* POLYMORPHIC */
}

// CHECK-LABEL: @test_vshlcq_m_s8(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* [[B:%.*]], align 4
// CHECK-NEXT:    [[TMP1:%.*]] = zext i16 [[P:%.*]] to i32
// CHECK-NEXT:    [[TMP2:%.*]] = call <16 x i1> @llvm.arm.mve.pred.i2v.v16i1(i32 [[TMP1]])
// CHECK-NEXT:    [[TMP3:%.*]] = call { i32, <16 x i8> } @llvm.arm.mve.vshlc.predicated.v16i8.v16i1(<16 x i8> [[A:%.*]], i32 [[TMP0]], i32 29, <16 x i1> [[TMP2]])
// CHECK-NEXT:    [[TMP4:%.*]] = extractvalue { i32, <16 x i8> } [[TMP3]], 0
// CHECK-NEXT:    store i32 [[TMP4]], i32* [[B]], align 4
// CHECK-NEXT:    [[TMP5:%.*]] = extractvalue { i32, <16 x i8> } [[TMP3]], 1
// CHECK-NEXT:    ret <16 x i8> [[TMP5]]
//
int8x16_t test_vshlcq_m_s8(int8x16_t a, uint32_t *b, mve_pred16_t p) {
#ifdef POLYMORPHIC
  return vshlcq_m(a, b, 29, p);
#else  /* POLYMORPHIC */
  return vshlcq_m_s8(a, b, 29, p);
#endif /* POLYMORPHIC */
}

// CHECK-LABEL: @test_vshlcq_m_s16(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* [[B:%.*]], align 4
// CHECK-NEXT:    [[TMP1:%.*]] = zext i16 [[P:%.*]] to i32
// CHECK-NEXT:    [[TMP2:%.*]] = call <8 x i1> @llvm.arm.mve.pred.i2v.v8i1(i32 [[TMP1]])
// CHECK-NEXT:    [[TMP3:%.*]] = call { i32, <8 x i16> } @llvm.arm.mve.vshlc.predicated.v8i16.v8i1(<8 x i16> [[A:%.*]], i32 [[TMP0]], i32 17, <8 x i1> [[TMP2]])
// CHECK-NEXT:    [[TMP4:%.*]] = extractvalue { i32, <8 x i16> } [[TMP3]], 0
// CHECK-NEXT:    store i32 [[TMP4]], i32* [[B]], align 4
// CHECK-NEXT:    [[TMP5:%.*]] = extractvalue { i32, <8 x i16> } [[TMP3]], 1
// CHECK-NEXT:    ret <8 x i16> [[TMP5]]
//
int16x8_t test_vshlcq_m_s16(int16x8_t a, uint32_t *b, mve_pred16_t p) {
#ifdef POLYMORPHIC
  return vshlcq_m(a, b, 17, p);
#else  /* POLYMORPHIC */
  return vshlcq_m_s16(a, b, 17, p);
#endif /* POLYMORPHIC */
}

// CHECK-LABEL: @test_vshlcq_m_s32(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* [[B:%.*]], align 4
// CHECK-NEXT:    [[TMP1:%.*]] = zext i16 [[P:%.*]] to i32
// CHECK-NEXT:    [[TMP2:%.*]] = call <4 x i1> @llvm.arm.mve.pred.i2v.v4i1(i32 [[TMP1]])
// CHECK-NEXT:    [[TMP3:%.*]] = call { i32, <4 x i32> } @llvm.arm.mve.vshlc.predicated.v4i32.v4i1(<4 x i32> [[A:%.*]], i32 [[TMP0]], i32 9, <4 x i1> [[TMP2]])
// CHECK-NEXT:    [[TMP4:%.*]] = extractvalue { i32, <4 x i32> } [[TMP3]], 0
// CHECK-NEXT:    store i32 [[TMP4]], i32* [[B]], align 4
// CHECK-NEXT:    [[TMP5:%.*]] = extractvalue { i32, <4 x i32> } [[TMP3]], 1
// CHECK-NEXT:    ret <4 x i32> [[TMP5]]
//
int32x4_t test_vshlcq_m_s32(int32x4_t a, uint32_t *b, mve_pred16_t p) {
#ifdef POLYMORPHIC
  return vshlcq_m(a, b, 9, p);
#else  /* POLYMORPHIC */
  return vshlcq_m_s32(a, b, 9, p);
#endif /* POLYMORPHIC */
}

// CHECK-LABEL: @test_vshlcq_m_u8(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* [[B:%.*]], align 4
// CHECK-NEXT:    [[TMP1:%.*]] = zext i16 [[P:%.*]] to i32
// CHECK-NEXT:    [[TMP2:%.*]] = call <16 x i1> @llvm.arm.mve.pred.i2v.v16i1(i32 [[TMP1]])
// CHECK-NEXT:    [[TMP3:%.*]] = call { i32, <16 x i8> } @llvm.arm.mve.vshlc.predicated.v16i8.v16i1(<16 x i8> [[A:%.*]], i32 [[TMP0]], i32 21, <16 x i1> [[TMP2]])
// CHECK-NEXT:    [[TMP4:%.*]] = extractvalue { i32, <16 x i8> } [[TMP3]], 0
// CHECK-NEXT:    store i32 [[TMP4]], i32* [[B]], align 4
// CHECK-NEXT:    [[TMP5:%.*]] = extractvalue { i32, <16 x i8> } [[TMP3]], 1
// CHECK-NEXT:    ret <16 x i8> [[TMP5]]
//
uint8x16_t test_vshlcq_m_u8(uint8x16_t a, uint32_t *b, mve_pred16_t p) {
#ifdef POLYMORPHIC
  return vshlcq_m(a, b, 21, p);
#else  /* POLYMORPHIC */
  return vshlcq_m_u8(a, b, 21, p);
#endif /* POLYMORPHIC */
}

// CHECK-LABEL: @test_vshlcq_m_u16(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* [[B:%.*]], align 4
// CHECK-NEXT:    [[TMP1:%.*]] = zext i16 [[P:%.*]] to i32
// CHECK-NEXT:    [[TMP2:%.*]] = call <8 x i1> @llvm.arm.mve.pred.i2v.v8i1(i32 [[TMP1]])
// CHECK-NEXT:    [[TMP3:%.*]] = call { i32, <8 x i16> } @llvm.arm.mve.vshlc.predicated.v8i16.v8i1(<8 x i16> [[A:%.*]], i32 [[TMP0]], i32 24, <8 x i1> [[TMP2]])
// CHECK-NEXT:    [[TMP4:%.*]] = extractvalue { i32, <8 x i16> } [[TMP3]], 0
// CHECK-NEXT:    store i32 [[TMP4]], i32* [[B]], align 4
// CHECK-NEXT:    [[TMP5:%.*]] = extractvalue { i32, <8 x i16> } [[TMP3]], 1
// CHECK-NEXT:    ret <8 x i16> [[TMP5]]
//
uint16x8_t test_vshlcq_m_u16(uint16x8_t a, uint32_t *b, mve_pred16_t p) {
#ifdef POLYMORPHIC
  return vshlcq_m(a, b, 24, p);
#else  /* POLYMORPHIC */
  return vshlcq_m_u16(a, b, 24, p);
#endif /* POLYMORPHIC */
}

// CHECK-LABEL: @test_vshlcq_m_u32(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* [[B:%.*]], align 4
// CHECK-NEXT:    [[TMP1:%.*]] = zext i16 [[P:%.*]] to i32
// CHECK-NEXT:    [[TMP2:%.*]] = call <4 x i1> @llvm.arm.mve.pred.i2v.v4i1(i32 [[TMP1]])
// CHECK-NEXT:    [[TMP3:%.*]] = call { i32, <4 x i32> } @llvm.arm.mve.vshlc.predicated.v4i32.v4i1(<4 x i32> [[A:%.*]], i32 [[TMP0]], i32 26, <4 x i1> [[TMP2]])
// CHECK-NEXT:    [[TMP4:%.*]] = extractvalue { i32, <4 x i32> } [[TMP3]], 0
// CHECK-NEXT:    store i32 [[TMP4]], i32* [[B]], align 4
// CHECK-NEXT:    [[TMP5:%.*]] = extractvalue { i32, <4 x i32> } [[TMP3]], 1
// CHECK-NEXT:    ret <4 x i32> [[TMP5]]
//
uint32x4_t test_vshlcq_m_u32(uint32x4_t a, uint32_t *b, mve_pred16_t p) {
#ifdef POLYMORPHIC
  return vshlcq_m(a, b, 26, p);
#else  /* POLYMORPHIC */
  return vshlcq_m_u32(a, b, 26, p);
#endif /* POLYMORPHIC */
}
