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
/// \brief String definitions.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STRING) || defined(__DOXYGEN)

#include "portable/language/cpp/include/string.h"
#include "portable/language/cpp/include/cstdlib.h"
//#include "portable/language/cpp/include/cwchar"
//#include "portable/language/cpp/include/cerrno"


namespace os
{
  namespace std
  {

template class __basic_string_common<true>;

template class basic_string<char>;
template class basic_string<wchar_t>;

template
    string
    operator+<char, char_traits<char>, allocator<char> >(char const*, string const&);

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

int
stoi(const string& str, size_t* idx, int base)
{
    char* ptr;
    const char* const p = str.c_str();
    typename remove_reference<decltype(errno)>::type errno_save = errno;
    errno = 0;
    long r = strtol(p, &ptr, base);
    swap(errno, errno_save);
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
    if (errno_save == ERANGE || r < numeric_limits<int>::min() ||
                                numeric_limits<int>::max() < r)
        throw out_of_range("stoi: out of range");
    if (ptr == p)
        throw invalid_argument("stoi: no conversion");
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
    if (idx)
        *idx = static_cast<size_t>(ptr - p);
    return static_cast<int>(r);
}

int
stoi(const wstring& str, size_t* idx, int base)
{
    wchar_t* ptr;
    const wchar_t* const p = str.c_str();
    typename remove_reference<decltype(errno)>::type errno_save = errno;
    errno = 0;
    long r = wcstol(p, &ptr, base);
    swap(errno, errno_save);
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
    if (errno_save == ERANGE || r < numeric_limits<int>::min() ||
                                numeric_limits<int>::max() < r)
        throw out_of_range("stoi: out of range");
    if (ptr == p)
        throw invalid_argument("stoi: no conversion");
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
    if (idx)
        *idx = static_cast<size_t>(ptr - p);
    return static_cast<int>(r);
}

long
stol(const string& str, size_t* idx, int base)
{
    char* ptr;
    const char* const p = str.c_str();
    typename remove_reference<decltype(errno)>::type errno_save = errno;
    errno = 0;
    long r = strtol(p, &ptr, base);
    swap(errno, errno_save);
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
    if (errno_save == ERANGE)
        throw out_of_range("stol: out of range");
    if (ptr == p)
        throw invalid_argument("stol: no conversion");
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
    if (idx)
        *idx = static_cast<size_t>(ptr - p);
    return r;
}

long
stol(const wstring& str, size_t* idx, int base)
{
    wchar_t* ptr;
    const wchar_t* const p = str.c_str();
    typename remove_reference<decltype(errno)>::type errno_save = errno;
    errno = 0;
    long r = wcstol(p, &ptr, base);
    swap(errno, errno_save);
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
    if (errno_save == ERANGE)
        throw out_of_range("stol: out of range");
    if (ptr == p)
        throw invalid_argument("stol: no conversion");
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
    if (idx)
        *idx = static_cast<size_t>(ptr - p);
    return r;
}

unsigned long
stoul(const string& str, size_t* idx, int base)
{
    char* ptr;
    const char* const p = str.c_str();
    typename remove_reference<decltype(errno)>::type errno_save = errno;
    errno = 0;
    unsigned long r = strtoul(p, &ptr, base);
    swap(errno, errno_save);
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
    if (errno_save == ERANGE)
        throw out_of_range("stoul: out of range");
    if (ptr == p)
        throw invalid_argument("stoul: no conversion");
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
    if (idx)
        *idx = static_cast<size_t>(ptr - p);
    return r;
}

unsigned long
stoul(const wstring& str, size_t* idx, int base)
{
    wchar_t* ptr;
    const wchar_t* const p = str.c_str();
    typename remove_reference<decltype(errno)>::type errno_save = errno;
    errno = 0;
    unsigned long r = wcstoul(p, &ptr, base);
    swap(errno, errno_save);
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
    if (errno_save == ERANGE)
        throw out_of_range("stoul: out of range");
    if (ptr == p)
        throw invalid_argument("stoul: no conversion");
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
    if (idx)
        *idx = static_cast<size_t>(ptr - p);
    return r;
}

long long
stoll(const string& str, size_t* idx, int base)
{
    char* ptr;
    const char* const p = str.c_str();
    typename remove_reference<decltype(errno)>::type errno_save = errno;
    errno = 0;
    long long r = strtoll(p, &ptr, base);
    swap(errno, errno_save);
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
    if (errno_save == ERANGE)
        throw out_of_range("stoll: out of range");
    if (ptr == p)
        throw invalid_argument("stoll: no conversion");
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
    if (idx)
        *idx = static_cast<size_t>(ptr - p);
    return r;
}

long long
stoll(const wstring& str, size_t* idx, int base)
{
    wchar_t* ptr;
    const wchar_t* const p = str.c_str();
    typename remove_reference<decltype(errno)>::type errno_save = errno;
    errno = 0;
    long long r = wcstoll(p, &ptr, base);
    swap(errno, errno_save);
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
    if (errno_save == ERANGE)
        throw out_of_range("stoll: out of range");
    if (ptr == p)
        throw invalid_argument("stoll: no conversion");
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
    if (idx)
        *idx = static_cast<size_t>(ptr - p);
    return r;
}

unsigned long long
stoull(const string& str, size_t* idx, int base)
{
    char* ptr;
    const char* const p = str.c_str();
    typename remove_reference<decltype(errno)>::type errno_save = errno;
    errno = 0;
    unsigned long long r = strtoull(p, &ptr, base);
    swap(errno, errno_save);
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
    if (errno_save == ERANGE)
        throw out_of_range("stoull: out of range");
    if (ptr == p)
        throw invalid_argument("stoull: no conversion");
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
    if (idx)
        *idx = static_cast<size_t>(ptr - p);
    return r;
}

unsigned long long
stoull(const wstring& str, size_t* idx, int base)
{
    wchar_t* ptr;
    const wchar_t* const p = str.c_str();
    typename remove_reference<decltype(errno)>::type errno_save = errno;
    errno = 0;
    unsigned long long r = wcstoull(p, &ptr, base);
    swap(errno, errno_save);
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
    if (errno_save == ERANGE)
        throw out_of_range("stoull: out of range");
    if (ptr == p)
        throw invalid_argument("stoull: no conversion");
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
    if (idx)
        *idx = static_cast<size_t>(ptr - p);
    return r;
}

float
stof(const string& str, size_t* idx)
{
    char* ptr;
    const char* const p = str.c_str();
    typename remove_reference<decltype(errno)>::type errno_save = errno;
    errno = 0;
    float r = strtof(p, &ptr);
    swap(errno, errno_save);
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
    if (errno_save == ERANGE)
        throw out_of_range("stof: out of range");
    if (ptr == p)
        throw invalid_argument("stof: no conversion");
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
    if (idx)
        *idx = static_cast<size_t>(ptr - p);
    return r;
}

float
stof(const wstring& str, size_t* idx)
{
    wchar_t* ptr;
    const wchar_t* const p = str.c_str();
    typename remove_reference<decltype(errno)>::type errno_save = errno;
    errno = 0;
    float r = wcstof(p, &ptr);
    swap(errno, errno_save);
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
    if (errno_save == ERANGE)
        throw out_of_range("stof: out of range");
    if (ptr == p)
        throw invalid_argument("stof: no conversion");
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
    if (idx)
        *idx = static_cast<size_t>(ptr - p);
    return r;
}

double
stod(const string& str, size_t* idx)
{
    char* ptr;
    const char* const p = str.c_str();
    typename remove_reference<decltype(errno)>::type errno_save = errno;
    errno = 0;
    double r = strtod(p, &ptr);
    swap(errno, errno_save);
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
    if (errno_save == ERANGE)
        throw out_of_range("stod: out of range");
    if (ptr == p)
        throw invalid_argument("stod: no conversion");
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
    if (idx)
        *idx = static_cast<size_t>(ptr - p);
    return r;
}

double
stod(const wstring& str, size_t* idx)
{
    wchar_t* ptr;
    const wchar_t* const p = str.c_str();
    typename remove_reference<decltype(errno)>::type errno_save = errno;
    errno = 0;
    double r = wcstod(p, &ptr);
    swap(errno, errno_save);
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
    if (errno_save == ERANGE)
        throw out_of_range("stod: out of range");
    if (ptr == p)
        throw invalid_argument("stod: no conversion");
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
    if (idx)
        *idx = static_cast<size_t>(ptr - p);
    return r;
}

long double
stold(const string& str, size_t* idx)
{
    char* ptr;
    const char* const p = str.c_str();
    typename remove_reference<decltype(errno)>::type errno_save = errno;
    errno = 0;
    long double r = strtold(p, &ptr);
    swap(errno, errno_save);
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
    if (errno_save == ERANGE)
        throw out_of_range("stold: out of range");
    if (ptr == p)
        throw invalid_argument("stold: no conversion");
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
    if (idx)
        *idx = static_cast<size_t>(ptr - p);
    return r;
}

long double
stold(const wstring& str, size_t* idx)
{
    wchar_t* ptr;
    const wchar_t* const p = str.c_str();
    typename remove_reference<decltype(errno)>::type errno_save = errno;
    errno = 0;
    long double r = wcstold(p, &ptr);
    swap(errno, errno_save);
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
    if (errno_save == ERANGE)
        throw out_of_range("stold: out of range");
    if (ptr == p)
        throw invalid_argument("stold: no conversion");
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
    if (idx)
        *idx = static_cast<size_t>(ptr - p);
    return r;
}

#endif // #if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

string to_string(int val)
{
    string s;
    s.resize(s.capacity());
    while (true)
    {
        size_t n2 = static_cast<size_t>(snprintf(&s[0], s.size()+1, "%d", val));
        if (n2 <= s.size())
        {
            s.resize(n2);
            break;
        }
        s.resize(n2);
    }
    return s;
}

string to_string(unsigned val)
{
    string s;
    s.resize(s.capacity());
    while (true)
    {
        size_t n2 = static_cast<size_t>(snprintf(&s[0], s.size()+1, "%u", val));
        if (n2 <= s.size())
        {
            s.resize(n2);
            break;
        }
        s.resize(n2);
    }
    return s;
}

string to_string(long val)
{
    string s;
    s.resize(s.capacity());
    while (true)
    {
        size_t n2 = static_cast<size_t>(snprintf(&s[0], s.size()+1, "%ld", val));
        if (n2 <= s.size())
        {
            s.resize(n2);
            break;
        }
        s.resize(n2);
    }
    return s;
}

string to_string(unsigned long val)
{
    string s;
    s.resize(s.capacity());
    while (true)
    {
        size_t n2 = static_cast<size_t>(snprintf(&s[0], s.size()+1, "%lu", val));
        if (n2 <= s.size())
        {
            s.resize(n2);
            break;
        }
        s.resize(n2);
    }
    return s;
}

string to_string(long long val)
{
    string s;
    s.resize(s.capacity());
    while (true)
    {
        size_t n2 = static_cast<size_t>(snprintf(&s[0], s.size()+1, "%lld", val));
        if (n2 <= s.size())
        {
            s.resize(n2);
            break;
        }
        s.resize(n2);
    }
    return s;
}

string to_string(unsigned long long val)
{
    string s;
    s.resize(s.capacity());
    while (true)
    {
        size_t n2 = static_cast<size_t>(snprintf(&s[0], s.size()+1, "%llu", val));
        if (n2 <= s.size())
        {
            s.resize(n2);
            break;
        }
        s.resize(n2);
    }
    return s;
}

string to_string(float val)
{
    string s;
    s.resize(s.capacity());
    while (true)
    {
        size_t n2 = static_cast<size_t>(snprintf(&s[0], s.size()+1, "%f", val));
        if (n2 <= s.size())
        {
            s.resize(n2);
            break;
        }
        s.resize(n2);
    }
    return s;
}

string to_string(double val)
{
    string s;
    s.resize(s.capacity());
    while (true)
    {
        size_t n2 = static_cast<size_t>(snprintf(&s[0], s.size()+1, "%f", val));
        if (n2 <= s.size())
        {
            s.resize(n2);
            break;
        }
        s.resize(n2);
    }
    return s;
}

string to_string(long double val)
{
    string s;
    s.resize(s.capacity());
    while (true)
    {
        size_t n2 = static_cast<size_t>(snprintf(&s[0], s.size()+1, "%Lf", val));
        if (n2 <= s.size())
        {
            s.resize(n2);
            break;
        }
        s.resize(n2);
    }
    return s;
}

wstring to_wstring(int val)
{
    const size_t n = (numeric_limits<int>::digits / 3)
          + ((numeric_limits<int>::digits % 3) != 0)
          + 1;
    wstring s(n, wchar_t());
    s.resize(s.capacity());
    while (true)
    {
        int n2 = swprintf(&s[0], s.size()+1, L"%d", val);
        if (n2 > 0)
        {
            s.resize(static_cast<size_t>(n2));
            break;
        }
        s.resize(2*s.size());
        s.resize(s.capacity());
    }
    return s;
}

wstring to_wstring(unsigned val)
{
    const size_t n = (numeric_limits<unsigned>::digits / 3)
          + ((numeric_limits<unsigned>::digits % 3) != 0)
          + 1;
    wstring s(n, wchar_t());
    s.resize(s.capacity());
    while (true)
    {
        int n2 = swprintf(&s[0], s.size()+1, L"%u", val);
        if (n2 > 0)
        {
            s.resize(static_cast<size_t>(n2));
            break;
        }
        s.resize(2*s.size());
        s.resize(s.capacity());
    }
    return s;
}

wstring to_wstring(long val)
{
    const size_t n = (numeric_limits<long>::digits / 3)
          + ((numeric_limits<long>::digits % 3) != 0)
          + 1;
    wstring s(n, wchar_t());
    s.resize(s.capacity());
    while (true)
    {
        int n2 = swprintf(&s[0], s.size()+1, L"%ld", val);
        if (n2 > 0)
        {
            s.resize(static_cast<size_t>(n2));
            break;
        }
        s.resize(2*s.size());
        s.resize(s.capacity());
    }
    return s;
}

wstring to_wstring(unsigned long val)
{
    const size_t n = (numeric_limits<unsigned long>::digits / 3)
          + ((numeric_limits<unsigned long>::digits % 3) != 0)
          + 1;
    wstring s(n, wchar_t());
    s.resize(s.capacity());
    while (true)
    {
        int n2 = swprintf(&s[0], s.size()+1, L"%lu", val);
        if (n2 > 0)
        {
            s.resize(static_cast<size_t>(n2));
            break;
        }
        s.resize(2*s.size());
        s.resize(s.capacity());
    }
    return s;
}

wstring to_wstring(long long val)
{
    const size_t n = (numeric_limits<long long>::digits / 3)
          + ((numeric_limits<long long>::digits % 3) != 0)
          + 1;
    wstring s(n, wchar_t());
    s.resize(s.capacity());
    while (true)
    {
        int n2 = swprintf(&s[0], s.size()+1, L"%lld", val);
        if (n2 > 0)
        {
            s.resize(static_cast<size_t>(n2));
            break;
        }
        s.resize(2*s.size());
        s.resize(s.capacity());
    }
    return s;
}

wstring to_wstring(unsigned long long val)
{
    const size_t n = (numeric_limits<unsigned long long>::digits / 3)
          + ((numeric_limits<unsigned long long>::digits % 3) != 0)
          + 1;
    wstring s(n, wchar_t());
    s.resize(s.capacity());
    while (true)
    {
        int n2 = swprintf(&s[0], s.size()+1, L"%llu", val);
        if (n2 > 0)
        {
            s.resize(static_cast<size_t>(n2));
            break;
        }
        s.resize(2*s.size());
        s.resize(s.capacity());
    }
    return s;
}

wstring to_wstring(float val)
{
    const size_t n = 20;
    wstring s(n, wchar_t());
    s.resize(s.capacity());
    while (true)
    {
        int n2 = swprintf(&s[0], s.size()+1, L"%f", val);
        if (n2 > 0)
        {
            s.resize(static_cast<size_t>(n2));
            break;
        }
        s.resize(2*s.size());
        s.resize(s.capacity());
    }
    return s;
}

wstring to_wstring(double val)
{
    const size_t n = 20;
    wstring s(n, wchar_t());
    s.resize(s.capacity());
    while (true)
    {
        int n2 = swprintf(&s[0], s.size()+1, L"%f", val);
        if (n2 > 0)
        {
            s.resize(static_cast<size_t>(n2));
            break;
        }
        s.resize(2*s.size());
        s.resize(s.capacity());
    }
    return s;
}

wstring to_wstring(long double val)
{
    const size_t n = 20;
    wstring s(n, wchar_t());
    s.resize(s.capacity());
    while (true)
    {
        int n2 = swprintf(&s[0], s.size()+1, L"%Lf", val);
        if (n2 > 0)
        {
            s.resize(static_cast<size_t>(n2));
            break;
        }
        s.resize(2*s.size());
        s.resize(s.capacity());
    }
    return s;
}


  } // namespace std
} // namespace os

#endif // defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STRING)
