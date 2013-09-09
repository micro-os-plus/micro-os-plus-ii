//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//
// [Partly inspired from the LLVM libcxx sources].
// Copyright (c) 2009-2013 by the contributors listed in
// 'LLVM libcxx Credits.txt'. See 'LLVM libcxx License.txt' for details.
//

/// \file
/// \brief Memory definitions.

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_MEMORY_H
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_MEMORY_H

#include "portable/language/cpp/include/internal/__config.h"
#include "portable/language/cpp/include/cstdlib.h"

#include "portable/language/cpp/include/type_traits.h"
#include "portable/language/cpp/include/typeinfo.h"
#include "portable/language/cpp/include/cstddef.h"
#include "portable/language/cpp/include/cstdint.h"
#include "portable/language/cpp/include/new.h"
#include "portable/language/cpp/include/utility.h"
#include "portable/language/cpp/include/limits.h"
#include "portable/language/cpp/include/iterator.h"
#include "portable/language/cpp/include/internal/_functional_base.h"
//#include "portable/language/cpp/include/iosfwd"
//#include "portable/language/cpp/include/tuple"
#include "portable/language/cpp/include/cstring.h"
#if !defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
#include "portable/language/cpp/include/cassert.h"
#endif

#if __has_feature(cxx_atomic)
//#  include "portable/language/cpp/include/atomic"
#endif

//#include "portable/language/cpp/include/__undef_min_max.h"

