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

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INTERNAL_LOCALE_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INTERNAL_LOCALE_H_

#include "portable/core/include/OS_Defines.h"

#if defined(__MICRO_OS_PLUS_PLUS__)

#include "portable/language/cpp/include/internal/__config.h"
//#include "portable/language/cpp/include/locale_tiny.h"
#include "portable/language/cpp/include/iosfwd.h"

//#include "portable/language/cpp/include/memory.h"
//#include "portable/language/cpp/include/cstddef.h"
#include "portable/language/cpp/include/cstdint.h"

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
#include "portable/language/cpp/include/string"
#include "portable/language/cpp/include/memory"
#include "portable/language/cpp/include/utility"
#include "portable/language/cpp/include/mutex"
#include "portable/language/cpp/include/cstdint"
#include "portable/language/cpp/include/cctype"
#endif

#include <locale.h>
#if defined(_WIN32)
# include <support/win32/locale_win32.h>
#elif defined(__GLIBC__) || defined(__APPLE__) || defined(__FreeBSD__) || defined(__sun__)
# include <xlocale.h>
#endif  // _WIN32 || __GLIBC__ || __APPLE__ || __FreeBSD_

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

#if _WIN32
# include <support/win32/locale_win32.h>
#elif (__GLIBC__ || __APPLE__ || __FreeBSD__ || __sun__)
# include <xlocale.h>
#endif  // _WIN32 || __GLIBC__ || __APPLE__ || __FreeBSD_
#endif

#else
#include <__config>
#include <string>
#include <memory>
#include <utility>
#include <mutex>
#include <cstdint>
#include <cctype>
#include <locale.h>
#if _WIN32
# include <support/win32/locale_win32.h>
#elif (__GLIBC__ || __APPLE__ || __FreeBSD__ || __sun__)
# include <xlocale.h>
#endif  // _WIN32 || __GLIBC__ || __APPLE__ || __FreeBSD_
#endif

//_LIBCPP_BEGIN_NAMESPACE_STD
namespace os
{
  namespace std
  {

    class _LIBCPP_VISIBLE locale;

    template<class _Facet>
      _LIBCPP_INLINE_VISIBILITY
      bool
      has_facet(const locale&) _NOEXCEPT;

    template<class _Facet>
      _LIBCPP_INLINE_VISIBILITY
      const _Facet&
      use_facet(const locale&);

    class _LIBCPP_VISIBLE locale
    {
    public:
#if 1 //defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      // types:
      class _LIBCPP_VISIBLE facet;
      class _LIBCPP_VISIBLE id;

      typedef int category;
      // values assigned here are for exposition only
      static const category none = 0;
      static const category collate = LC_COLLATE_MASK;
      static const category ctype = LC_CTYPE_MASK;
      static const category monetary = LC_MONETARY_MASK;
      static const category numeric = LC_NUMERIC_MASK;
      static const category time = LC_TIME_MASK;
      static const category messages = LC_MESSAGES_MASK;
      static const category all = collate | ctype | monetary | numeric | time
          | messages;
#endif

      // construct/copy/destroy:
      locale() _NOEXCEPT;

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      locale(const locale&) _NOEXCEPT;
      explicit locale(const char*);
      explicit locale(const string&);
      locale(const locale&, const char*, category);
      locale(const locale&, const string&, category);
      template <class _Facet>
      _LIBCPP_INLINE_VISIBILITY locale(const locale&, _Facet*);
      locale(const locale&, const locale&, category);

      ~locale();

      const locale& operator=(const locale&) _NOEXCEPT;

      template <class _Facet> locale combine(const locale&) const;

      // locale operations:
      string name() const;
      bool operator==(const locale&) const;
      bool operator!=(const locale& __y) const
        { return !(*this == __y);}
      template <class _CharT, class _Traits, class _Allocator>
      bool operator()(const basic_string<_CharT, _Traits, _Allocator>&,
          const basic_string<_CharT, _Traits, _Allocator>&) const;

      // global locale objects:
      static locale global(const locale&);
      static const locale& classic();
#endif

    private:

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      class __imp;
      __imp* __locale_;

      void __install_ctor(const locale&, facet*, long);
      static locale& __global();
#else

      bool has_facet(id&) const;
      const facet* use_facet(id&) const;

      template <class _Facet> friend bool has_facet(const locale&) _NOEXCEPT;
      template <class _Facet> friend const _Facet& use_facet(const locale&);

      // used to satisfy the static_assert in ios_base::imbue()
      void* dummy;

#endif
    };


#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
  class _LIBCPP_VISIBLE locale::facet
  : public __shared_count
    {
    protected:
      _LIBCPP_INLINE_VISIBILITY
      explicit facet(size_t __refs = 0)
      : __shared_count(static_cast<long>(__refs)-1)
        {}

      virtual ~facet();

//    facet(const facet&) = delete;     // effectively done in __shared_count
//    void operator=(const facet&) = delete;
    private:
      virtual void __on_zero_shared() _NOEXCEPT;
    };

  class _LIBCPP_VISIBLE locale::id
    {
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      once_flag __flag_;
#endif
      int32_t __id_;

      static int32_t __next_id;
    public:
      _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR id() :__id_(0)
        {}
    private:
      void __init();
      void operator=(const id&); // = delete;
      id(const id&);// = delete;
    public:// only needed for tests
      long __get();

      friend class locale;
      friend class locale::__imp;
    };

#else
  class _LIBCPP_VISIBLE locale::facet

    {
    protected:
      _LIBCPP_INLINE_VISIBILITY
      explicit facet()
        {}

    };

  class _LIBCPP_VISIBLE locale::id
    {
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      once_flag __flag_;
#endif
      int32_t __id_;

      static int32_t __next_id;
    public:
      _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR id() :__id_(0)
        {}
    private:
      void __init();
      void operator=(const id&); // = delete;
      id(const id&);// = delete;
    public:// only needed for tests
      long __get();

      friend class locale;
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      friend class locale::__imp;
#endif
    };

#endif

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

  template <class _Facet>
  inline _LIBCPP_INLINE_VISIBILITY
  locale::locale(const locale& __other, _Facet* __f)
    {
      __install_ctor(__other, __f, __f ? __f->id.__get() : 0);
    }

  template <class _Facet>
  locale
  locale::combine(const locale& __other) const
    {
#ifndef _LIBCPP_NO_EXCEPTIONS
      if (!_VSTD::has_facet<_Facet>(__other))
      throw runtime_error("locale::combine: locale missing facet");
#endif  // _LIBCPP_NO_EXCEPTIONS
      return locale(*this, &const_cast<_Facet&>(_VSTD::use_facet<_Facet>(__other)));
    }
#endif

