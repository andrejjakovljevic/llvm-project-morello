// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py UTC_ARGS: --function-signature
// REQUIRES: mips-registered-target

// RUN: %cheri_clang -fno-discard-value-names %s -emit-llvm -S -o - -fsanitize=fuzzer -###
// RUN: %cheri_clang -fno-discard-value-names %s -emit-llvm -S -o - -fsanitize=fuzzer | FileCheck %s -check-prefix MIPS
// RUN: %cheri_purecap_clang -fno-discard-value-names %s -S -emit-llvm -o - -fsanitize=fuzzer | FileCheck %s -check-prefix PURECAP

// Check that we can emit assembly:
// RUN: %cheri_clang -O2 %s -S -o /dev/null -fsanitize=fuzzer
// RUN: %cheri_purecap_clang -O2 %s -S -o /dev/null -fsanitize=fuzzer

extern char *gets(char *);
extern int puts(const char *);
extern int fail1(void);
extern int fail2(void);

// Check that the globals have the right type
// UTC_ARGS: --disable
// MIPS: @__sancov_lowest_stack = external thread_local(initialexec) global i64
// MIPS: @__sancov_gen_ = private global [1 x i8] zeroinitializer, section "__sancov_cntrs", comdat($main), align 1{{$}}
// MIPS: @__sancov_gen_.1 = private constant [2 x i64] [i64 ptrtoint (i32 ()* @main to i64), i64 1], section "__sancov_pcs", comdat($main), align 8{{$}}
// MIPS: @__sancov_gen_.2 = private global [4 x i8] zeroinitializer, section "__sancov_cntrs", comdat($func2), align 1{{$}}
// MIPS: @__sancov_gen_.3 = private constant [8 x i64] [i64 ptrtoint (i32 (i32)* @func2 to i64), i64 1, i64 ptrtoint (i8* blockaddress(@func2, %if.then) to i64), i64 0, i64 ptrtoint (i8* blockaddress(@func2, %if.then2) to i64), i64 0, i64 ptrtoint (i8* blockaddress(@func2, %if.end4) to i64), i64 0], section "__sancov_pcs", comdat($func2), align 8{{$}}
// MIPS: @__start___sancov_cntrs = extern_weak hidden global i8
// MIPS: @__stop___sancov_cntrs = extern_weak hidden global i8
// MIPS: @llvm.global_ctors = appending global [1 x { i32, void ()*, i8* }] [{ i32, void ()*, i8* } { i32 2, void ()* @sancov.module_ctor_8bit_counters, i8* bitcast (void ()* @sancov.module_ctor_8bit_counters to i8*) }]
// MIPS: @__start___sancov_pcs = extern_weak hidden global i64
// MIPS: @__stop___sancov_pcs = extern_weak hidden global i64
// MIPS: @llvm.compiler.used = appending global [4 x i8*] [i8* getelementptr inbounds ([1 x i8], [1 x i8]* @__sancov_gen_, i32 0, i32 0), i8* bitcast ([2 x i64]* @__sancov_gen_.1 to i8*), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @__sancov_gen_.2, i32 0, i32 0), i8* bitcast ([8 x i64]* @__sancov_gen_.3 to i8*)], section "llvm.metadata"

