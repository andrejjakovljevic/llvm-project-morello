// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py UTC_ARGS: --function-signature
// RUN: %cheri_purecap_cc1 -DCODEGEN -Wno-tautological-compare -o - -O2 -emit-llvm %s -cheri-uintcap=offset | FileCheck %s -check-prefix=PURECAP
// RUN: %cheri_cc1 -DCODEGEN -Wno-tautological-compare -o - -O2 -emit-llvm %s -cheri-uintcap=offset | FileCheck %s -check-prefix=HYBRID

typedef long vaddr_t;
typedef __UINTPTR_TYPE__ uintptr_t;

#define __static_assert_power_of_two(val)                          \
  _Static_assert(__builtin_choose_expr(__builtin_constant_p(val),  \
                                       (val & (val - 1)) == 0, 1), \
                 "Alignment must be a power-of-two");

#define __macro_is_aligned_array(addr, align) ({                               \
  extern char __check_align_is_power_of_two[__builtin_choose_expr(             \
      __builtin_constant_p(align), ((align & (align - 1)) == 0 ? 1 : -1), 1)]; \
  _Bool result = ((vaddr_t)addr & ((vaddr_t)(align)-1)) == 0;                  \
  result;                                                                      \
})

#define __macro_is_aligned(addr, align) ({                        \
  __static_assert_power_of_two(align)                             \
      _Bool result = ((vaddr_t)addr & ((vaddr_t)(align)-1)) == 0; \
  result;                                                         \
})

// PURECAP-LABEL: define {{[^@]+}}@is_aligned_macro
// PURECAP-SAME: (i32 addrspace(200)* [[PTR:%.*]], i32 signext [[ALIGN:%.*]]) local_unnamed_addr addrspace(200) #0
// PURECAP-NEXT:  entry:
// PURECAP-NEXT:    [[TMP0:%.*]] = bitcast i32 addrspace(200)* [[PTR]] to i8 addrspace(200)*
// PURECAP-NEXT:    [[TMP1:%.*]] = tail call i64 @llvm.cheri.cap.address.get.i64(i8 addrspace(200)* [[TMP0]])
// PURECAP-NEXT:    [[CONV:%.*]] = sext i32 [[ALIGN]] to i64
// PURECAP-NEXT:    [[SUB:%.*]] = add nsw i64 [[CONV]], -1
// PURECAP-NEXT:    [[AND:%.*]] = and i64 [[TMP1]], [[SUB]]
// PURECAP-NEXT:    [[CMP:%.*]] = icmp eq i64 [[AND]], 0
// PURECAP-NEXT:    ret i1 [[CMP]]
//
// HYBRID-LABEL: define {{[^@]+}}@is_aligned_macro
// HYBRID-SAME: (i32* [[PTR:%.*]], i32 signext [[ALIGN:%.*]]) local_unnamed_addr #0
// HYBRID-NEXT:  entry:
// HYBRID-NEXT:    [[TMP0:%.*]] = ptrtoint i32* [[PTR]] to i64
// HYBRID-NEXT:    [[CONV:%.*]] = sext i32 [[ALIGN]] to i64
// HYBRID-NEXT:    [[SUB:%.*]] = add nsw i64 [[CONV]], -1
// HYBRID-NEXT:    [[AND:%.*]] = and i64 [[SUB]], [[TMP0]]
// HYBRID-NEXT:    [[CMP:%.*]] = icmp eq i64 [[AND]], 0
// HYBRID-NEXT:    ret i1 [[CMP]]
//
_Bool is_aligned_macro(int *ptr, int align) {
  return __macro_is_aligned(ptr, align);
}

