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

#include "portable/core/include/ConfigDefines.h"

#include "portable/language/cpp/include/internal/__config.h"

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_OSTREAM)
#include "portable/language/cpp/include/ostream.h"
#endif
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_ISTREAM)
#include "portable/language/cpp/include/istream"
#endif

namespace os
{
  namespace std
  {

    /// \addtogroup standardManipulators
    /// @{
    /// \brief ios_base flags manipulators.
    /// \headerfile iomanip.h "portable/language/cpp/include/iomanip.h"
    /// \details
    /// The header `iomanip.h` defines several functions that
    /// support extractors and inserters that alter
    /// information maintained by class ios_base and
    /// its derived classes.

    // \name Standard manipulators (27.7.4)
    /// \name Standard manipulator functions
    /// @{

    // ------------------------------------------------------------------------
    // resetiosflags

    /// \brief Support class for resetiosflags().
    class __iom_resetiosflags
    {
      ios_base::fmtflags m_mask;
    public:
      _LIBCPP_INLINE_VISIBILITY
      explicit
      __iom_resetiosflags(ios_base::fmtflags mask)
          : m_mask(mask)
      {
      }

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_ISTREAM)
      template<class TChar_T, class TTraits_T>
      friend _LIBCPP_INLINE_VISIBILITY
      basic_istream<TChar_T, TTraits_T>&
      operator>>(basic_istream<TChar_T, TTraits_T>& __is, const __iom_resetiosflags& __x);
#endif

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_OSTREAM)
      template<class TChar_T, class TTraits_T>
        friend _LIBCPP_INLINE_VISIBILITY
        basic_ostream<TChar_T, TTraits_T>&
        operator<<(basic_ostream<TChar_T, TTraits_T>& outs,
            const __iom_resetiosflags& x);
#endif
          };

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_ISTREAM)
        template<class TChar_T, class TTraits_T>
        _LIBCPP_INLINE_VISIBILITY
        basic_istream<TChar_T, TTraits_T>&
        operator>>(basic_istream<TChar_T, TTraits_T>& __is, const __iom_resetiosflags& __x)
          {
            __is.unsetf(__x.m_mask);
            return __is;
          }
#endif

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_OSTREAM)
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_ostream<TChar_T, TTraits_T>&
      operator<<(basic_ostream<TChar_T, TTraits_T>& outs, const __iom_resetiosflags& x)
        {
          outs.unsetf(x.m_mask);
          return outs;
        }
#endif

      /// \brief Reset ios_base flags.
      ///
      /// \param mask A combination of `ios_base::fmtflags`.
      /// \returns An object of unspecified type such that if `out` is an
      /// object of type `basic_ostream<charT, traits>` then the
      /// expression `out << resetiosflags(mask)` behaves as if it called
      /// `f(out, mask)`, or if `in` is an object of type
      /// `basic_istream<charT, traits>` then the expression
      /// `in >> resetiosflags(mask)` behaves as if it called
      /// `f(in, mask)`, where the function `f` is defined as:
      /// ~~~
      /// void f(ios_base& str, ios_base::fmtflags mask)
      /// {
      ///     // reset specified flags
      ///     str.setf(ios_base::fmtflags(0), mask);
      /// }
      /// ~~~
      ///
      /// \details
      /// The expression `out << resetiosflags(mask)` shall
      /// have type `basic_ostream<charT,traits>&` and value `out`.
      /// The expression `in >> resetiosflags(mask)` shall have type
      /// `basic_istream<charT, traits>&` and value `in`.
    inline _LIBCPP_INLINE_VISIBILITY
    __iom_resetiosflags
    resetiosflags(ios_base::fmtflags mask)
    {
      return __iom_resetiosflags(mask);
    }

    // ------------------------------------------------------------------------
    // setiosflags

    /// \brief Support class for setiosflags().
    class __iom_setiosflags
    {
      ios_base::fmtflags m_mask;
    public:
      _LIBCPP_INLINE_VISIBILITY
      explicit
      __iom_setiosflags(ios_base::fmtflags mask)
          : m_mask(mask)
      {
      }
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_ISTREAM)
      template<class TChar_T, class TTraits_T>
      friend _LIBCPP_INLINE_VISIBILITY
      basic_istream<TChar_T, TTraits_T>&
      operator>>(basic_istream<TChar_T, TTraits_T>& __is, const __iom_setiosflags& __x);
