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

#include "portable/core/include/OS_Defines.h"

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS) || defined(__DOXYGEN__)

#include "portable/language/cpp/include/ios.h"
#include "portable/language/cpp/include/internal/_basic_ios.cpp.h"
#include "portable/language/cpp/include/streambuf.cpp.h"
#include "portable/language/cpp/include/limits.h"
#include "portable/language/cpp/include/cstdlib.h"

#if 0
#include "ios"
#include "streambuf"
#include "istream"
#include "string"
#include "__locale"
#include "algorithm"
#include "memory"
#include "new"
#include "limits"
#include <stdlib.h>
#endif

namespace os
{
  namespace std
  {

    // Explicit instantiations of all related templates
    template class basic_ios<char> ;

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
    template class basic_istream<char>;
    template class basic_ostream<char>;
    template class basic_iostream<char>;
#endif

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

    template class basic_ios<wchar_t>;
    template class basic_streambuf<wchar_t>;
    template class basic_istream<wchar_t>;
    template class basic_ostream<wchar_t>;

#endif

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
    class _LIBCPP_HIDDEN __iostream_category
    : public __do_message
      {
      public:
        virtual const char* name() const _NOEXCEPT;
        virtual string message(int ev) const;
      };

    const char*
    __iostream_category::name() const
    _NOEXCEPT
      {
        return "iostream";
      }

    string
    __iostream_category::message(int ev) const
      {
        if (ev != static_cast<int>(io_errc::stream)
#ifdef ELAST
            && ev <= ELAST
#endif
        )
        return __do_message::message(ev);
        return string("unspecified iostream_category error");
      }

    const error_category&
    iostream_category()
      {
        static __iostream_category s;
        return s;
      }

    // ios_base::failure

    ios_base::failure::failure(const string& msg, const error_code& ec)
    : system_error(ec, msg)
      {
      }

    ios_base::failure::failure(const char* msg, const error_code& ec)
    : system_error(ec, msg)
      {
      }

    ios_base::failure::~failure() throw ()
      {
      }
#endif

    // ios_base locale

    const ios_base::fmtflags ios_base::boolalpha;
    const ios_base::fmtflags ios_base::dec;
    const ios_base::fmtflags ios_base::fixed;
    const ios_base::fmtflags ios_base::hex;
    const ios_base::fmtflags ios_base::internal;
    const ios_base::fmtflags ios_base::left;
    const ios_base::fmtflags ios_base::oct;
    const ios_base::fmtflags ios_base::right;
    const ios_base::fmtflags ios_base::scientific;
    const ios_base::fmtflags ios_base::showbase;
    const ios_base::fmtflags ios_base::showpoint;
    const ios_base::fmtflags ios_base::showpos;
    const ios_base::fmtflags ios_base::skipws;
    const ios_base::fmtflags ios_base::unitbuf;
    const ios_base::fmtflags ios_base::uppercase;
    const ios_base::fmtflags ios_base::adjustfield;
    const ios_base::fmtflags ios_base::basefield;
    const ios_base::fmtflags ios_base::floatfield;

    const ios_base::iostate ios_base::badbit;
    const ios_base::iostate ios_base::eofbit;
    const ios_base::iostate ios_base::failbit;
    const ios_base::iostate ios_base::goodbit;

    const ios_base::openmode ios_base::app;
    const ios_base::openmode ios_base::ate;
    const ios_base::openmode ios_base::binary;
    const ios_base::openmode ios_base::in;
    const ios_base::openmode ios_base::out;
    const ios_base::openmode ios_base::trunc;

#if defined(OS_INCLUDE_STD_IOS_BASE_CALLBACKS)
    void
    ios_base::__call_callbacks(event ev __attribute__((unused)))
    {
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      for (size_t i = __event_size_; i;)
        {
          --i;
          __fn_[i](ev, *this, __index_[i]);
        }
#endif
    }
#endif

    // locale

    /// \details
    /// Sets the new locale for this stream, and then invokes each callback
    /// with \c imbue_event.
    locale
    ios_base::imbue(const locale& newloc)
    {
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      static_assert(sizeof(locale) == sizeof(m_locale), "");
#endif
      locale& loc_storage = *(locale*) &m_locale;
      locale oldloc = loc_storage;
      loc_storage = newloc;
#if defined(OS_INCLUDE_STD_IOS_BASE_CALLBACKS)
      __call_callbacks(imbue_event);
#endif
      return oldloc;
    }

