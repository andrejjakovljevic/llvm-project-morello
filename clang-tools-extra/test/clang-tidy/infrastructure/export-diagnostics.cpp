// RUN: grep -Ev "// *[A-Z-]+:" %s > %t-input.cpp
// RUN: not clang-tidy %t-input.cpp -checks='-*,google-explicit-constructor,clang-diagnostic-missing-prototypes' -export-fixes=%t.yaml -- -Wmissing-prototypes > %t.msg 2>&1
// RUN: FileCheck -input-file=%t.msg -check-prefix=CHECK-MESSAGES %s -implicit-check-not='{{warning|error|note}}:'
// RUN: FileCheck -input-file=%t.yaml -check-prefix=CHECK-YAML %s
#define X(n) void n ## n() {}
X(f)
int a[-1];

// CHECK-MESSAGES: -input.cpp:2:1: warning: no previous prototype for function 'ff' [clang-diagnostic-missing-prototypes]
// CHECK-MESSAGES: -input.cpp:1:19: note: expanded from macro 'X'
// CHECK-MESSAGES: {{^}}note: expanded from here{{$}}
// CHECK-MESSAGES: -input.cpp:2:1: note: declare 'static' if the function is not intended to be used outside of this translation unit
// CHECK-MESSAGES: -input.cpp:1:14: note: expanded from macro 'X'
// CHECK-MESSAGES: -input.cpp:3:7: error: 'a' declared as an array with a negative size [clang-diagnostic-error]

// CHECK-YAML: ---
// CHECK-YAML-NEXT: MainSourceFile:  '{{.*}}-input.cpp'
// CHECK-YAML-NEXT: Diagnostics:
// CHECK-YAML-NEXT:   - DiagnosticName:  clang-diagnostic-missing-prototypes
// CHECK-YAML-NEXT:     DiagnosticMessage:
// CHECK-YAML-NEXT:       Message:         'no previous prototype for function
// ''ff'''
// CHECK-YAML-NEXT:       FilePath:        '{{.*}}-input.cpp'
// CHECK-YAML-NEXT:       FileOffset:      30
// CHECK-YAML-NEXT:       Replacements:      []
// CHECK-YAML-NEXT:     Notes:
// CHECK-YAML-NEXT:       - Message:         'expanded from macro ''X'''
// CHECK-YAML-NEXT:         FilePath:        '{{.*}}-input.cpp'
// CHECK-YAML-NEXT:         FileOffset:      18
// CHECK-YAML-NEXT:         Replacements:    []
// CHECK-YAML-NEXT:       - Message:         expanded from here
// CHECK-YAML-NEXT:         FilePath:        ''
// CHECK-YAML-NEXT:         FileOffset:      0
// CHECK-YAML-NEXT:         Replacements:    []
// CHECK-YAML-NEXT:       - Message:         'declare ''static'' if the function is not intended to be used outside of this translation unit'
// CHECK-YAML-NEXT:         FilePath:        '{{.*}}-input.cpp'
// CHECK-YAML-NEXT:         FileOffset:      30
// CHECK-YAML-NEXT:         Replacements:
// CHECK-YAML-NEXT:           - FilePath:        '{{.*}}-input.cpp'
// CHECK-YAML-NEXT:             Offset:          30
// CHECK-YAML-NEXT:             Length:          0
// CHECK-YAML-NEXT:             ReplacementText: 'static '
// CHECK-YAML-NEXT:       - Message:         'expanded from macro ''X'''
// CHECK-YAML-NEXT:         FilePath:        '{{.*}}-input.cpp'
// CHECK-YAML-NEXT:         FileOffset:      13
// CHECK-YAML-NEXT:         Replacements:    []
// CHECK-YAML-NEXT:     Level:           Warning
// CHECK-YAML-NEXT:     BuildDirectory:  '{{.*}}'
// CHECK-YAML-NEXT:   - DiagnosticName:  clang-diagnostic-error
// CHECK-YAML-NEXT:     DiagnosticMessage:
// CHECK-YAML-NEXT:       Message:         '''a'' declared as an array with a negative size'
// CHECK-YAML-NEXT:       FilePath:        '{{.*}}-input.cpp'
// CHECK-YAML-NEXT:       FileOffset:      41
// CHECK-YAML-NEXT:       Replacements:    []
// CHECK-YAML-NEXT:     Level:           Error
// CHECK-YAML-NEXT:     BuildDirectory:  '{{.*}}'
// CHECK-YAML-NEXT:     Ranges:
// CHECK-YAML-NEXT:      - FilePath:        '{{.*}}-input.cpp'
// CHECK-YAML-NEXT:         FileOffset:      41
// CHECK-YAML-NEXT:         Length:          1
// CHECK-YAML-NEXT: ...
