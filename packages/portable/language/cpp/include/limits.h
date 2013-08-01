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
/// \brief Numeric limits.

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_LIMITS_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_LIMITS_H_

#include "portable/core/include/ConfigDefines.h"

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

        static constexpr bool is_specialized = false;
        __attribute__((always_inline)) static constexpr type
        min() noexcept
        {
          return type();
        }
        __attribute__((always_inline)) static constexpr type
        max() noexcept
        {
          return type();
        }
        __attribute__((always_inline)) static constexpr type
        lowest() noexcept
        {
          return type();
        }

        static constexpr int digits = 0;
        static constexpr int digits10 = 0;
        static constexpr int max_digits10 = 0;
        static constexpr bool is_signed = false;
        static constexpr bool is_integer = false;
        static constexpr bool is_exact = false;
        static constexpr int radix = 0;
        __attribute__((always_inline)) static constexpr type
        epsilon() noexcept
        {
          return type();
        }
        __attribute__((always_inline)) static constexpr type
        round_error() noexcept
        {
          return type();
        }

        static constexpr int min_exponent = 0;
        static constexpr int min_exponent10 = 0;
        static constexpr int max_exponent = 0;
        static constexpr int max_exponent10 = 0;

        static constexpr bool has_infinity = false;
        static constexpr bool has_quiet_NaN = false;
        static constexpr bool has_signaling_NaN = false;
        static constexpr float_denorm_style has_denorm = denorm_absent;
        static constexpr bool has_denorm_loss = false;
        __attribute__((always_inline)) static constexpr type
        infinity() noexcept
        {
          return type();
        }
        __attribute__((always_inline)) static constexpr type
        quiet_NaN() noexcept
        {
          return type();
        }
        __attribute__((always_inline)) static constexpr type
        signaling_NaN() noexcept
        {
          return type();
        }
        __attribute__((always_inline)) static constexpr type
        denorm_min() noexcept
        {
          return type();
        }

        static constexpr bool is_iec559 = false;
        static constexpr bool is_bounded = false;
        static constexpr bool is_modulo = false;

        static constexpr bool traps = false;
        static constexpr bool tinyness_before = false;
        static constexpr float_round_style round_style = round_toward_zero;
      };

    template<class _Tp, int digits, bool is_signed>
      struct __libcpp_compute_min
      {
#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wshift-sign-overflow"
#endif
        static constexpr _Tp value = _Tp(_Tp(1) << digits);
#pragma GCC diagnostic pop
      };

    template<class _Tp, int digits>
      struct __libcpp_compute_min<_Tp, digits, false>
      {
        static constexpr _Tp value = _Tp(0);
      };

    template<class _Tp>
      class __libcpp_numeric_limits<_Tp, true>
      {
      protected:
        typedef _Tp type;

        static constexpr bool is_specialized = true;

        static constexpr bool is_signed = type(-1) < type(0);
        static constexpr int digits = static_cast<int>(sizeof(type)
            * __CHAR_BIT__ - is_signed);
        static constexpr int digits10 = digits * 3 / 10;
        static constexpr int max_digits10 = 0;
        static constexpr type __min = __libcpp_compute_min<type, digits,
            is_signed>::value;
        static constexpr type __max =
            is_signed ? type(type(~0) ^ __min) : type(~0);
        __attribute__((always_inline)) static constexpr type
        min() noexcept
        {
          return __min;
        }
        __attribute__((always_inline)) static constexpr type
        max() noexcept
        {
          return __max;
        }
        __attribute__((always_inline)) static constexpr type
        lowest() noexcept
        {
          return min();
        }

        static constexpr bool is_integer = true;
        static constexpr bool is_exact = true;
        static constexpr int radix = 2;
        __attribute__((always_inline)) static constexpr type
        epsilon() noexcept
        {
          return type(0);
        }
        __attribute__((always_inline)) static constexpr type
        round_error() noexcept
        {
          return type(0);
        }

        static constexpr int min_exponent = 0;
        static constexpr int min_exponent10 = 0;
        static constexpr int max_exponent = 0;
        static constexpr int max_exponent10 = 0;

        static constexpr bool has_infinity = false;
        static constexpr bool has_quiet_NaN = false;
        static constexpr bool has_signaling_NaN = false;
        static constexpr float_denorm_style has_denorm = denorm_absent;
        static constexpr bool has_denorm_loss = false;
        __attribute__((always_inline)) static constexpr type
        infinity() noexcept
        {
          return type(0);
        }
        __attribute__((always_inline)) static constexpr type
        quiet_NaN() noexcept
        {
          return type(0);
        }
        __attribute__((always_inline)) static constexpr type
        signaling_NaN() noexcept
        {
          return type(0);
        }
        __attribute__((always_inline)) static constexpr type
        denorm_min() noexcept
        {
          return type(0);
        }

        static constexpr bool is_iec559 = false;
        static constexpr bool is_bounded = true;
        static constexpr bool is_modulo = true;

#if defined(__i386__) || defined(__x86_64__)
        static constexpr bool traps = true;
#else
        static constexpr bool traps = false;
#endif
        static constexpr bool tinyness_before = false;
        static constexpr float_round_style round_style = round_toward_zero;
      };

    template<>
      class __libcpp_numeric_limits<bool, true>
      {
      protected:
        typedef bool type;

        static constexpr bool is_specialized = true;

        static constexpr bool is_signed = false;
        static constexpr int digits = 1;
        static constexpr int digits10 = 0;
        static constexpr int max_digits10 = 0;
        static constexpr type __min = false;
        static constexpr type __max = true;
        __attribute__((always_inline)) static constexpr type
        min() noexcept
        {
          return __min;
        }
        __attribute__((always_inline)) static constexpr type
        max() noexcept
        {
          return __max;
        }
        __attribute__((always_inline)) static constexpr type
        lowest() noexcept
        {
          return min();
        }

        static constexpr bool is_integer = true;
        static constexpr bool is_exact = true;
        static constexpr int radix = 2;
        __attribute__((always_inline)) static constexpr type
        epsilon() noexcept
        {
          return type(0);
        }
        __attribute__((always_inline)) static constexpr type
        round_error() noexcept
        {
          return type(0);
        }

        static constexpr int min_exponent = 0;
        static constexpr int min_exponent10 = 0;
        static constexpr int max_exponent = 0;
        static constexpr int max_exponent10 = 0;

        static constexpr bool has_infinity = false;
        static constexpr bool has_quiet_NaN = false;
        static constexpr bool has_signaling_NaN = false;
        static constexpr float_denorm_style has_denorm = denorm_absent;
        static constexpr bool has_denorm_loss = false;
        __attribute__((always_inline)) static constexpr type
        infinity() noexcept
        {
          return type(0);
        }
        __attribute__((always_inline)) static constexpr type
        quiet_NaN() noexcept
        {
          return type(0);
        }
        __attribute__((always_inline)) static constexpr type
        signaling_NaN() noexcept
        {
          return type(0);
        }
        __attribute__((always_inline)) static constexpr type
        denorm_min() noexcept
        {
          return type(0);
        }

        static constexpr bool is_iec559 = false;
        static constexpr bool is_bounded = true;
        static constexpr bool is_modulo = false;

        static constexpr bool traps = false;
        static constexpr bool tinyness_before = false;
        static constexpr float_round_style round_style = round_toward_zero;
      };

    template<>
      class __libcpp_numeric_limits<float, true>
      {
      protected:
        typedef float type;

        static constexpr bool is_specialized = true;

        static constexpr bool is_signed = true;
        static constexpr int digits = __FLT_MANT_DIG__;
        static constexpr int digits10 = __FLT_DIG__;
        static constexpr int max_digits10 = 2 + (digits * 30103) / 100000;
        __attribute__((always_inline)) static constexpr type
        min() noexcept
        {
          return __FLT_MIN__;
        }
        __attribute__((always_inline)) static constexpr type
        max() noexcept
        {
          return __FLT_MAX__;
        }
        __attribute__((always_inline)) static constexpr type
        lowest() noexcept
        {
          return -max();
        }

        static constexpr bool is_integer = false;
        static constexpr bool is_exact = false;
        static constexpr int radix = __FLT_RADIX__;
        __attribute__((always_inline)) static constexpr type
        epsilon() noexcept
        {
          return __FLT_EPSILON__;
        }
        __attribute__((always_inline)) static constexpr type
        round_error() noexcept
        {
          return 0.5F;
        }

        static constexpr int min_exponent = __FLT_MIN_EXP__;
        static constexpr int min_exponent10 = __FLT_MIN_10_EXP__;
        static constexpr int max_exponent = __FLT_MAX_EXP__;
        static constexpr int max_exponent10 = __FLT_MAX_10_EXP__;

        static constexpr bool has_infinity = true;
        static constexpr bool has_quiet_NaN = true;
        static constexpr bool has_signaling_NaN = true;
        static constexpr float_denorm_style has_denorm = denorm_present;
        static constexpr bool has_denorm_loss = false;
        __attribute__((always_inline)) static constexpr type
        infinity() noexcept
        {
          return __builtin_huge_valf();
        }
        __attribute__((always_inline)) static constexpr type
        quiet_NaN() noexcept
        {
          return __builtin_nanf("");
        }
        __attribute__((always_inline)) static constexpr type
        signaling_NaN() noexcept
        {
          return __builtin_nansf("");
        }
        __attribute__((always_inline)) static constexpr type
        denorm_min() noexcept
        {
          return __FLT_DENORM_MIN__;
        }

        static constexpr bool is_iec559 = true;
        static constexpr bool is_bounded = true;
        static constexpr bool is_modulo = false;

        static constexpr bool traps = false;
        static constexpr bool tinyness_before = false;
        static constexpr float_round_style round_style = round_to_nearest;
      };

    template<>
      class __libcpp_numeric_limits<double, true>
      {
      protected:
        typedef double type;

        static constexpr bool is_specialized = true;

        static constexpr bool is_signed = true;
        static constexpr int digits = __DBL_MANT_DIG__;
        static constexpr int digits10 = __DBL_DIG__;
        static constexpr int max_digits10 = 2 + (digits * 30103) / 100000;
        __attribute__((always_inline)) static constexpr type
        min() noexcept
        {
          return __DBL_MIN__;
        }
        __attribute__((always_inline)) static constexpr type
        max() noexcept
        {
          return __DBL_MAX__;
        }
        __attribute__((always_inline)) static constexpr type
        lowest() noexcept
        {
          return -max();
        }

        static constexpr bool is_integer = false;
        static constexpr bool is_exact = false;
        static constexpr int radix = __FLT_RADIX__;
        __attribute__((always_inline)) static constexpr type
        epsilon() noexcept
        {
          return __DBL_EPSILON__;
        }
        __attribute__((always_inline)) static constexpr type
        round_error() noexcept
        {
          return 0.5;
        }

        static constexpr int min_exponent = __DBL_MIN_EXP__;
        static constexpr int min_exponent10 = __DBL_MIN_10_EXP__;
        static constexpr int max_exponent = __DBL_MAX_EXP__;
        static constexpr int max_exponent10 = __DBL_MAX_10_EXP__;

        static constexpr bool has_infinity = true;
        static constexpr bool has_quiet_NaN = true;
        static constexpr bool has_signaling_NaN = true;
        static constexpr float_denorm_style has_denorm = denorm_present;
        static constexpr bool has_denorm_loss = false;
        __attribute__((always_inline)) static constexpr type
        infinity() noexcept
        {
          return __builtin_huge_val();
        }
        __attribute__((always_inline)) static constexpr type
        quiet_NaN() noexcept
        {
          return __builtin_nan("");
        }
        __attribute__((always_inline)) static constexpr type
        signaling_NaN() noexcept
        {
          return __builtin_nans("");
        }
        __attribute__((always_inline)) static constexpr type
        denorm_min() noexcept
        {
          return __DBL_DENORM_MIN__;
        }

        static constexpr bool is_iec559 = true;
        static constexpr bool is_bounded = true;
        static constexpr bool is_modulo = false;

        static constexpr bool traps = false;
        static constexpr bool tinyness_before = false;
        static constexpr float_round_style round_style = round_to_nearest;
      };

    template<>
      class __libcpp_numeric_limits<long double, true>
      {
      protected:
        typedef long double type;

        static constexpr bool is_specialized = true;

        static constexpr bool is_signed = true;
        static constexpr int digits = __LDBL_MANT_DIG__;
        static constexpr int digits10 = __LDBL_DIG__;
        static constexpr int max_digits10 = 2 + (digits * 30103) / 100000;
        __attribute__((always_inline)) static constexpr type
        min() noexcept
        {
          return __LDBL_MIN__;
        }
        __attribute__((always_inline)) static constexpr type
        max() noexcept
        {
          return __LDBL_MAX__;
        }
        __attribute__((always_inline)) static constexpr type
        lowest() noexcept
        {
          return -max();
        }

        static constexpr bool is_integer = false;
        static constexpr bool is_exact = false;
        static constexpr int radix = __FLT_RADIX__;
        __attribute__((always_inline)) static constexpr type
        epsilon() noexcept
        {
          return __LDBL_EPSILON__;
        }
        __attribute__((always_inline)) static constexpr type
        round_error() noexcept
        {
          return 0.5;
        }

        static constexpr int min_exponent = __LDBL_MIN_EXP__;
        static constexpr int min_exponent10 = __LDBL_MIN_10_EXP__;
        static constexpr int max_exponent = __LDBL_MAX_EXP__;
        static constexpr int max_exponent10 = __LDBL_MAX_10_EXP__;

        static constexpr bool has_infinity = true;
        static constexpr bool has_quiet_NaN = true;
        static constexpr bool has_signaling_NaN = true;
        static constexpr float_denorm_style has_denorm = denorm_present;
        static constexpr bool has_denorm_loss = false;
        __attribute__((always_inline)) static constexpr type
        infinity() noexcept
        {
          return __builtin_huge_vall();
        }
        __attribute__((always_inline)) static constexpr type
        quiet_NaN() noexcept
        {
          return __builtin_nanl("");
        }
        __attribute__((always_inline)) static constexpr type
        signaling_NaN() noexcept
        {
          return __builtin_nansl("");
        }
        __attribute__((always_inline)) static constexpr type
        denorm_min() noexcept
        {
          return __LDBL_DENORM_MIN__;
        }

#if (defined(__ppc__) || defined(__ppc64__))
        static constexpr bool is_iec559 = false;
#else
        static constexpr bool is_iec559 = true;
#endif
        static constexpr bool is_bounded = true;
        static constexpr bool is_modulo = false;

        static constexpr bool traps = false;
        static constexpr bool tinyness_before = false;
        static constexpr float_round_style round_style = round_to_nearest;
      };

