//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//
// [Partly inspired from the LLVM libcxx sources].
// Copyright (c) 2009-2013 by the contributors listed in
// 'LLVM libcxx Credits.txt'. See 'LLVM libcxx License.txt' for details.
//

/// \file
/// \brief Library configuration definitions.

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_CONFIG_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_CONFIG_H_

//#include "portable/core/include/ConfigDefines.h"

#define _LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER

#ifdef __GNUC__
#define _GNUC_VER (__GNUC__ * 100 + __GNUC_MINOR__)
#endif

#define _LIBCPP_VERSION 1101

#define _LIBCPP_ABI_VERSION 1

#define _LIBCPP_CONCAT1(_LIBCPP_X,_LIBCPP_Y) _LIBCPP_X##_LIBCPP_Y
#define _LIBCPP_CONCAT(_LIBCPP_X,_LIBCPP_Y) _LIBCPP_CONCAT1(_LIBCPP_X,_LIBCPP_Y)

#define _LIBCPP_NAMESPACE _LIBCPP_CONCAT(__,_LIBCPP_ABI_VERSION)

#ifdef __LITTLE_ENDIAN__
#if __LITTLE_ENDIAN__
#define _LIBCPP_LITTLE_ENDIAN 1
#define _LIBCPP_BIG_ENDIAN    0
#endif  // __LITTLE_ENDIAN__
#endif  // __LITTLE_ENDIAN__
#ifdef __BIG_ENDIAN__
#if __BIG_ENDIAN__
#define _LIBCPP_LITTLE_ENDIAN 0
#define _LIBCPP_BIG_ENDIAN    1
#endif  // __BIG_ENDIAN__
#endif  // __BIG_ENDIAN__
#ifdef __FreeBSD__
# include <sys/endian.h>
#  if _BYTE_ORDER == _LITTLE_ENDIAN
#   define _LIBCPP_LITTLE_ENDIAN 1
#   define _LIBCPP_BIG_ENDIAN    0
# else  // _BYTE_ORDER == _LITTLE_ENDIAN
#   define _LIBCPP_LITTLE_ENDIAN 0
#   define _LIBCPP_BIG_ENDIAN    1
# endif  // _BYTE_ORDER == _LITTLE_ENDIAN
# ifndef __LONG_LONG_SUPPORTED
#  define _LIBCPP_HAS_NO_LONG_LONG
# endif  // __LONG_LONG_SUPPORTED
#endif  // __FreeBSD__
#ifdef _WIN32
#  define _LIBCPP_LITTLE_ENDIAN 1
#  define _LIBCPP_BIG_ENDIAN    0
// Compiler intrinsics (GCC or MSVC)
#  if (defined(_MSC_VER) && _MSC_VER >= 1400) \
   || (defined(__GNUC__) && _GNUC_VER > 403)
#    define _LIBCP_HAS_IS_BASE_OF
#  endif
#endif  // _WIN32
#ifdef __linux__
#  if defined(__GNUC__) && _GNUC_VER >= 403
#    define _LIBCP_HAS_IS_BASE_OF
#  endif
#endif

#ifdef __sun__
# include <sys/isa_defs.h>
# ifdef _LITTLE_ENDIAN
#   define _LIBCPP_LITTLE_ENDIAN 1
#   define _LIBCPP_BIG_ENDIAN    0
# else
#   define _LIBCPP_LITTLE_ENDIAN 0
#   define _LIBCPP_BIG_ENDIAN    1
# endif
#endif // __sun__
#if defined(__BYTE_ORDER__)

# if __BYTE_ORDER__ == 1234
#   define _LIBCPP_LITTLE_ENDIAN 1
#   define _LIBCPP_BIG_ENDIAN    0
# else
#   define _LIBCPP_LITTLE_ENDIAN 0
#   define _LIBCPP_BIG_ENDIAN    1
#endif

#endif

#if !defined(_LIBCPP_LITTLE_ENDIAN) || !defined(_LIBCPP_BIG_ENDIAN)
# include <endian.h>
# if __BYTE_ORDER == __LITTLE_ENDIAN
#  define _LIBCPP_LITTLE_ENDIAN 1
#  define _LIBCPP_BIG_ENDIAN    0
# elif __BYTE_ORDER == __BIG_ENDIAN
#  define _LIBCPP_LITTLE_ENDIAN 0
#  define _LIBCPP_BIG_ENDIAN    1
# else  // __BYTE_ORDER == __BIG_ENDIAN
#  error unable to determine endian
# endif
#endif  // !defined(_LIBCPP_LITTLE_ENDIAN) || !defined(_LIBCPP_BIG_ENDIAN)
#ifdef _WIN32