#endif
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_OSTREAM)
      template<class TChar_T, class TTraits_T>
        friend _LIBCPP_INLINE_VISIBILITY
        basic_ostream<TChar_T, TTraits_T>&
        operator<<(basic_ostream<TChar_T, TTraits_T>& outs,
            const __iom_setiosflags& __x );
#endif
          };

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_ISTREAM)
        template<class TChar_T, class TTraits_T>
        _LIBCPP_INLINE_VISIBILITY
        basic_istream<TChar_T, TTraits_T>&
        operator>>(basic_istream<TChar_T, TTraits_T>& __is, const __iom_setiosflags& __x)
          {
            __is.setf(__x.m_mask);
            return __is;
          }
#endif

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_OSTREAM)
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_ostream<TChar_T, TTraits_T>&
      operator<<(basic_ostream<TChar_T, TTraits_T>& outs,
          const __iom_setiosflags& __x) {
          outs.setf(__x.m_mask);
          return outs;
        }
#endif

      /// \brief Set ios_base flags.
      /// \param mask A combination of `ios_base::fmtflags`.
      /// \returns An object of unspecified type such that if out is
      /// an object of type `basic_ostream<charT, traits>` then
      /// the expression `out << resetiosflags(mask)` behaves as if
      /// it called `f(out, mask)`, or if in is an object of type
      /// `basic_istream<charT, traits>` then the expression
      /// `in >> resetiosflags(mask)` behaves as if it called
      /// `f(in, mask)`, where the function `f` is defined as:
      /// ~~~
      /// void f(ios_base& str, ios_base::fmtflags mask)
      /// {
      ///     // reset specified flags
      ///     str.setf(ios_base::fmtflags(0), mask);
      /// }
      /// ~~~
      ///
      /// \details
      /// The expression `out << resetiosflags(mask)` shall have
      /// type `basic_ostream<charT,traits>&` and value `out`.
      /// The expression `in >> resetiosflags(mask)` shall have
      /// `type basic_istream<charT, traits>&` and value `in`.
    inline _LIBCPP_INLINE_VISIBILITY
    __iom_setiosflags
    setiosflags(ios_base::fmtflags mask)
    {
      return __iom_setiosflags(mask);
    }

    // ------------------------------------------------------------------------
    // setbase

    /// \brief Support class for setbase().
    class __iom_setbase
    {
      int m_base;
    public:
      _LIBCPP_INLINE_VISIBILITY
      explicit
      __iom_setbase(int __b)
          : m_base(__b)
      {
      }

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_ISTREAM)
      template<class TChar_T, class TTraits_T>
      friend _LIBCPP_INLINE_VISIBILITY
      basic_istream<TChar_T, TTraits_T>&
      operator>>(basic_istream<TChar_T, TTraits_T>& __is, const __iom_setbase& __x);
#endif

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_OSTREAM)
      template<class TChar_T, class TTraits_T>
        friend _LIBCPP_INLINE_VISIBILITY
        basic_ostream<TChar_T, TTraits_T>&
        operator<<(basic_ostream<TChar_T, TTraits_T>& outs, const __iom_setbase& __x );
#endif

      };

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_ISTREAM)
    template<class TChar_T, class TTraits_T>
    _LIBCPP_INLINE_VISIBILITY
    basic_istream<TChar_T, TTraits_T>&
    operator>>(basic_istream<TChar_T, TTraits_T>& __is, const __iom_setbase& __x)
      {
        __is.setf(__x.m_base == 8 ? ios_base::oct :
            __x.m_base == 10 ? ios_base::dec :
            __x.m_base == 16 ? ios_base::hex :
            ios_base::fmtflags(0), ios_base::basefield);
        return __is;
      }
#endif

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_OSTREAM)
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_ostream<TChar_T, TTraits_T>&
      operator<<(basic_ostream<TChar_T, TTraits_T>& outs, const __iom_setbase& __x) {
      outs.setf(__x.m_base == 8 ? ios_base::oct :
          __x.m_base == 10 ? ios_base::dec :
          __x.m_base == 16 ? ios_base::hex :
          ios_base::fmtflags(0), ios_base::basefield);
      return outs;
    }