// These should all be in AS200:
// PURECAP: @__sancov_lowest_stack = external thread_local(initialexec) addrspace(200) global i64
// PURECAP: @__sancov_gen_ = private addrspace(200) global [1 x i8] zeroinitializer, section "__sancov_cntrs", comdat($main), align 1{{$}}
// PURECAP: @__sancov_gen_.1 = private addrspace(200) constant [2 x i64] [i64 ptrtoint (i32 () addrspace(200)* @main to i64), i64 1], section "__sancov_pcs", comdat($main), align 8{{$}}
// PURECAP: @__sancov_gen_.2 = private addrspace(200) global [4 x i8] zeroinitializer, section "__sancov_cntrs", comdat($func2), align 1{{$}}
// PURECAP: @__sancov_gen_.3 = private addrspace(200) constant [8 x i64] [
// PURECAP-SAME:   i64 ptrtoint (i32 (i32) addrspace(200)* @func2 to i64), i64 1,
// PURECAP-SAME:   i64 ptrtoint (i8 addrspace(200)* blockaddress(@func2, %if.then) to i64), i64 0,
// PURECAP-SAME:   i64 ptrtoint (i8 addrspace(200)* blockaddress(@func2, %if.then2) to i64), i64 0,
// PURECAP-SAME:   i64 ptrtoint (i8 addrspace(200)* blockaddress(@func2, %if.end4) to i64), i64 0],
// PURECAP-SAME: section "__sancov_pcs", comdat($func2), align 8{{$}}
// PURECAP: @__start___sancov_cntrs = extern_weak hidden addrspace(200) global i8
// PURECAP: @__stop___sancov_cntrs = extern_weak hidden addrspace(200) global i8
// PURECAP: @llvm.global_ctors = appending addrspace(200) global [1 x { i32, void () addrspace(200)*, i8 addrspace(200)* }] [{ i32, void () addrspace(200)*, i8 addrspace(200)* } { i32 2, void () addrspace(200)* @sancov.module_ctor_8bit_counters, i8 addrspace(200)* bitcast (void () addrspace(200)* @sancov.module_ctor_8bit_counters to i8 addrspace(200)*) }]
// PURECAP: @__start___sancov_pcs = extern_weak hidden addrspace(200) global i64
// PURECAP: @__stop___sancov_pcs = extern_weak hidden addrspace(200) global i64
// PURECAP: @llvm.compiler.used = appending addrspace(200) global [4 x i8*] [i8* addrspacecast (i8 addrspace(200)* getelementptr inbounds ([1 x i8], [1 x i8] addrspace(200)* @__sancov_gen_, i32 0, i32 0) to i8*), i8* addrspacecast (i8 addrspace(200)* bitcast ([2 x i64] addrspace(200)* @__sancov_gen_.1 to i8 addrspace(200)*) to i8*), i8* addrspacecast (i8 addrspace(200)* getelementptr inbounds ([4 x i8], [4 x i8] addrspace(200)* @__sancov_gen_.2, i32 0, i32 0) to i8*), i8* addrspacecast (i8 addrspace(200)* bitcast ([8 x i64] addrspace(200)* @__sancov_gen_.3 to i8 addrspace(200)*) to i8*)], section "llvm.metadata"

// UTC_ARGS: --enable

// MIPS-LABEL: define {{[^@]+}}@main
// MIPS-SAME: () #[[ATTR0:[0-9]+]] comdat {
// MIPS-NEXT:  entry:
// MIPS-NEXT:    [[FOO:%.*]] = alloca [10 x i8], align 1
// MIPS-NEXT:    [[TMP0:%.*]] = load i8, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @__sancov_gen_, i64 0, i64 0), align 1, !nosanitize !5
// MIPS-NEXT:    [[TMP1:%.*]] = add i8 [[TMP0]], 1
// MIPS-NEXT:    store i8 [[TMP1]], i8* getelementptr inbounds ([1 x i8], [1 x i8]* @__sancov_gen_, i64 0, i64 0), align 1, !nosanitize !5
// MIPS-NEXT:    [[ARRAYDECAY:%.*]] = getelementptr inbounds [10 x i8], [10 x i8]* [[FOO]], i64 0, i64 0
// MIPS-NEXT:    [[CALL:%.*]] = call i8* @gets(i8* noundef [[ARRAYDECAY]]) #[[ATTR3:[0-9]+]]
// MIPS-NEXT:    [[ARRAYDECAY1:%.*]] = getelementptr inbounds [10 x i8], [10 x i8]* [[FOO]], i64 0, i64 0
// MIPS-NEXT:    [[CALL2:%.*]] = call signext i32 @puts(i8* noundef [[ARRAYDECAY1]]) #[[ATTR3]]
// MIPS-NEXT:    ret i32 0
//
// PURECAP-LABEL: define {{[^@]+}}@main
// PURECAP-SAME: () addrspace(200) #[[ATTR0:[0-9]+]] comdat {
// PURECAP-NEXT:  entry:
// PURECAP-NEXT:    [[FOO:%.*]] = alloca [10 x i8], align 1, addrspace(200)
// PURECAP-NEXT:    [[TMP0:%.*]] = load i8, i8 addrspace(200)* getelementptr inbounds ([1 x i8], [1 x i8] addrspace(200)* @__sancov_gen_, i64 0, i64 0), align 1, !nosanitize !5
// PURECAP-NEXT:    [[TMP1:%.*]] = add i8 [[TMP0]], 1
// PURECAP-NEXT:    store i8 [[TMP1]], i8 addrspace(200)* getelementptr inbounds ([1 x i8], [1 x i8] addrspace(200)* @__sancov_gen_, i64 0, i64 0), align 1, !nosanitize !5
// PURECAP-NEXT:    [[ARRAYDECAY:%.*]] = getelementptr inbounds [10 x i8], [10 x i8] addrspace(200)* [[FOO]], i64 0, i64 0
// PURECAP-NEXT:    [[CALL:%.*]] = call i8 addrspace(200)* @gets(i8 addrspace(200)* noundef [[ARRAYDECAY]]) #[[ATTR3:[0-9]+]]
// PURECAP-NEXT:    [[ARRAYDECAY1:%.*]] = getelementptr inbounds [10 x i8], [10 x i8] addrspace(200)* [[FOO]], i64 0, i64 0
// PURECAP-NEXT:    [[CALL2:%.*]] = call signext i32 @puts(i8 addrspace(200)* noundef [[ARRAYDECAY1]]) #[[ATTR3]]
// PURECAP-NEXT:    ret i32 0
//
int main(void) {
  char foo[10];
  gets(foo);
  puts(foo);
}

