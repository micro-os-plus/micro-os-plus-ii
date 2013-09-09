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
/// \brief Locale (tiny) definitions.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS) || defined(__DOXYGEN__)

#include "portable/language/cpp/include/locale.h"
#include "portable/language/cpp/include/type_traits.h"

namespace os
{
  namespace std
  {

    // ========================================================================

    template<class TChar_T, class _OutputIterator>
      _LIBCPP_HIDDEN
      _OutputIterator
      __padAndOutput(_OutputIterator __s, const TChar_T* __ob,
          const TChar_T* __op, const TChar_T* __oe, ios_base& __iob,
          TChar_T __fl)
      {
        streamsize length = __oe - __ob;
        streamsize width = __iob.width();
        streamsize padding;

        if (width > length)
          {
            // compute how many padding positions we have to fill
            padding = width - length;
          }
        else
          {
            // no padding
            padding = 0;
          }

        // usually we have either left or right part, but in case of
        // internal format, the sign is aligned to the left and the rest
        // to the right

        // transfer the left side part, if any
        for (; __ob < __op; ++__ob, ++__s)
          {
            *__s = *__ob;
          }

        // pad, if needed
        for (; padding; --padding, ++__s)
          {
            *__s = __fl;
          }

        // transfer the right side part, if any
        for (; __ob < __oe; ++__ob, ++__s)
          {
            *__s = *__ob;
          }

        // clear width after each access
        __iob.width(0);

        return __s;
      }

    // ------------------------------------------------------------------------
    // support code, used to avoid calling snprintf()

    // inline, since the signed and unsigned versions are different anyway
    template<class TChar_T, class _OutputIterator, class _NumberT>
      inline _LIBCPP_ALWAYS_INLINE
      _OutputIterator
      __putGenericDecimal(_OutputIterator __s, ios_base& __iob, TChar_T __fl,
          _NumberT __v)
      {
        ios_base::fmtflags flags = __iob.flags();

        bool isNegative = false;

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wtautological-compare"
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wtype-limits"
#endif
        if (is_signed<_NumberT>::value && __v < 0)
          {
            isNegative = true;
            __v = -__v;
          }
#pragma GCC diagnostic pop

        size_t pos;
        TChar_T buff[sizeof(__v) * 5 / 2 + 1]; // one more for the sign

        for (pos = sizeof(buff); pos != 0;)
          {
            TChar_T ch = (__v % 10) + '0';
            buff[--pos] = ch;
            __v /= 10;
            if (__v == 0)
              break;
          }

        bool hasSign = false;
        if (is_signed<_NumberT>::value && isNegative)
          {
            buff[--pos] = '-';
            hasSign = true;
          }
        else
          {
            // positive
            if ((flags & ios_base::showpos) != 0)
              {
                buff[--pos] = '+';
                hasSign = true;
              }
          }

        const TChar_T* pBeg = &buff[pos];
        const TChar_T* pFill;
        const TChar_T* pEnd = &buff[sizeof(buff)];

        if ((flags & (ios_base::left | ios_base::internal)) == 0)
          {
            // right
            pFill = pBeg;
          }
        else if ((flags & ios_base::left) != 0)
          {
            // left
            pFill = pEnd;
          }
        else if ((flags & ios_base::internal) != 0)
          {
            // internal
            pFill = hasSign ? &buff[pos + 1] : pBeg;
          }
        else
          {
            // Should not reach this
            pFill = pBeg;
          }

        return __padAndOutput(__s, pBeg, pFill, pEnd, __iob, __fl);

      }

    // not inline, since it can be used both in signed and unsigned
    // instantiations of __putGenericInteger()

    template<class TChar_T, class _OutputIterator, class _NumberT>
      _LIBCPP_HIDDEN
      _OutputIterator
      __putUnsignedHex(_OutputIterator __s, ios_base& __iob, TChar_T __fl,
          _NumberT __v)
      {
        ios_base::fmtflags flags = __iob.flags();

        size_t pos;
        TChar_T buff[sizeof(__v) * 2 + 2]; // two more for the base

        bool isUpper = flags & ios_base::uppercase;
        TChar_T chLetter = (isUpper ? 'A' : 'a') - 10;

        for (pos = sizeof(buff); pos > 2;)
          {
            TChar_T ch = (__v & 0xF);
            if (ch < 10)
              {
                ch += '0';
              }
            else
              {
                ch += chLetter;
              }

            buff[--pos] = ch;
            __v >>= 4;
            if (__v == 0)
              break;
          }
        if ((flags & ios_base::showbase) != 0)
          {
            buff[--pos] = isUpper ? 'X' : 'x';
            buff[--pos] = '0';
          }

        const TChar_T* pBeg = &buff[pos];
        const TChar_T* pEnd = &buff[sizeof(buff)];
        const TChar_T* pFill;
        if ((flags & ios_base::left) != 0)
          {
            // left
            pFill = pEnd;
          }
        else
          {
            pFill = pBeg;
          }

        return __padAndOutput(__s, pBeg, pFill, pEnd, __iob, __fl);
      }

