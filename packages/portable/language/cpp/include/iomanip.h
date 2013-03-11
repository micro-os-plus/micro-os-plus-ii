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

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_IOMANIP_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_IOMANIP_H_

#include "portable/core/include/OS_Defines.h"

#include "portable/language/cpp/include/internal/__config.h"

#include "portable/language/cpp/include/ostream.h"

//#include "portable/language/cpp/include/istream"

namespace os
{
  namespace std
  {

    // resetiosflags

    class __iom_t1
    {
      ios_base::fmtflags m_mask;
    public:
      _LIBCPP_INLINE_VISIBILITY
      explicit
      __iom_t1(ios_base::fmtflags __m)
          : m_mask(__m)
      {
      }

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

      template<class _CharT, class _Traits>
      friend _LIBCPP_INLINE_VISIBILITY
      basic_istream<_CharT, _Traits>&
      operator>>(basic_istream<_CharT, _Traits>& __is, const __iom_t1& __x)
        {
          __is.unsetf(__x.m_mask);
          return __is;
        }
#endif

      template<class _CharT, class _Traits>
        friend _LIBCPP_INLINE_VISIBILITY
        basic_ostream<_CharT, _Traits>&
        operator<<(basic_ostream<_CharT, _Traits>& __os, const __iom_t1& __x) {
        __os.unsetf(__x.m_mask);
        return __os;
      }
  };

    inline _LIBCPP_INLINE_VISIBILITY
    __iom_t1
    resetiosflags(ios_base::fmtflags __mask)
    {
      return __iom_t1(__mask);
    }

    // setiosflags

    class __iom_t2
    {
      ios_base::fmtflags m_mask;
    public:
      _LIBCPP_INLINE_VISIBILITY
      explicit
      __iom_t2(ios_base::fmtflags __m)
          : m_mask(__m)
      {
      }

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      template<class _CharT, class _Traits>
      friend _LIBCPP_INLINE_VISIBILITY
      basic_istream<_CharT, _Traits>&
      operator>>(basic_istream<_CharT, _Traits>& __is, const __iom_t2& __x)
        {
          __is.setf(__x.m_mask);
          return __is;
        }
#endif

      template<class _CharT, class _Traits>
        friend _LIBCPP_INLINE_VISIBILITY
        basic_ostream<_CharT, _Traits>&
        operator<<(basic_ostream<_CharT, _Traits>& __os, const __iom_t2& __x) {
        __os.setf(__x.m_mask);
        return __os;
      }
  };

    inline _LIBCPP_INLINE_VISIBILITY
    __iom_t2
    setiosflags(ios_base::fmtflags __mask)
    {
      return __iom_t2(__mask);
    }

    // setbase

    class __iom_t3
    {
      int m_base;
    public:
      _LIBCPP_INLINE_VISIBILITY
      explicit
      __iom_t3(int __b)
          : m_base(__b)
      {
      }

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      template<class _CharT, class _Traits>
      friend _LIBCPP_INLINE_VISIBILITY
      basic_istream<_CharT, _Traits>&
      operator>>(basic_istream<_CharT, _Traits>& __is, const __iom_t3& __x)
        {
          __is.setf(__x.m_base == 8 ? ios_base::oct :
              __x.m_base == 10 ? ios_base::dec :
              __x.m_base == 16 ? ios_base::hex :
              ios_base::fmtflags(0), ios_base::basefield);
          return __is;
        }
#endif

      template<class _CharT, class _Traits>
        friend _LIBCPP_INLINE_VISIBILITY
        basic_ostream<_CharT, _Traits>&
        operator<<(basic_ostream<_CharT, _Traits>& __os, const __iom_t3& __x) {
        __os.setf(__x.m_base == 8 ? ios_base::oct :
            __x.m_base == 10 ? ios_base::dec :
            __x.m_base == 16 ? ios_base::hex :
            ios_base::fmtflags(0), ios_base::basefield);
        return __os;
      }
  };

    inline _LIBCPP_INLINE_VISIBILITY
    __iom_t3
    setbase(int __base)
    {
      return __iom_t3(__base);
    }