// only really useful for a DLL
#ifdef _LIBCPP_DLL // this should be a compiler builtin define ideally...
# ifdef cxx_EXPORTS
#  define _LIBCPP_HIDDEN
#  define _LIBCPP_VISIBLE __declspec(dllexport)
# else
#  define _LIBCPP_HIDDEN
#  define _LIBCPP_VISIBLE __declspec(dllimport)
# endif
#else
# define _LIBCPP_HIDDEN
# define _LIBCPP_VISIBLE
#endif

#ifndef _LIBCPP_INLINE_VISIBILITY
# if _MSC_VER
#  define _LIBCPP_INLINE_VISIBILITY __forceinline
# else // MinGW GCC and Clang
#  define _LIBCPP_INLINE_VISIBILITY __attribute__ ((__always_inline__))
# endif
#endif

#ifndef _LIBCPP_EXCEPTION_ABI
#define _LIBCPP_EXCEPTION_ABI _LIBCPP_VISIBLE
#endif

#ifndef _LIBCPP_ALWAYS_INLINE
# if _MSC_VER
#  define _LIBCPP_ALWAYS_INLINE __forceinline
# endif
#endif

#endif // _WIN32
#ifndef _LIBCPP_HIDDEN
//#define _LIBCPP_HIDDEN __attribute__ ((__visibility__("hidden")))
#define _LIBCPP_HIDDEN
#endif

#ifndef _LIBCPP_VISIBLE
//#define _LIBCPP_VISIBLE __attribute__ ((__visibility__("default")))
#define _LIBCPP_VISIBLE
#endif

#ifndef _LIBCPP_INLINE_VISIBILITY
//#define _LIBCPP_INLINE_VISIBILITY __attribute__ ((__always_inline__)) __attribute__ ((__visibility__("hidden")))
#define _LIBCPP_INLINE_VISIBILITY __attribute__ ((__always_inline__))
#endif

#ifndef _LIBCPP_EXCEPTION_ABI
//#define _LIBCPP_EXCEPTION_ABI __attribute__ ((__visibility__("default")))
#define _LIBCPP_EXCEPTION_ABI
#endif

#ifndef _LIBCPP_CANTTHROW
#define _LIBCPP_CANTTHROW __attribute__ ((__nothrow__))
#endif

#ifndef _LIBCPP_ALWAYS_INLINE
//#define _LIBCPP_ALWAYS_INLINE  __attribute__ ((__always_inline__)) __attribute__ ((__visibility__("hidden")))
#define _LIBCPP_ALWAYS_INLINE  __attribute__ ((__always_inline__))
#endif

#if defined(__clang__)

#if __has_feature(cxx_alignas)
#  define _ALIGNAS_TYPE(x) alignas(x)
#  define _ALIGNAS(x) alignas(x)
#else
#  define _ALIGNAS_TYPE(x) __attribute__((__aligned__(__alignof(x))))
#  define _ALIGNAS(x) __attribute__((__aligned__(x)))
#endif

#if !__has_feature(cxx_alias_templates)
#define _LIBCPP_HAS_NO_TEMPLATE_ALIASES
#endif

#ifndef __GXX_EXPERIMENTAL_CXX0X__
#ifdef __linux__
#define _LIBCPP_HAS_NO_UNICODE_CHARS
#else
typedef __char16_t char16_t;
typedef __char32_t char32_t;
#endif
#endif

#if !(__has_feature(cxx_exceptions))
#define _LIBCPP_NO_EXCEPTIONS
#endif

#if !(__has_feature(cxx_rtti))
#define _LIBCPP_NO_RTTI
#endif

#if !(__has_feature(cxx_strong_enums))
#define _LIBCPP_HAS_NO_STRONG_ENUMS
#endif

#if !(__has_feature(cxx_decltype))
#define _LIBCPP_HAS_NO_DECLTYPE
#endif

#if __has_feature(cxx_attributes)
#  define _LIBCPP_NORETURN [[noreturn]]
#else
#  define _LIBCPP_NORETURN __attribute__ ((noreturn))
#endif