// MIPS-LABEL: define {{[^@]+}}@func2
// MIPS-SAME: (i32 noundef signext [[I:%.*]]) #[[ATTR0]] comdat {
// MIPS-NEXT:  entry:
// MIPS-NEXT:    [[RETVAL:%.*]] = alloca i32, align 4
// MIPS-NEXT:    [[I_ADDR:%.*]] = alloca i32, align 4
// MIPS-NEXT:    [[TMP0:%.*]] = load i8, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @__sancov_gen_.2, i64 0, i64 0), align 1, !nosanitize !5
// MIPS-NEXT:    [[TMP1:%.*]] = add i8 [[TMP0]], 1
// MIPS-NEXT:    store i8 [[TMP1]], i8* getelementptr inbounds ([4 x i8], [4 x i8]* @__sancov_gen_.2, i64 0, i64 0), align 1, !nosanitize !5
// MIPS-NEXT:    store i32 [[I]], i32* [[I_ADDR]], align 4
// MIPS-NEXT:    [[TMP2:%.*]] = load i32, i32* [[I_ADDR]], align 4
// MIPS-NEXT:    call void @__sanitizer_cov_trace_const_cmp4(i32 100, i32 [[TMP2]])
// MIPS-NEXT:    [[CMP:%.*]] = icmp slt i32 [[TMP2]], 100
// MIPS-NEXT:    br i1 [[CMP]], label [[IF_THEN:%.*]], label [[IF_ELSE:%.*]]
// MIPS:       if.then:
// MIPS-NEXT:    [[TMP3:%.*]] = load i8, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @__sancov_gen_.2, i64 0, i64 1), align 1, !nosanitize !5
// MIPS-NEXT:    [[TMP4:%.*]] = add i8 [[TMP3]], 1
// MIPS-NEXT:    store i8 [[TMP4]], i8* getelementptr inbounds ([4 x i8], [4 x i8]* @__sancov_gen_.2, i64 0, i64 1), align 1, !nosanitize !5
// MIPS-NEXT:    [[CALL:%.*]] = call signext i32 @fail1() #[[ATTR3]]
// MIPS-NEXT:    store i32 [[CALL]], i32* [[RETVAL]], align 4
// MIPS-NEXT:    br label [[RETURN:%.*]]
// MIPS:       if.else:
// MIPS-NEXT:    [[TMP5:%.*]] = load i32, i32* [[I_ADDR]], align 4
// MIPS-NEXT:    call void @__sanitizer_cov_trace_const_cmp4(i32 200, i32 [[TMP5]])
// MIPS-NEXT:    [[CMP1:%.*]] = icmp slt i32 [[TMP5]], 200
// MIPS-NEXT:    br i1 [[CMP1]], label [[IF_THEN2:%.*]], label [[IF_END:%.*]]
// MIPS:       if.then2:
// MIPS-NEXT:    [[TMP6:%.*]] = load i8, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @__sancov_gen_.2, i64 0, i64 2), align 1, !nosanitize !5
// MIPS-NEXT:    [[TMP7:%.*]] = add i8 [[TMP6]], 1
// MIPS-NEXT:    store i8 [[TMP7]], i8* getelementptr inbounds ([4 x i8], [4 x i8]* @__sancov_gen_.2, i64 0, i64 2), align 1, !nosanitize !5
// MIPS-NEXT:    [[CALL3:%.*]] = call signext i32 @fail2() #[[ATTR3]]
// MIPS-NEXT:    store i32 [[CALL3]], i32* [[RETVAL]], align 4
// MIPS-NEXT:    br label [[RETURN]]
// MIPS:       if.end:
// MIPS-NEXT:    br label [[IF_END4:%.*]]
// MIPS:       if.end4:
// MIPS-NEXT:    [[TMP8:%.*]] = load i8, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @__sancov_gen_.2, i64 0, i64 3), align 1, !nosanitize !5
// MIPS-NEXT:    [[TMP9:%.*]] = add i8 [[TMP8]], 1
// MIPS-NEXT:    store i8 [[TMP9]], i8* getelementptr inbounds ([4 x i8], [4 x i8]* @__sancov_gen_.2, i64 0, i64 3), align 1, !nosanitize !5
// MIPS-NEXT:    [[TMP10:%.*]] = load i32, i32* [[I_ADDR]], align 4
// MIPS-NEXT:    [[ADD:%.*]] = add nsw i32 [[TMP10]], 1
// MIPS-NEXT:    store i32 [[ADD]], i32* [[RETVAL]], align 4
// MIPS-NEXT:    br label [[RETURN]]
// MIPS:       return:
// MIPS-NEXT:    [[TMP11:%.*]] = load i32, i32* [[RETVAL]], align 4
// MIPS-NEXT:    ret i32 [[TMP11]]
//
// PURECAP-LABEL: define {{[^@]+}}@func2
// PURECAP-SAME: (i32 noundef signext [[I:%.*]]) addrspace(200) #[[ATTR0]] comdat {
// PURECAP-NEXT:  entry:
// PURECAP-NEXT:    [[RETVAL:%.*]] = alloca i32, align 4, addrspace(200)
// PURECAP-NEXT:    [[I_ADDR:%.*]] = alloca i32, align 4, addrspace(200)
// PURECAP-NEXT:    [[TMP0:%.*]] = load i8, i8 addrspace(200)* getelementptr inbounds ([4 x i8], [4 x i8] addrspace(200)* @__sancov_gen_.2, i64 0, i64 0), align 1, !nosanitize !5
// PURECAP-NEXT:    [[TMP1:%.*]] = add i8 [[TMP0]], 1
// PURECAP-NEXT:    store i8 [[TMP1]], i8 addrspace(200)* getelementptr inbounds ([4 x i8], [4 x i8] addrspace(200)* @__sancov_gen_.2, i64 0, i64 0), align 1, !nosanitize !5
// PURECAP-NEXT:    store i32 [[I]], i32 addrspace(200)* [[I_ADDR]], align 4
// PURECAP-NEXT:    [[TMP2:%.*]] = load i32, i32 addrspace(200)* [[I_ADDR]], align 4
// PURECAP-NEXT:    call void @__sanitizer_cov_trace_const_cmp4(i32 100, i32 [[TMP2]])
// PURECAP-NEXT:    [[CMP:%.*]] = icmp slt i32 [[TMP2]], 100
// PURECAP-NEXT:    br i1 [[CMP]], label [[IF_THEN:%.*]], label [[IF_ELSE:%.*]]
// PURECAP:       if.then:
// PURECAP-NEXT:    [[TMP3:%.*]] = load i8, i8 addrspace(200)* getelementptr inbounds ([4 x i8], [4 x i8] addrspace(200)* @__sancov_gen_.2, i64 0, i64 1), align 1, !nosanitize !5
// PURECAP-NEXT:    [[TMP4:%.*]] = add i8 [[TMP3]], 1
// PURECAP-NEXT:    store i8 [[TMP4]], i8 addrspace(200)* getelementptr inbounds ([4 x i8], [4 x i8] addrspace(200)* @__sancov_gen_.2, i64 0, i64 1), align 1, !nosanitize !5
// PURECAP-NEXT:    [[CALL:%.*]] = call signext i32 @fail1() #[[ATTR3]]
// PURECAP-NEXT:    store i32 [[CALL]], i32 addrspace(200)* [[RETVAL]], align 4
// PURECAP-NEXT:    br label [[RETURN:%.*]]
// PURECAP:       if.else:
// PURECAP-NEXT:    [[TMP5:%.*]] = load i32, i32 addrspace(200)* [[I_ADDR]], align 4
// PURECAP-NEXT:    call void @__sanitizer_cov_trace_const_cmp4(i32 200, i32 [[TMP5]])
// PURECAP-NEXT:    [[CMP1:%.*]] = icmp slt i32 [[TMP5]], 200
// PURECAP-NEXT:    br i1 [[CMP1]], label [[IF_THEN2:%.*]], label [[IF_END:%.*]]
// PURECAP:       if.then2:
// PURECAP-NEXT:    [[TMP6:%.*]] = load i8, i8 addrspace(200)* getelementptr inbounds ([4 x i8], [4 x i8] addrspace(200)* @__sancov_gen_.2, i64 0, i64 2), align 1, !nosanitize !5
// PURECAP-NEXT:    [[TMP7:%.*]] = add i8 [[TMP6]], 1
// PURECAP-NEXT:    store i8 [[TMP7]], i8 addrspace(200)* getelementptr inbounds ([4 x i8], [4 x i8] addrspace(200)* @__sancov_gen_.2, i64 0, i64 2), align 1, !nosanitize !5
// PURECAP-NEXT:    [[CALL3:%.*]] = call signext i32 @fail2() #[[ATTR3]]
// PURECAP-NEXT:    store i32 [[CALL3]], i32 addrspace(200)* [[RETVAL]], align 4
// PURECAP-NEXT:    br label [[RETURN]]
// PURECAP:       if.end:
// PURECAP-NEXT:    br label [[IF_END4:%.*]]
// PURECAP:       if.end4:
// PURECAP-NEXT:    [[TMP8:%.*]] = load i8, i8 addrspace(200)* getelementptr inbounds ([4 x i8], [4 x i8] addrspace(200)* @__sancov_gen_.2, i64 0, i64 3), align 1, !nosanitize !5
// PURECAP-NEXT:    [[TMP9:%.*]] = add i8 [[TMP8]], 1
// PURECAP-NEXT:    store i8 [[TMP9]], i8 addrspace(200)* getelementptr inbounds ([4 x i8], [4 x i8] addrspace(200)* @__sancov_gen_.2, i64 0, i64 3), align 1, !nosanitize !5
// PURECAP-NEXT:    [[TMP10:%.*]] = load i32, i32 addrspace(200)* [[I_ADDR]], align 4
// PURECAP-NEXT:    [[ADD:%.*]] = add nsw i32 [[TMP10]], 1
// PURECAP-NEXT:    store i32 [[ADD]], i32 addrspace(200)* [[RETVAL]], align 4
// PURECAP-NEXT:    br label [[RETURN]]
// PURECAP:       return:
// PURECAP-NEXT:    [[TMP11:%.*]] = load i32, i32 addrspace(200)* [[RETVAL]], align 4
// PURECAP-NEXT:    ret i32 [[TMP11]]
//
int func2(int i) {
  if (i < 100) {
    return fail1();
  } else if (i < 200) {
    return fail2();
  }
  return i + 1;
}