  template <class _Facet>
  inline _LIBCPP_INLINE_VISIBILITY
  bool
  has_facet(const locale& __l) _NOEXCEPT
    {
      return __l.has_facet(_Facet::id);
    }


#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
  template <class _Facet>
  inline _LIBCPP_INLINE_VISIBILITY
  const _Facet&
  use_facet(const locale& __l)
    {
      return static_cast<const _Facet&>(*__l.use_facet(_Facet::id));
    }
#else

#if 0
  // Forward reference, since definition is in locale.h
  template<class _CharT, class _OutputIterator = ostreambuf_iterator<_CharT> >
    class _LIBCPP_VISIBLE num_put;

  //extern template class num_put<char> ;

  extern num_put<char> num_put_char_tiny;

  template <class _Facet>
  inline _LIBCPP_INLINE_VISIBILITY
  const _Facet&
  use_facet(const locale& __l __attribute__((unused)))
    {
      return static_cast<const _Facet&>(num_put_char_tiny);
    }
#endif

#endif

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

 // template <class _CharT> class collate;

  template <class _CharT>
  class _LIBCPP_VISIBLE collate
  : public locale::facet
    {
    public:
      typedef _CharT char_type;
      typedef basic_string<char_type> string_type;

      _LIBCPP_INLINE_VISIBILITY
      explicit collate(size_t __refs = 0)
      : locale::facet(__refs)
        {}

      _LIBCPP_INLINE_VISIBILITY
      int compare(const char_type* __lo1, const char_type* __hi1,
          const char_type* __lo2, const char_type* __hi2) const
        {
          return do_compare(__lo1, __hi1, __lo2, __hi2);
        }

      _LIBCPP_INLINE_VISIBILITY
      string_type transform(const char_type* __lo, const char_type* __hi) const
        {
          return do_transform(__lo, __hi);
        }

      _LIBCPP_INLINE_VISIBILITY
      long hash(const char_type* __lo, const char_type* __hi) const
        {
          return do_hash(__lo, __hi);
        }

      static locale::id id;

    protected:
      ~collate();
      virtual int do_compare(const char_type* __lo1, const char_type* __hi1,
          const char_type* __lo2, const char_type* __hi2) const;
      virtual string_type do_transform(const char_type* __lo, const char_type* __hi) const
        { return string_type(__lo, __hi);}
      virtual long do_hash(const char_type* __lo, const char_type* __hi) const;
    };

  template <class _CharT> locale::id collate<_CharT>::id;

  template <class _CharT>
  collate<_CharT>::~collate()
    {
    }

  template <class _CharT>
  int
  collate<_CharT>::do_compare(const char_type* __lo1, const char_type* __hi1,
      const char_type* __lo2, const char_type* __hi2) const
    {
      for (; __lo2 != __hi2; ++__lo1, ++__lo2)
        {
          if (__lo1 == __hi1 || *__lo1 < *__lo2)
          return -1;
          if (*__lo2 < *__lo1)
          return 1;
        }
      return __lo1 != __hi1;
    }

  template <class _CharT>
  long
  collate<_CharT>::do_hash(const char_type* __lo, const char_type* __hi) const
    {
      size_t __h = 0;
      const size_t __sr = __CHAR_BIT__ * sizeof(size_t) - 8;
      const size_t __mask = size_t(0xF) << (__sr + 4);
      for(const char_type* __p = __lo; __p != __hi; ++__p)
        {
          __h = (__h << 4) + static_cast<size_t>(*__p);
          size_t __g = __h & __mask;
          __h ^= __g | (__g >> __sr);
        }
      return static_cast<long>(__h);
    }

  _LIBCPP_EXTERN_TEMPLATE(class _LIBCPP_VISIBLE collate<char>)
  _LIBCPP_EXTERN_TEMPLATE(class _LIBCPP_VISIBLE collate<wchar_t>)

// template <class CharT> class collate_byname;

  template <class _CharT> class _LIBCPP_VISIBLE collate_byname;

  template <>
  class _LIBCPP_VISIBLE collate_byname<char>
  : public collate<char>
    {
      locale_t __l;
    public:
      typedef char char_type;
      typedef basic_string<char_type> string_type;

      explicit collate_byname(const char* __n, size_t __refs = 0);
      explicit collate_byname(const string& __n, size_t __refs = 0);

    protected:
      ~collate_byname();
      virtual int do_compare(const char_type* __lo1, const char_type* __hi1,
          const char_type* __lo2, const char_type* __hi2) const;
      virtual string_type do_transform(const char_type* __lo, const char_type* __hi) const;
    };

  template <>
  class _LIBCPP_VISIBLE collate_byname<wchar_t>
  : public collate<wchar_t>
    {
      locale_t __l;
    public:
      typedef wchar_t char_type;
      typedef basic_string<char_type> string_type;

      explicit collate_byname(const char* __n, size_t __refs = 0);
      explicit collate_byname(const string& __n, size_t __refs = 0);

    protected:
      ~collate_byname();

      virtual int do_compare(const char_type* __lo1, const char_type* __hi1,
          const char_type* __lo2, const char_type* __hi2) const;
      virtual string_type do_transform(const char_type* __lo, const char_type* __hi) const;
    };

  template <class _CharT, class _Traits, class _Allocator>
  bool
  locale::operator()(const basic_string<_CharT, _Traits, _Allocator>& __x,
      const basic_string<_CharT, _Traits, _Allocator>& __y) const
    {
      return _VSTD::use_facet<_VSTD::collate<_CharT> >(*this).compare(
          __x.data(), __x.data() + __x.size(),
          __y.data(), __y.data() + __y.size()) < 0;
    }

#endif


 // template <class charT> class ctype