// PURECAP-LABEL: define {{[^@]+}}@is_aligned_builtin
// PURECAP-SAME: (i32 addrspace(200)* [[PTR:%.*]], i32 signext [[ALIGN:%.*]]) local_unnamed_addr addrspace(200) #0
// PURECAP-NEXT:  entry:
// PURECAP-NEXT:    [[ALIGNMENT:%.*]] = zext i32 [[ALIGN]] to i64
// PURECAP-NEXT:    [[MASK:%.*]] = add nsw i64 [[ALIGNMENT]], -1
// PURECAP-NEXT:    [[TMP0:%.*]] = bitcast i32 addrspace(200)* [[PTR]] to i8 addrspace(200)*
// PURECAP-NEXT:    [[PTRADDR:%.*]] = tail call i64 @llvm.cheri.cap.address.get.i64(i8 addrspace(200)* [[TMP0]])
// PURECAP-NEXT:    [[SET_BITS:%.*]] = and i64 [[PTRADDR]], [[MASK]]
// PURECAP-NEXT:    [[IS_ALIGNED:%.*]] = icmp eq i64 [[SET_BITS]], 0
// PURECAP-NEXT:    ret i1 [[IS_ALIGNED]]
//
// HYBRID-LABEL: define {{[^@]+}}@is_aligned_builtin
// HYBRID-SAME: (i32* [[PTR:%.*]], i32 signext [[ALIGN:%.*]]) local_unnamed_addr #0
// HYBRID-NEXT:  entry:
// HYBRID-NEXT:    [[ALIGNMENT:%.*]] = zext i32 [[ALIGN]] to i64
// HYBRID-NEXT:    [[MASK:%.*]] = add nsw i64 [[ALIGNMENT]], -1
// HYBRID-NEXT:    [[INTPTR:%.*]] = ptrtoint i32* [[PTR]] to i64
// HYBRID-NEXT:    [[SET_BITS:%.*]] = and i64 [[MASK]], [[INTPTR]]
// HYBRID-NEXT:    [[IS_ALIGNED:%.*]] = icmp eq i64 [[SET_BITS]], 0
// HYBRID-NEXT:    ret i1 [[IS_ALIGNED]]
//
_Bool is_aligned_builtin(int *ptr, int align) {
  return __builtin_is_aligned(ptr, align);
}

// PURECAP-LABEL: define {{[^@]+}}@align_up_inline
// PURECAP-SAME: (i32 addrspace(200)* [[PTR:%.*]], i64 signext [[ALIGN:%.*]]) local_unnamed_addr addrspace(200) #0
// PURECAP-NEXT:  entry:
// PURECAP-NEXT:    [[TMP0:%.*]] = bitcast i32 addrspace(200)* [[PTR]] to i8 addrspace(200)*
// PURECAP-NEXT:    [[TMP1:%.*]] = tail call i64 @llvm.cheri.cap.address.get.i64(i8 addrspace(200)* [[TMP0]])
// PURECAP-NEXT:    [[SUB:%.*]] = add nsw i64 [[ALIGN]], -1
// PURECAP-NEXT:    [[AND:%.*]] = and i64 [[TMP1]], [[SUB]]
// PURECAP-NEXT:    [[CMP_NOT:%.*]] = icmp eq i64 [[AND]], 0
// PURECAP-NEXT:    [[SUB1:%.*]] = sub nsw i64 [[ALIGN]], [[AND]]
// PURECAP-NEXT:    [[ADD_PTR:%.*]] = getelementptr inbounds i8, i8 addrspace(200)* [[TMP0]], i64 [[SUB1]]
// PURECAP-NEXT:    [[RESULT_0:%.*]] = select i1 [[CMP_NOT]], i8 addrspace(200)* [[TMP0]], i8 addrspace(200)* [[ADD_PTR]]
// PURECAP-NEXT:    [[TMP2:%.*]] = bitcast i8 addrspace(200)* [[RESULT_0]] to i32 addrspace(200)*
// PURECAP-NEXT:    ret i32 addrspace(200)* [[TMP2]]
//
// HYBRID-LABEL: define {{[^@]+}}@align_up_inline
// HYBRID-SAME: (i32* [[PTR:%.*]], i64 signext [[ALIGN:%.*]]) local_unnamed_addr #0
// HYBRID-NEXT:  entry:
// HYBRID-NEXT:    [[TMP0:%.*]] = bitcast i32* [[PTR]] to i8*
// HYBRID-NEXT:    [[TMP1:%.*]] = ptrtoint i32* [[PTR]] to i64
// HYBRID-NEXT:    [[SUB:%.*]] = add nsw i64 [[ALIGN]], -1
// HYBRID-NEXT:    [[AND:%.*]] = and i64 [[SUB]], [[TMP1]]
// HYBRID-NEXT:    [[CMP_NOT:%.*]] = icmp eq i64 [[AND]], 0
// HYBRID-NEXT:    [[SUB1:%.*]] = sub nsw i64 [[ALIGN]], [[AND]]
// HYBRID-NEXT:    [[ADD_PTR:%.*]] = getelementptr inbounds i8, i8* [[TMP0]], i64 [[SUB1]]
// HYBRID-NEXT:    [[RESULT_0:%.*]] = select i1 [[CMP_NOT]], i8* [[TMP0]], i8* [[ADD_PTR]]
// HYBRID-NEXT:    [[TMP2:%.*]] = bitcast i8* [[RESULT_0]] to i32*
// HYBRID-NEXT:    ret i32* [[TMP2]]
//
int *align_up_inline(int *ptr, vaddr_t align) {
  char *result = (char *)ptr;
  vaddr_t unaligned = (vaddr_t)ptr & (align - 1);
  if (unaligned != 0) {
    result += align - unaligned;
  }
  return (int *)result;
}