    // not inline, since it can be used both in signed and unsigned
    // instantiations of __putGenericInteger()

    template<class TChar_T, class _OutputIterator, class _NumberT>
      _LIBCPP_HIDDEN
      _OutputIterator
      __putUnsignedOctal(_OutputIterator __s, ios_base& __iob, TChar_T __fl,
          _NumberT __v)
      {
        ios_base::fmtflags flags = __iob.flags();

        size_t pos;
        TChar_T buff[(sizeof(__v) * 8 + 2) / 3];

        for (pos = sizeof(buff); pos > 0;)
          {
            TChar_T ch = (__v & 0x7) + '0';
            buff[--pos] = ch;
            __v >>= 3;
            if (__v == 0)
              break;
          }

        const TChar_T* pBeg = &buff[pos];
        const TChar_T* pEnd = &buff[sizeof(buff)];
        const TChar_T* pFill;
        if ((flags & ios_base::left) != 0)
          {
            // left
            pFill = pEnd;
          }
        else
          {
            pFill = pBeg;
          }

        return __padAndOutput(__s, pBeg, pFill, pEnd, __iob, __fl);
      }

    // inline, since the signed and unsigned versions are different anyway
    // due to __putGenericDecimal()
    template<class TChar_T, class _OutputIterator, class _NumberT>
      inline _LIBCPP_ALWAYS_INLINE
      _OutputIterator
      __putGenericInteger(_OutputIterator __s, ios_base& __iob, TChar_T __fl,
          _NumberT __v)
      {
        ios_base::fmtflags flags = __iob.flags();

        if ((flags & (ios_base::hex | ios_base::oct)) == 0)
          {
            // if no hex or octal, then decimal
            return __putGenericDecimal(__s, __iob, __fl, __v);
          }
        else if ((flags & ios_base::hex) != 0)
          {
            // hex
            return __putUnsignedHex(__s, __iob, __fl,
                static_cast<typename make_unsigned<_NumberT>::type>(__v));
          }
        else
          {
            // octal
            return __putUnsignedOctal(__s, __iob, __fl,
                static_cast<typename make_unsigned<_NumberT>::type>(__v));
          }
      }

    // ========================================================================

    template<class TChar_T, class _OutputIterator>
      _OutputIterator
      num_put<TChar_T, _OutputIterator>::put(iter_type __s, ios_base& __iob,
          char_type __fl, bool __v) const
      {
        if ((__iob.flags() & ios_base::boolalpha) == 0)
          {
#if defined(OS_INCLUDE_LIBCPP_16BIT_OPTIMISATIONS)
            return put(__s, __iob, __fl, static_cast<unsigned int>(__v));
#else
            return put(__s, __iob, __fl, static_cast<unsigned long>(__v));
#endif
          }

        const char* pStr = ((__v) ? "true" : "false");

        const TChar_T* pBeg = pStr;
        const TChar_T* pEnd = pStr + strlen(pStr);
        const TChar_T* pFill;

        ios_base::fmtflags flags = __iob.flags();

        if ((flags & ios_base::left) != 0)
          {
            // left
            pFill = pEnd;
          }
        else
          {
            pFill = pBeg;
          }

        return __padAndOutput(__s, pBeg, pFill, pEnd, __iob, __fl);
      }

#if defined(OS_INCLUDE_LIBCPP_16BIT_OPTIMISATIONS)

    template<class TChar_T, class _OutputIterator>
    _OutputIterator
    num_put<TChar_T, _OutputIterator>::put(iter_type __s, ios_base& __iob,
        char_type __fl, short __v) const
      {
        // in-place template instantiation
        return __putGenericInteger(__s, __iob, __fl, __v);
      }

    template<class TChar_T, class _OutputIterator>
    _OutputIterator
    num_put<TChar_T, _OutputIterator>::put(iter_type __s, ios_base& __iob,
        char_type __fl, unsigned short __v) const
      {
        // in-place template instantiation
        return __putGenericInteger(__s, __iob, __fl, __v);
      }

