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
/// \brief Utility definitions.

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_UTILITY_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_UTILITY_H_

#include "portable/core/include/ConfigDefines.h"

#include "portable/language/cpp/include/internal/__config.h"
//#include "portable/language/cpp/include/__tuple.h"
#include "portable/language/cpp/include/type_traits.h"

namespace os
{
  namespace std
  {

    namespace rel_ops
    {

      template<class _Tp>
        inline __attribute__((always_inline))
        bool
        operator!=(const _Tp& __x, const _Tp& __y)
        {
          return !(__x == __y);
        }

      template<class _Tp>
        inline __attribute__((always_inline))
        bool
        operator>(const _Tp& __x, const _Tp& __y)
        {
          return __y < __x;
        }

      template<class _Tp>
        inline __attribute__((always_inline))
        bool
        operator<=(const _Tp& __x, const _Tp& __y)
        {
          return !(__y < __x);
        }

      template<class _Tp>
        inline __attribute__((always_inline))
        bool
        operator>=(const _Tp& __x, const _Tp& __y)
        {
          return !(__x < __y);
        }

    }  // rel_ops

    // swap_ranges

    template<class _ForwardIterator1, class _ForwardIterator2>
      inline __attribute__((always_inline))
      _ForwardIterator2
      swap_ranges(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
          _ForwardIterator2 __first2)
      {
        for (; __first1 != __last1; ++__first1, ++__first2)
          swap(*__first1, *__first2);
        return __first2;
      }

    template<class _Tp, size_t _Np>
      inline __attribute__((always_inline))
      void
      swap(_Tp (&__a)[_Np], _Tp (&__b)[_Np])
      noexcept (__is_nothrow_swappable<_Tp>::value)
      {
        os::std::swap_ranges(__a, __a + _Np, __b);
      }

    template<class _Tp>
      inline __attribute__((always_inline))
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
      typename conditional
      <
      !is_nothrow_move_constructible<_Tp>::value && is_copy_constructible<_Tp>::value,
      const _Tp&,
      _Tp&&
      >::type
#else  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
      const _Tp&
#endif
      move_if_noexcept(_Tp& __x) noexcept
      {
        return os::std::move(__x);
      }

    struct _LIBCPP_VISIBLE piecewise_construct_t
    {
    };
#if defined(_LIBCPP_HAS_NO_CONSTEXPR) || defined(_LIBCPP_BUILDING_UTILITY)
    extern const piecewise_construct_t piecewise_construct; // = piecewise_construct_t();
#else
    constexpr piecewise_construct_t piecewise_construct =
        piecewise_construct_t();
#endif

    template<class _T1, class _T2>
      struct _LIBCPP_VISIBLE pair
      {
        typedef _T1 first_type;
        typedef _T2 second_type;

        _T1 first;
        _T2 second;

        // pair(const pair&) = default;
        // pair(pair&&) = default;

        __attribute__((always_inline)) constexpr
        pair()
            : first(), second()
        {
        }

        __attribute__((always_inline))
        pair(const _T1& __x, const _T2& __y)
            : first(__x), second(__y)
        {
        }

        template<class _U1, class _U2>
          __attribute__((always_inline))
          pair(const pair<_U1, _U2>& __p
#ifndef _LIBCPP_HAS_NO_ADVANCED_SFINAE
              ,typename enable_if<is_convertible<const _U1&, _T1>::value &&
              is_convertible<const _U2&, _T2>::value>::type* = 0
#endif
              )
              : first(__p.first), second(__p.second)
          {
          }

        __attribute__((always_inline))
        pair(const pair& __p)
        noexcept (is_nothrow_copy_constructible<first_type>::value &&
            is_nothrow_copy_constructible<second_type>::value)
            : first(__p.first), second(__p.second)
        {
        }

        __attribute__((always_inline))
        pair&
        operator=(const pair& __p)
        noexcept (is_nothrow_copy_assignable<first_type>::value &&
            is_nothrow_copy_assignable<second_type>::value)
        {
          first = __p.first;
          second = __p.second;
          return *this;
        }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

        template <class _U1, class _U2,
        class = typename enable_if<is_convertible<_U1, first_type>::value &&
        is_convertible<_U2, second_type>::value>::type>
        __attribute__((always_inline))
        pair(_U1&& __u1, _U2&& __u2)
        : first(os::std::forward<_U1>(__u1)),
        second(os::std::forward<_U2>(__u2))
          {}