#define __macro_align_up(addr, align) ({                                                       \
  __static_assert_power_of_two(align);                                                         \
  vaddr_t unaligned_bits = (vaddr_t)addr & (align - 1);                                        \
  unaligned_bits == 0 ? addr : (__typeof__(addr))((uintptr_t)addr + (align - unaligned_bits)); \
})

// PURECAP-LABEL: define {{[^@]+}}@align_up_macro
// PURECAP-SAME: (i32 addrspace(200)* [[PTR:%.*]], i64 signext [[ALIGN:%.*]]) local_unnamed_addr addrspace(200) #0
// PURECAP-NEXT:  entry:
// PURECAP-NEXT:    [[TMP0:%.*]] = bitcast i32 addrspace(200)* [[PTR]] to i8 addrspace(200)*
// PURECAP-NEXT:    [[TMP1:%.*]] = tail call i64 @llvm.cheri.cap.address.get.i64(i8 addrspace(200)* [[TMP0]])
// PURECAP-NEXT:    [[SUB:%.*]] = add nsw i64 [[ALIGN]], -1
// PURECAP-NEXT:    [[AND:%.*]] = and i64 [[TMP1]], [[SUB]]
// PURECAP-NEXT:    [[CMP:%.*]] = icmp eq i64 [[AND]], 0
// PURECAP-NEXT:    br i1 [[CMP]], label [[COND_END:%.*]], label [[COND_FALSE:%.*]]
// PURECAP:       cond.false:
// PURECAP-NEXT:    [[SUB1:%.*]] = sub i64 [[ALIGN]], [[AND]]
// PURECAP-NEXT:    [[TMP2:%.*]] = tail call i64 @llvm.cheri.cap.offset.get.i64(i8 addrspace(200)* [[TMP0]])
// PURECAP-NEXT:    [[ADD:%.*]] = add i64 [[SUB1]], [[TMP2]]
// PURECAP-NEXT:    [[TMP3:%.*]] = tail call i8 addrspace(200)* @llvm.cheri.cap.offset.set.i64(i8 addrspace(200)* [[TMP0]], i64 [[ADD]])
// PURECAP-NEXT:    [[TMP4:%.*]] = bitcast i8 addrspace(200)* [[TMP3]] to i32 addrspace(200)*
// PURECAP-NEXT:    br label [[COND_END]]
// PURECAP:       cond.end:
// PURECAP-NEXT:    [[COND:%.*]] = phi i32 addrspace(200)* [ [[TMP4]], [[COND_FALSE]] ], [ [[PTR]], [[ENTRY:%.*]] ]
// PURECAP-NEXT:    ret i32 addrspace(200)* [[COND]]
//
// HYBRID-LABEL: define {{[^@]+}}@align_up_macro
// HYBRID-SAME: (i32* [[PTR:%.*]], i64 signext [[ALIGN:%.*]]) local_unnamed_addr #0
// HYBRID-NEXT:  entry:
// HYBRID-NEXT:    [[TMP0:%.*]] = ptrtoint i32* [[PTR]] to i64
// HYBRID-NEXT:    [[SUB:%.*]] = add nsw i64 [[ALIGN]], -1
// HYBRID-NEXT:    [[AND:%.*]] = and i64 [[SUB]], [[TMP0]]
// HYBRID-NEXT:    [[CMP:%.*]] = icmp eq i64 [[AND]], 0
// HYBRID-NEXT:    [[SUB1:%.*]] = add i64 [[TMP0]], [[ALIGN]]
// HYBRID-NEXT:    [[ADD:%.*]] = sub i64 [[SUB1]], [[AND]]
// HYBRID-NEXT:    [[TMP1:%.*]] = inttoptr i64 [[ADD]] to i32*
// HYBRID-NEXT:    [[COND:%.*]] = select i1 [[CMP]], i32* [[PTR]], i32* [[TMP1]]
// HYBRID-NEXT:    ret i32* [[COND]]
//
int *align_up_macro(int *ptr, vaddr_t align) {
  return __macro_align_up(ptr, align);
}