  class _LIBCPP_VISIBLE ctype_base
    {
    public:
#if defined(__GLIBC__)
      typedef unsigned short mask;
      static const mask space = _ISspace;
      static const mask print = _ISprint;
      static const mask cntrl = _IScntrl;
      static const mask upper = _ISupper;
      static const mask lower = _ISlower;
      static const mask alpha = _ISalpha;
      static const mask digit = _ISdigit;
      static const mask punct = _ISpunct;
      static const mask xdigit = _ISxdigit;
      static const mask blank = _ISblank;
#elif defined(_WIN32)
      typedef unsigned short mask;
      static const mask space = _SPACE;
      static const mask print = _BLANK|_PUNCT|_ALPHA|_DIGIT;
      static const mask cntrl = _CONTROL;
      static const mask upper = _UPPER;
      static const mask lower = _LOWER;
      static const mask alpha = _ALPHA;
      static const mask digit = _DIGIT;
      static const mask punct = _PUNCT;
      static const mask xdigit = _HEX;
      static const mask blank = _BLANK;
#elif 0 //(__APPLE__ || __FreeBSD__)
#if defined(__APPLE__)
      typedef __uint32_t mask;
#elif defined(__FreeBSD__)
      typedef unsigned long mask;
#endif
      static const mask space = _CTYPE_S;
      static const mask print = _CTYPE_R;
      static const mask cntrl = _CTYPE_C;
      static const mask upper = _CTYPE_U;
      static const mask lower = _CTYPE_L;
      static const mask alpha = _CTYPE_A;
      static const mask digit = _CTYPE_D;
      static const mask punct = _CTYPE_P;
      static const mask xdigit = _CTYPE_X;
      static const mask blank = _CTYPE_B;
#elif defined(__sun__)
      typedef unsigned int mask;
      static const mask space = _ISSPACE;
      static const mask print = _ISPRINT;
      static const mask cntrl = _ISCNTRL;
      static const mask upper = _ISUPPER;
      static const mask lower = _ISLOWER;
      static const mask alpha = _ISALPHA;
      static const mask digit = _ISDIGIT;
      static const mask punct = _ISPUNCT;
      static const mask xdigit = _ISXDIGIT;
      static const mask blank = _ISBLANK;
#else  // __GLIBC__ || _WIN32 || __APPLE__ || __FreeBSD__ || __sun__
      typedef unsigned long mask;
      static const mask space = 1<<0;
      static const mask print = 1<<1;
      static const mask cntrl = 1<<2;
      static const mask upper = 1<<3;
      static const mask lower = 1<<4;
      static const mask alpha = 1<<5;
      static const mask digit = 1<<6;
      static const mask punct = 1<<7;
      static const mask xdigit = 1<<8;
      static const mask blank = 1<<9;
#endif  // __GLIBC__ || _WIN32 || __APPLE__ || __FreeBSD__
      static const mask alnum = alpha | digit;
      static const mask graph = alnum | punct;

      _LIBCPP_ALWAYS_INLINE ctype_base()
        {}
    };

  template <class _CharT> class _LIBCPP_VISIBLE ctype;

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
  template <>
  class _LIBCPP_VISIBLE ctype<wchar_t>
  : public locale::facet,
public ctype_base
    {
    public:
      typedef wchar_t char_type;

      _LIBCPP_ALWAYS_INLINE
      explicit ctype(size_t __refs = 0)
      : locale::facet(__refs)
        {}

      _LIBCPP_ALWAYS_INLINE
      bool is(mask __m, char_type __c) const
        {
          return do_is(__m, __c);
        }

      _LIBCPP_ALWAYS_INLINE
      const char_type* is(const char_type* __low, const char_type* __high, mask* __vec) const
        {
          return do_is(__low, __high, __vec);
        }

      _LIBCPP_ALWAYS_INLINE
      const char_type* scan_is(mask __m, const char_type* __low, const char_type* __high) const
        {
          return do_scan_is(__m, __low, __high);
        }

      _LIBCPP_ALWAYS_INLINE
      const char_type* scan_not(mask __m, const char_type* __low, const char_type* __high) const
        {
          return do_scan_not(__m, __low, __high);
        }

      _LIBCPP_ALWAYS_INLINE
      char_type toupper(char_type __c) const
        {
          return do_toupper(__c);
        }

      _LIBCPP_ALWAYS_INLINE
      const char_type* toupper(char_type* __low, const char_type* __high) const
        {
          return do_toupper(__low, __high);
        }

      _LIBCPP_ALWAYS_INLINE
      char_type tolower(char_type __c) const
        {
          return do_tolower(__c);
        }

      _LIBCPP_ALWAYS_INLINE
      const char_type* tolower(char_type* __low, const char_type* __high) const
        {
          return do_tolower(__low, __high);
        }

      _LIBCPP_ALWAYS_INLINE
      char_type widen(char __c) const
        {
          return do_widen(__c);
        }

      _LIBCPP_ALWAYS_INLINE
      const char* widen(const char* __low, const char* __high, char_type* __to) const
        {
          return do_widen(__low, __high, __to);
        }

      _LIBCPP_ALWAYS_INLINE
      char narrow(char_type __c, char __dfault) const
        {
          return do_narrow(__c, __dfault);
        }

      _LIBCPP_ALWAYS_INLINE
      const char_type* narrow(const char_type* __low, const char_type* __high, char __dfault, char* __to) const
        {
          return do_narrow(__low, __high, __dfault, __to);
        }

      static locale::id id;

    protected:
      ~ctype();
      virtual bool do_is(mask __m, char_type __c) const;
      virtual const char_type* do_is(const char_type* __low, const char_type* __high, mask* __vec) const;
      virtual const char_type* do_scan_is(mask __m, const char_type* __low, const char_type* __high) const;
      virtual const char_type* do_scan_not(mask __m, const char_type* __low, const char_type* __high) const;
      virtual char_type do_toupper(char_type) const;
      virtual const char_type* do_toupper(char_type* __low, const char_type* __high) const;
      virtual char_type do_tolower(char_type) const;
      virtual const char_type* do_tolower(char_type* __low, const char_type* __high) const;
      virtual char_type do_widen(char) const;
      virtual const char* do_widen(const char* __low, const char* __high, char_type* __dest) const;
      virtual char do_narrow(char_type, char __dfault) const;
      virtual const char_type* do_narrow(const char_type* __low, const char_type* __high, char __dfault, char* __dest) const;
    };

