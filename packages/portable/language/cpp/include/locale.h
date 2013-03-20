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

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_LOCALE_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_LOCALE_H_

#include "portable/core/include/OS_Defines.h"

#include "portable/language/cpp/include/internal/__config.h"
#include "portable/language/cpp/include/internal/_locale.h"
#include "portable/language/cpp/include/ios.h"
#include "portable/language/cpp/include/streambuf.h"
#include "portable/language/cpp/include/iterator.h"

namespace os
{
  namespace std
  {

    // This is a tiny version of locale

    template<class _CharT, class _OutputIterator = ostreambuf_iterator<_CharT> >
      class _LIBCPP_VISIBLE num_put

      {
      public:
        typedef _CharT char_type;
        typedef _OutputIterator iter_type;

        iter_type
        put(iter_type __s, ios_base& __iob, char_type __fl, bool __v) const;

#if defined(OS_INCLUDE_LIBCPP_16BIT_OPTIMISATIONS)

        // The next 4 member functions are not standard, but were added
        // for 16bit platforms, to avoid doing all math as 32bit.

        iter_type
        put(iter_type __s, ios_base& __iob, char_type __fl, short __v) const;

        iter_type
        put(iter_type __s, ios_base& __iob, char_type __fl,
            unsigned short __v) const;

        iter_type
        put(iter_type __s, ios_base& __iob, char_type __fl, int __v) const;

        iter_type
        put(iter_type __s, ios_base& __iob, char_type __fl,
            unsigned int __v) const;

#endif

        iter_type
        put(iter_type __s, ios_base& __iob, char_type __fl, long __v) const;

        iter_type
        put(iter_type __s, ios_base& __iob, char_type __fl,
            unsigned long __v) const;

        iter_type
        put(iter_type __s, ios_base& __iob, char_type __fl,
            long long __v) const;

        iter_type
        put(iter_type __s, ios_base& __iob, char_type __fl,
            unsigned long long __v) const;

        iter_type
        put(iter_type __s, ios_base& __iob, char_type __fl, double __v) const;

        iter_type
        put(iter_type __s, ios_base& __iob, char_type __fl,
            long double __v) const;

        iter_type
        put(iter_type __s, ios_base& __iob, char_type __fl,
            const void* __v) const;

      };

    extern template class num_put<char> ;

    extern num_put<char> num_put_char_tiny;

    template<class _Facet>
      inline _LIBCPP_INLINE_VISIBILITY
      const _Facet&
      use_facet(const locale& __l __attribute__((unused)))
      {
        return static_cast<const _Facet&>(num_put_char_tiny);
      }

    template<class _CharT, class _OutputIterator>
      _LIBCPP_HIDDEN
      _OutputIterator
      __padAndOutput(_OutputIterator __s, const _CharT* __ob,
          const _CharT* __op, const _CharT* __oe, ios_base& __iob, _CharT __fl);

  }
}

#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_LOCALE_H_