// PURECAP-LABEL: define {{[^@]+}}@align_up_builtin
// PURECAP-SAME: (i32 addrspace(200)* [[PTR:%.*]], i64 signext [[ALIGN:%.*]]) local_unnamed_addr addrspace(200) #2
// PURECAP-NEXT:  entry:
// PURECAP-NEXT:    [[MASK:%.*]] = add i64 [[ALIGN]], -1
// PURECAP-NEXT:    [[TMP0:%.*]] = bitcast i32 addrspace(200)* [[PTR]] to i8 addrspace(200)*
// PURECAP-NEXT:    [[PTRADDR:%.*]] = tail call i64 @llvm.cheri.cap.address.get.i64(i8 addrspace(200)* [[TMP0]])
// PURECAP-NEXT:    [[OVER_BOUNDARY:%.*]] = add i64 [[MASK]], [[PTRADDR]]
// PURECAP-NEXT:    [[INVERTED_MASK:%.*]] = sub i64 0, [[ALIGN]]
// PURECAP-NEXT:    [[ALIGNED_INTPTR:%.*]] = and i64 [[OVER_BOUNDARY]], [[INVERTED_MASK]]
// PURECAP-NEXT:    [[DIFF:%.*]] = sub i64 [[ALIGNED_INTPTR]], [[PTRADDR]]
// PURECAP-NEXT:    [[ALIGNED_RESULT:%.*]] = getelementptr inbounds i8, i8 addrspace(200)* [[TMP0]], i64 [[DIFF]]
// PURECAP-NEXT:    [[TMP1:%.*]] = bitcast i8 addrspace(200)* [[ALIGNED_RESULT]] to i32 addrspace(200)*
// PURECAP-NEXT:    call void @llvm.assume(i1 true) [ "align"(i32 addrspace(200)* [[TMP1]], i64 [[ALIGN]]) ]
// PURECAP-NEXT:    ret i32 addrspace(200)* [[TMP1]]
//
// HYBRID-LABEL: define {{[^@]+}}@align_up_builtin
// HYBRID-SAME: (i32* [[PTR:%.*]], i64 signext [[ALIGN:%.*]]) local_unnamed_addr #1
// HYBRID-NEXT:  entry:
// HYBRID-NEXT:    [[MASK:%.*]] = add i64 [[ALIGN]], -1
// HYBRID-NEXT:    [[INTPTR:%.*]] = ptrtoint i32* [[PTR]] to i64
// HYBRID-NEXT:    [[OVER_BOUNDARY:%.*]] = add i64 [[MASK]], [[INTPTR]]
// HYBRID-NEXT:    [[INVERTED_MASK:%.*]] = sub i64 0, [[ALIGN]]
// HYBRID-NEXT:    [[ALIGNED_INTPTR:%.*]] = and i64 [[OVER_BOUNDARY]], [[INVERTED_MASK]]
// HYBRID-NEXT:    [[DIFF:%.*]] = sub i64 [[ALIGNED_INTPTR]], [[INTPTR]]
// HYBRID-NEXT:    [[TMP0:%.*]] = bitcast i32* [[PTR]] to i8*
// HYBRID-NEXT:    [[ALIGNED_RESULT:%.*]] = getelementptr inbounds i8, i8* [[TMP0]], i64 [[DIFF]]
// HYBRID-NEXT:    [[TMP1:%.*]] = bitcast i8* [[ALIGNED_RESULT]] to i32*
// HYBRID-NEXT:    call void @llvm.assume(i1 true) [ "align"(i32* [[TMP1]], i64 [[ALIGN]]) ]
// HYBRID-NEXT:    ret i32* [[TMP1]]
//
int *align_up_builtin(int *ptr, vaddr_t align) {
  return __builtin_align_up(ptr, align);
}

