// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py
// RUN: %cheri_purecap_cc1 -emit-llvm -o - %s | FileCheck %s
int nis_setgrent(void);
typedef int (*nss_method)(void);
typedef struct _ns_dtab {
 const char *src;
 nss_method method;
} ns_dtab;

// CHECK-LABEL: @compat_setgrent(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[DTAB:%.*]] = alloca [1 x %struct._ns_dtab], align 16, addrspace(200)
// CHECK-NEXT:    [[TMP0:%.*]] = bitcast [1 x %struct._ns_dtab] addrspace(200)* [[DTAB]] to i8 addrspace(200)*
// CHECK-NEXT:    call void @llvm.memcpy.p200i8.p200i8.i64(i8 addrspace(200)* align 16 [[TMP0]], i8 addrspace(200)* align 16 bitcast ([1 x %struct._ns_dtab] addrspace(200)* @__const.compat_setgrent.dtab to i8 addrspace(200)*), i64 32, i1 false)
// CHECK-NEXT:    ret void
//
void compat_setgrent(void)
{
 // Check that initialisation of this is done via a memcpy from something that
 // the linker will have set up correctly, and not by a simple store of the
 // constant.
 ns_dtab dtab[] = {
  { 0, nis_setgrent }
 };
}

