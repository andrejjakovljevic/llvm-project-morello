set(LLVM_LINK_COMPONENTS BitWriter Core Object Support TransformUtils)

add_clang_tool(clang-offload-wrapper
  ClangOffloadWrapper.cpp

  DEPENDS
  intrinsics_gen
  )

set(CLANG_OFFLOAD_WRAPPER_LIB_DEPS
  clangBasic
  )

add_dependencies(clang clang-offload-wrapper)

clang_target_link_libraries(clang-offload-wrapper
  PRIVATE
  ${CLANG_OFFLOAD_WRAPPER_LIB_DEPS}
  )

# TODO: port this to remove getUnqual
remove_definitions(-DLLVM_NO_DEFAULT_ADDRESS_SPACE)