#define _LIBCPP_HAS_NO_DEFAULTED_FUNCTIONS

#if !(__has_feature(cxx_deleted_functions))
#define _LIBCPP_HAS_NO_DELETED_FUNCTIONS
#endif  // !(__has_feature(cxx_deleted_functions))
#if !(__has_feature(cxx_lambdas))
#define _LIBCPP_HAS_NO_LAMBDAS
#endif

#if !(__has_feature(cxx_nullptr))
#define _LIBCPP_HAS_NO_NULLPTR
#endif

#if !(__has_feature(cxx_rvalue_references))
#define _LIBCPP_HAS_NO_RVALUE_REFERENCES
#endif

#if !(__has_feature(cxx_static_assert))
#define _LIBCPP_HAS_NO_STATIC_ASSERT
#endif

#if !(__has_feature(cxx_auto_type))
#define _LIBCPP_HAS_NO_AUTO_TYPE
#endif

#if !(__has_feature(cxx_access_control_sfinae)) || !__has_feature(cxx_trailing_return)
#define _LIBCPP_HAS_NO_ADVANCED_SFINAE
#endif

#if !(__has_feature(cxx_variadic_templates))
#define _LIBCPP_HAS_NO_VARIADICS
#endif

#if !(__has_feature(cxx_trailing_return))
#define _LIBCPP_HAS_NO_TRAILING_RETURN
#endif

#if !(__has_feature(cxx_generalized_initializers))
#define _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS
#endif

#if __has_feature(is_base_of)
#  define _LIBCP_HAS_IS_BASE_OF
#endif

// Objective-C++ features (opt-in)
#if __has_feature(objc_arc)
#define _LIBCPP_HAS_OBJC_ARC
#endif

#if __has_feature(objc_arc_weak)
#define _LIBCPP_HAS_OBJC_ARC_WEAK
#define _LIBCPP_HAS_NO_STRONG_ENUMS
#endif

#if !(__has_feature(cxx_constexpr))
#define _LIBCPP_HAS_NO_CONSTEXPR
#endif

#ifdef __FreeBSD__
#if __FreeBSD__ && (__ISO_C_VISIBLE >= 2011 || __cplusplus >= 201103L)
#define _LIBCPP_HAS_QUICK_EXIT
#define _LIBCPP_HAS_C11_FEATURES
#endif
#endif

#if defined(__MICRO_OS_PLUS_PLUS__) //(__has_feature(cxx_noexcept))
#  define _NOEXCEPT noexcept
#  define _NOEXCEPT_(x) noexcept(x)
#else
#  define _NOEXCEPT throw()
#  define _NOEXCEPT_(x)
#endif

#if __has_feature(underlying_type)
#  define _LIBCXX_UNDERLYING_TYPE(T) __underlying_type(T)
#endif

#if !defined(__MICRO_OS_PLUS_PLUS__)

// Inline namespaces are available in Clang regardless of C++ dialect.
#define _LIBCPP_BEGIN_NAMESPACE_STD namespace std {inline namespace _LIBCPP_NAMESPACE {
#define _LIBCPP_END_NAMESPACE_STD  } }
#define _VSTD std::_LIBCPP_NAMESPACE

namespace std
  {
    inline namespace _LIBCPP_NAMESPACE
      {
      }
  }

#else

#if defined(__MICRO_OS_PLUS_PLUS__)
#define _LIBCPP_BEGIN_NAMESPACE_STD namespace os {inline namespace std {
#define _LIBCPP_END_NAMESPACE_STD  } }
#define _VSTD os::std
#else
#define _LIBCPP_BEGIN_NAMESPACE_STD namespace std {
#define _LIBCPP_END_NAMESPACE_STD  }
#define _VSTD std
#endif

#endif

#elif defined(__GNUC__)

#define _ALIGNAS(x) __attribute__((__aligned__(x)))
#define _ALIGNAS_TYPE(x) __attribute__((__aligned__(__alignof(x))))

#define _LIBCPP_NORETURN __attribute__((noreturn))

//#if !__EXCEPTIONS
#if 1 || !__EXCEPTIONS
#define _LIBCPP_NO_EXCEPTIONS
#endif

#define _LIBCPP_HAS_NO_TEMPLATE_ALIASES
#define _LIBCPP_HAS_NO_CONSTEXPR

#define _NOEXCEPT throw()
#define _NOEXCEPT_(x)

