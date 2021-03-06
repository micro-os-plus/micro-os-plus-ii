//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//
// [Partly inspired from the LLVM libcxx sources].
// Copyright (c) 2009-2013 by the contributors listed in
// 'LLVM libcxx Credits.txt'. See 'LLVM libcxx License.txt' for details.
//
// References are to ISO/IEC 14882:2011(E) Third edition (2011-09-01).
//

/// \file
/// \brief Memory definitions.

#include "portable/core/include/ConfigDefines.h"

//#define _LIBCPP_BUILDING_MEMORY
#include "portable/language/cpp/include/memory.h"
//#include "mutex"
//#include "thread"

namespace os
{
  namespace std
  {

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

    namespace
      {

        template <class T>
        inline T
        increment(T& t) noexcept
          {
            return __sync_add_and_fetch(&t, 1);
          }

        template <class T>
        inline T
        decrement(T& t) noexcept
          {
            return __sync_add_and_fetch(&t, -1);
          }

      }  // namespace

    const allocator_arg_t allocator_arg = allocator_arg_t();

    bad_weak_ptr::~bad_weak_ptr() noexcept
      {}

    const char*
    bad_weak_ptr::what() const noexcept
      {
        return "bad_weak_ptr";
      }

    __shared_count::~__shared_count()
      {
      }

    void
    __shared_count::__add_shared() noexcept
      {
        increment(__shared_owners_);
      }

    bool
    __shared_count::__release_shared() noexcept
      {
        if (decrement(__shared_owners_) == -1)
          {
            __on_zero_shared();
            return true;
          }
        return false;
      }

    __shared_weak_count::~__shared_weak_count()
      {
      }

    void
    __shared_weak_count::__add_shared() noexcept
      {
        __shared_count::__add_shared();
      }

    void
    __shared_weak_count::__add_weak() noexcept
      {
        increment(__shared_weak_owners_);
      }

    void
    __shared_weak_count::__release_shared() noexcept
      {
        if (__shared_count::__release_shared())
        __release_weak();
      }

    void
    __shared_weak_count::__release_weak() noexcept
      {
        if (decrement(__shared_weak_owners_) == -1)
        __on_zero_shared_weak();
      }

    __shared_weak_count*
    __shared_weak_count::lock() noexcept
      {
        long object_owners = __shared_owners_;
        while (object_owners != -1)
          {
            if (__sync_bool_compare_and_swap(&__shared_owners_,
                    object_owners,
                    object_owners+1))
            return this;
            object_owners = __shared_owners_;
          }
        return 0;
      }

#ifndef _LIBCPP_NO_RTTI

    const void*
    __shared_weak_count::__get_deleter(const type_info&) const noexcept
      {
        return 0;
      }

#endif  // _LIBCPP_NO_RTTI
#if __has_feature(cxx_atomic)

    static const std::size_t __sp_mut_count = 16;
    static mutex mut_back[__sp_mut_count];

    constexpr __sp_mut::__sp_mut(void* p) noexcept
    : __lx(p)
      {
      }

    void
    __sp_mut::lock() noexcept
      {
        mutex& m = *static_cast<mutex*>(__lx);
        unsigned count = 0;
        while (!m.try_lock())
          {
            if (++count > 16)
              {
                m.lock();
                break;
              }
            this_thread::yield();
          }
      }

    void
    __sp_mut::unlock() noexcept
      {
        static_cast<mutex*>(__lx)->unlock();
      }

    __sp_mut&
    __get_sp_mut(const void* p)
      {
        static __sp_mut muts[__sp_mut_count]
          {
            &mut_back[ 0], &mut_back[ 1], &mut_back[ 2], &mut_back[ 3],
            &mut_back[ 4], &mut_back[ 5], &mut_back[ 6], &mut_back[ 7],
            &mut_back[ 8], &mut_back[ 9], &mut_back[10], &mut_back[11],
            &mut_back[12], &mut_back[13], &mut_back[14], &mut_back[15]
          };
        return muts[hash<const void*>()(p) & (__sp_mut_count-1)];
      }

#endif // __has_feature(cxx_atomic)
    void
    declare_reachable(void*)
      {
      }

    void
    declare_no_pointers(char*, size_t)
      {
      }

    void
    undeclare_no_pointers(char*, size_t)
      {
      }

    pointer_safety
    get_pointer_safety() noexcept
      {
        return pointer_safety::relaxed;
      }

    void*
    __undeclare_reachable(void* p)
      {
        return p;
      }

#endif // defined(OS_SKIP_NOT_YET_IMPLEMENTED)
    /// \details
    /// If it is possible to fit size bytes of storage aligned by
    /// alignment into the bu ffer pointed to by ptr with length space,
    /// the function updates ptr to point to the first possible
    /// address of such storage and decreases space by the number
    /// of bytes used for alignment. Otherwise, the function does
    /// nothing.
    void*
    align(size_t alignment, size_t size, void*& ptr, size_t& space)
    {
      void* r = nullptr;
      if (size <= space)
        {
          char* p1 = static_cast<char*>(ptr);
          char* p2 = (char*) ((size_t) (p1 + (alignment - 1)) & -alignment);
          size_t d = static_cast<size_t>(p2 - p1);
          if (d <= space - size)
            {
              r = p2;
              ptr = r;
              space -= d;
            }
        }
      return r;
    }

  } // namespace std
} // namespace os