  template <>
  class _LIBCPP_VISIBLE ctype<char>
  : public locale::facet, public ctype_base
    {
      const mask* __tab_;
      bool __del_;
    public:
      typedef char char_type;

      explicit ctype(const mask* __tab = 0, bool __del = false, size_t __refs = 0);

      _LIBCPP_ALWAYS_INLINE
      bool is(mask __m, char_type __c) const
        {
          return isascii(__c) ? __tab_[static_cast<int>(__c)] & __m : false;
        }

      _LIBCPP_ALWAYS_INLINE
      const char_type* is(const char_type* __low, const char_type* __high, mask* __vec) const
        {
          for (; __low != __high; ++__low, ++__vec)
          *__vec = isascii(*__low) ? __tab_[static_cast<int>(*__low)] : 0;
          return __low;
        }

      _LIBCPP_ALWAYS_INLINE
      const char_type* scan_is (mask __m, const char_type* __low, const char_type* __high) const
        {
          for (; __low != __high; ++__low)
          if (isascii(*__low) && (__tab_[static_cast<int>(*__low)] & __m))
          break;
          return __low;
        }

      _LIBCPP_ALWAYS_INLINE
      const char_type* scan_not(mask __m, const char_type* __low, const char_type* __high) const
        {
          for (; __low != __high; ++__low)
          if (!(isascii(*__low) && (__tab_[static_cast<int>(*__low)] & __m)))
          break;
          return __low;
        }

      _LIBCPP_ALWAYS_INLINE
      char_type toupper(char_type __c) const
        {
          return do_toupper(__c);
        }

      _LIBCPP_ALWAYS_INLINE
      const char_type* toupper(char_type* __low, const char_type* __high) const
        {
          return do_toupper(__low, __high);
        }

      _LIBCPP_ALWAYS_INLINE
      char_type tolower(char_type __c) const
        {
          return do_tolower(__c);
        }

      _LIBCPP_ALWAYS_INLINE
      const char_type* tolower(char_type* __low, const char_type* __high) const
        {
          return do_tolower(__low, __high);
        }

      _LIBCPP_ALWAYS_INLINE
      char_type widen(char __c) const
        {
          return do_widen(__c);
        }

      _LIBCPP_ALWAYS_INLINE
      const char* widen(const char* __low, const char* __high, char_type* __to) const
        {
          return do_widen(__low, __high, __to);
        }

      _LIBCPP_ALWAYS_INLINE
      char narrow(char_type __c, char __dfault) const
        {
          return do_narrow(__c, __dfault);
        }

      _LIBCPP_ALWAYS_INLINE
      const char* narrow(const char_type* __low, const char_type* __high, char __dfault, char* __to) const
        {
          return do_narrow(__low, __high, __dfault, __to);
        }

      static locale::id id;

#ifdef _CACHED_RUNES
      static const size_t table_size = _CACHED_RUNES;
#else
      static const size_t table_size = 256;  // FIXME: Don't hardcode this.
#endif
      _LIBCPP_ALWAYS_INLINE const mask* table() const _NOEXCEPT
        { return __tab_;}
      static const mask* classic_table() _NOEXCEPT;
#if defined(__GLIBC__)
      static const int* __classic_upper_table() _NOEXCEPT;
      static const int* __classic_lower_table() _NOEXCEPT;
#endif

    protected:
      ~ctype();
      virtual char_type do_toupper(char_type __c) const;
      virtual const char_type* do_toupper(char_type* __low, const char_type* __high) const;
      virtual char_type do_tolower(char_type __c) const;
      virtual const char_type* do_tolower(char_type* __low, const char_type* __high) const;
      virtual char_type do_widen(char __c) const;
      virtual const char* do_widen(const char* __low, const char* __high, char_type* __to) const;
      virtual char do_narrow(char_type __c, char __dfault) const;
      virtual const char* do_narrow(const char_type* __low, const char_type* __high, char __dfault, char* __to) const;
    };

// template <class CharT> class ctype_byname;

  template <class _CharT> class _LIBCPP_VISIBLE ctype_byname;

  template <>
  class _LIBCPP_VISIBLE ctype_byname<char>
  : public ctype<char>
    {
      locale_t __l;

    public:
      explicit ctype_byname(const char*, size_t = 0);
      explicit ctype_byname(const string&, size_t = 0);

    protected:
      ~ctype_byname();
      virtual char_type do_toupper(char_type) const;
      virtual const char_type* do_toupper(char_type* __low, const char_type* __high) const;
      virtual char_type do_tolower(char_type) const;
      virtual const char_type* do_tolower(char_type* __low, const char_type* __high) const;
    };

  template <>
  class _LIBCPP_VISIBLE ctype_byname<wchar_t>
  : public ctype<wchar_t>
    {
      locale_t __l;

    public:
      explicit ctype_byname(const char*, size_t = 0);
      explicit ctype_byname(const string&, size_t = 0);

    protected:
      ~ctype_byname();
      virtual bool do_is(mask __m, char_type __c) const;
      virtual const char_type* do_is(const char_type* __low, const char_type* __high, mask* __vec) const;
      virtual const char_type* do_scan_is(mask __m, const char_type* __low, const char_type* __high) const;
      virtual const char_type* do_scan_not(mask __m, const char_type* __low, const char_type* __high) const;
      virtual char_type do_toupper(char_type) const;
      virtual const char_type* do_toupper(char_type* __low, const char_type* __high) const;
      virtual char_type do_tolower(char_type) const;
      virtual const char_type* do_tolower(char_type* __low, const char_type* __high) const;
      virtual char_type do_widen(char) const;
      virtual const char* do_widen(const char* __low, const char* __high, char_type* __dest) const;
      virtual char do_narrow(char_type, char __dfault) const;
      virtual const char_type* do_narrow(const char_type* __low, const char_type* __high, char __dfault, char* __dest) const;
    };

  template <class _CharT>
  inline _LIBCPP_INLINE_VISIBILITY
  bool
  isspace(_CharT __c, const locale& __loc)
    {
      return use_facet<ctype<_CharT> >(__loc).is(ctype_base::space, __c);
    }

  template <class _CharT>
  inline _LIBCPP_INLINE_VISIBILITY
  bool
  isprint(_CharT __c, const locale& __loc)
    {
      return use_facet<ctype<_CharT> >(__loc).is(ctype_base::print, __c);
    }

  template <class _CharT>
  inline _LIBCPP_INLINE_VISIBILITY
  bool
  iscntrl(_CharT __c, const locale& __loc)
    {
      return use_facet<ctype<_CharT> >(__loc).is(ctype_base::cntrl, __c);
    }

  template <class _CharT>
  inline _LIBCPP_INLINE_VISIBILITY
  bool
  isupper(_CharT __c, const locale& __loc)
    {
      return use_facet<ctype<_CharT> >(__loc).is(ctype_base::upper, __c);
    }

  template <class _CharT>
  inline _LIBCPP_INLINE_VISIBILITY
  bool
  islower(_CharT __c, const locale& __loc)
    {
      return use_facet<ctype<_CharT> >(__loc).is(ctype_base::lower, __c);
    }

