//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//
// [Partly inspired from the LLVM libcxx sources].
// Copyright (c) 2009-2013 by the contributors listed in
// 'LLVM libcxx Credits.txt'. See 'LLVM libcxx License.txt' for details.
//

/// \file
/// \brief Initializer list definitions.

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INITIALIZERLIST_H
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INITIALIZERLIST_H

#include "portable/core/include/ConfigDefines.h"

#include "portable/language/cpp/include/internal/__config.h"
#include "portable/language/cpp/include/cstddef.h"

namespace os
{
  namespace std  // purposefully not versioned
  {

#ifndef _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS

    template<class _Ep>
      class initializer_list
      {
        const _Ep* __begin_;
        os::std::size_t __size_;

        initializer_list(const _Ep* __b, os::std::size_t __s) noexcept;

      public:
        typedef _Ep value_type;
        typedef const _Ep& reference;
        typedef const _Ep& const_reference;
        typedef os::std::size_t size_type;

        typedef const _Ep* iterator;
        typedef const _Ep* const_iterator;

        initializer_list() noexcept;

        os::std::size_t
        __attribute__((always_inline))
        size() const noexcept
        {
          return __size_;
        }

        const _Ep*
        __attribute__((always_inline))
        begin() const noexcept
        {
          return __begin_;
        }

        const _Ep*
        __attribute__((always_inline))
        end() const noexcept
        {
          return __begin_ + __size_;
        }
      };

    template<class _Ep>
      inline
      __attribute__((always_inline))
      initializer_list<_Ep>::initializer_list(const _Ep* __b, os::std::size_t __s)
noexcept          : //
          __begin_(__b),
          __size_(__s)
            {
            }

    template<class _Ep>
      inline
      __attribute__((always_inline))
      initializer_list<_Ep>::initializer_list()
noexcept          : //
          __begin_(nullptr),
          __size_(0)
            {
            }

    // free standing iterator functions
    template<class _Ep>
      inline const _Ep*
      __attribute__((always_inline))
      begin(initializer_list<_Ep> __il) noexcept
      {
        return __il.begin();
      }

    template<class _Ep>
      inline const _Ep*
      __attribute__((always_inline))
      end(initializer_list<_Ep> __il) noexcept
      {
        return __il.end();
      }

#endif  // _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS
  }  // namespace std
} // namespace os

#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INITIALIZERLIST_H