    /// \details
    /// If no locale has been imbued, a copy of the global C++ locale,
    /// locale(), in effect at the time of construction. Otherwise,
    /// returns the imbued locale, to be used to perform
    /// locale-dependent input and output operations.
    locale
    ios_base::getloc() const
    {
      const locale& loc_storage = *(locale*) &m_locale;
      return loc_storage;
    }

#if defined(OS_INCLUDE_STD_IOS_BASE_STORAGE)
    // xalloc

    int ios_base::ms_xindex = 0;

    ///
     /// \details
     /// This function returns a unique integer every time it is called.  It
     /// can be used for any purpose, but is primarily intended to be a unique
     /// index for the iword and pword functions.  The expectation is that an
     /// application calls xalloc in order to obtain an index in the iword and
     /// pword arrays that can be used without fear of conflict.
     ///
     /// The implementation maintains a static variable that is incremented and
     /// returned on each invocation.  xalloc is guaranteed to return an index
     /// that is safe to use in the iword and pword arrays.
   int
    ios_base::xalloc()
      {
        return ms_xindex++;
      }

   ///
   /// \details
   /// The iword function provides access to an array of integers that can be
   /// used for any purpose.  The array grows as required to hold the
   /// supplied index.  All integers in the array are initialized to 0.
   ///
   /// The implementation reserves several indices.  You should use xalloc to
   /// obtain an index that is safe to use.  Also note that since the array
   /// can grow dynamically, it is not safe to hold onto the reference.
    long&
    ios_base::iword(int index)
      {
        size_t req_size = static_cast<size_t>(index) + 1;
        if (req_size > __iarray_cap_)
          {
            size_t newcap;
            const size_t mx = numeric_limits < size_t > ::max();
            if (req_size < mx / 2)
            newcap = _VSTD::max(2 * __iarray_cap_, req_size);
            else
            newcap = mx;
            long* iarray = (long*) realloc(__iarray_, newcap * sizeof(long));
            if (iarray == 0)
              {
                setstate(badbit);
                static long error;
                error = 0;
                return error;
              }
            __iarray_ = iarray;
            for (long* p = __iarray_ + __iarray_size_; __iarray_cap_ < newcap;
                ++__iarray_cap_, ++p)
            *p = 0;
          }
        __iarray_size_ = max < size_t > (__iarray_size_, req_size);
        return __iarray_[index];
      }

    ///
    /// \details
    /// The pword function provides access to an array of pointers that can be
    /// used for any purpose.  The array grows as required to hold the
    /// supplied index.  All pointers in the array are initialized to 0.
    ///
    /// The implementation reserves several indices.  You should use xalloc to
    /// obtain an index that is safe to use.  Also note that since the array
    /// can grow dynamically, it is not safe to hold onto the reference.
    void*&
    ios_base::pword(int index)
      {
        size_t req_size = static_cast<size_t>(index) + 1;
        if (req_size > __parray_cap_)
          {
            size_t newcap;
            const size_t mx = numeric_limits < size_t > ::max();
            if (req_size < mx / 2)
            newcap = _VSTD::max(2 * __parray_cap_, req_size);
            else
            newcap = mx;
            void** parray = (void**) realloc(__parray_, newcap * sizeof(void*));
            if (parray == 0)
              {
                setstate(badbit);
                static void* error;
                error = 0;
                return error;
              }
            __parray_ = parray;
            for (void** p = __parray_ + __parray_size_; __parray_cap_ < newcap;
                ++__parray_cap_, ++p)
            *p = 0;
          }
        __parray_size_ = max < size_t > (__parray_size_, req_size);
        return __parray_[index];
      }
#endif

#if defined(OS_INCLUDE_STD_IOS_BASE_CALLBACKS)
    // register_callback