  template <class _CharT>
  inline _LIBCPP_INLINE_VISIBILITY
  bool
  isalpha(_CharT __c, const locale& __loc)
    {
      return use_facet<ctype<_CharT> >(__loc).is(ctype_base::alpha, __c);
    }

  template <class _CharT>
  inline _LIBCPP_INLINE_VISIBILITY
  bool
  isdigit(_CharT __c, const locale& __loc)
    {
      return use_facet<ctype<_CharT> >(__loc).is(ctype_base::digit, __c);
    }

  template <class _CharT>
  inline _LIBCPP_INLINE_VISIBILITY
  bool
  ispunct(_CharT __c, const locale& __loc)
    {
      return use_facet<ctype<_CharT> >(__loc).is(ctype_base::punct, __c);
    }

  template <class _CharT>
  inline _LIBCPP_INLINE_VISIBILITY
  bool
  isxdigit(_CharT __c, const locale& __loc)
    {
      return use_facet<ctype<_CharT> >(__loc).is(ctype_base::xdigit, __c);
    }

  template <class _CharT>
  inline _LIBCPP_INLINE_VISIBILITY
  bool
  isalnum(_CharT __c, const locale& __loc)
    {
      return use_facet<ctype<_CharT> >(__loc).is(ctype_base::alnum, __c);
    }

  template <class _CharT>
  inline _LIBCPP_INLINE_VISIBILITY
  bool
  isgraph(_CharT __c, const locale& __loc)
    {
      return use_facet<ctype<_CharT> >(__loc).is(ctype_base::graph, __c);
    }

  template <class _CharT>
  inline _LIBCPP_INLINE_VISIBILITY
  _CharT
  toupper(_CharT __c, const locale& __loc)
    {
      return use_facet<ctype<_CharT> >(__loc).toupper(__c);
    }

  template <class _CharT>
  inline _LIBCPP_INLINE_VISIBILITY
  _CharT
  tolower(_CharT __c, const locale& __loc)
    {
      return use_facet<ctype<_CharT> >(__loc).tolower(__c);
    }

// codecvt_base

  class _LIBCPP_VISIBLE codecvt_base
    {
    public:
      _LIBCPP_ALWAYS_INLINE codecvt_base()
        {}
      enum result
        { ok, partial, error, noconv};
    };

// template <class internT, class externT, class stateT> class codecvt;

  template <class _InternT, class _ExternT, class _StateT> class _LIBCPP_VISIBLE codecvt;

// template <> class codecvt<char, char, mbstate_t>

  template <>
  class _LIBCPP_VISIBLE codecvt<char, char, mbstate_t>
  : public locale::facet,
public codecvt_base
    {
    public:
      typedef char intern_type;
      typedef char extern_type;
      typedef mbstate_t state_type;

      _LIBCPP_ALWAYS_INLINE
      explicit codecvt(size_t __refs = 0)
      : locale::facet(__refs)
        {}

      _LIBCPP_ALWAYS_INLINE
      result out(state_type& __st,
          const intern_type* __frm, const intern_type* __frm_end, const intern_type*& __frm_nxt,
          extern_type* __to, extern_type* __to_end, extern_type*& __to_nxt) const
        {
          return do_out(__st, __frm, __frm_end, __frm_nxt, __to, __to_end, __to_nxt);
        }

      _LIBCPP_ALWAYS_INLINE
      result unshift(state_type& __st,
          extern_type* __to, extern_type* __to_end, extern_type*& __to_nxt) const
        {
          return do_unshift(__st, __to, __to_end, __to_nxt);
        }

      _LIBCPP_ALWAYS_INLINE
      result in(state_type& __st,
          const extern_type* __frm, const extern_type* __frm_end, const extern_type*& __frm_nxt,
          intern_type* __to, intern_type* __to_end, intern_type*& __to_nxt) const
        {
          return do_in(__st, __frm, __frm_end, __frm_nxt, __to, __to_end, __to_nxt);
        }

      _LIBCPP_ALWAYS_INLINE
      int encoding() const _NOEXCEPT
        {
          return do_encoding();
        }

      _LIBCPP_ALWAYS_INLINE
      bool always_noconv() const _NOEXCEPT
        {
          return do_always_noconv();
        }

      _LIBCPP_ALWAYS_INLINE
      int length(state_type& __st, const extern_type* __frm, const extern_type* __end, size_t __mx) const
        {
          return do_length(__st, __frm, __end, __mx);
        }

      _LIBCPP_ALWAYS_INLINE
      int max_length() const _NOEXCEPT
        {
          return do_max_length();
        }

      static locale::id id;

    protected:
      _LIBCPP_ALWAYS_INLINE
      explicit codecvt(const char*, size_t __refs = 0)
      : locale::facet(__refs)
        {}

      ~codecvt();

      virtual result do_out(state_type& __st,
          const intern_type* __frm, const intern_type* __frm_end, const intern_type*& __frm_nxt,
          extern_type* __to, extern_type* __to_end, extern_type*& __to_nxt) const;
      virtual result do_in(state_type& __st,
          const extern_type* __frm, const extern_type* __frm_end, const extern_type*& __frm_nxt,
          intern_type* __to, intern_type* __to_end, intern_type*& __to_nxt) const;
      virtual result do_unshift(state_type& __st,
          extern_type* __to, extern_type* __to_end, extern_type*& __to_nxt) const;
      virtual int do_encoding() const _NOEXCEPT;
      virtual bool do_always_noconv() const _NOEXCEPT;
      virtual int do_length(state_type& __st, const extern_type* __frm, const extern_type* __end, size_t __mx) const;
      virtual int do_max_length() const _NOEXCEPT;
    };

// template <> class codecvt<wchar_t, char, mbstate_t>