    template<class TChar_T, class _OutputIterator>
    _OutputIterator
    num_put<TChar_T, _OutputIterator>::put(iter_type __s, ios_base& __iob,
        char_type __fl, int __v) const
      {
        // in-place template instantiation
        return __putGenericInteger(__s, __iob, __fl, __v);
      }

    template<class TChar_T, class _OutputIterator>
    _OutputIterator
    num_put<TChar_T, _OutputIterator>::put(iter_type __s, ios_base& __iob,
        char_type __fl, unsigned int __v) const
      {
        // in-place template instantiation
        return __putGenericInteger(__s, __iob, __fl, __v);
      }

#endif

    template<class TChar_T, class _OutputIterator>
      _OutputIterator
      num_put<TChar_T, _OutputIterator>::put(iter_type __s, ios_base& __iob,
          char_type __fl, long __v) const
      {
        // in-place template instantiation
        return __putGenericInteger(__s, __iob, __fl, __v);
      }

    template<class TChar_T, class _OutputIterator>
      _OutputIterator
      num_put<TChar_T, _OutputIterator>::put(iter_type __s, ios_base& __iob,
          char_type __fl, unsigned long __v) const
      {
        // in-place template instantiation
        return __putGenericInteger(__s, __iob, __fl, __v);
      }

    template<class TChar_T, class _OutputIterator>
      _OutputIterator
      num_put<TChar_T, _OutputIterator>::put(iter_type __s, ios_base& __iob,
          char_type __fl, long long __v) const
      {
        // in-place template instantiation
        return __putGenericInteger(__s, __iob, __fl, __v);
      }

    template<class TChar_T, class _OutputIterator>
      _OutputIterator
      num_put<TChar_T, _OutputIterator>::put(iter_type __s, ios_base& __iob,
          char_type __fl, unsigned long long __v) const
      {
        // in-place template instantiation
        return __putGenericInteger(__s, __iob, __fl, __v);
      }

    template<class TChar_T, class _OutputIterator>
      _OutputIterator
      num_put<TChar_T, _OutputIterator>::put(iter_type __s, ios_base& __iob,
          char_type __fl, double __v __attribute__((unused))) const
      {

        TChar_T buff[] = "(tbd)";

        const TChar_T* pBeg = &buff[0];
        const TChar_T* pEnd = &buff[sizeof(buff)];
        const TChar_T* pFill = pBeg;

        return __padAndOutput(__s, pBeg, pFill, pEnd, __iob, __fl);

      }

    template<class TChar_T, class _OutputIterator>
      _OutputIterator
      num_put<TChar_T, _OutputIterator>::put(iter_type __s, ios_base& __iob,
          char_type __fl, long double __v __attribute__((unused))) const
      {

        TChar_T buff[] = "(tbd)";

        const TChar_T* pBeg = &buff[0];
        const TChar_T* pEnd = &buff[sizeof(buff)];
        const TChar_T* pFill = pBeg;

        return __padAndOutput(__s, pBeg, pFill, pEnd, __iob, __fl);

      }

    template<class TChar_T, class _OutputIterator>
      _OutputIterator
      num_put<TChar_T, _OutputIterator>::put(iter_type __s, ios_base& __iob,
          char_type __fl, const void* __v) const
      {
        ios_base::fmtflags flags = __iob.flags();

        union
        {
          unsigned long uval;
          const void * ptr;
        } u;

        u.ptr = __v;

        size_t pos;
        TChar_T buff[sizeof(__v) * 2 + 2]; // two more for the base

        bool isUpper = flags & ios_base::uppercase;
        TChar_T chLetter = (isUpper ? 'A' : 'a') - 10;

        for (pos = sizeof(buff); pos > 2;)
          {
            TChar_T ch = (u.uval & 0xF);
            if (ch < 10)
              {
                ch += '0';
              }
            else
              {
                ch += chLetter;
              }

            buff[--pos] = ch;
            u.uval >>= 4;
          }
        buff[--pos] = isUpper ? 'X' : 'x';
        buff[--pos] = '0';

        const TChar_T* pBeg = &buff[pos];
        const TChar_T* pEnd = &buff[sizeof(buff)];
        const TChar_T* pFill;
        if ((flags & ios_base::left) != 0)
          {
            // left
            pFill = pEnd;
          }
        else
          {
            pFill = pBeg;
          }

        return __padAndOutput(__s, pBeg, pFill, pEnd, __iob, __fl);
      }

    // ------------------------------------------------------------------------
    // Template explicit instantiation
    template class num_put<char> ;

    // Global object instantiation
    num_put<char> num_put_char_tiny;
  }
}

#endif