// UTC_ARGS: --disable
// Check that the trace functions take as200 pointers:
// MIPS: declare void @__sanitizer_cov_trace_pc_indir(i64)
// MIPS: declare void @__sanitizer_cov_trace_cmp1(i8 zeroext, i8 zeroext)
// MIPS: declare void @__sanitizer_cov_trace_cmp2(i16 zeroext, i16 zeroext)
// MIPS: declare void @__sanitizer_cov_trace_cmp4(i32 zeroext, i32 zeroext)
// MIPS: declare void @__sanitizer_cov_trace_cmp8(i64, i64)
// MIPS: declare void @__sanitizer_cov_trace_const_cmp1(i8 zeroext, i8 zeroext)
// MIPS: declare void @__sanitizer_cov_trace_const_cmp2(i16 zeroext, i16 zeroext)
// MIPS: declare void @__sanitizer_cov_trace_const_cmp4(i32 zeroext, i32 zeroext)
// MIPS: declare void @__sanitizer_cov_trace_const_cmp8(i64, i64)
// MIPS: declare void @__sanitizer_cov_trace_div4(i32 zeroext)
// MIPS: declare void @__sanitizer_cov_trace_div8(i64)
// MIPS: declare void @__sanitizer_cov_trace_gep(i64)
// MIPS: declare void @__sanitizer_cov_trace_switch(i64, i64*)
// MIPS: declare void @__sanitizer_cov_trace_pc()
// MIPS: declare void @__sanitizer_cov_trace_pc_guard(i32*)
// MIPS: declare void @__sanitizer_cov_8bit_counters_init(i8*, i8*)
// MIPS: define internal void @sancov.module_ctor_8bit_counters() #{{[0-9]+}} comdat {
// MIPS:   call void @__sanitizer_cov_8bit_counters_init(i8* @__start___sancov_cntrs, i8* @__stop___sancov_cntrs)
// MIPS:   call void @__sanitizer_cov_pcs_init(i64* @__start___sancov_pcs, i64* @__stop___sancov_pcs)
// MIPS:   ret void
// MIPS: }
// MIPS: declare void @__sanitizer_cov_pcs_init(i64*, i64*)