// PURECAP-LABEL: define {{[^@]+}}@align_up_macro_int_type
// PURECAP-SAME: (i64 signext [[ADDR:%.*]], i64 signext [[ALIGN:%.*]]) local_unnamed_addr addrspace(200) #4
// PURECAP-NEXT:  entry:
// PURECAP-NEXT:    [[SUB:%.*]] = add nsw i64 [[ALIGN]], -1
// PURECAP-NEXT:    [[AND:%.*]] = and i64 [[SUB]], [[ADDR]]
// PURECAP-NEXT:    [[CMP:%.*]] = icmp eq i64 [[AND]], 0
// PURECAP-NEXT:    [[SUB1:%.*]] = sub nsw i64 [[ALIGN]], [[AND]]
// PURECAP-NEXT:    [[ADD:%.*]] = select i1 [[CMP]], i64 0, i64 [[SUB1]]
// PURECAP-NEXT:    [[COND:%.*]] = add i64 [[ADD]], [[ADDR]]
// PURECAP-NEXT:    ret i64 [[COND]]
//
// HYBRID-LABEL: define {{[^@]+}}@align_up_macro_int_type
// HYBRID-SAME: (i64 signext [[ADDR:%.*]], i64 signext [[ALIGN:%.*]]) local_unnamed_addr #0
// HYBRID-NEXT:  entry:
// HYBRID-NEXT:    [[SUB:%.*]] = add nsw i64 [[ALIGN]], -1
// HYBRID-NEXT:    [[AND:%.*]] = and i64 [[SUB]], [[ADDR]]
// HYBRID-NEXT:    [[CMP:%.*]] = icmp eq i64 [[AND]], 0
// HYBRID-NEXT:    [[SUB1:%.*]] = sub nsw i64 [[ALIGN]], [[AND]]
// HYBRID-NEXT:    [[ADD:%.*]] = select i1 [[CMP]], i64 0, i64 [[SUB1]]
// HYBRID-NEXT:    [[COND:%.*]] = add i64 [[ADD]], [[ADDR]]
// HYBRID-NEXT:    ret i64 [[COND]]
//
vaddr_t align_up_macro_int_type(vaddr_t addr, vaddr_t align) {
  return __macro_align_up(addr, align);
}

// PURECAP-LABEL: define {{[^@]+}}@align_up_builtin_int_type
// PURECAP-SAME: (i64 signext [[ADDR:%.*]], i64 signext [[ALIGN:%.*]]) local_unnamed_addr addrspace(200) #4
// PURECAP-NEXT:  entry:
// PURECAP-NEXT:    [[MASK:%.*]] = add i64 [[ADDR]], -1
// PURECAP-NEXT:    [[OVER_BOUNDARY:%.*]] = add i64 [[MASK]], [[ALIGN]]
// PURECAP-NEXT:    [[INVERTED_MASK:%.*]] = sub i64 0, [[ALIGN]]
// PURECAP-NEXT:    [[ALIGNED_RESULT:%.*]] = and i64 [[OVER_BOUNDARY]], [[INVERTED_MASK]]
// PURECAP-NEXT:    ret i64 [[ALIGNED_RESULT]]
//
// HYBRID-LABEL: define {{[^@]+}}@align_up_builtin_int_type
// HYBRID-SAME: (i64 signext [[ADDR:%.*]], i64 signext [[ALIGN:%.*]]) local_unnamed_addr #0
// HYBRID-NEXT:  entry:
// HYBRID-NEXT:    [[MASK:%.*]] = add i64 [[ADDR]], -1
// HYBRID-NEXT:    [[OVER_BOUNDARY:%.*]] = add i64 [[MASK]], [[ALIGN]]
// HYBRID-NEXT:    [[INVERTED_MASK:%.*]] = sub i64 0, [[ALIGN]]
// HYBRID-NEXT:    [[ALIGNED_RESULT:%.*]] = and i64 [[OVER_BOUNDARY]], [[INVERTED_MASK]]
// HYBRID-NEXT:    ret i64 [[ALIGNED_RESULT]]
//
vaddr_t align_up_builtin_int_type(vaddr_t addr, vaddr_t align) {
  return __builtin_align_up(addr, align);
}

