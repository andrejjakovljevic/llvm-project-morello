; RUN: %cheri_llc %s -o - | FileCheck %s

; Function Attrs: nounwind readonly
; CHECK-LABEL: load64
define double @load64(double addrspace(200)* nocapture readonly %x) #0 {
entry:
  ; CHECK: cld
  ; CHECK: dmtc1
  %0 = load double, double addrspace(200)* %x, align 8
  ret double %0
}

; Function Attrs: nounwind readonly
; CHECK-LABEL: load32
define float @load32(float addrspace(200)* nocapture readonly %x) #0 {
entry:
  ; CHECK: clw
  ; CHECK: mtc1
  %0 = load float, float addrspace(200)* %x, align 4
  ret float %0
}

; Function Attrs: nounwind
; CHECK-LABEL: store64
define void @store64(double addrspace(200)* nocapture %x, double %y) #1 {
entry:
  ; CHECK: dmfc1
  ; CHECK: csd
  store double %y, double addrspace(200)* %x, align 8
  ret void
}

; Function Attrs: nounwind
; CHECK-LABEL: store32
define void @store32(float addrspace(200)* nocapture %x, float %y) #1 {
entry:
  ; CHECK: mfc1
  ; CHECK: csw
  store float %y, float addrspace(200)* %x, align 4
  ret void
}

attributes #0 = { nounwind readonly "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.4 "}
