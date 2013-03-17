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

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_LIMITS_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_LIMITS_H_

#include "portable/core/include/OS_Defines.h"

#include "portable/language/cpp/include/internal/__config.h"

#include "portable/language/cpp/include/type_traits.h"
#include "portable/language/cpp/include/internal/_undef_min_max.h"

namespace os
{
  namespace std
  {

    enum float_round_style
    {
      round_indeterminate = -1,
      round_toward_zero = 0,
      round_to_nearest = 1,
      round_toward_infinity = 2,
      round_toward_neg_infinity = 3
    };

    enum float_denorm_style
    {
      denorm_indeterminate = -1, denorm_absent = 0, denorm_present = 1
    };

#if !defined(__DOXYGEN__)
    template<class _Tp, bool = is_arithmetic<_Tp>::value>
      class __libcpp_numeric_limits
      {
      protected:
        typedef _Tp type;

        static _LIBCPP_CONSTEXPR bool is_specialized = false;_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        min() _NOEXCEPT
        {
          return type();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        max() _NOEXCEPT
        {
          return type();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        lowest() _NOEXCEPT
        {
          return type();
        }

        static _LIBCPP_CONSTEXPR int digits = 0;
        static _LIBCPP_CONSTEXPR int digits10 = 0;
        static _LIBCPP_CONSTEXPR int max_digits10 = 0;
        static _LIBCPP_CONSTEXPR bool is_signed = false;
        static _LIBCPP_CONSTEXPR bool is_integer = false;
        static _LIBCPP_CONSTEXPR bool is_exact = false;
        static _LIBCPP_CONSTEXPR int radix = 0;_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        epsilon() _NOEXCEPT
        {
          return type();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        round_error() _NOEXCEPT
        {
          return type();
        }

        static _LIBCPP_CONSTEXPR int min_exponent = 0;
        static _LIBCPP_CONSTEXPR int min_exponent10 = 0;
        static _LIBCPP_CONSTEXPR int max_exponent = 0;
        static _LIBCPP_CONSTEXPR int max_exponent10 = 0;

        static _LIBCPP_CONSTEXPR bool has_infinity = false;
        static _LIBCPP_CONSTEXPR bool has_quiet_NaN = false;
        static _LIBCPP_CONSTEXPR bool has_signaling_NaN = false;
        static _LIBCPP_CONSTEXPR float_denorm_style has_denorm = denorm_absent;
        static _LIBCPP_CONSTEXPR bool has_denorm_loss = false;_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        infinity() _NOEXCEPT
        {
          return type();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        quiet_NaN() _NOEXCEPT
        {
          return type();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        signaling_NaN() _NOEXCEPT
        {
          return type();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        denorm_min() _NOEXCEPT
        {
          return type();
        }

        static _LIBCPP_CONSTEXPR bool is_iec559 = false;
        static _LIBCPP_CONSTEXPR bool is_bounded = false;
        static _LIBCPP_CONSTEXPR bool is_modulo = false;

        static _LIBCPP_CONSTEXPR bool traps = false;
        static _LIBCPP_CONSTEXPR bool tinyness_before = false;
        static _LIBCPP_CONSTEXPR float_round_style round_style =
            round_toward_zero;
      };

    template<class _Tp, int digits, bool is_signed>
      struct __libcpp_compute_min
      {
        static _LIBCPP_CONSTEXPR _Tp value = _Tp(_Tp(1) << digits);
      };

    template<class _Tp, int digits>
      struct __libcpp_compute_min<_Tp, digits, false>
      {
        static _LIBCPP_CONSTEXPR _Tp value = _Tp(0);
      };

    template<class _Tp>
      class __libcpp_numeric_limits<_Tp, true>
      {
      protected:
        typedef _Tp type;

        static _LIBCPP_CONSTEXPR bool is_specialized = true;

        static _LIBCPP_CONSTEXPR bool is_signed = type(-1) < type(0);
        static _LIBCPP_CONSTEXPR int digits = static_cast<int>(sizeof(type)
            * __CHAR_BIT__ - is_signed);
        static _LIBCPP_CONSTEXPR int digits10 = digits * 3 / 10;
        static _LIBCPP_CONSTEXPR int max_digits10 = 0;
        static _LIBCPP_CONSTEXPR type __min = __libcpp_compute_min<type, digits,
            is_signed>::value;
        static _LIBCPP_CONSTEXPR type __max =
            is_signed ? type(type(~0) ^ __min) : type(~0);_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        min() _NOEXCEPT
        {
          return __min;
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        max() _NOEXCEPT
        {
          return __max;
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        lowest() _NOEXCEPT
        {
          return min();
        }

        static _LIBCPP_CONSTEXPR bool is_integer = true;
        static _LIBCPP_CONSTEXPR bool is_exact = true;
        static _LIBCPP_CONSTEXPR int radix = 2;_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        epsilon() _NOEXCEPT
        {
          return type(0);
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        round_error() _NOEXCEPT
        {
          return type(0);
        }

        static _LIBCPP_CONSTEXPR int min_exponent = 0;
        static _LIBCPP_CONSTEXPR int min_exponent10 = 0;
        static _LIBCPP_CONSTEXPR int max_exponent = 0;
        static _LIBCPP_CONSTEXPR int max_exponent10 = 0;

        static _LIBCPP_CONSTEXPR bool has_infinity = false;
        static _LIBCPP_CONSTEXPR bool has_quiet_NaN = false;
        static _LIBCPP_CONSTEXPR bool has_signaling_NaN = false;
        static _LIBCPP_CONSTEXPR float_denorm_style has_denorm = denorm_absent;
        static _LIBCPP_CONSTEXPR bool has_denorm_loss = false;_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        infinity() _NOEXCEPT
        {
          return type(0);
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        quiet_NaN() _NOEXCEPT
        {
          return type(0);
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        signaling_NaN() _NOEXCEPT
        {
          return type(0);
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        denorm_min() _NOEXCEPT
        {
          return type(0);
        }

        static _LIBCPP_CONSTEXPR bool is_iec559 = false;
        static _LIBCPP_CONSTEXPR bool is_bounded = true;
        static _LIBCPP_CONSTEXPR bool is_modulo = true;

#if defined(__i386__) || defined(__x86_64__)
        static _LIBCPP_CONSTEXPR bool traps = true;
#else
        static _LIBCPP_CONSTEXPR bool traps = false;
#endif
        static _LIBCPP_CONSTEXPR bool tinyness_before = false;
        static _LIBCPP_CONSTEXPR float_round_style round_style =
            round_toward_zero;
      };

    template<>
      class __libcpp_numeric_limits<bool, true>
      {
      protected:
        typedef bool type;

        static _LIBCPP_CONSTEXPR bool is_specialized = true;

        static _LIBCPP_CONSTEXPR bool is_signed = false;
        static _LIBCPP_CONSTEXPR int digits = 1;
        static _LIBCPP_CONSTEXPR int digits10 = 0;
        static _LIBCPP_CONSTEXPR int max_digits10 = 0;
        static _LIBCPP_CONSTEXPR type __min = false;
        static _LIBCPP_CONSTEXPR type __max = true;_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        min() _NOEXCEPT
        {
          return __min;
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        max() _NOEXCEPT
        {
          return __max;
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        lowest() _NOEXCEPT
        {
          return min();
        }

        static _LIBCPP_CONSTEXPR bool is_integer = true;
        static _LIBCPP_CONSTEXPR bool is_exact = true;
        static _LIBCPP_CONSTEXPR int radix = 2;_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        epsilon() _NOEXCEPT
        {
          return type(0);
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        round_error() _NOEXCEPT
        {
          return type(0);
        }

        static _LIBCPP_CONSTEXPR int min_exponent = 0;
        static _LIBCPP_CONSTEXPR int min_exponent10 = 0;
        static _LIBCPP_CONSTEXPR int max_exponent = 0;
        static _LIBCPP_CONSTEXPR int max_exponent10 = 0;

        static _LIBCPP_CONSTEXPR bool has_infinity = false;
        static _LIBCPP_CONSTEXPR bool has_quiet_NaN = false;
        static _LIBCPP_CONSTEXPR bool has_signaling_NaN = false;
        static _LIBCPP_CONSTEXPR float_denorm_style has_denorm = denorm_absent;
        static _LIBCPP_CONSTEXPR bool has_denorm_loss = false;_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        infinity() _NOEXCEPT
        {
          return type(0);
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        quiet_NaN() _NOEXCEPT
        {
          return type(0);
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        signaling_NaN() _NOEXCEPT
        {
          return type(0);
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        denorm_min() _NOEXCEPT
        {
          return type(0);
        }

        static _LIBCPP_CONSTEXPR bool is_iec559 = false;
        static _LIBCPP_CONSTEXPR bool is_bounded = true;
        static _LIBCPP_CONSTEXPR bool is_modulo = false;

        static _LIBCPP_CONSTEXPR bool traps = false;
        static _LIBCPP_CONSTEXPR bool tinyness_before = false;
        static _LIBCPP_CONSTEXPR float_round_style round_style =
            round_toward_zero;
      };

    template<>
      class __libcpp_numeric_limits<float, true>
      {
      protected:
        typedef float type;

        static _LIBCPP_CONSTEXPR bool is_specialized = true;

        static _LIBCPP_CONSTEXPR bool is_signed = true;
        static _LIBCPP_CONSTEXPR int digits = __FLT_MANT_DIG__;
        static _LIBCPP_CONSTEXPR int digits10 = __FLT_DIG__;
        static _LIBCPP_CONSTEXPR int max_digits10 = 2
            + (digits * 30103) / 100000;_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        min() _NOEXCEPT
        {
          return __FLT_MIN__;
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        max() _NOEXCEPT
        {
          return __FLT_MAX__;
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        lowest() _NOEXCEPT
        {
          return -max();
        }

        static _LIBCPP_CONSTEXPR bool is_integer = false;
        static _LIBCPP_CONSTEXPR bool is_exact = false;
        static _LIBCPP_CONSTEXPR int radix = __FLT_RADIX__;_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        epsilon() _NOEXCEPT
        {
          return __FLT_EPSILON__;
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        round_error() _NOEXCEPT
        {
          return 0.5F;
        }

        static _LIBCPP_CONSTEXPR int min_exponent = __FLT_MIN_EXP__;
        static _LIBCPP_CONSTEXPR int min_exponent10 = __FLT_MIN_10_EXP__;
        static _LIBCPP_CONSTEXPR int max_exponent = __FLT_MAX_EXP__;
        static _LIBCPP_CONSTEXPR int max_exponent10 = __FLT_MAX_10_EXP__;

        static _LIBCPP_CONSTEXPR bool has_infinity = true;
        static _LIBCPP_CONSTEXPR bool has_quiet_NaN = true;
        static _LIBCPP_CONSTEXPR bool has_signaling_NaN = true;
        static _LIBCPP_CONSTEXPR float_denorm_style has_denorm = denorm_present;
        static _LIBCPP_CONSTEXPR bool has_denorm_loss = false;_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        infinity() _NOEXCEPT
        {
          return __builtin_huge_valf();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        quiet_NaN() _NOEXCEPT
        {
          return __builtin_nanf("");
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        signaling_NaN() _NOEXCEPT
        {
          return __builtin_nansf("");
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        denorm_min() _NOEXCEPT
        {
          return __FLT_DENORM_MIN__;
        }

        static _LIBCPP_CONSTEXPR bool is_iec559 = true;
        static _LIBCPP_CONSTEXPR bool is_bounded = true;
        static _LIBCPP_CONSTEXPR bool is_modulo = false;

        static _LIBCPP_CONSTEXPR bool traps = false;
        static _LIBCPP_CONSTEXPR bool tinyness_before = false;
        static _LIBCPP_CONSTEXPR float_round_style round_style =
            round_to_nearest;
      };

    template<>
      class __libcpp_numeric_limits<double, true>
      {
      protected:
        typedef double type;

        static _LIBCPP_CONSTEXPR bool is_specialized = true;

        static _LIBCPP_CONSTEXPR bool is_signed = true;
        static _LIBCPP_CONSTEXPR int digits = __DBL_MANT_DIG__;
        static _LIBCPP_CONSTEXPR int digits10 = __DBL_DIG__;
        static _LIBCPP_CONSTEXPR int max_digits10 = 2
            + (digits * 30103) / 100000;_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        min() _NOEXCEPT
        {
          return __DBL_MIN__;
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        max() _NOEXCEPT
        {
          return __DBL_MAX__;
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        lowest() _NOEXCEPT
        {
          return -max();
        }

        static _LIBCPP_CONSTEXPR bool is_integer = false;
        static _LIBCPP_CONSTEXPR bool is_exact = false;
        static _LIBCPP_CONSTEXPR int radix = __FLT_RADIX__;_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        epsilon() _NOEXCEPT
        {
          return __DBL_EPSILON__;
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        round_error() _NOEXCEPT
        {
          return 0.5;
        }

        static _LIBCPP_CONSTEXPR int min_exponent = __DBL_MIN_EXP__;
        static _LIBCPP_CONSTEXPR int min_exponent10 = __DBL_MIN_10_EXP__;
        static _LIBCPP_CONSTEXPR int max_exponent = __DBL_MAX_EXP__;
        static _LIBCPP_CONSTEXPR int max_exponent10 = __DBL_MAX_10_EXP__;

        static _LIBCPP_CONSTEXPR bool has_infinity = true;
        static _LIBCPP_CONSTEXPR bool has_quiet_NaN = true;
        static _LIBCPP_CONSTEXPR bool has_signaling_NaN = true;
        static _LIBCPP_CONSTEXPR float_denorm_style has_denorm = denorm_present;
        static _LIBCPP_CONSTEXPR bool has_denorm_loss = false;_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        infinity() _NOEXCEPT
        {
          return __builtin_huge_val();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        quiet_NaN() _NOEXCEPT
        {
          return __builtin_nan("");
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        signaling_NaN() _NOEXCEPT
        {
          return __builtin_nans("");
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        denorm_min() _NOEXCEPT
        {
          return __DBL_DENORM_MIN__;
        }

        static _LIBCPP_CONSTEXPR bool is_iec559 = true;
        static _LIBCPP_CONSTEXPR bool is_bounded = true;
        static _LIBCPP_CONSTEXPR bool is_modulo = false;

        static _LIBCPP_CONSTEXPR bool traps = false;
        static _LIBCPP_CONSTEXPR bool tinyness_before = false;
        static _LIBCPP_CONSTEXPR float_round_style round_style =
            round_to_nearest;
      };

    template<>
      class __libcpp_numeric_limits<long double, true>
      {
      protected:
        typedef long double type;

        static _LIBCPP_CONSTEXPR bool is_specialized = true;

        static _LIBCPP_CONSTEXPR bool is_signed = true;
        static _LIBCPP_CONSTEXPR int digits = __LDBL_MANT_DIG__;
        static _LIBCPP_CONSTEXPR int digits10 = __LDBL_DIG__;
        static _LIBCPP_CONSTEXPR int max_digits10 = 2
            + (digits * 30103) / 100000;_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        min() _NOEXCEPT
        {
          return __LDBL_MIN__;
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        max() _NOEXCEPT
        {
          return __LDBL_MAX__;
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        lowest() _NOEXCEPT
        {
          return -max();
        }

        static _LIBCPP_CONSTEXPR bool is_integer = false;
        static _LIBCPP_CONSTEXPR bool is_exact = false;
        static _LIBCPP_CONSTEXPR int radix = __FLT_RADIX__;_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        epsilon() _NOEXCEPT
        {
          return __LDBL_EPSILON__;
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        round_error() _NOEXCEPT
        {
          return 0.5;
        }

        static _LIBCPP_CONSTEXPR int min_exponent = __LDBL_MIN_EXP__;
        static _LIBCPP_CONSTEXPR int min_exponent10 = __LDBL_MIN_10_EXP__;
        static _LIBCPP_CONSTEXPR int max_exponent = __LDBL_MAX_EXP__;
        static _LIBCPP_CONSTEXPR int max_exponent10 = __LDBL_MAX_10_EXP__;

        static _LIBCPP_CONSTEXPR bool has_infinity = true;
        static _LIBCPP_CONSTEXPR bool has_quiet_NaN = true;
        static _LIBCPP_CONSTEXPR bool has_signaling_NaN = true;
        static _LIBCPP_CONSTEXPR float_denorm_style has_denorm = denorm_present;
        static _LIBCPP_CONSTEXPR bool has_denorm_loss = false;_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        infinity() _NOEXCEPT
        {
          return __builtin_huge_vall();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        quiet_NaN() _NOEXCEPT
        {
          return __builtin_nanl("");
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        signaling_NaN() _NOEXCEPT
        {
          return __builtin_nansl("");
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        denorm_min() _NOEXCEPT
        {
          return __LDBL_DENORM_MIN__;
        }

#if (defined(__ppc__) || defined(__ppc64__))
        static _LIBCPP_CONSTEXPR bool is_iec559 = false;
#else
        static _LIBCPP_CONSTEXPR bool is_iec559 = true;
#endif
        static _LIBCPP_CONSTEXPR bool is_bounded = true;
        static _LIBCPP_CONSTEXPR bool is_modulo = false;

        static _LIBCPP_CONSTEXPR bool traps = false;
        static _LIBCPP_CONSTEXPR bool tinyness_before = false;
        static _LIBCPP_CONSTEXPR float_round_style round_style =
            round_to_nearest;
      };

#endif

    template<class _Tp>
      class _LIBCPP_VISIBLE numeric_limits : private __libcpp_numeric_limits<
          typename remove_cv<_Tp>::type>
      {
        typedef __libcpp_numeric_limits <typename remove_cv<_Tp>::type> __base;
        typedef typename __base::type type;
      public:
        static _LIBCPP_CONSTEXPR bool is_specialized = __base::is_specialized;_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        min() _NOEXCEPT
        {
          return __base::min();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        max() _NOEXCEPT
        {
          return __base::max();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        lowest() _NOEXCEPT
        {
          return __base::lowest();
        }

        static _LIBCPP_CONSTEXPR int digits = __base::digits;
        static _LIBCPP_CONSTEXPR int digits10 = __base::digits10;
        static _LIBCPP_CONSTEXPR int max_digits10 = __base::max_digits10;
        static _LIBCPP_CONSTEXPR bool is_signed = __base::is_signed;
        static _LIBCPP_CONSTEXPR bool is_integer = __base::is_integer;
        static _LIBCPP_CONSTEXPR bool is_exact = __base::is_exact;
        static _LIBCPP_CONSTEXPR int radix = __base::radix;_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        epsilon() _NOEXCEPT
        {
          return __base::epsilon();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        round_error() _NOEXCEPT
        {
          return __base::round_error();
        }

        static _LIBCPP_CONSTEXPR int min_exponent = __base::min_exponent;
        static _LIBCPP_CONSTEXPR int min_exponent10 = __base::min_exponent10;
        static _LIBCPP_CONSTEXPR int max_exponent = __base::max_exponent;
        static _LIBCPP_CONSTEXPR int max_exponent10 = __base::max_exponent10;

        static _LIBCPP_CONSTEXPR bool has_infinity = __base::has_infinity;
        static _LIBCPP_CONSTEXPR bool has_quiet_NaN = __base::has_quiet_NaN;
        static _LIBCPP_CONSTEXPR bool has_signaling_NaN =
            __base::has_signaling_NaN;
        static _LIBCPP_CONSTEXPR float_denorm_style has_denorm =
            __base::has_denorm;
        static _LIBCPP_CONSTEXPR bool has_denorm_loss = __base::has_denorm_loss;_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        infinity() _NOEXCEPT
        {
          return __base::infinity();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        quiet_NaN() _NOEXCEPT
        {
          return __base::quiet_NaN();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        signaling_NaN() _NOEXCEPT
        {
          return __base::signaling_NaN();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        denorm_min() _NOEXCEPT
        {
          return __base::denorm_min();
        }

        static _LIBCPP_CONSTEXPR bool is_iec559 = __base::is_iec559;
        static _LIBCPP_CONSTEXPR bool is_bounded = __base::is_bounded;
        static _LIBCPP_CONSTEXPR bool is_modulo = __base::is_modulo;

        static _LIBCPP_CONSTEXPR bool traps = __base::traps;
        static _LIBCPP_CONSTEXPR bool tinyness_before = __base::tinyness_before;
        static _LIBCPP_CONSTEXPR float_round_style round_style =
            __base::round_style;
      };

    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<_Tp>::is_specialized;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<_Tp>::digits;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<_Tp>::digits10;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<_Tp>::max_digits10;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<_Tp>::is_signed;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<_Tp>::is_integer;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<_Tp>::is_exact;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<_Tp>::radix;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<_Tp>::min_exponent;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<_Tp>::min_exponent10;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<_Tp>::max_exponent;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<_Tp>::max_exponent10;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<_Tp>::has_infinity;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<_Tp>::has_quiet_NaN;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<_Tp>::has_signaling_NaN;
    template<class _Tp>
      _LIBCPP_CONSTEXPR float_denorm_style numeric_limits<_Tp>::has_denorm;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<_Tp>::has_denorm_loss;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<_Tp>::is_iec559;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<_Tp>::is_bounded;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<_Tp>::is_modulo;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<_Tp>::traps;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<_Tp>::tinyness_before;
    template<class _Tp>
      _LIBCPP_CONSTEXPR float_round_style numeric_limits<_Tp>::round_style;

    template<class _Tp>
      class _LIBCPP_VISIBLE numeric_limits<const _Tp> : private numeric_limits<
          _Tp>
      {
        typedef numeric_limits<_Tp> __base;
        typedef _Tp type;
      public:
        static _LIBCPP_CONSTEXPR bool is_specialized = __base::is_specialized;_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        min() _NOEXCEPT
        {
          return __base::min();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        max() _NOEXCEPT
        {
          return __base::max();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        lowest() _NOEXCEPT
        {
          return __base::lowest();
        }

        static _LIBCPP_CONSTEXPR int digits = __base::digits;
        static _LIBCPP_CONSTEXPR int digits10 = __base::digits10;
        static _LIBCPP_CONSTEXPR int max_digits10 = __base::max_digits10;
        static _LIBCPP_CONSTEXPR bool is_signed = __base::is_signed;
        static _LIBCPP_CONSTEXPR bool is_integer = __base::is_integer;
        static _LIBCPP_CONSTEXPR bool is_exact = __base::is_exact;
        static _LIBCPP_CONSTEXPR int radix = __base::radix;_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        epsilon() _NOEXCEPT
        {
          return __base::epsilon();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        round_error() _NOEXCEPT
        {
          return __base::round_error();
        }

        static _LIBCPP_CONSTEXPR int min_exponent = __base::min_exponent;
        static _LIBCPP_CONSTEXPR int min_exponent10 = __base::min_exponent10;
        static _LIBCPP_CONSTEXPR int max_exponent = __base::max_exponent;
        static _LIBCPP_CONSTEXPR int max_exponent10 = __base::max_exponent10;

        static _LIBCPP_CONSTEXPR bool has_infinity = __base::has_infinity;
        static _LIBCPP_CONSTEXPR bool has_quiet_NaN = __base::has_quiet_NaN;
        static _LIBCPP_CONSTEXPR bool has_signaling_NaN =
            __base::has_signaling_NaN;
        static _LIBCPP_CONSTEXPR float_denorm_style has_denorm =
            __base::has_denorm;
        static _LIBCPP_CONSTEXPR bool has_denorm_loss = __base::has_denorm_loss;_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        infinity() _NOEXCEPT
        {
          return __base::infinity();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        quiet_NaN() _NOEXCEPT
        {
          return __base::quiet_NaN();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        signaling_NaN() _NOEXCEPT
        {
          return __base::signaling_NaN();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        denorm_min() _NOEXCEPT
        {
          return __base::denorm_min();
        }

        static _LIBCPP_CONSTEXPR bool is_iec559 = __base::is_iec559;
        static _LIBCPP_CONSTEXPR bool is_bounded = __base::is_bounded;
        static _LIBCPP_CONSTEXPR bool is_modulo = __base::is_modulo;

        static _LIBCPP_CONSTEXPR bool traps = __base::traps;
        static _LIBCPP_CONSTEXPR bool tinyness_before = __base::tinyness_before;
        static _LIBCPP_CONSTEXPR float_round_style round_style =
            __base::round_style;
      };

    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<const _Tp>::is_specialized;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<const _Tp>::digits;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<const _Tp>::digits10;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<const _Tp>::max_digits10;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<const _Tp>::is_signed;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<const _Tp>::is_integer;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<const _Tp>::is_exact;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<const _Tp>::radix;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<const _Tp>::min_exponent;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<const _Tp>::min_exponent10;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<const _Tp>::max_exponent;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<const _Tp>::max_exponent10;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<const _Tp>::has_infinity;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<const _Tp>::has_quiet_NaN;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<const _Tp>::has_signaling_NaN;
    template<class _Tp>
      _LIBCPP_CONSTEXPR float_denorm_style numeric_limits<const _Tp>::has_denorm;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<const _Tp>::has_denorm_loss;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<const _Tp>::is_iec559;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<const _Tp>::is_bounded;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<const _Tp>::is_modulo;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<const _Tp>::traps;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<const _Tp>::tinyness_before;
    template<class _Tp>
      _LIBCPP_CONSTEXPR float_round_style numeric_limits<const _Tp>::round_style;

    template<class _Tp>
      class _LIBCPP_VISIBLE numeric_limits<volatile _Tp> : private numeric_limits<
          _Tp>
      {
        typedef numeric_limits<_Tp> __base;
        typedef _Tp type;
      public:
        static _LIBCPP_CONSTEXPR bool is_specialized = __base::is_specialized;_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        min() _NOEXCEPT
        {
          return __base::min();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        max() _NOEXCEPT
        {
          return __base::max();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        lowest() _NOEXCEPT
        {
          return __base::lowest();
        }

        static _LIBCPP_CONSTEXPR int digits = __base::digits;
        static _LIBCPP_CONSTEXPR int digits10 = __base::digits10;
        static _LIBCPP_CONSTEXPR int max_digits10 = __base::max_digits10;
        static _LIBCPP_CONSTEXPR bool is_signed = __base::is_signed;
        static _LIBCPP_CONSTEXPR bool is_integer = __base::is_integer;
        static _LIBCPP_CONSTEXPR bool is_exact = __base::is_exact;
        static _LIBCPP_CONSTEXPR int radix = __base::radix;_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        epsilon() _NOEXCEPT
        {
          return __base::epsilon();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        round_error() _NOEXCEPT
        {
          return __base::round_error();
        }

        static _LIBCPP_CONSTEXPR int min_exponent = __base::min_exponent;
        static _LIBCPP_CONSTEXPR int min_exponent10 = __base::min_exponent10;
        static _LIBCPP_CONSTEXPR int max_exponent = __base::max_exponent;
        static _LIBCPP_CONSTEXPR int max_exponent10 = __base::max_exponent10;

        static _LIBCPP_CONSTEXPR bool has_infinity = __base::has_infinity;
        static _LIBCPP_CONSTEXPR bool has_quiet_NaN = __base::has_quiet_NaN;
        static _LIBCPP_CONSTEXPR bool has_signaling_NaN =
            __base::has_signaling_NaN;
        static _LIBCPP_CONSTEXPR float_denorm_style has_denorm =
            __base::has_denorm;
        static _LIBCPP_CONSTEXPR bool has_denorm_loss = __base::has_denorm_loss;_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        infinity() _NOEXCEPT
        {
          return __base::infinity();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        quiet_NaN() _NOEXCEPT
        {
          return __base::quiet_NaN();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        signaling_NaN() _NOEXCEPT
        {
          return __base::signaling_NaN();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        denorm_min() _NOEXCEPT
        {
          return __base::denorm_min();
        }

        static _LIBCPP_CONSTEXPR bool is_iec559 = __base::is_iec559;
        static _LIBCPP_CONSTEXPR bool is_bounded = __base::is_bounded;
        static _LIBCPP_CONSTEXPR bool is_modulo = __base::is_modulo;

        static _LIBCPP_CONSTEXPR bool traps = __base::traps;
        static _LIBCPP_CONSTEXPR bool tinyness_before = __base::tinyness_before;
        static _LIBCPP_CONSTEXPR float_round_style round_style =
            __base::round_style;
      };

    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<volatile _Tp>::is_specialized;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<volatile _Tp>::digits;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<volatile _Tp>::digits10;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<volatile _Tp>::max_digits10;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<volatile _Tp>::is_signed;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<volatile _Tp>::is_integer;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<volatile _Tp>::is_exact;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<volatile _Tp>::radix;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<volatile _Tp>::min_exponent;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<volatile _Tp>::min_exponent10;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<volatile _Tp>::max_exponent;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<volatile _Tp>::max_exponent10;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<volatile _Tp>::has_infinity;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<volatile _Tp>::has_quiet_NaN;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<volatile _Tp>::has_signaling_NaN;
    template<class _Tp>
      _LIBCPP_CONSTEXPR float_denorm_style numeric_limits<volatile _Tp>::has_denorm;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<volatile _Tp>::has_denorm_loss;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<volatile _Tp>::is_iec559;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<volatile _Tp>::is_bounded;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<volatile _Tp>::is_modulo;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<volatile _Tp>::traps;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<volatile _Tp>::tinyness_before;
    template<class _Tp>
      _LIBCPP_CONSTEXPR float_round_style numeric_limits<volatile _Tp>::round_style;

    template<class _Tp>
      class _LIBCPP_VISIBLE numeric_limits<const volatile _Tp> : private numeric_limits<
          _Tp>
      {
        typedef numeric_limits<_Tp> __base;
        typedef _Tp type;
      public:
        static _LIBCPP_CONSTEXPR bool is_specialized = __base::is_specialized;_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        min() _NOEXCEPT
        {
          return __base::min();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        max() _NOEXCEPT
        {
          return __base::max();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        lowest() _NOEXCEPT
        {
          return __base::lowest();
        }

        static _LIBCPP_CONSTEXPR int digits = __base::digits;
        static _LIBCPP_CONSTEXPR int digits10 = __base::digits10;
        static _LIBCPP_CONSTEXPR int max_digits10 = __base::max_digits10;
        static _LIBCPP_CONSTEXPR bool is_signed = __base::is_signed;
        static _LIBCPP_CONSTEXPR bool is_integer = __base::is_integer;
        static _LIBCPP_CONSTEXPR bool is_exact = __base::is_exact;
        static _LIBCPP_CONSTEXPR int radix = __base::radix;_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        epsilon() _NOEXCEPT
        {
          return __base::epsilon();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        round_error() _NOEXCEPT
        {
          return __base::round_error();
        }

        static _LIBCPP_CONSTEXPR int min_exponent = __base::min_exponent;
        static _LIBCPP_CONSTEXPR int min_exponent10 = __base::min_exponent10;
        static _LIBCPP_CONSTEXPR int max_exponent = __base::max_exponent;
        static _LIBCPP_CONSTEXPR int max_exponent10 = __base::max_exponent10;

        static _LIBCPP_CONSTEXPR bool has_infinity = __base::has_infinity;
        static _LIBCPP_CONSTEXPR bool has_quiet_NaN = __base::has_quiet_NaN;
        static _LIBCPP_CONSTEXPR bool has_signaling_NaN =
            __base::has_signaling_NaN;
        static _LIBCPP_CONSTEXPR float_denorm_style has_denorm =
            __base::has_denorm;
        static _LIBCPP_CONSTEXPR bool has_denorm_loss = __base::has_denorm_loss;_LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        infinity() _NOEXCEPT
        {
          return __base::infinity();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        quiet_NaN() _NOEXCEPT
        {
          return __base::quiet_NaN();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        signaling_NaN() _NOEXCEPT
        {
          return __base::signaling_NaN();
        }
        _LIBCPP_INLINE_VISIBILITY static _LIBCPP_CONSTEXPR type
        denorm_min() _NOEXCEPT
        {
          return __base::denorm_min();
        }

        static _LIBCPP_CONSTEXPR bool is_iec559 = __base::is_iec559;
        static _LIBCPP_CONSTEXPR bool is_bounded = __base::is_bounded;
        static _LIBCPP_CONSTEXPR bool is_modulo = __base::is_modulo;

        static _LIBCPP_CONSTEXPR bool traps = __base::traps;
        static _LIBCPP_CONSTEXPR bool tinyness_before = __base::tinyness_before;
        static _LIBCPP_CONSTEXPR float_round_style round_style =
            __base::round_style;
      };

    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<const volatile _Tp>::is_specialized;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<const volatile _Tp>::digits;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<const volatile _Tp>::digits10;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<const volatile _Tp>::max_digits10;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<const volatile _Tp>::is_signed;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<const volatile _Tp>::is_integer;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<const volatile _Tp>::is_exact;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<const volatile _Tp>::radix;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<const volatile _Tp>::min_exponent;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<const volatile _Tp>::min_exponent10;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<const volatile _Tp>::max_exponent;
    template<class _Tp>
      _LIBCPP_CONSTEXPR int numeric_limits<const volatile _Tp>::max_exponent10;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<const volatile _Tp>::has_infinity;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<const volatile _Tp>::has_quiet_NaN;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<const volatile _Tp>::has_signaling_NaN;
    template<class _Tp>
      _LIBCPP_CONSTEXPR float_denorm_style numeric_limits<const volatile _Tp>::has_denorm;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<const volatile _Tp>::has_denorm_loss;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<const volatile _Tp>::is_iec559;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<const volatile _Tp>::is_bounded;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<const volatile _Tp>::is_modulo;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<const volatile _Tp>::traps;
    template<class _Tp>
      _LIBCPP_CONSTEXPR bool numeric_limits<const volatile _Tp>::tinyness_before;
    template<class _Tp>
      _LIBCPP_CONSTEXPR float_round_style numeric_limits<const volatile _Tp>::round_style;

  }
}

#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_LIMITS_H_
