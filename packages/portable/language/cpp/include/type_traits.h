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
/// \brief Type traits.

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_TYPE_TRAITS_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_TYPE_TRAITS_H_

#include "portable/core/include/ConfigDefines.h"

#include "portable/language/cpp/include/internal/__config.h"
#include "portable/language/cpp/include/cstddef.h"

namespace os
{
  namespace std
  {

#if !defined(__DOXYGEN__)
    template<bool _Bp, class _If, class _Then>
      struct _LIBCPP_VISIBLE conditional
      {
        typedef _If type;
      };

    template<class _If, class _Then>
      struct _LIBCPP_VISIBLE conditional<false, _If, _Then>
      {
        typedef _Then type;
      };

    template<bool, class _Tp = void>
      struct _LIBCPP_VISIBLE enable_if
      {

      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE enable_if<true, _Tp>
      {
        typedef _Tp type;
      };

#if !defined(__DOXYGEN__)
    struct __two
    {
      char __lx[2];
    };
#endif

    // helper class:

    template<class _Tp, _Tp __v>
      struct _LIBCPP_VISIBLE integral_constant
      {
        static _LIBCPP_CONSTEXPR _Tp value = __v;
        typedef _Tp value_type;
        typedef integral_constant type;_LIBCPP_INLINE_VISIBILITY
        _LIBCPP_CONSTEXPR
        operator value_type() const
        {
          return value;
        }
      };

    template<class _Tp, _Tp __v>
      _LIBCPP_CONSTEXPR _Tp integral_constant<_Tp, __v>::value;

    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;

