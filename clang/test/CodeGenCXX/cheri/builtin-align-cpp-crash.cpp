// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py UTC_ARGS: --function-signature
// RUN: %cheri_purecap_cc1 -o - -O2 -emit-llvm  %s | FileCheck %s
// Found while trying to use the builtin in QtBase
// CHECK-LABEL: define {{[^@]+}}@test1
// CHECK-SAME: (i8 addrspace(200)* [[C:%.*]], i32 signext [[B:%.*]]) local_unnamed_addr addrspace(200) #0
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[ALIGNMENT:%.*]] = zext i32 [[B]] to i64
// CHECK-NEXT:    [[PTRADDR:%.*]] = tail call i64 @llvm.cheri.cap.address.get.i64(i8 addrspace(200)* [[C]])
// CHECK-NEXT:    [[TMP0:%.*]] = add nsw i64 [[ALIGNMENT]], -1
// CHECK-NEXT:    [[TMP1:%.*]] = and i64 [[PTRADDR]], [[TMP0]]
// CHECK-NEXT:    [[DIFF:%.*]] = sub i64 0, [[TMP1]]
// CHECK-NEXT:    [[ALIGNED_RESULT:%.*]] = getelementptr inbounds i8, i8 addrspace(200)* [[C]], i64 [[DIFF]]
// CHECK-NEXT:    call void @llvm.assume(i1 true) [ "align"(i8 addrspace(200)* [[ALIGNED_RESULT]], i64 [[ALIGNMENT]]) ]
// CHECK-NEXT:    ret i8 addrspace(200)* [[ALIGNED_RESULT]]
//
extern "C" char* test1(char* c, int b) {
  return __builtin_align_down(c, b);
}

// Found while compiling libnv
// CHECK-LABEL: define {{[^@]+}}@test2
// CHECK-SAME: (i8 addrspace(200)* [[VALUE:%.*]]) local_unnamed_addr addrspace(200) #0
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[PTRADDR:%.*]] = tail call i64 @llvm.cheri.cap.address.get.i64(i8 addrspace(200)* [[VALUE]])
// CHECK-NEXT:    [[OVER_BOUNDARY:%.*]] = add i64 [[PTRADDR]], 3
// CHECK-NEXT:    [[ALIGNED_INTPTR:%.*]] = and i64 [[OVER_BOUNDARY]], -4
// CHECK-NEXT:    [[DIFF:%.*]] = sub i64 [[ALIGNED_INTPTR]], [[PTRADDR]]
// CHECK-NEXT:    [[ALIGNED_RESULT:%.*]] = getelementptr i8, i8 addrspace(200)* [[VALUE]], i64 [[DIFF]]
// CHECK-NEXT:    call void @llvm.assume(i1 true) [ "align"(i8 addrspace(200)* [[ALIGNED_RESULT]], i64 4) ]
// CHECK-NEXT:    ret i8 addrspace(200)* [[ALIGNED_RESULT]]
//
extern "C" __uintcap_t test2(__uintcap_t value) {
  // There should be two casts from capability to address (one for size, one for
  // alignment). The alignment one could be an offset get instead but this doesn't
  // really make any difference since Sema validates that it is a valid capability.
  return __builtin_align_up(value, (__uintcap_t)sizeof(0));
}