    // setfill

    template<class _CharT>
      class __iom_t4
      {
        _CharT m_fill;
      public:
        _LIBCPP_INLINE_VISIBILITY
        explicit
        __iom_t4(_CharT __c)
            : m_fill(__c)
        {
        }

        template<class _Traits>
          friend _LIBCPP_INLINE_VISIBILITY
          basic_ostream<_CharT, _Traits>&
          operator<<(basic_ostream<_CharT, _Traits>& __os, const __iom_t4& __x) {
          __os.fill(__x.m_fill);
          return __os;
        }
    };

    template<class _CharT>
      inline _LIBCPP_INLINE_VISIBILITY
      __iom_t4<_CharT>
      setfill(_CharT __c)
      {
        return __iom_t4<_CharT>(__c);
      }

    // setprecision

    class __iom_t5
    {
      int __n_;
    public:
      _LIBCPP_INLINE_VISIBILITY
      explicit
      __iom_t5(int __n)
          : __n_(__n)
      {
      }

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      template<class _CharT, class _Traits>
      friend _LIBCPP_INLINE_VISIBILITY
      basic_istream<_CharT, _Traits>&
      operator>>(basic_istream<_CharT, _Traits>& __is, const __iom_t5& __x)
        {
          __is.precision(__x.m_num);
          return __is;
        }
#endif

      template<class _CharT, class _Traits>
        friend _LIBCPP_INLINE_VISIBILITY
        basic_ostream<_CharT, _Traits>&
        operator<<(basic_ostream<_CharT, _Traits>& __os, const __iom_t5& __x) {
        __os.precision(__x.__n_);
        return __os;
      }
  };

    inline _LIBCPP_INLINE_VISIBILITY
    __iom_t5
    setprecision(int __n)
    {
      return __iom_t5(__n);
    }

    // setw

    class __iom_t6
    {
      int m_num;
    public:
      _LIBCPP_INLINE_VISIBILITY
      explicit
      __iom_t6(int __n)
          : m_num(__n)
      {
      }

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      template<class _CharT, class _Traits>
      friend _LIBCPP_INLINE_VISIBILITY
      basic_istream<_CharT, _Traits>&
      operator>>(basic_istream<_CharT, _Traits>& __is, const __iom_t6& __x)
        {
          __is.width(__x.m_num);
          return __is;
        }
#endif

      template<class _CharT, class _Traits>
        friend _LIBCPP_INLINE_VISIBILITY
        basic_ostream<_CharT, _Traits>&
        operator<<(basic_ostream<_CharT, _Traits>& __os, const __iom_t6& __x) {
        __os.width(__x.m_num);
        return __os;
      }
  };

    inline _LIBCPP_INLINE_VISIBILITY
    __iom_t6
    setw(int __n)
    {
      return __iom_t6(__n);
    }

    // get_money

    template<class _MoneyT>
      class __iom_t7;

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
    template<class _CharT, class _Traits, class _MoneyT>
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __is,
        const __iom_t7 <_MoneyT>& __x);
#endif

    template<class _MoneyT>
    class __iom_t7
    {
      _MoneyT& m_money;
      bool m_intl;
    public:
      _LIBCPP_INLINE_VISIBILITY
      __iom_t7(_MoneyT& __mon, bool __intl)
          : m_money(__mon), m_intl(__intl)
      {
      }

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      template<class _CharT, class _Traits, class _Mp>
      friend basic_istream<_CharT, _Traits>&
      operator>>(basic_istream<_CharT, _Traits>& __is,
          const __iom_t7 <_Mp>& __x);
#endif
    };

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
  template<class _CharT, class _Traits, class _MoneyT>
  basic_istream<_CharT, _Traits>&
  operator>>(basic_istream<_CharT, _Traits>& __is,
      const __iom_t7 <_MoneyT>& __x)
    {
#ifndef _LIBCPP_NO_EXCEPTIONS
      try
        {
#endif  // _LIBCPP_NO_EXCEPTIONS
          typename basic_istream<_CharT, _Traits>::sentry __s(__is);
          if (__s)
            {
              typedef istreambuf_iterator<_CharT, _Traits> _Ip;
              typedef money_get<_CharT, _Ip> _Fp;
              ios_base::iostate __err = ios_base::goodbit;
              const _Fp& __mf = use_facet<_Fp>(__is.getloc());
              __mf.get(_Ip(__is), _Ip(), __x.m_intl, __is, __err, __x.m_money);
              __is.setstate(__err);
            }
#ifndef _LIBCPP_NO_EXCEPTIONS
        }
      catch (...)
        {
          __is.__set_badbit_and_consider_rethrow();
        }
#endif  // _LIBCPP_NO_EXCEPTIONS
      return __is;
    }
#endif