    // is_const

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_const : public false_type
      {

      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_const<_Tp const> : public true_type
      {

      };

    // is_volatile

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_volatile : public false_type
      {

      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_volatile<_Tp volatile> : public true_type
      {

      };

    // remove_const

    template<class _Tp>
      struct _LIBCPP_VISIBLE remove_const
      {
        typedef _Tp type;
      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE remove_const<const _Tp>
      {
        typedef _Tp type;
      };

    // remove_volatile

    template<class _Tp>
      struct _LIBCPP_VISIBLE remove_volatile
      {
        typedef _Tp type;
      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE remove_volatile<volatile _Tp>
      {
        typedef _Tp type;
      };

    // remove_cv

    template<class _Tp>
      struct _LIBCPP_VISIBLE remove_cv
      {
        typedef typename remove_volatile<typename remove_const<_Tp>::type>::type type;
      };

    // is_void

    template<class _Tp>
      struct __is_void : public false_type
      {

      };

    template<>
      struct __is_void<void> : public true_type
      {
      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_void : public __is_void<
          typename remove_cv<_Tp>::type>
      {

      };

    // __is_nullptr_t

    template<class _Tp>
      struct ____is_nullptr_t : public false_type
      {

      };

    template<>
      struct ____is_nullptr_t<nullptr_t> : public true_type
      {

      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE __is_nullptr_t : public ____is_nullptr_t<
          typename remove_cv<_Tp>::type>
      {

      };

    // is_integral

    template<class _Tp>
      struct __is_integral : public false_type
      {

      };

    template<>
      struct __is_integral<bool> : public true_type
      {

      };

    template<>
      struct __is_integral<char> : public true_type
      {

      };

    template<>
      struct __is_integral<signed char> : public true_type
      {

      };

    template<>
      struct __is_integral<unsigned char> : public true_type
      {

      };

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

    template <> struct __is_integral<wchar_t> : public true_type
      {};

#endif

#ifndef _LIBCPP_HAS_NO_UNICODE_CHARS
    template<>
      struct __is_integral<char16_t> : public true_type
      {

      };

    template<>
      struct __is_integral<char32_t> : public true_type
      {

      };

#endif  // _LIBCPP_HAS_NO_UNICODE_CHARS
    template<>
      struct __is_integral<short> : public true_type
      {

      };

    template<>
      struct __is_integral<unsigned short> : public true_type
      {

      };

    template<>
      struct __is_integral<int> : public true_type
      {

      };

    template<>
      struct __is_integral<unsigned int> : public true_type
      {

      };

    template<>
      struct __is_integral<long> : public true_type
      {

      };

    template<>
      struct __is_integral<unsigned long> : public true_type
      {

      };

    template<>
      struct __is_integral<long long> : public true_type
      {

      };

    template<>
      struct __is_integral<unsigned long long> : public true_type
      {

      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_integral : public __is_integral<
          typename remove_cv<_Tp>::type>
      {

      };

    // is_floating_point

    template<class _Tp>
      struct __is_floating_point : public false_type
      {

      };

    template<>
      struct __is_floating_point<float> : public true_type
      {

      };

    template<>
      struct __is_floating_point<double> : public true_type
      {

      };

    template<>
      struct __is_floating_point<long double> : public true_type
      {

      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_floating_point : public __is_floating_point<
          typename remove_cv<_Tp>::type>
      {

      };

    // is_array

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_array : public false_type
      {
      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_array<_Tp[]> : public true_type
      {
      };

    template<class _Tp, size_t _Np>
      struct _LIBCPP_VISIBLE is_array<_Tp[_Np]> : public true_type
      {
      };

    // is_pointer

    template<class _Tp>
      struct __is_pointer : public false_type
      {
      };

    template<class _Tp>
      struct __is_pointer<_Tp*> : public true_type
      {
      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_pointer : public __is_pointer<
          typename remove_cv<_Tp>::type>
      {
      };

    // is_reference

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_lvalue_reference : public false_type
      {
      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_lvalue_reference<_Tp&> : public true_type
      {
      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_rvalue_reference : public false_type
      {
      };

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
    template<class _Tp>
    struct _LIBCPP_VISIBLE is_rvalue_reference<_Tp&&> : public true_type
      {};
#endif

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_reference : public false_type
      {
      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_reference<_Tp&> : public true_type
      {
      };

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
    template<class _Tp>
    struct _LIBCPP_VISIBLE is_reference<_Tp&&> : public true_type
      {};
#endif

#if defined(__clang__) || (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)
#define _LIBCPP_HAS_TYPE_TRAITS
#endif

    // is_union

#if __has_feature(is_union) || (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)

    template <class _Tp> struct _LIBCPP_VISIBLE is_union
    : public integral_constant<bool, __is_union(_Tp)>
      {};

#else

template    <class _Tp>
    struct __libcpp_union : public false_type
      {
      };
    template<class _Tp>
      struct _LIBCPP_VISIBLE is_union : public __libcpp_union<
          typename remove_cv<_Tp>::type>
      {
      };

#endif

    // is_class

#if __has_feature(is_class) || (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)

    template <class _Tp> struct _LIBCPP_VISIBLE is_class
    : public integral_constant<bool, __is_class(_Tp)>
      {};

#else

#if !defined(__DOXYGEN__)
namespace    __is_class_imp
      {
        template <class _Tp> char __test(int _Tp::*);
        template <class _Tp> __two __test(...);
      }
#endif

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_class : public integral_constant<bool,
          sizeof(__is_class_imp::__test<_Tp>(0)) == 1 && !is_union<_Tp>::value>
      {
      };

#endif

    // is_same

    template<class _Tp, class _Up>
      struct _LIBCPP_VISIBLE is_same : public false_type
      {
      };
    template<class _Tp>
      struct _LIBCPP_VISIBLE is_same<_Tp, _Tp> : public true_type
      {
      };

    // is_function

#if !defined(__DOXYGEN__)

    namespace __is_function_imp
    {
      template<class _Tp>
        char
        __test(_Tp*);
      template<class _Tp>
        __two                 __test(...);
template<      class _Tp> _Tp& __source();}

#endif

    template<class _Tp, bool = is_class<_Tp>::value || is_union<_Tp>::value
        || is_void<_Tp>::value || is_reference<_Tp>::value
        || is_same<_Tp, nullptr_t>::value>
      struct __is_function : public integral_constant<bool,
          sizeof(__is_function_imp::__test<_Tp>(
              __is_function_imp::__source<_Tp>())) == 1>
      {
      };
    template<class _Tp>
      struct __is_function<_Tp, true> : public false_type
      {
      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_function : public __is_function<_Tp>
      {
      };

    // is_member_function_pointer

    template<class _Tp>
      struct __is_member_function_pointer : public false_type
      {
      };
    template<class _Tp, class _Up>
      struct __is_member_function_pointer<_Tp _Up::*> : public is_function<_Tp>
      {
      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_member_function_pointer : public __is_member_function_pointer<
          typename remove_cv<_Tp>::type>
      {
      };

    // is_member_pointer

    template<class _Tp>
      struct __is_member_pointer : public false_type
      {
      };
    template<class _Tp, class _Up>
      struct __is_member_pointer<_Tp _Up::*> : public true_type
      {
      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_member_pointer : public __is_member_pointer<
          typename remove_cv<_Tp>::type>
      {
      };

    // is_member_object_pointer

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_member_object_pointer : public integral_constant<
          bool,
          is_member_pointer<_Tp>::value
              && !is_member_function_pointer<_Tp>::value>
      {
      };

    // is_enum

#if __has_feature(is_enum) || (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)

    template <class _Tp> struct _LIBCPP_VISIBLE is_enum
    : public integral_constant<bool, __is_enum(_Tp)>
      {};

#else

template    <class _Tp> struct _LIBCPP_VISIBLE is_enum
    : public integral_constant<bool, !is_void<_Tp>::value &&
    !is_integral<_Tp>::value &&
    !is_floating_point<_Tp>::value &&
    !is_array<_Tp>::value &&
    !is_pointer<_Tp>::value &&
    !is_reference<_Tp>::value &&
    !is_member_pointer<_Tp>::value &&
    !is_union<_Tp>::value &&
    !is_class<_Tp>::value &&
    !is_function<_Tp>::value >
      {};

#endif

    // is_arithmetic

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_arithmetic : public integral_constant<bool,
          is_integral<_Tp>::value || is_floating_point<_Tp>::value>
      {
      };

    // is_fundamental

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_fundamental : public integral_constant<bool,
          is_void<_Tp>::value || __is_nullptr_t<_Tp>::value
              || is_arithmetic<_Tp>::value>
      {
      };

    // is_scalar

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_scalar : public integral_constant<bool,
          is_arithmetic<_Tp>::value || is_member_pointer<_Tp>::value
              || is_pointer<_Tp>::value || __is_nullptr_t<_Tp>::value
              || is_enum<_Tp>::value>
      {
      };

    template<>
      struct _LIBCPP_VISIBLE is_scalar<nullptr_t> : public true_type
      {
      };

    // is_object

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_object : public integral_constant<bool,
          is_scalar<_Tp>::value || is_array<_Tp>::value || is_union<_Tp>::value
              || is_class<_Tp>::value>
      {
      };

    // is_compound

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_compound : public integral_constant<bool,
          !is_fundamental<_Tp>::value>
      {
      };

    // add_const

    template<class _Tp, bool = is_reference<_Tp>::value
        || is_function<_Tp>::value || is_const<_Tp>::value>
      struct __add_const
      {
        typedef _Tp type;
      };

    template<class _Tp>
      struct __add_const<_Tp, false>
      {
        typedef const _Tp type;
      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE add_const
      {
        typedef typename __add_const<_Tp>::type type;
      };

    // add_volatile

    template<class _Tp, bool = is_reference<_Tp>::value
        || is_function<_Tp>::value || is_volatile<_Tp>::value>
      struct __add_volatile
      {
        typedef _Tp type;
      };

    template<class _Tp>
      struct __add_volatile<_Tp, false>
      {
        typedef volatile _Tp type;
      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE add_volatile
      {
        typedef typename __add_volatile<_Tp>::type type;
      };

    // add_cv

    template<class _Tp>
      struct _LIBCPP_VISIBLE add_cv
      {
        typedef typename add_const<typename add_volatile<_Tp>::type>::type type;
      };

    // remove_reference

    template<class _Tp>
      struct _LIBCPP_VISIBLE remove_reference
      {
        typedef _Tp type;
      };
    template<class _Tp>
      struct _LIBCPP_VISIBLE remove_reference<_Tp&>
      {
        typedef _Tp type;
      };
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
    template<class _Tp>
    struct _LIBCPP_VISIBLE remove_reference<_Tp&&>
      { typedef _Tp type;};
#endif

    // add_lvalue_reference

    template<class _Tp>
      struct _LIBCPP_VISIBLE add_lvalue_reference
      {
        typedef _Tp& type;
      };
    template<class _Tp>
      struct _LIBCPP_VISIBLE add_lvalue_reference<_Tp&>
      {
        typedef _Tp& type;
      };
    // for older compiler
    template<>
      struct _LIBCPP_VISIBLE add_lvalue_reference<void>
      {
        typedef void type;
      };
    template<>
      struct _LIBCPP_VISIBLE add_lvalue_reference<const void>
      {
        typedef const void type;
      };
    template<>
      struct _LIBCPP_VISIBLE add_lvalue_reference<volatile void>
      {
        typedef volatile void type;
      };
    template<>
      struct _LIBCPP_VISIBLE add_lvalue_reference<const volatile void>
      {
        typedef const volatile void type;
      };

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

    template<class _Tp>
    struct _LIBCPP_VISIBLE add_rvalue_reference
      {
        typedef _Tp&& type;};
    template<>
    struct _LIBCPP_VISIBLE add_rvalue_reference<void>
      {
        typedef void type;
      };
    template<>
    struct _LIBCPP_VISIBLE add_rvalue_reference<const void>
      {
        typedef const void type;
      };
    template<>
    struct _LIBCPP_VISIBLE add_rvalue_reference<volatile void>
      {
        typedef volatile void type;
      };
    template<>
    struct _LIBCPP_VISIBLE add_rvalue_reference<const volatile void>
      {
        typedef const volatile void type;
      };

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

    template<class _Tp>
    typename add_rvalue_reference<_Tp>::type
    declval() _NOEXCEPT;

#else  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
    template<class _Tp>
      typename add_lvalue_reference<_Tp>::type
      declval();

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
#if !defined(__DOXYGEN__)
    struct __any
    {
      __any(...);
    };
#endif

    // remove_pointer

    template<class _Tp>
      struct _LIBCPP_VISIBLE remove_pointer
      {
        typedef _Tp type;
      };
    template<class _Tp>
      struct _LIBCPP_VISIBLE remove_pointer<_Tp*>
      {
        typedef _Tp type;
      };
    template<class _Tp>
      struct _LIBCPP_VISIBLE remove_pointer<_Tp* const >
      {
        typedef _Tp type;
      };
    template<class _Tp>
      struct _LIBCPP_VISIBLE remove_pointer<_Tp* volatile >
      {
        typedef _Tp type;
      };
    template<class _Tp>
      struct _LIBCPP_VISIBLE remove_pointer<_Tp* const volatile >
      {
        typedef _Tp type;
      };

    // add_pointer

    template<class _Tp>
      struct _LIBCPP_VISIBLE add_pointer
      {
        typedef typename remove_reference<_Tp>::type* type;
      };

    // is_signed

    template<class _Tp, bool = is_integral<_Tp>::value>
      struct ___is_signed : public integral_constant<bool, _Tp(-1) < _Tp(0)>
      {
      };

    template<class _Tp>
      struct ___is_signed<_Tp, false> : public true_type
      {
      };
    // floating point

    template<class _Tp, bool = is_arithmetic<_Tp>::value>
      struct __is_signed : public ___is_signed<_Tp>
      {
      };

    template<class _Tp>
      struct __is_signed<_Tp, false> : public false_type
      {
      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_signed : public __is_signed<_Tp>
      {
      };

    // is_unsigned

    template<class _Tp, bool = is_integral<_Tp>::value>
      struct ___is_unsigned : public integral_constant<bool, _Tp(0) < _Tp(-1)>
      {
      };

    template<class _Tp>
      struct ___is_unsigned<_Tp, false> : public false_type
      {
      };
    // floating point

    template<class _Tp, bool = is_arithmetic<_Tp>::value>
      struct __is_unsigned : public ___is_unsigned<_Tp>
      {
      };

    template<class _Tp>
      struct __is_unsigned<_Tp, false> : public false_type
      {
      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_unsigned : public __is_unsigned<_Tp>
      {
      };

    // rank

    template<class _Tp>
      struct _LIBCPP_VISIBLE rank : public integral_constant<size_t, 0>
      {
      };
    template<class _Tp>
      struct _LIBCPP_VISIBLE rank<_Tp[]> : public integral_constant<size_t,
          rank<_Tp>::value + 1>
      {
      };
    template<class _Tp, size_t _Np>
      struct _LIBCPP_VISIBLE rank<_Tp[_Np]> : public integral_constant<size_t,
          rank<_Tp>::value + 1>
      {
      };

    // extent

    template<class _Tp, unsigned _Ip = 0>
      struct _LIBCPP_VISIBLE extent : public integral_constant<size_t, 0>
      {
      };
    template<class _Tp>
      struct _LIBCPP_VISIBLE extent<_Tp[], 0> : public integral_constant<size_t,
          0>
      {
      };
    template<class _Tp, unsigned _Ip>
      struct _LIBCPP_VISIBLE extent<_Tp[], _Ip> : public integral_constant<
          size_t, extent<_Tp, _Ip - 1>::value>
      {
      };
    template<class _Tp, size_t _Np>
      struct _LIBCPP_VISIBLE extent<_Tp[_Np], 0> : public integral_constant<
          size_t, _Np>
      {
      };
    template<class _Tp, size_t _Np, unsigned _Ip>
      struct _LIBCPP_VISIBLE extent<_Tp[_Np], _Ip> : public integral_constant<
          size_t, extent<_Tp, _Ip - 1>::value>
      {
      };

    // remove_extent

    template<class _Tp>
      struct _LIBCPP_VISIBLE remove_extent
      {
        typedef _Tp type;
      };
    template<class _Tp>
      struct _LIBCPP_VISIBLE remove_extent<_Tp[]>
      {
        typedef _Tp type;
      };
    template<class _Tp, size_t _Np>
      struct _LIBCPP_VISIBLE remove_extent<_Tp[_Np]>
      {
        typedef _Tp type;
      };

    // remove_all_extents

    template<class _Tp>
      struct _LIBCPP_VISIBLE remove_all_extents
      {
        typedef _Tp type;
      };
    template<class _Tp>
      struct _LIBCPP_VISIBLE remove_all_extents<_Tp[]>
      {
        typedef typename remove_all_extents<_Tp>::type type;
      };
    template<class _Tp, size_t _Np>
      struct _LIBCPP_VISIBLE remove_all_extents<_Tp[_Np]>
      {
        typedef typename remove_all_extents<_Tp>::type type;
      };

    // is_abstract

    namespace __is_abstract_imp
    {
      template<class _Tp>
        char
        __test(_Tp (*)[1]);
      template<class _Tp>
        __two                 __test(...);
}      template<class _Tp, bool = is_class<_Tp>::value>
        struct __libcpp_abstract : public integral_constant<bool,
            sizeof(__is_abstract_imp::__test<_Tp>(0)) != 1>
        {
        };

      template<class _Tp>
        struct __libcpp_abstract<_Tp, false> : public false_type
        {
        };

      template<class _Tp>
        struct _LIBCPP_VISIBLE is_abstract : public __libcpp_abstract<_Tp>
        {
        };

      // is_base_of

#ifdef _LIBCP_HAS_IS_BASE_OF

      template <class _Bp, class _Dp>
      struct _LIBCPP_VISIBLE is_base_of
      : public integral_constant<bool, __is_base_of(_Bp, _Dp)>
        {};

#else  // __has_feature(is_base_of)
      namespace __is_base_of_imp
      {
        template<class _Tp>
          struct _Dst
          {
            _Dst(const volatile _Tp &);
          };
        template<class _Tp>
          struct _Src
          {
            operator const volatile _Tp &();
            template<class _Up>
              operator const _Dst<_Up> &();
          };
        template<size_t>
          struct __one
          {
            typedef char type;
          };
        template<class _Bp, class _Dp>
          typename __one<sizeof(_Dst<_Bp>(declval<_Src<_Dp> >()))>::type
          __test(int);
        template<class _Bp, class _Dp>
          __two                 __test(...);
}        template<class _Bp, class _Dp>
          struct _LIBCPP_VISIBLE is_base_of : public integral_constant<bool,
              is_class<_Bp>::value
                  && sizeof(__is_base_of_imp::__test<_Bp, _Dp>(0)) == 2>
          {
          };

#endif  // __has_feature(is_base_of)
        // is_convertible

#if __has_feature(is_convertible_to)

        template <class _T1, class _T2> struct _LIBCPP_VISIBLE is_convertible
        : public integral_constant<bool, __is_convertible_to(_T1, _T2) &&
        !is_abstract<_T2>::value>
          {};

#else  // __has_feature(is_convertible_to)
namespace        __is_convertible_imp
          {
            template <class _Tp> char __test(_Tp);
            template <class _Tp> __two __test(...);
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
            template <class _Tp> _Tp&& __source();
#else
            template <class _Tp> typename remove_reference<_Tp>::type& __source();
#endif

            template <class _Tp, bool _IsArray = is_array<_Tp>::value,
            bool _IsFunction = is_function<_Tp>::value,
            bool _IsVoid = is_void<_Tp>::value>
            struct __is_array_function_or_void
              { enum
                  { value = 0};};
            template <class _Tp> struct __is_array_function_or_void<_Tp, true, false, false>
              { enum
                  { value = 1};};
            template <class _Tp> struct __is_array_function_or_void<_Tp, false, true, false>
              { enum
                  { value = 2};};
            template <class _Tp> struct __is_array_function_or_void<_Tp, false, false, true>
              { enum
                  { value = 3};};
          }

    template<class _Tp, unsigned =
        __is_convertible_imp::__is_array_function_or_void<
            typename remove_reference<_Tp>::type>::value>
      struct __is_convertible_check
      {
        static const size_t __v = 0;
      };

    template<class _Tp>
      struct __is_convertible_check<_Tp, 0>
      {
        static const size_t __v = sizeof(_Tp);
      };

    template<class _T1, class _T2, unsigned _T1_is_array_function_or_void =
        __is_convertible_imp::__is_array_function_or_void<_T1>::value,
        unsigned _T2_is_array_function_or_void =
            __is_convertible_imp::__is_array_function_or_void<_T2>::value>
      struct __is_convertible : public integral_constant<bool,
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
          sizeof(__is_convertible_imp::__test<_T2>(
                  __is_convertible_imp::__source<_T1>())) == 1
#else
          sizeof(__is_convertible_imp::__test<_T2>(
              __is_convertible_imp::__source<_T1>())) == 1
              && !(!is_function<_T1>::value && !is_reference<_T1>::value
                  && is_reference<_T2>::value
                  && (!is_const<typename remove_reference<_T2>::type>::value
                      || is_volatile<typename remove_reference<_T2>::type>::value)
                  && (is_same<typename remove_cv<_T1>::type,
                      typename remove_cv<typename remove_reference<_T2>::type>::type>::value
                      || is_base_of<typename remove_reference<_T2>::type, _T1>::value))
#endif
          >
      {
      };

    template<class _T1, class _T2>
      struct __is_convertible<_T1, _T2, 1, 0> : false_type
      {
      };

    template<class _T1>
      struct __is_convertible<_T1, const _T1&, 1, 0> : true_type
      {
      };
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
    template<class _T1>
    struct __is_convertible<_T1, _T1&&, 1, 0> : true_type
      {};
    template<class _T1>
    struct __is_convertible<_T1, const _T1&&, 1, 0> : true_type
      {};
    template<class _T1>
    struct __is_convertible<_T1, volatile _T1&&, 1, 0> : true_type
      {};
    template<class _T1>
    struct __is_convertible<_T1, const volatile _T1&&, 1, 0> : true_type
      {};
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
    template<class _T1, class _T2>
      struct __is_convertible<_T1, _T2*, 1, 0> : public integral_constant<bool,
          __is_convertible<typename remove_all_extents<_T1>::type*, _T2*>::value>
      {
      };

    template<class _T1, class _T2>
      struct __is_convertible<_T1, _T2* const, 1, 0> : public integral_constant<
          bool,
          __is_convertible<typename remove_all_extents<_T1>::type*, _T2* const >::value>
      {
      };

    template<class _T1, class _T2>
      struct __is_convertible<_T1, _T2* volatile, 1, 0> : public integral_constant<
          bool,
          __is_convertible<typename remove_all_extents<_T1>::type*,
              _T2* volatile >::value>
      {
      };

    template<class _T1, class _T2>
      struct __is_convertible<_T1, _T2* const volatile, 1, 0> : public integral_constant<
          bool,
          __is_convertible<typename remove_all_extents<_T1>::type*,
              _T2* const volatile >::value>
      {
      };

    template<class _T1, class _T2>
      struct __is_convertible<_T1, _T2, 2, 0> : public false_type
      {
      };
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
    template<class _T1>
    struct __is_convertible<_T1, _T1&&, 2, 0> : public true_type
      {};
#endif
    template<class _T1>
      struct __is_convertible<_T1, _T1&, 2, 0> : public true_type
      {
      };
    template<class _T1>
      struct __is_convertible<_T1, _T1*, 2, 0> : public true_type
      {
      };
    template<class _T1>
      struct __is_convertible<_T1, _T1* const, 2, 0> : public true_type
      {
      };
    template<class _T1>
      struct __is_convertible<_T1, _T1* volatile, 2, 0> : public true_type
      {
      };
    template<class _T1>
      struct __is_convertible<_T1, _T1* const volatile, 2, 0> : public true_type
      {
      };

    template<class _T1, class _T2>
      struct __is_convertible<_T1, _T2, 3, 0> : public false_type
      {
      };

    template<class _T1, class _T2>
      struct __is_convertible<_T1, _T2, 0, 1> : public false_type
      {
      };
    template<class _T1, class _T2>
      struct __is_convertible<_T1, _T2, 1, 1> : public false_type
      {
      };
    template<class _T1, class _T2>
      struct __is_convertible<_T1, _T2, 2, 1> : public false_type
      {
      };
    template<class _T1, class _T2>
      struct __is_convertible<_T1, _T2, 3, 1> : public false_type
      {
      };

    template<class _T1, class _T2>
      struct __is_convertible<_T1, _T2, 0, 2> : public false_type
      {
      };
    template<class _T1, class _T2>
      struct __is_convertible<_T1, _T2, 1, 2> : public false_type
      {
      };
    template<class _T1, class _T2>
      struct __is_convertible<_T1, _T2, 2, 2> : public false_type
      {
      };
    template<class _T1, class _T2>
      struct __is_convertible<_T1, _T2, 3, 2> : public false_type
      {
      };

    template<class _T1, class _T2>
      struct __is_convertible<_T1, _T2, 0, 3> : public false_type
      {
      };
    template<class _T1, class _T2>
      struct __is_convertible<_T1, _T2, 1, 3> : public false_type
      {
      };
    template<class _T1, class _T2>
      struct __is_convertible<_T1, _T2, 2, 3> : public false_type
      {
      };
    template<class _T1, class _T2>
      struct __is_convertible<_T1, _T2, 3, 3> : public true_type
      {
      };

    template<class _T1, class _T2>
      struct _LIBCPP_VISIBLE is_convertible : public __is_convertible<_T1, _T2>
      {
        static const size_t __complete_check1 = __is_convertible_check<_T1>::__v;
        static const size_t __complete_check2 = __is_convertible_check<_T2>::__v;
      };

#endif  // __has_feature(is_convertible_to)
    // is_empty

//#if __has_feature(is_empty)
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

    template <class _Tp>
    struct _LIBCPP_VISIBLE is_empty
    : public integral_constant<bool, __is_empty(_Tp)>
      {};

#else  // __has_feature(is_empty)
    template<class _Tp>
      struct __is_empty1 : public _Tp
      {
        double __lx;
      };

    struct __is_empty2
    {
      double __lx;
    };

    template<class _Tp, bool = is_class<_Tp>::value>
      struct __libcpp_empty : public integral_constant<bool,
          sizeof(__is_empty1 <_Tp> ) == sizeof(__is_empty2 )>
      {
      };

    template<class _Tp>
      struct __libcpp_empty<_Tp, false> : public false_type
      {
      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_empty : public __libcpp_empty<_Tp>
      {
      };

#endif  // __has_feature(is_empty)
    // is_polymorphic

#if __has_feature(is_polymorphic)

    template <class _Tp>
    struct _LIBCPP_VISIBLE is_polymorphic
    : public integral_constant<bool, __is_polymorphic(_Tp)>
      {};

#else

template    <class _Tp> struct __is_polymorphic1 : public _Tp
      {};
    template<class _Tp>
      struct __is_polymorphic2 : public _Tp
      {
        virtual
        ~__is_polymorphic2() throw ();
      };

    template<class _Tp, bool = is_class<_Tp>::value>
      struct __libcpp_polymorphic : public integral_constant<bool,
          sizeof(__is_polymorphic1 <_Tp> ) == sizeof(__is_polymorphic2 <_Tp> )>
      {
      };

    template<class _Tp>
      struct __libcpp_polymorphic<_Tp, false> : public false_type
      {
      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_polymorphic : public __libcpp_polymorphic<_Tp>
      {
      };

#endif // __has_feature(is_polymorphic)
    // has_virtual_destructor

#if __has_feature(has_virtual_destructor) || (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)

    template <class _Tp> struct _LIBCPP_VISIBLE has_virtual_destructor
    : public integral_constant<bool, __has_virtual_destructor(_Tp)>
      {};

#else  // _LIBCPP_HAS_TYPE_TRAITS
template    <class _Tp> struct _LIBCPP_VISIBLE has_virtual_destructor
    : public false_type
      {};

#endif  // _LIBCPP_HAS_TYPE_TRAITS
// alignment_of

    template<class _Tp>
      struct __alignment_of
      {
        _Tp __lx;
      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE alignment_of : public integral_constant<size_t,
          __alignof__(__alignment_of <typename remove_all_extents<_Tp>::type> )>
      {
      };

    // aligned_storage

    template<class _Hp, class _Tp>
      struct __type_list
      {
        typedef _Hp _Head;
        typedef _Tp _Tail;
      };

    struct __nat
    {
#ifndef _LIBCPP_HAS_NO_DELETED_FUNCTIONS
      __nat() = delete;
      __nat(const __nat&) = delete;
      __nat& operator=(const __nat&) = delete;
      ~__nat() = delete;
#endif
    };

    template<class _Tp>
      struct __align_type
      {
        static const size_t value = alignment_of<_Tp>::value;
        typedef _Tp type;
      };

    struct __struct_double
    {
      long double __lx;
    };
    struct __struct_double4
    {
      double __lx[4];
    };

    typedef __type_list< __align_type< unsigned char>,
    __type_list<__align_type<unsigned short>,
    __type_list<__align_type<unsigned int>,
    __type_list<__align_type<unsigned long>,
    __type_list<__align_type<unsigned long long>,
    __type_list<__align_type<double>,
    __type_list<__align_type<long double>,
    __type_list<__align_type<__struct_double>,
    __type_list<__align_type<__struct_double4>,
    __type_list<__align_type<int*>,
    __nat
    > > > > > > > > > > __all_types;

    template<class _TL, size_t _Align>
      struct __find_pod;

    template<class _Hp, size_t _Align>
      struct __find_pod<__type_list <_Hp, __nat >, _Align>
      {
        typedef typename conditional<_Align == _Hp::value, typename _Hp::type,
            void>::type type;
      };

    template<class _Hp, class _Tp, size_t _Align>
      struct __find_pod<__type_list <_Hp, _Tp>, _Align>
      {
        typedef typename conditional<_Align == _Hp::value, typename _Hp::type,
            typename __find_pod<_Tp, _Align>::type>::type type;
      };

    template<class _TL, size_t _Len>
      struct __find_max_align;

    template<class _Hp, size_t _Len>
      struct __find_max_align<__type_list <_Hp, __nat >, _Len> : public integral_constant<
          size_t, _Hp::value>
      {
      };

    template<size_t _Len, size_t _A1, size_t _A2>
      struct __select_align
      {
      private:
        static const size_t __min = _A2 < _A1 ? _A2 : _A1;
        static const size_t __max = _A1 < _A2 ? _A2 : _A1;
      public:
        static const size_t value = _Len < __max ? __min : __max;
      };

    template<class _Hp, class _Tp, size_t _Len>
      struct __find_max_align<__type_list <_Hp, _Tp>, _Len> : public integral_constant<
          size_t,
          __select_align<_Len, _Hp::value, __find_max_align<_Tp, _Len>::value>::value>
      {
      };

    template<size_t _Len, const size_t _Align = __find_max_align<__all_types,
        _Len>::value>
      struct _LIBCPP_VISIBLE aligned_storage
      {
        typedef typename __find_pod<__all_types, _Align>::type _Aligner;
        static_assert(!is_void<_Aligner>::value, "");
        union type
        {
          _Aligner __align;
          unsigned char __data[_Len];
        };
      };

    // __promote

    template<class _A1, class _A2 = void, class _A3 = void, bool =
        (is_arithmetic<_A1>::value || is_void<_A1>::value)
            && (is_arithmetic<_A2>::value || is_void<_A2>::value)
            && (is_arithmetic<_A3>::value || is_void<_A3>::value)>
      class __promote
      {
      };

    template<class _A1, class _A2, class _A3>
      class __promote<_A1, _A2, _A3, true>
      {
      private:
        typedef typename __promote<_A1>::type __type1;
        typedef typename __promote<_A2>::type __type2;
        typedef typename __promote<_A3>::type __type3;
      public:
        typedef decltype(__type1() + __type2() + __type3()) type;
      };

    template<class _A1, class _A2>
      class __promote<_A1, _A2, void, true>
      {
      private:
        typedef typename __promote<_A1>::type __type1;
        typedef typename __promote<_A2>::type __type2;
      public:
        typedef decltype(__type1() + __type2()) type;
      };

    template<class _A1>
      class __promote<_A1, void, void, true>
      {
      public:
        typedef typename conditional<is_arithmetic<_A1>::value,
            typename conditional<is_integral<_A1>::value, double, _A1>::type,
            void>::type type;
      };

#ifdef _LIBCPP_STORE_AS_OPTIMIZATION

    // __transform

    template <class _Tp, size_t = sizeof(_Tp), bool = is_scalar<_Tp>::value> struct __transform
      { typedef _Tp type;};
    template <class _Tp> struct __transform<_Tp, 1, true>
      { typedef unsigned char type;};
    template <class _Tp> struct __transform<_Tp, 2, true>
      { typedef unsigned short type;};
    template <class _Tp> struct __transform<_Tp, 4, true>
      { typedef unsigned int type;};
    template <class _Tp> struct __transform<_Tp, 8, true>
      { typedef unsigned long long type;};

#endif  // _LIBCPP_STORE_AS_OPTIMIZATION
    // make_signed / make_unsigned

    typedef __type_list< signed char,
    __type_list<signed short,
    __type_list<signed int,
    __type_list<signed long,
    __type_list<signed long long,
    __nat
    > > > > > __signed_types;

    typedef __type_list< unsigned char,
    __type_list<unsigned short,
    __type_list<unsigned int,
    __type_list<unsigned long,
    __type_list<unsigned long long,
    __nat
    > > > > > __unsigned_types;

    template<class _TypeList, size_t _Size, bool = _Size
        <= sizeof(typename _TypeList::_Head)>
      struct __find_first;

    template<class _Hp, class _Tp, size_t _Size>
      struct __find_first<__type_list <_Hp, _Tp>, _Size, true>
      {
        typedef _Hp type;
      };

    template<class _Hp, class _Tp, size_t _Size>
      struct __find_first<__type_list <_Hp, _Tp>, _Size, false>
      {
        typedef typename __find_first<_Tp, _Size>::type type;
      };

    template<class _Tp, class _Up, bool = is_const<
        typename remove_reference<_Tp>::type>::value, bool = is_volatile<
        typename remove_reference<_Tp>::type>::value>
      struct __apply_cv
      {
        typedef _Up type;
      };

    template<class _Tp, class _Up>
      struct __apply_cv<_Tp, _Up, true, false>
      {
        typedef const _Up type;
      };

    template<class _Tp, class _Up>
      struct __apply_cv<_Tp, _Up, false, true>
      {
        typedef volatile _Up type;
      };

    template<class _Tp, class _Up>
      struct __apply_cv<_Tp, _Up, true, true>
      {
        typedef const volatile _Up type;
      };

    template<class _Tp, class _Up>
      struct __apply_cv<_Tp&, _Up, false, false>
      {
        typedef _Up& type;
      };

    template<class _Tp, class _Up>
      struct __apply_cv<_Tp&, _Up, true, false>
      {
        typedef const _Up& type;
      };

    template<class _Tp, class _Up>
      struct __apply_cv<_Tp&, _Up, false, true>
      {
        typedef volatile _Up& type;
      };

    template<class _Tp, class _Up>
      struct __apply_cv<_Tp&, _Up, true, true>
      {
        typedef const volatile _Up& type;
      };

    template<class _Tp, bool = is_integral<_Tp>::value || is_enum<_Tp>::value>
      struct __make_signed
      {
      };

    template<class _Tp>
      struct __make_signed<_Tp, true>
      {
        typedef typename __find_first<__signed_types, sizeof(_Tp)>::type type;
      };

    template<>
      struct __make_signed<bool, true>
      {
      };
    template<>
      struct __make_signed<signed short, true>
      {
        typedef short type;
      };
    template<>
      struct __make_signed<unsigned short, true>
      {
        typedef short type;
      };
    template<>
      struct __make_signed<signed int, true>
      {
        typedef int type;
      };
    template<>
      struct __make_signed<unsigned int, true>
      {
        typedef int type;
      };
    template<>
      struct __make_signed<signed long, true>
      {
        typedef long type;
      };
    template<>
      struct __make_signed<unsigned long, true>
      {
        typedef long type;
      };
    template<>
      struct __make_signed<signed long long, true>
      {
        typedef long long type;
      };
    template<>
      struct __make_signed<unsigned long long, true>
      {
        typedef long long type;
      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE make_signed
      {
        typedef typename __apply_cv<_Tp,
            typename __make_signed<typename remove_cv<_Tp>::type>::type>::type type;
      };

    template<class _Tp, bool = is_integral<_Tp>::value || is_enum<_Tp>::value>
      struct __make_unsigned
      {
      };

    template<class _Tp>
      struct __make_unsigned<_Tp, true>
      {
        typedef typename __find_first<__unsigned_types, sizeof(_Tp)>::type type;
      };

    template<>
      struct __make_unsigned<bool, true>
      {
      };
    template<>
      struct __make_unsigned<signed short, true>
      {
        typedef unsigned short type;
      };
    template<>
      struct __make_unsigned<unsigned short, true>
      {
        typedef unsigned short type;
      };
    template<>
      struct __make_unsigned<signed int, true>
      {
        typedef unsigned int type;
      };
    template<>
      struct __make_unsigned<unsigned int, true>
      {
        typedef unsigned int type;
      };
    template<>
      struct __make_unsigned<signed long, true>
      {
        typedef unsigned long type;
      };
    template<>
      struct __make_unsigned<unsigned long, true>
      {
        typedef unsigned long type;
      };
    template<>
      struct __make_unsigned<signed long long, true>
      {
        typedef unsigned long long type;
      };
    template<>
      struct __make_unsigned<unsigned long long, true>
      {
        typedef unsigned long long type;
      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE make_unsigned
      {
        typedef typename __apply_cv<_Tp,
            typename __make_unsigned<typename remove_cv<_Tp>::type>::type>::type type;
      };

#ifdef _LIBCPP_HAS_NO_VARIADICS

    template<class _Tp, class _Up = void, class V = void>
    struct _LIBCPP_VISIBLE common_type
      {
      public:
        typedef typename common_type<typename common_type<_Tp, _Up>::type, V>::type type;
      };

    template<class _Tp>
    struct _LIBCPP_VISIBLE common_type<_Tp, void, void>
      {
      public:
        typedef _Tp type;
      };

    template<class _Tp, class _Up>
    struct _LIBCPP_VISIBLE common_type<_Tp, _Up, void>
      {
      private:
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
        static _Tp&& __t();
        static _Up&& __u();
#else  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
        static _Tp
        __t();
        static _Up
        __u();
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
      public:
        typedef typename remove_reference<decltype(true ? __t() : __u())>::type type;
      };

#else  // _LIBCPP_HAS_NO_VARIADICS
    template<class ..._Tp>
      struct common_type;

    template<class _Tp>
      struct _LIBCPP_VISIBLE common_type<_Tp>
      {
        typedef _Tp type;
      };

    template<class _Tp, class _Up>
      struct _LIBCPP_VISIBLE common_type<_Tp, _Up>
      {
      private:
        static _Tp&& __t();
        static _Up&& __u();
        static bool __f();
      public:
        typedef typename remove_reference<decltype(__f() ? __t() : __u())>::type type;
      };

    template<class _Tp, class _Up, class ..._Vp>
      struct _LIBCPP_VISIBLE common_type<_Tp, _Up, _Vp...>
      {
        typedef typename common_type<typename common_type<_Tp, _Up>::type,
            _Vp...>::type type;
      };

#endif  // _LIBCPP_HAS_NO_VARIADICS
    // is_assignable

    template<class _Tp, class _Arg>
      decltype((_VSTD::declval<_Tp>() = _VSTD::declval<_Arg>(), true_type()))
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
      __is_assignable_test(_Tp&&, _Arg&&);
#else
      __is_assignable_test(_Tp, _Arg&);
#endif

    template<class _Arg>
      false_type
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
      __is_assignable_test(__any, _Arg&&);
#else
      __is_assignable_test(__any, _Arg&);
#endif

    template<class _Tp, class _Arg, bool = is_void<_Tp>::value
        || is_void<_Arg>::value>
      struct __is_assignable_imp : public common_type<
          decltype(__is_assignable_test(declval<_Tp>(), declval<_Arg>()))>::type
      {
      };

    template<class _Tp, class _Arg>
      struct __is_assignable_imp<_Tp, _Arg, true> : public false_type
      {
      };

    template<class _Tp, class _Arg>
      struct is_assignable : public __is_assignable_imp<_Tp, _Arg>
      {
      };

    // is_copy_assignable

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_copy_assignable : public is_assignable<
          typename add_lvalue_reference<_Tp>::type,
          const typename add_lvalue_reference<_Tp>::type>
      {
      };

    // is_move_assignable

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_move_assignable
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
          : public is_assignable<typename add_lvalue_reference<_Tp>::type,
          const typename add_rvalue_reference<_Tp>::type>
            {
            };
#else
          : public is_copy_assignable<_Tp>
      {
      };
#endif

    // is_destructible

    template<class _Tp>
      struct __destructible_test
      {
        _Tp __t;
      };

    template<class _Tp>
      decltype((_VSTD::declval<__destructible_test<_Tp> >().~__destructible_test<_Tp>(), true_type()))
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
      __is_destructible_test(_Tp&&);
#else
      __is_destructible_test(_Tp&);
#endif

    false_type
    __is_destructible_test(__any);

    template<class _Tp, bool = is_void<_Tp>::value || is_abstract<_Tp>::value>
      struct __destructible_imp : public common_type<
          decltype(__is_destructible_test(declval<_Tp>()))>::type
      {
      };

    template<class _Tp>
      struct __destructible_imp<_Tp, true> : public false_type
      {
      };

    template<class _Tp>
      struct is_destructible : public __destructible_imp<_Tp>
      {
      };

    // move

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

    template<class _Tp>
    inline _LIBCPP_INLINE_VISIBILITY
    typename remove_reference<_Tp>::type&&
    move(_Tp&& __t) _NOEXCEPT
      {
        typedef typename remove_reference<_Tp>::type _Up;
        return static_cast<_Up&&>(__t);
      }

    template<class _Tp>
    inline _LIBCPP_INLINE_VISIBILITY
    _Tp&&
    forward(typename _VSTD::remove_reference<_Tp>::type& __t) _NOEXCEPT
      {
        return static_cast<_Tp&&>(__t);
      }

    template<class _Tp>
    inline _LIBCPP_INLINE_VISIBILITY
    _Tp&&
    forward(typename _VSTD::remove_reference<_Tp>::type&& __t) _NOEXCEPT
      {
        static_assert(!_VSTD::is_lvalue_reference<_Tp>::value,
            "Can not forward an rvalue as an lvalue.");
        return static_cast<_Tp&&>(__t);
      }

#else  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
    template<class _Tp>
      inline _LIBCPP_INLINE_VISIBILITY
      _Tp&
      move(_Tp& __t)
      {
        return __t;
      }

    template<class _Tp>
      inline _LIBCPP_INLINE_VISIBILITY
      const _Tp&
      move(const _Tp& __t)
      {
        return __t;
      }

    template<class _Tp>
      inline _LIBCPP_INLINE_VISIBILITY
      _Tp&
      forward(typename remove_reference<_Tp>::type& __t) _NOEXCEPT
      {
        return __t;
      }

    template<class _Tp>
      class __rv
      {
        typedef typename remove_reference<_Tp>::type _Trr;
        _Trr& t_;
      public:
        _LIBCPP_INLINE_VISIBILITY
        _Trr*
        operator->()
        {
          return &t_;
        }
        _LIBCPP_INLINE_VISIBILITY
        explicit
        __rv(_Trr& __t)
            : t_(__t)
        {
        }
      };

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
    template<class _Tp>
      struct _LIBCPP_VISIBLE decay
      {
      private:
        typedef typename remove_reference<_Tp>::type _Up;
      public:
        typedef typename conditional<is_array<_Up>::value,
            typename remove_extent<_Up>::type*,
            typename conditional<is_function<_Up>::value,
                typename add_pointer<_Up>::type, typename remove_cv<_Up>::type>::type>::type type;
      };

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

    template<class _Tp>
    inline _LIBCPP_INLINE_VISIBILITY
    typename decay<_Tp>::type
    __decay_copy(_Tp&& __t)
      {
        return _VSTD::forward<_Tp>(__t);
      }

#else

    template<class _Tp>
      inline _LIBCPP_INLINE_VISIBILITY
      typename decay<_Tp>::type
      __decay_copy(const _Tp& __t)
        {
          return _VSTD::forward<_Tp>(__t);
        }

#endif

    template<class _MP, bool _IsMemberFuctionPtr, bool _IsMemberObjectPtr>
      struct __member_pointer_traits_imp
      {
      };

#ifndef _LIBCPP_HAS_NO_VARIADICS

    template<class _Rp, class _Class, class ..._Param>
      struct __member_pointer_traits_imp<_Rp
      (_Class::*)(_Param...), true, false>
      {
        typedef _Class _ClassType;
        typedef _Rp _ReturnType;
      };

    template<class _Rp, class _Class, class ..._Param>
      struct __member_pointer_traits_imp<_Rp
      (_Class::*)(_Param...) const, true, false>
      {
        typedef _Class const _ClassType;
        typedef _Rp _ReturnType;
      };

    template<class _Rp, class _Class, class ..._Param>
      struct __member_pointer_traits_imp<_Rp
      (_Class::*)(_Param...) volatile, true, false>
      {
        typedef _Class volatile _ClassType;
        typedef _Rp _ReturnType;
      };

    template<class _Rp, class _Class, class ..._Param>
      struct __member_pointer_traits_imp<_Rp
      (_Class::*)(_Param...) const volatile, true, false>
      {
        typedef _Class const volatile _ClassType;
        typedef _Rp _ReturnType;
      };

#if __has_feature(cxx_reference_qualified_functions)

    template <class _Rp, class _Class, class ..._Param>
    struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) &, true, false>
      {
        typedef _Class& _ClassType;
        typedef _Rp _ReturnType;
      };

    template <class _Rp, class _Class, class ..._Param>
    struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) const&, true, false>
      {
        typedef _Class const& _ClassType;
        typedef _Rp _ReturnType;
      };

    template <class _Rp, class _Class, class ..._Param>
    struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) volatile&, true, false>
      {
        typedef _Class volatile& _ClassType;
        typedef _Rp _ReturnType;
      };

    template <class _Rp, class _Class, class ..._Param>
    struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) const volatile&, true, false>
      {
        typedef _Class const volatile& _ClassType;
        typedef _Rp _ReturnType;
      };

    template <class _Rp, class _Class, class ..._Param>
    struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) &&, true, false>
      {
        typedef _Class&& _ClassType;
        typedef _Rp _ReturnType;
      };

    template <class _Rp, class _Class, class ..._Param>
    struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) const&&, true, false>
      {
        typedef _Class const&& _ClassType;
        typedef _Rp _ReturnType;
      };

    template <class _Rp, class _Class, class ..._Param>
    struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) volatile&&, true, false>
      {
        typedef _Class volatile&& _ClassType;
        typedef _Rp _ReturnType;
      };

    template <class _Rp, class _Class, class ..._Param>
    struct __member_pointer_traits_imp<_Rp (_Class::*)(_Param...) const volatile&&, true, false>
      {
        typedef _Class const volatile&& _ClassType;
        typedef _Rp _ReturnType;
      };

#endif  // __has_feature(cxx_reference_qualified_functions)
#else  // _LIBCPP_HAS_NO_VARIADICS
    template<class _Rp, class _Class>
    struct __member_pointer_traits_imp<_Rp
    (_Class::*)(), true, false>
      {
        typedef _Class _ClassType;
        typedef _Rp _ReturnType;
      };

    template<class _Rp, class _Class, class _P0>
    struct __member_pointer_traits_imp<_Rp
    (_Class::*)(_P0), true, false>
      {
        typedef _Class _ClassType;
        typedef _Rp _ReturnType;
      };

    template<class _Rp, class _Class, class _P0, class _P1>
    struct __member_pointer_traits_imp<_Rp
    (_Class::*)(_P0, _P1), true, false>
      {
        typedef _Class _ClassType;
        typedef _Rp _ReturnType;
      };

    template<class _Rp, class _Class, class _P0, class _P1, class _P2>
    struct __member_pointer_traits_imp<_Rp
    (_Class::*)(_P0, _P1, _P2), true, false>
      {
        typedef _Class _ClassType;
        typedef _Rp _ReturnType;
      };

    template<class _Rp, class _Class>
    struct __member_pointer_traits_imp<_Rp
    (_Class::*)() const, true, false>
      {
        typedef _Class const _ClassType;
        typedef _Rp _ReturnType;
      };

    template<class _Rp, class _Class, class _P0>
    struct __member_pointer_traits_imp<_Rp
    (_Class::*)(_P0) const, true, false>
      {
        typedef _Class const _ClassType;
        typedef _Rp _ReturnType;
      };

    template<class _Rp, class _Class, class _P0, class _P1>
    struct __member_pointer_traits_imp<_Rp
    (_Class::*)(_P0, _P1) const, true, false>
      {
        typedef _Class const _ClassType;
        typedef _Rp _ReturnType;
      };

    template<class _Rp, class _Class, class _P0, class _P1, class _P2>
    struct __member_pointer_traits_imp<_Rp
    (_Class::*)(_P0, _P1, _P2) const, true, false>
      {
        typedef _Class const _ClassType;
        typedef _Rp _ReturnType;
      };

    template<class _Rp, class _Class>
    struct __member_pointer_traits_imp<_Rp
    (_Class::*)() volatile, true, false>
      {
        typedef _Class volatile _ClassType;
        typedef _Rp _ReturnType;
      };

    template<class _Rp, class _Class, class _P0>
    struct __member_pointer_traits_imp<_Rp
    (_Class::*)(_P0) volatile, true, false>
      {
        typedef _Class volatile _ClassType;
        typedef _Rp _ReturnType;
      };

    template<class _Rp, class _Class, class _P0, class _P1>
    struct __member_pointer_traits_imp<_Rp
    (_Class::*)(_P0, _P1) volatile, true, false>
      {
        typedef _Class volatile _ClassType;
        typedef _Rp _ReturnType;
      };

    template<class _Rp, class _Class, class _P0, class _P1, class _P2>
    struct __member_pointer_traits_imp<_Rp
    (_Class::*)(_P0, _P1, _P2) volatile, true, false>
      {
        typedef _Class volatile _ClassType;
        typedef _Rp _ReturnType;
      };

    template<class _Rp, class _Class>
    struct __member_pointer_traits_imp<_Rp
    (_Class::*)() const volatile, true, false>
      {
        typedef _Class const volatile _ClassType;
        typedef _Rp _ReturnType;
      };

    template<class _Rp, class _Class, class _P0>
    struct __member_pointer_traits_imp<_Rp
    (_Class::*)(_P0) const volatile, true, false>
      {
        typedef _Class const volatile _ClassType;
        typedef _Rp _ReturnType;
      };

    template<class _Rp, class _Class, class _P0, class _P1>
    struct __member_pointer_traits_imp<_Rp
    (_Class::*)(_P0, _P1) const volatile, true, false>
      {
        typedef _Class const volatile _ClassType;
        typedef _Rp _ReturnType;
      };

    template<class _Rp, class _Class, class _P0, class _P1, class _P2>
    struct __member_pointer_traits_imp<_Rp
    (_Class::*)(_P0, _P1, _P2) const volatile, true, false>
      {
        typedef _Class const volatile _ClassType;
        typedef _Rp _ReturnType;
      };

#endif  // _LIBCPP_HAS_NO_VARIADICS
    //
template    <class _Rp, class _Class>
    struct __member_pointer_traits_imp<_Rp _Class::*, false, true>
      {
        typedef _Class _ClassType;
        typedef _Rp _ReturnType;
      };

    template<class _MP>
      struct __member_pointer_traits : public __member_pointer_traits_imp<_MP,
          is_member_function_pointer<_MP>::value,
          is_member_object_pointer<_MP>::value>
      {
        //     typedef ... _ClassType;
        //     typedef ... _ReturnType;
      };

    // result_of

    template<class _Callable>
      class result_of;

#ifdef _LIBCPP_HAS_NO_VARIADICS

    template<class _Fn, bool, bool>
    class __result_of
      {
      };

    template<class _Fn>
    class __result_of<_Fn
    (), true, false>
      {
      public:
        typedef decltype(declval<_Fn>()()) type;
      };

    template<class _Fn, class _A0>
    class __result_of<_Fn
    (_A0), true, false>
      {
      public:
        typedef decltype(declval<_Fn>()(declval<_A0>())) type;
      };

    template<class _Fn, class _A0, class _A1>
    class __result_of<_Fn
    (_A0, _A1), true, false>
      {
      public:
        typedef decltype(declval<_Fn>()(declval<_A0>(), declval<_A1>())) type;
      };

    template<class _Fn, class _A0, class _A1, class _A2>
    class __result_of<_Fn
    (_A0, _A1, _A2), true, false>
      {
      public:
        typedef decltype(declval<_Fn>()(declval<_A0>(), declval<_A1>(), declval<_A2>())) type;
      };

    template<class _MP, class _Tp, bool _IsMemberFunctionPtr>
    struct __result_of_mp;

    // member function pointer

    template<class _MP, class _Tp>
    struct __result_of_mp<_MP, _Tp, true> : public common_type<
    typename __member_pointer_traits<_MP>::_ReturnType>
      {
      };

    // member data pointer

    template<class _MP, class _Tp, bool>
    struct __result_of_mdp;

    template<class _Rp, class _Class, class _Tp>
    struct __result_of_mdp<_Rp _Class::*, _Tp, false>
      {
        typedef typename __apply_cv<decltype(*_VSTD::declval<_Tp>()), _Rp>::type& type;
      };

    template<class _Rp, class _Class, class _Tp>
    struct __result_of_mdp<_Rp _Class::*, _Tp, true>
      {
        typedef typename __apply_cv<_Tp, _Rp>::type& type;
      };

    template<class _Rp, class _Class, class _Tp>
    struct __result_of_mp<_Rp _Class::*, _Tp, false> : public __result_of_mdp<
    _Rp _Class::*, _Tp,
    is_base_of<_Class, typename remove_reference<_Tp>::type>::value>
      {
      };

    template<class _Fn, class _Tp>
    class __result_of<_Fn
    (_Tp), false, true>  // _Fn must be member pointer
    : public __result_of_mp<typename remove_reference<_Fn>::type, _Tp,
    is_member_function_pointer<typename remove_reference<_Fn>::type>::value>
      {
      };

    template<class _Fn, class _Tp, class _A0>
    class __result_of<_Fn
    (_Tp, _A0), false, true>  // _Fn must be member pointer
    : public __result_of_mp<typename remove_reference<_Fn>::type, _Tp,
    is_member_function_pointer<typename remove_reference<_Fn>::type>::value>
      {
      };

    template<class _Fn, class _Tp, class _A0, class _A1>
    class __result_of<_Fn
    (_Tp, _A0, _A1), false, true> // _Fn must be member pointer
    : public __result_of_mp<typename remove_reference<_Fn>::type, _Tp,
    is_member_function_pointer<typename remove_reference<_Fn>::type>::value>
      {
      };

    template<class _Fn, class _Tp, class _A0, class _A1, class _A2>
    class __result_of<_Fn
    (_Tp, _A0, _A1, _A2), false, true> // _Fn must be member pointer
    : public __result_of_mp<typename remove_reference<_Fn>::type, _Tp,
    is_member_function_pointer<typename remove_reference<_Fn>::type>::value>
      {
      };

    // result_of

    template<class _Fn>
    class _LIBCPP_VISIBLE result_of<_Fn
    ()> : public __result_of<_Fn
    (),
    is_class<typename remove_reference<_Fn>::type>::value
    || is_function<typename remove_reference<_Fn>::type>::value,
    is_member_pointer<typename remove_reference<_Fn>::type>::value>
      {
      };

    template<class _Fn, class _A0>
    class _LIBCPP_VISIBLE result_of<_Fn
    (_A0)> : public __result_of<_Fn
    (_A0),
    is_class<typename remove_reference<_Fn>::type>::value
    || is_function<typename remove_reference<_Fn>::type>::value,
    is_member_pointer<typename remove_reference<_Fn>::type>::value>
      {
      };

    template<class _Fn, class _A0, class _A1>
    class _LIBCPP_VISIBLE result_of<_Fn
    (_A0, _A1)> : public __result_of<_Fn
    (_A0, _A1),
    is_class<typename remove_reference<_Fn>::type>::value
    || is_function<typename remove_reference<_Fn>::type>::value,
    is_member_pointer<typename remove_reference<_Fn>::type>::value>
      {
      };

    template<class _Fn, class _A0, class _A1, class _A2>
    class _LIBCPP_VISIBLE result_of<_Fn
    (_A0, _A1, _A2)> : public __result_of<_Fn
    (_A0, _A1, _A2),
    is_class<typename remove_reference<_Fn>::type>::value
    || is_function<typename remove_reference<_Fn>::type>::value,
    is_member_pointer<typename remove_reference<_Fn>::type>::value>
      {
      };

#endif  // _LIBCPP_HAS_NO_VARIADICS
#ifndef _LIBCPP_HAS_NO_VARIADICS

// template <class T, class... Args> struct is_constructible;

//      main is_constructible test

    template<typename, typename T>
      struct __select_2nd
      {
        typedef T type;
      };

    template<class _Tp, class ..._Args>
      typename __select_2nd<
          decltype(_VSTD::move(_Tp(_VSTD::declval<_Args>()...))), true_type>::type
      __is_constructible_test(_Tp&&, _Args&& ...);

    template<class ..._Args>
      false_type
      __is_constructible_test(__any, _Args&& ...);

    template<bool, class _Tp, class ... _Args>
      struct __is_constructible // false, _Tp is not a scalar
      : public common_type<
          decltype(__is_constructible_test(declval<_Tp>(), declval<_Args>()...))>::type
      {
      };

    //      function types are not constructible

    template<class _Rp, class ... _A1, class ... _A2>
      struct __is_constructible<false, _Rp
      (_A1...), _A2...> : public false_type
      {
      };

    //      handle scalars and reference types

    //      Scalars are default constructible, references are not

    template<class _Tp>
      struct __is_constructible<true, _Tp> : public is_scalar<_Tp>
      {
      };

    //      Scalars and references are constructible from one arg if that arg is
    //          implicitly convertible to the scalar or reference.

    template<class _Tp>
      struct __is_constructible_ref
      {
        true_type static
        __lxx(_Tp);
        false_type static
        __lxx(...);
      };

    template<class _Tp, class _A0>
      struct __is_constructible<true, _Tp, _A0> : public common_type<
          decltype(__is_constructible_ref<_Tp>::__lxx(declval<_A0>()))>::type
      {
      };

    //      Scalars and references are not constructible from multiple args.

    template<class _Tp, class _A0, class ..._Args>
      struct __is_constructible<true, _Tp, _A0, _Args...> : public false_type
      {
      };

    //      Treat scalars and reference types separately

    template<bool, class _Tp, class ... _Args>
      struct __is_constructible_void_check : public __is_constructible<
          is_scalar<_Tp>::value || is_reference<_Tp>::value, _Tp, _Args...>
      {
      };

    //      If any of T or Args is void, is_constructible should be false

    template<class _Tp, class ... _Args>
      struct __is_constructible_void_check<true, _Tp, _Args...> : public false_type
      {
      };

    template<class ..._Args>
      struct __contains_void;

    template<>
      struct __contains_void<> : false_type
      {
      };

    template<class _A0, class ..._Args>
      struct __contains_void<_A0, _Args...>
      {
        static const bool value = is_void<_A0>::value
            || __contains_void<_Args...>::value;
      };

    //      is_constructible entry point

    template<class _Tp, class ... _Args>
      struct _LIBCPP_VISIBLE is_constructible : public __is_constructible_void_check<
          __contains_void<_Tp, _Args...>::value || is_abstract<_Tp>::value, _Tp,
          _Args...>
      {
      };

    //      Array types are default constructible if their element type
    //      is default constructible

    template<class _Ap, size_t _Np>
      struct __is_constructible<false, _Ap[_Np]> : public is_constructible<
          typename remove_all_extents<_Ap>::type>
      {
      };

    //      Otherwise array types are not constructible by this syntax

    template<class _Ap, size_t _Np, class ..._Args>
      struct __is_constructible<false, _Ap[_Np], _Args...> : public false_type
      {
      };

    //      Incomplete array types are not constructible

    template<class _Ap, class ..._Args>
      struct __is_constructible<false, _Ap[], _Args...> : public false_type
      {
      };

#else  // _LIBCPP_HAS_NO_VARIADICS
    // template <class T> struct is_constructible0;

    //      main is_constructible0 test

    template<class _Tp>
    decltype((_Tp(), true_type()))
    __is_constructible0_test(_Tp&);

    false_type
    __is_constructible0_test(__any);

    template<class _Tp, class _A0>
    decltype((_Tp(_VSTD::declval<_A0>()), true_type()))
    __is_constructible1_test(_Tp&, _A0&);

    template<class _A0>
    false_type
    __is_constructible1_test(__any, _A0&);

    template<class _Tp, class _A0, class _A1>
    decltype((_Tp(_VSTD::declval<_A0>(), _VSTD::declval<_A1>()), true_type()))
    __is_constructible2_test(_Tp&, _A0&, _A1&);

    template<class _A0, class _A1>
    false_type
    __is_constructible2_test(__any, _A0&, _A1&);

    template<bool, class _Tp>
    struct __is_constructible0_imp// false, _Tp is not a scalar
    : public common_type<decltype(__is_constructible0_test(declval<_Tp&>()))
    >::type
      {
      };

    template<bool, class _Tp, class _A0>
    struct __is_constructible1_imp // false, _Tp is not a scalar
    : public common_type<
    decltype(__is_constructible1_test(declval<_Tp&>(), declval<_A0&>()))
    >::type
      {
      };

    template<bool, class _Tp, class _A0, class _A1>
    struct __is_constructible2_imp // false, _Tp is not a scalar
    : public common_type<
    decltype(__is_constructible2_test(declval<_Tp&>(), declval<_A0>(), declval<_A1>()))
    >::type
      {
      };

    //      handle scalars and reference types

    //      Scalars are default constructible, references are not

    template<class _Tp>
    struct __is_constructible0_imp<true, _Tp> : public is_scalar<_Tp>
      {
      };

    template<class _Tp, class _A0>
    struct __is_constructible1_imp<true, _Tp, _A0> : public is_convertible<
    _A0, _Tp>
      {
      };

    template<class _Tp, class _A0, class _A1>
    struct __is_constructible2_imp<true, _Tp, _A0, _A1> : public false_type
      {
      };

    //      Treat scalars and reference types separately

    template<bool, class _Tp>
    struct __is_constructible0_void_check : public __is_constructible0_imp<
    is_scalar<_Tp>::value || is_reference<_Tp>::value, _Tp>
      {
      };

    template<bool, class _Tp, class _A0>
    struct __is_constructible1_void_check : public __is_constructible1_imp<
    is_scalar<_Tp>::value || is_reference<_Tp>::value, _Tp, _A0>
      {
      };

    template<bool, class _Tp, class _A0, class _A1>
    struct __is_constructible2_void_check : public __is_constructible2_imp<
    is_scalar<_Tp>::value || is_reference<_Tp>::value, _Tp, _A0, _A1>
      {
      };

    //      If any of T or Args is void, is_constructible should be false

    template<class _Tp>
    struct __is_constructible0_void_check<true, _Tp> : public false_type
      {
      };

    template<class _Tp, class _A0>
    struct __is_constructible1_void_check<true, _Tp, _A0> : public false_type
      {
      };

    template<class _Tp, class _A0, class _A1>
    struct __is_constructible2_void_check<true, _Tp, _A0, _A1> : public false_type
      {
      };

    //      is_constructible entry point

    namespace __is_construct
      {

        struct __nat
          {
          };

      }

    template<class _Tp, class _A0 = __is_construct:: __nat, class _A1 = __is_construct::__nat>
    struct _LIBCPP_VISIBLE is_constructible
    : public __is_constructible2_void_check<is_void<_Tp>::value
    || is_abstract<_Tp>::value
    || is_function<_Tp>::value
    || is_void<_A0>::value
    || is_void<_A1>::value,
    _Tp, _A0, _A1>
      {};

    template<class _Tp>
    struct _LIBCPP_VISIBLE is_constructible<_Tp,
    __is_construct:: __nat, __is_construct:: __nat> : public __is_constructible0_void_check<is_void<_Tp>::value
    || is_abstract<_Tp>::value
    || is_function<_Tp>::value,
    _Tp>
      {};

    template<class _Tp, class _A0>
    struct _LIBCPP_VISIBLE is_constructible<_Tp, _A0, __is_construct:: __nat> :public __is_constructible1_void_check<is_void<_Tp>::value
    || is_abstract<_Tp>::value
    || is_function<_Tp>::value
    || is_void<_A0>::value,
    _Tp, _A0>
      {};

    //      Array types are default constructible if their element type
    //      is default constructible

    template<class _Ap, size_t _Np>
    struct __is_constructible0_imp<false, _Ap[_Np]> : public is_constructible<
    typename remove_all_extents<_Ap>::type>
      {
      };

    template<class _Ap, size_t _Np, class _A0>
    struct __is_constructible1_imp<false, _Ap[_Np], _A0> : public false_type
      {
      };

    template<class _Ap, size_t _Np, class _A0, class _A1>
    struct __is_constructible2_imp<false, _Ap[_Np], _A0, _A1> : public false_type
      {
      };

    //      Incomplete array types are not constructible

    template<class _Ap>
    struct __is_constructible0_imp<false, _Ap[]> : public false_type
      {
      };

    template<class _Ap, class _A0>
    struct __is_constructible1_imp<false, _Ap[], _A0> : public false_type
      {
      };

    template<class _Ap, class _A0, class _A1>
    struct __is_constructible2_imp<false, _Ap[], _A0, _A1> : public false_type
      {
      };

#endif  // _LIBCPP_HAS_NO_VARIADICS
    // is_default_constructible

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_default_constructible : public is_constructible<
          _Tp>
      {
      };

    // is_copy_constructible

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_copy_constructible : public is_constructible<
          _Tp, const typename add_lvalue_reference<_Tp>::type>
      {
      };

    // is_move_constructible

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_move_constructible
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
          : public is_constructible<_Tp,
          typename add_rvalue_reference<_Tp>::type>
#else
          : public is_copy_constructible<_Tp>
#endif
      {
      };

    // is_trivially_constructible

#ifndef _LIBCPP_HAS_NO_VARIADICS

#if __has_feature(is_trivially_constructible)

    template <class _Tp, class... _Args>
    struct _LIBCPP_VISIBLE is_trivially_constructible
    : integral_constant<bool, __is_trivially_constructible(_Tp, _Args...)>
      {
      };

#else  // !__has_feature(is_trivially_constructible)
template    <class _Tp, class... _Args>
    struct _LIBCPP_VISIBLE is_trivially_constructible
    : false_type
      {
      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_trivially_constructible<_Tp>
#if __has_feature(has_trivial_constructor) || (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)
          : integral_constant<bool, __has_trivial_constructor(_Tp)>
#else
          : integral_constant<bool, is_scalar<_Tp>::value>
#endif
      {
      };

    template<class _Tp>
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
      struct _LIBCPP_VISIBLE is_trivially_constructible<_Tp, _Tp&&>
#else
      struct _LIBCPP_VISIBLE is_trivially_constructible<_Tp, _Tp>
#endif
          : integral_constant<bool, is_scalar<_Tp>::value>
      {
      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_trivially_constructible<_Tp, const _Tp&> : integral_constant<
          bool, is_scalar<_Tp>::value>
      {
      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_trivially_constructible<_Tp, _Tp&> : integral_constant<
          bool, is_scalar<_Tp>::value>
      {
      };

#endif  // !__has_feature(is_trivially_constructible)
#else  // _LIBCPP_HAS_NO_VARIADICS
    template<class _Tp, class _A0 = __is_construct:: __nat, class _A1 = __is_construct::__nat>
    struct _LIBCPP_VISIBLE is_trivially_constructible
    : false_type
      {
      };

#if __has_feature(is_trivially_constructible)

    template <class _Tp>
    struct _LIBCPP_VISIBLE is_trivially_constructible<_Tp, __is_construct::__nat,
    __is_construct::__nat>
    : integral_constant<bool, __is_trivially_constructible(_Tp)>
      {
      };

    template <class _Tp>
    struct _LIBCPP_VISIBLE is_trivially_constructible<_Tp, _Tp,
    __is_construct::__nat>
    : integral_constant<bool, __is_trivially_constructible(_Tp, _Tp)>
      {
      };

    template <class _Tp>
    struct _LIBCPP_VISIBLE is_trivially_constructible<_Tp, const _Tp&,
    __is_construct::__nat>
    : integral_constant<bool, __is_trivially_constructible(_Tp, const _Tp&)>
      {
      };

    template <class _Tp>
    struct _LIBCPP_VISIBLE is_trivially_constructible<_Tp, _Tp&,
    __is_construct::__nat>
    : integral_constant<bool, __is_trivially_constructible(_Tp, _Tp&)>
      {
      };

#else  // !__has_feature(is_trivially_constructible)
    template<class _Tp>
    struct _LIBCPP_VISIBLE is_trivially_constructible<_Tp,
    __is_construct:: __nat, __is_construct:: __nat> : integral_constant<bool, is_scalar<_Tp>::value>
      {
      };

    template<class _Tp>
    struct _LIBCPP_VISIBLE is_trivially_constructible<_Tp, _Tp,
    __is_construct:: __nat> : integral_constant<bool, is_scalar<_Tp>::value>
      {
      };

    template<class _Tp>
    struct _LIBCPP_VISIBLE is_trivially_constructible<_Tp, const _Tp&,
    __is_construct:: __nat> : integral_constant<bool, is_scalar<_Tp>::value>
      {
      };

    template<class _Tp>
    struct _LIBCPP_VISIBLE is_trivially_constructible<_Tp, _Tp&,
    __is_construct:: __nat> : integral_constant<bool, is_scalar<_Tp>::value>
      {
      };

#endif  // !__has_feature(is_trivially_constructible)
#endif  // _LIBCPP_HAS_NO_VARIADICS
    // is_trivially_default_constructible

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_trivially_default_constructible : public is_trivially_constructible<
          _Tp>
      {
      };

    // is_trivially_copy_constructible

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_trivially_copy_constructible : public is_trivially_constructible<
          _Tp, const typename add_lvalue_reference<_Tp>::type>
      {
      };

    // is_trivially_move_constructible

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_trivially_move_constructible
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
          : public is_trivially_constructible<_Tp,
          typename add_rvalue_reference<_Tp>::type>
#else
          : public is_trivially_copy_constructible<_Tp>
#endif
      {
      };

    // is_trivially_assignable

#if __has_feature(is_trivially_constructible)

    template <class _Tp, class _Arg>
    struct is_trivially_assignable
    : integral_constant<bool, __is_trivially_assignable(_Tp, _Arg)>
      {
      };

#else  // !__has_feature(is_trivially_constructible)
template    <class _Tp, class _Arg>
    struct is_trivially_assignable
    : public false_type
      {};

    template<class _Tp>
      struct is_trivially_assignable<_Tp&, _Tp> : integral_constant<bool,
          is_scalar<_Tp>::value>
      {
      };

    template<class _Tp>
      struct is_trivially_assignable<_Tp&, _Tp&> : integral_constant<bool,
          is_scalar<_Tp>::value>
      {
      };

    template<class _Tp>
      struct is_trivially_assignable<_Tp&, const _Tp&> : integral_constant<bool,
          is_scalar<_Tp>::value>
      {
      };

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

    template<class _Tp>
    struct is_trivially_assignable<_Tp&, _Tp&&>
    : integral_constant<bool, is_scalar<_Tp>::value>
      {};

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
#endif  // !__has_feature(is_trivially_constructible)
    // is_trivially_copy_assignable

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_trivially_copy_assignable : public is_trivially_assignable<
          typename add_lvalue_reference<_Tp>::type,
          const typename add_lvalue_reference<_Tp>::type>
      {
      };

    // is_trivially_move_assignable

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_trivially_move_assignable : public is_trivially_assignable<
          typename add_lvalue_reference<_Tp>::type,
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
          typename add_rvalue_reference<_Tp>::type>
#else
          typename add_lvalue_reference<_Tp>::type>
#endif
      {
      };

    // is_trivially_destructible

#if __has_feature(has_trivial_destructor) || (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)

    template <class _Tp> struct _LIBCPP_VISIBLE is_trivially_destructible
    : public integral_constant<bool, __has_trivial_destructor(_Tp)>
      {};

#else  // _LIBCPP_HAS_TYPE_TRAITS
template    <class _Tp> struct __libcpp_trivial_destructor
    : public integral_constant<bool, is_scalar<_Tp>::value ||
    is_reference<_Tp>::value>
      {};

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_trivially_destructible : public __libcpp_trivial_destructor<
          typename remove_all_extents<_Tp>::type>
      {
      };

#endif  // _LIBCPP_HAS_TYPE_TRAITS
    // is_nothrow_constructible

#ifndef _LIBCPP_HAS_NO_VARIADICS

#if __has_feature(cxx_noexcept)

    template <bool, class _Tp, class... _Args> struct __is_nothrow_constructible;

    template <class _Tp, class... _Args>
    struct __is_nothrow_constructible<true, _Tp, _Args...>
    : public integral_constant<bool, noexcept(_Tp(declval<_Args>()...))>
      {
      };

    template <class _Tp, class... _Args>
    struct __is_nothrow_constructible<false, _Tp, _Args...>
    : public false_type
      {
      };

    template <class _Tp, class... _Args>
    struct _LIBCPP_VISIBLE is_nothrow_constructible
    : __is_nothrow_constructible<is_constructible<_Tp, _Args...>::value, _Tp, _Args...>
      {
      };

    template <class _Tp, size_t _Ns>
    struct _LIBCPP_VISIBLE is_nothrow_constructible<_Tp[_Ns]>
    : __is_nothrow_constructible<is_constructible<_Tp>::value, _Tp>
      {
      };

#else  // __has_feature(cxx_noexcept)
template    <class _Tp, class... _Args>
    struct _LIBCPP_VISIBLE is_nothrow_constructible
    : false_type
      {
      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_nothrow_constructible<_Tp>
#if __has_feature(has_nothrow_constructor) || (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)
          : integral_constant<bool, __has_nothrow_constructor(_Tp)>
#else
          : integral_constant<bool, is_scalar<_Tp>::value>
#endif
      {
      };

    template<class _Tp>
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
      struct _LIBCPP_VISIBLE is_nothrow_constructible<_Tp, _Tp&&>
#else
      struct _LIBCPP_VISIBLE is_nothrow_constructible<_Tp, _Tp>
#endif
#if __has_feature(has_nothrow_copy) || (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)
          : integral_constant<bool, __has_nothrow_copy(_Tp)>
#else
          : integral_constant<bool, is_scalar<_Tp>::value>
#endif
      {
      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_nothrow_constructible<_Tp, const _Tp&>
#if __has_feature(has_nothrow_copy) || (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)
          : integral_constant<bool, __has_nothrow_copy(_Tp)>
#else
          : integral_constant<bool, is_scalar<_Tp>::value>
#endif
      {
      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_nothrow_constructible<_Tp, _Tp&>
#if __has_feature(has_nothrow_copy) || (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)
          : integral_constant<bool, __has_nothrow_copy(_Tp)>
#else
          : integral_constant<bool, is_scalar<_Tp>::value>
#endif
      {
      };

#endif  // __has_feature(cxx_noexcept)
#else  // _LIBCPP_HAS_NO_VARIADICS
    template<class _Tp, class _A0 = __is_construct:: __nat, class _A1 = __is_construct::__nat>
    struct _LIBCPP_VISIBLE is_nothrow_constructible
    : false_type
      {
      };

    template<class _Tp>
    struct _LIBCPP_VISIBLE is_nothrow_constructible<_Tp,
    __is_construct:: __nat, __is_construct:: __nat>
#if __has_feature(has_nothrow_constructor) || (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)
    : integral_constant<bool, __has_nothrow_constructor(_Tp)>
#else
    : integral_constant<bool, is_scalar<_Tp>::value>
#endif
      {
      };

    template<class _Tp>
    struct _LIBCPP_VISIBLE is_nothrow_constructible<_Tp, _Tp,
    __is_construct:: __nat>
#if __has_feature(has_nothrow_copy) || (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)
    : integral_constant<bool, __has_nothrow_copy(_Tp)>
#else
    : integral_constant<bool, is_scalar<_Tp>::value>
#endif
      {
      };

    template<class _Tp>
    struct _LIBCPP_VISIBLE is_nothrow_constructible<_Tp, const _Tp&,
    __is_construct:: __nat>
#if __has_feature(has_nothrow_copy) || (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)
    : integral_constant<bool, __has_nothrow_copy(_Tp)>
#else
    : integral_constant<bool, is_scalar<_Tp>::value>
#endif
      {
      };

    template<class _Tp>
    struct _LIBCPP_VISIBLE is_nothrow_constructible<_Tp, _Tp&,
    __is_construct:: __nat>
#if __has_feature(has_nothrow_copy) || (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)
    : integral_constant<bool, __has_nothrow_copy(_Tp)>
#else
    : integral_constant<bool, is_scalar<_Tp>::value>
#endif
      {
      };

#endif  // _LIBCPP_HAS_NO_VARIADICS
    // is_nothrow_default_constructible

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_nothrow_default_constructible : public is_nothrow_constructible<
          _Tp>
      {
      };

    // is_nothrow_copy_constructible

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_nothrow_copy_constructible : public is_nothrow_constructible<
          _Tp, const typename add_lvalue_reference<_Tp>::type>
      {
      };

    // is_nothrow_move_constructible

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_nothrow_move_constructible
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
          : public is_nothrow_constructible<_Tp,
          typename add_rvalue_reference<_Tp>::type>
#else
          : public is_nothrow_copy_constructible<_Tp>
#endif
      {
      };

    // is_nothrow_assignable

#if __has_feature(cxx_noexcept)

    template <bool, class _Tp, class _Arg> struct __is_nothrow_assignable;

    template <class _Tp, class _Arg>
    struct __is_nothrow_assignable<false, _Tp, _Arg>
    : public false_type
      {
      };

    template <class _Tp, class _Arg>
    struct __is_nothrow_assignable<true, _Tp, _Arg>
    : public integral_constant<bool, noexcept(_VSTD::declval<_Tp>() = _VSTD::declval<_Arg>()) >
      {
      };

    template <class _Tp, class _Arg>
    struct _LIBCPP_VISIBLE is_nothrow_assignable
    : public __is_nothrow_assignable<is_assignable<_Tp, _Arg>::value, _Tp, _Arg>
      {
      };

#else  // __has_feature(cxx_noexcept)
template    <class _Tp, class _Arg>
    struct _LIBCPP_VISIBLE is_nothrow_assignable
    : public false_type
      {};

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_nothrow_assignable<_Tp&, _Tp>
#if __has_feature(has_nothrow_assign) || (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)
          : integral_constant<bool, __has_nothrow_assign(_Tp)>
            {};
#else
          : integral_constant<bool, is_scalar<_Tp>::value>
      {
      };
#endif

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_nothrow_assignable<_Tp&, _Tp&>
#if __has_feature(has_nothrow_assign) || (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)
          : integral_constant<bool, __has_nothrow_assign(_Tp)>
            {};
#else
          : integral_constant<bool, is_scalar<_Tp>::value>
      {
      };
#endif

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_nothrow_assignable<_Tp&, const _Tp&>
#if __has_feature(has_nothrow_assign) || (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)
          : integral_constant<bool, __has_nothrow_assign(_Tp)>
            {};
#else
          : integral_constant<bool, is_scalar<_Tp>::value>
      {
      };
#endif

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

    template<class _Tp>
    struct is_nothrow_assignable<_Tp&, _Tp&&>
#if __has_feature(has_nothrow_assign) || (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)
    : integral_constant<bool, __has_nothrow_assign(_Tp)>
      {};
#else
    : integral_constant<bool, is_scalar<_Tp>::value>
      {};
#endif

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
#endif  // __has_feature(cxx_noexcept)
    // is_nothrow_copy_assignable

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_nothrow_copy_assignable : public is_nothrow_assignable<
          typename add_lvalue_reference<_Tp>::type,
          const typename add_lvalue_reference<_Tp>::type>
      {
      };

    // is_nothrow_move_assignable

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_nothrow_move_assignable : public is_nothrow_assignable<
          typename add_lvalue_reference<_Tp>::type,
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
          typename add_rvalue_reference<_Tp>::type>
#else
          typename add_lvalue_reference<_Tp>::type>
#endif
      {
      };

    // is_nothrow_destructible

#if __has_feature(cxx_noexcept)

    template <bool, class _Tp> struct __is_nothrow_destructible;

    template <class _Tp>
    struct __is_nothrow_destructible<false, _Tp>
    : public false_type
      {
      };

    template <class _Tp>
    struct __is_nothrow_destructible<true, _Tp>
    : public integral_constant<bool, noexcept(_VSTD::declval<_Tp>().~_Tp()) >
      {
      };

    template <class _Tp>
    struct _LIBCPP_VISIBLE is_nothrow_destructible
    : public __is_nothrow_destructible<is_destructible<_Tp>::value, _Tp>
      {
      };

    template <class _Tp, size_t _Ns>
    struct _LIBCPP_VISIBLE is_nothrow_destructible<_Tp[_Ns]>
    : public is_nothrow_destructible<_Tp>
      {
      };

    template <class _Tp>
    struct _LIBCPP_VISIBLE is_nothrow_destructible<_Tp&>
    : public true_type
      {
      };

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

    template <class _Tp>
    struct _LIBCPP_VISIBLE is_nothrow_destructible<_Tp&&>
    : public true_type
      {
      };

#endif

#else

template    <class _Tp> struct __libcpp_nothrow_destructor
    : public integral_constant<bool, is_scalar<_Tp>::value ||
    is_reference<_Tp>::value>
      {};

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_nothrow_destructible : public __libcpp_nothrow_destructor<
          typename remove_all_extents<_Tp>::type>
      {
      };

#endif

    // is_pod

//#if __has_feature(is_pod) || (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

    template <class _Tp> struct _LIBCPP_VISIBLE is_pod
    : public integral_constant<bool, __is_pod(_Tp)>
      {};

#else  // _LIBCPP_HAS_TYPE_TRAITS
    template<class _Tp>
      struct _LIBCPP_VISIBLE is_pod : public integral_constant<bool,
          is_trivially_default_constructible<_Tp>::value
              && is_trivially_copy_constructible<_Tp>::value
              && is_trivially_copy_assignable<_Tp>::value
              && is_trivially_destructible<_Tp>::value>
      {
      };

#endif  // _LIBCPP_HAS_TYPE_TRAITS
    // is_literal_type;

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_literal_type
#if __has_feature(is_literal)
          : public integral_constant<bool, __is_literal(_Tp)>
#else
          : integral_constant<bool,
              is_scalar<typename remove_all_extents<_Tp>::type>::value
                  || is_reference<typename remove_all_extents<_Tp>::type>::value>
#endif
      {
      };

    // is_standard_layout;

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_standard_layout
#if __has_feature(is_standard_layout)
          : public integral_constant<bool, __is_standard_layout(_Tp)>
#else
          : integral_constant<bool,
              is_scalar<typename remove_all_extents<_Tp>::type>::value>
#endif
      {
      };

    // is_trivially_copyable;

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_trivially_copyable
#if __has_feature(is_trivially_copyable)
          : public integral_constant<bool, __is_trivially_copyable(_Tp)>
#else
          : integral_constant<bool,
              is_scalar<typename remove_all_extents<_Tp>::type>::value>
#endif
      {
      };

    // is_trivial;

    template<class _Tp>
      struct _LIBCPP_VISIBLE is_trivial
#if __has_feature(is_trivial)
          : public integral_constant<bool, __is_trivial(_Tp)>
#else
          : integral_constant<bool,
              is_trivially_copyable<_Tp>::value
                  && is_trivially_default_constructible<_Tp>::value>
#endif
      {
      };

#ifndef _LIBCPP_HAS_NO_VARIADICS

    // Check for complete types

    template<class ..._Tp>
      struct __check_complete;

    template<>
      struct __check_complete<>
      {
      };

    template<class _Hp, class _T0, class ..._Tp>
      struct __check_complete<_Hp, _T0, _Tp...> : private __check_complete<_Hp>,
          private __check_complete<_T0, _Tp...>
      {
      };

    template<class _Hp>
      struct __check_complete<_Hp, _Hp> : private __check_complete<_Hp>
      {
      };

    template<class _Tp>
      struct __check_complete<_Tp>
      {
        static_assert(sizeof(_Tp) > 0, "Type must be complete.");
      };

    template<class _Tp>
      struct __check_complete<_Tp&> : private __check_complete<_Tp>
      {
      };

    template<class _Tp>
      struct __check_complete<_Tp&&>
      : private __check_complete<_Tp>
        {
        };

    template<class _Rp, class ..._Param>
      struct __check_complete<_Rp
      (*)(_Param...)> : private __check_complete<_Rp>
      {
      };

    template<class _Rp, class ..._Param>
      struct __check_complete<_Rp
      (_Param...)> : private __check_complete<_Rp>
      {
      };

    template<class _Rp, class _Class, class ..._Param>
      struct __check_complete<_Rp
      (_Class::*)(_Param...)> : private __check_complete<_Class>
      {
      };

    template<class _Rp, class _Class, class ..._Param>
      struct __check_complete<_Rp
      (_Class::*)(_Param...) const> : private __check_complete<_Class>
      {
      };

    template<class _Rp, class _Class, class ..._Param>
      struct __check_complete<_Rp
      (_Class::*)(_Param...) volatile> : private __check_complete<_Class>
      {
      };

    template<class _Rp, class _Class, class ..._Param>
      struct __check_complete<_Rp
      (_Class::*)(_Param...) const volatile> : private __check_complete<_Class>
      {
      };

#if __has_feature(cxx_reference_qualified_functions)

    template <class _Rp, class _Class, class ..._Param>
    struct __check_complete<_Rp (_Class::*)(_Param...) &>
    : private __check_complete<_Class>
      {
      };

    template <class _Rp, class _Class, class ..._Param>
    struct __check_complete<_Rp (_Class::*)(_Param...) const&>
    : private __check_complete<_Class>
      {
      };

    template <class _Rp, class _Class, class ..._Param>
    struct __check_complete<_Rp (_Class::*)(_Param...) volatile&>
    : private __check_complete<_Class>
      {
      };

    template <class _Rp, class _Class, class ..._Param>
    struct __check_complete<_Rp (_Class::*)(_Param...) const volatile&>
    : private __check_complete<_Class>
      {
      };

    template <class _Rp, class _Class, class ..._Param>
    struct __check_complete<_Rp (_Class::*)(_Param...) &&>
    : private __check_complete<_Class>
      {
      };

    template <class _Rp, class _Class, class ..._Param>
    struct __check_complete<_Rp (_Class::*)(_Param...) const&&>
    : private __check_complete<_Class>
      {
      };

    template <class _Rp, class _Class, class ..._Param>
    struct __check_complete<_Rp (_Class::*)(_Param...) volatile&&>
    : private __check_complete<_Class>
      {
      };

    template <class _Rp, class _Class, class ..._Param>
    struct __check_complete<_Rp (_Class::*)(_Param...) const volatile&&>
    : private __check_complete<_Class>
      {
      };

#endif

template    <class _Rp, class _Class>
    struct __check_complete<_Rp _Class::*>
    : private __check_complete<_Class>
      {
      };

    // __invoke forward declarations

    // fall back - none of the bullets

    template<class ..._Args>
      auto
      __invoke(__any, _Args&& ...__args)
      -> __nat;

      // bullets 1 and 2

    template<class _Fp, class _A0, class ..._Args>
      _LIBCPP_INLINE_VISIBILITY
      auto
      __invoke(_Fp&& __f, _A0&& __a0, _Args&& ...__args)
      -> decltype((_VSTD::forward<_A0>(__a0).*__f)(_VSTD::forward<_Args>(__args)...));

    template<class _Fp, class _A0, class ..._Args>
      _LIBCPP_INLINE_VISIBILITY
      auto
      __invoke(_Fp&& __f, _A0&& __a0, _Args&& ...__args)
      -> decltype(((*_VSTD::forward<_A0>(__a0)).*__f)(_VSTD::forward<_Args>(__args)...));

      // bullets 3 and 4

    template<class _Fp, class _A0>
      _LIBCPP_INLINE_VISIBILITY
      auto
      __invoke(_Fp&& __f, _A0&& __a0)
      -> decltype(_VSTD::forward<_A0>(__a0).*__f);

    template<class _Fp, class _A0>
      _LIBCPP_INLINE_VISIBILITY
      auto
      __invoke(_Fp&& __f, _A0&& __a0)
      -> decltype((*_VSTD::forward<_A0>(__a0)).*__f);

      // bullet 5

    template<class _Fp, class ..._Args>
      _LIBCPP_INLINE_VISIBILITY
      auto
      __invoke(_Fp&& __f, _Args&& ...__args)
      -> decltype(_VSTD::forward<_Fp>(__f)(_VSTD::forward<_Args>(__args)...));

      // __invokable

    template<class _Fp, class ..._Args>
      struct __invokable_imp : private __check_complete<_Fp>
      {
        typedef decltype(
            __invoke(_VSTD::declval<_Fp>(), _VSTD::declval<_Args>()...)
        ) type;
        static const bool value = !is_same<type, __nat >::value;
      }
    ;

    template<class _Fp, class ..._Args>
      struct __invokable : public integral_constant<bool,
          __invokable_imp<_Fp, _Args...>::value>
      {
      };

    // __invoke_of

    template<bool _Invokable, class _Fp, class ..._Args>
      struct __invoke_of_imp // false
      {
      };

    template<class _Fp, class ..._Args>
      struct __invoke_of_imp<true, _Fp, _Args...>
      {
        typedef typename __invokable_imp<_Fp, _Args...>::type type;
      };

    template<class _Fp, class ..._Args>
      struct __invoke_of : public __invoke_of_imp<
          __invokable<_Fp, _Args...>::value, _Fp, _Args...>
      {
      };

    template<class _Fp, class ..._Args>
      class _LIBCPP_VISIBLE result_of<_Fp
      (_Args...)> : public __invoke_of<_Fp, _Args...>
      {
      };

#endif  // _LIBCPP_HAS_NO_VARIADICS
    template<class _Tp>
      inline _LIBCPP_INLINE_VISIBILITY
#ifndef _LIBCPP_HAS_NO_ADVANCED_SFINAE
      typename enable_if
      <
      is_move_constructible<_Tp>::value &&
      is_move_assignable<_Tp>::value
      >::type
#else
      void
#endif
      swap(_Tp& __x, _Tp& __y) _NOEXCEPT_(is_nothrow_move_constructible<_Tp>::value &&
          is_nothrow_move_assignable<_Tp>::value)
      {
        _Tp __t(_VSTD::move(__x));
        __x = _VSTD::move(__y);
        __y = _VSTD::move(__t);
      }

    template<class _ForwardIterator1, class _ForwardIterator2>
      inline _LIBCPP_INLINE_VISIBILITY
      void
      iter_swap(_ForwardIterator1 __a, _ForwardIterator2 __b)
      //                                  _NOEXCEPT_(_NOEXCEPT_(swap(*__a, *__b)))
      _NOEXCEPT_(_NOEXCEPT_(swap(*_VSTD::declval<_ForwardIterator1>(),
                  *_VSTD::declval<_ForwardIterator2>())))
      {
        swap(*__a, *__b);
      }

    // __swappable

#if !defined(__DOXYGEN__)
    namespace __detail
    {

      using _VSTD::swap;
      __nat
      swap(__any, __any);

      template<class _Tp>
        struct __swappable
        {
          typedef decltype(swap(_VSTD::declval<_Tp&>(), _VSTD::declval<_Tp&>())) type;
          static const bool value = !is_same<type, __nat >::value;
        };

    }  // __detail
#endif

    template<class _Tp>
      struct __is_swappable : public integral_constant<bool,
          __detail::__swappable<_Tp>::value>
      {
      };

#if __has_feature(cxx_noexcept)

    template <bool, class _Tp>
    struct __is_nothrow_swappable_imp
    : public integral_constant<bool, noexcept(swap(_VSTD::declval<_Tp&>(),
            _VSTD::declval<_Tp&>()))>
      {
      };

    template <class _Tp>
    struct __is_nothrow_swappable_imp<false, _Tp>
    : public false_type
      {
      };

    template <class _Tp>
    struct __is_nothrow_swappable
    : public __is_nothrow_swappable_imp<__is_swappable<_Tp>::value, _Tp>
      {
      };

#else  // __has_feature(cxx_noexcept)
template    <class _Tp>
    struct __is_nothrow_swappable
    : public false_type
      {
      };

#endif  // __has_feature(cxx_noexcept)
#ifdef _LIBCXX_UNDERLYING_TYPE

    template <class _Tp>
    struct underlying_type
      {
        typedef _LIBCXX_UNDERLYING_TYPE(_Tp) type;
      };

#else  // _LIBCXX_UNDERLYING_TYPE
    template<class _Tp, bool _Support = false>
      struct underlying_type
      {
        static_assert(_Support, "The underyling_type trait requires compiler "
            "support. Either no such support exists or "
            "libc++ does not know how to use it.");
      };

#endif // _LIBCXX_UNDERLYING_TYPE
#define _CREATE_ALIGNED_STORAGE_SPECIALIZATION(n) \
template <size_t _Len>\
struct _LIBCPP_VISIBLE aligned_storage<_Len, n>\
{\
    struct _ALIGNAS(n) type\
    {\
        unsigned char __lx[_Len];\
    };\
}

    _CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x1);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION    (0x2);
    _CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x4);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION    (0x8);
    _CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x10);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION    (0x20);
    _CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x40);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION    (0x80);
    _CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x100);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION    (0x200);
    _CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x400);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION    (0x800);
    _CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x1000);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION    (0x2000);
// MSDN says that MSVC does not support alignment beyond 8192 (=0x2000)
#if !defined(_MSC_VER)
    _CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x4000);
#endif // !_MSC_VER
#undef _CREATE_ALIGNED_STORAGE_SPECIALIZATION

#endif

}  }

#endif  /* OS_PORTABLE_LANGUAGE_CPP_INCLUDE_TYPE_TRAITS_H_ */