// PURECAP-LABEL: define {{[^@]+}}@align_up_macro_const() local_unnamed_addr addrspace(200) #4
// PURECAP-NEXT:  entry:
// PURECAP-NEXT:    ret i32 64
//
// HYBRID-LABEL: define {{[^@]+}}@align_up_macro_const() local_unnamed_addr #0
// HYBRID-NEXT:  entry:
// HYBRID-NEXT:    ret i32 64
//
int align_up_macro_const() {
  return __macro_align_up(31, 64);
}

// PURECAP-LABEL: define {{[^@]+}}@align_up_builtin_const() local_unnamed_addr addrspace(200) #4
// PURECAP-NEXT:  entry:
// PURECAP-NEXT:    ret i32 64
//
// HYBRID-LABEL: define {{[^@]+}}@align_up_builtin_const() local_unnamed_addr #0
// HYBRID-NEXT:  entry:
// HYBRID-NEXT:    ret i32 64
//
int align_up_builtin_const() {
  return __builtin_align_up(31, 64);
}

#define __macro_align_down(addr, align) ({              \
  __static_assert_power_of_two(align);                  \
  vaddr_t unaligned_bits = (vaddr_t)addr & (align - 1); \
  (__typeof__(addr))((uintptr_t)addr - unaligned_bits); \
})

// PURECAP-LABEL: define {{[^@]+}}@align_down_macro
// PURECAP-SAME: (i32 addrspace(200)* [[PTR:%.*]], i64 signext [[ALIGN:%.*]]) local_unnamed_addr addrspace(200) #0
// PURECAP-NEXT:  entry:
// PURECAP-NEXT:    [[TMP0:%.*]] = bitcast i32 addrspace(200)* [[PTR]] to i8 addrspace(200)*
// PURECAP-NEXT:    [[TMP1:%.*]] = tail call i64 @llvm.cheri.cap.address.get.i64(i8 addrspace(200)* [[TMP0]])
// PURECAP-NEXT:    [[SUB:%.*]] = add nsw i64 [[ALIGN]], -1
// PURECAP-NEXT:    [[AND:%.*]] = and i64 [[TMP1]], [[SUB]]
// PURECAP-NEXT:    [[TMP2:%.*]] = tail call i64 @llvm.cheri.cap.offset.get.i64(i8 addrspace(200)* [[TMP0]])
// PURECAP-NEXT:    [[SUB1:%.*]] = sub i64 [[TMP2]], [[AND]]
// PURECAP-NEXT:    [[TMP3:%.*]] = tail call i8 addrspace(200)* @llvm.cheri.cap.offset.set.i64(i8 addrspace(200)* [[TMP0]], i64 [[SUB1]])
// PURECAP-NEXT:    [[TMP4:%.*]] = bitcast i8 addrspace(200)* [[TMP3]] to i32 addrspace(200)*
// PURECAP-NEXT:    ret i32 addrspace(200)* [[TMP4]]
//
// HYBRID-LABEL: define {{[^@]+}}@align_down_macro
// HYBRID-SAME: (i32* [[PTR:%.*]], i64 signext [[ALIGN:%.*]]) local_unnamed_addr #0
// HYBRID-NEXT:  entry:
// HYBRID-NEXT:    [[TMP0:%.*]] = ptrtoint i32* [[PTR]] to i64
// HYBRID-NEXT:    [[SUB_NOT:%.*]] = sub i64 0, [[ALIGN]]
// HYBRID-NEXT:    [[SUB1:%.*]] = and i64 [[TMP0]], [[SUB_NOT]]
// HYBRID-NEXT:    [[TMP1:%.*]] = inttoptr i64 [[SUB1]] to i32*
// HYBRID-NEXT:    ret i32* [[TMP1]]
//
int *align_down_macro(int *ptr, vaddr_t align) {
  return __macro_align_down(ptr, align);
}