      template<class _MoneyT>
        inline _LIBCPP_INLINE_VISIBILITY
        __iom_t7<_MoneyT>
        get_money(_MoneyT& __mon, bool __intl = false)
        {
          return __iom_t7 < _MoneyT > (__mon, __intl);
        }

      // put_money

      template<class _MoneyT>
        class __iom_t8;

      template<class _CharT, class _Traits, class _MoneyT>
        basic_ostream<_CharT, _Traits>&
        operator<<(basic_ostream<_CharT, _Traits>& __os,
            const __iom_t8 <_MoneyT>& __x);

      template<class _MoneyT>
        class __iom_t8
        {
          const _MoneyT& m_money;
          bool m_intl;
        public:
          _LIBCPP_INLINE_VISIBILITY
          __iom_t8(const _MoneyT& __mon, bool __intl)
              : m_money(__mon), m_intl(__intl)
          {
          }

          template<class _CharT, class _Traits, class _Mp>
            friend basic_ostream<_CharT, _Traits>&
            operator<<(basic_ostream<_CharT, _Traits>& __os,
                const __iom_t8 <_Mp>& __x);
        };

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      template<class _CharT, class _Traits, class _MoneyT>
        basic_ostream<_CharT, _Traits>&
        operator<<(basic_ostream<_CharT, _Traits>& __os,
            const __iom_t8 <_MoneyT>& __x)
        {
#ifndef _LIBCPP_NO_EXCEPTIONS
          try
            {
#endif  // _LIBCPP_NO_EXCEPTIONS
          typename basic_ostream<_CharT, _Traits>::sentry __s(__os);
          if (__s)
            {
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
              typedef ostreambuf_iterator<_CharT, _Traits> _Op;
              typedef money_put<_CharT, _Op> _Fp;
              const _Fp& __mf = use_facet<_Fp>(__os.getloc());
              if (__mf.put(_Op(__os), __x.m_intl, __os, __os.fill(),
                  __x.m_money).failed())
                {
                  __os.setstate(ios_base::badbit);
                }
#endif
            }
#ifndef _LIBCPP_NO_EXCEPTIONS
        }
      catch (...)
        {
          __os.__set_badbit_and_consider_rethrow();
        }
#endif  // _LIBCPP_NO_EXCEPTIONS
          return __os;
        }

      template<class _MoneyT>
        inline _LIBCPP_INLINE_VISIBILITY
        __iom_t8<_MoneyT>
        put_money(const _MoneyT& __mon, bool __intl = false)
        {
          return __iom_t8<_MoneyT>(__mon, __intl);
        }
#endif

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      // get_time

      template<class _CharT>
      class __iom_t9;

      template<class _CharT, class _Traits>
      basic_istream<_CharT, _Traits>&
      operator>>(basic_istream<_CharT, _Traits>& __is,
          const __iom_t9 <_CharT>& __x);

      template<class _CharT>
      class __iom_t9
        {
          tm* m_tm;
          const _CharT* m_fmt;
        public:
          _LIBCPP_INLINE_VISIBILITY
          __iom_t9(tm* __tm, const _CharT* __fmt)
          : m_tm(__tm), m_fmt(__fmt)
            {
            }

