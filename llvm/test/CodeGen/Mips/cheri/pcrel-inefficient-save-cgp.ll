; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: %cheri_purecap_llc -cheri-cap-table-abi=plt -O2 %s -o - | %cheri_FileCheck %s -check-prefixes PLT
; RUN: %cheri_purecap_llc -cheri-cap-table-abi=pcrel -O2 %s -o - | %cheri_FileCheck %s -check-prefixes PCREL


%class.QWebSettings = type opaque
%class.QGraphicsWebView = type { i8 }
%class.QWebPage = type { i8 }


declare %class.QWebPage addrspace(200)* @_ZN16QGraphicsWebView4pageEv(%class.QGraphicsWebView addrspace(200)*) addrspace(200)
declare %class.QWebSettings addrspace(200)* @_ZN8QWebPage8settingsEv(%class.QWebPage addrspace(200)*) addrspace(200)

; Function Attrs: nounwind
define %class.QWebSettings addrspace(200)* @_ZN16QGraphicsWebView8settingsEv(%class.QGraphicsWebView addrspace(200)* %this) addrspace(200) nounwind align 2 {
; PLT-LABEL: _ZN16QGraphicsWebView8settingsEv:
; PLT:       # %bb.0: # %entry
; PLT-NEXT:    cincoffset $c11, $c11, -[[STACKFRAME_SIZE:32|64]]
; PLT-NEXT:    csc $c18, $zero, [[#CAP_SIZE * 1]]($c11)
; PLT-NEXT:    csc $c17, $zero, 0($c11)
; PLT-NEXT:    cmove $c18, $c26
; PLT-NEXT:    clcbi $c12, %capcall20(_ZN16QGraphicsWebView4pageEv)($c18)
; PLT-NEXT:    cjalr $c12, $c17
; PLT-NEXT:    nop
; PLT-NEXT:    clcbi $c12, %capcall20(_ZN8QWebPage8settingsEv)($c18)
; PLT-NEXT:    cjalr $c12, $c17
; PLT-NEXT:    cmove $c26, $c18
; PLT-NEXT:    cmove $c26, $c18
; PLT-NEXT:    clc $c17, $zero, 0($c11)
; PLT-NEXT:    clc $c18, $zero, [[#CAP_SIZE * 1]]($c11)
; PLT-NEXT:    cjr $c17
; PLT-NEXT:    cincoffset $c11, $c11, [[STACKFRAME_SIZE]]
;
; PCREL-LABEL: _ZN16QGraphicsWebView8settingsEv:
; PCREL:       # %bb.0: # %entry
; PCREL-NEXT:    cincoffset $c11, $c11, -[[STACKFRAME_SIZE:32|64]]
; PCREL-NEXT:    csc $c18, $zero, [[#CAP_SIZE * 1]]($c11)
; PCREL-NEXT:    csc $c17, $zero, 0($c11)
; PCREL-NEXT:    lui $1, %hi(%neg(%captab_rel(_ZN16QGraphicsWebView8settingsEv)))
; PCREL-NEXT:    daddiu $1, $1, %lo(%neg(%captab_rel(_ZN16QGraphicsWebView8settingsEv)))
; PCREL-NEXT:    cincoffset $c18, $c12, $1
; PCREL-NEXT:    clcbi $c12, %capcall20(_ZN16QGraphicsWebView4pageEv)($c18)
; PCREL-NEXT:    cjalr $c12, $c17
; PCREL-NEXT:    nop
; PCREL-NEXT:    clcbi $c12, %capcall20(_ZN8QWebPage8settingsEv)($c18)
; PCREL-NEXT:    cjalr $c12, $c17
; PCREL-NEXT:    nop
; PCREL-NEXT:    clc $c17, $zero, 0($c11)
; PCREL-NEXT:    clc $c18, $zero, [[#CAP_SIZE * 1]]($c11)
; PCREL-NEXT:    cjr $c17
; PCREL-NEXT:    cincoffset $c11, $c11, [[STACKFRAME_SIZE]]
entry:
  %call = tail call %class.QWebPage addrspace(200)* @_ZN16QGraphicsWebView4pageEv(%class.QGraphicsWebView addrspace(200)* %this)
  %call2 = tail call %class.QWebSettings addrspace(200)* @_ZN8QWebPage8settingsEv(%class.QWebPage addrspace(200)* %call)
  ret %class.QWebSettings addrspace(200)* %call2
}