namespace os
  {
    namespace std
      {

        // addressof

        template <class _Tp>
        inline _Tp*
        __attribute__((always_inline))
        addressof(_Tp& __x) noexcept
          {
            return (_Tp*)&(char&)__x;
          }

#if defined(_LIBCPP_HAS_OBJC_ARC) && !defined(_LIBCPP_PREDEFINED_OBJC_ARC_ADDRESSOF)
// Objective-C++ Automatic Reference Counting uses qualified pointers
// that require special addressof() signatures. When
// _LIBCPP_PREDEFINED_OBJC_ARC_ADDRESSOF is defined, the compiler
// itself is providing these definitions. Otherwise, we provide them.
        template <class _Tp>
        inline __attribute__((always_inline))
        __strong _Tp*
        addressof(__strong _Tp& __x) noexcept
          {
            return &__x;
          }

#ifdef _LIBCPP_HAS_OBJC_ARC_WEAK
        template <class _Tp>
        inline __attribute__((always_inline))
        __weak _Tp*
        addressof(__weak _Tp& __x) noexcept
          {
            return &__x;
          }
#endif

        template <class _Tp>
        inline __attribute__((always_inline))
        __autoreleasing _Tp*
        addressof(__autoreleasing _Tp& __x) noexcept
          {
            return &__x;
          }

        template <class _Tp>
        inline __attribute__((always_inline))
        __unsafe_unretained _Tp*
        addressof(__unsafe_unretained _Tp& __x) noexcept
          {
            return &__x;
          }
#endif

        template <class _Tp> class allocator;

        template <>
        class allocator<void>
          {
          public:
            typedef void* pointer;
            typedef const void* const_pointer;
            typedef void value_type;

            template <class _Up> struct rebind
              { typedef allocator<_Up> other;};
          };

        template <>
        class allocator<const void>
          {
          public:
            typedef const void* pointer;
            typedef const void* const_pointer;
            typedef const void value_type;

            template <class _Up> struct rebind
              { typedef allocator<_Up> other;};
          };

        // pointer_traits

        template <class _Tp>
        struct __has_element_type
          {
          private:
            struct __two
              { char __lx; char __lxx;};
            template <class _Up> static __two __test(...);
            template <class _Up> static char __test(typename _Up::element_type* = 0);
          public:
            static const bool value = sizeof(__test<_Tp>(0)) == 1;
          };

        template <class _Ptr, bool = __has_element_type<_Ptr>::value>
        struct __pointer_traits_element_type;

        template <class _Ptr>
        struct __pointer_traits_element_type<_Ptr, true>
          {
            typedef typename _Ptr::element_type type;
          };

#ifndef _LIBCPP_HAS_NO_VARIADICS

        template <template <class, class...> class _Sp, class _Tp, class ..._Args>
        struct __pointer_traits_element_type<_Sp<_Tp, _Args...>, true>
          {
            typedef typename _Sp<_Tp, _Args...>::element_type type;
          };

        template <template <class, class...> class _Sp, class _Tp, class ..._Args>
        struct __pointer_traits_element_type<_Sp<_Tp, _Args...>, false>
          {
            typedef _Tp type;
          };

#else  // _LIBCPP_HAS_NO_VARIADICS
        template <template <class> class _Sp, class _Tp>
        struct __pointer_traits_element_type<_Sp<_Tp>, true>
          {
            typedef typename _Sp<_Tp>::element_type type;
          };

        template <template <class> class _Sp, class _Tp>
        struct __pointer_traits_element_type<_Sp<_Tp>, false>
          {
            typedef _Tp type;
          };

        template <template <class, class> class _Sp, class _Tp, class _A0>
        struct __pointer_traits_element_type<_Sp<_Tp, _A0>, true>
          {
            typedef typename _Sp<_Tp, _A0>::element_type type;
          };

        template <template <class, class> class _Sp, class _Tp, class _A0>
        struct __pointer_traits_element_type<_Sp<_Tp, _A0>, false>
          {
            typedef _Tp type;
          };

        template <template <class, class, class> class _Sp, class _Tp, class _A0, class _A1>
        struct __pointer_traits_element_type<_Sp<_Tp, _A0, _A1>, true>
          {
            typedef typename _Sp<_Tp, _A0, _A1>::element_type type;
          };

        template <template <class, class, class> class _Sp, class _Tp, class _A0, class _A1>
        struct __pointer_traits_element_type<_Sp<_Tp, _A0, _A1>, false>
          {
            typedef _Tp type;
          };

        template <template <class, class, class, class> class _Sp, class _Tp, class _A0,
        class _A1, class _A2>
        struct __pointer_traits_element_type<_Sp<_Tp, _A0, _A1, _A2>, true>
          {
            typedef typename _Sp<_Tp, _A0, _A1, _A2>::element_type type;
          };

        template <template <class, class, class, class> class _Sp, class _Tp, class _A0,
        class _A1, class _A2>
        struct __pointer_traits_element_type<_Sp<_Tp, _A0, _A1, _A2>, false>
          {
            typedef _Tp type;
          };

#endif  // _LIBCPP_HAS_NO_VARIADICS
        template <class _Tp>
        struct __has_difference_type
          {
          private:
            struct __two
              { char __lx; char __lxx;};
            template <class _Up> static __two __test(...);
            template <class _Up> static char __test(typename _Up::difference_type* = 0);
          public:
            static const bool value = sizeof(__test<_Tp>(0)) == 1;
          };

        template <class _Ptr, bool = __has_difference_type<_Ptr>::value>
        struct __pointer_traits_difference_type
          {
            typedef ptrdiff_t type;
          };

        template <class _Ptr>
        struct __pointer_traits_difference_type<_Ptr, true>
          {
            typedef typename _Ptr::difference_type type;
          };

        template <class _Tp, class _Up>
        struct __has_rebind
          {
          private:
            struct __two
              { char __lx; char __lxx;};
            template <class _Xp> static __two __test(...);
            template <class _Xp> static char __test(typename _Xp::template rebind<_Up>* = 0);
          public:
            static const bool value = sizeof(__test<_Tp>(0)) == 1;
          };

        template <class _Tp, class _Up, bool = __has_rebind<_Tp, _Up>::value>
        struct __pointer_traits_rebind
          {
#ifndef _LIBCPP_HAS_NO_TEMPLATE_ALIASES
            typedef typename _Tp::template rebind<_Up> type;
#else
            typedef typename _Tp::template rebind<_Up>::other type;
#endif
          };

#ifndef _LIBCPP_HAS_NO_VARIADICS

        template <template <class, class...> class _Sp, class _Tp, class ..._Args, class _Up>
        struct __pointer_traits_rebind<_Sp<_Tp, _Args...>, _Up, true>
          {
#ifndef _LIBCPP_HAS_NO_TEMPLATE_ALIASES
            typedef typename _Sp<_Tp, _Args...>::template rebind<_Up> type;
#else
            typedef typename _Sp<_Tp, _Args...>::template rebind<_Up>::other type;
#endif
          };

        template <template <class, class...> class _Sp, class _Tp, class ..._Args, class _Up>
        struct __pointer_traits_rebind<_Sp<_Tp, _Args...>, _Up, false>
          {
            typedef _Sp<_Up, _Args...> type;
          };

#else  // _LIBCPP_HAS_NO_VARIADICS
        template <template <class> class _Sp, class _Tp, class _Up>
        struct __pointer_traits_rebind<_Sp<_Tp>, _Up, true>
          {
#ifndef _LIBCPP_HAS_NO_TEMPLATE_ALIASES
            typedef typename _Sp<_Tp>::template rebind<_Up> type;
#else
            typedef typename _Sp<_Tp>::template rebind<_Up>::other type;
#endif
          };

        template <template <class> class _Sp, class _Tp, class _Up>
        struct __pointer_traits_rebind<_Sp<_Tp>, _Up, false>
          {
            typedef _Sp<_Up> type;
          };

        template <template <class, class> class _Sp, class _Tp, class _A0, class _Up>
        struct __pointer_traits_rebind<_Sp<_Tp, _A0>, _Up, true>
          {
#ifndef _LIBCPP_HAS_NO_TEMPLATE_ALIASES
            typedef typename _Sp<_Tp, _A0>::template rebind<_Up> type;
#else
            typedef typename _Sp<_Tp, _A0>::template rebind<_Up>::other type;
#endif
          };

        template <template <class, class> class _Sp, class _Tp, class _A0, class _Up>
        struct __pointer_traits_rebind<_Sp<_Tp, _A0>, _Up, false>
          {
            typedef _Sp<_Up, _A0> type;
          };

        template <template <class, class, class> class _Sp, class _Tp, class _A0,
        class _A1, class _Up>
        struct __pointer_traits_rebind<_Sp<_Tp, _A0, _A1>, _Up, true>
          {
#ifndef _LIBCPP_HAS_NO_TEMPLATE_ALIASES
            typedef typename _Sp<_Tp, _A0, _A1>::template rebind<_Up> type;
#else
            typedef typename _Sp<_Tp, _A0, _A1>::template rebind<_Up>::other type;
#endif
          };

        template <template <class, class, class> class _Sp, class _Tp, class _A0,
        class _A1, class _Up>
        struct __pointer_traits_rebind<_Sp<_Tp, _A0, _A1>, _Up, false>
          {
            typedef _Sp<_Up, _A0, _A1> type;
          };

        template <template <class, class, class, class> class _Sp, class _Tp, class _A0,
        class _A1, class _A2, class _Up>
        struct __pointer_traits_rebind<_Sp<_Tp, _A0, _A1, _A2>, _Up, true>
          {
#ifndef _LIBCPP_HAS_NO_TEMPLATE_ALIASES
            typedef typename _Sp<_Tp, _A0, _A1, _A2>::template rebind<_Up> type;
#else
            typedef typename _Sp<_Tp, _A0, _A1, _A2>::template rebind<_Up>::other type;
#endif
          };

        template <template <class, class, class, class> class _Sp, class _Tp, class _A0,
        class _A1, class _A2, class _Up>
        struct __pointer_traits_rebind<_Sp<_Tp, _A0, _A1, _A2>, _Up, false>
          {
            typedef _Sp<_Up, _A0, _A1, _A2> type;
          };

#endif  // _LIBCPP_HAS_NO_VARIADICS
        template <class _Ptr>
        struct pointer_traits
          {
            typedef _Ptr pointer;
            typedef typename __pointer_traits_element_type<pointer>::type element_type;
            typedef typename __pointer_traits_difference_type<pointer>::type difference_type;

#ifndef _LIBCPP_HAS_NO_TEMPLATE_ALIASES
            template <class _Up> using rebind = typename __pointer_traits_rebind<pointer, _Up>::type;
#else
            template <class _Up> struct rebind
              { typedef typename __pointer_traits_rebind<pointer, _Up>::type other;};
#endif  // _LIBCPP_HAS_NO_TEMPLATE_ALIASES
          private:
            struct __nat
              {};
          public:
            __attribute__((always_inline))
            static pointer pointer_to(typename conditional<is_void<element_type>::value,
                __nat, element_type>::type& __r)
              { return pointer::pointer_to(__r);}
          };

        template <class _Tp>
        struct pointer_traits<_Tp*>
          {
            typedef _Tp* pointer;
            typedef _Tp element_type;
            typedef ptrdiff_t difference_type;

#ifndef _LIBCPP_HAS_NO_TEMPLATE_ALIASES
            template <class _Up> using rebind = _Up*;
#else
            template <class _Up> struct rebind
              { typedef _Up* other;};
#endif

          private:
            struct __nat
              {};
          public:
            __attribute__((always_inline))
            static pointer pointer_to(typename conditional<is_void<element_type>::value,
                __nat, element_type>::type& __r) noexcept
              { return os::std::addressof(__r);}
          };

// allocator_traits

        namespace __has_pointer_type_imp
          {
            template <class _Up> static __two test(...);
            template <class _Up> static char test(typename _Up::pointer* = 0);
          }

        template <class _Tp>
        struct __has_pointer_type
        : public integral_constant<bool, sizeof(__has_pointer_type_imp::test<_Tp>(0)) == 1>
          {
          };

        namespace __pointer_type_imp
          {

            template <class _Tp, class _Dp, bool = __has_pointer_type<_Dp>::value>
            struct __pointer_type
              {
                typedef typename _Dp::pointer type;
              };

            template <class _Tp, class _Dp>
            struct __pointer_type<_Tp, _Dp, false>
              {
                typedef _Tp* type;
              };

          }  // __pointer_type_imp

        template <class _Tp, class _Dp>
        struct __pointer_type
          {
            typedef typename __pointer_type_imp::__pointer_type<_Tp, typename remove_reference<_Dp>::type>::type type;
          };

        template <class _Tp>
        struct __has_const_pointer
          {
          private:
            struct __two
              { char __lx; char __lxx;};
            template <class _Up> static __two __test(...);
            template <class _Up> static char __test(typename _Up::const_pointer* = 0);
          public:
            static const bool value = sizeof(__test<_Tp>(0)) == 1;
          };

        template <class _Tp, class _Ptr, class _Alloc, bool = __has_const_pointer<_Alloc>::value>
        struct __const_pointer
          {
            typedef typename _Alloc::const_pointer type;
          };

        template <class _Tp, class _Ptr, class _Alloc>
        struct __const_pointer<_Tp, _Ptr, _Alloc, false>
          {
#ifndef _LIBCPP_HAS_NO_TEMPLATE_ALIASES
            typedef typename pointer_traits<_Ptr>::template rebind<const _Tp> type;
#else
            typedef typename pointer_traits<_Ptr>::template rebind<const _Tp>::other type;
#endif
          };

        template <class _Tp>
        struct __has_void_pointer
          {
          private:
            struct __two
              { char __lx; char __lxx;};
            template <class _Up> static __two __test(...);
            template <class _Up> static char __test(typename _Up::void_pointer* = 0);
          public:
            static const bool value = sizeof(__test<_Tp>(0)) == 1;
          };

        template <class _Ptr, class _Alloc, bool = __has_void_pointer<_Alloc>::value>
        struct __void_pointer
          {
            typedef typename _Alloc::void_pointer type;
          };

        template <class _Ptr, class _Alloc>
        struct __void_pointer<_Ptr, _Alloc, false>
          {
#ifndef _LIBCPP_HAS_NO_TEMPLATE_ALIASES
            typedef typename pointer_traits<_Ptr>::template rebind<void> type;
#else
            typedef typename pointer_traits<_Ptr>::template rebind<void>::other type;
#endif
          };

        template <class _Tp>
        struct __has_const_void_pointer
          {
          private:
            struct __two
              { char __lx; char __lxx;};
            template <class _Up> static __two __test(...);
            template <class _Up> static char __test(typename _Up::const_void_pointer* = 0);
          public:
            static const bool value = sizeof(__test<_Tp>(0)) == 1;
          };

        template <class _Ptr, class _Alloc, bool = __has_const_void_pointer<_Alloc>::value>
        struct __const_void_pointer
          {
            typedef typename _Alloc::const_void_pointer type;
          };

        template <class _Ptr, class _Alloc>
        struct __const_void_pointer<_Ptr, _Alloc, false>
          {
#ifndef _LIBCPP_HAS_NO_TEMPLATE_ALIASES
            typedef typename pointer_traits<_Ptr>::template rebind<const void> type;
#else
            typedef typename pointer_traits<_Ptr>::template rebind<const void>::other type;
#endif
          };

        template <class _Tp>
        inline __attribute__((always_inline))
        _Tp*
        __to_raw_pointer(_Tp* __p) noexcept
          {
            return __p;
          }

        template <class _Pointer>
        inline __attribute__((always_inline))
        typename pointer_traits<_Pointer>::element_type*
        __to_raw_pointer(_Pointer __p) noexcept
          {
            return os::std::__to_raw_pointer(__p.operator->());
          }

        template <class _Tp>
        struct __has_size_type
          {
          private:
            struct __two
              { char __lx; char __lxx;};
            template <class _Up> static __two __test(...);
            template <class _Up> static char __test(typename _Up::size_type* = 0);
          public:
            static const bool value = sizeof(__test<_Tp>(0)) == 1;
          };

        template <class _Alloc, class _DiffType, bool = __has_size_type<_Alloc>::value>
        struct __size_type
          {
            typedef typename make_unsigned<_DiffType>::type type;
          };

        template <class _Alloc, class _DiffType>
        struct __size_type<_Alloc, _DiffType, true>
          {
            typedef typename _Alloc::size_type type;
          };

        template <class _Tp>
        struct __has_propagate_on_container_copy_assignment
          {
          private:
            struct __two
              { char __lx; char __lxx;};
            template <class _Up> static __two __test(...);
            template <class _Up> static char __test(typename _Up::propagate_on_container_copy_assignment* = 0);
          public:
            static const bool value = sizeof(__test<_Tp>(0)) == 1;
          };

        template <class _Alloc, bool = __has_propagate_on_container_copy_assignment<_Alloc>::value>
        struct __propagate_on_container_copy_assignment
          {
            typedef false_type type;
          };

        template <class _Alloc>
        struct __propagate_on_container_copy_assignment<_Alloc, true>
          {
            typedef typename _Alloc::propagate_on_container_copy_assignment type;
          };

        template <class _Tp>
        struct __has_propagate_on_container_move_assignment
          {
          private:
            struct __two
              { char __lx; char __lxx;};
            template <class _Up> static __two __test(...);
            template <class _Up> static char __test(typename _Up::propagate_on_container_move_assignment* = 0);
          public:
            static const bool value = sizeof(__test<_Tp>(0)) == 1;
          };

        template <class _Alloc, bool = __has_propagate_on_container_move_assignment<_Alloc>::value>
        struct __propagate_on_container_move_assignment
          {
            typedef false_type type;
          };

        template <class _Alloc>
        struct __propagate_on_container_move_assignment<_Alloc, true>
          {
            typedef typename _Alloc::propagate_on_container_move_assignment type;
          };

        template <class _Tp>
        struct __has_propagate_on_container_swap
          {
          private:
            struct __two
              { char __lx; char __lxx;};
            template <class _Up> static __two __test(...);
            template <class _Up> static char __test(typename _Up::propagate_on_container_swap* = 0);
          public:
            static const bool value = sizeof(__test<_Tp>(0)) == 1;
          };

        template <class _Alloc, bool = __has_propagate_on_container_swap<_Alloc>::value>
        struct __propagate_on_container_swap
          {
            typedef false_type type;
          };

        template <class _Alloc>
        struct __propagate_on_container_swap<_Alloc, true>
          {
            typedef typename _Alloc::propagate_on_container_swap type;
          };

        template <class _Tp, class _Up, bool = __has_rebind<_Tp, _Up>::value>
        struct __has_rebind_other
          {
          private:
            struct __two
              { char __lx; char __lxx;};
            template <class _Xp> static __two __test(...);
            template <class _Xp> static char __test(typename _Xp::template rebind<_Up>::other* = 0);
          public:
            static const bool value = sizeof(__test<_Tp>(0)) == 1;
          };

        template <class _Tp, class _Up>
        struct __has_rebind_other<_Tp, _Up, false>
          {
            static const bool value = false;
          };

        template <class _Tp, class _Up, bool = __has_rebind_other<_Tp, _Up>::value>
        struct __allocator_traits_rebind
          {
            typedef typename _Tp::template rebind<_Up>::other type;
          };

#ifndef _LIBCPP_HAS_NO_VARIADICS

        template <template <class, class...> class _Alloc, class _Tp, class ..._Args, class _Up>
        struct __allocator_traits_rebind<_Alloc<_Tp, _Args...>, _Up, true>
          {
            typedef typename _Alloc<_Tp, _Args...>::template rebind<_Up>::other type;
          };

        template <template <class, class...> class _Alloc, class _Tp, class ..._Args, class _Up>
        struct __allocator_traits_rebind<_Alloc<_Tp, _Args...>, _Up, false>
          {
            typedef _Alloc<_Up, _Args...> type;
          };

#else  // _LIBCPP_HAS_NO_VARIADICS
        template <template <class> class _Alloc, class _Tp, class _Up>
        struct __allocator_traits_rebind<_Alloc<_Tp>, _Up, true>
          {
            typedef typename _Alloc<_Tp>::template rebind<_Up>::other type;
          };

        template <template <class> class _Alloc, class _Tp, class _Up>
        struct __allocator_traits_rebind<_Alloc<_Tp>, _Up, false>
          {
            typedef _Alloc<_Up> type;
          };

        template <template <class, class> class _Alloc, class _Tp, class _A0, class _Up>
        struct __allocator_traits_rebind<_Alloc<_Tp, _A0>, _Up, true>
          {
            typedef typename _Alloc<_Tp, _A0>::template rebind<_Up>::other type;
          };

        template <template <class, class> class _Alloc, class _Tp, class _A0, class _Up>
        struct __allocator_traits_rebind<_Alloc<_Tp, _A0>, _Up, false>
          {
            typedef _Alloc<_Up, _A0> type;
          };

        template <template <class, class, class> class _Alloc, class _Tp, class _A0,
        class _A1, class _Up>
        struct __allocator_traits_rebind<_Alloc<_Tp, _A0, _A1>, _Up, true>
          {
            typedef typename _Alloc<_Tp, _A0, _A1>::template rebind<_Up>::other type;
          };

        template <template <class, class, class> class _Alloc, class _Tp, class _A0,
        class _A1, class _Up>
        struct __allocator_traits_rebind<_Alloc<_Tp, _A0, _A1>, _Up, false>
          {
            typedef _Alloc<_Up, _A0, _A1> type;
          };

        template <template <class, class, class, class> class _Alloc, class _Tp, class _A0,
        class _A1, class _A2, class _Up>
        struct __allocator_traits_rebind<_Alloc<_Tp, _A0, _A1, _A2>, _Up, true>
          {
            typedef typename _Alloc<_Tp, _A0, _A1, _A2>::template rebind<_Up>::other type;
          };

        template <template <class, class, class, class> class _Alloc, class _Tp, class _A0,
        class _A1, class _A2, class _Up>
        struct __allocator_traits_rebind<_Alloc<_Tp, _A0, _A1, _A2>, _Up, false>
          {
            typedef _Alloc<_Up, _A0, _A1, _A2> type;
          };

#endif  // _LIBCPP_HAS_NO_VARIADICS
#ifndef _LIBCPP_HAS_NO_ADVANCED_SFINAE

        template <class _Alloc, class _SizeType, class _ConstVoidPtr>
        auto
        __has_allocate_hint_test(_Alloc&& __a, _SizeType&& __sz, _ConstVoidPtr&& __p)
        -> decltype(__a.allocate(__sz, __p), true_type());

        template <class _Alloc, class _SizeType, class _ConstVoidPtr>
        auto
        __has_allocate_hint_test(const _Alloc& __a, _SizeType&& __sz, _ConstVoidPtr&& __p)
        -> false_type;

        template <class _Alloc, class _SizeType, class _ConstVoidPtr>
        struct __has_allocate_hint
        : integral_constant<bool,
        is_same<
        decltype(__has_allocate_hint_test(declval<_Alloc>(),
                declval<_SizeType>(),
                declval<_ConstVoidPtr>())),
        true_type>::value>
          {
          };

#else  // _LIBCPP_HAS_NO_ADVANCED_SFINAE
        template <class _Alloc, class _SizeType, class _ConstVoidPtr>
        struct __has_allocate_hint
        : true_type
          {
          };

#endif  // _LIBCPP_HAS_NO_ADVANCED_SFINAE
#if !defined(_LIBCPP_HAS_NO_ADVANCED_SFINAE) && !defined(_LIBCPP_HAS_NO_VARIADICS)

        template <class _Alloc, class _Tp, class ..._Args>
        decltype(os::std::declval<_Alloc>().construct(os::std::declval<_Tp*>(),
                os::std::declval<_Args>()...),
            true_type())
        __has_construct_test(_Alloc&& __a, _Tp* __p, _Args&& ...__args);

        template <class _Alloc, class _Pointer, class ..._Args>
        false_type
        __has_construct_test(const _Alloc& __a, _Pointer&& __p, _Args&& ...__args);

        template <class _Alloc, class _Pointer, class ..._Args>
        struct __has_construct
        : integral_constant<bool,
        is_same<
        decltype(__has_construct_test(declval<_Alloc>(),
                declval<_Pointer>(),
                declval<_Args>()...)),
        true_type>::value>
          {
          };

        template <class _Alloc, class _Pointer>
        auto
        __has_destroy_test(_Alloc&& __a, _Pointer&& __p)
        -> decltype(__a.destroy(__p), true_type());

        template <class _Alloc, class _Pointer>
        auto
        __has_destroy_test(const _Alloc& __a, _Pointer&& __p)
        -> false_type;

        template <class _Alloc, class _Pointer>
        struct __has_destroy
        : integral_constant<bool,
        is_same<
        decltype(__has_destroy_test(declval<_Alloc>(),
                declval<_Pointer>())),
        true_type>::value>
          {
          };

        template <class _Alloc>
        auto
        __has_max_size_test(_Alloc&& __a)
        -> decltype(__a.max_size(), true_type());

        template <class _Alloc>
        auto
        __has_max_size_test(const volatile _Alloc& __a)
        -> false_type;

        template <class _Alloc>
        struct __has_max_size
        : integral_constant<bool,
        is_same<
        decltype(__has_max_size_test(declval<_Alloc&>())),
        true_type>::value>
          {
          };

        template <class _Alloc>
        auto
        __has_select_on_container_copy_construction_test(_Alloc&& __a)
        -> decltype(__a.select_on_container_copy_construction(), true_type());

        template <class _Alloc>
        auto
        __has_select_on_container_copy_construction_test(const volatile _Alloc& __a)
        -> false_type;

        template <class _Alloc>
        struct __has_select_on_container_copy_construction
        : integral_constant<bool,
        is_same<
        decltype(__has_select_on_container_copy_construction_test(declval<_Alloc&>())),
        true_type>::value>
          {
          };

#else  // _LIBCPP_HAS_NO_ADVANCED_SFINAE
#ifndef _LIBCPP_HAS_NO_VARIADICS

        template <class _Alloc, class _Pointer, class ..._Args>
        struct __has_construct
        : false_type
          {
          };

#else  // _LIBCPP_HAS_NO_VARIADICS
        template <class _Alloc, class _Pointer, class _Args>
        struct __has_construct
        : false_type
          {
          };

#endif  // _LIBCPP_HAS_NO_VARIADICS
        template <class _Alloc, class _Pointer>
        struct __has_destroy
        : false_type
          {
          };

        template <class _Alloc>
        struct __has_max_size
        : true_type
          {
          };

        template <class _Alloc>
        struct __has_select_on_container_copy_construction
        : false_type
          {
          };

#endif  // _LIBCPP_HAS_NO_ADVANCED_SFINAE
        template <class _Alloc, class _Ptr, bool = __has_difference_type<_Alloc>::value>
        struct __alloc_traits_difference_type
          {
            typedef typename pointer_traits<_Ptr>::difference_type type;
          };

        template <class _Alloc, class _Ptr>
        struct __alloc_traits_difference_type<_Alloc, _Ptr, true>
          {
            typedef typename _Alloc::difference_type type;
          };

        template <class _Alloc>
        struct allocator_traits
          {
            typedef _Alloc allocator_type;
            typedef typename allocator_type::value_type value_type;

            typedef typename __pointer_type<value_type, allocator_type>::type pointer;
            typedef typename __const_pointer<value_type, pointer, allocator_type>::type const_pointer;
            typedef typename __void_pointer<pointer, allocator_type>::type void_pointer;
            typedef typename __const_void_pointer<pointer, allocator_type>::type const_void_pointer;

            typedef typename __alloc_traits_difference_type<allocator_type, pointer>::type difference_type;
            typedef typename __size_type<allocator_type, difference_type>::type size_type;

            typedef typename __propagate_on_container_copy_assignment<allocator_type>::type
            propagate_on_container_copy_assignment;
            typedef typename __propagate_on_container_move_assignment<allocator_type>::type
            propagate_on_container_move_assignment;
            typedef typename __propagate_on_container_swap<allocator_type>::type
            propagate_on_container_swap;

#ifndef _LIBCPP_HAS_NO_TEMPLATE_ALIASES
            template <class _Tp> using rebind_alloc =
            typename __allocator_traits_rebind<allocator_type, _Tp>::type;
            template <class _Tp> using rebind_traits = allocator_traits<rebind_alloc<_Tp>>;
#else  // _LIBCPP_HAS_NO_TEMPLATE_ALIASES
            template <class _Tp> struct rebind_alloc
              { typedef typename __allocator_traits_rebind<allocator_type, _Tp>::type other;};
            template <class _Tp> struct rebind_traits
              { typedef allocator_traits<typename rebind_alloc<_Tp>::other> other;};
#endif  // _LIBCPP_HAS_NO_TEMPLATE_ALIASES
            __attribute__((always_inline))
            static pointer allocate(allocator_type& __a, size_type __n)
              { return __a.allocate(__n);}
            __attribute__((always_inline))
            static pointer allocate(allocator_type& __a, size_type __n, const_void_pointer __hint)
              { return allocate(__a, __n, __hint,
                    __has_allocate_hint<allocator_type, size_type, const_void_pointer>());}

            __attribute__((always_inline))
            static void deallocate(allocator_type& __a, pointer __p, size_type __n) noexcept
              { __a.deallocate(__p, __n);}

#ifndef _LIBCPP_HAS_NO_VARIADICS
            template <class _Tp, class... _Args>
            __attribute__((always_inline))
            static void construct(allocator_type& __a, _Tp* __p, _Args&&... __args)
              { __construct(__has_construct<allocator_type, pointer, _Args...>(),
                    __a, __p, os::std::forward<_Args>(__args)...);}
#else  // _LIBCPP_HAS_NO_VARIADICS
            template <class _Tp>
            __attribute__((always_inline))
            static void construct(allocator_type& __a, _Tp* __p)
              {
                ::new ((void*)__p) _Tp();
              }
            template <class _Tp, class _A0>
            __attribute__((always_inline))
            static void construct(allocator_type& __a, _Tp* __p, const _A0& __a0)
              {
                ::new ((void*)__p) _Tp(__a0);
              }
            template <class _Tp, class _A0, class _A1>
            __attribute__((always_inline))
            static void construct(allocator_type& __a, _Tp* __p, const _A0& __a0,
                const _A1& __a1)
              {
                ::new ((void*)__p) _Tp(__a0, __a1);
              }
            template <class _Tp, class _A0, class _A1, class _A2>
            __attribute__((always_inline))
            static void construct(allocator_type& __a, _Tp* __p, const _A0& __a0,
                const _A1& __a1, const _A2& __a2)
              {
                ::new ((void*)__p) _Tp(__a0, __a1, __a2);
              }
#endif  // _LIBCPP_HAS_NO_VARIADICS
            template <class _Tp>
            __attribute__((always_inline))
            static void destroy(allocator_type& __a, _Tp* __p)
              { __destroy(__has_destroy<allocator_type, _Tp*>(), __a, __p);}

            __attribute__((always_inline))
            static size_type max_size(const allocator_type& __a)
              { return __max_size(__has_max_size<const allocator_type>(), __a);}

            __attribute__((always_inline))
            static allocator_type
            select_on_container_copy_construction(const allocator_type& __a)
              { return select_on_container_copy_construction(
                    __has_select_on_container_copy_construction<const allocator_type>(),
                    __a);}

            template <class _Ptr>
            __attribute__((always_inline))
            static
            void
            __construct_forward(allocator_type& __a, _Ptr __begin1, _Ptr __end1, _Ptr& __begin2)
              {
                for (; __begin1 != __end1; ++__begin1, ++__begin2)
                construct(__a, os::std::__to_raw_pointer(__begin2), os::std::move_if_noexcept(*__begin1));
              }

            template <class _Tp>
            __attribute__((always_inline))
            static
            typename enable_if
            <
            (is_same<allocator_type, allocator<_Tp> >::value
                || !__has_construct<allocator_type, _Tp*, _Tp>::value) &&
            is_trivially_move_constructible<_Tp>::value,
            void
            >::type
            __construct_forward(allocator_type& __a __attribute__((unused)), _Tp* __begin1, _Tp* __end1, _Tp*& __begin2)
              {
                ptrdiff_t _Np = __end1 - __begin1;
                os::std::memcpy(__begin2, __begin1, _Np * sizeof(_Tp));
                __begin2 += _Np;
              }

            template <class _Ptr>
            __attribute__((always_inline))
            static
            void
            __construct_backward(allocator_type& __a, _Ptr __begin1, _Ptr __end1, _Ptr& __end2)
              {
                while (__end1 != __begin1)
                  {
                    construct(__a, os::std::__to_raw_pointer(__end2-1), os::std::move_if_noexcept(*--__end1));
                    --__end2;
                  }
              }

            template <class _Tp>
            __attribute__((always_inline))
            static
            typename enable_if
            <
            (is_same<allocator_type, allocator<_Tp> >::value
                || !__has_construct<allocator_type, _Tp*, _Tp>::value) &&
            is_trivially_move_constructible<_Tp>::value,
            void
            >::type
            __construct_backward(allocator_type& __a __attribute__((unused)), _Tp* __begin1, _Tp* __end1, _Tp*& __end2)
              {
                ptrdiff_t _Np = __end1 - __begin1;
                __end2 -= _Np;
                os::std::memcpy(__end2, __begin1, _Np * sizeof(_Tp));
              }

          private:

            __attribute__((always_inline))
            static pointer allocate(allocator_type& __a, size_type __n,
                const_void_pointer __hint, true_type)
              { return __a.allocate(__n, __hint);}
            __attribute__((always_inline))
            static pointer allocate(allocator_type& __a, size_type __n,
                const_void_pointer, false_type)
              { return __a.allocate(__n);}

#ifndef _LIBCPP_HAS_NO_VARIADICS
            template <class _Tp, class... _Args>
            __attribute__((always_inline))
            static void __construct(true_type, allocator_type& __a, _Tp* __p, _Args&&... __args)
              { __a.construct(__p, os::std::forward<_Args>(__args)...);}
            template <class _Tp, class... _Args>
            __attribute__((always_inline))
            static void __construct(false_type, allocator_type&, _Tp* __p, _Args&&... __args)
              {
                ::new ((void*)__p) _Tp(os::std::forward<_Args>(__args)...);
              }
#endif  // _LIBCPP_HAS_NO_VARIADICS
            template <class _Tp>
            __attribute__((always_inline))
            static void __destroy(true_type, allocator_type& __a, _Tp* __p)
              { __a.destroy(__p);}
            template <class _Tp>
            __attribute__((always_inline))
            static void __destroy(false_type, allocator_type&, _Tp* __p)
              {
                __p->~_Tp();
              }

            __attribute__((always_inline))
            static size_type __max_size(true_type, const allocator_type& __a)
              { return __a.max_size();}
            __attribute__((always_inline))
            static size_type __max_size(false_type, const allocator_type&)
              { return numeric_limits<size_type>::max();}

            __attribute__((always_inline))
            static allocator_type
            select_on_container_copy_construction(true_type, const allocator_type& __a)
              { return __a.select_on_container_copy_construction();}
            __attribute__((always_inline))
            static allocator_type
            select_on_container_copy_construction(false_type, const allocator_type& __a)
              { return __a;}
          };

// allocator

        template <class _Tp>
        class allocator
          {
          public:
            typedef size_t size_type;
            typedef ptrdiff_t difference_type;
            typedef _Tp* pointer;
            typedef const _Tp* const_pointer;
            typedef _Tp& reference;
            typedef const _Tp& const_reference;
            typedef _Tp value_type;

            typedef true_type propagate_on_container_move_assignment;

            template <class _Up> struct rebind
              { typedef allocator<_Up> other;};

            __attribute__((always_inline))
            allocator() noexcept
              {
              }

            template <class _Up>
            __attribute__((always_inline))
            allocator(const allocator<_Up>&) noexcept
              {
              }

            pointer
            __attribute__((always_inline))
            address(reference __x) const noexcept
              {
                return os::std::addressof(__x);
              }

            const_pointer
            __attribute__((always_inline))
            address(const_reference __x) const noexcept
              {
                return os::std::addressof(__x);
              }

            pointer
            __attribute__((always_inline))
            allocate(size_type __n, allocator<void>::const_pointer = 0)
              {
                return static_cast<pointer>(::operator new(__n * sizeof(_Tp)));
              }

            void
            __attribute__((always_inline))
            deallocate(pointer __p, size_type) noexcept
              {
                ::operator delete((void*)__p);
              }

            size_type
            __attribute__((always_inline))
            max_size() const noexcept
              {
                return size_type(~0) / sizeof(_Tp);
              }

#if !defined(_LIBCPP_HAS_NO_RVALUE_REFERENCES) && !defined(_LIBCPP_HAS_NO_VARIADICS)
            template <class _Up, class... _Args>
            __attribute__((always_inline))
            void
            construct(_Up* __p, _Args&&... __args)
              {
                ::new((void*)__p) _Up(os::std::forward<_Args>(__args)...);
              }
#else  // !defined(_LIBCPP_HAS_NO_RVALUE_REFERENCES) && !defined(_LIBCPP_HAS_NO_VARIADICS)
            void
            __attribute__((always_inline))
            construct(pointer __p)
              {
                ::new((void*)__p) _Tp();
              }
# if defined(_LIBCPP_HAS_NO_RVALUE_REFERENCES)

            template <class _A0>
            void
            __attribute__((always_inline))
            construct(pointer __p, _A0& __a0)
              {
                ::new((void*)__p) _Tp(__a0);
              }

            template <class _A0>
            void
            __attribute__((always_inline))
            construct(pointer __p, const _A0& __a0)
              {
                ::new((void*)__p) _Tp(__a0);
              }

# endif  // defined(_LIBCPP_HAS_NO_RVALUE_REFERENCES)
            template <class _A0, class _A1>
            void
            __attribute__((always_inline))
            construct(pointer __p, _A0& __a0, _A1& __a1)
              {
                ::new((void*)__p) _Tp(__a0, __a1);
              }

            template <class _A0, class _A1>
            void
            __attribute__((always_inline))
            construct(pointer __p, const _A0& __a0, _A1& __a1)
              {
                ::new((void*)__p) _Tp(__a0, __a1);
              }

            template <class _A0, class _A1>
            void
            __attribute__((always_inline))
            construct(pointer __p, _A0& __a0, const _A1& __a1)
              {
                ::new((void*)__p) _Tp(__a0, __a1);
              }

            template <class _A0, class _A1>
            void
            __attribute__((always_inline))
            construct(pointer __p, const _A0& __a0, const _A1& __a1)
              {
                ::new((void*)__p) _Tp(__a0, __a1);
              }

#endif  // !defined(_LIBCPP_HAS_NO_RVALUE_REFERENCES) && !defined(_LIBCPP_HAS_NO_VARIADICS)
            void
            __attribute__((always_inline))
            destroy(pointer __p)
              {
                __p->~_Tp();
              }
          };

        template <class _Tp>
        class allocator<const _Tp>
          {
          public:
            typedef size_t size_type;
            typedef ptrdiff_t difference_type;
            typedef const _Tp* pointer;
            typedef const _Tp* const_pointer;
            typedef const _Tp& reference;
            typedef const _Tp& const_reference;
            typedef _Tp value_type;

            typedef true_type propagate_on_container_move_assignment;

            template <class _Up> struct rebind
              { typedef allocator<_Up> other;};

            __attribute__((always_inline))
            allocator() noexcept
              {
              }

            template <class _Up>
            __attribute__((always_inline))
            allocator(const allocator<_Up>&) noexcept
              {
              }

            const_pointer
            __attribute__((always_inline))
            address(const_reference __x) const noexcept
              {
                return os::std::addressof(__x);
              }

            pointer
            __attribute__((always_inline))
            allocate(size_type __n, allocator<void>::const_pointer = 0)
              {
                return static_cast<pointer>(::operator new(__n * sizeof(_Tp)));
              }

            void
            __attribute__((always_inline))
            deallocate(pointer __p, size_type) noexcept
              {
                ::operator delete((void*)__p);
              }

            size_type
            __attribute__((always_inline))
            max_size() const noexcept
              {
                return size_type(~0) / sizeof(_Tp);
              }

#if !defined(_LIBCPP_HAS_NO_RVALUE_REFERENCES) && !defined(_LIBCPP_HAS_NO_VARIADICS)
            template <class _Up, class... _Args>
            void
            __attribute__((always_inline))
            construct(_Up* __p, _Args&&... __args)
              {
                ::new((void*)__p) _Up(os::std::forward<_Args>(__args)...);
              }
#else  // !defined(_LIBCPP_HAS_NO_RVALUE_REFERENCES) && !defined(_LIBCPP_HAS_NO_VARIADICS)
            void
            __attribute__((always_inline))
            construct(pointer __p)
              {
                ::new((void*)__p) _Tp();
              }
# if defined(_LIBCPP_HAS_NO_RVALUE_REFERENCES)

            template <class _A0>
            void
            __attribute__((always_inline))
            construct(pointer __p, _A0& __a0)
              {
                ::new((void*)__p) _Tp(__a0);
              }

            template <class _A0>
            void
            __attribute__((always_inline))
            construct(pointer __p, const _A0& __a0)
              {
                ::new((void*)__p) _Tp(__a0);
              }

# endif  // defined(_LIBCPP_HAS_NO_RVALUE_REFERENCES)
            template <class _A0, class _A1>
            void
            __attribute__((always_inline))
            construct(pointer __p, _A0& __a0, _A1& __a1)
              {
                ::new((void*)__p) _Tp(__a0, __a1);
              }

            template <class _A0, class _A1>
            void
            __attribute__((always_inline))
            construct(pointer __p, const _A0& __a0, _A1& __a1)
              {
                ::new((void*)__p) _Tp(__a0, __a1);
              }

            template <class _A0, class _A1>
            void
            __attribute__((always_inline))
            construct(pointer __p, _A0& __a0, const _A1& __a1)
              {
                ::new((void*)__p) _Tp(__a0, __a1);
              }

            template <class _A0, class _A1>
            void
            __attribute__((always_inline))
            construct(pointer __p, const _A0& __a0, const _A1& __a1)
              {
                ::new((void*)__p) _Tp(__a0, __a1);
              }

#endif  // !defined(_LIBCPP_HAS_NO_RVALUE_REFERENCES) && !defined(_LIBCPP_HAS_NO_VARIADICS)
            void
            __attribute__((always_inline))
            destroy(pointer __p)
              {
                __p->~_Tp();
              }
          };

        template <class _Tp, class _Up>
        inline bool
        __attribute__((always_inline))
        operator==(const allocator<_Tp>&, const allocator<_Up>&) noexcept
          {
            return true;
          }

        template <class _Tp, class _Up>
        inline __attribute__((always_inline))
        bool operator!=(const allocator<_Tp>&, const allocator<_Up>&) noexcept
          {
            return false;
          }

        template <class _OutputIterator, class _Tp>
        class raw_storage_iterator
        : public iterator<output_iterator_tag,
        _Tp,                                         // purposefully not C++03
        ptrdiff_t,// purposefully not C++03
        _Tp*,// purposefully not C++03
        raw_storage_iterator<_OutputIterator, _Tp>&>// purposefully not C++03
          {
          private:
            _OutputIterator __x_;
          public:
            __attribute__((always_inline)) explicit raw_storage_iterator(_OutputIterator __x) : __x_(__x)
              {}
            __attribute__((always_inline)) raw_storage_iterator& operator*()
              { return *this;}
            __attribute__((always_inline)) raw_storage_iterator& operator=(const _Tp& __element)
              { ::new(&*__x_) _Tp(__element); return *this;}
            __attribute__((always_inline)) raw_storage_iterator& operator++()
              { ++__x_; return *this;}
            __attribute__((always_inline)) raw_storage_iterator operator++(int)
              { raw_storage_iterator __t(*this); ++__x_; return __t;}
          };

        template <class _Tp>
        pair<_Tp*, ptrdiff_t>
        get_temporary_buffer(ptrdiff_t __n) noexcept
          {
            pair<_Tp*, ptrdiff_t> __r(0, 0);

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wshift-sign-overflow"
#endif
            const ptrdiff_t __m = (~ptrdiff_t(0) ^
                ptrdiff_t(ptrdiff_t(1) << (sizeof(ptrdiff_t) * __CHAR_BIT__ - 1)))
            / sizeof(_Tp);
#pragma GCC diagnostic pop

            if (__n > __m)
            __n = __m;
            while (__n > 0)
              {
                __r.first = static_cast<_Tp*>(::operator new(__n * sizeof(_Tp), nothrow));
                if (__r.first)
                  {
                    __r.second = __n;
                    break;
                  }
                __n /= 2;
              }
            return __r;
          }

        template <class _Tp>
        inline __attribute__((always_inline))
        void return_temporary_buffer(_Tp* __p) noexcept
          { ::operator delete(__p);}

        template <class _Tp>
        struct auto_ptr_ref
          {
            _Tp* __ptr_;
          };

        template<class _Tp>
        class auto_ptr
          {
          private:
            _Tp* __ptr_;
          public:
            typedef _Tp element_type;

            __attribute__((always_inline)) explicit auto_ptr(_Tp* __p = 0) throw() : __ptr_(__p)
              {}
            __attribute__((always_inline)) auto_ptr(auto_ptr& __p) throw() : __ptr_(__p.release())
              {}
            template<class _Up> __attribute__((always_inline)) auto_ptr(auto_ptr<_Up>& __p) throw()
            : __ptr_(__p.release())
              {}
            __attribute__((always_inline)) auto_ptr& operator=(auto_ptr& __p) throw()
              { reset(__p.release()); return *this;}
            template<class _Up> __attribute__((always_inline)) auto_ptr& operator=(auto_ptr<_Up>& __p) throw()
              { reset(__p.release()); return *this;}
            __attribute__((always_inline)) auto_ptr& operator=(auto_ptr_ref<_Tp> __p) throw()
              { reset(__p.__ptr_); return *this;}
            __attribute__((always_inline)) ~auto_ptr() throw()
              { delete __ptr_;}

            __attribute__((always_inline)) _Tp& operator*() const throw()
              { return *__ptr_;}
            __attribute__((always_inline)) _Tp* operator->() const throw()
              { return __ptr_;}
            __attribute__((always_inline)) _Tp* get() const throw()
              { return __ptr_;}
            __attribute__((always_inline)) _Tp* release() throw()
              {
                _Tp* __t = __ptr_;
                __ptr_ = 0;
                return __t;
              }
            __attribute__((always_inline)) void reset(_Tp* __p = 0) throw()
              {
                if (__ptr_ != __p)
                delete __ptr_;
                __ptr_ = __p;
              }

            __attribute__((always_inline)) auto_ptr(auto_ptr_ref<_Tp> __p) throw() : __ptr_(__p.__ptr_)
              {}
            template<class _Up> __attribute__((always_inline)) operator auto_ptr_ref<_Up>() throw()
              { auto_ptr_ref<_Up> __t; __t.__ptr_ = release(); return __t;}
            template<class _Up> __attribute__((always_inline)) operator auto_ptr<_Up>() throw()
              { return auto_ptr<_Up>(release());}
          };

        template <>
        class auto_ptr<void>
          {
          public:
            typedef void element_type;
          };

        template <class _T1, class _T2, bool = is_same<typename remove_cv<_T1>::type,
        typename remove_cv<_T2>::type>::value,
        bool = is_empty<_T1>::value
#if __has_feature(is_final)
        && !__is_final(_T1)
#endif
        ,
        bool = is_empty<_T2>::value
#if __has_feature(is_final)
        && !__is_final(_T2)
#endif
        >
        struct __libcpp_compressed_pair_switch;

        template <class _T1, class _T2, bool IsSame>
        struct __libcpp_compressed_pair_switch<_T1, _T2, IsSame, false, false>
          { enum
              { value = 0};};

        template <class _T1, class _T2, bool IsSame>
        struct __libcpp_compressed_pair_switch<_T1, _T2, IsSame, true, false>
          { enum
              { value = 1};};

        template <class _T1, class _T2, bool IsSame>
        struct __libcpp_compressed_pair_switch<_T1, _T2, IsSame, false, true>
          { enum
              { value = 2};};

        template <class _T1, class _T2>
        struct __libcpp_compressed_pair_switch<_T1, _T2, false, true, true>
          { enum
              { value = 3};};

        template <class _T1, class _T2>
        struct __libcpp_compressed_pair_switch<_T1, _T2, true, true, true>
          { enum
              { value = 1};};

        template <class _T1, class _T2, unsigned = __libcpp_compressed_pair_switch<_T1, _T2>::value>
        class __libcpp_compressed_pair_imp;

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

        template <class _T1, class _T2>
        class __libcpp_compressed_pair_imp<_T1, _T2, 0>
          {
          private:
            _T1 __first_;
            _T2 __second_;
          public:
            typedef _T1 _T1_param;
            typedef _T2 _T2_param;

            typedef typename remove_reference<_T1>::type& _T1_reference;
            typedef typename remove_reference<_T2>::type& _T2_reference;

            typedef const typename remove_reference<_T1>::type& _T1_const_reference;
            typedef const typename remove_reference<_T2>::type& _T2_const_reference;

            __attribute__((always_inline)) __libcpp_compressed_pair_imp()
              {}
            __attribute__((always_inline)) explicit __libcpp_compressed_pair_imp(_T1_param __t1)
            : __first_(os::std::forward<_T1_param>(__t1))
              {}
            __attribute__((always_inline)) explicit __libcpp_compressed_pair_imp(_T2_param __t2)
            : __second_(os::std::forward<_T2_param>(__t2))
              {}
            __attribute__((always_inline)) __libcpp_compressed_pair_imp(_T1_param __t1, _T2_param __t2)
            : __first_(os::std::forward<_T1_param>(__t1)), __second_(os::std::forward<_T2_param>(__t2))
              {}

#ifdef _LIBCPP_HAS_NO_DEFAULTED_FUNCTIONS

            __attribute__((always_inline))
            __libcpp_compressed_pair_imp(const __libcpp_compressed_pair_imp& __p)
            noexcept (is_nothrow_copy_constructible<_T1>::value &&
                is_nothrow_copy_constructible<_T2>::value)
            : __first_(__p.first()),
            __second_(__p.second())
              {}

            __attribute__((always_inline))
            __libcpp_compressed_pair_imp& operator=(const __libcpp_compressed_pair_imp& __p)
            noexcept (is_nothrow_copy_assignable<_T1>::value &&
                is_nothrow_copy_assignable<_T2>::value)
              {
                __first_ = __p.first();
                __second_ = __p.second();
                return *this;
              }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

            __attribute__((always_inline))
            __libcpp_compressed_pair_imp(__libcpp_compressed_pair_imp&& __p)
            noexcept (is_nothrow_move_constructible<_T1>::value &&
                is_nothrow_move_constructible<_T2>::value)
            : __first_(os::std::forward<_T1>(__p.first())),
            __second_(os::std::forward<_T2>(__p.second()))
              {}

            __attribute__((always_inline))
            __libcpp_compressed_pair_imp& operator=(__libcpp_compressed_pair_imp&& __p)
            noexcept (is_nothrow_move_assignable<_T1>::value &&
                is_nothrow_move_assignable<_T2>::value)
              {
                __first_ = os::std::forward<_T1>(__p.first());
                __second_ = os::std::forward<_T2>(__p.second());
                return *this;
              }

#ifndef _LIBCPP_HAS_NO_VARIADICS

            template <class... _Args1, class... _Args2, size_t... _I1, size_t... _I2>
            __attribute__((always_inline))
            __libcpp_compressed_pair_imp(piecewise_construct_t __pc,
                tuple<_Args1...> __first_args,
                tuple<_Args2...> __second_args,
                __tuple_indices<_I1...>,
                __tuple_indices<_I2...>)
            : __first_(os::std::forward<_Args1>(get<_I1>(__first_args))...),
            __second_(os::std::forward<_Args2>(get<_I2>(__second_args))...)
              {}

#endif  // _LIBCPP_HAS_NO_VARIADICS
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
#endif  // _LIBCPP_HAS_NO_DEFAULTED_FUNCTIONS
            __attribute__((always_inline)) _T1_reference first() noexcept
              { return __first_;}
            __attribute__((always_inline)) _T1_const_reference first() const noexcept
              { return __first_;}

            __attribute__((always_inline)) _T2_reference second() noexcept
              { return __second_;}
            __attribute__((always_inline)) _T2_const_reference second() const noexcept
              { return __second_;}

            __attribute__((always_inline)) void swap(__libcpp_compressed_pair_imp& __x)
            noexcept (__is_nothrow_swappable<_T1>::value &&
                __is_nothrow_swappable<_T1>::value)
              {
                using os::std::swap;
                swap(__first_, __x.__first_);
                swap(__second_, __x.__second_);
              }
          };

#pragma GCC diagnostic pop

        template <class _T1, class _T2>
        class __libcpp_compressed_pair_imp<_T1, _T2, 1>
        : private _T1
          {
          private:
            _T2 __second_;
          public:
            typedef _T1 _T1_param;
            typedef _T2 _T2_param;

            typedef _T1& _T1_reference;
            typedef typename remove_reference<_T2>::type& _T2_reference;

            typedef const _T1& _T1_const_reference;
            typedef const typename remove_reference<_T2>::type& _T2_const_reference;

            __attribute__((always_inline)) __libcpp_compressed_pair_imp()
              {}
            __attribute__((always_inline)) explicit __libcpp_compressed_pair_imp(_T1_param __t1)
            : _T1(os::std::forward<_T1_param>(__t1))
              {}
            __attribute__((always_inline)) explicit __libcpp_compressed_pair_imp(_T2_param __t2)
            : __second_(os::std::forward<_T2_param>(__t2))
              {}
            __attribute__((always_inline)) __libcpp_compressed_pair_imp(_T1_param __t1, _T2_param __t2)
            : _T1(os::std::forward<_T1_param>(__t1)), __second_(os::std::forward<_T2_param>(__t2))
              {}

#ifdef _LIBCPP_HAS_NO_DEFAULTED_FUNCTIONS

            __attribute__((always_inline))
            __libcpp_compressed_pair_imp(const __libcpp_compressed_pair_imp& __p)
            noexcept (is_nothrow_copy_constructible<_T1>::value &&
                is_nothrow_copy_constructible<_T2>::value)
            : _T1(__p.first()), __second_(__p.second())
              {}

            __attribute__((always_inline))
            __libcpp_compressed_pair_imp& operator=(const __libcpp_compressed_pair_imp& __p)
            noexcept (is_nothrow_copy_assignable<_T1>::value &&
                is_nothrow_copy_assignable<_T2>::value)
              {
                _T1::operator=(__p.first());
                __second_ = __p.second();
                return *this;
              }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

            __attribute__((always_inline))
            __libcpp_compressed_pair_imp(__libcpp_compressed_pair_imp&& __p)
            noexcept (is_nothrow_move_constructible<_T1>::value &&
                is_nothrow_move_constructible<_T2>::value)
            : _T1(os::std::move(__p.first())), __second_(os::std::forward<_T2>(__p.second()))
              {}

            __attribute__((always_inline))
            __libcpp_compressed_pair_imp& operator=(__libcpp_compressed_pair_imp&& __p)
            noexcept (is_nothrow_move_assignable<_T1>::value &&
                is_nothrow_move_assignable<_T2>::value)
              {
                _T1::operator=(os::std::move(__p.first()));
                __second_ = os::std::forward<_T2>(__p.second());
                return *this;
              }

#ifndef _LIBCPP_HAS_NO_VARIADICS

            template <class... _Args1, class... _Args2, size_t... _I1, size_t... _I2>
            __attribute__((always_inline))
            __libcpp_compressed_pair_imp(piecewise_construct_t __pc,
                tuple<_Args1...> __first_args,
                tuple<_Args2...> __second_args,
                __tuple_indices<_I1...>,
                __tuple_indices<_I2...>)
            : _T1(os::std::forward<_Args1>(get<_I1>(__first_args))...),
            __second_(os::std::forward<_Args2>(get<_I2>(__second_args))...)
              {}

#endif  // _LIBCPP_HAS_NO_VARIADICS
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
#endif  // _LIBCPP_HAS_NO_DEFAULTED_FUNCTIONS
            __attribute__((always_inline)) _T1_reference first() noexcept
              { return *this;}
            __attribute__((always_inline)) _T1_const_reference first() const noexcept
              { return *this;}

            __attribute__((always_inline)) _T2_reference second() noexcept
              { return __second_;}
            __attribute__((always_inline)) _T2_const_reference second() const noexcept
              { return __second_;}

            __attribute__((always_inline)) void swap(__libcpp_compressed_pair_imp& __x)
            noexcept (__is_nothrow_swappable<_T1>::value &&
                __is_nothrow_swappable<_T1>::value)
              {
                using os::std::swap;
                swap(__second_, __x.__second_);
              }
          };

        template <class _T1, class _T2>
        class __libcpp_compressed_pair_imp<_T1, _T2, 2>
        : private _T2
          {
          private:
            _T1 __first_;
          public:
            typedef _T1 _T1_param;
            typedef _T2 _T2_param;

            typedef typename remove_reference<_T1>::type& _T1_reference;
            typedef _T2& _T2_reference;

            typedef const typename remove_reference<_T1>::type& _T1_const_reference;
            typedef const _T2& _T2_const_reference;

            __attribute__((always_inline)) __libcpp_compressed_pair_imp()
              {}
            __attribute__((always_inline)) explicit __libcpp_compressed_pair_imp(_T1_param __t1)
            : __first_(os::std::forward<_T1_param>(__t1))
              {}
            __attribute__((always_inline)) explicit __libcpp_compressed_pair_imp(_T2_param __t2)
            : _T2(os::std::forward<_T2_param>(__t2))
              {}
            __attribute__((always_inline)) __libcpp_compressed_pair_imp(_T1_param __t1, _T2_param __t2)
            noexcept (is_nothrow_move_constructible<_T1>::value &&
                is_nothrow_move_constructible<_T2>::value)
            : _T2(os::std::forward<_T2_param>(__t2)), __first_(os::std::forward<_T1_param>(__t1))
              {}

#ifdef _LIBCPP_HAS_NO_DEFAULTED_FUNCTIONS

            __attribute__((always_inline))
            __libcpp_compressed_pair_imp(const __libcpp_compressed_pair_imp& __p)
            noexcept (is_nothrow_copy_constructible<_T1>::value &&
                is_nothrow_copy_constructible<_T2>::value)
            : _T2(__p.second()), __first_(__p.first())
              {}

            __attribute__((always_inline))
            __libcpp_compressed_pair_imp& operator=(const __libcpp_compressed_pair_imp& __p)
            noexcept (is_nothrow_copy_assignable<_T1>::value &&
                is_nothrow_copy_assignable<_T2>::value)
              {
                _T2::operator=(__p.second());
                __first_ = __p.first();
                return *this;
              }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

            __attribute__((always_inline))
            __libcpp_compressed_pair_imp(__libcpp_compressed_pair_imp&& __p)
            noexcept (is_nothrow_move_constructible<_T1>::value &&
                is_nothrow_move_constructible<_T2>::value)
            : _T2(os::std::forward<_T2>(__p.second())), __first_(os::std::move(__p.first()))
              {}

            __attribute__((always_inline))
            __libcpp_compressed_pair_imp& operator=(__libcpp_compressed_pair_imp&& __p)
            noexcept (is_nothrow_move_assignable<_T1>::value &&
                is_nothrow_move_assignable<_T2>::value)
              {
                _T2::operator=(os::std::forward<_T2>(__p.second()));
                __first_ = os::std::move(__p.first());
                return *this;
              }

#ifndef _LIBCPP_HAS_NO_VARIADICS

            template <class... _Args1, class... _Args2, size_t... _I1, size_t... _I2>
            __attribute__((always_inline))
            __libcpp_compressed_pair_imp(piecewise_construct_t __pc,
                tuple<_Args1...> __first_args,
                tuple<_Args2...> __second_args,
                __tuple_indices<_I1...>,
                __tuple_indices<_I2...>)
            : _T2(os::std::forward<_Args2>(get<_I2>(__second_args))...),
            __first_(os::std::forward<_Args1>(get<_I1>(__first_args))...)

              {}

#endif  // _LIBCPP_HAS_NO_VARIADICS
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
#endif  // _LIBCPP_HAS_NO_DEFAULTED_FUNCTIONS
            __attribute__((always_inline)) _T1_reference first() noexcept
              { return __first_;}
            __attribute__((always_inline)) _T1_const_reference first() const noexcept
              { return __first_;}

            __attribute__((always_inline)) _T2_reference second() noexcept
              { return *this;}
            __attribute__((always_inline)) _T2_const_reference second() const noexcept
              { return *this;}

            __attribute__((always_inline)) void swap(__libcpp_compressed_pair_imp& __x)
            noexcept (__is_nothrow_swappable<_T1>::value &&
                __is_nothrow_swappable<_T1>::value)
              {
                using os::std::swap;
                swap(__first_, __x.__first_);
              }
          };

        template <class _T1, class _T2>
        class __libcpp_compressed_pair_imp<_T1, _T2, 3>
        : private _T1,
      private _T2
          {
          public:
            typedef _T1 _T1_param;
            typedef _T2 _T2_param;

            typedef _T1& _T1_reference;
            typedef _T2& _T2_reference;

            typedef const _T1& _T1_const_reference;
            typedef const _T2& _T2_const_reference;

            __attribute__((always_inline)) __libcpp_compressed_pair_imp()
              {}
            __attribute__((always_inline)) explicit __libcpp_compressed_pair_imp(_T1_param __t1)
            : _T1(os::std::forward<_T1_param>(__t1))
              {}
            __attribute__((always_inline)) explicit __libcpp_compressed_pair_imp(_T2_param __t2)
            : _T2(os::std::forward<_T2_param>(__t2))
              {}
            __attribute__((always_inline)) __libcpp_compressed_pair_imp(_T1_param __t1, _T2_param __t2)
            : _T1(os::std::forward<_T1_param>(__t1)), _T2(os::std::forward<_T2_param>(__t2))
              {}

#ifdef _LIBCPP_HAS_NO_DEFAULTED_FUNCTIONS

            __attribute__((always_inline))
            __libcpp_compressed_pair_imp(const __libcpp_compressed_pair_imp& __p)
            noexcept (is_nothrow_copy_constructible<_T1>::value &&
                is_nothrow_copy_constructible<_T2>::value)
            : _T1(__p.first()), _T2(__p.second())
              {}

            __attribute__((always_inline))
            __libcpp_compressed_pair_imp& operator=(const __libcpp_compressed_pair_imp& __p)
            noexcept (is_nothrow_copy_assignable<_T1>::value &&
                is_nothrow_copy_assignable<_T2>::value)
              {
                _T1::operator=(__p.first());
                _T2::operator=(__p.second());
                return *this;
              }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

            __attribute__((always_inline))
            __libcpp_compressed_pair_imp(__libcpp_compressed_pair_imp&& __p)
            noexcept (is_nothrow_move_constructible<_T1>::value &&
                is_nothrow_move_constructible<_T2>::value)
            : _T1(os::std::move(__p.first())), _T2(os::std::move(__p.second()))
              {}

            __attribute__((always_inline))
            __libcpp_compressed_pair_imp& operator=(__libcpp_compressed_pair_imp&& __p)
            noexcept (is_nothrow_move_assignable<_T1>::value &&
                is_nothrow_move_assignable<_T2>::value)
              {
                _T1::operator=(os::std::move(__p.first()));
                _T2::operator=(os::std::move(__p.second()));
                return *this;
              }

#ifndef _LIBCPP_HAS_NO_VARIADICS

            template <class... _Args1, class... _Args2, size_t... _I1, size_t... _I2>
            __attribute__((always_inline))
            __libcpp_compressed_pair_imp(piecewise_construct_t __pc,
                tuple<_Args1...> __first_args,
                tuple<_Args2...> __second_args,
                __tuple_indices<_I1...>,
                __tuple_indices<_I2...>)
            : _T1(os::std::forward<_Args1>(get<_I1>(__first_args))...),
            _T2(os::std::forward<_Args2>(get<_I2>(__second_args))...)
              {}

#endif  // _LIBCPP_HAS_NO_VARIADICS
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
#endif  // _LIBCPP_HAS_NO_DEFAULTED_FUNCTIONS
            __attribute__((always_inline)) _T1_reference first() noexcept
              { return *this;}
            __attribute__((always_inline)) _T1_const_reference first() const noexcept
              { return *this;}

            __attribute__((always_inline)) _T2_reference second() noexcept
              { return *this;}
            __attribute__((always_inline)) _T2_const_reference second() const noexcept
              { return *this;}

            __attribute__((always_inline)) void swap(__libcpp_compressed_pair_imp&)
            noexcept (__is_nothrow_swappable<_T1>::value &&
                __is_nothrow_swappable<_T1>::value)
              {
              }
          };

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

        template <class _T1, class _T2>
        class __compressed_pair
        : private __libcpp_compressed_pair_imp<_T1, _T2>
          {
            typedef __libcpp_compressed_pair_imp<_T1, _T2> base;
          public:
            typedef typename base::_T1_param _T1_param;
            typedef typename base::_T2_param _T2_param;

            typedef typename base::_T1_reference _T1_reference;
            typedef typename base::_T2_reference _T2_reference;

            typedef typename base::_T1_const_reference _T1_const_reference;
            typedef typename base::_T2_const_reference _T2_const_reference;

            __attribute__((always_inline)) __compressed_pair()
              {}
            __attribute__((always_inline)) explicit __compressed_pair(_T1_param __t1)
            : base(os::std::forward<_T1_param>(__t1))
              {}
            __attribute__((always_inline)) explicit __compressed_pair(_T2_param __t2)
            : base(os::std::forward<_T2_param>(__t2))
              {}
            __attribute__((always_inline)) __compressed_pair(_T1_param __t1, _T2_param __t2)
            : base(os::std::forward<_T1_param>(__t1), os::std::forward<_T2_param>(__t2))
              {}

#ifdef _LIBCPP_HAS_NO_DEFAULTED_FUNCTIONS

            __attribute__((always_inline))
            __compressed_pair(const __compressed_pair& __p)
            noexcept (is_nothrow_copy_constructible<_T1>::value &&
                is_nothrow_copy_constructible<_T2>::value)
            : base(__p)
              {}

            __attribute__((always_inline))
            __compressed_pair& operator=(const __compressed_pair& __p)
            noexcept (is_nothrow_copy_assignable<_T1>::value &&
                is_nothrow_copy_assignable<_T2>::value)
              {
                base::operator=(__p);
                return *this;
              }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
            __attribute__((always_inline))
            __compressed_pair(__compressed_pair&& __p)
            noexcept (is_nothrow_move_constructible<_T1>::value &&
                is_nothrow_move_constructible<_T2>::value)
            : base(os::std::move(__p))
              {}

            __attribute__((always_inline))
            __compressed_pair& operator=(__compressed_pair&& __p)
            noexcept (is_nothrow_move_assignable<_T1>::value &&
                is_nothrow_move_assignable<_T2>::value)
              {
                base::operator=(os::std::move(__p));
                return *this;
              }

#ifndef _LIBCPP_HAS_NO_VARIADICS

            template <class... _Args1, class... _Args2>
            __attribute__((always_inline))
            __compressed_pair(piecewise_construct_t __pc, tuple<_Args1...> __first_args,
                tuple<_Args2...> __second_args)
            : base(__pc, os::std::move(__first_args), os::std::move(__second_args),
                typename __make_tuple_indices<sizeof...(_Args1)>::type(),
                typename __make_tuple_indices<sizeof...(_Args2) >::type())
              {}

#endif  // _LIBCPP_HAS_NO_VARIADICS
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
#endif  // _LIBCPP_HAS_NO_DEFAULTED_FUNCTIONS
            __attribute__((always_inline)) _T1_reference first() noexcept
              { return base::first();}
            __attribute__((always_inline)) _T1_const_reference first() const noexcept
              { return base::first();}

            __attribute__((always_inline)) _T2_reference second() noexcept
              { return base::second();}
            __attribute__((always_inline)) _T2_const_reference second() const noexcept
              { return base::second();}

            __attribute__((always_inline)) void swap(__compressed_pair& __x)
            noexcept (__is_nothrow_swappable<_T1>::value &&
                __is_nothrow_swappable<_T1>::value)
              { base::swap(__x);}
          };

#pragma GCC diagnostic pop

        template <class _T1, class _T2>
        inline __attribute__((always_inline))
        void
        swap(__compressed_pair<_T1, _T2>& __x, __compressed_pair<_T1, _T2>& __y)
        noexcept (__is_nothrow_swappable<_T1>::value &&
            __is_nothrow_swappable<_T1>::value)
          { __x.swap(__y);}

// __same_or_less_cv_qualified

        template <class _Ptr1, class _Ptr2,
        bool = is_same<typename remove_cv<typename pointer_traits<_Ptr1>::element_type>::type,
        typename remove_cv<typename pointer_traits<_Ptr2>::element_type>::type
        >::value
        >
        struct __same_or_less_cv_qualified_imp
        : is_convertible<_Ptr1, _Ptr2>
          {};

        template <class _Ptr1, class _Ptr2>
        struct __same_or_less_cv_qualified_imp<_Ptr1, _Ptr2, false>
        : false_type
          {};

        template <class _Ptr1, class _Ptr2, bool = is_scalar<_Ptr1>::value &&
        !is_pointer<_Ptr1>::value>
        struct __same_or_less_cv_qualified
        : __same_or_less_cv_qualified_imp<_Ptr1, _Ptr2>
          {};

        template <class _Ptr1, class _Ptr2>
        struct __same_or_less_cv_qualified<_Ptr1, _Ptr2, true>
        : false_type
          {};

// default_delete

        template <class _Tp>
        struct default_delete
          {
#ifndef _LIBCPP_HAS_NO_DEFAULTED_FUNCTIONS
            __attribute__((always_inline)) constexpr default_delete() noexcept = default;
#else
            __attribute__((always_inline)) constexpr default_delete() noexcept
              {}
#endif
            template <class _Up>
            __attribute__((always_inline)) default_delete(const default_delete<_Up>&,
                typename enable_if<is_convertible<_Up*, _Tp*>::value>::type* = 0) noexcept
              {}
            __attribute__((always_inline)) void operator() (_Tp* __ptr) const noexcept
              {
                static_assert(sizeof(_Tp) > 0, "default_delete can not delete incomplete type");
                delete __ptr;
              }
          };

        template <class _Tp>
        struct default_delete<_Tp[]>
          {
          public:
#ifndef _LIBCPP_HAS_NO_DEFAULTED_FUNCTIONS
            __attribute__((always_inline)) constexpr default_delete() noexcept = default;
#else
            __attribute__((always_inline)) constexpr default_delete() noexcept
              {}
#endif
            template <class _Up>
            __attribute__((always_inline)) default_delete(const default_delete<_Up[]>&,
                typename enable_if<__same_or_less_cv_qualified<_Up*, _Tp*>::value>::type* = 0) noexcept
              {}
            template <class _Up>
            __attribute__((always_inline))
            void operator() (_Up* __ptr,
                typename enable_if<__same_or_less_cv_qualified<_Up*, _Tp*>::value>::type* = 0) const noexcept
              {
                static_assert(sizeof(_Tp) > 0, "default_delete can not delete incomplete type");
                delete [] __ptr;
              }
          };

        template <class _Tp, class _Dp = default_delete<_Tp> >
        class unique_ptr
          {
          public:
            typedef _Tp element_type;
            typedef _Dp deleter_type;
            typedef typename __pointer_type<_Tp, deleter_type>::type pointer;
          private:
            __compressed_pair<pointer, deleter_type> __ptr_;

#ifdef _LIBCPP_HAS_NO_RVALUE_REFERENCES
            unique_ptr(unique_ptr&);
            template <class _Up, class _Ep>
            unique_ptr(unique_ptr<_Up, _Ep>&);
            unique_ptr& operator=(unique_ptr&);
            template <class _Up, class _Ep>
            unique_ptr& operator=(unique_ptr<_Up, _Ep>&);
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
            struct __nat
              { int __for_bool_;};

            typedef typename remove_reference<deleter_type>::type& _Dp_reference;
            typedef const typename remove_reference<deleter_type>::type& _Dp_const_reference;
          public:
            __attribute__((always_inline)) constexpr unique_ptr() noexcept
            : __ptr_(pointer())
              {
                static_assert(!is_pointer<deleter_type>::value,
                    "unique_ptr constructed with null function pointer deleter");
              }
            __attribute__((always_inline)) constexpr unique_ptr(nullptr_t) noexcept
            : __ptr_(pointer())
              {
                static_assert(!is_pointer<deleter_type>::value,
                    "unique_ptr constructed with null function pointer deleter");
              }
            __attribute__((always_inline)) explicit unique_ptr(pointer __p) noexcept
            : __ptr_(os::std::move(__p))
              {
                static_assert(!is_pointer<deleter_type>::value,
                    "unique_ptr constructed with null function pointer deleter");
              }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
            __attribute__((always_inline)) unique_ptr(pointer __p, typename conditional<
                is_reference<deleter_type>::value,
                deleter_type,
                typename add_lvalue_reference<const deleter_type>::type>::type __d)
            noexcept
            : __ptr_(__p, __d)
              {}

            __attribute__((always_inline)) unique_ptr(pointer __p, typename remove_reference<deleter_type>::type&& __d)
            noexcept
            : __ptr_(__p, os::std::move(__d))
              {
                static_assert(!is_reference<deleter_type>::value, "rvalue deleter bound to reference");
              }
            __attribute__((always_inline)) unique_ptr(unique_ptr&& __u) noexcept
            : __ptr_(__u.release(), os::std::forward<deleter_type>(__u.get_deleter()))
              {}
            template <class _Up, class _Ep>
            __attribute__((always_inline))
            unique_ptr(unique_ptr<_Up, _Ep>&& __u,
                typename enable_if
                <
                !is_array<_Up>::value &&
                is_convertible<typename unique_ptr<_Up, _Ep>::pointer, pointer>::value &&
                is_convertible<_Ep, deleter_type>::value &&
                (
                    !is_reference<deleter_type>::value ||
                    is_same<deleter_type, _Ep>::value
                ),
                __nat
                >::type = __nat()) noexcept
            : __ptr_(__u.release(), os::std::forward<_Ep>(__u.get_deleter()))
              {}

            template <class _Up>
            __attribute__((always_inline)) unique_ptr(auto_ptr<_Up>&& __p,
                typename enable_if<
                is_convertible<_Up*, _Tp*>::value &&
                is_same<_Dp, default_delete<_Tp> >::value,
                __nat
                >::type = __nat()) noexcept
            : __ptr_(__p.release())
              {
              }

            __attribute__((always_inline)) unique_ptr& operator=(unique_ptr&& __u) noexcept
              {
                reset(__u.release());
                __ptr_.second() = os::std::forward<deleter_type>(__u.get_deleter());
                return *this;
              }

            template <class _Up, class _Ep>
            __attribute__((always_inline))
            typename enable_if
            <
            !is_array<_Up>::value &&
            is_convertible<typename unique_ptr<_Up, _Ep>::pointer, pointer>::value &&
            is_assignable<deleter_type&, _Ep&&>::value,
            unique_ptr&
            >::type
            operator=(unique_ptr<_Up, _Ep>&& __u) noexcept
              {
                reset(__u.release());
                __ptr_.second() = os::std::forward<_Ep>(__u.get_deleter());
                return *this;
              }
#else  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
            __attribute__((always_inline)) operator __rv<unique_ptr>()
              {
                return __rv<unique_ptr>(*this);
              }

            __attribute__((always_inline)) unique_ptr(__rv<unique_ptr> __u)
            : __ptr_(__u->release(), os::std::forward<deleter_type>(__u->get_deleter()))
              {}

            template <class _Up, class _Ep>
            __attribute__((always_inline)) unique_ptr& operator=(unique_ptr<_Up, _Ep> __u)
              {
                reset(__u.release());
                __ptr_.second() = os::std::forward<deleter_type>(__u.get_deleter());
                return *this;
              }

            __attribute__((always_inline)) unique_ptr(pointer __p, deleter_type __d)
            : __ptr_(os::std::move(__p), os::std::move(__d))
              {}

            template <class _Up>
            __attribute__((always_inline))
            typename enable_if<
            is_convertible<_Up*, _Tp*>::value &&
            is_same<_Dp, default_delete<_Tp> >::value,
            unique_ptr&
            >::type
            operator=(auto_ptr<_Up> __p)
              { reset(__p.release()); return *this;}

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
            __attribute__((always_inline)) ~unique_ptr()
              { reset();}

            __attribute__((always_inline)) unique_ptr& operator=(nullptr_t) noexcept
              {
                reset();
                return *this;
              }

            __attribute__((always_inline)) typename add_lvalue_reference<_Tp>::type operator*() const
              { return *__ptr_.first();}
            __attribute__((always_inline)) pointer operator->() const noexcept
              { return __ptr_.first();}
            __attribute__((always_inline)) pointer get() const noexcept
              { return __ptr_.first();}
            __attribute__((always_inline)) _Dp_reference get_deleter() noexcept
              { return __ptr_.second();}
            __attribute__((always_inline)) _Dp_const_reference get_deleter() const noexcept
              { return __ptr_.second();}
            __attribute__((always_inline))
            _LIBCPP_EXPLICIT operator bool() const noexcept
              { return __ptr_.first() != nullptr;}

            __attribute__((always_inline)) pointer release() noexcept
              {
                pointer __t = __ptr_.first();
                __ptr_.first() = pointer();
                return __t;
              }

            __attribute__((always_inline)) void reset(pointer __p = pointer()) noexcept
              {
                pointer __tmp = __ptr_.first();
                __ptr_.first() = __p;
                if (__tmp)
                __ptr_.second()(__tmp);
              }

            __attribute__((always_inline)) void swap(unique_ptr& __u) noexcept
              { __ptr_.swap(__u.__ptr_);}
          };

        template <class _Tp, class _Dp>
        class unique_ptr<_Tp[], _Dp>
          {
          public:
            typedef _Tp element_type;
            typedef _Dp deleter_type;
            typedef typename __pointer_type<_Tp, deleter_type>::type pointer;
          private:
            __compressed_pair<pointer, deleter_type> __ptr_;

#ifdef _LIBCPP_HAS_NO_RVALUE_REFERENCES
            unique_ptr(unique_ptr&);
            template <class _Up>
            unique_ptr(unique_ptr<_Up>&);
            unique_ptr& operator=(unique_ptr&);
            template <class _Up>
            unique_ptr& operator=(unique_ptr<_Up>&);
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
            struct __nat
              { int __for_bool_;};

            typedef typename remove_reference<deleter_type>::type& _Dp_reference;
            typedef const typename remove_reference<deleter_type>::type& _Dp_const_reference;
          public:
            __attribute__((always_inline)) constexpr unique_ptr() noexcept
            : __ptr_(pointer())
              {
                static_assert(!is_pointer<deleter_type>::value,
                    "unique_ptr constructed with null function pointer deleter");
              }
            __attribute__((always_inline)) constexpr unique_ptr(nullptr_t) noexcept
            : __ptr_(pointer())
              {
                static_assert(!is_pointer<deleter_type>::value,
                    "unique_ptr constructed with null function pointer deleter");
              }
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
            template <class _Pp,
            class = typename enable_if<__same_or_less_cv_qualified<_Pp, pointer>::value>::type
            >
            __attribute__((always_inline)) explicit unique_ptr(_Pp __p) noexcept
            : __ptr_(__p)
              {
                static_assert(!is_pointer<deleter_type>::value,
                    "unique_ptr constructed with null function pointer deleter");
              }

            template <class _Pp,
            class = typename enable_if<__same_or_less_cv_qualified<_Pp, pointer>::value>::type
            >
            __attribute__((always_inline)) unique_ptr(_Pp __p, typename conditional<
                is_reference<deleter_type>::value,
                deleter_type,
                typename add_lvalue_reference<const deleter_type>::type>::type __d)
            noexcept
            : __ptr_(__p, __d)
              {}

            __attribute__((always_inline)) unique_ptr(nullptr_t, typename conditional<
                is_reference<deleter_type>::value,
                deleter_type,
                typename add_lvalue_reference<const deleter_type>::type>::type __d)
            noexcept
            : __ptr_(pointer(), __d)
              {}

            template <class _Pp,
            class = typename enable_if<__same_or_less_cv_qualified<_Pp, pointer>::value>::type
            >
            __attribute__((always_inline)) unique_ptr(_Pp __p, typename remove_reference<deleter_type>::type&& __d)
            noexcept
            : __ptr_(__p, os::std::move(__d))
              {
                static_assert(!is_reference<deleter_type>::value, "rvalue deleter bound to reference");
              }

            __attribute__((always_inline)) unique_ptr(nullptr_t, typename remove_reference<deleter_type>::type&& __d)
            noexcept
            : __ptr_(pointer(), os::std::move(__d))
              {
                static_assert(!is_reference<deleter_type>::value, "rvalue deleter bound to reference");
              }

            __attribute__((always_inline)) unique_ptr(unique_ptr&& __u) noexcept
            : __ptr_(__u.release(), os::std::forward<deleter_type>(__u.get_deleter()))
              {}

            __attribute__((always_inline)) unique_ptr& operator=(unique_ptr&& __u) noexcept
              {
                reset(__u.release());
                __ptr_.second() = os::std::forward<deleter_type>(__u.get_deleter());
                return *this;
              }

            template <class _Up, class _Ep>
            __attribute__((always_inline))
            unique_ptr(unique_ptr<_Up, _Ep>&& __u,
                typename enable_if
                <
                is_array<_Up>::value &&
                __same_or_less_cv_qualified<typename unique_ptr<_Up, _Ep>::pointer, pointer>::value
                && is_convertible<_Ep, deleter_type>::value &&
                (
                    !is_reference<deleter_type>::value ||
                    is_same<deleter_type, _Ep>::value
                ),
                __nat
                >::type = __nat()
            ) noexcept
            : __ptr_(__u.release(), os::std::forward<deleter_type>(__u.get_deleter()))
              {}

            template <class _Up, class _Ep>
            __attribute__((always_inline))
            typename enable_if
            <
            is_array<_Up>::value &&
            __same_or_less_cv_qualified<typename unique_ptr<_Up, _Ep>::pointer, pointer>::value &&
            is_assignable<deleter_type&, _Ep&&>::value,
            unique_ptr&
            >::type
            operator=(unique_ptr<_Up, _Ep>&& __u) noexcept
              {
                reset(__u.release());
                __ptr_.second() = os::std::forward<_Ep>(__u.get_deleter());
                return *this;
              }
#else  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
            __attribute__((always_inline)) explicit unique_ptr(pointer __p)
            : __ptr_(__p)
              {
                static_assert(!is_pointer<deleter_type>::value,
                    "unique_ptr constructed with null function pointer deleter");
              }

            __attribute__((always_inline)) unique_ptr(pointer __p, deleter_type __d)
            : __ptr_(__p, os::std::forward<deleter_type>(__d))
              {}

            __attribute__((always_inline)) unique_ptr(nullptr_t, deleter_type __d)
            : __ptr_(pointer(), os::std::forward<deleter_type>(__d))
              {}

            __attribute__((always_inline)) operator __rv<unique_ptr>()
              {
                return __rv<unique_ptr>(*this);
              }

            __attribute__((always_inline)) unique_ptr(__rv<unique_ptr> __u)
            : __ptr_(__u->release(), os::std::forward<deleter_type>(__u->get_deleter()))
              {}

            __attribute__((always_inline)) unique_ptr& operator=(__rv<unique_ptr> __u)
              {
                reset(__u->release());
                __ptr_.second() = os::std::forward<deleter_type>(__u->get_deleter());
                return *this;
              }

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
            __attribute__((always_inline)) ~unique_ptr()
              { reset();}

            __attribute__((always_inline)) unique_ptr& operator=(nullptr_t) noexcept
              {
                reset();
                return *this;
              }

            __attribute__((always_inline)) typename add_lvalue_reference<_Tp>::type operator[](size_t __i) const
              { return __ptr_.first()[__i];}
            __attribute__((always_inline)) pointer get() const noexcept
              { return __ptr_.first();}
            __attribute__((always_inline)) _Dp_reference get_deleter() noexcept
              { return __ptr_.second();}
            __attribute__((always_inline)) _Dp_const_reference get_deleter() const noexcept
              { return __ptr_.second();}
            __attribute__((always_inline))
            _LIBCPP_EXPLICIT operator bool() const noexcept
              { return __ptr_.first() != nullptr;}

            __attribute__((always_inline)) pointer release() noexcept
              {
                pointer __t = __ptr_.first();
                __ptr_.first() = pointer();
                return __t;
              }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
            template <class _Pp,
            class = typename enable_if<__same_or_less_cv_qualified<_Pp, pointer>::value>::type
            >
            __attribute__((always_inline)) void reset(_Pp __p) noexcept
              {
                pointer __tmp = __ptr_.first();
                __ptr_.first() = __p;
                if (__tmp)
                __ptr_.second()(__tmp);
              }
            __attribute__((always_inline)) void reset(nullptr_t) noexcept
              {
                pointer __tmp = __ptr_.first();
                __ptr_.first() = nullptr;
                if (__tmp)
                __ptr_.second()(__tmp);
              }
            __attribute__((always_inline)) void reset() noexcept
              {
                pointer __tmp = __ptr_.first();
                __ptr_.first() = nullptr;
                if (__tmp)
                __ptr_.second()(__tmp);
              }
#else  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
            __attribute__((always_inline)) void reset(pointer __p = pointer())
              {
                pointer __tmp = __ptr_.first();
                __ptr_.first() = __p;
                if (__tmp)
                __ptr_.second()(__tmp);
              }
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
            __attribute__((always_inline)) void swap(unique_ptr& __u)
              { __ptr_.swap(__u.__ptr_);}
          private:

#ifdef _LIBCPP_HAS_NO_RVALUE_REFERENCES
            template <class _Up>
            explicit unique_ptr(_Up);
            template <class _Up>
            unique_ptr(_Up __u,
                typename conditional<
                is_reference<deleter_type>::value,
                deleter_type,
                typename add_lvalue_reference<const deleter_type>::type>::type,
                typename enable_if
                <
                is_convertible<_Up, pointer>::value,
                __nat
                >::type = __nat());
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
          };

        template <class _Tp, class _Dp>
        inline __attribute__((always_inline))
        void
        swap(unique_ptr<_Tp, _Dp>& __x, unique_ptr<_Tp, _Dp>& __y) noexcept
          { __x.swap(__y);}

        template <class _T1, class _D1, class _T2, class _D2>
        inline __attribute__((always_inline))
        bool
        operator==(const unique_ptr<_T1, _D1>& __x, const unique_ptr<_T2, _D2>& __y)
          { return __x.get() == __y.get();}

        template <class _T1, class _D1, class _T2, class _D2>
        inline __attribute__((always_inline))
        bool
        operator!=(const unique_ptr<_T1, _D1>& __x, const unique_ptr<_T2, _D2>& __y)
          { return !(__x == __y);}

        template <class _T1, class _D1, class _T2, class _D2>
        inline __attribute__((always_inline))
        bool
        operator< (const unique_ptr<_T1, _D1>& __x, const unique_ptr<_T2, _D2>& __y)
          {
            typedef typename unique_ptr<_T1, _D1>::pointer _P1;
            typedef typename unique_ptr<_T2, _D2>::pointer _P2;
            typedef typename common_type<_P1, _P2>::type _V;
            return less<_V>()(__x.get(), __y.get());
          }

        template <class _T1, class _D1, class _T2, class _D2>
        inline __attribute__((always_inline))
        bool
        operator> (const unique_ptr<_T1, _D1>& __x, const unique_ptr<_T2, _D2>& __y)
          { return __y < __x;}

        template <class _T1, class _D1, class _T2, class _D2>
        inline __attribute__((always_inline))
        bool
        operator<=(const unique_ptr<_T1, _D1>& __x, const unique_ptr<_T2, _D2>& __y)
          { return !(__y < __x);}

        template <class _T1, class _D1, class _T2, class _D2>
        inline __attribute__((always_inline))
        bool
        operator>=(const unique_ptr<_T1, _D1>& __x, const unique_ptr<_T2, _D2>& __y)
          { return !(__x < __y);}

        template <class _T1, class _D1>
        inline __attribute__((always_inline))
        bool
        operator==(const unique_ptr<_T1, _D1>& __x, nullptr_t) noexcept
          {
            return !__x;
          }

        template <class _T1, class _D1>
        inline __attribute__((always_inline))
        bool
        operator==(nullptr_t, const unique_ptr<_T1, _D1>& __x) noexcept
          {
            return !__x;
          }

        template <class _T1, class _D1>
        inline __attribute__((always_inline))
        bool
        operator!=(const unique_ptr<_T1, _D1>& __x, nullptr_t) noexcept
          {
            return static_cast<bool>(__x);
          }

        template <class _T1, class _D1>
        inline __attribute__((always_inline))
        bool
        operator!=(nullptr_t, const unique_ptr<_T1, _D1>& __x) noexcept
          {
            return static_cast<bool>(__x);
          }

        template <class _T1, class _D1>
        inline __attribute__((always_inline))
        bool
        operator<(const unique_ptr<_T1, _D1>& __x, nullptr_t)
          {
            typedef typename unique_ptr<_T1, _D1>::pointer _P1;
            return less<_P1>()(__x.get(), nullptr);
          }

        template <class _T1, class _D1>
        inline __attribute__((always_inline))
        bool
        operator<(nullptr_t, const unique_ptr<_T1, _D1>& __x)
          {
            typedef typename unique_ptr<_T1, _D1>::pointer _P1;
            return less<_P1>()(nullptr, __x.get());
          }

        template <class _T1, class _D1>
        inline __attribute__((always_inline))
        bool
        operator>(const unique_ptr<_T1, _D1>& __x, nullptr_t)
          {
            return nullptr < __x;
          }

        template <class _T1, class _D1>
        inline __attribute__((always_inline))
        bool
        operator>(nullptr_t, const unique_ptr<_T1, _D1>& __x)
          {
            return __x < nullptr;
          }

        template <class _T1, class _D1>
        inline __attribute__((always_inline))
        bool
        operator<=(const unique_ptr<_T1, _D1>& __x, nullptr_t)
          {
            return !(nullptr < __x);
          }

        template <class _T1, class _D1>
        inline __attribute__((always_inline))
        bool
        operator<=(nullptr_t, const unique_ptr<_T1, _D1>& __x)
          {
            return !(__x < nullptr);
          }

        template <class _T1, class _D1>
        inline __attribute__((always_inline))
        bool
        operator>=(const unique_ptr<_T1, _D1>& __x, nullptr_t)
          {
            return !(__x < nullptr);
          }

        template <class _T1, class _D1>
        inline __attribute__((always_inline))
        bool
        operator>=(nullptr_t, const unique_ptr<_T1, _D1>& __x)
          {
            return !(nullptr < __x);
          }

#ifdef _LIBCPP_HAS_NO_RVALUE_REFERENCES

        template <class _Tp, class _Dp>
        inline __attribute__((always_inline))
        unique_ptr<_Tp, _Dp>
        move(unique_ptr<_Tp, _Dp>& __t)
          {
            return unique_ptr<_Tp, _Dp>(__rv<unique_ptr<_Tp, _Dp> >(__t));
          }

#endif

        template <class _Tp> struct hash;

// We use murmur2 when size_t is 32 bits, and cityhash64 when size_t
// is 64 bits.  This is because cityhash64 uses 64bit x 64bit
// multiplication, which can be very slow on 32-bit systems.
        template <class _Size, size_t = sizeof(_Size)*__CHAR_BIT__>
        struct __murmur2_or_cityhash;

        template <class _Size>
        struct __murmur2_or_cityhash<_Size, 32>
          {
            _Size operator()(const void* __key, _Size __len);
          };

// murmur2
        template <class _Size>
        _Size
        __murmur2_or_cityhash<_Size, 32>::operator()(const void* __key, _Size __len)
          {
            const _Size __m = 0x5bd1e995;
            const _Size __r = 24;
            _Size __h = __len;
            const unsigned char* __data = static_cast<const unsigned char*>(__key);
            for (; __len >= 4; __data += 4, __len -= 4)
              {
                _Size __k = *(const _Size*)__data;
                __k *= __m;
                __k ^= __k >> __r;
                __k *= __m;
                __h *= __m;
                __h ^= __k;
              }
            switch (__len)
              {
                case 3:
                __h ^= __data[2] << 16;
                case 2:
                __h ^= __data[1] << 8;
                case 1:
                __h ^= __data[0];
                __h *= __m;
              }
            __h ^= __h >> 13;
            __h *= __m;
            __h ^= __h >> 15;
            return __h;
          }

        template <class _Size>
        struct __murmur2_or_cityhash<_Size, 64>
          {
            _Size operator()(const void* __key, _Size __len);

          private:
            // Some primes between 2^63 and 2^64.
            static const _Size __k0 = 0xc3a5c85c97cb3127ULL;
            static const _Size __k1 = 0xb492b66fbe98f273ULL;
            static const _Size __k2 = 0x9ae16a3b2f90404fULL;
            static const _Size __k3 = 0xc949d7c7509e6557ULL;

            static _Size __rotate(_Size __val, int __shift)
              {
                return __shift == 0 ? __val : ((__val >> __shift) | (__val << (64 - __shift)));
              }

            static _Size __rotate_by_at_least_1(_Size __val, int __shift)
              {
                return (__val >> __shift) | (__val << (64 - __shift));
              }

            static _Size __shift_mix(_Size __val)
              {
                return __val ^ (__val >> 47);
              }

            static _Size __hash_len_16(_Size __u, _Size __v)
              {
                const _Size __mul = 0x9ddfea08eb382d69ULL;
                _Size __a = (__u ^ __v) * __mul;
                __a ^= (__a >> 47);
                _Size __b = (__v ^ __a) * __mul;
                __b ^= (__b >> 47);
                __b *= __mul;
                return __b;
              }

            static _Size __hash_len_0_to_16(const char* __s, _Size __len)
              {
                if (__len > 8)
                  {
                    const _Size __a = *(const _Size*)__s;
                    const _Size __b = *(const _Size*)(__s + __len - 8);
                    return __hash_len_16(__a, __rotate_by_at_least_1(__b + __len, __len)) ^ __b;
                  }
                if (__len >= 4)
                  {
#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wcast-align"
#endif
                    const uint32_t __a = *(const uint32_t*)(__s);
#pragma GCC diagnostic pop
                    const uint32_t __b = *(const uint32_t*)(__s + __len - 4);
                    return __hash_len_16(__len + (__a << 3), __b);
                  }
                if (__len > 0)
                  {
#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wsign-conversion"
#endif
                    const unsigned char __a = __s[0];
#pragma GCC diagnostic pop
                    const unsigned char __b = __s[__len >> 1];
                    const unsigned char __c = __s[__len - 1];
                    const uint32_t __y = static_cast<uint32_t>(__a) +
                    (static_cast<uint32_t>(__b) << 8);
                    const uint32_t __z = __len + (static_cast<uint32_t>(__c) << 2);
                    return __shift_mix(__y * __k2 ^ __z * __k3) * __k2;
                  }
                return __k2;
              }

            static _Size __hash_len_17_to_32(const char *__s, _Size __len)
              {
                const _Size __a = *(const _Size*)(__s) * __k1;
                const _Size __b = *(const _Size*)(__s + 8);
                const _Size __c = *(const _Size*)(__s + __len - 8) * __k2;
                const _Size __d = *(const _Size*)(__s + __len - 16) * __k0;
                return __hash_len_16(__rotate(__a - __b, 43) + __rotate(__c, 30) + __d,
                    __a + __rotate(__b ^ __k3, 20) - __c + __len);
              }

            // Return a 16-byte hash for 48 bytes.  Quick and dirty.
            // Callers do best to use "random-looking" values for a and b.
            static pair<_Size, _Size> __weak_hash_len_32_with_seeds(
                _Size __w, _Size __x, _Size __y, _Size __z, _Size __a, _Size __b)
              {
                __a += __w;
                __b = __rotate(__b + __a + __z, 21);
                const _Size __c = __a;
                __a += __x;
                __a += __y;
                __b += __rotate(__a, 44);
                return pair<_Size, _Size>(__a + __z, __b + __c);
              }

            // Return a 16-byte hash for s[0] ... s[31], a, and b.  Quick and dirty.
            static pair<_Size, _Size> __weak_hash_len_32_with_seeds(
                const char* __s, _Size __a, _Size __b)
              {
                return __weak_hash_len_32_with_seeds(*(const _Size*)(__s),
                    *(const _Size*)(__s + 8),
                    *(const _Size*)(__s + 16),
                    *(const _Size*)(__s + 24),
                    __a,
                    __b);
              }

            // Return an 8-byte hash for 33 to 64 bytes.
            static _Size __hash_len_33_to_64(const char *__s, size_t __len)
              {
                _Size __z = *(const _Size*)(__s + 24);
                _Size __a = *(const _Size*)(__s) +
                (__len + *(const _Size*)(__s + __len - 16)) * __k0;
                _Size __b = __rotate(__a + __z, 52);
                _Size __c = __rotate(__a, 37);
                __a += *(const _Size*)(__s + 8);
                __c += __rotate(__a, 7);
                __a += *(const _Size*)(__s + 16);
                _Size __vf = __a + __z;
                _Size __vs = __b + __rotate(__a, 31) + __c;
                __a = *(const _Size*)(__s + 16) + *(const _Size*)(__s + __len - 32);
                __z += *(const _Size*)(__s + __len - 8);
                __b = __rotate(__a + __z, 52);
                __c = __rotate(__a, 37);
                __a += *(const _Size*)(__s + __len - 24);
                __c += __rotate(__a, 7);
                __a += *(const _Size*)(__s + __len - 16);
                _Size __wf = __a + __z;
                _Size __ws = __b + __rotate(__a, 31) + __c;
                _Size __r = __shift_mix((__vf + __ws) * __k2 + (__wf + __vs) * __k0);
                return __shift_mix(__r * __k0 + __vs) * __k2;
              }
          };

// cityhash64
        template <class _Size>
        _Size
        __murmur2_or_cityhash<_Size, 64>::operator()(const void* __key, _Size __len)
          {
            const char* __s = static_cast<const char*>(__key);
            if (__len <= 32)
              {
                if (__len <= 16)
                  {
                    return __hash_len_0_to_16(__s, __len);
                  }
                else
                  {
                    return __hash_len_17_to_32(__s, __len);
                  }
              }
            else if (__len <= 64)
              {
                return __hash_len_33_to_64(__s, __len);
              }

            // For strings over 64 bytes we hash the end first, and then as we
            // loop we keep 56 bytes of state: v, w, x, y, and z.
            _Size __x = *(const _Size*)(__s + __len - 40);
            _Size __y = *(const _Size*)(__s + __len - 16) +
            *(const _Size*)(__s + __len - 56);
            _Size __z = __hash_len_16(*(const _Size*)(__s + __len - 48) + __len,
                *(const _Size*)(__s + __len - 24));
            pair<_Size, _Size> __v = __weak_hash_len_32_with_seeds(__s + __len - 64, __len, __z);
            pair<_Size, _Size> __w = __weak_hash_len_32_with_seeds(__s + __len - 32, __y + __k1, __x);
            __x = __x * __k1 + *(const _Size*)(__s);

            // Decrease len to the nearest multiple of 64, and operate on 64-byte chunks.
            __len = (__len - 1) & ~static_cast<_Size>(63);
            do
              {
                __x = __rotate(__x + __y + __v.first + *(const _Size*)(__s + 8), 37) * __k1;
                __y = __rotate(__y + __v.second + *(const _Size*)(__s + 48), 42) * __k1;
                __x ^= __w.second;
                __y += __v.first + *(const _Size*)(__s + 40);
                __z = __rotate(__z + __w.first, 33) * __k1;
                __v = __weak_hash_len_32_with_seeds(__s, __v.second * __k1, __x + __w.first);
                __w = __weak_hash_len_32_with_seeds(__s + 32, __z + __w.second,
                    __y + *(const _Size*)(__s + 16));
                std::swap(__z, __x);
                __s += 64;
                __len -= 64;
              }while (__len != 0);
            return __hash_len_16(
                __hash_len_16(__v.first, __w.first) + __shift_mix(__y) * __k1 + __z,
                __hash_len_16(__v.second, __w.second) + __x);
          }

        template <class _Tp, size_t = sizeof(_Tp) / sizeof(size_t)>
        struct __scalar_hash;

        template <class _Tp>
        struct __scalar_hash<_Tp, 0>
        : public unary_function<_Tp, size_t>
          {
            __attribute__((always_inline))
            size_t operator()(_Tp __v) const noexcept
              {
                union
                  {
                    _Tp __t;
                    size_t __a;
                  }__u;
                __u.__a = 0;
                __u.__t = __v;
                return __u.__a;
              }
          };

        template <class _Tp>
        struct __scalar_hash<_Tp, 1>
        : public unary_function<_Tp, size_t>
          {
            __attribute__((always_inline))
            size_t operator()(_Tp __v) const noexcept
              {
                union
                  {
                    _Tp __t;
                    size_t __a;
                  }__u;
                __u.__t = __v;
                return __u.__a;
              }
          };

        template <class _Tp>
        struct __scalar_hash<_Tp, 2>
        : public unary_function<_Tp, size_t>
          {
            __attribute__((always_inline))
            size_t operator()(_Tp __v) const noexcept
              {
                union
                  {
                    _Tp __t;
                    struct s
                      {
                        size_t __a;
                        size_t __b;
                      };
                  }__u;
                __u.__t = __v;
                return __murmur2_or_cityhash<size_t>()(&__u, sizeof(__u));
              }
          };

        template <class _Tp>
        struct __scalar_hash<_Tp, 3>
        : public unary_function<_Tp, size_t>
          {
            __attribute__((always_inline))
            size_t operator()(_Tp __v) const noexcept
              {
                union
                  {
                    _Tp __t;
                    struct s
                      {
                        size_t __a;
                        size_t __b;
                        size_t __c;
                      };
                  }__u;
                __u.__t = __v;
                return __murmur2_or_cityhash<size_t>()(&__u, sizeof(__u));
              }
          };

        template <class _Tp>
        struct __scalar_hash<_Tp, 4>
        : public unary_function<_Tp, size_t>
          {
            __attribute__((always_inline))
            size_t operator()(_Tp __v) const noexcept
              {
                union
                  {
                    _Tp __t;
                    struct s
                      {
                        size_t __a;
                        size_t __b;
                        size_t __c;
                        size_t __d;
                      };
                  }__u;
                __u.__t = __v;
                return __murmur2_or_cityhash<size_t>()(&__u, sizeof(__u));
              }
          };

        template<class _Tp>
        struct hash<_Tp*>
        : public unary_function<_Tp*, size_t>
          {
            __attribute__((always_inline))
            size_t operator()(_Tp* __v) const noexcept
              {
                union
                  {
                    _Tp* __t;
                    size_t __a;
                  }__u;
                __u.__t = __v;
                return __murmur2_or_cityhash<size_t>()(&__u, sizeof(__u));
              }
          };

        template <class _Tp, class _Dp>
        struct hash<unique_ptr<_Tp, _Dp> >
          {
            typedef unique_ptr<_Tp, _Dp> argument_type;
            typedef size_t result_type;
            __attribute__((always_inline))
            result_type operator()(const argument_type& __ptr) const noexcept
              {
                typedef typename argument_type::pointer pointer;
                return hash<pointer>()(__ptr.get());
              }
          };

        struct __destruct_n
          {
          private:
            size_t size;

            template <class _Tp>
            __attribute__((always_inline)) void __process(_Tp* __p, false_type) noexcept
              { for (size_t __i = 0; __i < size; ++__i, ++__p) __p->~_Tp();}

            template <class _Tp>
            __attribute__((always_inline)) void __process(_Tp*, true_type) noexcept
              {}

            __attribute__((always_inline)) void __incr(false_type) noexcept
              { ++size;}
            __attribute__((always_inline)) void __incr(true_type) noexcept
              {}

            __attribute__((always_inline)) void __set(size_t __s, false_type) noexcept
              { size = __s;}
            __attribute__((always_inline)) void __set(size_t, true_type) noexcept
              {}
          public:
            __attribute__((always_inline)) explicit __destruct_n(size_t __s) noexcept
            : size(__s)
              {}

            template <class _Tp>
            __attribute__((always_inline)) void __incr(_Tp*) noexcept
              { __incr(integral_constant<bool, is_trivially_destructible<_Tp>::value>());}

            template <class _Tp>
            __attribute__((always_inline)) void __set(size_t __s, _Tp*) noexcept
              { __set(__s, integral_constant<bool, is_trivially_destructible<_Tp>::value>());}

            template <class _Tp>
            __attribute__((always_inline)) void operator()(_Tp* __p) noexcept
              { __process(__p, integral_constant<bool, is_trivially_destructible<_Tp>::value>());}
          };

        template <class _Alloc>
        class __allocator_destructor
          {
            typedef allocator_traits<_Alloc> __alloc_traits;
          public:
            typedef typename __alloc_traits::pointer pointer;
            typedef typename __alloc_traits::size_type size_type;
          private:
            _Alloc& __alloc_;
            size_type __s_;
          public:
            __attribute__((always_inline)) __allocator_destructor(_Alloc& __a, size_type __s)
            noexcept
            : __alloc_(__a), __s_(__s)
              {}
            __attribute__((always_inline))
            void operator()(pointer __p) noexcept
              { __alloc_traits::deallocate(__alloc_, __p, __s_);}
          };

        template <class _InputIterator, class _ForwardIterator>
        _ForwardIterator
        uninitialized_copy(_InputIterator __f, _InputIterator __l, _ForwardIterator __r)
          {
            typedef typename iterator_traits<_ForwardIterator>::value_type value_type;
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
            _ForwardIterator __s = __r;
            try
              {
#endif
                for (; __f != __l; ++__f, ++__r)
                ::new(&*__r) value_type(*__f);
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
              }
            catch (...)
              {
                for (; __s != __r; ++__s)
                __s->~value_type();
                throw;
              }
#endif
            return __r;
          }

        template <class _InputIterator, class _Size, class _ForwardIterator>
        _ForwardIterator
        uninitialized_copy_n(_InputIterator __f, _Size __n, _ForwardIterator __r)
          {
            typedef typename iterator_traits<_ForwardIterator>::value_type value_type;
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
            _ForwardIterator __s = __r;
            try
              {
#endif
                for (; __n > 0; ++__f, ++__r, --__n)
                ::new(&*__r) value_type(*__f);
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
              }
            catch (...)
              {
                for (; __s != __r; ++__s)
                __s->~value_type();
                throw;
              }
#endif
            return __r;
          }

        template <class _ForwardIterator, class _Tp>
        void
        uninitialized_fill(_ForwardIterator __f, _ForwardIterator __l, const _Tp& __x)
          {
            typedef typename iterator_traits<_ForwardIterator>::value_type value_type;
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
            _ForwardIterator __s = __f;
            try
              {
#endif
                for (; __f != __l; ++__f)
                ::new(&*__f) value_type(__x);
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
              }
            catch (...)
              {
                for (; __s != __f; ++__s)
                __s->~value_type();
                throw;
              }
#endif
          }

        template <class _ForwardIterator, class _Size, class _Tp>
        _ForwardIterator
        uninitialized_fill_n(_ForwardIterator __f, _Size __n, const _Tp& __x)
          {
            typedef typename iterator_traits<_ForwardIterator>::value_type value_type;
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
            _ForwardIterator __s = __f;
            try
              {
#endif
                for (; __n > 0; ++__f, --__n)
                ::new(&*__f) value_type(__x);
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
              }
            catch (...)
              {
                for (; __s != __f; ++__s)
                __s->~value_type();
                throw;
              }
#endif
            return __f;
          }

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)

        class bad_weak_ptr
        : public os::std::exception
          {
          public:
            virtual ~bad_weak_ptr() noexcept;
            virtual const char* what() const noexcept;
          };

#endif

        template<class _Tp> class weak_ptr;

        class __shared_count
          {
            __shared_count(const __shared_count&);
            __shared_count& operator=(const __shared_count&);

          protected:
            long __shared_owners_;
            virtual ~__shared_count();
          private:
            virtual void __on_zero_shared() noexcept = 0;

          public:
            __attribute__((always_inline))
            explicit __shared_count(long __refs = 0) noexcept
            : __shared_owners_(__refs)
              {}

            void __add_shared() noexcept;
            bool __release_shared() noexcept;
            __attribute__((always_inline))
            long use_count() const noexcept
              { return __shared_owners_ + 1;}
          };

        class __shared_weak_count
        : private __shared_count
          {
            long __shared_weak_owners_;

          public:
            __attribute__((always_inline))
            explicit __shared_weak_count(long __refs = 0) noexcept
            : __shared_count(__refs),
            __shared_weak_owners_(__refs)
              {}
          protected:
            virtual ~__shared_weak_count();

          public:
            void __add_shared() noexcept;
            void __add_weak() noexcept;
            void __release_shared() noexcept;
            void __release_weak() noexcept;
            __attribute__((always_inline))
            long use_count() const noexcept
              { return __shared_count::use_count();}
            __shared_weak_count* lock() noexcept;

            // purposefully not protected with #ifndef _LIBCPP_NO_RTTI because doing so
            //  breaks ABI for those clients who need to compile their projects with
            //    -fno-rtti and yet link against a libc++.dylib compiled without -fno-rtti.
            virtual const void* __get_deleter(const type_info&) const noexcept;
          private:
            virtual void __on_zero_shared_weak() noexcept = 0;
          };

        template <class _Tp, class _Dp, class _Alloc>
        class __shared_ptr_pointer
        : public __shared_weak_count
          {
            __compressed_pair<__compressed_pair<_Tp, _Dp>, _Alloc> __data_;
          public:
            __attribute__((always_inline))
            __shared_ptr_pointer(_Tp __p, _Dp __d, _Alloc __a)
            : __data_(__compressed_pair<_Tp, _Dp>(__p, os::std::move(__d)), os::std::move(__a))
              {}

#ifndef _LIBCPP_NO_RTTI
            virtual const void* __get_deleter(const type_info&) const noexcept;
#endif

          private:
            virtual void __on_zero_shared() noexcept;
            virtual void __on_zero_shared_weak() noexcept;
          };

#ifndef _LIBCPP_NO_RTTI

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
        template <class _Tp, class _Dp, class _Alloc>
        const void*
        __shared_ptr_pointer<_Tp, _Dp, _Alloc>::__get_deleter(const type_info& __t) const noexcept
          {
            return __t == typeid(_Dp) ? &__data_.first().second() : 0;
          }
#endif // defined(OS_SKIP_NOT_YET_IMPLEMENTED)
#endif  // _LIBCPP_NO_RTTI
        template <class _Tp, class _Dp, class _Alloc>
        void
        __shared_ptr_pointer<_Tp, _Dp, _Alloc>::__on_zero_shared() noexcept
          {
            __data_.first().second()(__data_.first().first());
            __data_.first().second().~_Dp();
          }

        template <class _Tp, class _Dp, class _Alloc>
        void
        __shared_ptr_pointer<_Tp, _Dp, _Alloc>::__on_zero_shared_weak() noexcept
          {
            typename _Alloc::template rebind<__shared_ptr_pointer>::other __a(__data_.second());
            __data_.second().~_Alloc();
            __a.deallocate(this, 1);
          }

        template <class _Tp, class _Alloc>
        class __shared_ptr_emplace
        : public __shared_weak_count
          {
            __compressed_pair<_Alloc, _Tp> __data_;
          public:
#ifndef _LIBCPP_HAS_NO_VARIADICS

            __attribute__((always_inline))
            __shared_ptr_emplace(_Alloc __a)
            : __data_(os::std::move(__a))
              {}

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
            template <class ..._Args>
            __attribute__((always_inline))
            __shared_ptr_emplace(_Alloc __a, _Args&& ...__args)
            : __data_(piecewise_construct, os::std::forward_as_tuple(__a),
                os::std::forward_as_tuple(os::std::forward<_Args>(__args)...))
              {}

#endif // defined(OS_SKIP_NOT_YET_IMPLEMENTED)
#else  // _LIBCPP_HAS_NO_VARIADICS
            __attribute__((always_inline))
            __shared_ptr_emplace(_Alloc __a)
            : __data_(__a)
              {}

            template <class _A0>
            __attribute__((always_inline))
            __shared_ptr_emplace(_Alloc __a, _A0& __a0)
            : __data_(__a, _Tp(__a0))
              {}

            template <class _A0, class _A1>
            __attribute__((always_inline))
            __shared_ptr_emplace(_Alloc __a, _A0& __a0, _A1& __a1)
            : __data_(__a, _Tp(__a0, __a1))
              {}

            template <class _A0, class _A1, class _A2>
            __attribute__((always_inline))
            __shared_ptr_emplace(_Alloc __a, _A0& __a0, _A1& __a1, _A2& __a2)
            : __data_(__a, _Tp(__a0, __a1, __a2))
              {}

#endif  // _LIBCPP_HAS_NO_VARIADICS
          private:
            virtual void __on_zero_shared() noexcept;
            virtual void __on_zero_shared_weak() noexcept;
          public:
            __attribute__((always_inline))
            _Tp* get() noexcept
              { return &__data_.second();}
          };

        template <class _Tp, class _Alloc>
        void
        __shared_ptr_emplace<_Tp, _Alloc>::__on_zero_shared() noexcept
          {
            __data_.second().~_Tp();
          }

        template <class _Tp, class _Alloc>
        void
        __shared_ptr_emplace<_Tp, _Alloc>::__on_zero_shared_weak() noexcept
          {
            typename _Alloc::template rebind<__shared_ptr_emplace>::other __a(__data_.first());
            __data_.first().~_Alloc();
            __a.deallocate(this, 1);
          }

        template<class _Tp> class enable_shared_from_this;

        template<class _Tp>
        class shared_ptr
          {
          public:
            typedef _Tp element_type;
          private:
            element_type* __ptr_;
            __shared_weak_count* __cntrl_;

            struct __nat
              { int __for_bool_;};
          public:
            constexpr shared_ptr() noexcept;
            constexpr shared_ptr(nullptr_t) noexcept;
            template<class _Yp,
            class = typename enable_if
            <
            is_convertible<_Yp*, element_type*>::value
            >::type
            >
            explicit shared_ptr(_Yp* __p);
            template<class _Yp, class _Dp,
            class = typename enable_if
            <
            is_convertible<_Yp*, element_type*>::value
            >::type
            >
            shared_ptr(_Yp* __p, _Dp __d);
            template<class _Yp, class _Dp, class _Alloc,
            class = typename enable_if
            <
            is_convertible<_Yp*, element_type*>::value
            >::type
            >
            shared_ptr(_Yp* __p, _Dp __d, _Alloc __a);
            template <class _Dp> shared_ptr(nullptr_t __p, _Dp __d);
            template <class _Dp, class _Alloc> shared_ptr(nullptr_t __p, _Dp __d, _Alloc __a);
            template<class _Yp> shared_ptr(const shared_ptr<_Yp>& __r, element_type* __p) noexcept;
            shared_ptr(const shared_ptr& __r) noexcept;
            template<class _Yp>
            shared_ptr(const shared_ptr<_Yp>& __r,
                typename enable_if<is_convertible<_Yp*, _Tp*>::value, __nat>::type = __nat())
            noexcept;
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
            shared_ptr(shared_ptr&& __r) noexcept;
            template<class _Yp> shared_ptr(shared_ptr<_Yp>&& __r,
                typename enable_if<is_convertible<_Yp*, _Tp*>::value, __nat>::type = __nat())
            noexcept;
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
            template<class _Yp> explicit shared_ptr(const weak_ptr<_Yp>& __r,
                typename enable_if<is_convertible<_Yp*, _Tp*>::value, __nat>::type= __nat());
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
            template<class _Yp,
            class = typename enable_if
            <
            is_convertible<_Yp*, element_type*>::value
            >::type
            >
            shared_ptr(auto_ptr<_Yp>&& __r);
#else
            template<class _Yp,
            class = typename enable_if
            <
            is_convertible<_Yp*, element_type*>::value
            >::type
            >
            shared_ptr(auto_ptr<_Yp> __r);
#endif
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
            template <class _Yp, class _Dp,
            class = typename enable_if
            <
            !is_array<_Yp>::value &&
            is_convertible<typename unique_ptr<_Yp, _Dp>::pointer, element_type*>::value
            >::type
            >
            shared_ptr(unique_ptr<_Yp, _Dp>&&,
                typename enable_if<!is_lvalue_reference<_Dp>::value, __nat>::type = __nat());
            template <class _Yp, class _Dp,
            class = typename enable_if
            <
            !is_array<_Yp>::value &&
            is_convertible<typename unique_ptr<_Yp, _Dp>::pointer, element_type*>::value
            >::type
            >
            shared_ptr(unique_ptr<_Yp, _Dp>&&,
                typename enable_if<is_lvalue_reference<_Dp>::value, __nat>::type = __nat());
#else  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
            template <class _Yp, class _Dp,
            class = typename enable_if
            <
            !is_array<_Yp>::value &&
            is_convertible<typename unique_ptr<_Yp, _Dp>::pointer, element_type*>::value
            >::type
            > shared_ptr(unique_ptr<_Yp, _Dp>,
                typename enable_if<!is_lvalue_reference<_Dp>::value, __nat>::type = __nat());
            template <class _Yp, class _Dp,
            class = typename enable_if
            <
            !is_array<_Yp>::value &&
            is_convertible<typename unique_ptr<_Yp, _Dp>::pointer, element_type*>::value
            >::type
            >
            shared_ptr(unique_ptr<_Yp, _Dp>,
                typename enable_if<is_lvalue_reference<_Dp>::value, __nat>::type = __nat());
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
            ~shared_ptr();

            shared_ptr& operator=(const shared_ptr& __r) noexcept;
            template<class _Yp>
            typename enable_if
            <
            is_convertible<_Yp*, element_type*>::value,
            shared_ptr&
            >::type
            operator=(const shared_ptr<_Yp>& __r) noexcept;
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
            shared_ptr& operator=(shared_ptr&& __r) noexcept;
            template<class _Yp>
            typename enable_if
            <
            is_convertible<_Yp*, element_type*>::value,
            shared_ptr<_Tp>&
            >::type
            operator=(shared_ptr<_Yp>&& __r);
            template<class _Yp>
            typename enable_if
            <
            !is_array<_Yp>::value &&
            is_convertible<_Yp*, element_type*>::value,
            shared_ptr&
            >::type
            operator=(auto_ptr<_Yp>&& __r);
#else  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
            template<class _Yp>
            typename enable_if
            <
            !is_array<_Yp>::value &&
            is_convertible<_Yp*, element_type*>::value,
            shared_ptr&
            >::type
            operator=(auto_ptr<_Yp> __r);
#endif
            template <class _Yp, class _Dp>
            typename enable_if
            <
            !is_array<_Yp>::value &&
            is_convertible<typename unique_ptr<_Yp, _Dp>::pointer, element_type*>::value,
            shared_ptr&
            >::type
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
            operator=(unique_ptr<_Yp, _Dp>&& __r);
#else  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
            operator=(unique_ptr<_Yp, _Dp> __r);
#endif

            void swap(shared_ptr& __r) noexcept;
            void reset() noexcept;
            template<class _Yp>
            typename enable_if
            <
            is_convertible<_Yp*, element_type*>::value,
            void
            >::type
            reset(_Yp* __p);
            template<class _Yp, class _Dp>
            typename enable_if
            <
            is_convertible<_Yp*, element_type*>::value,
            void
            >::type
            reset(_Yp* __p, _Dp __d);
            template<class _Yp, class _Dp, class _Alloc>
            typename enable_if
            <
            is_convertible<_Yp*, element_type*>::value,
            void
            >::type
            reset(_Yp* __p, _Dp __d, _Alloc __a);

            __attribute__((always_inline))
            element_type* get() const noexcept
              { return __ptr_;}
            __attribute__((always_inline))
            typename add_lvalue_reference<element_type>::type operator*() const noexcept
              { return *__ptr_;}
            __attribute__((always_inline))
            element_type* operator->() const noexcept
              { return __ptr_;}
            __attribute__((always_inline))
            long use_count() const noexcept
              { return __cntrl_ ? __cntrl_->use_count() : 0;}
            __attribute__((always_inline))
            bool unique() const noexcept
              { return use_count() == 1;}
            __attribute__((always_inline))
            _LIBCPP_EXPLICIT operator bool() const noexcept
              { return get() != 0;}
            template <class _Up>
            __attribute__((always_inline))
            bool owner_before(shared_ptr<_Up> const& __p) const
              { return __cntrl_ < __p.__cntrl_;}
            template <class _Up>
            __attribute__((always_inline))
            bool owner_before(weak_ptr<_Up> const& __p) const
              { return __cntrl_ < __p.__cntrl_;}
            __attribute__((always_inline))
            bool
            __owner_equivalent(const shared_ptr& __p) const
              { return __cntrl_ == __p.__cntrl_;}

#ifndef _LIBCPP_NO_RTTI

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
            template <class _Dp>
            __attribute__((always_inline))
            _Dp* __get_deleter() const noexcept
              { return (_Dp*)(__cntrl_ ? __cntrl_->__get_deleter(typeid(_Dp)) : 0);}
#endif

#endif  // _LIBCPP_NO_RTTI
#ifndef _LIBCPP_HAS_NO_VARIADICS

            template<class ..._Args>
            static
            shared_ptr<_Tp>
            make_shared(_Args&& ...__args);

            template<class _Alloc, class ..._Args>
            static
            shared_ptr<_Tp>
            allocate_shared(const _Alloc& __a, _Args&& ...__args);

#else  // _LIBCPP_HAS_NO_VARIADICS
            static shared_ptr<_Tp> make_shared();

            template<class _A0>
            static shared_ptr<_Tp> make_shared(_A0&);

            template<class _A0, class _A1>
            static shared_ptr<_Tp> make_shared(_A0&, _A1&);

            template<class _A0, class _A1, class _A2>
            static shared_ptr<_Tp> make_shared(_A0&, _A1&, _A2&);

            template<class _Alloc>
            static shared_ptr<_Tp>
            allocate_shared(const _Alloc& __a);

            template<class _Alloc, class _A0>
            static shared_ptr<_Tp>
            allocate_shared(const _Alloc& __a, _A0& __a0);

            template<class _Alloc, class _A0, class _A1>
            static shared_ptr<_Tp>
            allocate_shared(const _Alloc& __a, _A0& __a0, _A1& __a1);

            template<class _Alloc, class _A0, class _A1, class _A2>
            static shared_ptr<_Tp>
            allocate_shared(const _Alloc& __a, _A0& __a0, _A1& __a1, _A2& __a2);

#endif  // _LIBCPP_HAS_NO_VARIADICS
          private:

            template <class _Yp>
            __attribute__((always_inline))
            void
            __enable_weak_this(const enable_shared_from_this<_Yp>* __e) noexcept
              {
                if (__e)
                __e->__weak_this_ = *this;
              }

            __attribute__((always_inline))
            void __enable_weak_this(const void*) noexcept
              {}

            template <class _Up> friend class shared_ptr;
            template <class _Up> friend class weak_ptr;
          };

        template<class _Tp>
        inline __attribute__((always_inline))
        constexpr
        shared_ptr<_Tp>::shared_ptr() noexcept
        : __ptr_(0),
        __cntrl_(0)
          {
          }

        template<class _Tp>
        inline __attribute__((always_inline))
        constexpr
        shared_ptr<_Tp>::shared_ptr(nullptr_t) noexcept
        : __ptr_(0),
        __cntrl_(0)
          {
          }

        template<class _Tp>
        template<class _Yp, class>
        shared_ptr<_Tp>::shared_ptr(_Yp* __p)
        : __ptr_(__p)
          {
            unique_ptr<_Yp> __hold(__p);
            typedef __shared_ptr_pointer<_Yp*, default_delete<_Yp>, allocator<_Yp> > _CntrlBlk;
            __cntrl_ = new _CntrlBlk(__p, default_delete<_Yp>(), allocator<_Yp>());
            __hold.release();
            __enable_weak_this(__p);
          }

        template<class _Tp>
        template<class _Yp, class _Dp, class>
        shared_ptr<_Tp>::shared_ptr(_Yp* __p, _Dp __d)
        : __ptr_(__p)
          {
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
            try
              {
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
                typedef __shared_ptr_pointer<_Yp*, _Dp, allocator<_Yp> > _CntrlBlk;
                __cntrl_ = new _CntrlBlk(__p, __d, allocator<_Yp>());
                __enable_weak_this(__p);
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
              }
            catch (...)
              {
                __d(__p);
                throw;
              }
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
          }

        template<class _Tp>
        template<class _Dp>
        shared_ptr<_Tp>::shared_ptr(nullptr_t __p, _Dp __d)
        : __ptr_(0)
          {
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
            try
              {
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
                typedef __shared_ptr_pointer<nullptr_t, _Dp, allocator<_Tp> > _CntrlBlk;
                __cntrl_ = new _CntrlBlk(__p, __d, allocator<_Tp>());
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
              }
            catch (...)
              {
                __d(__p);
                throw;
              }
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
          }

        template<class _Tp>
        template<class _Yp, class _Dp, class _Alloc, class>
        shared_ptr<_Tp>::shared_ptr(_Yp* __p, _Dp __d, _Alloc __a)
        : __ptr_(__p)
          {
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
            try
              {
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
                typedef __shared_ptr_pointer<_Yp*, _Dp, _Alloc> _CntrlBlk;
                typedef typename _Alloc::template rebind<_CntrlBlk>::other _A2;
                typedef __allocator_destructor<_A2> _D2;
                _A2 __a2(__a);
                unique_ptr<_CntrlBlk, _D2> __hold2(__a2.allocate(1), _D2(__a2, 1));
                ::new(__hold2.get()) _CntrlBlk(__p, __d, __a);
                __cntrl_ = __hold2.release();
                __enable_weak_this(__p);
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
              }
            catch (...)
              {
                __d(__p);
                throw;
              }
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
          }

        template<class _Tp>
        template<class _Dp, class _Alloc>
        shared_ptr<_Tp>::shared_ptr(nullptr_t __p, _Dp __d, _Alloc __a)
        : __ptr_(0)
          {
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
            try
              {
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
                typedef __shared_ptr_pointer<nullptr_t, _Dp, _Alloc> _CntrlBlk;
                typedef typename _Alloc::template rebind<_CntrlBlk>::other _A2;
                typedef __allocator_destructor<_A2> _D2;
                _A2 __a2(__a);
                unique_ptr<_CntrlBlk, _D2> __hold2(__a2.allocate(1), _D2(__a2, 1));
                ::new(__hold2.get()) _CntrlBlk(__p, __d, __a);
                __cntrl_ = __hold2.release();
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
              }
            catch (...)
              {
                __d(__p);
                throw;
              }
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
          }

        template<class _Tp>
        template<class _Yp>
        inline __attribute__((always_inline))
        shared_ptr<_Tp>::shared_ptr(const shared_ptr<_Yp>& __r, element_type *__p) noexcept
        : __ptr_(__p),
        __cntrl_(__r.__cntrl_)
          {
            if (__cntrl_)
            __cntrl_->__add_shared();
          }

        template<class _Tp>
        inline __attribute__((always_inline))
        shared_ptr<_Tp>::shared_ptr(const shared_ptr& __r) noexcept
        : __ptr_(__r.__ptr_),
        __cntrl_(__r.__cntrl_)
          {
            if (__cntrl_)
            __cntrl_->__add_shared();
          }

        template<class _Tp>
        template<class _Yp>
        inline __attribute__((always_inline))
        shared_ptr<_Tp>::shared_ptr(const shared_ptr<_Yp>& __r,
            typename enable_if<is_convertible<_Yp*, _Tp*>::value, __nat>::type)
        noexcept
        : __ptr_(__r.__ptr_),
        __cntrl_(__r.__cntrl_)
          {
            if (__cntrl_)
            __cntrl_->__add_shared();
          }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

        template<class _Tp>
        inline __attribute__((always_inline))
        shared_ptr<_Tp>::shared_ptr(shared_ptr&& __r) noexcept
        : __ptr_(__r.__ptr_),
        __cntrl_(__r.__cntrl_)
          {
            __r.__ptr_ = 0;
            __r.__cntrl_ = 0;
          }

        template<class _Tp>
        template<class _Yp>
        inline __attribute__((always_inline))
        shared_ptr<_Tp>::shared_ptr(shared_ptr<_Yp>&& __r,
            typename enable_if<is_convertible<_Yp*, _Tp*>::value, __nat>::type)
        noexcept
        : __ptr_(__r.__ptr_),
        __cntrl_(__r.__cntrl_)
          {
            __r.__ptr_ = 0;
            __r.__cntrl_ = 0;
          }

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
        template<class _Tp>
        template<class _Yp, class>
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
        shared_ptr<_Tp>::shared_ptr(auto_ptr<_Yp>&& __r)
#else
        shared_ptr<_Tp>::shared_ptr(auto_ptr<_Yp> __r)
#endif
        : __ptr_(__r.get())
          {
            typedef __shared_ptr_pointer<_Yp*, default_delete<_Yp>, allocator<_Yp> > _CntrlBlk;
            __cntrl_ = new _CntrlBlk(__r.get(), default_delete<_Yp>(), allocator<_Yp>());
            __enable_weak_this(__r.get());
            __r.release();
          }

        template<class _Tp>
        template <class _Yp, class _Dp, class>
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
        shared_ptr<_Tp>::shared_ptr(unique_ptr<_Yp, _Dp>&& __r,
#else
            shared_ptr<_Tp>::shared_ptr(unique_ptr<_Yp, _Dp> __r,
#endif
                typename enable_if<!is_lvalue_reference<_Dp>::value, __nat>::type)
            : __ptr_(__r.get())
              {
                typedef __shared_ptr_pointer<_Yp*, _Dp, allocator<_Yp> > _CntrlBlk;
                __cntrl_ = new _CntrlBlk(__r.get(), __r.get_deleter(), allocator<_Yp>());
                __enable_weak_this(__r.get());
                __r.release();
              }

            template<class _Tp>
            template <class _Yp, class _Dp, class>
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
            shared_ptr<_Tp>::shared_ptr(unique_ptr<_Yp, _Dp>&& __r,
#else
                shared_ptr<_Tp>::shared_ptr(unique_ptr<_Yp, _Dp> __r,
#endif
                    typename enable_if<is_lvalue_reference<_Dp>::value, __nat>::type)
                : __ptr_(__r.get())
                  {
                    typedef __shared_ptr_pointer<_Yp*,
                    reference_wrapper<typename remove_reference<_Dp>::type>,
                    allocator<_Yp> > _CntrlBlk;
                    __cntrl_ = new _CntrlBlk(__r.get(), ref(__r.get_deleter()), allocator<_Yp>());
                    __enable_weak_this(__r.get());
                    __r.release();
                  }

#ifndef _LIBCPP_HAS_NO_VARIADICS

                template<class _Tp>
                template<class ..._Args>
                shared_ptr<_Tp>
                shared_ptr<_Tp>::make_shared(_Args&& ...__args)
                  {
                    typedef __shared_ptr_emplace<_Tp, allocator<_Tp> > _CntrlBlk;
                    typedef allocator<_CntrlBlk> _A2;
                    typedef __allocator_destructor<_A2> _D2;
                    _A2 __a2;
                    unique_ptr<_CntrlBlk, _D2> __hold2(__a2.allocate(1), _D2(__a2, 1));
                    ::new(__hold2.get()) _CntrlBlk(__a2, os::std::forward<_Args>(__args)...);
                    shared_ptr<_Tp> __r;
                    __r.__ptr_ = __hold2.get()->get();
                    __r.__cntrl_ = __hold2.release();
                    __r.__enable_weak_this(__r.__ptr_);
                    return __r;
                  }

                template<class _Tp>
                template<class _Alloc, class ..._Args>
                shared_ptr<_Tp>
                shared_ptr<_Tp>::allocate_shared(const _Alloc& __a, _Args&& ...__args)
                  {
                    typedef __shared_ptr_emplace<_Tp, _Alloc> _CntrlBlk;
                    typedef typename _Alloc::template rebind<_CntrlBlk>::other _A2;
                    typedef __allocator_destructor<_A2> _D2;
                    _A2 __a2(__a);
                    unique_ptr<_CntrlBlk, _D2> __hold2(__a2.allocate(1), _D2(__a2, 1));
                    ::new(__hold2.get()) _CntrlBlk(__a, os::std::forward<_Args>(__args)...);
                    shared_ptr<_Tp> __r;
                    __r.__ptr_ = __hold2.get()->get();
                    __r.__cntrl_ = __hold2.release();
                    __r.__enable_weak_this(__r.__ptr_);
                    return __r;
                  }

#else  // _LIBCPP_HAS_NO_VARIADICS
                template<class _Tp>
                shared_ptr<_Tp>
                shared_ptr<_Tp>::make_shared()
                  {
                    typedef __shared_ptr_emplace<_Tp, allocator<_Tp> > _CntrlBlk;
                    typedef allocator<_CntrlBlk> _Alloc2;
                    typedef __allocator_destructor<_Alloc2> _D2;
                    _Alloc2 __alloc2;
                    unique_ptr<_CntrlBlk, _D2> __hold2(__alloc2.allocate(1), _D2(__alloc2, 1));
                    ::new(__hold2.get()) _CntrlBlk(__alloc2);
                    shared_ptr<_Tp> __r;
                    __r.__ptr_ = __hold2.get()->get();
                    __r.__cntrl_ = __hold2.release();
                    __r.__enable_weak_this(__r.__ptr_);
                    return __r;
                  }

                template<class _Tp>
                template<class _A0>
                shared_ptr<_Tp>
                shared_ptr<_Tp>::make_shared(_A0& __a0)
                  {
                    typedef __shared_ptr_emplace<_Tp, allocator<_Tp> > _CntrlBlk;
                    typedef allocator<_CntrlBlk> _Alloc2;
                    typedef __allocator_destructor<_Alloc2> _D2;
                    _Alloc2 __alloc2;
                    unique_ptr<_CntrlBlk, _D2> __hold2(__alloc2.allocate(1), _D2(__alloc2, 1));
                    ::new(__hold2.get()) _CntrlBlk(__alloc2, __a0);
                    shared_ptr<_Tp> __r;
                    __r.__ptr_ = __hold2.get()->get();
                    __r.__cntrl_ = __hold2.release();
                    __r.__enable_weak_this(__r.__ptr_);
                    return __r;
                  }

                template<class _Tp>
                template<class _A0, class _A1>
                shared_ptr<_Tp>
                shared_ptr<_Tp>::make_shared(_A0& __a0, _A1& __a1)
                  {
                    typedef __shared_ptr_emplace<_Tp, allocator<_Tp> > _CntrlBlk;
                    typedef allocator<_CntrlBlk> _Alloc2;
                    typedef __allocator_destructor<_Alloc2> _D2;
                    _Alloc2 __alloc2;
                    unique_ptr<_CntrlBlk, _D2> __hold2(__alloc2.allocate(1), _D2(__alloc2, 1));
                    ::new(__hold2.get()) _CntrlBlk(__alloc2, __a0, __a1);
                    shared_ptr<_Tp> __r;
                    __r.__ptr_ = __hold2.get()->get();
                    __r.__cntrl_ = __hold2.release();
                    __r.__enable_weak_this(__r.__ptr_);
                    return __r;
                  }

                template<class _Tp>
                template<class _A0, class _A1, class _A2>
                shared_ptr<_Tp>
                shared_ptr<_Tp>::make_shared(_A0& __a0, _A1& __a1, _A2& __a2)
                  {
                    typedef __shared_ptr_emplace<_Tp, allocator<_Tp> > _CntrlBlk;
                    typedef allocator<_CntrlBlk> _Alloc2;
                    typedef __allocator_destructor<_Alloc2> _D2;
                    _Alloc2 __alloc2;
                    unique_ptr<_CntrlBlk, _D2> __hold2(__alloc2.allocate(1), _D2(__alloc2, 1));
                    ::new(__hold2.get()) _CntrlBlk(__alloc2, __a0, __a1, __a2);
                    shared_ptr<_Tp> __r;
                    __r.__ptr_ = __hold2.get()->get();
                    __r.__cntrl_ = __hold2.release();
                    __r.__enable_weak_this(__r.__ptr_);
                    return __r;
                  }

                template<class _Tp>
                template<class _Alloc>
                shared_ptr<_Tp>
                shared_ptr<_Tp>::allocate_shared(const _Alloc& __a)
                  {
                    typedef __shared_ptr_emplace<_Tp, _Alloc> _CntrlBlk;
                    typedef typename _Alloc::template rebind<_CntrlBlk>::other _Alloc2;
                    typedef __allocator_destructor<_Alloc2> _D2;
                    _Alloc2 __alloc2(__a);
                    unique_ptr<_CntrlBlk, _D2> __hold2(__alloc2.allocate(1), _D2(__alloc2, 1));
                    ::new(__hold2.get()) _CntrlBlk(__a);
                    shared_ptr<_Tp> __r;
                    __r.__ptr_ = __hold2.get()->get();
                    __r.__cntrl_ = __hold2.release();
                    __r.__enable_weak_this(__r.__ptr_);
                    return __r;
                  }

                template<class _Tp>
                template<class _Alloc, class _A0>
                shared_ptr<_Tp>
                shared_ptr<_Tp>::allocate_shared(const _Alloc& __a, _A0& __a0)
                  {
                    typedef __shared_ptr_emplace<_Tp, _Alloc> _CntrlBlk;
                    typedef typename _Alloc::template rebind<_CntrlBlk>::other _Alloc2;
                    typedef __allocator_destructor<_Alloc2> _D2;
                    _Alloc2 __alloc2(__a);
                    unique_ptr<_CntrlBlk, _D2> __hold2(__alloc2.allocate(1), _D2(__alloc2, 1));
                    ::new(__hold2.get()) _CntrlBlk(__a, __a0);
                    shared_ptr<_Tp> __r;
                    __r.__ptr_ = __hold2.get()->get();
                    __r.__cntrl_ = __hold2.release();
                    __r.__enable_weak_this(__r.__ptr_);
                    return __r;
                  }

                template<class _Tp>
                template<class _Alloc, class _A0, class _A1>
                shared_ptr<_Tp>
                shared_ptr<_Tp>::allocate_shared(const _Alloc& __a, _A0& __a0, _A1& __a1)
                  {
                    typedef __shared_ptr_emplace<_Tp, _Alloc> _CntrlBlk;
                    typedef typename _Alloc::template rebind<_CntrlBlk>::other _Alloc2;
                    typedef __allocator_destructor<_Alloc2> _D2;
                    _Alloc2 __alloc2(__a);
                    unique_ptr<_CntrlBlk, _D2> __hold2(__alloc2.allocate(1), _D2(__alloc2, 1));
                    ::new(__hold2.get()) _CntrlBlk(__a, __a0, __a1);
                    shared_ptr<_Tp> __r;
                    __r.__ptr_ = __hold2.get()->get();
                    __r.__cntrl_ = __hold2.release();
                    __r.__enable_weak_this(__r.__ptr_);
                    return __r;
                  }

                template<class _Tp>
                template<class _Alloc, class _A0, class _A1, class _A2>
                shared_ptr<_Tp>
                shared_ptr<_Tp>::allocate_shared(const _Alloc& __a, _A0& __a0, _A1& __a1, _A2& __a2)
                  {
                    typedef __shared_ptr_emplace<_Tp, _Alloc> _CntrlBlk;
                    typedef typename _Alloc::template rebind<_CntrlBlk>::other _Alloc2;
                    typedef __allocator_destructor<_Alloc2> _D2;
                    _Alloc2 __alloc2(__a);
                    unique_ptr<_CntrlBlk, _D2> __hold2(__alloc2.allocate(1), _D2(__alloc2, 1));
                    ::new(__hold2.get()) _CntrlBlk(__a, __a0, __a1, __a2);
                    shared_ptr<_Tp> __r;
                    __r.__ptr_ = __hold2.get()->get();
                    __r.__cntrl_ = __hold2.release();
                    __r.__enable_weak_this(__r.__ptr_);
                    return __r;
                  }

#endif  // _LIBCPP_HAS_NO_VARIADICS
                template<class _Tp>
                shared_ptr<_Tp>::~shared_ptr()
                  {
                    if (__cntrl_)
                    __cntrl_->__release_shared();
                  }

                template<class _Tp>
                inline __attribute__((always_inline))
                shared_ptr<_Tp>&
                shared_ptr<_Tp>::operator=(const shared_ptr& __r) noexcept
                  {
                    shared_ptr(__r).swap(*this);
                    return *this;
                  }

                template<class _Tp>
                template<class _Yp>
                inline __attribute__((always_inline))
                typename enable_if
                <
                is_convertible<_Yp*, _Tp*>::value,
                shared_ptr<_Tp>&
                >::type
                shared_ptr<_Tp>::operator=(const shared_ptr<_Yp>& __r) noexcept
                  {
                    shared_ptr(__r).swap(*this);
                    return *this;
                  }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

                template<class _Tp>
                inline __attribute__((always_inline))
                shared_ptr<_Tp>&
                shared_ptr<_Tp>::operator=(shared_ptr&& __r) noexcept
                  {
                    shared_ptr(os::std::move(__r)).swap(*this);
                    return *this;
                  }

                template<class _Tp>
                template<class _Yp>
                inline __attribute__((always_inline))
                typename enable_if
                <
                is_convertible<_Yp*, _Tp*>::value,
                shared_ptr<_Tp>&
                >::type
                shared_ptr<_Tp>::operator=(shared_ptr<_Yp>&& __r)
                  {
                    shared_ptr(os::std::move(__r)).swap(*this);
                    return *this;
                  }

                template<class _Tp>
                template<class _Yp>
                inline __attribute__((always_inline))
                typename enable_if
                <
                !is_array<_Yp>::value &&
                is_convertible<_Yp*, _Tp*>::value,
                shared_ptr<_Tp>&
                >::type
                shared_ptr<_Tp>::operator=(auto_ptr<_Yp>&& __r)
                  {
                    shared_ptr(os::std::move(__r)).swap(*this);
                    return *this;
                  }

                template<class _Tp>
                template <class _Yp, class _Dp>
                inline __attribute__((always_inline))
                typename enable_if
                <
                !is_array<_Yp>::value &&
                is_convertible<typename unique_ptr<_Yp, _Dp>::pointer, _Tp*>::value,
                shared_ptr<_Tp>&
                >::type
                shared_ptr<_Tp>::operator=(unique_ptr<_Yp, _Dp>&& __r)
                  {
                    shared_ptr(os::std::move(__r)).swap(*this);
                    return *this;
                  }

#else  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
                template<class _Tp>
                template<class _Yp>
                inline __attribute__((always_inline))
                typename enable_if
                <
                !is_array<_Yp>::value &&
                is_convertible<_Yp*, _Tp*>::value,
                shared_ptr<_Tp>&
                >::type
                shared_ptr<_Tp>::operator=(auto_ptr<_Yp> __r)
                  {
                    shared_ptr(__r).swap(*this);
                    return *this;
                  }

                template<class _Tp>
                template <class _Yp, class _Dp>
                inline __attribute__((always_inline))
                typename enable_if
                <
                !is_array<_Yp>::value &&
                is_convertible<typename unique_ptr<_Yp, _Dp>::pointer, _Tp*>::value,
                shared_ptr<_Tp>&
                >::type
                shared_ptr<_Tp>::operator=(unique_ptr<_Yp, _Dp> __r)
                  {
                    shared_ptr(os::std::move(__r)).swap(*this);
                    return *this;
                  }

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
                template<class _Tp>
                inline __attribute__((always_inline))
                void
                shared_ptr<_Tp>::swap(shared_ptr& __r) noexcept
                  {
                    os::std::swap(__ptr_, __r.__ptr_);
                    os::std::swap(__cntrl_, __r.__cntrl_);
                  }

                template<class _Tp>
                inline __attribute__((always_inline))
                void
                shared_ptr<_Tp>::reset() noexcept
                  {
                    shared_ptr().swap(*this);
                  }

                template<class _Tp>
                template<class _Yp>
                inline __attribute__((always_inline))
                typename enable_if
                <
                is_convertible<_Yp*, _Tp*>::value,
                void
                >::type
                shared_ptr<_Tp>::reset(_Yp* __p)
                  {
                    shared_ptr(__p).swap(*this);
                  }

                template<class _Tp>
                template<class _Yp, class _Dp>
                inline __attribute__((always_inline))
                typename enable_if
                <
                is_convertible<_Yp*, _Tp*>::value,
                void
                >::type
                shared_ptr<_Tp>::reset(_Yp* __p, _Dp __d)
                  {
                    shared_ptr(__p, __d).swap(*this);
                  }

                template<class _Tp>
                template<class _Yp, class _Dp, class _Alloc>
                inline __attribute__((always_inline))
                typename enable_if
                <
                is_convertible<_Yp*, _Tp*>::value,
                void
                >::type
                shared_ptr<_Tp>::reset(_Yp* __p, _Dp __d, _Alloc __a)
                  {
                    shared_ptr(__p, __d, __a).swap(*this);
                  }

#ifndef _LIBCPP_HAS_NO_VARIADICS

                template<class _Tp, class ..._Args>
                inline __attribute__((always_inline))
                typename enable_if
                <
                !is_array<_Tp>::value,
                shared_ptr<_Tp>
                >::type
                make_shared(_Args&& ...__args)
                  {
                    return shared_ptr<_Tp>::make_shared(os::std::forward<_Args>(__args)...);
                  }

                template<class _Tp, class _Alloc, class ..._Args>
                inline __attribute__((always_inline))
                typename enable_if
                <
                !is_array<_Tp>::value,
                shared_ptr<_Tp>
                >::type
                allocate_shared(const _Alloc& __a, _Args&& ...__args)
                  {
                    return shared_ptr<_Tp>::allocate_shared(__a, os::std::forward<_Args>(__args)...);
                  }

#else  // _LIBCPP_HAS_NO_VARIADICS
                template<class _Tp>
                inline __attribute__((always_inline))
                shared_ptr<_Tp>
                make_shared()
                  {
                    return shared_ptr<_Tp>::make_shared();
                  }

                template<class _Tp, class _A0>
                inline __attribute__((always_inline))
                shared_ptr<_Tp>
                make_shared(_A0& __a0)
                  {
                    return shared_ptr<_Tp>::make_shared(__a0);
                  }

                template<class _Tp, class _A0, class _A1>
                inline __attribute__((always_inline))
                shared_ptr<_Tp>
                make_shared(_A0& __a0, _A1& __a1)
                  {
                    return shared_ptr<_Tp>::make_shared(__a0, __a1);
                  }

                template<class _Tp, class _A0, class _A1, class _A2>
                inline __attribute__((always_inline))
                shared_ptr<_Tp>
                make_shared(_A0& __a0, _A1& __a1, _A2& __a2)
                  {
                    return shared_ptr<_Tp>::make_shared(__a0, __a1, __a2);
                  }

                template<class _Tp, class _Alloc>
                inline __attribute__((always_inline))
                shared_ptr<_Tp>
                allocate_shared(const _Alloc& __a)
                  {
                    return shared_ptr<_Tp>::allocate_shared(__a);
                  }

                template<class _Tp, class _Alloc, class _A0>
                inline __attribute__((always_inline))
                shared_ptr<_Tp>
                allocate_shared(const _Alloc& __a, _A0& __a0)
                  {
                    return shared_ptr<_Tp>::allocate_shared(__a, __a0);
                  }

                template<class _Tp, class _Alloc, class _A0, class _A1>
                inline __attribute__((always_inline))
                shared_ptr<_Tp>
                allocate_shared(const _Alloc& __a, _A0& __a0, _A1& __a1)
                  {
                    return shared_ptr<_Tp>::allocate_shared(__a, __a0, __a1);
                  }

                template<class _Tp, class _Alloc, class _A0, class _A1, class _A2>
                inline __attribute__((always_inline))
                shared_ptr<_Tp>
                allocate_shared(const _Alloc& __a, _A0& __a0, _A1& __a1, _A2& __a2)
                  {
                    return shared_ptr<_Tp>::allocate_shared(__a, __a0, __a1, __a2);
                  }

#endif  // _LIBCPP_HAS_NO_VARIADICS
                template<class _Tp, class _Up>
                inline __attribute__((always_inline))
                bool
                operator==(const shared_ptr<_Tp>& __x, const shared_ptr<_Up>& __y) noexcept
                  {
                    return __x.get() == __y.get();
                  }

                template<class _Tp, class _Up>
                inline __attribute__((always_inline))
                bool
                operator!=(const shared_ptr<_Tp>& __x, const shared_ptr<_Up>& __y) noexcept
                  {
                    return !(__x == __y);
                  }

                template<class _Tp, class _Up>
                inline __attribute__((always_inline))
                bool
                operator<(const shared_ptr<_Tp>& __x, const shared_ptr<_Up>& __y) noexcept
                  {
                    typedef typename common_type<_Tp*, _Up*>::type _V;
                    return less<_V>()(__x.get(), __y.get());
                  }

                template<class _Tp, class _Up>
                inline __attribute__((always_inline))
                bool
                operator>(const shared_ptr<_Tp>& __x, const shared_ptr<_Up>& __y) noexcept
                  {
                    return __y < __x;
                  }

                template<class _Tp, class _Up>
                inline __attribute__((always_inline))
                bool
                operator<=(const shared_ptr<_Tp>& __x, const shared_ptr<_Up>& __y) noexcept
                  {
                    return !(__y < __x);
                  }

                template<class _Tp, class _Up>
                inline __attribute__((always_inline))
                bool
                operator>=(const shared_ptr<_Tp>& __x, const shared_ptr<_Up>& __y) noexcept
                  {
                    return !(__x < __y);
                  }

                template<class _Tp>
                inline __attribute__((always_inline))
                bool
                operator==(const shared_ptr<_Tp>& __x, nullptr_t) noexcept
                  {
                    return !__x;
                  }

                template<class _Tp>
                inline __attribute__((always_inline))
                bool
                operator==(nullptr_t, const shared_ptr<_Tp>& __x) noexcept
                  {
                    return !__x;
                  }

                template<class _Tp>
                inline __attribute__((always_inline))
                bool
                operator!=(const shared_ptr<_Tp>& __x, nullptr_t) noexcept
                  {
                    return static_cast<bool>(__x);
                  }

                template<class _Tp>
                inline __attribute__((always_inline))
                bool
                operator!=(nullptr_t, const shared_ptr<_Tp>& __x) noexcept
                  {
                    return static_cast<bool>(__x);
                  }

                template<class _Tp>
                inline __attribute__((always_inline))
                bool
                operator<(const shared_ptr<_Tp>& __x, nullptr_t) noexcept
                  {
                    return less<_Tp*>()(__x.get(), nullptr);
                  }

                template<class _Tp>
                inline __attribute__((always_inline))
                bool
                operator<(nullptr_t, const shared_ptr<_Tp>& __x) noexcept
                  {
                    return less<_Tp*>()(nullptr, __x.get());
                  }

                template<class _Tp>
                inline __attribute__((always_inline))
                bool
                operator>(const shared_ptr<_Tp>& __x, nullptr_t) noexcept
                  {
                    return nullptr < __x;
                  }

                template<class _Tp>
                inline __attribute__((always_inline))
                bool
                operator>(nullptr_t, const shared_ptr<_Tp>& __x) noexcept
                  {
                    return __x < nullptr;
                  }

                template<class _Tp>
                inline __attribute__((always_inline))
                bool
                operator<=(const shared_ptr<_Tp>& __x, nullptr_t) noexcept
                  {
                    return !(nullptr < __x);
                  }

                template<class _Tp>
                inline __attribute__((always_inline))
                bool
                operator<=(nullptr_t, const shared_ptr<_Tp>& __x) noexcept
                  {
                    return !(__x < nullptr);
                  }

                template<class _Tp>
                inline __attribute__((always_inline))
                bool
                operator>=(const shared_ptr<_Tp>& __x, nullptr_t) noexcept
                  {
                    return !(__x < nullptr);
                  }

                template<class _Tp>
                inline __attribute__((always_inline))
                bool
                operator>=(nullptr_t, const shared_ptr<_Tp>& __x) noexcept
                  {
                    return !(nullptr < __x);
                  }

                template<class _Tp>
                inline __attribute__((always_inline))
                void
                swap(shared_ptr<_Tp>& __x, shared_ptr<_Tp>& __y) noexcept
                  {
                    __x.swap(__y);
                  }

                template<class _Tp, class _Up>
                inline __attribute__((always_inline))
                typename enable_if
                <
                !is_array<_Tp>::value && !is_array<_Up>::value,
                shared_ptr<_Tp>
                >::type
                static_pointer_cast(const shared_ptr<_Up>& __r) noexcept
                  {
                    return shared_ptr<_Tp>(__r, static_cast<_Tp*>(__r.get()));
                  }

                template<class _Tp, class _Up>
                inline __attribute__((always_inline))
                typename enable_if
                <
                !is_array<_Tp>::value && !is_array<_Up>::value,
                shared_ptr<_Tp>
                >::type
                dynamic_pointer_cast(const shared_ptr<_Up>& __r) noexcept
                  {
                    _Tp* __p = dynamic_cast<_Tp*>(__r.get());
                    return __p ? shared_ptr<_Tp>(__r, __p) : shared_ptr<_Tp>();
                  }

                template<class _Tp, class _Up>
                typename enable_if
                <
                is_array<_Tp>::value == is_array<_Up>::value,
                shared_ptr<_Tp>
                >::type
                const_pointer_cast(const shared_ptr<_Up>& __r) noexcept
                  {
                    typedef typename remove_extent<_Tp>::type _RTp;
                    return shared_ptr<_Tp>(__r, const_cast<_RTp*>(__r.get()));
                  }

#ifndef _LIBCPP_NO_RTTI

                template<class _Dp, class _Tp>
                inline __attribute__((always_inline))
                _Dp*
                get_deleter(const shared_ptr<_Tp>& __p) noexcept
                  {
                    return __p.template __get_deleter<_Dp>();
                  }

#endif  // _LIBCPP_NO_RTTI
                template<class _Tp>
                class weak_ptr
                  {
                  public:
                    typedef _Tp element_type;
                  private:
                    element_type* __ptr_;
                    __shared_weak_count* __cntrl_;

                  public:
                    constexpr weak_ptr() noexcept;
                    template<class _Yp> weak_ptr(shared_ptr<_Yp> const& __r,
                        typename enable_if<is_convertible<_Yp*, _Tp*>::value, __nat*>::type = 0)
                    noexcept;
                    weak_ptr(weak_ptr const& __r) noexcept;
                    template<class _Yp> weak_ptr(weak_ptr<_Yp> const& __r,
                        typename enable_if<is_convertible<_Yp*, _Tp*>::value, __nat*>::type = 0)
                    noexcept;

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
                    weak_ptr(weak_ptr&& __r) noexcept;
                    template<class _Yp> weak_ptr(weak_ptr<_Yp>&& __r,
                        typename enable_if<is_convertible<_Yp*, _Tp*>::value, __nat*>::type = 0)
                    noexcept;
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
                    ~weak_ptr();

                    weak_ptr& operator=(weak_ptr const& __r) noexcept;
                    template<class _Yp>
                    typename enable_if
                    <
                    is_convertible<_Yp*, element_type*>::value,
                    weak_ptr&
                    >::type
                    operator=(weak_ptr<_Yp> const& __r) noexcept;

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

                    weak_ptr& operator=(weak_ptr&& __r) noexcept;
                    template<class _Yp>
                    typename enable_if
                    <
                    is_convertible<_Yp*, element_type*>::value,
                    weak_ptr&
                    >::type
                    operator=(weak_ptr<_Yp>&& __r) noexcept;

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
                    template<class _Yp>
                    typename enable_if
                    <
                    is_convertible<_Yp*, element_type*>::value,
                    weak_ptr&
                    >::type
                    operator=(shared_ptr<_Yp> const& __r) noexcept;

                    void swap(weak_ptr& __r) noexcept;
                    void reset() noexcept;

                    __attribute__((always_inline))
                    long use_count() const noexcept
                      { return __cntrl_ ? __cntrl_->use_count() : 0;}
                    __attribute__((always_inline))
                    bool expired() const noexcept
                      { return __cntrl_ == 0 || __cntrl_->use_count() == 0;}
                    shared_ptr<_Tp> lock() const noexcept;
                    template<class _Up>
                    __attribute__((always_inline))
                    bool owner_before(const shared_ptr<_Up>& __r) const
                      { return __cntrl_ < __r.__cntrl_;}
                    template<class _Up>
                    __attribute__((always_inline))
                    bool owner_before(const weak_ptr<_Up>& __r) const
                      { return __cntrl_ < __r.__cntrl_;}

                    template <class _Up> friend class weak_ptr;
                    template <class _Up> friend class shared_ptr;
                  };

                template<class _Tp>
                inline __attribute__((always_inline))
                constexpr
                weak_ptr<_Tp>::weak_ptr() noexcept
                : __ptr_(0),
                __cntrl_(0)
                  {
                  }

                template<class _Tp>
                inline __attribute__((always_inline))
                weak_ptr<_Tp>::weak_ptr(weak_ptr const& __r) noexcept
                : __ptr_(__r.__ptr_),
                __cntrl_(__r.__cntrl_)
                  {
                    if (__cntrl_)
                    __cntrl_->__add_weak();
                  }

                template<class _Tp>
                template<class _Yp>
                inline __attribute__((always_inline))
                weak_ptr<_Tp>::weak_ptr(shared_ptr<_Yp> const& __r,
                    typename enable_if<is_convertible<_Yp*, _Tp*>::value, __nat*>::type)
                noexcept
                : __ptr_(__r.__ptr_),
                __cntrl_(__r.__cntrl_)
                  {
                    if (__cntrl_)
                    __cntrl_->__add_weak();
                  }

                template<class _Tp>
                template<class _Yp>
                inline __attribute__((always_inline))
                weak_ptr<_Tp>::weak_ptr(weak_ptr<_Yp> const& __r,
                    typename enable_if<is_convertible<_Yp*, _Tp*>::value, __nat*>::type)
                noexcept
                : __ptr_(__r.__ptr_),
                __cntrl_(__r.__cntrl_)
                  {
                    if (__cntrl_)
                    __cntrl_->__add_weak();
                  }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

                template<class _Tp>
                inline __attribute__((always_inline))
                weak_ptr<_Tp>::weak_ptr(weak_ptr&& __r) noexcept
                : __ptr_(__r.__ptr_),
                __cntrl_(__r.__cntrl_)
                  {
                    __r.__ptr_ = 0;
                    __r.__cntrl_ = 0;
                  }

                template<class _Tp>
                template<class _Yp>
                inline __attribute__((always_inline))
                weak_ptr<_Tp>::weak_ptr(weak_ptr<_Yp>&& __r,
                    typename enable_if<is_convertible<_Yp*, _Tp*>::value, __nat*>::type)
                noexcept
                : __ptr_(__r.__ptr_),
                __cntrl_(__r.__cntrl_)
                  {
                    __r.__ptr_ = 0;
                    __r.__cntrl_ = 0;
                  }

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
                template<class _Tp>
                weak_ptr<_Tp>::~weak_ptr()
                  {
                    if (__cntrl_)
                    __cntrl_->__release_weak();
                  }

                template<class _Tp>
                inline __attribute__((always_inline))
                weak_ptr<_Tp>&
                weak_ptr<_Tp>::operator=(weak_ptr const& __r) noexcept
                  {
                    weak_ptr(__r).swap(*this);
                    return *this;
                  }

                template<class _Tp>
                template<class _Yp>
                inline __attribute__((always_inline))
                typename enable_if
                <
                is_convertible<_Yp*, _Tp*>::value,
                weak_ptr<_Tp>&
                >::type
                weak_ptr<_Tp>::operator=(weak_ptr<_Yp> const& __r) noexcept
                  {
                    weak_ptr(__r).swap(*this);
                    return *this;
                  }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

                template<class _Tp>
                inline __attribute__((always_inline))
                weak_ptr<_Tp>&
                weak_ptr<_Tp>::operator=(weak_ptr&& __r) noexcept
                  {
                    weak_ptr(os::std::move(__r)).swap(*this);
                    return *this;
                  }

                template<class _Tp>
                template<class _Yp>
                inline __attribute__((always_inline))
                typename enable_if
                <
                is_convertible<_Yp*, _Tp*>::value,
                weak_ptr<_Tp>&
                >::type
                weak_ptr<_Tp>::operator=(weak_ptr<_Yp>&& __r) noexcept
                  {
                    weak_ptr(os::std::move(__r)).swap(*this);
                    return *this;
                  }

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
                template<class _Tp>
                template<class _Yp>
                inline __attribute__((always_inline))
                typename enable_if
                <
                is_convertible<_Yp*, _Tp*>::value,
                weak_ptr<_Tp>&
                >::type
                weak_ptr<_Tp>::operator=(shared_ptr<_Yp> const& __r) noexcept
                  {
                    weak_ptr(__r).swap(*this);
                    return *this;
                  }

                template<class _Tp>
                inline __attribute__((always_inline))
                void
                weak_ptr<_Tp>::swap(weak_ptr& __r) noexcept
                  {
                    os::std::swap(__ptr_, __r.__ptr_);
                    os::std::swap(__cntrl_, __r.__cntrl_);
                  }

                template<class _Tp>
                inline __attribute__((always_inline))
                void
                swap(weak_ptr<_Tp>& __x, weak_ptr<_Tp>& __y) noexcept
                  {
                    __x.swap(__y);
                  }

                template<class _Tp>
                inline __attribute__((always_inline))
                void
                weak_ptr<_Tp>::reset() noexcept
                  {
                    weak_ptr().swap(*this);
                  }

                template<class _Tp>
                template<class _Yp>
                shared_ptr<_Tp>::shared_ptr(const weak_ptr<_Yp>& __r,
                    typename enable_if<is_convertible<_Yp*, _Tp*>::value, __nat>::type)
                : __ptr_(__r.__ptr_),
                __cntrl_(__r.__cntrl_ ? __r.__cntrl_->lock() : __r.__cntrl_)
                  {
                    if (__cntrl_ == 0)
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
                    throw bad_weak_ptr();
#else
                    assert(!"bad_weak_ptr");
#endif
                  }

                template<class _Tp>
                shared_ptr<_Tp>
                weak_ptr<_Tp>::lock() const noexcept
                  {
                    shared_ptr<_Tp> __r;
                    __r.__cntrl_ = __cntrl_ ? __cntrl_->lock() : __cntrl_;
                    if (__r.__cntrl_)
                    __r.__ptr_ = __ptr_;
                    return __r;
                  }

                template <class _Tp> struct owner_less;

                template <class _Tp>
                struct owner_less<shared_ptr<_Tp> >
                : binary_function<shared_ptr<_Tp>, shared_ptr<_Tp>, bool>
                  {
                    typedef bool result_type;
                    __attribute__((always_inline))
                    bool operator()(shared_ptr<_Tp> const& __x, shared_ptr<_Tp> const& __y) const
                      { return __x.owner_before(__y);}
                    __attribute__((always_inline))
                    bool operator()(shared_ptr<_Tp> const& __x, weak_ptr<_Tp> const& __y) const
                      { return __x.owner_before(__y);}
                    __attribute__((always_inline))
                    bool operator()( weak_ptr<_Tp> const& __x, shared_ptr<_Tp> const& __y) const
                      { return __x.owner_before(__y);}
                  };

                template <class _Tp>
                struct owner_less<weak_ptr<_Tp> >
                : binary_function<weak_ptr<_Tp>, weak_ptr<_Tp>, bool>
                  {
                    typedef bool result_type;
                    __attribute__((always_inline))
                    bool operator()( weak_ptr<_Tp> const& __x, weak_ptr<_Tp> const& __y) const
                      { return __x.owner_before(__y);}
                    __attribute__((always_inline))
                    bool operator()(shared_ptr<_Tp> const& __x, weak_ptr<_Tp> const& __y) const
                      { return __x.owner_before(__y);}
                    __attribute__((always_inline))
                    bool operator()( weak_ptr<_Tp> const& __x, shared_ptr<_Tp> const& __y) const
                      { return __x.owner_before(__y);}
                  };

                template<class _Tp>
                class enable_shared_from_this
                  {
                    mutable weak_ptr<_Tp> __weak_this_;
                  protected:
                    __attribute__((always_inline)) constexpr
                    enable_shared_from_this() noexcept
                      {}
                    __attribute__((always_inline))
                    enable_shared_from_this(enable_shared_from_this const&) noexcept
                      {}
                    __attribute__((always_inline))
                    enable_shared_from_this& operator=(enable_shared_from_this const&) noexcept
                      { return *this;}
                    __attribute__((always_inline))
                    ~enable_shared_from_this()
                      {}
                  public:
                    __attribute__((always_inline))
                    shared_ptr<_Tp> shared_from_this()
                      { return shared_ptr<_Tp>(__weak_this_);}
                    __attribute__((always_inline))
                    shared_ptr<_Tp const> shared_from_this() const
                      { return shared_ptr<const _Tp>(__weak_this_);}

                    template <class _Up> friend class shared_ptr;
                  };

                template <class _Tp>
                struct hash<shared_ptr<_Tp> >
                  {
                    typedef shared_ptr<_Tp> argument_type;
                    typedef size_t result_type;
                    __attribute__((always_inline))
                    result_type operator()(const argument_type& __ptr) const noexcept
                      {
                        return hash<_Tp*>()(__ptr.get());
                      }
                  };

                template<class _CharT, class _Traits, class _Yp>
                inline __attribute__((always_inline))
                basic_ostream<_CharT, _Traits>&
                operator<<(basic_ostream<_CharT, _Traits>& __os, shared_ptr<_Yp> const& __p);

#if __has_feature(cxx_atomic)

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

                class __sp_mut
                  {
                    void* __lx;
                  public:
                    void lock() noexcept;
                    void unlock() noexcept;

                  private:
                    constexpr __sp_mut(void*) noexcept;
                    __sp_mut(const __sp_mut&);
                    __sp_mut& operator=(const __sp_mut&);

                    friend __sp_mut& __get_sp_mut(const void*);
                  };

                __sp_mut& __get_sp_mut(const void*);

                template <class _Tp>
                inline __attribute__((always_inline))
                bool
                atomic_is_lock_free(const shared_ptr<_Tp>*)
                  {
                    return false;
                  }

                template <class _Tp>
                shared_ptr<_Tp>
                atomic_load(const shared_ptr<_Tp>* __p)
                  {
                    __sp_mut& __m = __get_sp_mut(__p);
                    __m.lock();
                    shared_ptr<_Tp> __q = *__p;
                    __m.unlock();
                    return __q;
                  }

                template <class _Tp>
                inline __attribute__((always_inline))
                shared_ptr<_Tp>
                atomic_load_explicit(const shared_ptr<_Tp>* __p, memory_order)
                  {
                    return atomic_load(__p);
                  }

                template <class _Tp>
                void
                atomic_store(shared_ptr<_Tp>* __p, shared_ptr<_Tp> __r)
                  {
                    __sp_mut& __m = __get_sp_mut(__p);
                    __m.lock();
                    __p->swap(__r);
                    __m.unlock();
                  }

                template <class _Tp>
                inline __attribute__((always_inline))
                void
                atomic_store_explicit(shared_ptr<_Tp>* __p, shared_ptr<_Tp> __r, memory_order)
                  {
                    atomic_store(__p, __r);
                  }

                template <class _Tp>
                shared_ptr<_Tp>
                atomic_exchange(shared_ptr<_Tp>* __p, shared_ptr<_Tp> __r)
                  {
                    __sp_mut& __m = __get_sp_mut(__p);
                    __m.lock();
                    __p->swap(__r);
                    __m.unlock();
                    return __r;
                  }

                template <class _Tp>
                inline __attribute__((always_inline))
                shared_ptr<_Tp>
                atomic_exchange_explicit(shared_ptr<_Tp>* __p, shared_ptr<_Tp> __r, memory_order)
                  {
                    return atomic_exchange(__p, __r);
                  }

                template <class _Tp>
                bool
                atomic_compare_exchange_strong(shared_ptr<_Tp>* __p, shared_ptr<_Tp>* __v, shared_ptr<_Tp> __w)
                  {
                    __sp_mut& __m = __get_sp_mut(__p);
                    __m.lock();
                    if (__p->__owner_equivalent(*__v))
                      {
                        *__p = __w;
                        __m.unlock();
                        return true;
                      }
                    *__v = *__p;
                    __m.unlock();
                    return false;
                  }

                template <class _Tp>
                inline __attribute__((always_inline))
                bool
                atomic_compare_exchange_weak(shared_ptr<_Tp>* __p, shared_ptr<_Tp>* __v, shared_ptr<_Tp> __w)
                  {
                    return atomic_compare_exchange_strong(__p, __v, __w);
                  }

                template <class _Tp>
                inline __attribute__((always_inline))
                bool
                atomic_compare_exchange_strong_explicit(shared_ptr<_Tp>* __p, shared_ptr<_Tp>* __v,
                    shared_ptr<_Tp> __w, memory_order, memory_order)
                  {
                    return atomic_compare_exchange_strong(__p, __v, __w);
                  }

                template <class _Tp>
                inline __attribute__((always_inline))
                bool
                atomic_compare_exchange_weak_explicit(shared_ptr<_Tp>* __p, shared_ptr<_Tp>* __v,
                    shared_ptr<_Tp> __w, memory_order, memory_order)
                  {
                    return atomic_compare_exchange_weak(__p, __v, __w);
                  }

#endif // defined(OS_SKIP_NOT_YET_IMPLEMENTED)
#endif  // __has_feature(cxx_atomic)
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
//enum class
                struct pointer_safety
                  {
                    enum __lxe
                      {
                        relaxed,
                        preferred,
                        strict
                      };

                    __lxe __v_;

                    __attribute__((always_inline))
                    pointer_safety(__lxe __v) : __v_(__v)
                      {}
                    __attribute__((always_inline))
                    operator int() const
                      { return __v_;}
                  };

                void declare_reachable(void* __p);
                void declare_no_pointers(char* __p, size_t __n);
                void undeclare_no_pointers(char* __p, size_t __n);
                pointer_safety get_pointer_safety() noexcept;
                void* __undeclare_reachable(void* __p);

                template <class _Tp>
                inline __attribute__((always_inline))
                _Tp*
                undeclare_reachable(_Tp* __p)
                  {
                    return static_cast<_Tp*>(__undeclare_reachable(__p));
                  }

#endif // defined(OS_SKIP_NOT_YET_IMPLEMENTED)
// 20.6.5 Align
/// \brief Align
///
/// \param [in] alignment       Requested alignment.
/// \param [in] size            Requested size.
/// \param [in] ptr             Pointer to buffer.
/// \param [in] space           Buffer storage size.
/// \retval nullptr             The requested aligned buff er would not fit into the available space.
/// \retval pointer             The adjusted value of ptr.
                void*
                align(size_t alignment, size_t size, void*& ptr, size_t& space);

              } // namespace std
          } // namespace os

#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_MEMORY_H
