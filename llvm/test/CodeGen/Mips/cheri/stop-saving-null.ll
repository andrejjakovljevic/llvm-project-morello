; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; We previously create a NULL value in $c18 and moved that into $c13 since it was being used twice
; RUN: %cheri_purecap_llc -verify-machineinstrs  -o - -O2 -cheri-cap-table-abi=pcrel %s 2>&1 | %cheri_FileCheck %s -implicit-check-not cmove

declare i8 addrspace(200)* @one_arg(i8 addrspace(200)* %first_arg)


define void @call_one_arg_from_many_arg(i8 addrspace(200)* %in_arg1, i8 addrspace(200)* %arg2, i8 addrspace(200)* %arg3, i8 addrspace(200)* %arg4,
; CHECK-LABEL: call_one_arg_from_many_arg:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    cincoffset $c11, $c11, -[[#CAP_SIZE]]
; CHECK-NEXT:    .cfi_def_cfa_offset [[#CAP_SIZE]]
; CHECK-NEXT:    csc $c17, $zero, 0($c11)
; CHECK-NEXT:    .cfi_offset 89, -[[#CAP_SIZE]]
; CHECK-NEXT:    lui $1, %hi(%neg(%captab_rel(call_one_arg_from_many_arg)))
; CHECK-NEXT:    daddiu $1, $1, %lo(%neg(%captab_rel(call_one_arg_from_many_arg)))
; CHECK-NEXT:    cincoffset [[CGP:\$c1]], $c12, $1
; CHECK-NEXT:    cincoffset $c3, $c3, 77
; CHECK-NEXT:    clcbi $c12, %capcall20(one_arg)([[CGP]])
; CHECK-NEXT:    cjalr $c12, $c17
; CHECK-NEXT:    cgetnull $c13
; CHECK-NEXT:    cgetnull $c13
; CHECK-NEXT:    clc $c17, $zero, 0($c11)
; CHECK-NEXT:    cjr $c17
; CHECK-NEXT:    cincoffset $c11, $c11, [[#CAP_SIZE]]
                                        i8 addrspace(200)* %arg5, i8 addrspace(200)* %arg6, i8 addrspace(200)* %arg7, i8 addrspace(200)* %arg8,
                                        i8 addrspace(200)* %arg9, i8 addrspace(200)* %arg10, i8 addrspace(200)* %arg11, i8 addrspace(200)* %arg12) {
; TODO: we should not be saving null to $c18 since that is a waste of time and space
entry:
  %first_arg = call i8 addrspace(200)* @llvm.cheri.cap.offset.increment.i64(i8 addrspace(200)* %in_arg1, i64 77)
  %0 = call i8 addrspace(200)* @one_arg(i8 addrspace(200)* %first_arg)
  ret void
}

declare i8 addrspace(200)* @llvm.cheri.cap.offset.increment.i64(i8 addrspace(200)*, i64)