  template <>
  class _LIBCPP_VISIBLE codecvt<wchar_t, char, mbstate_t>
  : public locale::facet,
public codecvt_base
    {
      locale_t __l;
    public:
      typedef wchar_t intern_type;
      typedef char extern_type;
      typedef mbstate_t state_type;

      explicit codecvt(size_t __refs = 0);

      _LIBCPP_ALWAYS_INLINE
      result out(state_type& __st,
          const intern_type* __frm, const intern_type* __frm_end, const intern_type*& __frm_nxt,
          extern_type* __to, extern_type* __to_end, extern_type*& __to_nxt) const
        {
          return do_out(__st, __frm, __frm_end, __frm_nxt, __to, __to_end, __to_nxt);
        }

      _LIBCPP_ALWAYS_INLINE
      result unshift(state_type& __st,
          extern_type* __to, extern_type* __to_end, extern_type*& __to_nxt) const
        {
          return do_unshift(__st, __to, __to_end, __to_nxt);
        }

      _LIBCPP_ALWAYS_INLINE
      result in(state_type& __st,
          const extern_type* __frm, const extern_type* __frm_end, const extern_type*& __frm_nxt,
          intern_type* __to, intern_type* __to_end, intern_type*& __to_nxt) const
        {
          return do_in(__st, __frm, __frm_end, __frm_nxt, __to, __to_end, __to_nxt);
        }

      _LIBCPP_ALWAYS_INLINE
      int encoding() const _NOEXCEPT
        {
          return do_encoding();
        }

      _LIBCPP_ALWAYS_INLINE
      bool always_noconv() const _NOEXCEPT
        {
          return do_always_noconv();
        }

      _LIBCPP_ALWAYS_INLINE
      int length(state_type& __st, const extern_type* __frm, const extern_type* __end, size_t __mx) const
        {
          return do_length(__st, __frm, __end, __mx);
        }

      _LIBCPP_ALWAYS_INLINE
      int max_length() const _NOEXCEPT
        {
          return do_max_length();
        }

      static locale::id id;

    protected:
      explicit codecvt(const char*, size_t __refs = 0);

      ~codecvt();

      virtual result do_out(state_type& __st,
          const intern_type* __frm, const intern_type* __frm_end, const intern_type*& __frm_nxt,
          extern_type* __to, extern_type* __to_end, extern_type*& __to_nxt) const;
      virtual result do_in(state_type& __st,
          const extern_type* __frm, const extern_type* __frm_end, const extern_type*& __frm_nxt,
          intern_type* __to, intern_type* __to_end, intern_type*& __to_nxt) const;
      virtual result do_unshift(state_type& __st,
          extern_type* __to, extern_type* __to_end, extern_type*& __to_nxt) const;
      virtual int do_encoding() const _NOEXCEPT;
      virtual bool do_always_noconv() const _NOEXCEPT;
      virtual int do_length(state_type&, const extern_type* __frm, const extern_type* __end, size_t __mx) const;
      virtual int do_max_length() const _NOEXCEPT;
    };

// template <> class codecvt<char16_t, char, mbstate_t>

  template <>
  class _LIBCPP_VISIBLE codecvt<char16_t, char, mbstate_t>
  : public locale::facet,
public codecvt_base
    {
    public:
      typedef char16_t intern_type;
      typedef char extern_type;
      typedef mbstate_t state_type;

      _LIBCPP_ALWAYS_INLINE
      explicit codecvt(size_t __refs = 0)
      : locale::facet(__refs)
        {}

      _LIBCPP_ALWAYS_INLINE
      result out(state_type& __st,
          const intern_type* __frm, const intern_type* __frm_end, const intern_type*& __frm_nxt,
          extern_type* __to, extern_type* __to_end, extern_type*& __to_nxt) const
        {
          return do_out(__st, __frm, __frm_end, __frm_nxt, __to, __to_end, __to_nxt);
        }

      _LIBCPP_ALWAYS_INLINE
      result unshift(state_type& __st,
          extern_type* __to, extern_type* __to_end, extern_type*& __to_nxt) const
        {
          return do_unshift(__st, __to, __to_end, __to_nxt);
        }

      _LIBCPP_ALWAYS_INLINE
      result in(state_type& __st,
          const extern_type* __frm, const extern_type* __frm_end, const extern_type*& __frm_nxt,
          intern_type* __to, intern_type* __to_end, intern_type*& __to_nxt) const
        {
          return do_in(__st, __frm, __frm_end, __frm_nxt, __to, __to_end, __to_nxt);
        }

      _LIBCPP_ALWAYS_INLINE
      int encoding() const _NOEXCEPT
        {
          return do_encoding();
        }

      _LIBCPP_ALWAYS_INLINE
      bool always_noconv() const _NOEXCEPT
        {
          return do_always_noconv();
        }

      _LIBCPP_ALWAYS_INLINE
      int length(state_type& __st, const extern_type* __frm, const extern_type* __end, size_t __mx) const
        {
          return do_length(__st, __frm, __end, __mx);
        }

      _LIBCPP_ALWAYS_INLINE
      int max_length() const _NOEXCEPT
        {
          return do_max_length();
        }

      static locale::id id;

    protected:
      _LIBCPP_ALWAYS_INLINE
      explicit codecvt(const char*, size_t __refs = 0)
      : locale::facet(__refs)
        {}

      ~codecvt();

      virtual result do_out(state_type& __st,
          const intern_type* __frm, const intern_type* __frm_end, const intern_type*& __frm_nxt,
          extern_type* __to, extern_type* __to_end, extern_type*& __to_nxt) const;
      virtual result do_in(state_type& __st,
          const extern_type* __frm, const extern_type* __frm_end, const extern_type*& __frm_nxt,
          intern_type* __to, intern_type* __to_end, intern_type*& __to_nxt) const;
      virtual result do_unshift(state_type& __st,
          extern_type* __to, extern_type* __to_end, extern_type*& __to_nxt) const;
      virtual int do_encoding() const _NOEXCEPT;
      virtual bool do_always_noconv() const _NOEXCEPT;
      virtual int do_length(state_type&, const extern_type* __frm, const extern_type* __end, size_t __mx) const;
      virtual int do_max_length() const _NOEXCEPT;
    };

// template <> class codecvt<char32_t, char, mbstate_t>