    /// \details
    /// Registers a function as an event callback with an integer parameter to
    /// be passed to the function when invoked.  Multiple copies of the
    /// function are allowed.  If there are multiple callbacks, they are
    /// invoked in the order they were registered.
    void
    ios_base::register_callback(event_callback fn __attribute__((unused)),
        int index __attribute__((unused)))
    {
      size_t req_size = __event_size_ + 1;
      if (req_size > __event_cap_)
        {
          size_t newcap;
          const size_t mx = numeric_limits < size_t > ::max();
          if (req_size < mx / 2)
          newcap = _VSTD::max(2 * __event_cap_, req_size);
          else
          newcap = mx;
          event_callback* fns = (event_callback*) realloc(__fn_,
              newcap * sizeof(event_callback));
          if (fns == 0)
          setstate(badbit);
          __fn_ = fns;
          int* indxs = (int*) realloc(__index_, newcap * sizeof(int));
          if (indxs == 0)
          setstate(badbit);
          __index_ = indxs;
        }
      __fn_[__event_size_] = fn;
      __index_[__event_size_] = index;
      ++__event_size_;
    }
#endif

    /// \details
    /// Destroys an object of class ios_base. Calls each registered
    /// callback pair (fn, index) (27.5.3.6) as
    /// <code>(*fn)(erase_event, *this, index)</code>
    /// at such time that any ios_base member function
    /// called from within fn has well defined results.
    ios_base::~ios_base()
    {
#if defined(OS_INCLUDE_STD_IOS_BASE_CALLBACKS)
      __call_callbacks(erase_event);
#endif
      locale& loc_storage = *(locale*) &m_locale;
      loc_storage.~locale();
#if defined(OS_INCLUDE_STD_IOS_BASE_STORAGE)
      free(__fn_);
      free(__index_);
      free(__iarray_);
      free(__parray_);
#endif
    }

    void
    ios_base::copyfmt(const ios_base& rhs)
    {
#if defined(OS_INCLUDE_STD_IOS_BASE_CALLBACKS)
      // If we can't acquire the needed resources, throw bad_alloc (can't set badbit)
      // Don't alter *this until all needed resources are aquired
      unique_ptr<event_callback, void (*)(void*)> new_callbacks(0, free);
      unique_ptr<int, void (*)(void*)> new_ints(0, free);
      unique_ptr<long, void (*)(void*)> new_longs(0, free);
      unique_ptr<void*, void (*)(void*)> new_pointers(0, free);
      if (__event_cap_ < rhs.__event_size_)
        {
          new_callbacks.reset((event_callback*)malloc(sizeof(event_callback) * rhs.__event_size_));
#if defined(OS_INCLUDE_STD_EXCEPTIONS)
          if (!new_callbacks)
          throw bad_alloc();
#endif  // OS_INCLUDE_STD_EXCEPTIONS
          new_ints.reset((int*)malloc(sizeof(int) * rhs.__event_size_));
#if defined(OS_INCLUDE_STD_EXCEPTIONS)
          if (!new_ints)
          throw bad_alloc();
#endif  // OS_INCLUDE_STD_EXCEPTIONS
        }
#endif

#if defined(OS_INCLUDE_STD_IOS_BASE_STORAGE)
      if (__iarray_cap_ < rhs.__iarray_size_)
        {
          new_longs.reset((long*)malloc(sizeof(long) * rhs.__iarray_size_));
#if defined(OS_INCLUDE_STD_EXCEPTIONS)
          if (!new_longs)
          throw bad_alloc();
#endif  // OS_INCLUDE_STD_EXCEPTIONS
        }
      if (__parray_cap_ < rhs.__parray_size_)
        {
          new_pointers.reset((void**)malloc(sizeof(void*) * rhs.__parray_size_));
#if defined(OS_INCLUDE_STD_EXCEPTIONS)
          if (!new_pointers)
          throw bad_alloc();
#endif  // OS_INCLUDE_STD_EXCEPTIONS
        }
#endif
      // Got everything we need.  Copy everything but __rdstate_, __rdbuf_ and __exceptions_
      m_fmtflags = rhs.m_fmtflags;
      m_precision = rhs.m_precision;
      m_width = rhs.m_width;
      locale& lhs_loc = *(locale*)&m_locale;
      locale& rhs_loc = *(locale*)&rhs.m_locale;
      lhs_loc = rhs_loc;
#if defined(OS_INCLUDE_STD_IOS_BASE_CALLBACKS)
      if (__event_cap_ < rhs.__event_size_)
        {
          free(__fn_);
          __fn_ = new_callbacks.release();
          free(__index_);
          __index_ = new_ints.release();
          __event_cap_ = rhs.__event_size_;
        }
      for (__event_size_ = 0; __event_size_ < rhs.__event_size_; ++__event_size_)
        {
          __fn_[__event_size_] = rhs.__fn_[__event_size_];
          __index_[__event_size_] = rhs.__index_[__event_size_];
        }
#endif
#if defined(OS_INCLUDE_STD_IOS_BASE_STORAGE)
      if (__iarray_cap_ < rhs.__iarray_size_)
        {
          free(__iarray_);
          __iarray_ = new_longs.release();
          __iarray_cap_ = rhs.__iarray_size_;
        }
      for (__iarray_size_ = 0; __iarray_size_ < rhs.__iarray_size_; ++__iarray_size_)
      __iarray_[__iarray_size_] = rhs.__iarray_[__iarray_size_];
      if (__parray_cap_ < rhs.__parray_size_)
        {
          free(__parray_);
          __parray_ = new_pointers.release();
          __parray_cap_ = rhs.__parray_size_;
        }
      for (__parray_size_ = 0; __parray_size_ < rhs.__parray_size_; ++__parray_size_)
      __parray_[__parray_size_] = rhs.__parray_[__parray_size_];
#endif
    }