        template<class _U1, class _U2>
        __attribute__((always_inline))
        pair(pair<_U1, _U2>&& __p,
            typename enable_if<is_convertible<_U1, _T1>::value &&
            is_convertible<_U2, _T2>::value>::type* = 0)
        : first(os::std::forward<_U1>(__p.first)),
        second(os::std::forward<_U2>(__p.second))
          {}

        __attribute__((always_inline))
        pair(pair&& __p) noexcept (is_nothrow_move_constructible<first_type>::value &&
            is_nothrow_move_constructible<second_type>::value)
        : first(os::std::forward<first_type>(__p.first)),
        second(os::std::forward<second_type>(__p.second))
          {
          }

        __attribute__((always_inline))
        pair&
        operator=(pair&& __p) noexcept (is_nothrow_move_assignable<first_type>::value &&
            is_nothrow_move_assignable<second_type>::value)
          {
            first = os::std::forward<first_type>(__p.first);
            second = os::std::forward<second_type>(__p.second);
            return *this;
          }

#ifndef _LIBCPP_HAS_NO_VARIADICS

        template<class _Tuple,
        class = typename enable_if<__tuple_convertible<_Tuple, pair>::value>::type>
        __attribute__((always_inline))
        pair(_Tuple&& __p)
        : first(os::std::forward<typename tuple_element<0,
            typename __make_tuple_types<_Tuple>::type>::type>(get<0>(__p))),
        second(os::std::forward<typename tuple_element<1,
            typename __make_tuple_types<_Tuple>::type>::type>(get<1>(__p)))
          {}

        template <class... _Args1, class... _Args2>
        __attribute__((always_inline))
        pair(piecewise_construct_t __pc, tuple<_Args1...> __first_args,
            tuple<_Args2...> __second_args)
        : pair(__pc, __first_args, __second_args,
            typename __make_tuple_indices<sizeof...(_Args1)>::type(),
            typename __make_tuple_indices<sizeof...(_Args2) >::type())
          {}

        template <class _Tuple,
        class = typename enable_if<__tuple_assignable<_Tuple, pair>::value>::type>
        __attribute__((always_inline))
        pair&
        operator=(_Tuple&& __p)
          {
            typedef typename __make_tuple_types<_Tuple>::type _TupleRef;
            typedef typename tuple_element<0, _TupleRef>::type _U0;
            typedef typename tuple_element<1, _TupleRef>::type _U1;
            first = os::std::forward<_U0>(os::std::get<0>(__p));
            second = os::std::forward<_U1>(os::std::get<1>(__p));
            return *this;
          }

#endif  // _LIBCPP_HAS_NO_VARIADICS
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
        __attribute__((always_inline))
        void
        swap(pair& __p) noexcept (__is_nothrow_swappable<first_type>::value &&
            __is_nothrow_swappable<second_type>::value)
        {
          os::std::iter_swap(&first, &__p.first);
          os::std::iter_swap(&second, &__p.second);
        }
      private:

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

#ifndef _LIBCPP_HAS_NO_VARIADICS
        template <class... _Args1, class... _Args2, size_t... _I1, size_t... _I2>
        __attribute__((always_inline))
        pair(piecewise_construct_t,
            tuple<_Args1...>& __first_args, tuple<_Args2...>& __second_args,
            __tuple_indices<_I1...>, __tuple_indices<_I2...>);
#endif  // _LIBCPP_HAS_NO_VARIADICS
#endif
      };