// PURECAP-LABEL: define {{[^@]+}}@align_down_builtin
// PURECAP-SAME: (i32 addrspace(200)* [[PTR:%.*]], i64 signext [[ALIGN:%.*]]) local_unnamed_addr addrspace(200) #2
// PURECAP-NEXT:  entry:
// PURECAP-NEXT:    [[TMP0:%.*]] = bitcast i32 addrspace(200)* [[PTR]] to i8 addrspace(200)*
// PURECAP-NEXT:    [[PTRADDR:%.*]] = tail call i64 @llvm.cheri.cap.address.get.i64(i8 addrspace(200)* [[TMP0]])
// PURECAP-NEXT:    [[TMP1:%.*]] = add i64 [[ALIGN]], -1
// PURECAP-NEXT:    [[TMP2:%.*]] = and i64 [[PTRADDR]], [[TMP1]]
// PURECAP-NEXT:    [[DIFF:%.*]] = sub i64 0, [[TMP2]]
// PURECAP-NEXT:    [[ALIGNED_RESULT:%.*]] = getelementptr inbounds i8, i8 addrspace(200)* [[TMP0]], i64 [[DIFF]]
// PURECAP-NEXT:    [[TMP3:%.*]] = bitcast i8 addrspace(200)* [[ALIGNED_RESULT]] to i32 addrspace(200)*
// PURECAP-NEXT:    call void @llvm.assume(i1 true) [ "align"(i32 addrspace(200)* [[TMP3]], i64 [[ALIGN]]) ]
// PURECAP-NEXT:    ret i32 addrspace(200)* [[TMP3]]
//
// HYBRID-LABEL: define {{[^@]+}}@align_down_builtin
// HYBRID-SAME: (i32* [[PTR:%.*]], i64 signext [[ALIGN:%.*]]) local_unnamed_addr #1
// HYBRID-NEXT:  entry:
// HYBRID-NEXT:    [[INTPTR:%.*]] = ptrtoint i32* [[PTR]] to i64
// HYBRID-NEXT:    [[TMP0:%.*]] = add i64 [[ALIGN]], -1
// HYBRID-NEXT:    [[TMP1:%.*]] = and i64 [[TMP0]], [[INTPTR]]
// HYBRID-NEXT:    [[DIFF:%.*]] = sub i64 0, [[TMP1]]
// HYBRID-NEXT:    [[TMP2:%.*]] = bitcast i32* [[PTR]] to i8*
// HYBRID-NEXT:    [[ALIGNED_RESULT:%.*]] = getelementptr inbounds i8, i8* [[TMP2]], i64 [[DIFF]]
// HYBRID-NEXT:    [[TMP3:%.*]] = bitcast i8* [[ALIGNED_RESULT]] to i32*
// HYBRID-NEXT:    call void @llvm.assume(i1 true) [ "align"(i32* [[TMP3]], i64 [[ALIGN]]) ]
// HYBRID-NEXT:    ret i32* [[TMP3]]
//
int *align_down_builtin(int *ptr, vaddr_t align) {
  return __builtin_align_down(ptr, align);
}

// PURECAP-LABEL: define {{[^@]+}}@align_down_macro_int_type
// PURECAP-SAME: (i64 signext [[ADDR:%.*]], i64 signext [[ALIGN:%.*]]) local_unnamed_addr addrspace(200) #4
// PURECAP-NEXT:  entry:
// PURECAP-NEXT:    [[SUB_NOT:%.*]] = sub i64 0, [[ALIGN]]
// PURECAP-NEXT:    [[SUB1:%.*]] = and i64 [[SUB_NOT]], [[ADDR]]
// PURECAP-NEXT:    ret i64 [[SUB1]]
//
// HYBRID-LABEL: define {{[^@]+}}@align_down_macro_int_type
// HYBRID-SAME: (i64 signext [[ADDR:%.*]], i64 signext [[ALIGN:%.*]]) local_unnamed_addr #0
// HYBRID-NEXT:  entry:
// HYBRID-NEXT:    [[SUB_NOT:%.*]] = sub i64 0, [[ALIGN]]
// HYBRID-NEXT:    [[SUB1:%.*]] = and i64 [[SUB_NOT]], [[ADDR]]
// HYBRID-NEXT:    ret i64 [[SUB1]]
//
vaddr_t align_down_macro_int_type(vaddr_t addr, vaddr_t align) {
  return __macro_align_down(addr, align);
}