    void
    ios_base::move(ios_base& rhs)
    {
      // *this is uninitialized
      m_fmtflags = rhs.m_fmtflags;
      m_precision = rhs.m_precision;
      m_width = rhs.m_width;

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      locale& rhs_loc = *(locale*) &rhs.m_locale;
      ::new (&m_locale) locale(rhs_loc);
#endif

#if defined(OS_INCLUDE_STD_IOS_BASE_CALLBACKS)
      __fn_ = rhs.__fn_;
      rhs.__fn_ = 0;
      __index_ = rhs.__index_;
      rhs.__index_ = 0;
      __event_size_ = rhs.__event_size_;
      rhs.__event_size_ = 0;
      __event_cap_ = rhs.__event_cap_;
      rhs.__event_cap_ = 0;
#endif
#if defined(OS_INCLUDE_STD_IOS_BASE_STORAGE)
      __iarray_ = rhs.__iarray_;
      rhs.__iarray_ = 0;
      __iarray_size_ = rhs.__iarray_size_;
      rhs.__iarray_size_ = 0;
      __iarray_cap_ = rhs.__iarray_cap_;
      rhs.__iarray_cap_ = 0;
      __parray_ = rhs.__parray_;
      rhs.__parray_ = 0;
      __parray_size_ = rhs.__parray_size_;
      rhs.__parray_size_ = 0;
      __parray_cap_ = rhs.__parray_cap_;
      rhs.__parray_cap_ = 0;
#endif
    }

    void
    ios_base::swap(ios_base& rhs)
    _NOEXCEPT
    {
      _VSTD::swap(m_fmtflags, rhs.m_fmtflags);
      _VSTD::swap(m_precision, rhs.m_precision);
      _VSTD::swap(m_width, rhs.m_width);
      locale& lhs_loc = *(locale*)&m_locale;
      locale& rhs_loc = *(locale*)&rhs.m_locale;
      _VSTD::swap(lhs_loc, rhs_loc);

#if defined(OS_INCLUDE_STD_IOS_BASE_CALLBACKS)
      _VSTD::swap(__fn_, rhs.__fn_);
      _VSTD::swap(__index_, rhs.__index_);
      _VSTD::swap(__event_size_, rhs.__event_size_);
      _VSTD::swap(__event_cap_, rhs.__event_cap_);
#endif
#if defined(OS_INCLUDE_STD_IOS_BASE_STORAGE)
      _VSTD::swap(__iarray_, rhs.__iarray_);
      _VSTD::swap(__iarray_size_, rhs.__iarray_size_);
      _VSTD::swap(__iarray_cap_, rhs.__iarray_cap_);
      _VSTD::swap(__parray_, rhs.__parray_);
      _VSTD::swap(__parray_size_, rhs.__parray_size_);
      _VSTD::swap(__parray_cap_, rhs.__parray_cap_);
#endif
    }

  /// \details
  /// The synchronization referred to is \e only that between the standard
  /// C facilities (e.g., stdout) and the standard C++ objects (e.g.,
  /// cout).  User-declared streams are unaffected.
    bool
    ios_base::sync_with_stdio(bool sync)
    {
      static bool previous_state = true;
      bool r = previous_state;
      previous_state = sync;
      return r;
    }

  }
}

#endif // defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS)