#endif

  /// \brief Set ios_base numerical base.
  /// \param base An integer in [8, 10, 16].
  /// \returns An object of unspecified type such that
  /// if `out` is an object of type `basic_ostream<charT, traits>` then
  /// the expression `out << setbase(base)` behaves as if it
  /// called `f(out, base)`, or if `in` is an object of type
  /// `basic_istream<charT, traits>` then the expression
  /// `in >> setbase(base)` behaves as if it called
  /// `f(in, base)`, where the function `f` is defined as:
  /// ~~~
  /// void f(ios_base& str, int base)
  /// {
  ///   // set basefield
  ///   str.setf(base == 8 ? ios_base::oct :
  ///           base == 10 ? ios_base::dec :
  ///           base == 16 ? ios_base::hex :
  ///           ios_base::fmtflags(0), ios_base::basefield);
  /// }
  /// ~~~
  ///
  /// \details
  /// The expression `out << setbase(base)` shall have type
  /// `basic_ostream<charT, traits>&` and value `out`.
  /// The expression `in >> setbase(base)` shall have
  /// type `basic_istream<charT, traits>&` and value `in`.
    inline _LIBCPP_INLINE_VISIBILITY
    __iom_setbase
    setbase(int base)
    {
      return __iom_setbase(base);
    }

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_OSTREAM)

    // setfill

    /// \brief Support class for setfill().
    template<class TChar_T>
      class __iom_setfill
      {
        TChar_T m_fill;
      public:
        _LIBCPP_INLINE_VISIBILITY
        explicit
        __iom_setfill(TChar_T __c)
            : m_fill(__c)
        {
        }

        template<class TTraits_T>
          friend _LIBCPP_INLINE_VISIBILITY
          basic_ostream<TChar_T, TTraits_T>&
          operator<<(basic_ostream<TChar_T, TTraits_T>& outs,
              const __iom_setfill& __x) {
              outs.fill(__x.m_fill);
              return outs;
            }
        };

          /// \brief Set ios_base fill character.
          /// \param c A character.
          /// \returns  An object of unspecified type such that
          /// if out is an object of type basic_ostream<charT, traits>
          /// and c has type charT then the expression out << setfill(c)
          /// behaves as if it called f(out, c), where the function
          /// f is defined as:
          /// ~~~
          /// template<class charT, class traits>
          /// void f(basic_ios<charT,traits>& str, charT c)
          /// {
          ///         // set fill character
          ///         str.fill(c);
          /// }
          /// ~~~
          ///
          /// \details
          /// The expression `out << setfill(c)` shall have type
          /// `basic_ostream<charT, traits>&` and value `out`.
    template<class TChar_T>
      inline _LIBCPP_INLINE_VISIBILITY
      __iom_setfill<TChar_T>
      setfill(TChar_T c)
      {
        return __iom_setfill<TChar_T>(c);
      }

#endif

    // ------------------------------------------------------------------------
    // setprecision

    /// \brief Support class for setprecision().
    class __iom_setprecision
    {
      int m_n;
    public:
      _LIBCPP_INLINE_VISIBILITY
      explicit
      __iom_setprecision(int n)
          : m_n(n)
      {
      }

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_ISTREAM)
      template<class TChar_T, class TTraits_T>
      friend _LIBCPP_INLINE_VISIBILITY
      basic_istream<TChar_T, TTraits_T>&
      operator>>(basic_istream<TChar_T, TTraits_T>& __is, const __iom_setprecision& __x);
#endif

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_OSTREAM)
      template<class TChar_T, class TTraits_T>
        friend _LIBCPP_INLINE_VISIBILITY
        basic_ostream<TChar_T, TTraits_T>&
        operator<<(basic_ostream<TChar_T, TTraits_T>& outs,
            const __iom_setprecision& x);
