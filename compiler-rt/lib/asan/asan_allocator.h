//===-- asan_allocator.h ----------------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file is a part of AddressSanitizer, an address sanity checker.
//
// ASan-private header for asan_allocator.cpp.
//===----------------------------------------------------------------------===//

#ifndef ASAN_ALLOCATOR_H
#define ASAN_ALLOCATOR_H

#include "asan_flags.h"
#include "asan_internal.h"
#include "asan_interceptors.h"
#include "sanitizer_common/sanitizer_allocator.h"
#include "sanitizer_common/sanitizer_list.h"

namespace __asan {

enum AllocType {
  FROM_MALLOC = 1,  // Memory block came from malloc, calloc, realloc, etc.
  FROM_NEW = 2,     // Memory block came from operator new.
  FROM_NEW_BR = 3   // Memory block came from operator new [ ]
};

struct AsanChunk;

struct AllocatorOptions {
  u32 quarantine_size_mb;
  u32 thread_local_quarantine_size_kb;
  u16 min_redzone;
  u16 max_redzone;
  u8 may_return_null;
  u8 alloc_dealloc_mismatch;
  s32 release_to_os_interval_ms;

  void SetFrom(const Flags *f, const CommonFlags *cf);
  void CopyTo(Flags *f, CommonFlags *cf);
};

void InitializeAllocator(const AllocatorOptions &options);
void ReInitializeAllocator(const AllocatorOptions &options);
void GetAllocatorOptions(AllocatorOptions *options);

class AsanChunkView {
 public:
  explicit AsanChunkView(AsanChunk *chunk) : chunk_(chunk) {}
  bool IsValid() const;        // Checks if AsanChunkView points to a valid
                               // allocated or quarantined chunk.
  bool IsAllocated() const;    // Checks if the memory is currently allocated.
  bool IsQuarantined() const;  // Checks if the memory is currently quarantined.
  uptr Beg() const;            // First byte of user memory.
  uptr End() const;            // Last byte of user memory.
  uptr UsedSize() const;       // Size requested by the user.
  u32 UserRequestedAlignment() const;  // Originally requested alignment.
  uptr AllocTid() const;
  uptr FreeTid() const;
  bool Eq(const AsanChunkView &c) const { return chunk_ == c.chunk_; }
  u32 GetAllocStackId() const;
  u32 GetFreeStackId() const;
  StackTrace GetAllocStack() const;
  StackTrace GetFreeStack() const;
  AllocType GetAllocType() const;
  bool AddrIsInside(uptr addr, uptr access_size, sptr *offset) const {
    if (addr >= Beg() && (addr + access_size) <= End()) {
      *offset = addr - Beg();
      return true;
    }
    return false;
  }
  bool AddrIsAtLeft(uptr addr, uptr access_size, sptr *offset) const {
    (void)access_size;
    if (addr < Beg()) {
      *offset = Beg() - addr;
      return true;
    }
    return false;
  }
  bool AddrIsAtRight(uptr addr, uptr access_size, sptr *offset) const {
    if (addr + access_size > End()) {
      *offset = addr - End();
      return true;
    }
    return false;
  }

