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
/// \brief I/O stream base.

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INTERNAL_FUNCTIONALBASE_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INTERNAL_FUNCTIONALBASE_H_

#include "portable/core/include/ConfigDefines.h"

#include "portable/language/cpp/include/internal/__config.h"
#include "portable/language/cpp/include/type_traits.h"
//#include "portable/language/cpp/include/typeinfo"
#include "portable/language/cpp/include/exception.h"

namespace os
{
  namespace std
  {

    template<class _Arg, class _Result>
      struct unary_function
      {
        typedef _Arg argument_type;
        typedef _Result result_type;
      };

    template<class _Arg1, class _Arg2, class _Result>
      struct binary_function
      {
        typedef _Arg1 first_argument_type;
        typedef _Arg2 second_argument_type;
        typedef _Result result_type;
      };

    template<class _Tp>
      struct hash;

    template<class _Tp>
      struct __has_result_type
      {
      private:
        struct __two
        {
          char __lx;
          char __lxx;
        };
        template<class _Up>
          static __two         __test(...);
template          <class _Up> static char __test(typename _Up::result_type* = 0);
        public:
          static const bool value = sizeof(__test<_Tp>(0)) == 1;
        };

    template<class _Tp>
      struct less : binary_function<_Tp, _Tp, bool>
      {
        __attribute__((always_inline)) bool
        operator()(const _Tp& __x, const _Tp& __y) const
        {
          return __x < __y;
        }
      };

#ifdef _LIBCPP_HAS_NO_VARIADICS

#include <__functional_base_03>

#else  // _LIBCPP_HAS_NO_VARIADICS
    // __weak_result_type

    template<class _Tp>
      struct __derives_from_unary_function
      {
      private:
        struct __two
        {
          char __lx;
          char __lxx;
        };
        static __two  __test(...);    //
template        <class _Ap, class _Rp>
        static unary_function<_Ap, _Rp>
        __test(const volatile unary_function<_Ap, _Rp>*);
      public:
        static const bool value = !is_same<decltype(__test((_Tp*)0)), __two>::value;
        typedef decltype(__test((_Tp*)0)) type;
      };

    template<class _Tp>
      struct __derives_from_binary_function
      {
      private:
        struct __two
        {
          char __lx;
          char __lxx;
        };
        static __two         __test(...);
template        <class _A1, class _A2, class _Rp>
        static binary_function<_A1, _A2, _Rp>
        __test(const volatile binary_function<_A1, _A2, _Rp>*);
      public:
        static const bool value = !is_same<decltype(__test((_Tp*)0)), __two>::value;
        typedef decltype(__test((_Tp*)0)) type;
      };

    template<class _Tp, bool = __derives_from_unary_function<_Tp>::value>
      struct __maybe_derive_from_unary_function  // bool is true
      : public __derives_from_unary_function<_Tp>::type
      {
      };

    template<class _Tp>
      struct __maybe_derive_from_unary_function<_Tp, false>
      {
      };

    template<class _Tp, bool = __derives_from_binary_function<_Tp>::value>
      struct __maybe_derive_from_binary_function  // bool is true
      : public __derives_from_binary_function<_Tp>::type
      {
      };

    template<class _Tp>
      struct __maybe_derive_from_binary_function<_Tp, false>
      {
      };

    template<class _Tp, bool = __has_result_type<_Tp>::value>
      struct __weak_result_type_imp // bool is true
      : public __maybe_derive_from_unary_function<_Tp>,
          public __maybe_derive_from_binary_function<_Tp>
      {
        typedef typename _Tp::result_type result_type;
      };

    template<class _Tp>
      struct __weak_result_type_imp<_Tp, false> : public __maybe_derive_from_unary_function<
          _Tp>,
          public __maybe_derive_from_binary_function<_Tp>
      {
      };

    template<class _Tp>
      struct __weak_result_type : public __weak_result_type_imp<_Tp>
      {
      };

    // 0 argument case

    template<class _Rp>
      struct __weak_result_type<_Rp
      ()>
      {
        typedef _Rp result_type;
      };

    template<class _Rp>
      struct __weak_result_type<_Rp
      (&)()>
      {
        typedef _Rp result_type;
      };

    template<class _Rp>
      struct __weak_result_type<_Rp
      (*)()>
      {
        typedef _Rp result_type;
      };

    // 1 argument case

    template<class _Rp, class _A1>
      struct __weak_result_type<_Rp
      (_A1)> : public unary_function<_A1, _Rp>
      {
      };