// PURECAP: declare void @__sanitizer_cov_trace_pc_indir(i64) addrspace(200)
// PURECAP: declare void @__sanitizer_cov_trace_cmp1(i8 zeroext, i8 zeroext) addrspace(200)
// PURECAP: declare void @__sanitizer_cov_trace_cmp2(i16 zeroext, i16 zeroext) addrspace(200)
// PURECAP: declare void @__sanitizer_cov_trace_cmp4(i32 zeroext, i32 zeroext) addrspace(200)
// PURECAP: declare void @__sanitizer_cov_trace_cmp8(i64, i64) addrspace(200)
// PURECAP: declare void @__sanitizer_cov_trace_const_cmp1(i8 zeroext, i8 zeroext) addrspace(200)
// PURECAP: declare void @__sanitizer_cov_trace_const_cmp2(i16 zeroext, i16 zeroext) addrspace(200)
// PURECAP: declare void @__sanitizer_cov_trace_const_cmp4(i32 zeroext, i32 zeroext) addrspace(200)
// PURECAP: declare void @__sanitizer_cov_trace_const_cmp8(i64, i64) addrspace(200)
// PURECAP: declare void @__sanitizer_cov_trace_div4(i32 zeroext) addrspace(200)
// PURECAP: declare void @__sanitizer_cov_trace_div8(i64) addrspace(200)
// PURECAP: declare void @__sanitizer_cov_trace_gep(i64) addrspace(200)
// PURECAP: declare void @__sanitizer_cov_trace_switch(i64, i64 addrspace(200)*) addrspace(200)
// PURECAP: declare void @__sanitizer_cov_trace_pc() addrspace(200)
// PURECAP: declare void @__sanitizer_cov_trace_pc_guard(i32 addrspace(200)*) addrspace(200)
// PURECAP: declare void @__sanitizer_cov_8bit_counters_init(i8 addrspace(200)*, i8 addrspace(200)*) addrspace(200)
// PURECAP: define internal void @sancov.module_ctor_8bit_counters() addrspace(200) #{{[0-9]+}} comdat {
// PURECAP:   call void @__sanitizer_cov_8bit_counters_init(i8 addrspace(200)* @__start___sancov_cntrs, i8 addrspace(200)* @__stop___sancov_cntrs)
// PURECAP:   call void @__sanitizer_cov_pcs_init(i64 addrspace(200)* @__start___sancov_pcs, i64 addrspace(200)* @__stop___sancov_pcs)
// PURECAP:   ret void
// PURECAP: }
// PURECAP: declare void @__sanitizer_cov_pcs_init(i64 addrspace(200)*, i64 addrspace(200)*) addrspace(200)
// UTC_ARGS: --enable