 private:
  AsanChunk *const chunk_;
};

AsanChunkView FindHeapChunkByAddress(uptr address);
AsanChunkView FindHeapChunkByAllocBeg(uptr address);

// List of AsanChunks with total size.
class AsanChunkFifoList: public IntrusiveList<AsanChunk> {
 public:
  explicit AsanChunkFifoList(LinkerInitialized) { }
  AsanChunkFifoList() { clear(); }
  void Push(AsanChunk *n);
  void PushList(AsanChunkFifoList *q);
  AsanChunk *Pop();
  uptr size() { return size_; }
  void clear() {
    IntrusiveList<AsanChunk>::clear();
    size_ = 0;
  }
 private:
  uptr size_;
};

struct AsanMapUnmapCallback {
  void OnMap(uptr p, usize size) const;
  void OnUnmap(uptr p, usize size) const;
};

#if defined(__aarch64__)
// AArch64 supports 39, 42 and 48-bit VMA.
const vaddr kAllocatorSpace = ~(uptr)0;
#if SANITIZER_ANDROID
const uptr kAllocatorSize = 0x2000000000ULL;  // 128G.
typedef VeryCompactSizeClassMap SizeClassMap64;
#else
const uptr kAllocatorSize = 0x40000000000ULL;  // 4T.
typedef DefaultSizeClassMap SizeClassMap64;
#endif

template <typename AddressSpaceViewTy>
struct AP64 {  // Allocator64 parameters. Deliberately using a short name.
  static const vaddr kSpaceBeg = kAllocatorSpace;
  static const usize kSpaceSize = kAllocatorSize;
  static const usize kMetadataSize = 0;
  typedef __asan::SizeClassMap64 SizeClassMap;
  typedef AsanMapUnmapCallback MapUnmapCallback;
  static const usize kFlags = 0;
  using AddressSpaceView = AddressSpaceViewTy;
};
template <typename AddressSpaceView>
using Allocator64ASVT = SizeClassAllocator64<AP64<AddressSpaceView>>;
using Allocator64 = Allocator64ASVT<LocalAddressSpaceView>;

typedef CompactSizeClassMap SizeClassMap32;
template <typename AddressSpaceViewTy>
struct AP32 {
  static const vaddr kSpaceBeg = 0;
  static const u64 kSpaceSize = SANITIZER_MMAP_RANGE_SIZE;
  static const usize kMetadataSize = 16;
  typedef __asan::SizeClassMap32 SizeClassMap;
  static const usize kRegionSizeLog = 20;
  using AddressSpaceView = AddressSpaceViewTy;
  typedef AsanMapUnmapCallback MapUnmapCallback;
  static const usize kFlags = 0;
};
template <typename AddressSpaceView>
using Allocator32ASVT = SizeClassAllocator32<AP32<AddressSpaceView>>;
using Allocator32 = Allocator32ASVT<LocalAddressSpaceView>;
using Allocator32or64 = RuntimeSelectAllocator<Allocator32, Allocator64>;

static const usize kMaxNumberOfSizeClasses =
    SizeClassMap32::kNumClasses < SizeClassMap64::kNumClasses
        ? SizeClassMap64::kNumClasses
        : SizeClassMap32::kNumClasses;

template <typename AddressSpaceView>
using PrimaryAllocatorASVT =
    RuntimeSelectAllocator<Allocator32ASVT<AddressSpaceView>,
                           Allocator64ASVT<AddressSpaceView>>;
#elif SANITIZER_CAN_USE_ALLOCATOR64
# if SANITIZER_FUCHSIA
const vaddr kAllocatorSpace = ~(uptr)0;
const uptr kAllocatorSize  =  0x40000000000ULL;  // 4T.
# elif defined(__powerpc64__)
const vaddr kAllocatorSpace = ~(uptr)0;
const uptr kAllocatorSize  =  0x20000000000ULL;  // 2T.
# elif defined(__sparc__)
const vaddr kAllocatorSpace = ~(uptr)0;
const uptr kAllocatorSize = 0x20000000000ULL;  // 2T.
# elif SANITIZER_WINDOWS
const vaddr kAllocatorSpace = ~(uptr)0;
const uptr kAllocatorSize  =  0x8000000000ULL;  // 500G
# else
const vaddr kAllocatorSpace = 0x600000000000ULL;
const uptr kAllocatorSize  =  0x40000000000ULL;  // 4T.
# endif
typedef DefaultSizeClassMap SizeClassMap;
static const usize kMaxNumberOfSizeClasses = SizeClassMap::kNumClasses;
template <typename AddressSpaceViewTy>
struct AP64 {  // Allocator64 parameters. Deliberately using a short name.
  static const vaddr kSpaceBeg = kAllocatorSpace;
  static const usize kSpaceSize = kAllocatorSize;
  static const usize kMetadataSize = 0;
  typedef __asan::SizeClassMap SizeClassMap;
  typedef AsanMapUnmapCallback MapUnmapCallback;
  static const usize kFlags = 0;
  using AddressSpaceView = AddressSpaceViewTy;
};

template <typename AddressSpaceView>
using PrimaryAllocatorASVT = SizeClassAllocator64<AP64<AddressSpaceView>>;
#else  // Fallback to SizeClassAllocator32.
typedef CompactSizeClassMap SizeClassMap;
static const usize kMaxNumberOfSizeClasses = SizeClassMap::kNumClasses;
template <typename AddressSpaceViewTy>
struct AP32 {
  static const vaddr kSpaceBeg = 0;
  static const u64 kSpaceSize = SANITIZER_MMAP_RANGE_SIZE;
  static const usize kMetadataSize = 16;
  typedef __asan::SizeClassMap SizeClassMap;
  static const usize kRegionSizeLog = 20;
  using AddressSpaceView = AddressSpaceViewTy;
  typedef AsanMapUnmapCallback MapUnmapCallback;
  static const usize kFlags = 0;
};
template <typename AddressSpaceView>
using PrimaryAllocatorASVT = SizeClassAllocator32<AP32<AddressSpaceView> >;
#endif  // SANITIZER_CAN_USE_ALLOCATOR64

template <typename AddressSpaceView>
using AsanAllocatorASVT =
    CombinedAllocator<PrimaryAllocatorASVT<AddressSpaceView>>;
using AsanAllocator = AsanAllocatorASVT<LocalAddressSpaceView>;
using AllocatorCache = AsanAllocator::AllocatorCache;
using PrimaryAllocator = PrimaryAllocatorASVT<LocalAddressSpaceView>;

struct AsanThreadLocalMallocStorage {
  uptr quarantine_cache[16];
  AllocatorCache allocator_cache;
  void CommitBack();
 private:
  // These objects are allocated via mmap() and are zero-initialized.
  AsanThreadLocalMallocStorage() {}
};

void *asan_memalign(uptr alignment, usize size, BufferedStackTrace *stack,
                    AllocType alloc_type);
void asan_free(void *ptr, BufferedStackTrace *stack, AllocType alloc_type);
void asan_delete(void *ptr, usize size, usize alignment,
                 BufferedStackTrace *stack, AllocType alloc_type);

void *asan_malloc(usize size, BufferedStackTrace *stack);
void *asan_calloc(usize nmemb, usize size, BufferedStackTrace *stack);
void *asan_realloc(void *p, usize size, BufferedStackTrace *stack);
void *asan_reallocarray(void *p, usize nmemb, usize size,
                        BufferedStackTrace *stack);
void *asan_valloc(usize size, BufferedStackTrace *stack);
void *asan_pvalloc(usize size, BufferedStackTrace *stack);

void *asan_aligned_alloc(uptr alignment, usize size, BufferedStackTrace *stack);
int asan_posix_memalign(void **memptr, usize alignment, usize size,
                        BufferedStackTrace *stack);
uptr asan_malloc_usable_size(const void *ptr, uptr pc, uptr bp);

uptr asan_mz_size(const void *ptr);
void asan_mz_force_lock();
void asan_mz_force_unlock();

void PrintInternalAllocatorStats();
void AsanSoftRssLimitExceededCallback(bool exceeded);

AsanAllocator &get_allocator();

}  // namespace __asan
#endif  // ASAN_ALLOCATOR_H
