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

    /// \details
    /// This is called from the public constructor.  It is not virtual and
    /// cannot be redefined.
    ///
    /// \post
    /// Member | Postcondition
    /// -------|----------
    /// rdbuf() | sb
    /// tie() | 0
    /// rdstate() | goodbit if sb is not a null pointer, otherwise badbit.
    /// exceptions() | goodbit
    /// flags() | skipws \| dec
    /// width() | 0
    /// precision() | 6
    /// fill() | widen(’ ’);
    /// getloc() | a copy of the value returned by locale()
    /// iarray | a null pointer
    /// parray | a null pointer
    template<class TChar_T, class TTraits_T>
      void
      basic_ios<TChar_T, TTraits_T>::init(
          basic_streambuf<TChar_T, TTraits_T>* sb)
      {
        ios_base::__init();

        m_rdbuf = sb;

        m_rdstate = m_rdbuf ? goodbit : badbit;
        m_exceptions = goodbit;

        m_tie = 0;
        m_fill = traits_type::eof();
      }

    /// \details
    /// This destructor does nothing.  More specifically, it does not
    /// destroy the streambuf held by `rdbuf()`.
    template<class TChar_T, class TTraits_T>
      basic_ios<TChar_T, TTraits_T>::~basic_ios()
      {
      }

    /// \details
    /// All fields of `rhs` are copied into this object except that `rdbuf()`
    /// and `rdstate()` remain unchanged.
    ///
    /// If `(this == &rhs)` does nothing. Otherwise assigns to the member
    /// objects of `*this` the corresponding member objects of `rhs` as follows:
    /// -# calls each registered callback pair `(fn, index)` as
    /// `(*fn)(erase_event, *this, index);`
    /// -# assigns to the member objects of `*this` the corresponding
    /// member objects of `rhs`, except that
    ///  + `rdstate()`, `rdbuf()`, and `exceptions()` are left unchanged;
    ///  + the contents of arrays pointed at by `pword` and `iword` are copied,
    /// not the pointers themselves; and
    /// if any newly stored pointer values in `*this` point at objects
    /// stored outside the object `rhs` and those objects are destroyed
    /// when `rhs` is destroyed, the newly stored pointer values are
    /// altered to point at newly constructed copies of the objects;
    /// -# calls each callback pair that was copied from `rhs` as
    /// `(*fn)(copyfmt_event, *this, index);`
    /// -# calls `exceptions(rhs.except())`.
    template<class TChar_T, class TTraits_T>
      basic_ios<TChar_T, TTraits_T>&
      basic_ios<TChar_T, TTraits_T>::copyfmt(const basic_ios& rhs)
      {
        if (this != &rhs)
          {
#if defined(OS_INCLUDE_STD_IOS_BASE_CALLBACKS)
            __call_callbacks(erase_event);
#endif

#if defined(SHOULD_BE_DELETED)
            ios_base::copyfmt(rhs);
#endif

#if defined(OS_INCLUDE_STD_IOS_BASE_CALLBACKS)
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
#if defined(OS_INCLUDE_STD_EXCEPTIONS)
                if (!new_callbacks)
                throw bad_alloc();
#endif  // OS_INCLUDE_STD_EXCEPTIONS
                new_ints.reset((int*) malloc(sizeof(int) * rhs.__event_size_));
#if defined(OS_INCLUDE_STD_EXCEPTIONS)
                if (!new_ints)
                throw bad_alloc();
#endif  // OS_INCLUDE_STD_EXCEPTIONS
              }
#endif
#if defined(OS_INCLUDE_STD_IOS_BASE_STORAGE)
            if (__iarray_cap_ < rhs.__iarray_size_)
              {
                new_longs.reset((long*) malloc(sizeof(long) * rhs.__iarray_size_));
#if defined(OS_INCLUDE_STD_EXCEPTIONS)
                if (!new_longs)
                throw bad_alloc();
#endif  // OS_INCLUDE_STD_EXCEPTIONS
              }
            if (__parray_cap_ < rhs.__parray_size_)
              {
                new_pointers.reset(
                    (void**) malloc(sizeof(void*) * rhs.__parray_size_));
#if defined(OS_INCLUDE_STD_EXCEPTIONS)
                if (!new_pointers)
                throw bad_alloc();
#endif  // OS_INCLUDE_STD_EXCEPTIONS
              }
#endif

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
// Got everything we need.  Copy everything but __rdstate_, __rdbuf_ and __exceptions_
            m_fmtflags = rhs.m_fmtflags;
            m_precision = rhs.m_precision;
            m_width = rhs.m_width;

            locale& lhs_loc = *(locale*) &m_locale;
            locale& rhs_loc = *(locale*) &rhs.m_locale;
            lhs_loc = rhs_loc;
#endif

#if defined(OS_INCLUDE_STD_IOS_BASE_CALLBACKS)
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

            m_tie = rhs.m_tie;
            m_fill = rhs.m_fill;

#if defined(OS_INCLUDE_STD_IOS_BASE_CALLBACKS)
            __call_callbacks(copyfmt_event);
#endif
            exceptions(rhs.exceptions());
          }
        return *this;
      }

    /// \details
    /// See `ios_base::iostate` for the possible bit values.  Most
    /// users will not need to pass an argument.
    template<class TChar_T, class TTraits_T>
      void
      basic_ios<TChar_T, TTraits_T>::clear(iostate state)
      {
        if (m_rdbuf)
          {
            m_rdstate = state;
          }
        else
          {
            m_rdstate = state | badbit;
          }
#if defined(OS_INCLUDE_STD_EXCEPTIONS)
        if (((state | (m_rdbuf ? goodbit : badbit)) & __exceptions_) != 0)
          {
            throw failure("ios_base::clear");
          }
#endif  // OS_INCLUDE_STD_EXCEPTIONS
      }

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

  template<class TChar_T, class TTraits_T>
  void
  basic_ios<TChar_T, TTraits_T>::__set_badbit_and_consider_rethrow()
    {
      m_rdstate |= badbit;
#if defined(OS_INCLUDE_STD_EXCEPTIONS)
      if (__exceptions_ & badbit)
        {
          throw;
        }
#endif  // OS_INCLUDE_STD_EXCEPTIONS
    }

  template<class TChar_T, class TTraits_T>
  void
  basic_ios<TChar_T, TTraits_T>::__set_failbit_and_consider_rethrow()
    {
      m_rdstate |= failbit;
#if defined(OS_INCLUDE_STD_EXCEPTIONS)
      if (__exceptions_ & failbit)
        {
          throw;
        }
#endif  // OS_INCLUDE_STD_EXCEPTIONS
    }

#endif

}
}

#endif // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_IOS_CPP_H_