  template <>
  class _LIBCPP_VISIBLE codecvt<char32_t, char, mbstate_t>
  : public locale::facet,
public codecvt_base
    {
    public:
      typedef char32_t intern_type;
      typedef char extern_type;
      typedef mbstate_t state_type;

      _LIBCPP_ALWAYS_INLINE
      explicit codecvt(size_t __refs = 0)
      : locale::facet(__refs)
        {}

      _LIBCPP_ALWAYS_INLINE
      result out(state_type& __st,
          const intern_type* __frm, const intern_type* __frm_end, const intern_type*& __frm_nxt,
          extern_type* __to, extern_type* __to_end, extern_type*& __to_nxt) const
        {
          return do_out(__st, __frm, __frm_end, __frm_nxt, __to, __to_end, __to_nxt);
        }

      _LIBCPP_ALWAYS_INLINE
      result unshift(state_type& __st,
          extern_type* __to, extern_type* __to_end, extern_type*& __to_nxt) const
        {
          return do_unshift(__st, __to, __to_end, __to_nxt);
        }

      _LIBCPP_ALWAYS_INLINE
      result in(state_type& __st,
          const extern_type* __frm, const extern_type* __frm_end, const extern_type*& __frm_nxt,
          intern_type* __to, intern_type* __to_end, intern_type*& __to_nxt) const
        {
          return do_in(__st, __frm, __frm_end, __frm_nxt, __to, __to_end, __to_nxt);
        }

      _LIBCPP_ALWAYS_INLINE
      int encoding() const _NOEXCEPT
        {
          return do_encoding();
        }

      _LIBCPP_ALWAYS_INLINE
      bool always_noconv() const _NOEXCEPT
        {
          return do_always_noconv();
        }

      _LIBCPP_ALWAYS_INLINE
      int length(state_type& __st, const extern_type* __frm, const extern_type* __end, size_t __mx) const
        {
          return do_length(__st, __frm, __end, __mx);
        }

      _LIBCPP_ALWAYS_INLINE
      int max_length() const _NOEXCEPT
        {
          return do_max_length();
        }

      static locale::id id;

    protected:
      _LIBCPP_ALWAYS_INLINE
      explicit codecvt(const char*, size_t __refs = 0)
      : locale::facet(__refs)
        {}

      ~codecvt();

      virtual result do_out(state_type& __st,
          const intern_type* __frm, const intern_type* __frm_end, const intern_type*& __frm_nxt,
          extern_type* __to, extern_type* __to_end, extern_type*& __to_nxt) const;
      virtual result do_in(state_type& __st,
          const extern_type* __frm, const extern_type* __frm_end, const extern_type*& __frm_nxt,
          intern_type* __to, intern_type* __to_end, intern_type*& __to_nxt) const;
      virtual result do_unshift(state_type& __st,
          extern_type* __to, extern_type* __to_end, extern_type*& __to_nxt) const;
      virtual int do_encoding() const _NOEXCEPT;
      virtual bool do_always_noconv() const _NOEXCEPT;
      virtual int do_length(state_type&, const extern_type* __frm, const extern_type* __end, size_t __mx) const;
      virtual int do_max_length() const _NOEXCEPT;
    };

// template <class _InternT, class _ExternT, class _StateT> class codecvt_byname

  template <class _InternT, class _ExternT, class _StateT>
  class _LIBCPP_VISIBLE codecvt_byname
  : public codecvt<_InternT, _ExternT, _StateT>
    {
    public:
      _LIBCPP_ALWAYS_INLINE
      explicit codecvt_byname(const char* __nm, size_t __refs = 0)
      : codecvt<_InternT, _ExternT, _StateT>(__nm, __refs)
        {}
      _LIBCPP_ALWAYS_INLINE
      explicit codecvt_byname(const string& __nm, size_t __refs = 0)
      : codecvt<_InternT, _ExternT, _StateT>(__nm.c_str(), __refs)
        {}
    protected:
      ~codecvt_byname();
    };

  template <class _InternT, class _ExternT, class _StateT>
  codecvt_byname<_InternT, _ExternT, _StateT>::~codecvt_byname()
    {
    }

  _LIBCPP_EXTERN_TEMPLATE(class codecvt_byname<char, char, mbstate_t>)
  _LIBCPP_EXTERN_TEMPLATE(class codecvt_byname<wchar_t, char, mbstate_t>)
  _LIBCPP_EXTERN_TEMPLATE(class codecvt_byname<char16_t, char, mbstate_t>)
  _LIBCPP_EXTERN_TEMPLATE(class codecvt_byname<char32_t, char, mbstate_t>)

  _LIBCPP_VISIBLE void __throw_runtime_error(const char*);

  template <size_t _Np>
  struct __narrow_to_utf8
    {
      template <class _OutputIterator, class _CharT>
      _OutputIterator
      operator()(_OutputIterator __s, const _CharT* __wb, const _CharT* __we) const;
    };

  template <>
  struct __narrow_to_utf8<8>
    {
      template <class _OutputIterator, class _CharT>
      _LIBCPP_ALWAYS_INLINE
      _OutputIterator
      operator()(_OutputIterator __s, const _CharT* __wb, const _CharT* __we) const
        {
          for (; __wb < __we; ++__wb, ++__s)
          *__s = *__wb;
          return __s;
        }
    };

  template <>
  struct __narrow_to_utf8<16>
  : public codecvt<char16_t, char, mbstate_t>
    {
      _LIBCPP_ALWAYS_INLINE
      __narrow_to_utf8() : codecvt<char16_t, char, mbstate_t>(1)
        {}

      ~__narrow_to_utf8();

      template <class _OutputIterator, class _CharT>
      _LIBCPP_ALWAYS_INLINE
      _OutputIterator
      operator()(_OutputIterator __s, const _CharT* __wb, const _CharT* __we) const
        {
          result __r = ok;
          mbstate_t __mb;
          while (__wb < __we && __r != error)
            {
              const int __sz = 32;
              char __buf[__sz];
              char* __bn;
              const char16_t* __wn = (const char16_t*)__wb;
              __r = do_out(__mb, (const char16_t*)__wb, (const char16_t*)__we, __wn,
                  __buf, __buf+__sz, __bn);
              if (__r == codecvt_base::error || __wn == (const char16_t*)__wb)
              __throw_runtime_error("locale not supported");
              for (const char* __p = __buf; __p < __bn; ++__p, ++__s)
              *__s = *__p;
              __wb = (const _CharT*)__wn;
            }
          return __s;
        }
    };

  template <>
  struct __narrow_to_utf8<32>
  : public codecvt<char32_t, char, mbstate_t>
    {
      _LIBCPP_ALWAYS_INLINE
      __narrow_to_utf8() : codecvt<char32_t, char, mbstate_t>(1)
        {}

      ~__narrow_to_utf8();

      template <class _OutputIterator, class _CharT>
      _LIBCPP_ALWAYS_INLINE
      _OutputIterator
      operator()(_OutputIterator __s, const _CharT* __wb, const _CharT* __we) const
        {
          result __r = ok;
          mbstate_t __mb;
          while (__wb < __we && __r != error)
            {
              const int __sz = 32;
              char __buf[__sz];
              char* __bn;
              const char32_t* __wn = (const char32_t*)__wb;
              __r = do_out(__mb, (const char32_t*)__wb, (const char32_t*)__we, __wn,
                  __buf, __buf+__sz, __bn);
              if (__r == codecvt_base::error || __wn == (const char32_t*)__wb)
              __throw_runtime_error("locale not supported");
              for (const char* __p = __buf; __p < __bn; ++__p, ++__s)
              *__s = *__p;
              __wb = (const _CharT*)__wn;
            }
          return __s;
        }
    };