#ifndef __GXX_EXPERIMENTAL_CXX0X__

#define _LIBCPP_HAS_NO_ADVANCED_SFINAE
#define _LIBCPP_HAS_NO_DECLTYPE
#define _LIBCPP_HAS_NO_DEFAULTED_FUNCTIONS
#define _LIBCPP_HAS_NO_DELETED_FUNCTIONS
#define _LIBCPP_HAS_NO_NULLPTR
#define _LIBCPP_HAS_NO_STATIC_ASSERT
#define _LIBCPP_HAS_NO_UNICODE_CHARS
#define _LIBCPP_HAS_NO_VARIADICS
#define _LIBCPP_HAS_NO_RVALUE_REFERENCES
#define _LIBCPP_HAS_NO_ALWAYS_INLINE_VARIADICS

#else  // __GXX_EXPERIMENTAL_CXX0X__
#define _LIBCPP_HAS_NO_TRAILING_RETURN
#define _LIBCPP_HAS_NO_ALWAYS_INLINE_VARIADICS

#if _GNUC_VER < 403
#define _LIBCPP_HAS_NO_RVALUE_REFERENCES
#endif

#if _GNUC_VER < 403
#define _LIBCPP_HAS_NO_STATIC_ASSERT
#endif

#if _GNUC_VER < 404
#define _LIBCPP_HAS_NO_ADVANCED_SFINAE
#define _LIBCPP_HAS_NO_DECLTYPE
#define _LIBCPP_HAS_NO_DEFAULTED_FUNCTIONS
#define _LIBCPP_HAS_NO_DELETED_FUNCTIONS
#define _LIBCPP_HAS_NO_UNICODE_CHARS
#define _LIBCPP_HAS_NO_VARIADICS
#define _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS
#endif  // _GNUC_VER < 404
#if _GNUC_VER < 406
#define _LIBCPP_HAS_NO_NULLPTR
#endif

#endif  // __GXX_EXPERIMENTAL_CXX0X__
#if !defined(__MICRO_OS_PLUS_PLUS__)

#define _LIBCPP_BEGIN_NAMESPACE_STD namespace std { namespace _LIBCPP_NAMESPACE {
#define _LIBCPP_END_NAMESPACE_STD  } }
#define _VSTD std::_LIBCPP_NAMESPACE

namespace std
  {
    namespace _LIBCPP_NAMESPACE
      {
      }
    using namespace _LIBCPP_NAMESPACE __attribute__((__strong__));
  }

#else

#if defined(__MICRO_OS_PLUS_PLUS__)
#define _LIBCPP_BEGIN_NAMESPACE_STD namespace os {inline namespace std {
#define _LIBCPP_END_NAMESPACE_STD  } }
#define _VSTD os::std
#else
#define _LIBCPP_BEGIN_NAMESPACE_STD namespace std {
#define _LIBCPP_END_NAMESPACE_STD  }
#define _VSTD std
#endif
#endif

#elif defined(_MSC_VER)

#define _LIBCPP_HAS_NO_TEMPLATE_ALIASES
#define _LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER
#define _LIBCPP_HAS_NO_CONSTEXPR
#define _LIBCPP_HAS_NO_UNICODE_CHARS
#define _LIBCPP_HAS_NO_DELETED_FUNCTIONS
#define __alignof__ __alignof
#define _LIBCPP_NORETURN __declspec(noreturn)
#define _ALIGNAS(x) __declspec(align(x))
#define _LIBCPP_HAS_NO_VARIADICS

#define _NOEXCEPT throw()
#define _NOEXCEPT_(x)

#define _LIBCPP_BEGIN_NAMESPACE_STD namespace std {
#define _LIBCPP_END_NAMESPACE_STD  }
#define _VSTD std

namespace std
  {
  }

#endif // __clang__ || __GNUC___ || _MSC_VER
#ifdef _LIBCPP_HAS_NO_UNICODE_CHARS
typedef unsigned short char16_t;
typedef unsigned int char32_t;
#endif  // _LIBCPP_HAS_NO_UNICODE_CHARS
#ifdef _LIBCPP_HAS_NO_STATIC_ASSERT

#if !defined(__DOXYGEN__)
template<bool>
struct __static_assert_test;
template<>
struct __static_assert_test<true>
  {
  };
template<unsigned>
struct __static_assert_check
  {
  };