#endif

          };

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_ISTREAM)
        template<class TChar_T, class TTraits_T>
        _LIBCPP_INLINE_VISIBILITY
        basic_istream<TChar_T, TTraits_T>&
        operator>>(basic_istream<TChar_T, TTraits_T>& __is, const __iom_setprecision& __x)
          {
            __is.precision(__x.m_num);
            return __is;
          }
#endif

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_OSTREAM)
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_ostream<TChar_T, TTraits_T>&
      operator<<(basic_ostream<TChar_T, TTraits_T>& outs, const __iom_setprecision& x)
        {
          outs.precision(x.m_n);
          return outs;
        }
#endif

      /// \brief Set ios_base float precision.
      /// \param n An integer defining the precision.
      /// \returns An object of unspecified type such that if `out` is
      /// an object of type `basic_ostream<charT, traits>` then the
      /// expression `out << setprecision(n)` behaves as if it
      /// called `f(out, n)`, or if `in` is an object of type
      /// `basic_istream<charT, traits>` then the expression
      /// `in >> setprecision(n)` behaves as if it called
      /// `f(in, n)`, where the function `f` is defined as:
      /// ~~~
      /// void f(ios_base& str, int n)
      /// {
      ///       // set precision
      ///       str.precision(n);
      /// }
      /// ~~~
      ///
      /// \details
      /// The expression `out << setprecision(n)` shall have type
      /// `basic_ostream<charT, traits>&` and value `out`.
      /// The expression `in >> setprecision(n)` shall have
      /// type `basic_istream<charT, traits>&` and value `in`.

    inline _LIBCPP_INLINE_VISIBILITY
    __iom_setprecision
    setprecision(int n)
    {
      return __iom_setprecision(n);
    }

    // ------------------------------------------------------------------------
    // setw

    /// \brief Support class for setw().
    class __iom_setw
    {
      int m_width;
    public:
      _LIBCPP_INLINE_VISIBILITY
      explicit
      __iom_setw(int n)
          : m_width(n)
      {
      }

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_ISTREAM)
      template<class TChar_T, class TTraits_T>
      friend _LIBCPP_INLINE_VISIBILITY
      basic_istream<TChar_T, TTraits_T>&
      operator>>(basic_istream<TChar_T, TTraits_T>& __is, const __iom_setw& __x);
#endif

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_OSTREAM)
      template<class TChar_T, class TTraits_T>
        friend _LIBCPP_INLINE_VISIBILITY
        basic_ostream<TChar_T, TTraits_T>&
        operator<<(basic_ostream<TChar_T, TTraits_T>& outs, const __iom_setw& x);
#endif

      };

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_ISTREAM)
    template<class TChar_T, class TTraits_T>
    _LIBCPP_INLINE_VISIBILITY
    basic_istream<TChar_T, TTraits_T>&
    operator>>(basic_istream<TChar_T, TTraits_T>& __is, const __iom_setw& __x)
      {
        __is.width(__x.m_num);
        return __is;
      }
#endif

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_OSTREAM)
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_ostream<TChar_T, TTraits_T>&
      operator<<(basic_ostream<TChar_T, TTraits_T>& outs, const __iom_setw& x)
        {
          outs.width(x.m_width);
          return outs;
        }
#endif

      /// \brief Set ios_base field width.
      /// \param n An integer defining the width.
      /// \returns An object of unspecified type such that if out
      /// is an instance of `basic_ostream<charT, traits>` then the
      /// expression `out << setw(n)` behaves as if it called
      /// `f(out, n)`, or if `in` is an object of type
      /// `basic_istream<charT, traits>` then the expression
      /// `in >> setw(n)` behaves as if it called `f(in, n)`,
      /// where the function `f` is defined as:
      /// ~~~
      /// void f(ios_base& str, int n)
      /// {
      ///       // set width
      ///       str.width(n);
      /// }
      /// ~~~
      ///
      /// \details
      /// The expression `out << setw(n)` shall have type
      /// `basic_ostream<charT, traits>&` and value `out`. The
      /// expression `in >> setw(n)` shall have type
      /// `basic_istream<charT, traits>&` and value `in`.
    inline _LIBCPP_INLINE_VISIBILITY
    __iom_setw
    setw(int n)
    {
      return __iom_setw(n);
    }

/// @}
// end of \name Standard manipulators (27.7.4)

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