    template<class _Rp, class _A1>
      struct __weak_result_type<_Rp
      (&)(_A1)> : public unary_function<_A1, _Rp>
      {
      };

    template<class _Rp, class _A1>
      struct __weak_result_type<_Rp
      (*)(_A1)> : public unary_function<_A1, _Rp>
      {
      };

    template<class _Rp, class _Cp>
      struct __weak_result_type<_Rp
      (_Cp::*)()> : public unary_function<_Cp*, _Rp>
      {
      };

    template<class _Rp, class _Cp>
      struct __weak_result_type<_Rp
      (_Cp::*)() const> : public unary_function<const _Cp*, _Rp>
      {
      };

    template<class _Rp, class _Cp>
      struct __weak_result_type<_Rp
      (_Cp::*)() volatile> : public unary_function<volatile _Cp*, _Rp>
      {
      };

    template<class _Rp, class _Cp>
      struct __weak_result_type<_Rp
      (_Cp::*)() const volatile> : public unary_function<const volatile _Cp*,
          _Rp>
      {
      };

    // 2 argument case

    template<class _Rp, class _A1, class _A2>
      struct __weak_result_type<_Rp
      (_A1, _A2)> : public binary_function<_A1, _A2, _Rp>
      {
      };

    template<class _Rp, class _A1, class _A2>
      struct __weak_result_type<_Rp
      (*)(_A1, _A2)> : public binary_function<_A1, _A2, _Rp>
      {
      };

    template<class _Rp, class _A1, class _A2>
      struct __weak_result_type<_Rp
      (&)(_A1, _A2)> : public binary_function<_A1, _A2, _Rp>
      {
      };

    template<class _Rp, class _Cp, class _A1>
      struct __weak_result_type<_Rp
      (_Cp::*)(_A1)> : public binary_function<_Cp*, _A1, _Rp>
      {
      };

    template<class _Rp, class _Cp, class _A1>
      struct __weak_result_type<_Rp
      (_Cp::*)(_A1) const> : public binary_function<const _Cp*, _A1, _Rp>
      {
      };

    template<class _Rp, class _Cp, class _A1>
      struct __weak_result_type<_Rp
      (_Cp::*)(_A1) volatile> : public binary_function<volatile _Cp*, _A1, _Rp>
      {
      };

    template<class _Rp, class _Cp, class _A1>
      struct __weak_result_type<_Rp
      (_Cp::*)(_A1) const volatile> : public binary_function<
          const volatile _Cp*, _A1, _Rp>
      {
      };

    // 3 or more arguments

    template<class _Rp, class _A1, class _A2, class _A3, class ..._A4>
      struct __weak_result_type<_Rp
      (_A1, _A2, _A3, _A4...)>
      {
        typedef _Rp result_type;
      };

    template<class _Rp, class _A1, class _A2, class _A3, class ..._A4>
      struct __weak_result_type<_Rp
      (&)(_A1, _A2, _A3, _A4...)>
      {
        typedef _Rp result_type;
      };

    template<class _Rp, class _A1, class _A2, class _A3, class ..._A4>
      struct __weak_result_type<_Rp
      (*)(_A1, _A2, _A3, _A4...)>
      {
        typedef _Rp result_type;
      };

    template<class _Rp, class _Cp, class _A1, class _A2, class ..._A3>
      struct __weak_result_type<_Rp
      (_Cp::*)(_A1, _A2, _A3...)>
      {
        typedef _Rp result_type;
      };

    template<class _Rp, class _Cp, class _A1, class _A2, class ..._A3>
      struct __weak_result_type<_Rp
      (_Cp::*)(_A1, _A2, _A3...) const>
      {
        typedef _Rp result_type;
      };

    template<class _Rp, class _Cp, class _A1, class _A2, class ..._A3>
      struct __weak_result_type<_Rp
      (_Cp::*)(_A1, _A2, _A3...) volatile>
      {
        typedef _Rp result_type;
      };

    template<class _Rp, class _Cp, class _A1, class _A2, class ..._A3>
      struct __weak_result_type<_Rp
      (_Cp::*)(_A1, _A2, _A3...) const volatile>
      {
        typedef _Rp result_type;
      };

    // __invoke

    // bullets 1 and 2

    template<class _Fp, class _A0, class ..._Args>
      inline __attribute__((always_inline))
      auto
      __invoke(_Fp&& __f, _A0&& __a0,
          _Args&& ...__args)
          -> decltype((os::std::forward<_A0>(__a0).*__f)(os::std::forward<_Args>(__args)...))
      {
        return (os::std::forward<_A0>(__a0).*__f)(
            os::std::forward<_Args>(__args)...);
      }

