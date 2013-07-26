// -*- C++ -*-
//===-------------------------- exception ---------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_EXCEPTION_H
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_EXCEPTION_H

#include "portable/language/cpp/include/internal/__config.h"
//#include "portable/language/cpp/include/cstddef.h"
//#include "portable/language/cpp/include/type_traits.h"

namespace os {
namespace std
{


class _LIBCPP_EXCEPTION_ABI exception
{
public:
    _LIBCPP_INLINE_VISIBILITY exception() _NOEXCEPT {}
    virtual ~exception() _NOEXCEPT;
    virtual const char* what() const _NOEXCEPT;
};

class _LIBCPP_EXCEPTION_ABI bad_exception
    : public exception
{
public:
    _LIBCPP_INLINE_VISIBILITY bad_exception() _NOEXCEPT {}
    virtual ~bad_exception() _NOEXCEPT;
    virtual const char* what() const _NOEXCEPT;
};

#if 0
typedef void (*unexpected_handler)();
_LIBCPP_VISIBLE unexpected_handler set_unexpected(unexpected_handler) _NOEXCEPT;
_LIBCPP_VISIBLE unexpected_handler get_unexpected() _NOEXCEPT;
_LIBCPP_NORETURN _LIBCPP_VISIBLE void unexpected();

typedef void (*terminate_handler)();
_LIBCPP_VISIBLE terminate_handler set_terminate(terminate_handler) _NOEXCEPT;
_LIBCPP_VISIBLE terminate_handler get_terminate() _NOEXCEPT;
#endif
_LIBCPP_NORETURN _LIBCPP_VISIBLE void terminate() _NOEXCEPT __attribute__((noreturn));

#if 0

_LIBCPP_VISIBLE bool uncaught_exception() _NOEXCEPT;

class _LIBCPP_VISIBLE exception_ptr;

exception_ptr  current_exception() _NOEXCEPT ;
_LIBCPP_NORETURN void  rethrow_exception(exception_ptr) ;

class _LIBCPP_VISIBLE exception_ptr
{
    void* __ptr_;
public:
    _LIBCPP_INLINE_VISIBILITY exception_ptr() _NOEXCEPT : __ptr_() {}
    _LIBCPP_INLINE_VISIBILITY exception_ptr(nullptr_t) _NOEXCEPT : __ptr_() {}
    exception_ptr(const exception_ptr&) _NOEXCEPT;
    exception_ptr& operator=(const exception_ptr&) _NOEXCEPT;
    ~exception_ptr() _NOEXCEPT;

    _LIBCPP_INLINE_VISIBILITY
    _LIBCPP_EXPLICIT
        operator bool() const _NOEXCEPT {return __ptr_ != nullptr;}

    friend _LIBCPP_INLINE_VISIBILITY
    bool operator==(const exception_ptr& __x, const exception_ptr& __y) _NOEXCEPT
        {return __x.__ptr_ == __y.__ptr_;}
    friend _LIBCPP_INLINE_VISIBILITY
    bool operator!=(const exception_ptr& __x, const exception_ptr& __y) _NOEXCEPT
        {return !(__x == __y);}

    friend exception_ptr current_exception() _NOEXCEPT;
    friend void rethrow_exception(exception_ptr);
};

template<class _Ep>
exception_ptr
make_exception_ptr(_Ep __e) _NOEXCEPT
{
#ifndef _LIBCPP_NO_EXCEPTIONS
    try
    {
        throw __e;
    }
    catch (...)
    {
        return current_exception();
    }
#endif  // _LIBCPP_NO_EXCEPTIONS
}

#endif

// nested_exception

#if 0
class _LIBCPP_EXCEPTION_ABI nested_exception
{
    exception_ptr __ptr_;
public:
    nested_exception() _NOEXCEPT;
//     nested_exception(const nested_exception&) noexcept = default;
//     nested_exception& operator=(const nested_exception&) noexcept = default;
    virtual ~nested_exception() _NOEXCEPT;

    // access functions
    _LIBCPP_NORETURN void rethrow_nested() const;
    _LIBCPP_INLINE_VISIBILITY exception_ptr nested_ptr() const _NOEXCEPT {return __ptr_;}
};

template <class _Tp>
struct __nested
    : public _Tp,
      public nested_exception
{
    _LIBCPP_INLINE_VISIBILITY explicit __nested(const _Tp& __t) : _Tp(__t) {}
};

template <class _Tp>
_LIBCPP_NORETURN
void
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
throw_with_nested(_Tp&& __t, typename enable_if<
                  is_class<typename remove_reference<_Tp>::type>::value &&
                  !is_base_of<nested_exception, typename remove_reference<_Tp>::type>::value
                                    >::type* = 0)
#else  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
throw_with_nested (_Tp& __t, typename enable_if<
                  is_class<_Tp>::value && !is_base_of<nested_exception, _Tp>::value
                                    >::type* = 0)
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
{
#ifndef _LIBCPP_NO_EXCEPTIONS
    throw __nested<typename remove_reference<_Tp>::type>(_VSTD::forward<_Tp>(__t));
#endif
}

template <class _Tp>
_LIBCPP_NORETURN
void
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
throw_with_nested(_Tp&& __t, typename enable_if<
                  !is_class<typename remove_reference<_Tp>::type>::value ||
                  is_base_of<nested_exception, typename remove_reference<_Tp>::type>::value
                                    >::type* = 0)
#else  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
throw_with_nested (_Tp& __t, typename enable_if<
                  !is_class<_Tp>::value || is_base_of<nested_exception, _Tp>::value
                                    >::type* = 0)
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
{
#ifndef _LIBCPP_NO_EXCEPTIONS
    throw _VSTD::forward<_Tp>(__t);
#endif
}

template <class _Ep>
inline _LIBCPP_INLINE_VISIBILITY
void
rethrow_if_nested(const _Ep& __e, typename enable_if<
                                   is_polymorphic<_Ep>::value
                                                   >::type* = 0)
{
    const nested_exception* __nep = dynamic_cast<const nested_exception*>(&__e);
    if (__nep)
        __nep->rethrow_nested();
}

template <class _Ep>
inline _LIBCPP_INLINE_VISIBILITY
void
rethrow_if_nested(const _Ep&, typename enable_if<
                                   !is_polymorphic<_Ep>::value
                                                   >::type* = 0)
{
}
#endif

}  // std
}

#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_EXCEPTION_H
