// -*- C++ -*-
//===--------------------------- stdexcept --------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP_STDEXCEPT
#define _LIBCPP_STDEXCEPT

/*
    stdexcept synopsis

namespace std
{

class logic_error;
    class domain_error;
    class invalid_argument;
    class length_error;
    class out_of_range;
class runtime_error;
    class range_error;
    class overflow_error;
    class underflow_error;

for each class xxx_error:

class xxx_error : public exception // at least indirectly
{
public:
    explicit xxx_error(const string& what_arg);
    explicit xxx_error(const char*   what_arg);

    virtual const char* what() const noexcept // returns what_arg
};

}  // std

*/

#if defined(__MICRO_OS_PLUS_PLUS__)
#include "portable/language/cpp/include/__config.h"
#include "portable/language/cpp/include/exception"
#include "portable/language/cpp/include/iosfwd"  // for string forward decl

#else
#include <__config>
#include <exception>
#include <iosfwd>  // for string forward decl

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif
#endif

#if defined(__MICRO_OS_PLUS_PLUS__)
namespace os {
#endif

namespace std  // purposefully not using versioning namespace
{

class _LIBCPP_EXCEPTION_ABI logic_error
    : public exception
{
private:
    void* __imp_;
public:
    explicit logic_error(const string&);
    explicit logic_error(const char*);

    logic_error(const logic_error&) _NOEXCEPT;
    logic_error& operator=(const logic_error&) _NOEXCEPT;

    virtual ~logic_error() _NOEXCEPT;

    virtual const char* what() const _NOEXCEPT;
};

class _LIBCPP_EXCEPTION_ABI runtime_error
    : public exception
{
private:
    void* __imp_;
public:
    explicit runtime_error(const string&);
    explicit runtime_error(const char*);

    runtime_error(const runtime_error&) _NOEXCEPT;
    runtime_error& operator=(const runtime_error&) _NOEXCEPT;

    virtual ~runtime_error() _NOEXCEPT;

    virtual const char* what() const _NOEXCEPT;
};

class _LIBCPP_EXCEPTION_ABI domain_error
    : public logic_error
{
public:
    _LIBCPP_INLINE_VISIBILITY explicit domain_error(const string& __s) : logic_error(__s) {}
    _LIBCPP_INLINE_VISIBILITY explicit domain_error(const char* __s)   : logic_error(__s) {}

    virtual ~domain_error() _NOEXCEPT;
};

class _LIBCPP_EXCEPTION_ABI invalid_argument
    : public logic_error
{
public:
    _LIBCPP_INLINE_VISIBILITY explicit invalid_argument(const string& __s) : logic_error(__s) {}
    _LIBCPP_INLINE_VISIBILITY explicit invalid_argument(const char* __s)   : logic_error(__s) {}

    virtual ~invalid_argument() _NOEXCEPT;
};

class _LIBCPP_EXCEPTION_ABI length_error
    : public logic_error
{
public:
    _LIBCPP_INLINE_VISIBILITY explicit length_error(const string& __s) : logic_error(__s) {}
    _LIBCPP_INLINE_VISIBILITY explicit length_error(const char* __s)   : logic_error(__s) {}

    virtual ~length_error() _NOEXCEPT;
};

class _LIBCPP_EXCEPTION_ABI out_of_range
    : public logic_error
{
public:
    _LIBCPP_INLINE_VISIBILITY explicit out_of_range(const string& __s) : logic_error(__s) {}
    _LIBCPP_INLINE_VISIBILITY explicit out_of_range(const char* __s)   : logic_error(__s) {}

    virtual ~out_of_range() _NOEXCEPT;
};

class _LIBCPP_EXCEPTION_ABI range_error
    : public runtime_error
{
public:
    _LIBCPP_INLINE_VISIBILITY explicit range_error(const string& __s) : runtime_error(__s) {}
    _LIBCPP_INLINE_VISIBILITY explicit range_error(const char* __s)   : runtime_error(__s) {}

    virtual ~range_error() _NOEXCEPT;
};

class _LIBCPP_EXCEPTION_ABI overflow_error
    : public runtime_error
{
public:
    _LIBCPP_INLINE_VISIBILITY explicit overflow_error(const string& __s) : runtime_error(__s) {}
    _LIBCPP_INLINE_VISIBILITY explicit overflow_error(const char* __s)   : runtime_error(__s) {}

    virtual ~overflow_error() _NOEXCEPT;
};

class _LIBCPP_EXCEPTION_ABI underflow_error
    : public runtime_error
{
public:
    _LIBCPP_INLINE_VISIBILITY explicit underflow_error(const string& __s) : runtime_error(__s) {}
    _LIBCPP_INLINE_VISIBILITY explicit underflow_error(const char* __s)   : runtime_error(__s) {}

    virtual ~underflow_error() _NOEXCEPT;
};

}  // std
#if defined(__MICRO_OS_PLUS_PLUS__)
}
#endif

#endif  // _LIBCPP_STDEXCEPT
