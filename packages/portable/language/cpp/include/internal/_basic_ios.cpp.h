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

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_IOS_CPP_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_IOS_CPP_H_

#include "portable/core/include/OS_Defines.h"

#include "portable/language/cpp/include/ios.h"

namespace os
{
  namespace std
  {

    // init
    template<class _CharT, class _Traits>
      void
      basic_ios<_CharT, _Traits>::init(
          basic_streambuf<char_type, traits_type>* __sb)
      {
        ios_base::__init();

        m_rdbuf = __sb;

        m_rdstate = m_rdbuf ? goodbit : badbit;
        m_exceptions = goodbit;

        m_tie = 0;
        m_fill = traits_type::eof();
      }

    template<class _CharT, class _Traits>
      basic_ios<_CharT, _Traits>::~basic_ios()
      {
        ;
      }

    template<class _CharT, class _Traits>
      basic_ios<_CharT, _Traits>&
      basic_ios<_CharT, _Traits>::copyfmt(const basic_ios& __rhs)
      {
        if (this != &__rhs)
          {
            __call_callbacks(erase_event);

#if defined(SHOULD_BE_DELETED)
            ios_base::copyfmt(__rhs);
#endif

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
            // If we can't acquire the needed resources, throw bad_alloc (can't set badbit)
            // Don't alter *this until all needed resources are aquired
            unique_ptr<event_callback, void
            (*)(void*)> new_callbacks(0, free);
            unique_ptr<int, void
            (*)(void*)> new_ints(0, free);
            unique_ptr<long, void
            (*)(void*)> new_longs(0, free);
            unique_ptr<void*, void
            (*)(void*)> new_pointers(0, free);
            if (__event_cap_ < rhs.__event_size_)
              {
                new_callbacks.reset(
                    (event_callback*) malloc(
                        sizeof(event_callback) * rhs.__event_size_));
#ifndef _LIBCPP_NO_EXCEPTIONS
                if (!new_callbacks)
                throw bad_alloc();
#endif  // _LIBCPP_NO_EXCEPTIONS
                new_ints.reset((int*) malloc(sizeof(int) * rhs.__event_size_));
#ifndef _LIBCPP_NO_EXCEPTIONS
                if (!new_ints)
                throw bad_alloc();
#endif  // _LIBCPP_NO_EXCEPTIONS
              }
            if (__iarray_cap_ < rhs.__iarray_size_)
              {
                new_longs.reset((long*) malloc(sizeof(long) * rhs.__iarray_size_));
#ifndef _LIBCPP_NO_EXCEPTIONS
                if (!new_longs)
                throw bad_alloc();
#endif  // _LIBCPP_NO_EXCEPTIONS
              }
            if (__parray_cap_ < rhs.__parray_size_)
              {
                new_pointers.reset(
                    (void**) malloc(sizeof(void*) * rhs.__parray_size_));
#ifndef _LIBCPP_NO_EXCEPTIONS
                if (!new_pointers)
                throw bad_alloc();
#endif  // _LIBCPP_NO_EXCEPTIONS
              }
            // Got everything we need.  Copy everything but __rdstate_, __rdbuf_ and __exceptions_
            __fmtflags_ = rhs.__fmtflags_;
            __precision_ = rhs.__precision_;
            __width_ = rhs.__width_;
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
            locale& lhs_loc = *(locale*) &__loc_;
            locale& rhs_loc = *(locale*) &rhs.__loc_;
#endif
            lhs_loc = rhs_loc;
            if (__event_cap_ < rhs.__event_size_)
              {
                free(__fn_);
                __fn_ = new_callbacks.release();
                free(__index_);
                __index_ = new_ints.release();
                __event_cap_ = rhs.__event_size_;
              }
            for (__event_size_ = 0; __event_size_ < rhs.__event_size_;
                ++__event_size_)
              {
                __fn_[__event_size_] = rhs.__fn_[__event_size_];
                __index_[__event_size_] = rhs.__index_[__event_size_];
              }
            if (__iarray_cap_ < rhs.__iarray_size_)
              {
                free(__iarray_);
                __iarray_ = new_longs.release();
                __iarray_cap_ = rhs.__iarray_size_;
              }
            for (__iarray_size_ = 0; __iarray_size_ < rhs.__iarray_size_;
                ++__iarray_size_)
            __iarray_[__iarray_size_] = rhs.__iarray_[__iarray_size_];
            if (__parray_cap_ < rhs.__parray_size_)
              {
                free(__parray_);
                __parray_ = new_pointers.release();
                __parray_cap_ = rhs.__parray_size_;
              }
            for (__parray_size_ = 0; __parray_size_ < rhs.__parray_size_;
                ++__parray_size_)
            __parray_[__parray_size_] = rhs.__parray_[__parray_size_];

#endif

            m_tie = __rhs.m_tie;
            m_fill = __rhs.m_fill;

            __call_callbacks(copyfmt_event);
            exceptions(__rhs.exceptions());
          }
        return *this;
      }

    template<class _CharT, class _Traits>
      void
      basic_ios<_CharT, _Traits>::clear(iostate state)
      {
        if (m_rdbuf)
          {
            m_rdstate = state;
          }
        else
          {
            m_rdstate = state | badbit;
          }
#ifndef _LIBCPP_NO_EXCEPTIONS
        if (((state | (m_rdbuf ? goodbit : badbit)) & __exceptions_) != 0)
          {
            throw failure("ios_base::clear");
          }
#endif  // _LIBCPP_NO_EXCEPTIONS
      }

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

  template<class _CharT, class _Traits>
  void
  basic_ios<_CharT, _Traits>::__set_badbit_and_consider_rethrow()
    {
      m_rdstate |= badbit;
#ifndef _LIBCPP_NO_EXCEPTIONS
      if (__exceptions_ & badbit)
        {
          throw;
        }
#endif  // _LIBCPP_NO_EXCEPTIONS
    }

  template<class _CharT, class _Traits>
  void
  basic_ios<_CharT, _Traits>::__set_failbit_and_consider_rethrow()
    {
      m_rdstate |= failbit;
#ifndef _LIBCPP_NO_EXCEPTIONS
      if (__exceptions_ & failbit)
        {
          throw;
        }
#endif  // _LIBCPP_NO_EXCEPTIONS
    }

#endif

}
}

#endif // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_IOS_CPP_H_
