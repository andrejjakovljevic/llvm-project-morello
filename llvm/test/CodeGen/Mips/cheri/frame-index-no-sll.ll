; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: %cheri_purecap_llc -o - -O2 -verify-machineinstrs %s | %cheri_FileCheck %s

define i32 @load_store_stack_i32(i32 %arg, i64 addrspace(200)* %padding) addrspace(200) nounwind {
; CHECK-LABEL: load_store_stack_i32:
; CHECK:       # %bb.0:
; CHECK-NEXT:    cincoffset $c11, $c11, -[[STACKFRAME_SIZE:16|32]]
; CHECK-NEXT:    #APP
; CHECK-NEXT:    #NO_APP
; CHECK-NEXT:    csw $4, $zero, [[#CAP_SIZE - 8]]($c11)
; CHECK-NEXT:    #APP
; CHECK-NEXT:    #NO_APP
; CHECK-NEXT:    clw $2, $zero, [[#CAP_SIZE - 8]]($c11)
; CHECK-NEXT:    #APP
; CHECK-NEXT:    #NO_APP
; CHECK-NEXT:    cjr $c17
; CHECK-NEXT:    cincoffset $c11, $c11, [[STACKFRAME_SIZE]]
  tail call void asm sideeffect "", ""()
  ; Store the i32 to stack slot 2
  %arg.stack = alloca i32, align 8, addrspace(200)
  store volatile i32 %arg, i32 addrspace(200)* %arg.stack, align 4
  tail call void asm sideeffect "", ""()
  ; And load it back
  %loaded = load volatile i32, i32 addrspace(200)* %arg.stack, align 4
  tail call void asm sideeffect "", ""()
  ret i32 %loaded
}

define i16 @load_store_stack_i16(i16 %arg, i64 addrspace(200)* %padding) addrspace(200) nounwind {
; CHECK-LABEL: load_store_stack_i16:
; CHECK:       # %bb.0:
; CHECK-NEXT:    cincoffset $c11, $c11, -[[STACKFRAME_SIZE:16|32]]
; CHECK-NEXT:    #APP
; CHECK-NEXT:    #NO_APP
; CHECK-NEXT:    csh $4, $zero, [[#CAP_SIZE - 8]]($c11)
; CHECK-NEXT:    #APP
; CHECK-NEXT:    #NO_APP
; CHECK-NEXT:    clhu $2, $zero, [[#CAP_SIZE - 8]]($c11)
; CHECK-NEXT:    #APP
; CHECK-NEXT:    #NO_APP
; CHECK-NEXT:    cjr $c17
; CHECK-NEXT:    cincoffset $c11, $c11, [[STACKFRAME_SIZE]]
  tail call void asm sideeffect "", ""()

  ; Store the i16 to stack slot 2
  %arg.stack = alloca i16, align 8, addrspace(200)
  store volatile i16 %arg, i16 addrspace(200)* %arg.stack, align 4
  tail call void asm sideeffect "", ""()

  ; And load it back
  %loaded = load volatile i16, i16 addrspace(200)* %arg.stack, align 4
  tail call void asm sideeffect "", ""()
  ret i16 %loaded
}


define i1 @load_store_stack_i1(i1 %arg, i64 addrspace(200)* %padding) addrspace(200) nounwind {
; CHECK-LABEL: load_store_stack_i1:
; CHECK:       # %bb.0:
; CHECK-NEXT:    cincoffset $c11, $c11, -[[STACKFRAME_SIZE:16|32]]
; CHECK-NEXT:    #APP
; CHECK-NEXT:    #NO_APP
; CHECK-NEXT:    andi $1, $4, 1
; CHECK-NEXT:    csb $1, $zero, [[#CAP_SIZE - 8]]($c11)
; CHECK-NEXT:    #APP
; CHECK-NEXT:    #NO_APP
; CHECK-NEXT:    clbu $2, $zero, [[#CAP_SIZE - 8]]($c11)
; CHECK-NEXT:    #APP
; CHECK-NEXT:    #NO_APP
; CHECK-NEXT:    cjr $c17
; CHECK-NEXT:    cincoffset $c11, $c11, [[STACKFRAME_SIZE]]
  tail call void asm sideeffect "", ""()

  ; Store the i1 to stack slot 2
  %arg.stack = alloca i1, align 8, addrspace(200)
  store volatile i1 %arg, i1 addrspace(200)* %arg.stack, align 4
  tail call void asm sideeffect "", ""()

  ; And load it back
  %loaded = load volatile i1, i1 addrspace(200)* %arg.stack, align 4
  tail call void asm sideeffect "", ""()
  ret i1 %loaded
}