    template<class _T1, class _T2>
      inline __attribute__((always_inline))
      bool
      operator==(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
      {
        return __x.first == __y.first && __x.second == __y.second;
      }

    template<class _T1, class _T2>
      inline __attribute__((always_inline))
      bool
      operator!=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
      {
        return !(__x == __y);
      }

    template<class _T1, class _T2>
      inline __attribute__((always_inline))
      bool
      operator<(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
      {
        return __x.first < __y.first
            || (!(__y.first < __x.first) && __x.second < __y.second);
      }

    template<class _T1, class _T2>
      inline __attribute__((always_inline))
      bool
      operator>(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
      {
        return __y < __x;
      }

    template<class _T1, class _T2>
      inline __attribute__((always_inline))
      bool
      operator>=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
      {
        return !(__x < __y);
      }

    template<class _T1, class _T2>
      inline __attribute__((always_inline))
      bool
      operator<=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
      {
        return !(__y < __x);
      }

    template<class _T1, class _T2>
      inline __attribute__((always_inline))
      typename enable_if
      <
      __is_swappable<_T1>::value &&
      __is_swappable<_T2>::value,
      void
      >::type
      swap(pair<_T1, _T2>& __x, pair<_T1, _T2>& __y)
      noexcept ((__is_nothrow_swappable<_T1>::value &&
              __is_nothrow_swappable<_T2>::value))
        {
          __x.swap(__y);
        }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

      template <class _Tp> class _LIBCPP_VISIBLE reference_wrapper;

      template <class _Tp>
      struct ___make_pair_return
        {
          typedef _Tp type;
        };

      template <class _Tp>
      struct ___make_pair_return<reference_wrapper<_Tp>>
        {
          typedef _Tp& type;
        };

      template <class _Tp>
      struct __make_pair_return
        {
          typedef typename ___make_pair_return<typename decay<_Tp>::type>::type type;
        };

      template <class _T1, class _T2>
      inline __attribute__((always_inline))
      pair<typename __make_pair_return<_T1>::type, typename __make_pair_return<_T2>::type>
      make_pair(_T1&& __t1, _T2&& __t2)
        {
          return pair<typename __make_pair_return<_T1>::type, typename __make_pair_return<_T2>::type>
          (os::std::forward<_T1>(__t1), os::std::forward<_T2>(__t2));
        }

#else  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
    template<class _T1, class _T2>
      inline __attribute__((always_inline))
      pair<_T1, _T2>
      make_pair(_T1 __x, _T2 __y)
      {
        return pair<_T1, _T2>(__x, __y);
      }

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

  template <class _T1, class _T2>
  class _LIBCPP_VISIBLE tuple_size<pair<_T1, _T2> >
  : public integral_constant<size_t, 2>
    {};

  template <class _T1, class _T2>
  class _LIBCPP_VISIBLE tuple_size<const pair<_T1, _T2> >
  : public integral_constant<size_t, 2>
    {};

  template <class _T1, class _T2>
  class _LIBCPP_VISIBLE tuple_element<0, pair<_T1, _T2> >
    {
    public:
      typedef _T1 type;
    };

  template <class _T1, class _T2>
  class _LIBCPP_VISIBLE tuple_element<1, pair<_T1, _T2> >
    {
    public:
      typedef _T2 type;
    };

  template <class _T1, class _T2>
  class _LIBCPP_VISIBLE tuple_element<0, const pair<_T1, _T2> >
    {
    public:
      typedef const _T1 type;
    };

  template <class _T1, class _T2>
  class _LIBCPP_VISIBLE tuple_element<1, const pair<_T1, _T2> >
    {
    public:
      typedef const _T2 type;
    };

  template <size_t _Ip> struct __get_pair;

  template <>
  struct __get_pair<0>
    {
      template <class _T1, class _T2>
      static
      __attribute__((always_inline))
      _T1&
      get(pair<_T1, _T2>& __p) noexcept
        { return __p.first;}

      template <class _T1, class _T2>
      static
      __attribute__((always_inline))
      const _T1&
      get(const pair<_T1, _T2>& __p) noexcept
        { return __p.first;}

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

      template <class _T1, class _T2>
      static
      __attribute__((always_inline))
      _T1&&
      get(pair<_T1, _T2>&& __p) noexcept
        { return os::std::forward<_T1>(__p.first);}

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
    };

  template <>
  struct __get_pair<1>
    {
      template <class _T1, class _T2>
      static
      __attribute__((always_inline))
      _T2&
      get(pair<_T1, _T2>& __p) noexcept
        { return __p.second;}

      template <class _T1, class _T2>
      static
      __attribute__((always_inline))
      const _T2&
      get(const pair<_T1, _T2>& __p) noexcept
        { return __p.second;}

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

      template <class _T1, class _T2>
      static
      __attribute__((always_inline))
      _T2&&
      get(pair<_T1, _T2>&& __p) noexcept
        { return os::std::forward<_T2>(__p.second);}

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
    };

  template <size_t _Ip, class _T1, class _T2>
  __attribute__((always_inline)) inline
  typename tuple_element<_Ip, pair<_T1, _T2> >::type&
  get(pair<_T1, _T2>& __p) noexcept
    {
      return __get_pair<_Ip>::get(__p);
    }

  template <size_t _Ip, class _T1, class _T2>
  __attribute__((always_inline)) inline
  const typename tuple_element<_Ip, pair<_T1, _T2> >::type&
  get(const pair<_T1, _T2>& __p) noexcept
    {
      return __get_pair<_Ip>::get(__p);
    }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

  template <size_t _Ip, class _T1, class _T2>
  __attribute__((always_inline)) inline
  typename tuple_element<_Ip, pair<_T1, _T2> >::type&&
  get(pair<_T1, _T2>&& __p) noexcept
    {
      return __get_pair<_Ip>::get(os::std::move(__p));
    }

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
#endif

}
        // namespace std
}       // namespace os

#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_UTILITY_H_