          template<class _Cp, class _Traits>
          friend basic_istream<_Cp, _Traits>&
          operator>>(basic_istream<_Cp, _Traits>& __is,
              const __iom_t9 <_Cp>& __x);
        };

      template<class _CharT, class _Traits>
      basic_istream<_CharT, _Traits>&
      operator>>(basic_istream<_CharT, _Traits>& __is,
          const __iom_t9 <_CharT>& __x)
        {
#ifndef _LIBCPP_NO_EXCEPTIONS
          try
            {
#endif  // _LIBCPP_NO_EXCEPTIONS
              typename basic_istream<_CharT, _Traits>::sentry __s(__is);
              if (__s)
                {
                  typedef istreambuf_iterator<_CharT, _Traits> _Ip;
                  typedef time_get<_CharT, _Ip> _Fp;
                  ios_base::iostate __err = ios_base::goodbit;
                  const _Fp& __tf = use_facet<_Fp>(__is.getloc());
                  __tf.get(_Ip(__is), _Ip(), __is, __err, __x.m_tm, __x.m_fmt,
                      __x.m_fmt + _Traits::length(__x.m_fmt));
                  __is.setstate(__err);
                }
#ifndef _LIBCPP_NO_EXCEPTIONS
            }
          catch (...)
            {
              __is.__set_badbit_and_consider_rethrow();
            }
#endif  // _LIBCPP_NO_EXCEPTIONS
          return __is;
        }

      template<class _CharT>
      inline _LIBCPP_INLINE_VISIBILITY
      __iom_t9<_CharT>
      get_time(tm* __tm, const _CharT* __fmt)
        {
          return __iom_t9<_CharT>(__tm, __fmt);
        }
#endif

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      // put_time

      template<class _CharT>
        class __iom_t10;

      template<class _CharT, class _Traits>
        basic_ostream<_CharT, _Traits>&
        operator<<(basic_ostream<_CharT, _Traits>& __os,
            const __iom_t10 <_CharT>& __x);

      template<class _CharT>
        class __iom_t10
        {
          const tm* m_tm;
          const _CharT* m_fmt;
        public:
          _LIBCPP_INLINE_VISIBILITY
          __iom_t10(const tm* __tm, const _CharT* __fmt)
              : m_tm(__tm), m_fmt(__fmt)
          {
          }

          template<class _Cp, class _Traits>
            friend basic_ostream<_Cp, _Traits>&
            operator<<(basic_ostream<_Cp, _Traits>& __os,
                const __iom_t10 <_Cp>& __x);
        };

      template<class _CharT, class _Traits>
        basic_ostream<_CharT, _Traits>&
        operator<<(basic_ostream<_CharT, _Traits>& __os,
            const __iom_t10 <_CharT>& __x)
        {
#ifndef _LIBCPP_NO_EXCEPTIONS
          try
            {
#endif  // _LIBCPP_NO_EXCEPTIONS
          typename basic_ostream<_CharT, _Traits>::sentry __s(__os);
          if (__s)
            {
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
              typedef ostreambuf_iterator<_CharT, _Traits> _Op;
              typedef time_put<_CharT, _Op> _Fp;
              const _Fp& __tf = use_facet<_Fp>(__os.getloc());
              if (__tf.put(_Op(__os), __os, __os.fill(), __x.m_tm, __x.m_fmt,
                  __x.m_fmt + _Traits::length(__x.m_fmt)).failed())
                {
                  __os.setstate(ios_base::badbit);
                }
#endif
            }
#ifndef _LIBCPP_NO_EXCEPTIONS
        }
      catch (...)
        {
          __os.__set_badbit_and_consider_rethrow();
        }
#endif  // _LIBCPP_NO_EXCEPTIONS
          return __os;
        }

      template<class _CharT>
        inline _LIBCPP_INLINE_VISIBILITY
        __iom_t10<_CharT>
        put_time(const tm* __tm, const _CharT* __fmt)
        {
          return __iom_t10<_CharT>(__tm, __fmt);
        }
#endif

    }
  }

#endif // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_IOMANIP_H_