    template<class _Fp, class _A0, class ..._Args>
      inline __attribute__((always_inline))
      auto
      __invoke(_Fp&& __f, _A0&& __a0,
          _Args&& ...__args)
          -> decltype(((*os::std::forward<_A0>(__a0)).*__f)(os::std::forward<_Args>(__args)...))
      {
        return ((*os::std::forward<_A0>(__a0)).*__f)(
            os::std::forward<_Args>(__args)...);
      }

    // bullets 3 and 4

    template<class _Fp, class _A0>
      inline __attribute__((always_inline))
      auto
      __invoke(_Fp&& __f, _A0&& __a0)
      -> decltype(os::std::forward<_A0>(__a0).*__f)
      {
        return os::std::forward<_A0>(__a0).*__f;
      }

    template<class _Fp, class _A0>
      inline __attribute__((always_inline))
      auto
      __invoke(_Fp&& __f, _A0&& __a0)
      -> decltype((*os::std::forward<_A0>(__a0)).*__f)
      {
        return (*os::std::forward<_A0>(__a0)).*__f;
      }

// bullet 5

    template<class _Fp, class ..._Args>
      inline __attribute__((always_inline))
      auto
      __invoke(_Fp&& __f,
          _Args&& ...__args)
          -> decltype(os::std::forward<_Fp>(__f)(os::std::forward<_Args>(__args)...))
      {
        return os::std::forward<_Fp>(__f)(os::std::forward<_Args>(__args)...);
      }

    template<class _Tp, class ..._Args>
      struct __invoke_return
      {
        typedef decltype(__invoke(os::std::declval<_Tp>(), os::std::declval<_Args>()...)) type;
      };

    template<class _Tp>
      class reference_wrapper : public __weak_result_type<_Tp>
      {
      public:
        // types
        typedef _Tp type;
      private:
        type* __f_;

      public:
        // construct/copy/destroy
        __attribute__((always_inline))
        reference_wrapper(type& __f)
noexcept            : __f_(&__f)
              {}
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
          private: reference_wrapper(type&&); public: // = delete; // do not bind to temps
#endif

            // access
            __attribute__((always_inline)) operator type& () const noexcept
              { return *__f_;}
            __attribute__((always_inline)) type& get() const noexcept
              { return *__f_;}

            // invoke
            template <class... _ArgTypes>
            __attribute__((always_inline))
            typename __invoke_of<type&, _ArgTypes...>::type
            operator() (_ArgTypes&&... __args) const
              {
                return __invoke(get(), os::std::forward<_ArgTypes>(__args)...);
              }
          };

    template<class _Tp>
      struct ____is_reference_wrapper : public false_type
      {
      };
    template<class _Tp>
      struct ____is_reference_wrapper<reference_wrapper<_Tp> > : public true_type
      {
      };
    template<class _Tp>
      struct __is_reference_wrapper : public ____is_reference_wrapper<
          typename remove_cv<_Tp>::type>
      {
      };

    template<class _Tp>
      inline __attribute__((always_inline))
       reference_wrapper<_Tp>
      ref(_Tp& __t) noexcept
      {
        return reference_wrapper<_Tp>(__t);
      }

    template<class _Tp>
      inline __attribute__((always_inline))
       reference_wrapper<_Tp>
      ref(reference_wrapper<_Tp> __t) noexcept
      {
        return ref(__t.get());
      }

    template<class _Tp>
      inline __attribute__((always_inline))
       reference_wrapper<const _Tp>
      cref(const _Tp& __t) noexcept
      {
        return reference_wrapper<const _Tp>(__t);
      }

    template<class _Tp>
      inline __attribute__((always_inline))
       reference_wrapper<const _Tp>
      cref(reference_wrapper<_Tp> __t) noexcept
      {
        return cref(__t.get());
      }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
#ifndef _LIBCPP_HAS_NO_DELETED_FUNCTIONS

  template <class _Tp> void ref(const _Tp&&) = delete;
  template <class _Tp> void cref(const _Tp&&) = delete;

#else  // _LIBCPP_HAS_NO_DELETED_FUNCTIONS
  template <class _Tp> void ref(const _Tp&&); // = delete;
  template <class _Tp> void cref(const _Tp&&);// = delete;

#endif  // _LIBCPP_HAS_NO_DELETED_FUNCTIONS
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
#endif  // _LIBCPP_HAS_NO_VARIADICS
}
 // namespace std
}// namespace os

#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INTERNAL_FUNCTIONALBASE_H_