#define static_assert(__b, __m) \
    typedef __static_assert_check<sizeof(__static_assert_test<(__b)>)> \
    _LIBCPP_CONCAT(__t, __LINE__)
#endif

#endif  // _LIBCPP_HAS_NO_STATIC_ASSERT
#ifdef _LIBCPP_HAS_NO_DECLTYPE
#define decltype(x) __typeof__(x)
#endif

#if !defined(__MICRO_OS_PLUS_PLUS__) //defined(_LIBCPP_HAS_NO_CONSTEXPR)
#define _LIBCPP_CONSTEXPR
#else
#define _LIBCPP_CONSTEXPR constexpr
#endif

#ifdef __GNUC__
#define _NOALIAS __attribute__((malloc))
#else
#define _NOALIAS
#endif

#ifndef __has_feature
#define __has_feature(__x) 0
#endif

#if defined(__MICRO_OS_PLUS_PLUS__) //__has_feature(cxx_explicit_conversions)
#   define _LIBCPP_EXPLICIT explicit
#else
#   define _LIBCPP_EXPLICIT
#endif

#ifdef _LIBCPP_HAS_NO_STRONG_ENUMS
#define _LIBCPP_DECLARE_STRONG_ENUM(x) struct _LIBCPP_VISIBLE x { enum __lx
#define _LIBCPP_DECLARE_STRONG_ENUM_EPILOG(x) \
    __lx __v_; \
    _LIBCPP_ALWAYS_INLINE x(__lx __v) : __v_(__v) {} \
    _LIBCPP_ALWAYS_INLINE explicit x(int __v) : __v_(static_cast<__lx>(__v)) {} \
    _LIBCPP_ALWAYS_INLINE operator int() const {return __v_;} \
    };
#else  // _LIBCPP_HAS_NO_STRONG_ENUMS
#define _LIBCPP_DECLARE_STRONG_ENUM(x) enum class _LIBCPP_VISIBLE x
#define _LIBCPP_DECLARE_STRONG_ENUM_EPILOG(x)
#endif  // _LIBCPP_HAS_NO_STRONG_ENUMS
#ifndef _LIBCPP_EXTERN_TEMPLATE
#define _LIBCPP_EXTERN_TEMPLATE(...) extern template __VA_ARGS__;
#endif

#if defined(__APPLE__) || defined(__FreeBSD__) || defined(_WIN32) || defined(__sun__)
#define _LIBCPP_LOCALE__L_EXTENSIONS 1
#endif
#if defined(__FreeBSD__)
#define _DECLARE_C99_LDBL_MATH 1
#endif

#if defined(__APPLE__) || defined(__FreeBSD__)
#define _LIBCPP_HAS_DEFAULTRUNELOCALE
#endif

#if defined(__APPLE__) || defined(__FreeBSD__) || defined(__sun__)
#define _LIBCPP_WCTYPE_IS_MASK
#endif

#ifdef _LIBCPP_DEBUG2
#   if _LIBCPP_DEBUG2 == 0
#       define _LIBCPP_DEBUG_LEVEL 1
#   elif _LIBCPP_DEBUG2 == 1
#       define _LIBCPP_DEBUG_LEVEL 2
#   else
#       error Supported values for _LIBCPP_DEBUG2 are 0 and 1
#   endif
#else
#       define _LIBCPP_DEBUG_LEVEL 0
#endif

#ifdef _LIBCPP_DEBUG2
#   include <__debug>
#else
#   define _LIBCPP_ASSERT(x, m) ((void)0)
#endif

// ----------------------------------------------------------------------------
// µOS++ specifics

#if defined(__ARM_EABI__)
#define _LIBCPP_HAS_NO_LONG_LONG
#endif

//#if defined(OS_INCLUDE_STD_EXCEPTIONS)
//#undef OS_INCLUDE_STD_EXCEPTIONS
//#endif

// force HAS_NO_GENERALIZED_INITIALIZERS
#ifdef _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS
#undef _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS
#endif

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
#define _LIBCPP_HAS_NO_RVALUE_REFERENCES
#endif

#ifndef _LIBCPP_HAS_NO_ADVANCED_SFINAE
#define _LIBCPP_HAS_NO_ADVANCED_SFINAE
#endif

#ifdef _LIBCPP_HAS_NO_NULLPTR
#error "nullptr is mandatory"
#endif

#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_CONFIG_H_