#endif

    template<class _Tp>
      class numeric_limits : private __libcpp_numeric_limits<
          typename remove_cv<_Tp>::type>
      {
        typedef __libcpp_numeric_limits <typename remove_cv<_Tp>::type> __base;
        typedef typename __base::type type;
      public:
        static constexpr bool is_specialized = __base::is_specialized;
        __attribute__((always_inline)) static constexpr type
        min() noexcept
        {
          return __base::min();
        }
        __attribute__((always_inline)) static constexpr type
        max() noexcept
        {
          return __base::max();
        }
        __attribute__((always_inline)) static constexpr type
        lowest() noexcept
        {
          return __base::lowest();
        }

        static constexpr int digits = __base::digits;
        static constexpr int digits10 = __base::digits10;
        static constexpr int max_digits10 = __base::max_digits10;
        static constexpr bool is_signed = __base::is_signed;
        static constexpr bool is_integer = __base::is_integer;
        static constexpr bool is_exact = __base::is_exact;
        static constexpr int radix = __base::radix;
        __attribute__((always_inline)) static constexpr type
        epsilon() noexcept
        {
          return __base::epsilon();
        }
        __attribute__((always_inline)) static constexpr type
        round_error() noexcept
        {
          return __base::round_error();
        }

        static constexpr int min_exponent = __base::min_exponent;
        static constexpr int min_exponent10 = __base::min_exponent10;
        static constexpr int max_exponent = __base::max_exponent;
        static constexpr int max_exponent10 = __base::max_exponent10;

        static constexpr bool has_infinity = __base::has_infinity;
        static constexpr bool has_quiet_NaN = __base::has_quiet_NaN;
        static constexpr bool has_signaling_NaN = __base::has_signaling_NaN;
        static constexpr float_denorm_style has_denorm = __base::has_denorm;
        static constexpr bool has_denorm_loss = __base::has_denorm_loss;
        __attribute__((always_inline)) static constexpr type
        infinity() noexcept
        {
          return __base::infinity();
        }
        __attribute__((always_inline)) static constexpr type
        quiet_NaN() noexcept
        {
          return __base::quiet_NaN();
        }
        __attribute__((always_inline)) static constexpr type
        signaling_NaN() noexcept
        {
          return __base::signaling_NaN();
        }
        __attribute__((always_inline)) static constexpr type
        denorm_min() noexcept
        {
          return __base::denorm_min();
        }

        static constexpr bool is_iec559 = __base::is_iec559;
        static constexpr bool is_bounded = __base::is_bounded;
        static constexpr bool is_modulo = __base::is_modulo;

        static constexpr bool traps = __base::traps;
        static constexpr bool tinyness_before = __base::tinyness_before;
        static constexpr float_round_style round_style = __base::round_style;
      };

    template<class _Tp>
      constexpr bool numeric_limits<_Tp>::is_specialized;
    template<class _Tp>
      constexpr int numeric_limits<_Tp>::digits;
    template<class _Tp>
      constexpr int numeric_limits<_Tp>::digits10;
    template<class _Tp>
      constexpr int numeric_limits<_Tp>::max_digits10;
    template<class _Tp>
      constexpr bool numeric_limits<_Tp>::is_signed;
    template<class _Tp>
      constexpr bool numeric_limits<_Tp>::is_integer;
    template<class _Tp>
      constexpr bool numeric_limits<_Tp>::is_exact;
    template<class _Tp>
      constexpr int numeric_limits<_Tp>::radix;
    template<class _Tp>
      constexpr int numeric_limits<_Tp>::min_exponent;
    template<class _Tp>
      constexpr int numeric_limits<_Tp>::min_exponent10;
    template<class _Tp>
      constexpr int numeric_limits<_Tp>::max_exponent;
    template<class _Tp>
      constexpr int numeric_limits<_Tp>::max_exponent10;
    template<class _Tp>
      constexpr bool numeric_limits<_Tp>::has_infinity;
    template<class _Tp>
      constexpr bool numeric_limits<_Tp>::has_quiet_NaN;
    template<class _Tp>
      constexpr bool numeric_limits<_Tp>::has_signaling_NaN;
    template<class _Tp>
      constexpr float_denorm_style numeric_limits<_Tp>::has_denorm;
    template<class _Tp>
      constexpr bool numeric_limits<_Tp>::has_denorm_loss;
    template<class _Tp>
      constexpr bool numeric_limits<_Tp>::is_iec559;
    template<class _Tp>
      constexpr bool numeric_limits<_Tp>::is_bounded;
    template<class _Tp>
      constexpr bool numeric_limits<_Tp>::is_modulo;
    template<class _Tp>
      constexpr bool numeric_limits<_Tp>::traps;
    template<class _Tp>
      constexpr bool numeric_limits<_Tp>::tinyness_before;
    template<class _Tp>
      constexpr float_round_style numeric_limits<_Tp>::round_style;

    template<class _Tp>
      class numeric_limits<const _Tp> : private numeric_limits<_Tp>
      {
        typedef numeric_limits<_Tp> __base;
        typedef _Tp type;
      public:
        static constexpr bool is_specialized = __base::is_specialized;
        __attribute__((always_inline)) static constexpr type
        min() noexcept
        {
          return __base::min();
        }
        __attribute__((always_inline)) static constexpr type
        max() noexcept
        {
          return __base::max();
        }
        __attribute__((always_inline)) static constexpr type
        lowest() noexcept
        {
          return __base::lowest();
        }

        static constexpr int digits = __base::digits;
        static constexpr int digits10 = __base::digits10;
        static constexpr int max_digits10 = __base::max_digits10;
        static constexpr bool is_signed = __base::is_signed;
        static constexpr bool is_integer = __base::is_integer;
        static constexpr bool is_exact = __base::is_exact;
        static constexpr int radix = __base::radix;
        __attribute__((always_inline)) static constexpr type
        epsilon() noexcept
        {
          return __base::epsilon();
        }
        __attribute__((always_inline)) static constexpr type
        round_error() noexcept
        {
          return __base::round_error();
        }

        static constexpr int min_exponent = __base::min_exponent;
        static constexpr int min_exponent10 = __base::min_exponent10;
        static constexpr int max_exponent = __base::max_exponent;
        static constexpr int max_exponent10 = __base::max_exponent10;

        static constexpr bool has_infinity = __base::has_infinity;
        static constexpr bool has_quiet_NaN = __base::has_quiet_NaN;
        static constexpr bool has_signaling_NaN = __base::has_signaling_NaN;
        static constexpr float_denorm_style has_denorm = __base::has_denorm;
        static constexpr bool has_denorm_loss = __base::has_denorm_loss;
        __attribute__((always_inline)) static constexpr type
        infinity() noexcept
        {
          return __base::infinity();
        }
        __attribute__((always_inline)) static constexpr type
        quiet_NaN() noexcept
        {
          return __base::quiet_NaN();
        }
        __attribute__((always_inline)) static constexpr type
        signaling_NaN() noexcept
        {
          return __base::signaling_NaN();
        }
        __attribute__((always_inline)) static constexpr type
        denorm_min() noexcept
        {
          return __base::denorm_min();
        }

        static constexpr bool is_iec559 = __base::is_iec559;
        static constexpr bool is_bounded = __base::is_bounded;
        static constexpr bool is_modulo = __base::is_modulo;

        static constexpr bool traps = __base::traps;
        static constexpr bool tinyness_before = __base::tinyness_before;
        static constexpr float_round_style round_style = __base::round_style;
      };

    template<class _Tp>
      constexpr bool numeric_limits<const _Tp>::is_specialized;
    template<class _Tp>
      constexpr int numeric_limits<const _Tp>::digits;
    template<class _Tp>
      constexpr int numeric_limits<const _Tp>::digits10;
    template<class _Tp>
      constexpr int numeric_limits<const _Tp>::max_digits10;
    template<class _Tp>
      constexpr bool numeric_limits<const _Tp>::is_signed;
    template<class _Tp>
      constexpr bool numeric_limits<const _Tp>::is_integer;
    template<class _Tp>
      constexpr bool numeric_limits<const _Tp>::is_exact;
    template<class _Tp>
      constexpr int numeric_limits<const _Tp>::radix;
    template<class _Tp>
      constexpr int numeric_limits<const _Tp>::min_exponent;
    template<class _Tp>
      constexpr int numeric_limits<const _Tp>::min_exponent10;
    template<class _Tp>
      constexpr int numeric_limits<const _Tp>::max_exponent;
    template<class _Tp>
      constexpr int numeric_limits<const _Tp>::max_exponent10;
    template<class _Tp>
      constexpr bool numeric_limits<const _Tp>::has_infinity;
    template<class _Tp>
      constexpr bool numeric_limits<const _Tp>::has_quiet_NaN;
    template<class _Tp>
      constexpr bool numeric_limits<const _Tp>::has_signaling_NaN;
    template<class _Tp>
      constexpr float_denorm_style numeric_limits<const _Tp>::has_denorm;
    template<class _Tp>
      constexpr bool numeric_limits<const _Tp>::has_denorm_loss;
    template<class _Tp>
      constexpr bool numeric_limits<const _Tp>::is_iec559;
    template<class _Tp>
      constexpr bool numeric_limits<const _Tp>::is_bounded;
    template<class _Tp>
      constexpr bool numeric_limits<const _Tp>::is_modulo;
    template<class _Tp>
      constexpr bool numeric_limits<const _Tp>::traps;
    template<class _Tp>
      constexpr bool numeric_limits<const _Tp>::tinyness_before;
    template<class _Tp>
      constexpr float_round_style numeric_limits<const _Tp>::round_style;

    template<class _Tp>
      class numeric_limits<volatile _Tp> : private numeric_limits<_Tp>
      {
        typedef numeric_limits<_Tp> __base;
        typedef _Tp type;
      public:
        static constexpr bool is_specialized = __base::is_specialized;
        __attribute__((always_inline)) static constexpr type
        min() noexcept
        {
          return __base::min();
        }
        __attribute__((always_inline)) static constexpr type
        max() noexcept
        {
          return __base::max();
        }
        __attribute__((always_inline)) static constexpr type
        lowest() noexcept
        {
          return __base::lowest();
        }

        static constexpr int digits = __base::digits;
        static constexpr int digits10 = __base::digits10;
        static constexpr int max_digits10 = __base::max_digits10;
        static constexpr bool is_signed = __base::is_signed;
        static constexpr bool is_integer = __base::is_integer;
        static constexpr bool is_exact = __base::is_exact;
        static constexpr int radix = __base::radix;
        __attribute__((always_inline)) static constexpr type
        epsilon() noexcept
        {
          return __base::epsilon();
        }
        __attribute__((always_inline)) static constexpr type
        round_error() noexcept
        {
          return __base::round_error();
        }

        static constexpr int min_exponent = __base::min_exponent;
        static constexpr int min_exponent10 = __base::min_exponent10;
        static constexpr int max_exponent = __base::max_exponent;
        static constexpr int max_exponent10 = __base::max_exponent10;

        static constexpr bool has_infinity = __base::has_infinity;
        static constexpr bool has_quiet_NaN = __base::has_quiet_NaN;
        static constexpr bool has_signaling_NaN = __base::has_signaling_NaN;
        static constexpr float_denorm_style has_denorm = __base::has_denorm;
        static constexpr bool has_denorm_loss = __base::has_denorm_loss;
        __attribute__((always_inline)) static constexpr type
        infinity() noexcept
        {
          return __base::infinity();
        }
        __attribute__((always_inline)) static constexpr type
        quiet_NaN() noexcept
        {
          return __base::quiet_NaN();
        }
        __attribute__((always_inline)) static constexpr type
        signaling_NaN() noexcept
        {
          return __base::signaling_NaN();
        }
        __attribute__((always_inline)) static constexpr type
        denorm_min() noexcept
        {
          return __base::denorm_min();
        }

        static constexpr bool is_iec559 = __base::is_iec559;
        static constexpr bool is_bounded = __base::is_bounded;
        static constexpr bool is_modulo = __base::is_modulo;

        static constexpr bool traps = __base::traps;
        static constexpr bool tinyness_before = __base::tinyness_before;
        static constexpr float_round_style round_style = __base::round_style;
      };

    template<class _Tp>
      constexpr bool numeric_limits<volatile _Tp>::is_specialized;
    template<class _Tp>
      constexpr int numeric_limits<volatile _Tp>::digits;
    template<class _Tp>
      constexpr int numeric_limits<volatile _Tp>::digits10;
    template<class _Tp>
      constexpr int numeric_limits<volatile _Tp>::max_digits10;
    template<class _Tp>
      constexpr bool numeric_limits<volatile _Tp>::is_signed;
    template<class _Tp>
      constexpr bool numeric_limits<volatile _Tp>::is_integer;
    template<class _Tp>
      constexpr bool numeric_limits<volatile _Tp>::is_exact;
    template<class _Tp>
      constexpr int numeric_limits<volatile _Tp>::radix;
    template<class _Tp>
      constexpr int numeric_limits<volatile _Tp>::min_exponent;
    template<class _Tp>
      constexpr int numeric_limits<volatile _Tp>::min_exponent10;
    template<class _Tp>
      constexpr int numeric_limits<volatile _Tp>::max_exponent;
    template<class _Tp>
      constexpr int numeric_limits<volatile _Tp>::max_exponent10;
    template<class _Tp>
      constexpr bool numeric_limits<volatile _Tp>::has_infinity;
    template<class _Tp>
      constexpr bool numeric_limits<volatile _Tp>::has_quiet_NaN;
    template<class _Tp>
      constexpr bool numeric_limits<volatile _Tp>::has_signaling_NaN;
    template<class _Tp>
      constexpr float_denorm_style numeric_limits<volatile _Tp>::has_denorm;
    template<class _Tp>
      constexpr bool numeric_limits<volatile _Tp>::has_denorm_loss;
    template<class _Tp>
      constexpr bool numeric_limits<volatile _Tp>::is_iec559;
    template<class _Tp>
      constexpr bool numeric_limits<volatile _Tp>::is_bounded;
    template<class _Tp>
      constexpr bool numeric_limits<volatile _Tp>::is_modulo;
    template<class _Tp>
      constexpr bool numeric_limits<volatile _Tp>::traps;
    template<class _Tp>
      constexpr bool numeric_limits<volatile _Tp>::tinyness_before;
    template<class _Tp>
      constexpr float_round_style numeric_limits<volatile _Tp>::round_style;

    template<class _Tp>
      class numeric_limits<const volatile _Tp> : private numeric_limits<_Tp>
      {
        typedef numeric_limits<_Tp> __base;
        typedef _Tp type;
      public:
        static constexpr bool is_specialized = __base::is_specialized;
        __attribute__((always_inline)) static constexpr type
        min() noexcept
        {
          return __base::min();
        }
        __attribute__((always_inline)) static constexpr type
        max() noexcept
        {
          return __base::max();
        }
        __attribute__((always_inline)) static constexpr type
        lowest() noexcept
        {
          return __base::lowest();
        }

        static constexpr int digits = __base::digits;
        static constexpr int digits10 = __base::digits10;
        static constexpr int max_digits10 = __base::max_digits10;
        static constexpr bool is_signed = __base::is_signed;
        static constexpr bool is_integer = __base::is_integer;
        static constexpr bool is_exact = __base::is_exact;
        static constexpr int radix = __base::radix;
        __attribute__((always_inline)) static constexpr type
        epsilon() noexcept
        {
          return __base::epsilon();
        }
        __attribute__((always_inline)) static constexpr type
        round_error() noexcept
        {
          return __base::round_error();
        }

        static constexpr int min_exponent = __base::min_exponent;
        static constexpr int min_exponent10 = __base::min_exponent10;
        static constexpr int max_exponent = __base::max_exponent;
        static constexpr int max_exponent10 = __base::max_exponent10;

        static constexpr bool has_infinity = __base::has_infinity;
        static constexpr bool has_quiet_NaN = __base::has_quiet_NaN;
        static constexpr bool has_signaling_NaN = __base::has_signaling_NaN;
        static constexpr float_denorm_style has_denorm = __base::has_denorm;
        static constexpr bool has_denorm_loss = __base::has_denorm_loss;
        __attribute__((always_inline)) static constexpr type
        infinity() noexcept
        {
          return __base::infinity();
        }
        __attribute__((always_inline)) static constexpr type
        quiet_NaN() noexcept
        {
          return __base::quiet_NaN();
        }
        __attribute__((always_inline)) static constexpr type
        signaling_NaN() noexcept
        {
          return __base::signaling_NaN();
        }
        __attribute__((always_inline)) static constexpr type
        denorm_min() noexcept
        {
          return __base::denorm_min();
        }

        static constexpr bool is_iec559 = __base::is_iec559;
        static constexpr bool is_bounded = __base::is_bounded;
        static constexpr bool is_modulo = __base::is_modulo;

        static constexpr bool traps = __base::traps;
        static constexpr bool tinyness_before = __base::tinyness_before;
        static constexpr float_round_style round_style = __base::round_style;
      };

    template<class _Tp>
      constexpr bool numeric_limits<const volatile _Tp>::is_specialized;
    template<class _Tp>
      constexpr int numeric_limits<const volatile _Tp>::digits;
    template<class _Tp>
      constexpr int numeric_limits<const volatile _Tp>::digits10;
    template<class _Tp>
      constexpr int numeric_limits<const volatile _Tp>::max_digits10;
    template<class _Tp>
      constexpr bool numeric_limits<const volatile _Tp>::is_signed;
    template<class _Tp>
      constexpr bool numeric_limits<const volatile _Tp>::is_integer;
    template<class _Tp>
      constexpr bool numeric_limits<const volatile _Tp>::is_exact;
    template<class _Tp>
      constexpr int numeric_limits<const volatile _Tp>::radix;
    template<class _Tp>
      constexpr int numeric_limits<const volatile _Tp>::min_exponent;
    template<class _Tp>
      constexpr int numeric_limits<const volatile _Tp>::min_exponent10;
    template<class _Tp>
      constexpr int numeric_limits<const volatile _Tp>::max_exponent;
    template<class _Tp>
      constexpr int numeric_limits<const volatile _Tp>::max_exponent10;
    template<class _Tp>
      constexpr bool numeric_limits<const volatile _Tp>::has_infinity;
    template<class _Tp>
      constexpr bool numeric_limits<const volatile _Tp>::has_quiet_NaN;
    template<class _Tp>
      constexpr bool numeric_limits<const volatile _Tp>::has_signaling_NaN;
    template<class _Tp>
      constexpr float_denorm_style numeric_limits<const volatile _Tp>::has_denorm;
    template<class _Tp>
      constexpr bool numeric_limits<const volatile _Tp>::has_denorm_loss;
    template<class _Tp>
      constexpr bool numeric_limits<const volatile _Tp>::is_iec559;
    template<class _Tp>
      constexpr bool numeric_limits<const volatile _Tp>::is_bounded;
    template<class _Tp>
      constexpr bool numeric_limits<const volatile _Tp>::is_modulo;
    template<class _Tp>
      constexpr bool numeric_limits<const volatile _Tp>::traps;
    template<class _Tp>
      constexpr bool numeric_limits<const volatile _Tp>::tinyness_before;
    template<class _Tp>
      constexpr float_round_style numeric_limits<const volatile _Tp>::round_style;

  }
}

#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_LIMITS_H_