// PURECAP-LABEL: define {{[^@]+}}@align_down_builtin_int_type
// PURECAP-SAME: (i64 signext [[ADDR:%.*]], i64 signext [[ALIGN:%.*]]) local_unnamed_addr addrspace(200) #4
// PURECAP-NEXT:  entry:
// PURECAP-NEXT:    [[INVERTED_MASK:%.*]] = sub i64 0, [[ALIGN]]
// PURECAP-NEXT:    [[ALIGNED_RESULT:%.*]] = and i64 [[INVERTED_MASK]], [[ADDR]]
// PURECAP-NEXT:    ret i64 [[ALIGNED_RESULT]]
//
// HYBRID-LABEL: define {{[^@]+}}@align_down_builtin_int_type
// HYBRID-SAME: (i64 signext [[ADDR:%.*]], i64 signext [[ALIGN:%.*]]) local_unnamed_addr #0
// HYBRID-NEXT:  entry:
// HYBRID-NEXT:    [[INVERTED_MASK:%.*]] = sub i64 0, [[ALIGN]]
// HYBRID-NEXT:    [[ALIGNED_RESULT:%.*]] = and i64 [[INVERTED_MASK]], [[ADDR]]
// HYBRID-NEXT:    ret i64 [[ALIGNED_RESULT]]
//
vaddr_t align_down_builtin_int_type(vaddr_t addr, vaddr_t align) {
  return __builtin_align_down(addr, align);
}

// PURECAP-LABEL: define {{[^@]+}}@align_down_macro_const() local_unnamed_addr addrspace(200) #4
// PURECAP-NEXT:  entry:
// PURECAP-NEXT:    ret i32 64
//
// HYBRID-LABEL: define {{[^@]+}}@align_down_macro_const() local_unnamed_addr #0
// HYBRID-NEXT:  entry:
// HYBRID-NEXT:    ret i32 64
//
int align_down_macro_const() {
  return __macro_align_down(65, 32);
}

// PURECAP-LABEL: define {{[^@]+}}@align_down_builtin_const() local_unnamed_addr addrspace(200) #4
// PURECAP-NEXT:  entry:
// PURECAP-NEXT:    ret i32 64
//
// HYBRID-LABEL: define {{[^@]+}}@align_down_builtin_const() local_unnamed_addr #0
// HYBRID-NEXT:  entry:
// HYBRID-NEXT:    ret i32 64
//
int align_down_builtin_const() {
  return __builtin_align_down(65, 32);
}

#ifndef CODEGEN
void bad_align_macro(int *ptr) {
  (void)__macro_is_aligned_array(ptr, 7); // expected-error {{'__check_align_is_power_of_two' declared as an array with a negative size}}
  (void)__macro_is_aligned(ptr, 7);       // expected-error {{static_assert failed due to requirement '(7 & (7 - 1)) == 0' "Alignment must be a power-of-two"}}
  (void)__macro_align_up(ptr, 7);         // expected-error {{static_assert failed due to requirement '(7 & (7 - 1)) == 0' "Alignment must be a power-of-two"}}
  (void)__macro_align_down(ptr, 7);       // expected-error {{static_assert failed due to requirement '(7 & (7 - 1)) == 0' "Alignment must be a power-of-two"}}
}

_Bool bad_align_builtin(int *ptr) {
  (void)__builtin_is_aligned(ptr, 7); // expected-error {{requested alignment is not a power of 2}}
  (void)__builtin_align_up(ptr, 7);   // expected-error {{requested alignment is not a power of 2}}
  (void)__builtin_align_down(ptr, 7); // expected-error {{requested alignment is not a power of 2}}
}
#endif