  template <size_t _Np>
  struct __widen_from_utf8
    {
      template <class _OutputIterator>
      _OutputIterator
      operator()(_OutputIterator __s, const char* __nb, const char* __ne) const;
    };

  template <>
  struct __widen_from_utf8<8>
    {
      template <class _OutputIterator>
      _LIBCPP_ALWAYS_INLINE
      _OutputIterator
      operator()(_OutputIterator __s, const char* __nb, const char* __ne) const
        {
          for (; __nb < __ne; ++__nb, ++__s)
          *__s = *__nb;
          return __s;
        }
    };

  template <>
  struct __widen_from_utf8<16>
  : public codecvt<char16_t, char, mbstate_t>
    {
      _LIBCPP_ALWAYS_INLINE
      __widen_from_utf8() : codecvt<char16_t, char, mbstate_t>(1)
        {}

      ~__widen_from_utf8();

      template <class _OutputIterator>
      _LIBCPP_ALWAYS_INLINE
      _OutputIterator
      operator()(_OutputIterator __s, const char* __nb, const char* __ne) const
        {
          result __r = ok;
          mbstate_t __mb;
          while (__nb < __ne && __r != error)
            {
              const int __sz = 32;
              char16_t __buf[__sz];
              char16_t* __bn;
              const char* __nn = __nb;
              __r = do_in(__mb, __nb, __ne - __nb > __sz ? __nb+__sz : __ne, __nn,
                  __buf, __buf+__sz, __bn);
              if (__r == codecvt_base::error || __nn == __nb)
              __throw_runtime_error("locale not supported");
              for (const char16_t* __p = __buf; __p < __bn; ++__p, ++__s)
              *__s = (wchar_t)*__p;
              __nb = __nn;
            }
          return __s;
        }
    };

  template <>
  struct __widen_from_utf8<32>
  : public codecvt<char32_t, char, mbstate_t>
    {
      _LIBCPP_ALWAYS_INLINE
      __widen_from_utf8() : codecvt<char32_t, char, mbstate_t>(1)
        {}

      ~__widen_from_utf8();

      template <class _OutputIterator>
      _LIBCPP_ALWAYS_INLINE
      _OutputIterator
      operator()(_OutputIterator __s, const char* __nb, const char* __ne) const
        {
          result __r = ok;
          mbstate_t __mb;
          while (__nb < __ne && __r != error)
            {
              const int __sz = 32;
              char32_t __buf[__sz];
              char32_t* __bn;
              const char* __nn = __nb;
              __r = do_in(__mb, __nb, __ne - __nb > __sz ? __nb+__sz : __ne, __nn,
                  __buf, __buf+__sz, __bn);
              if (__r == codecvt_base::error || __nn == __nb)
              __throw_runtime_error("locale not supported");
              for (const char32_t* __p = __buf; __p < __bn; ++__p, ++__s)
              *__s = (wchar_t)*__p;
              __nb = __nn;
            }
          return __s;
        }
    };

// template <class charT> class numpunct

  template <class _CharT> class _LIBCPP_VISIBLE numpunct;

  template <>
  class _LIBCPP_VISIBLE numpunct<char>
  : public locale::facet
    {
    public:
      typedef char char_type;
      typedef basic_string<char_type> string_type;

      explicit numpunct(size_t __refs = 0);

      _LIBCPP_ALWAYS_INLINE char_type decimal_point() const
        { return do_decimal_point();}
      _LIBCPP_ALWAYS_INLINE char_type thousands_sep() const
        { return do_thousands_sep();}
      _LIBCPP_ALWAYS_INLINE string grouping() const
        { return do_grouping();}
      _LIBCPP_ALWAYS_INLINE string_type truename() const
        { return do_truename();}
      _LIBCPP_ALWAYS_INLINE string_type falsename() const
        { return do_falsename();}

      static locale::id id;

    protected:
      ~numpunct();
      virtual char_type do_decimal_point() const;
      virtual char_type do_thousands_sep() const;
      virtual string do_grouping() const;
      virtual string_type do_truename() const;
      virtual string_type do_falsename() const;

      char_type __decimal_point_;
      char_type __thousands_sep_;
      string __grouping_;
    };

  template <>
  class _LIBCPP_VISIBLE numpunct<wchar_t>
  : public locale::facet
    {
    public:
      typedef wchar_t char_type;
      typedef basic_string<char_type> string_type;

      explicit numpunct(size_t __refs = 0);

      _LIBCPP_ALWAYS_INLINE char_type decimal_point() const
        { return do_decimal_point();}
      _LIBCPP_ALWAYS_INLINE char_type thousands_sep() const
        { return do_thousands_sep();}
      _LIBCPP_ALWAYS_INLINE string grouping() const
        { return do_grouping();}
      _LIBCPP_ALWAYS_INLINE string_type truename() const
        { return do_truename();}
      _LIBCPP_ALWAYS_INLINE string_type falsename() const
        { return do_falsename();}

      static locale::id id;

    protected:
      ~numpunct();
      virtual char_type do_decimal_point() const;
      virtual char_type do_thousands_sep() const;
      virtual string do_grouping() const;
      virtual string_type do_truename() const;
      virtual string_type do_falsename() const;

      char_type __decimal_point_;
      char_type __thousands_sep_;
      string __grouping_;
    };

// template <class charT> class numpunct_byname

  template <class charT> class _LIBCPP_VISIBLE numpunct_byname;

  template <>
  class _LIBCPP_VISIBLE numpunct_byname<char>
  : public numpunct<char>
    {
    public:
      typedef char char_type;
      typedef basic_string<char_type> string_type;

      explicit numpunct_byname(const char* __nm, size_t __refs = 0);
      explicit numpunct_byname(const string& __nm, size_t __refs = 0);

    protected:
      ~numpunct_byname();

    private:
      void __init(const char*);
    };

  template <>
  class _LIBCPP_VISIBLE numpunct_byname<wchar_t>
  : public numpunct<wchar_t>
    {
    public:
      typedef wchar_t char_type;
      typedef basic_string<char_type> string_type;

      explicit numpunct_byname(const char* __nm, size_t __refs = 0);
      explicit numpunct_byname(const string& __nm, size_t __refs = 0);

    protected:
      ~numpunct_byname();

    private:
      void __init(const char*);
    };
#endif

//_LIBCPP_END_NAMESPACE_STD
}
}

#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INTERNAL_LOCALE_H_