/// \name Extended manipulators (27.7.5)
/// @{

// ------------------------------------------------------------------------
// get_money

template<class _MoneyT>
class __iom_t7;

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
template<class TChar_T, class TTraits_T, class _MoneyT>
basic_istream<TChar_T, TTraits_T>&
operator>>(basic_istream<TChar_T, TTraits_T>& __is,
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

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_ISTREAM)
    template<class TChar_T, class TTraits_T, class _Mp>
    friend basic_istream<TChar_T, TTraits_T>&
    operator>>(basic_istream<TChar_T, TTraits_T>& __is,
        const __iom_t7 <_Mp>& __x);
#endif
  };

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_ISTREAM)
template<class TChar_T, class TTraits_T, class _MoneyT>
basic_istream<TChar_T, TTraits_T>&
operator>>(basic_istream<TChar_T, TTraits_T>& __is,
    const __iom_t7 <_MoneyT>& __x)
  {
#if defined(OS_INCLUDE_STD_EXCEPTIONS)
    try
      {
#endif  // OS_INCLUDE_STD_EXCEPTIONS
        typename basic_istream<TChar_T, TTraits_T>::sentry __s(__is);
        if (__s)
          {
            typedef istreambuf_iterator<TChar_T, TTraits_T> _Ip;
            typedef money_get<TChar_T, _Ip> _Fp;
            ios_base::iostate __err = ios_base::goodbit;
            const _Fp& __mf = use_facet<_Fp>(__is.getloc());
            __mf.get(_Ip(__is), _Ip(), __x.m_intl, __is, __err, __x.m_money);
            __is.setstate(__err);
          }
#if defined(OS_INCLUDE_STD_EXCEPTIONS)
      }
    catch (...)
      {
        __is.__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_STD_EXCEPTIONS
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

// ----------------------------------------------------------------------
// put_money

template<class _MoneyT>
class __iom_t8;

template<class TChar_T, class TTraits_T, class _MoneyT>
basic_ostream<TChar_T, TTraits_T>&
operator<<(basic_ostream<TChar_T, TTraits_T>& outs,
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

    template<class TChar_T, class TTraits_T, class _Mp>
    friend basic_ostream<TChar_T, TTraits_T>&
    operator<<(basic_ostream<TChar_T, TTraits_T>& outs,
        const __iom_t8 <_Mp>& __x);
  };

template<class TChar_T, class TTraits_T, class _MoneyT>
basic_ostream<TChar_T, TTraits_T>&
operator<<(basic_ostream<TChar_T, TTraits_T>& outs,
    const __iom_t8 <_MoneyT>& __x)
  {
#if defined(OS_INCLUDE_STD_EXCEPTIONS)
    try
      {
#endif  // OS_INCLUDE_STD_EXCEPTIONS
        typename basic_ostream<TChar_T, TTraits_T>::sentry __s(outs);
        if (__s)
          {
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
            typedef ostreambuf_iterator<TChar_T, TTraits_T> _Op;
            typedef money_put<TChar_T, _Op> _Fp;
            const _Fp& __mf = use_facet<_Fp>(outs.getloc());
            if (__mf.put(_Op(outs), __x.m_intl, outs, outs.fill(),
                    __x.m_money).failed())
              {
                outs.setstate(ios_base::badbit);
              }
#endif
          }
#if defined(OS_INCLUDE_STD_EXCEPTIONS)
      }
    catch (...)
      {
        outs.__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_STD_EXCEPTIONS
    return outs;
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

// ------------------------------------------------------------------------
// get_time

template<class TChar_T>
class __iom_t9;

template<class TChar_T, class TTraits_T>
basic_istream<TChar_T, TTraits_T>&
operator>>(basic_istream<TChar_T, TTraits_T>& __is,
    const __iom_t9 <TChar_T>& __x);

template<class TChar_T>
class __iom_t9
  {
    tm* m_tm;
    const TChar_T* m_fmt;
  public:
    _LIBCPP_INLINE_VISIBILITY
    __iom_t9(tm* __tm, const TChar_T* __fmt)
    : m_tm(__tm), m_fmt(__fmt)
      {
      }

    template<class _Cp, class TTraits_T>
    friend basic_istream<_Cp, TTraits_T>&
    operator>>(basic_istream<_Cp, TTraits_T>& __is,
        const __iom_t9 <_Cp>& __x);
  };

template<class TChar_T, class TTraits_T>
basic_istream<TChar_T, TTraits_T>&
operator>>(basic_istream<TChar_T, TTraits_T>& __is,
    const __iom_t9 <TChar_T>& __x)
  {
#if defined(OS_INCLUDE_STD_EXCEPTIONS)
    try
      {
#endif  // OS_INCLUDE_STD_EXCEPTIONS
        typename basic_istream<TChar_T, TTraits_T>::sentry __s(__is);
        if (__s)
          {
            typedef istreambuf_iterator<TChar_T, TTraits_T> _Ip;
            typedef time_get<TChar_T, _Ip> _Fp;
            ios_base::iostate __err = ios_base::goodbit;
            const _Fp& __tf = use_facet<_Fp>(__is.getloc());
            __tf.get(_Ip(__is), _Ip(), __is, __err, __x.m_tm, __x.m_fmt,
                __x.m_fmt + TTraits_T::length(__x.m_fmt));
            __is.setstate(__err);
          }
#if defined(OS_INCLUDE_STD_EXCEPTIONS)
      }
    catch (...)
      {
        __is.__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_STD_EXCEPTIONS
    return __is;
  }

template<class TChar_T>
inline _LIBCPP_INLINE_VISIBILITY
__iom_t9<TChar_T>
get_time(tm* __tm, const TChar_T* __fmt)
  {
    return __iom_t9<TChar_T>(__tm, __fmt);
  }
#endif

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

// ------------------------------------------------------------------------
// put_time

template<class TChar_T>
class __iom_t10;

template<class TChar_T, class TTraits_T>
basic_ostream<TChar_T, TTraits_T>&
operator<<(basic_ostream<TChar_T, TTraits_T>& outs,
    const __iom_t10 <TChar_T>& __x);

template<class TChar_T>
class __iom_t10
  {
    const tm* m_tm;
    const TChar_T* m_fmt;
  public:
    _LIBCPP_INLINE_VISIBILITY
    __iom_t10(const tm* __tm, const TChar_T* __fmt)
    : m_tm(__tm), m_fmt(__fmt)
      {
      }

    template<class _Cp, class TTraits_T>
    friend basic_ostream<_Cp, TTraits_T>&
    operator<<(basic_ostream<_Cp, TTraits_T>& outs,
        const __iom_t10 <_Cp>& __x);
  };

template<class TChar_T, class TTraits_T>
basic_ostream<TChar_T, TTraits_T>&
operator<<(basic_ostream<TChar_T, TTraits_T>& outs,
    const __iom_t10 <TChar_T>& __x)
  {
#if defined(OS_INCLUDE_STD_EXCEPTIONS)
    try
      {
#endif  // OS_INCLUDE_STD_EXCEPTIONS
        typename basic_ostream<TChar_T, TTraits_T>::sentry __s(outs);
        if (__s)
          {
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
            typedef ostreambuf_iterator<TChar_T, TTraits_T> _Op;
            typedef time_put<TChar_T, _Op> _Fp;
            const _Fp& __tf = use_facet<_Fp>(outs.getloc());
            if (__tf.put(_Op(outs), outs, outs.fill(), __x.m_tm, __x.m_fmt,
                    __x.m_fmt + TTraits_T::length(__x.m_fmt)).failed())
              {
                outs.setstate(ios_base::badbit);
              }
#endif
          }
#if defined(OS_INCLUDE_STD_EXCEPTIONS)
      }
    catch (...)
      {
        outs.__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_STD_EXCEPTIONS
    return outs;
  }

template<class TChar_T>
inline _LIBCPP_INLINE_VISIBILITY
__iom_t10<TChar_T>
put_time(const tm* __tm, const TChar_T* __fmt)
  {
    return __iom_t10<TChar_T>(__tm, __fmt);
  }

/// @}
// end of \name Extended manipulators (27.7.5)

#endif

/// @}
}
}

#endif // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_IOMANIP_H_
