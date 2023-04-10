; ModuleID = 'tests/hello.c'
source_filename = "tests/hello.c"
target datalayout = "e-m:e-pf200:128:128:128:64-i8:8:32-i16:16:32-i64:64-i128:128-n32:64-S128-A200-P200-G200"
target triple = "aarch64-unknown-freebsd14.0"

%struct.hello = type { i32, i32 }

@.str = private unnamed_addr addrspace(200) constant [12 x i8] c"size is=%lu\00", align 1
@.str.1 = private unnamed_addr addrspace(200) constant [13 x i8] c"Hello world\0A\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define i32 @main() addrspace(200) #0 {
entry:
  %retval = alloca i32, align 4, addrspace(200)
  %l = alloca i32, align 4, addrspace(200)
  %h = alloca %struct.hello, align 4, addrspace(200)
  store i32 0, i32 addrspace(200)* %retval, align 4
  store i32 1, i32 addrspace(200)* %l, align 4
  %call = call i32 (i8 addrspace(200)*, ...) @printf(i8 addrspace(200)* getelementptr inbounds ([12 x i8], [12 x i8] addrspace(200)* @.str, i64 0, i64 0), i64 16)
  %call1 = call i32 (i8 addrspace(200)*, ...) @printf(i8 addrspace(200)* getelementptr inbounds ([13 x i8], [13 x i8] addrspace(200)* @.str.1, i64 0, i64 0))
  ret i32 0
}

declare i32 @printf(i8 addrspace(200)*, ...) addrspace(200) #1

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="non-leaf" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" "target-features"="+c64,+dotprod,+fp-armv8,+fullfp16,+morello,+neon,+rcpc,+spe,+ssbs,+v8.2a" }
attributes #1 = { "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" "target-features"="+c64,+dotprod,+fp-armv8,+fullfp16,+morello,+neon,+rcpc,+spe,+ssbs,+v8.2a" }

!llvm.module.flags = !{!0, !1, !2, !3, !4, !5, !6, !7}
!llvm.ident = !{!8}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 1, !"branch-target-enforcement", i32 0}
!2 = !{i32 1, !"sign-return-address", i32 0}
!3 = !{i32 1, !"sign-return-address-all", i32 0}
!4 = !{i32 1, !"sign-return-address-with-bkey", i32 0}
!5 = !{i32 7, !"PIC Level", i32 1}
!6 = !{i32 7, !"uwtable", i32 1}
!7 = !{i32 7, !"frame-pointer", i32 1}
!8 = !{!"clang version 13.0.0"}
