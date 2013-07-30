// -*- C++ -*-
//===--------------------------- string -----------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP_STRING
#define _LIBCPP_STRING

/*
    string synopsis

namespace std
{

template <class stateT>
class fpos
{
private:
    stateT st;
public:
    fpos(streamoff = streamoff());

    operator streamoff() const;

    stateT state() const;
    void state(stateT);

    fpos& operator+=(streamoff);
    fpos  operator+ (streamoff) const;
    fpos& operator-=(streamoff);
    fpos  operator- (streamoff) const;
};

template <class stateT> streamoff operator-(const fpos<stateT>& x, const fpos<stateT>& y);

template <class stateT> bool operator==(const fpos<stateT>& x, const fpos<stateT>& y);
template <class stateT> bool operator!=(const fpos<stateT>& x, const fpos<stateT>& y);

template <class charT>
struct char_traits
{
    typedef charT     char_type;
    typedef ...       int_type;
    typedef streamoff off_type;
    typedef streampos pos_type;
    typedef mbstate_t state_type;

    static void assign(char_type& c1, const char_type& c2) noexcept;
    static constexpr bool eq(char_type c1, char_type c2) noexcept;
    static constexpr bool lt(char_type c1, char_type c2) noexcept;

    static int              compare(const char_type* s1, const char_type* s2, size_t n);
    static size_t           length(const char_type* s);
    static const char_type* find(const char_type* s, size_t n, const char_type& a);
    static char_type*       move(char_type* s1, const char_type* s2, size_t n);
    static char_type*       copy(char_type* s1, const char_type* s2, size_t n);
    static char_type*       assign(char_type* s, size_t n, char_type a);

    static constexpr int_type  not_eof(int_type c) noexcept;
    static constexpr char_type to_char_type(int_type c) noexcept;
    static constexpr int_type  to_int_type(char_type c) noexcept;
    static constexpr bool      eq_int_type(int_type c1, int_type c2) noexcept;
    static constexpr int_type  eof() noexcept;
};

template <> struct char_traits<char>;
template <> struct char_traits<wchar_t>;

template<class charT, class traits = char_traits<charT>, class Allocator = allocator<charT> >
class basic_string
{
public:
// types:
    typedef traits traits_type;
    typedef typename traits_type::char_type value_type;
    typedef Allocator allocator_type;
    typedef typename allocator_type::size_type size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef implementation-defined iterator;
    typedef implementation-defined const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    static const size_type npos = -1;

    basic_string()
        noexcept(is_nothrow_default_constructible<allocator_type>::value);
    explicit basic_string(const allocator_type& a);
    basic_string(const basic_string& str);
    basic_string(basic_string&& str)
        noexcept(is_nothrow_move_constructible<allocator_type>::value);
    basic_string(const basic_string& str, size_type pos, size_type n = npos,
                 const allocator_type& a = allocator_type());
    basic_string(const_pointer s, const allocator_type& a = allocator_type());
    basic_string(const_pointer s, size_type n, const allocator_type& a = allocator_type());
    basic_string(size_type n, value_type c, const allocator_type& a = allocator_type());
    template<class InputIterator>
        basic_string(InputIterator begin, InputIterator end,
                     const allocator_type& a = allocator_type());
    basic_string(initializer_list<value_type>, const Allocator& = Allocator());
    basic_string(const basic_string&, const Allocator&);
    basic_string(basic_string&&, const Allocator&);

    ~basic_string();

    basic_string& operator=(const basic_string& str);
    basic_string& operator=(basic_string&& str)
        noexcept(
             allocator_type::propagate_on_container_move_assignment::value &&
             is_nothrow_move_assignable<allocator_type>::value);
    basic_string& operator=(const_pointer s);
    basic_string& operator=(value_type c);
    basic_string& operator=(initializer_list<value_type>);

    iterator       begin() noexcept;
    const_iterator begin() const noexcept;
    iterator       end() noexcept;
    const_iterator end() const noexcept;

    reverse_iterator       rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    reverse_iterator       rend() noexcept;
    const_reverse_iterator rend() const noexcept;

    const_iterator         cbegin() const noexcept;
    const_iterator         cend() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;

    size_type size() const noexcept;
    size_type length() const noexcept;
    size_type max_size() const noexcept;
    size_type capacity() const noexcept;

    void resize(size_type n, value_type c);
    void resize(size_type n);

    void reserve(size_type res_arg = 0);
    void shrink_to_fit();
    void clear() noexcept;
    bool empty() const noexcept;

    const_reference operator[](size_type pos) const;
    reference       operator[](size_type pos);

    const_reference at(size_type n) const;
    reference       at(size_type n);

    basic_string& operator+=(const basic_string& str);
    basic_string& operator+=(const_pointer s);
    basic_string& operator+=(value_type c);
    basic_string& operator+=(initializer_list<value_type>);

    basic_string& append(const basic_string& str);
    basic_string& append(const basic_string& str, size_type pos, size_type n);
    basic_string& append(const_pointer s, size_type n);
    basic_string& append(const_pointer s);
    basic_string& append(size_type n, value_type c);
    template<class InputIterator>
        basic_string& append(InputIterator first, InputIterator last);
    basic_string& append(initializer_list<value_type>);

    void push_back(value_type c);
    void pop_back();
    reference       front();
    const_reference front() const;
    reference       back();
    const_reference back() const;

    basic_string& assign(const basic_string& str);
    basic_string& assign(basic_string&& str);
    basic_string& assign(const basic_string& str, size_type pos, size_type n);
    basic_string& assign(const_pointer s, size_type n);
    basic_string& assign(const_pointer s);
    basic_string& assign(size_type n, value_type c);
    template<class InputIterator>
        basic_string& assign(InputIterator first, InputIterator last);
    basic_string& assign(initializer_list<value_type>);

    basic_string& insert(size_type pos1, const basic_string& str);
    basic_string& insert(size_type pos1, const basic_string& str,
                         size_type pos2, size_type n);
    basic_string& insert(size_type pos, const_pointer s, size_type n);
    basic_string& insert(size_type pos, const_pointer s);
    basic_string& insert(size_type pos, size_type n, value_type c);
    iterator      insert(const_iterator p, value_type c);
    iterator      insert(const_iterator p, size_type n, value_type c);
    template<class InputIterator>
        iterator insert(const_iterator p, InputIterator first, InputIterator last);
    iterator      insert(const_iterator p, initializer_list<value_type>);

    basic_string& erase(size_type pos = 0, size_type n = npos);
    iterator      erase(const_iterator position);
    iterator      erase(const_iterator first, const_iterator last);

    basic_string& replace(size_type pos1, size_type n1, const basic_string& str);
    basic_string& replace(size_type pos1, size_type n1, const basic_string& str,
                          size_type pos2, size_type n2);
    basic_string& replace(size_type pos, size_type n1, const_pointer s, size_type n2);
    basic_string& replace(size_type pos, size_type n1, const_pointer s);
    basic_string& replace(size_type pos, size_type n1, size_type n2, value_type c);
    basic_string& replace(const_iterator i1, const_iterator i2, const basic_string& str);
    basic_string& replace(const_iterator i1, const_iterator i2, const_pointer s, size_type n);
    basic_string& replace(const_iterator i1, const_iterator i2, const_pointer s);
    basic_string& replace(const_iterator i1, const_iterator i2, size_type n, value_type c);
    template<class InputIterator>
        basic_string& replace(const_iterator i1, const_iterator i2, InputIterator j1, InputIterator j2);
    basic_string& replace(const_iterator i1, const_iterator i2, initializer_list<value_type>);

    size_type copy(pointer s, size_type n, size_type pos = 0) const;
    basic_string substr(size_type pos = 0, size_type n = npos) const;

    void swap(basic_string& str)
        noexcept(!allocator_type::propagate_on_container_swap::value ||
                 __is_nothrow_swappable<allocator_type>::value)

    const_pointer c_str() const noexcept;
    const_pointer data() const noexcept;

    allocator_type get_allocator() const noexcept;

    size_type find(const basic_string& str, size_type pos = 0) const noexcept;
    size_type find(const_pointer s, size_type pos, size_type n) const noexcept;
    size_type find(const_pointer s, size_type pos = 0) const noexcept;
    size_type find(value_type c, size_type pos = 0) const noexcept;

    size_type rfind(const basic_string& str, size_type pos = npos) const noexcept;
    size_type rfind(const_pointer s, size_type pos, size_type n) const noexcept;
    size_type rfind(const_pointer s, size_type pos = npos) const noexcept;
    size_type rfind(value_type c, size_type pos = npos) const noexcept;

    size_type find_first_of(const basic_string& str, size_type pos = 0) const noexcept;
    size_type find_first_of(const_pointer s, size_type pos, size_type n) const noexcept;
    size_type find_first_of(const_pointer s, size_type pos = 0) const noexcept;
    size_type find_first_of(value_type c, size_type pos = 0) const noexcept;

    size_type find_last_of(const basic_string& str, size_type pos = npos) const noexcept;
    size_type find_last_of(const_pointer s, size_type pos, size_type n) const noexcept;
    size_type find_last_of(const_pointer s, size_type pos = npos) const noexcept;
    size_type find_last_of(value_type c, size_type pos = npos) const noexcept;

    size_type find_first_not_of(const basic_string& str, size_type pos = 0) const noexcept;
    size_type find_first_not_of(const_pointer s, size_type pos, size_type n) const noexcept;
    size_type find_first_not_of(const_pointer s, size_type pos = 0) const noexcept;
    size_type find_first_not_of(value_type c, size_type pos = 0) const noexcept;

    size_type find_last_not_of(const basic_string& str, size_type pos = npos) const noexcept;
    size_type find_last_not_of(const_pointer s, size_type pos, size_type n) const noexcept;
    size_type find_last_not_of(const_pointer s, size_type pos = npos) const noexcept;
    size_type find_last_not_of(value_type c, size_type pos = npos) const noexcept;

    int compare(const basic_string& str) const noexcept;
    int compare(size_type pos1, size_type n1, const basic_string& str) const;
    int compare(size_type pos1, size_type n1, const basic_string& str,
                size_type pos2, size_type n2) const;
    int compare(const_pointer s) const noexcept;
    int compare(size_type pos1, size_type n1, const_pointer s) const;
    int compare(size_type pos1, size_type n1, const_pointer s, size_type n2) const;

    bool __invariants() const;
};

template<class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>
operator+(const basic_string<charT, traits, Allocator>& lhs,
          const basic_string<charT, traits, Allocator>& rhs);

template<class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>
operator+(const charT* lhs , const basic_string<charT,traits,Allocator>&rhs);

template<class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>
operator+(charT lhs, const basic_string<charT,traits,Allocator>& rhs);

template<class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>
operator+(const basic_string<charT, traits, Allocator>& lhs, const charT* rhs);

template<class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>
operator+(const basic_string<charT, traits, Allocator>& lhs, charT rhs);

template<class charT, class traits, class Allocator>
bool operator==(const basic_string<charT, traits, Allocator>& lhs,
                const basic_string<charT, traits, Allocator>& rhs) noexcept;

template<class charT, class traits, class Allocator>
bool operator==(const charT* lhs, const basic_string<charT, traits, Allocator>& rhs) noexcept;

template<class charT, class traits, class Allocator>
bool operator==(const basic_string<charT,traits,Allocator>& lhs, const charT* rhs) noexcept;

template<class charT, class traits, class Allocator>
bool operator!=(const basic_string<charT,traits,Allocator>& lhs,
                const basic_string<charT, traits, Allocator>& rhs) noexcept;

template<class charT, class traits, class Allocator>
bool operator!=(const charT* lhs, const basic_string<charT, traits, Allocator>& rhs) noexcept;

template<class charT, class traits, class Allocator>
bool operator!=(const basic_string<charT, traits, Allocator>& lhs, const charT* rhs) noexcept;

template<class charT, class traits, class Allocator>
bool operator< (const basic_string<charT, traits, Allocator>& lhs,
                const basic_string<charT, traits, Allocator>& rhs) noexcept;

template<class charT, class traits, class Allocator>
bool operator< (const basic_string<charT, traits, Allocator>& lhs, const charT* rhs) noexcept;

template<class charT, class traits, class Allocator>
bool operator< (const charT* lhs, const basic_string<charT, traits, Allocator>& rhs) noexcept;

template<class charT, class traits, class Allocator>
bool operator> (const basic_string<charT, traits, Allocator>& lhs,
                const basic_string<charT, traits, Allocator>& rhs) noexcept;

template<class charT, class traits, class Allocator>
bool operator> (const basic_string<charT, traits, Allocator>& lhs, const charT* rhs) noexcept;

template<class charT, class traits, class Allocator>
bool operator> (const charT* lhs, const basic_string<charT, traits, Allocator>& rhs) noexcept;

template<class charT, class traits, class Allocator>
bool operator<=(const basic_string<charT, traits, Allocator>& lhs,
                const basic_string<charT, traits, Allocator>& rhs) noexcept;

template<class charT, class traits, class Allocator>
bool operator<=(const basic_string<charT, traits, Allocator>& lhs, const charT* rhs) noexcept;

template<class charT, class traits, class Allocator>
bool operator<=(const charT* lhs, const basic_string<charT, traits, Allocator>& rhs) noexcept;

template<class charT, class traits, class Allocator>
bool operator>=(const basic_string<charT, traits, Allocator>& lhs,
                const basic_string<charT, traits, Allocator>& rhs) noexcept;

template<class charT, class traits, class Allocator>
bool operator>=(const basic_string<charT, traits, Allocator>& lhs, const charT* rhs) noexcept;

template<class charT, class traits, class Allocator>
bool operator>=(const charT* lhs, const basic_string<charT, traits, Allocator>& rhs) noexcept;

template<class charT, class traits, class Allocator>
void swap(basic_string<charT, traits, Allocator>& lhs,
          basic_string<charT, traits, Allocator>& rhs)
            noexcept(noexcept(lhs.swap(rhs)));

template<class charT, class traits, class Allocator>
basic_istream<charT, traits>&
operator>>(basic_istream<charT, traits>& is, basic_string<charT, traits, Allocator>& str);

template<class charT, class traits, class Allocator>
basic_ostream<charT, traits>&
operator<<(basic_ostream<charT, traits>& os, const basic_string<charT, traits, Allocator>& str);

template<class charT, class traits, class Allocator>
basic_istream<charT, traits>&
getline(basic_istream<charT, traits>& is, basic_string<charT, traits, Allocator>& str,
        charT delim);

template<class charT, class traits, class Allocator>
basic_istream<charT, traits>&
getline(basic_istream<charT, traits>& is, basic_string<charT, traits, Allocator>& str);

typedef basic_string<char>    string;
typedef basic_string<wchar_t> wstring;
typedef basic_string<char16_t> u16string;
typedef basic_string<char32_t> u32string;

int                stoi  (const string& str, size_t* idx = 0, int base = 10);
long               stol  (const string& str, size_t* idx = 0, int base = 10);
unsigned long      stoul (const string& str, size_t* idx = 0, int base = 10);
long long          stoll (const string& str, size_t* idx = 0, int base = 10);
unsigned long long stoull(const string& str, size_t* idx = 0, int base = 10);

float       stof (const string& str, size_t* idx = 0);
double      stod (const string& str, size_t* idx = 0);
long double stold(const string& str, size_t* idx = 0);

string to_string(int val);
string to_string(unsigned val);
string to_string(long val);
string to_string(unsigned long val);
string to_string(long long val);
string to_string(unsigned long long val);
string to_string(float val);
string to_string(double val);
string to_string(long double val);

int                stoi  (const wstring& str, size_t* idx = 0, int base = 10);
long               stol  (const wstring& str, size_t* idx = 0, int base = 10);
unsigned long      stoul (const wstring& str, size_t* idx = 0, int base = 10);
long long          stoll (const wstring& str, size_t* idx = 0, int base = 10);
unsigned long long stoull(const wstring& str, size_t* idx = 0, int base = 10);

float       stof (const wstring& str, size_t* idx = 0);
double      stod (const wstring& str, size_t* idx = 0);
long double stold(const wstring& str, size_t* idx = 0);

wstring to_wstring(int val);
wstring to_wstring(unsigned val);
wstring to_wstring(long val);
wstring to_wstring(unsigned long val);
wstring to_wstring(long long val);
wstring to_wstring(unsigned long long val);
wstring to_wstring(float val);
wstring to_wstring(double val);
wstring to_wstring(long double val);

template <> struct hash<string>;
template <> struct hash<u16string>;
template <> struct hash<u32string>;
template <> struct hash<wstring>;

}  // std

*/

#if defined(__MICRO_OS_PLUS_PLUS__)
#include "portable/language/cpp/include/__config.h"
#include "portable/language/cpp/include/iosfwd"
#include "portable/language/cpp/include/cstring"
#include "portable/language/cpp/include/cstdio"  // For EOF.
#include "portable/language/cpp/include/cwchar"
#include "portable/language/cpp/include/algorithm"
#include "portable/language/cpp/include/iterator"
#include "portable/language/cpp/include/utility"
#include "portable/language/cpp/include/memory"
#include "portable/language/cpp/include/stdexcept"
#include "portable/language/cpp/include/type_traits"
#include "portable/language/cpp/include/initializer_list"
#include "portable/language/cpp/include/__functional_base.h"
#ifndef _LIBCPP_HAS_NO_UNICODE_CHARS
#include "portable/language/cpp/include/cstdint"
#endif
#if defined(_LIBCPP_NO_EXCEPTIONS) || defined(_LIBCPP_DEBUG)
#include "portable/language/cpp/include/cassert"
#endif

#include "portable/language/cpp/include/__undef_min_max.h"

#else
#include <__config>
#include <iosfwd>
#include <cstring>
#include <cstdio>  // For EOF.
#include <cwchar>
#include <algorithm>
#include <iterator>
#include <utility>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <initializer_list>
#include <__functional_base>
#ifndef _LIBCPP_HAS_NO_UNICODE_CHARS
#include <cstdint>
#endif
#if defined(_LIBCPP_NO_EXCEPTIONS) || defined(_LIBCPP_DEBUG)
#include <cassert>
#endif

#include <__undef_min_max>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

// fpos

template <class _StateT>
class _LIBCPP_VISIBLE fpos
{
private:
    _StateT __st_;
    streamoff __off_;
public:
    _LIBCPP_INLINE_VISIBILITY fpos(streamoff __off = streamoff()) : __st_(), __off_(__off) {}

    _LIBCPP_INLINE_VISIBILITY operator streamoff() const {return __off_;}

    _LIBCPP_INLINE_VISIBILITY _StateT state() const {return __st_;}
    _LIBCPP_INLINE_VISIBILITY void state(_StateT __st) {__st_ = __st;}

    _LIBCPP_INLINE_VISIBILITY fpos& operator+=(streamoff __off) {__off_ += __off; return *this;}
    _LIBCPP_INLINE_VISIBILITY fpos  operator+ (streamoff __off) const {fpos __t(*this); __t += __off; return __t;}
    _LIBCPP_INLINE_VISIBILITY fpos& operator-=(streamoff __off) {__off_ -= __off; return *this;}
    _LIBCPP_INLINE_VISIBILITY fpos  operator- (streamoff __off) const {fpos __t(*this); __t -= __off; return __t;}
};

template <class _StateT>
inline _LIBCPP_INLINE_VISIBILITY
streamoff operator-(const fpos<_StateT>& __x, const fpos<_StateT>& __y)
    {return streamoff(__x) - streamoff(__y);}

template <class _StateT>
inline _LIBCPP_INLINE_VISIBILITY
bool operator==(const fpos<_StateT>& __x, const fpos<_StateT>& __y)
    {return streamoff(__x) == streamoff(__y);}

template <class _StateT>
inline _LIBCPP_INLINE_VISIBILITY
bool operator!=(const fpos<_StateT>& __x, const fpos<_StateT>& __y)
    {return streamoff(__x) != streamoff(__y);}

// char_traits

template <class _CharT>
struct _LIBCPP_VISIBLE char_traits
{
    typedef _CharT    char_type;
    typedef int       int_type;
    typedef streamoff off_type;
    typedef streampos pos_type;
    typedef mbstate_t state_type;

    _LIBCPP_INLINE_VISIBILITY
    static void assign(char_type& __c1, const char_type& __c2) _NOEXCEPT
        {__c1 = __c2;}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR bool eq(char_type __c1, char_type __c2) _NOEXCEPT
        {return __c1 == __c2;}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR bool lt(char_type __c1, char_type __c2) _NOEXCEPT
        {return __c1 < __c2;}

    static int              compare(const char_type* __s1, const char_type* __s2, size_t __n);
    static size_t           length(const char_type* __s);
    static const char_type* find(const char_type* __s, size_t __n, const char_type& __a);
    static char_type*       move(char_type* __s1, const char_type* __s2, size_t __n);
    static char_type*       copy(char_type* __s1, const char_type* __s2, size_t __n);
    static char_type*       assign(char_type* __s, size_t __n, char_type __a);

    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR int_type  not_eof(int_type __c) _NOEXCEPT
        {return eq_int_type(__c, eof()) ? ~eof() : __c;}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR char_type to_char_type(int_type __c) _NOEXCEPT
        {return char_type(__c);}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR int_type  to_int_type(char_type __c) _NOEXCEPT
        {return int_type(__c);}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR bool      eq_int_type(int_type __c1, int_type __c2) _NOEXCEPT
        {return __c1 == __c2;}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR int_type  eof() _NOEXCEPT
        {return int_type(EOF);}
};

template <class _CharT>
int
char_traits<_CharT>::compare(const char_type* __s1, const char_type* __s2, size_t __n)
{
    for (; __n; --__n, ++__s1, ++__s2)
    {
        if (lt(*__s1, *__s2))
            return -1;
        if (lt(*__s2, *__s1))
            return 1;
    }
    return 0;
}

template <class _CharT>
inline _LIBCPP_INLINE_VISIBILITY
size_t
char_traits<_CharT>::length(const char_type* __s)
{
    size_t __len = 0;
    for (; !eq(*__s, char_type(0)); ++__s)
        ++__len;
    return __len;
}

template <class _CharT>
inline _LIBCPP_INLINE_VISIBILITY
const _CharT*
char_traits<_CharT>::find(const char_type* __s, size_t __n, const char_type& __a)
{
    for (; __n; --__n)
    {
        if (eq(*__s, __a))
            return __s;
        ++__s;
    }
    return 0;
}

template <class _CharT>
_CharT*
char_traits<_CharT>::move(char_type* __s1, const char_type* __s2, size_t __n)
{
    char_type* __r = __s1;
    if (__s1 < __s2)
    {
        for (; __n; --__n, ++__s1, ++__s2)
            assign(*__s1, *__s2);
    }
    else if (__s2 < __s1)
    {
        __s1 += __n;
        __s2 += __n;
        for (; __n; --__n)
            assign(*--__s1, *--__s2);
    }
    return __r;
}

template <class _CharT>
inline _LIBCPP_INLINE_VISIBILITY
_CharT*
char_traits<_CharT>::copy(char_type* __s1, const char_type* __s2, size_t __n)
{
    char_type* __r = __s1;
    for (; __n; --__n, ++__s1, ++__s2)
        assign(*__s1, *__s2);
    return __r;
}

template <class _CharT>
inline _LIBCPP_INLINE_VISIBILITY
_CharT*
char_traits<_CharT>::assign(char_type* __s, size_t __n, char_type __a)
{
    char_type* __r = __s;
    for (; __n; --__n, ++__s)
        assign(*__s, __a);
    return __r;
}

// char_traits<char>

template <>
struct _LIBCPP_VISIBLE char_traits<char>
{
    typedef char      char_type;
    typedef int       int_type;
    typedef streamoff off_type;
    typedef streampos pos_type;
    typedef mbstate_t state_type;

    _LIBCPP_INLINE_VISIBILITY
    static void assign(char_type& __c1, const char_type& __c2) _NOEXCEPT
        {__c1 = __c2;}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR bool eq(char_type __c1, char_type __c2) _NOEXCEPT
            {return __c1 == __c2;}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR bool lt(char_type __c1, char_type __c2) _NOEXCEPT
        {return (unsigned char)__c1 < (unsigned char)__c2;}

    _LIBCPP_INLINE_VISIBILITY
    static int compare(const char_type* __s1, const char_type* __s2, size_t __n)
        {return memcmp(__s1, __s2, __n);}
    _LIBCPP_INLINE_VISIBILITY
    static size_t length(const char_type* __s) {return strlen(__s);}
    _LIBCPP_INLINE_VISIBILITY
    static const char_type* find(const char_type* __s, size_t __n, const char_type& __a)
        {return (const char_type*)memchr(__s, to_int_type(__a), __n);}
    _LIBCPP_INLINE_VISIBILITY
    static char_type* move(char_type* __s1, const char_type* __s2, size_t __n)
        {return (char_type*)memmove(__s1, __s2, __n);}
    _LIBCPP_INLINE_VISIBILITY
    static char_type* copy(char_type* __s1, const char_type* __s2, size_t __n)
        {return (char_type*)memcpy(__s1, __s2, __n);}
    _LIBCPP_INLINE_VISIBILITY
    static char_type* assign(char_type* __s, size_t __n, char_type __a)
        {return (char_type*)memset(__s, to_int_type(__a), __n);}

    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR int_type  not_eof(int_type __c) _NOEXCEPT
        {return eq_int_type(__c, eof()) ? ~eof() : __c;}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR char_type to_char_type(int_type __c) _NOEXCEPT
        {return char_type(__c);}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR int_type to_int_type(char_type __c) _NOEXCEPT
        {return int_type((unsigned char)__c);}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR bool eq_int_type(int_type __c1, int_type __c2) _NOEXCEPT
        {return __c1 == __c2;}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR int_type  eof() _NOEXCEPT
        {return int_type(EOF);}
};

// char_traits<wchar_t>

template <>
struct _LIBCPP_VISIBLE char_traits<wchar_t>
{
    typedef wchar_t   char_type;
    typedef wint_t    int_type;
    typedef streamoff off_type;
    typedef streampos pos_type;
    typedef mbstate_t state_type;

    _LIBCPP_INLINE_VISIBILITY
    static void assign(char_type& __c1, const char_type& __c2) _NOEXCEPT
        {__c1 = __c2;}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR bool eq(char_type __c1, char_type __c2) _NOEXCEPT
        {return __c1 == __c2;}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR bool lt(char_type __c1, char_type __c2) _NOEXCEPT
        {return __c1 < __c2;}

    _LIBCPP_INLINE_VISIBILITY
    static int compare(const char_type* __s1, const char_type* __s2, size_t __n)
        {return wmemcmp(__s1, __s2, __n);}
    _LIBCPP_INLINE_VISIBILITY
    static size_t length(const char_type* __s)
        {return wcslen(__s);}
    _LIBCPP_INLINE_VISIBILITY
    static const char_type* find(const char_type* __s, size_t __n, const char_type& __a)
        {return (const char_type*)wmemchr(__s, __a, __n);}
    _LIBCPP_INLINE_VISIBILITY
    static char_type* move(char_type* __s1, const char_type* __s2, size_t __n)
        {return (char_type*)wmemmove(__s1, __s2, __n);}
    _LIBCPP_INLINE_VISIBILITY
    static char_type* copy(char_type* __s1, const char_type* __s2, size_t __n)
        {return (char_type*)wmemcpy(__s1, __s2, __n);}
    _LIBCPP_INLINE_VISIBILITY
    static char_type* assign(char_type* __s, size_t __n, char_type __a)
        {return (char_type*)wmemset(__s, __a, __n);}

    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR int_type  not_eof(int_type __c) _NOEXCEPT
        {return eq_int_type(__c, eof()) ? ~eof() : __c;}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR char_type to_char_type(int_type __c) _NOEXCEPT
        {return char_type(__c);}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR int_type to_int_type(char_type __c) _NOEXCEPT
        {return int_type(__c);}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR bool eq_int_type(int_type __c1, int_type __c2) _NOEXCEPT
        {return __c1 == __c2;}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR int_type eof() _NOEXCEPT
        {return int_type(WEOF);}
};

#ifndef _LIBCPP_HAS_NO_UNICODE_CHARS

template <>
struct _LIBCPP_VISIBLE char_traits<char16_t>
{
    typedef char16_t       char_type;
    typedef uint_least16_t int_type;
    typedef streamoff      off_type;
    typedef u16streampos   pos_type;
    typedef mbstate_t      state_type;

    _LIBCPP_INLINE_VISIBILITY
    static void assign(char_type& __c1, const char_type& __c2) _NOEXCEPT
        {__c1 = __c2;}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR bool eq(char_type __c1, char_type __c2) _NOEXCEPT
        {return __c1 == __c2;}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR bool lt(char_type __c1, char_type __c2) _NOEXCEPT
        {return __c1 < __c2;}

    static int              compare(const char_type* __s1, const char_type* __s2, size_t __n);
    static size_t           length(const char_type* __s);
    static const char_type* find(const char_type* __s, size_t __n, const char_type& __a);
    static char_type*       move(char_type* __s1, const char_type* __s2, size_t __n);
    static char_type*       copy(char_type* __s1, const char_type* __s2, size_t __n);
    static char_type*       assign(char_type* __s, size_t __n, char_type __a);

    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR int_type  not_eof(int_type __c) _NOEXCEPT
        {return eq_int_type(__c, eof()) ? ~eof() : __c;}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR char_type to_char_type(int_type __c) _NOEXCEPT
        {return char_type(__c);}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR int_type to_int_type(char_type __c) _NOEXCEPT
        {return int_type(__c);}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR bool eq_int_type(int_type __c1, int_type __c2) _NOEXCEPT
        {return __c1 == __c2;}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR int_type eof() _NOEXCEPT
        {return int_type(0xDFFF);}
};

inline _LIBCPP_INLINE_VISIBILITY
int
char_traits<char16_t>::compare(const char_type* __s1, const char_type* __s2, size_t __n)
{
    for (; __n; --__n, ++__s1, ++__s2)
    {
        if (lt(*__s1, *__s2))
            return -1;
        if (lt(*__s2, *__s1))
            return 1;
    }
    return 0;
}

inline _LIBCPP_INLINE_VISIBILITY
size_t
char_traits<char16_t>::length(const char_type* __s)
{
    size_t __len = 0;
    for (; !eq(*__s, char_type(0)); ++__s)
        ++__len;
    return __len;
}

inline _LIBCPP_INLINE_VISIBILITY
const char16_t*
char_traits<char16_t>::find(const char_type* __s, size_t __n, const char_type& __a)
{
    for (; __n; --__n)
    {
        if (eq(*__s, __a))
            return __s;
        ++__s;
    }
    return 0;
}

inline _LIBCPP_INLINE_VISIBILITY
char16_t*
char_traits<char16_t>::move(char_type* __s1, const char_type* __s2, size_t __n)
{
    char_type* __r = __s1;
    if (__s1 < __s2)
    {
        for (; __n; --__n, ++__s1, ++__s2)
            assign(*__s1, *__s2);
    }
    else if (__s2 < __s1)
    {
        __s1 += __n;
        __s2 += __n;
        for (; __n; --__n)
            assign(*--__s1, *--__s2);
    }
    return __r;
}

inline _LIBCPP_INLINE_VISIBILITY
char16_t*
char_traits<char16_t>::copy(char_type* __s1, const char_type* __s2, size_t __n)
{
    char_type* __r = __s1;
    for (; __n; --__n, ++__s1, ++__s2)
        assign(*__s1, *__s2);
    return __r;
}

inline _LIBCPP_INLINE_VISIBILITY
char16_t*
char_traits<char16_t>::assign(char_type* __s, size_t __n, char_type __a)
{
    char_type* __r = __s;
    for (; __n; --__n, ++__s)
        assign(*__s, __a);
    return __r;
}

template <>
struct _LIBCPP_VISIBLE char_traits<char32_t>
{
    typedef char32_t       char_type;
    typedef uint_least32_t int_type;
    typedef streamoff      off_type;
    typedef u32streampos   pos_type;
    typedef mbstate_t      state_type;

    _LIBCPP_INLINE_VISIBILITY
    static void assign(char_type& __c1, const char_type& __c2) _NOEXCEPT
        {__c1 = __c2;}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR bool eq(char_type __c1, char_type __c2) _NOEXCEPT
        {return __c1 == __c2;}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR bool lt(char_type __c1, char_type __c2) _NOEXCEPT
        {return __c1 < __c2;}

    static int              compare(const char_type* __s1, const char_type* __s2, size_t __n);
    static size_t           length(const char_type* __s);
    static const char_type* find(const char_type* __s, size_t __n, const char_type& __a);
    static char_type*       move(char_type* __s1, const char_type* __s2, size_t __n);
    static char_type*       copy(char_type* __s1, const char_type* __s2, size_t __n);
    static char_type*       assign(char_type* __s, size_t __n, char_type __a);

    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR int_type  not_eof(int_type __c) _NOEXCEPT
        {return eq_int_type(__c, eof()) ? ~eof() : __c;}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR char_type to_char_type(int_type __c) _NOEXCEPT
        {return char_type(__c);}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR int_type to_int_type(char_type __c) _NOEXCEPT
        {return int_type(__c);}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR bool eq_int_type(int_type __c1, int_type __c2) _NOEXCEPT
        {return __c1 == __c2;}
    _LIBCPP_INLINE_VISIBILITY
    static _LIBCPP_CONSTEXPR int_type eof() _NOEXCEPT
        {return int_type(0xFFFFFFFF);}
};

inline _LIBCPP_INLINE_VISIBILITY
int
char_traits<char32_t>::compare(const char_type* __s1, const char_type* __s2, size_t __n)
{
    for (; __n; --__n, ++__s1, ++__s2)
    {
        if (lt(*__s1, *__s2))
            return -1;
        if (lt(*__s2, *__s1))
            return 1;
    }
    return 0;
}

inline _LIBCPP_INLINE_VISIBILITY
size_t
char_traits<char32_t>::length(const char_type* __s)
{
    size_t __len = 0;
    for (; !eq(*__s, char_type(0)); ++__s)
        ++__len;
    return __len;
}

inline _LIBCPP_INLINE_VISIBILITY
const char32_t*
char_traits<char32_t>::find(const char_type* __s, size_t __n, const char_type& __a)
{
    for (; __n; --__n)
    {
        if (eq(*__s, __a))
            return __s;
        ++__s;
    }
    return 0;
}

inline _LIBCPP_INLINE_VISIBILITY
char32_t*
char_traits<char32_t>::move(char_type* __s1, const char_type* __s2, size_t __n)
{
    char_type* __r = __s1;
    if (__s1 < __s2)
    {
        for (; __n; --__n, ++__s1, ++__s2)
            assign(*__s1, *__s2);
    }
    else if (__s2 < __s1)
    {
        __s1 += __n;
        __s2 += __n;
        for (; __n; --__n)
            assign(*--__s1, *--__s2);
    }
    return __r;
}

inline _LIBCPP_INLINE_VISIBILITY
char32_t*
char_traits<char32_t>::copy(char_type* __s1, const char_type* __s2, size_t __n)
{
    char_type* __r = __s1;
    for (; __n; --__n, ++__s1, ++__s2)
        assign(*__s1, *__s2);
    return __r;
}

inline _LIBCPP_INLINE_VISIBILITY
char32_t*
char_traits<char32_t>::assign(char_type* __s, size_t __n, char_type __a)
{
    char_type* __r = __s;
    for (; __n; --__n, ++__s)
        assign(*__s, __a);
    return __r;
}

#endif  // _LIBCPP_HAS_NO_UNICODE_CHARS

// basic_string

template<class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>
operator+(const basic_string<_CharT, _Traits, _Allocator>& __x,
          const basic_string<_CharT, _Traits, _Allocator>& __y);

template<class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>
operator+(const _CharT* __x, const basic_string<_CharT,_Traits,_Allocator>& __y);

template<class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>
operator+(_CharT __x, const basic_string<_CharT,_Traits,_Allocator>& __y);

template<class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>
operator+(const basic_string<_CharT, _Traits, _Allocator>& __x, const _CharT* __y);

template<class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>
operator+(const basic_string<_CharT, _Traits, _Allocator>& __x, _CharT __y);

template <bool>
class __basic_string_common
{
protected:
    void __throw_length_error() const;
    void __throw_out_of_range() const;
};

template <bool __b>
void
__basic_string_common<__b>::__throw_length_error() const
{
#ifndef _LIBCPP_NO_EXCEPTIONS
    throw length_error("basic_string");
#else
    assert(!"basic_string length_error");
#endif
}

template <bool __b>
void
__basic_string_common<__b>::__throw_out_of_range() const
{
#ifndef _LIBCPP_NO_EXCEPTIONS
    throw out_of_range("basic_string");
#else
    assert(!"basic_string out_of_range");
#endif
}

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4231 )
#endif // _MSC_VER
_LIBCPP_EXTERN_TEMPLATE(class __basic_string_common<true>)
#ifdef _MSC_VER
#pragma warning( pop )
#endif // _MSC_VER

template<class _CharT, class _Traits, class _Allocator>
class _LIBCPP_VISIBLE basic_string
    : private __basic_string_common<true>
{
public:
    typedef basic_string                                 __self;
    typedef _Traits                                      traits_type;
    typedef typename traits_type::char_type              value_type;
    typedef _Allocator                                   allocator_type;
    typedef allocator_traits<allocator_type>             __alloc_traits;
    typedef typename __alloc_traits::size_type           size_type;
    typedef typename __alloc_traits::difference_type     difference_type;
    typedef value_type&                                  reference;
    typedef const value_type&                            const_reference;
    typedef typename __alloc_traits::pointer             pointer;
    typedef typename __alloc_traits::const_pointer       const_pointer;
#ifdef _LIBCPP_DEBUG
    typedef __debug_iter<basic_string, pointer>          iterator;
    typedef __debug_iter<basic_string, const_pointer>    const_iterator;

    friend class __debug_iter<basic_string, pointer>;
    friend class __debug_iter<basic_string, const_pointer>;
#elif defined(_LIBCPP_RAW_ITERATORS)
    typedef pointer                                      iterator;
    typedef const_pointer                                const_iterator;
#else  // defined(_LIBCPP_RAW_ITERATORS)
    typedef __wrap_iter<pointer>                         iterator;
    typedef __wrap_iter<const_pointer>                   const_iterator;
#endif  // defined(_LIBCPP_RAW_ITERATORS)
    typedef _VSTD::reverse_iterator<iterator>             reverse_iterator;
    typedef _VSTD::reverse_iterator<const_iterator>       const_reverse_iterator;

private:
    struct __long
    {
        size_type __cap_;
        size_type __size_;
        pointer   __data_;
    };

#if _LIBCPP_BIG_ENDIAN
    enum {__short_mask = 0x80};
    enum {__long_mask  = ~(size_type(~0) >> 1)};
#else  // _LIBCPP_BIG_ENDIAN
    enum {__short_mask = 0x01};
    enum {__long_mask  = 0x1ul};
#endif  // _LIBCPP_BIG_ENDIAN

    enum {__mask = size_type(~0) >> 1};

    enum {__min_cap = (sizeof(__long) - 1)/sizeof(value_type) > 2 ?
                      (sizeof(__long) - 1)/sizeof(value_type) : 2};

    struct __short
    {
        union
        {
            unsigned char __size_;
            value_type __lx;
        };
        value_type __data_[__min_cap];
    };

    union __lx{__long __lx; __short __lxx;};

    enum {__n_words = sizeof(__lx) / sizeof(size_type)};

    struct __raw
    {
        size_type __words[__n_words];
    };

    struct __rep
    {
        union
        {
            __long  __l;
            __short __s;
            __raw   __r;
        };
    };

    __compressed_pair<__rep, allocator_type> __r_;

#ifdef _LIBCPP_DEBUG

    pair<iterator*, const_iterator*> __iterator_list_;

    _LIBCPP_INLINE_VISIBILITY iterator*&       __get_iterator_list(iterator*)       {return __iterator_list_.first;}
    _LIBCPP_INLINE_VISIBILITY const_iterator*& __get_iterator_list(const_iterator*) {return __iterator_list_.second;}

#endif  // _LIBCPP_DEBUG

public:
    static const size_type npos = -1;

    _LIBCPP_INLINE_VISIBILITY basic_string()
        _NOEXCEPT_(is_nothrow_default_constructible<allocator_type>::value);
    _LIBCPP_INLINE_VISIBILITY explicit basic_string(const allocator_type& __a);
    basic_string(const basic_string& __str);
    basic_string(const basic_string& __str, const allocator_type& __a);
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
    _LIBCPP_INLINE_VISIBILITY
    basic_string(basic_string&& __str)
        _NOEXCEPT_(is_nothrow_move_constructible<allocator_type>::value);
    _LIBCPP_INLINE_VISIBILITY
    basic_string(basic_string&& __str, const allocator_type& __a);
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
    _LIBCPP_INLINE_VISIBILITY basic_string(const_pointer __s);
    _LIBCPP_INLINE_VISIBILITY
    basic_string(const_pointer __s, const allocator_type& __a);
    _LIBCPP_INLINE_VISIBILITY
    basic_string(const_pointer __s, size_type __n);
    _LIBCPP_INLINE_VISIBILITY
    basic_string(const_pointer __s, size_type __n, const allocator_type& __a);
    _LIBCPP_INLINE_VISIBILITY
    basic_string(size_type __n, value_type __c);
    _LIBCPP_INLINE_VISIBILITY
    basic_string(size_type __n, value_type __c, const allocator_type& __a);
    basic_string(const basic_string& __str, size_type __pos, size_type __n = npos,
                 const allocator_type& __a = allocator_type());
    template<class _InputIterator>
        _LIBCPP_INLINE_VISIBILITY
        basic_string(_InputIterator __first, _InputIterator __last);
    template<class _InputIterator>
        _LIBCPP_INLINE_VISIBILITY
        basic_string(_InputIterator __first, _InputIterator __last, const allocator_type& __a);
#ifndef _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS
    _LIBCPP_INLINE_VISIBILITY
    basic_string(initializer_list<value_type> __il);
    _LIBCPP_INLINE_VISIBILITY
    basic_string(initializer_list<value_type> __il, const allocator_type& __a);
#endif  // _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS

    ~basic_string();

    basic_string& operator=(const basic_string& __str);
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
    _LIBCPP_INLINE_VISIBILITY
    basic_string& operator=(basic_string&& __str)
        _NOEXCEPT_(__alloc_traits::propagate_on_container_move_assignment::value &&
                   is_nothrow_move_assignable<allocator_type>::value);
#endif
    _LIBCPP_INLINE_VISIBILITY basic_string& operator=(const_pointer __s) {return assign(__s);}
    basic_string& operator=(value_type __c);
#ifndef _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS
    _LIBCPP_INLINE_VISIBILITY
    basic_string& operator=(initializer_list<value_type> __il) {return assign(__il.begin(), __il.size());}
#endif  // _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS

#ifndef _LIBCPP_DEBUG
    _LIBCPP_INLINE_VISIBILITY
    iterator begin() _NOEXCEPT
        {return iterator(__get_pointer());}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator begin() const _NOEXCEPT
        {return const_iterator(data());}
    _LIBCPP_INLINE_VISIBILITY
    iterator end() _NOEXCEPT
        {return iterator(__get_pointer() + size());}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator end() const _NOEXCEPT
        {return const_iterator(data() + size());}
#else  // _LIBCPP_DEBUG
    _LIBCPP_INLINE_VISIBILITY iterator       begin()       {return iterator(this, __get_pointer());}
    _LIBCPP_INLINE_VISIBILITY const_iterator begin() const {return const_iterator(this, data());}
    _LIBCPP_INLINE_VISIBILITY iterator       end()         {return iterator(this, __get_pointer() + size());}
    _LIBCPP_INLINE_VISIBILITY const_iterator end() const   {return const_iterator(this, data() + size());}
#endif  // _LIBCPP_DEBUG
    _LIBCPP_INLINE_VISIBILITY
    reverse_iterator rbegin() _NOEXCEPT
        {return reverse_iterator(end());}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator rbegin() const _NOEXCEPT
        {return const_reverse_iterator(end());}
    _LIBCPP_INLINE_VISIBILITY
    reverse_iterator rend() _NOEXCEPT
        {return reverse_iterator(begin());}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator rend() const _NOEXCEPT
        {return const_reverse_iterator(begin());}

    _LIBCPP_INLINE_VISIBILITY
    const_iterator cbegin() const _NOEXCEPT
        {return begin();}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator cend() const _NOEXCEPT
        {return end();}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator crbegin() const _NOEXCEPT
        {return rbegin();}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator crend() const _NOEXCEPT
        {return rend();}

    _LIBCPP_INLINE_VISIBILITY size_type size() const _NOEXCEPT
        {return __is_long() ? __get_long_size() : __get_short_size();}
    _LIBCPP_INLINE_VISIBILITY size_type length() const _NOEXCEPT {return size();}
    _LIBCPP_INLINE_VISIBILITY size_type max_size() const _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY size_type capacity() const _NOEXCEPT
        {return (__is_long() ? __get_long_cap() : __min_cap) - 1;}

    void resize(size_type __n, value_type __c);
    _LIBCPP_INLINE_VISIBILITY void resize(size_type __n) {resize(__n, value_type());}

    void reserve(size_type res_arg = 0);
    _LIBCPP_INLINE_VISIBILITY
    void shrink_to_fit() _NOEXCEPT {reserve();}
    _LIBCPP_INLINE_VISIBILITY
    void clear() _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY bool empty() const _NOEXCEPT {return size() == 0;}

    _LIBCPP_INLINE_VISIBILITY const_reference operator[](size_type __pos) const;
    _LIBCPP_INLINE_VISIBILITY reference       operator[](size_type __pos);

    const_reference at(size_type __n) const;
    reference       at(size_type __n);

    _LIBCPP_INLINE_VISIBILITY basic_string& operator+=(const basic_string& __str) {return append(__str);}
    _LIBCPP_INLINE_VISIBILITY basic_string& operator+=(const_pointer __s)         {return append(__s);}
    _LIBCPP_INLINE_VISIBILITY basic_string& operator+=(value_type __c)            {push_back(__c); return *this;}
#ifndef _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS
    _LIBCPP_INLINE_VISIBILITY basic_string& operator+=(initializer_list<value_type> __il) {return append(__il);}
#endif  // _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS

    _LIBCPP_INLINE_VISIBILITY
    basic_string& append(const basic_string& __str);
    basic_string& append(const basic_string& __str, size_type __pos, size_type __n);
    basic_string& append(const_pointer __s, size_type __n);
    basic_string& append(const_pointer __s);
    basic_string& append(size_type __n, value_type __c);
    template<class _InputIterator>
        typename enable_if
        <
             __is_input_iterator  <_InputIterator>::value &&
            !__is_forward_iterator<_InputIterator>::value,
            basic_string&
        >::type
        append(_InputIterator __first, _InputIterator __last);
    template<class _ForwardIterator>
        typename enable_if
        <
            __is_forward_iterator<_ForwardIterator>::value,
            basic_string&
        >::type
        append(_ForwardIterator __first, _ForwardIterator __last);
#ifndef _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS
    _LIBCPP_INLINE_VISIBILITY
    basic_string& append(initializer_list<value_type> __il) {return append(__il.begin(), __il.size());}
#endif  // _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS

    void push_back(value_type __c);
    _LIBCPP_INLINE_VISIBILITY
    void pop_back();
    _LIBCPP_INLINE_VISIBILITY reference       front();
    _LIBCPP_INLINE_VISIBILITY const_reference front() const;
    _LIBCPP_INLINE_VISIBILITY reference       back();
    _LIBCPP_INLINE_VISIBILITY const_reference back() const;

    _LIBCPP_INLINE_VISIBILITY
    basic_string& assign(const basic_string& __str);
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
    _LIBCPP_INLINE_VISIBILITY
    basic_string& assign(basic_string&& str)
        {*this = _VSTD::move(str); return *this;}
#endif
    basic_string& assign(const basic_string& __str, size_type __pos, size_type __n);
    basic_string& assign(const_pointer __s, size_type __n);
    basic_string& assign(const_pointer __s);
    basic_string& assign(size_type __n, value_type __c);
    template<class _InputIterator>
        typename enable_if
        <
             __is_input_iterator  <_InputIterator>::value &&
            !__is_forward_iterator<_InputIterator>::value,
            basic_string&
        >::type
        assign(_InputIterator __first, _InputIterator __last);
    template<class _ForwardIterator>
        typename enable_if
        <
            __is_forward_iterator<_ForwardIterator>::value,
            basic_string&
        >::type
        assign(_ForwardIterator __first, _ForwardIterator __last);
#ifndef _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS
    _LIBCPP_INLINE_VISIBILITY
    basic_string& assign(initializer_list<value_type> __il) {return assign(__il.begin(), __il.size());}
#endif  // _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS

    _LIBCPP_INLINE_VISIBILITY
    basic_string& insert(size_type __pos1, const basic_string& __str);
    basic_string& insert(size_type __pos1, const basic_string& __str, size_type __pos2, size_type __n);
    basic_string& insert(size_type __pos, const_pointer __s, size_type __n);
    basic_string& insert(size_type __pos, const_pointer __s);
    basic_string& insert(size_type __pos, size_type __n, value_type __c);
    iterator      insert(const_iterator __pos, value_type __c);
    _LIBCPP_INLINE_VISIBILITY
    iterator      insert(const_iterator __pos, size_type __n, value_type __c);
    template<class _InputIterator>
        typename enable_if
        <
             __is_input_iterator  <_InputIterator>::value &&
            !__is_forward_iterator<_InputIterator>::value,
            iterator
        >::type
        insert(const_iterator __pos, _InputIterator __first, _InputIterator __last);
    template<class _ForwardIterator>
        typename enable_if
        <
            __is_forward_iterator<_ForwardIterator>::value,
            iterator
        >::type
        insert(const_iterator __pos, _ForwardIterator __first, _ForwardIterator __last);
#ifndef _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS
    _LIBCPP_INLINE_VISIBILITY
    iterator insert(const_iterator __pos, initializer_list<value_type> __il)
                    {return insert(__pos, __il.begin(), __il.end());}
#endif  // _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS

    basic_string& erase(size_type __pos = 0, size_type __n = npos);
    _LIBCPP_INLINE_VISIBILITY
    iterator      erase(const_iterator __pos);
    _LIBCPP_INLINE_VISIBILITY
    iterator      erase(const_iterator __first, const_iterator __last);

    _LIBCPP_INLINE_VISIBILITY
    basic_string& replace(size_type __pos1, size_type __n1, const basic_string& __str);
    basic_string& replace(size_type __pos1, size_type __n1, const basic_string& __str, size_type __pos2, size_type __n2);
    basic_string& replace(size_type __pos, size_type __n1, const_pointer __s, size_type __n2);
    basic_string& replace(size_type __pos, size_type __n1, const_pointer __s);
    basic_string& replace(size_type __pos, size_type __n1, size_type __n2, value_type __c);
    _LIBCPP_INLINE_VISIBILITY
    basic_string& replace(const_iterator __i1, const_iterator __i2, const basic_string& __str);
    _LIBCPP_INLINE_VISIBILITY
    basic_string& replace(const_iterator __i1, const_iterator __i2, const_pointer __s, size_type __n);
    _LIBCPP_INLINE_VISIBILITY
    basic_string& replace(const_iterator __i1, const_iterator __i2, const_pointer __s);
    _LIBCPP_INLINE_VISIBILITY
    basic_string& replace(const_iterator __i1, const_iterator __i2, size_type __n, value_type __c);
    template<class _InputIterator>
        typename enable_if
        <
            __is_input_iterator<_InputIterator>::value,
            basic_string&
        >::type
        replace(const_iterator __i1, const_iterator __i2, _InputIterator __j1, _InputIterator __j2);
#ifndef _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS
    _LIBCPP_INLINE_VISIBILITY
    basic_string& replace(const_iterator __i1, const_iterator __i2, initializer_list<value_type> __il)
        {return replace(__i1, __i2, __il.begin(), __il.end());}
#endif  // _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS

    size_type copy(pointer __s, size_type __n, size_type __pos = 0) const;
    _LIBCPP_INLINE_VISIBILITY
    basic_string substr(size_type __pos = 0, size_type __n = npos) const;

    _LIBCPP_INLINE_VISIBILITY
    void swap(basic_string& __str)
        _NOEXCEPT_(!__alloc_traits::propagate_on_container_swap::value ||
                   __is_nothrow_swappable<allocator_type>::value);

    _LIBCPP_INLINE_VISIBILITY
    const_pointer c_str() const _NOEXCEPT {return data();}
    _LIBCPP_INLINE_VISIBILITY
    const_pointer data() const _NOEXCEPT  {return __get_pointer();}

    _LIBCPP_INLINE_VISIBILITY
    allocator_type get_allocator() const _NOEXCEPT {return __alloc();}

    _LIBCPP_INLINE_VISIBILITY
    size_type find(const basic_string& __str, size_type __pos = 0) const _NOEXCEPT;
    size_type find(const_pointer __s, size_type __pos, size_type __n) const _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY
    size_type find(const_pointer __s, size_type __pos = 0) const _NOEXCEPT;
    size_type find(value_type __c, size_type __pos = 0) const _NOEXCEPT;

    _LIBCPP_INLINE_VISIBILITY
    size_type rfind(const basic_string& __str, size_type __pos = npos) const _NOEXCEPT;
    size_type rfind(const_pointer __s, size_type __pos, size_type __n) const _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY
    size_type rfind(const_pointer __s, size_type __pos = npos) const _NOEXCEPT;
    size_type rfind(value_type __c, size_type __pos = npos) const _NOEXCEPT;

    _LIBCPP_INLINE_VISIBILITY
    size_type find_first_of(const basic_string& __str, size_type __pos = 0) const _NOEXCEPT;
    size_type find_first_of(const_pointer __s, size_type __pos, size_type __n) const _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY
    size_type find_first_of(const_pointer __s, size_type __pos = 0) const _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY
    size_type find_first_of(value_type __c, size_type __pos = 0) const _NOEXCEPT;

    _LIBCPP_INLINE_VISIBILITY
    size_type find_last_of(const basic_string& __str, size_type __pos = npos) const _NOEXCEPT;
    size_type find_last_of(const_pointer __s, size_type __pos, size_type __n) const _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY
    size_type find_last_of(const_pointer __s, size_type __pos = npos) const _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY
    size_type find_last_of(value_type __c, size_type __pos = npos) const _NOEXCEPT;

    _LIBCPP_INLINE_VISIBILITY
    size_type find_first_not_of(const basic_string& __str, size_type __pos = 0) const _NOEXCEPT;
    size_type find_first_not_of(const_pointer __s, size_type __pos, size_type __n) const _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY
    size_type find_first_not_of(const_pointer __s, size_type __pos = 0) const _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY
    size_type find_first_not_of(value_type __c, size_type __pos = 0) const _NOEXCEPT;

    _LIBCPP_INLINE_VISIBILITY
    size_type find_last_not_of(const basic_string& __str, size_type __pos = npos) const _NOEXCEPT;
    size_type find_last_not_of(const_pointer __s, size_type __pos, size_type __n) const _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY
    size_type find_last_not_of(const_pointer __s, size_type __pos = npos) const _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY
    size_type find_last_not_of(value_type __c, size_type __pos = npos) const _NOEXCEPT;

    _LIBCPP_INLINE_VISIBILITY
    int compare(const basic_string& __str) const _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY
    int compare(size_type __pos1, size_type __n1, const basic_string& __str) const;
    int compare(size_type __pos1, size_type __n1, const basic_string& __str, size_type __pos2, size_type __n2) const;
    int compare(const_pointer __s) const _NOEXCEPT;
    int compare(size_type __pos1, size_type __n1, const_pointer __s) const;
    int compare(size_type __pos1, size_type __n1, const_pointer __s, size_type __n2) const;

    _LIBCPP_INLINE_VISIBILITY bool __invariants() const;
private:
    _LIBCPP_INLINE_VISIBILITY
    allocator_type& __alloc() _NOEXCEPT
        {return __r_.second();}
    _LIBCPP_INLINE_VISIBILITY
    const allocator_type& __alloc() const _NOEXCEPT
        {return __r_.second();}

    _LIBCPP_INLINE_VISIBILITY
    bool __is_long() const _NOEXCEPT
        {return bool(__r_.first().__s.__size_ & __short_mask);}

    _LIBCPP_INLINE_VISIBILITY
    void __set_short_size(size_type __s) _NOEXCEPT
#if _LIBCPP_BIG_ENDIAN
        {__r_.first().__s.__size_ = (unsigned char)(__s);}
#else
        {__r_.first().__s.__size_ = (unsigned char)(__s << 1);}
#endif
    _LIBCPP_INLINE_VISIBILITY
    size_type __get_short_size() const _NOEXCEPT
#if _LIBCPP_BIG_ENDIAN
        {return __r_.first().__s.__size_;}
#else
        {return __r_.first().__s.__size_ >> 1;}
#endif
    _LIBCPP_INLINE_VISIBILITY
    void __set_long_size(size_type __s) _NOEXCEPT
        {__r_.first().__l.__size_ = __s;}
    _LIBCPP_INLINE_VISIBILITY
    size_type __get_long_size() const _NOEXCEPT
        {return __r_.first().__l.__size_;}
    _LIBCPP_INLINE_VISIBILITY
    void __set_size(size_type __s) _NOEXCEPT
        {if (__is_long()) __set_long_size(__s); else __set_short_size(__s);}

    _LIBCPP_INLINE_VISIBILITY
    void __set_long_cap(size_type __s) _NOEXCEPT
        {__r_.first().__l.__cap_  = __long_mask | __s;}
    _LIBCPP_INLINE_VISIBILITY
    size_type __get_long_cap() const _NOEXCEPT
        {return __r_.first().__l.__cap_ & size_type(~__long_mask);}

    _LIBCPP_INLINE_VISIBILITY
    void __set_long_pointer(pointer __p) _NOEXCEPT
        {__r_.first().__l.__data_ = __p;}
    _LIBCPP_INLINE_VISIBILITY
    pointer __get_long_pointer() _NOEXCEPT
        {return __r_.first().__l.__data_;}
    _LIBCPP_INLINE_VISIBILITY
    const_pointer __get_long_pointer() const _NOEXCEPT
        {return __r_.first().__l.__data_;}
    _LIBCPP_INLINE_VISIBILITY
    pointer __get_short_pointer() _NOEXCEPT
        {return __r_.first().__s.__data_;}
    _LIBCPP_INLINE_VISIBILITY
    const_pointer __get_short_pointer() const _NOEXCEPT
        {return __r_.first().__s.__data_;}
    _LIBCPP_INLINE_VISIBILITY
    pointer __get_pointer() _NOEXCEPT
        {return __is_long() ? __get_long_pointer() : __get_short_pointer();}
    _LIBCPP_INLINE_VISIBILITY
    const_pointer __get_pointer() const _NOEXCEPT
        {return __is_long() ? __get_long_pointer() : __get_short_pointer();}

    _LIBCPP_INLINE_VISIBILITY
    void __zero() _NOEXCEPT
        {
            size_type (&__a)[__n_words] = __r_.first().__r.__words;
            for (unsigned __i = 0; __i < __n_words; ++__i)
                __a[__i] = 0;
        }

    template <size_type __a> static
        _LIBCPP_INLINE_VISIBILITY
        size_type __align(size_type __s) _NOEXCEPT
            {return __s + (__a-1) & ~(__a-1);}
    enum {__alignment = 16};
    static _LIBCPP_INLINE_VISIBILITY
    size_type __recommend(size_type __s) _NOEXCEPT
        {return (__s < __min_cap ? __min_cap :
                 __align<sizeof(value_type) < __alignment ?
                            __alignment/sizeof(value_type) : 1 > (__s+1)) - 1;}

    void __init(const_pointer __s, size_type __sz, size_type __reserve);
    void __init(const_pointer __s, size_type __sz);
    void __init(size_type __n, value_type __c);

    template <class _InputIterator>
    typename enable_if
    <
         __is_input_iterator  <_InputIterator>::value &&
        !__is_forward_iterator<_InputIterator>::value,
        void
    >::type
    __init(_InputIterator __first, _InputIterator __last);

    template <class _ForwardIterator>
    typename enable_if
    <
        __is_forward_iterator<_ForwardIterator>::value,
        void
    >::type
    __init(_ForwardIterator __first, _ForwardIterator __last);

    void __grow_by(size_type __old_cap, size_type __delta_cap, size_type __old_sz,
                   size_type __n_copy,  size_type __n_del,     size_type __n_add = 0);
    void __grow_by_and_replace(size_type __old_cap, size_type __delta_cap, size_type __old_sz,
                               size_type __n_copy,  size_type __n_del,
                               size_type __n_add, const_pointer __p_new_stuff);

    _LIBCPP_INLINE_VISIBILITY
    void __erase_to_end(size_type __pos);

    _LIBCPP_INLINE_VISIBILITY
    void __copy_assign_alloc(const basic_string& __str)
        {__copy_assign_alloc(__str, integral_constant<bool,
                      __alloc_traits::propagate_on_container_copy_assignment::value>());}

    _LIBCPP_INLINE_VISIBILITY
    void __copy_assign_alloc(const basic_string& __str, true_type)
        {
            if (__alloc() != __str.__alloc())
            {
                clear();
                shrink_to_fit();
            }
            __alloc() = __str.__alloc();
        }

    _LIBCPP_INLINE_VISIBILITY
    void __copy_assign_alloc(const basic_string&, false_type) _NOEXCEPT
        {}

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
    _LIBCPP_INLINE_VISIBILITY
    void __move_assign(basic_string& __str, false_type);
    _LIBCPP_INLINE_VISIBILITY
    void __move_assign(basic_string& __str, true_type)
        _NOEXCEPT_(is_nothrow_move_assignable<allocator_type>::value);
#endif

    _LIBCPP_INLINE_VISIBILITY
    void
    __move_assign_alloc(basic_string& __str)
        _NOEXCEPT_(
            !__alloc_traits::propagate_on_container_move_assignment::value ||
            is_nothrow_move_assignable<allocator_type>::value)
    {__move_assign_alloc(__str, integral_constant<bool,
                      __alloc_traits::propagate_on_container_move_assignment::value>());}

    _LIBCPP_INLINE_VISIBILITY
    void __move_assign_alloc(basic_string& __c, true_type)
        _NOEXCEPT_(is_nothrow_move_assignable<allocator_type>::value)
        {
            __alloc() = _VSTD::move(__c.__alloc());
        }

    _LIBCPP_INLINE_VISIBILITY
    void __move_assign_alloc(basic_string&, false_type)
        _NOEXCEPT
        {}

    _LIBCPP_INLINE_VISIBILITY
    static void __swap_alloc(allocator_type& __x, allocator_type& __y)
        _NOEXCEPT_(!__alloc_traits::propagate_on_container_swap::value ||
                   __is_nothrow_swappable<allocator_type>::value)
        {__swap_alloc(__x, __y, integral_constant<bool,
                      __alloc_traits::propagate_on_container_swap::value>());}

    _LIBCPP_INLINE_VISIBILITY
    static void __swap_alloc(allocator_type& __x, allocator_type& __y, true_type)
        _NOEXCEPT_(__is_nothrow_swappable<allocator_type>::value)
        {
            using _VSTD::swap;
            swap(__x, __y);
        }
    _LIBCPP_INLINE_VISIBILITY
    static void __swap_alloc(allocator_type&, allocator_type&, false_type) _NOEXCEPT
        {}

    _LIBCPP_INLINE_VISIBILITY void __invalidate_all_iterators();
    _LIBCPP_INLINE_VISIBILITY void __invalidate_iterators_past(size_type);

    friend basic_string operator+<>(const basic_string&, const basic_string&);
    friend basic_string operator+<>(const value_type*, const basic_string&);
    friend basic_string operator+<>(value_type, const basic_string&);
    friend basic_string operator+<>(const basic_string&, const value_type*);
    friend basic_string operator+<>(const basic_string&, value_type);
};

template <class _CharT, class _Traits, class _Allocator>
#ifndef _LIBCPP_DEBUG
_LIBCPP_INLINE_VISIBILITY inline
#endif
void
basic_string<_CharT, _Traits, _Allocator>::__invalidate_all_iterators()
{
#ifdef _LIBCPP_DEBUG
    iterator::__remove_all(this);
    const_iterator::__remove_all(this);
#endif  // _LIBCPP_DEBUG
}

template <class _CharT, class _Traits, class _Allocator>
#ifndef _LIBCPP_DEBUG
_LIBCPP_INLINE_VISIBILITY inline
#endif
void
basic_string<_CharT, _Traits, _Allocator>::__invalidate_iterators_past(size_type
#ifdef _LIBCPP_DEBUG
                                                                        __pos
#endif
                                                                      )
{
#ifdef _LIBCPP_DEBUG
    const_iterator __beg = begin();
    if (__iterator_list_.first)
    {
        for (iterator* __p = __iterator_list_.first; __p;)
        {
            if (*__p - __beg > static_cast<difference_type>(__pos))
            {
                iterator* __n = __p;
                __p = __p->__next;
                __n->__remove_owner();
            }
            else
                __p = __p->__next;
        }
    }
    if (__iterator_list_.second)
    {
        for (const_iterator* __p = __iterator_list_.second; __p;)
        {
            if (*__p - __beg > static_cast<difference_type>(__pos))
            {
                const_iterator* __n = __p;
                __p = __p->__next;
                __n->__remove_owner();
            }
            else
                __p = __p->__next;
        }
    }
#endif  // _LIBCPP_DEBUG
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>::basic_string()
    _NOEXCEPT_(is_nothrow_default_constructible<allocator_type>::value)
{
    __zero();
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>::basic_string(const allocator_type& __a)
    : __r_(__a)
{
    __zero();
}

template <class _CharT, class _Traits, class _Allocator>
void
basic_string<_CharT, _Traits, _Allocator>::__init(const_pointer __s, size_type __sz, size_type __reserve)
{
    if (__reserve > max_size())
        this->__throw_length_error();
    pointer __p;
    if (__reserve < __min_cap)
    {
        __set_short_size(__sz);
        __p = __get_short_pointer();
    }
    else
    {
        size_type __cap = __recommend(__reserve);
        __p = __alloc_traits::allocate(__alloc(), __cap+1);
        __set_long_pointer(__p);
        __set_long_cap(__cap+1);
        __set_long_size(__sz);
    }
    traits_type::copy(__p, __s, __sz);
    traits_type::assign(__p[__sz], value_type());
}

template <class _CharT, class _Traits, class _Allocator>
void
basic_string<_CharT, _Traits, _Allocator>::__init(const_pointer __s, size_type __sz)
{
    if (__sz > max_size())
        this->__throw_length_error();
    pointer __p;
    if (__sz < __min_cap)
    {
        __set_short_size(__sz);
        __p = __get_short_pointer();
    }
    else
    {
        size_type __cap = __recommend(__sz);
        __p = __alloc_traits::allocate(__alloc(), __cap+1);
        __set_long_pointer(__p);
        __set_long_cap(__cap+1);
        __set_long_size(__sz);
    }
    traits_type::copy(__p, __s, __sz);
    traits_type::assign(__p[__sz], value_type());
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>::basic_string(const_pointer __s)
{
#ifdef _LIBCPP_DEBUG
    assert(__s != 0);
#endif
    __init(__s, traits_type::length(__s));
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>::basic_string(const_pointer __s, const allocator_type& __a)
    : __r_(__a)
{
#ifdef _LIBCPP_DEBUG
    assert(__s != 0);
#endif
    __init(__s, traits_type::length(__s));
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>::basic_string(const_pointer __s, size_type __n)
{
#ifdef _LIBCPP_DEBUG
    assert(__s != 0);
#endif
    __init(__s, __n);
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>::basic_string(const_pointer __s, size_type __n, const allocator_type& __a)
    : __r_(__a)
{
#ifdef _LIBCPP_DEBUG
    assert(__s != 0);
#endif
    __init(__s, __n);
}

template <class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>::basic_string(const basic_string& __str)
    : __r_(__alloc_traits::select_on_container_copy_construction(__str.__alloc()))
{
    if (!__str.__is_long())
        __r_.first().__r = __str.__r_.first().__r;
    else
        __init(__str.__get_long_pointer(), __str.__get_long_size());
}

template <class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>::basic_string(const basic_string& __str, const allocator_type& __a)
    : __r_(__a)
{
    if (!__str.__is_long())
        __r_.first().__r = __str.__r_.first().__r;
    else
        __init(__str.__get_long_pointer(), __str.__get_long_size());
}

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>::basic_string(basic_string&& __str)
        _NOEXCEPT_(is_nothrow_move_constructible<allocator_type>::value)
    : __r_(_VSTD::move(__str.__r_))
{
    __str.__zero();
#ifdef _LIBCPP_DEBUG
    __str.__invalidate_all_iterators();
#endif
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>::basic_string(basic_string&& __str, const allocator_type& __a)
    : __r_(__a)
{
    if (__a == __str.__alloc() || !__str.__is_long())
        __r_.first().__r = __str.__r_.first().__r;
    else
        __init(__str.__get_long_pointer(), __str.__get_long_size());
    __str.__zero();
#ifdef _LIBCPP_DEBUG
    __str.__invalidate_all_iterators();
#endif
}

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES

template <class _CharT, class _Traits, class _Allocator>
void
basic_string<_CharT, _Traits, _Allocator>::__init(size_type __n, value_type __c)
{
    if (__n > max_size())
        this->__throw_length_error();
    pointer __p;
    if (__n < __min_cap)
    {
        __set_short_size(__n);
        __p = __get_short_pointer();
    }
    else
    {
        size_type __cap = __recommend(__n);
        __p = __alloc_traits::allocate(__alloc(), __cap+1);
        __set_long_pointer(__p);
        __set_long_cap(__cap+1);
        __set_long_size(__n);
    }
    traits_type::assign(__p, __n, __c);
    traits_type::assign(__p[__n], value_type());
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>::basic_string(size_type __n, value_type __c)
{
    __init(__n, __c);
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>::basic_string(size_type __n, value_type __c, const allocator_type& __a)
    : __r_(__a)
{
    __init(__n, __c);
}

template <class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>::basic_string(const basic_string& __str, size_type __pos, size_type __n,
                                                        const allocator_type& __a)
    : __r_(__a)
{
    size_type __str_sz = __str.size();
    if (__pos > __str_sz)
        this->__throw_out_of_range();
    __init(__str.data() + __pos, _VSTD::min(__n, __str_sz - __pos));
}

template <class _CharT, class _Traits, class _Allocator>
template <class _InputIterator>
typename enable_if
<
     __is_input_iterator  <_InputIterator>::value &&
    !__is_forward_iterator<_InputIterator>::value,
    void
>::type
basic_string<_CharT, _Traits, _Allocator>::__init(_InputIterator __first, _InputIterator __last)
{
    __zero();
#ifndef _LIBCPP_NO_EXCEPTIONS
    try
    {
#endif  // _LIBCPP_NO_EXCEPTIONS
    for (; __first != __last; ++__first)
        push_back(*__first);
#ifndef _LIBCPP_NO_EXCEPTIONS
    }
    catch (...)
    {
        if (__is_long())
            __alloc_traits::deallocate(__alloc(), __get_long_pointer(), __get_long_cap());
        throw;
    }
#endif  // _LIBCPP_NO_EXCEPTIONS
}

template <class _CharT, class _Traits, class _Allocator>
template <class _ForwardIterator>
typename enable_if
<
    __is_forward_iterator<_ForwardIterator>::value,
    void
>::type
basic_string<_CharT, _Traits, _Allocator>::__init(_ForwardIterator __first, _ForwardIterator __last)
{
    size_type __sz = static_cast<size_type>(_VSTD::distance(__first, __last));
    if (__sz > max_size())
        this->__throw_length_error();
    pointer __p;
    if (__sz < __min_cap)
    {
        __set_short_size(__sz);
        __p = __get_short_pointer();
    }
    else
    {
        size_type __cap = __recommend(__sz);
        __p = __alloc_traits::allocate(__alloc(), __cap+1);
        __set_long_pointer(__p);
        __set_long_cap(__cap+1);
        __set_long_size(__sz);
    }
    for (; __first != __last; ++__first, ++__p)
        traits_type::assign(*__p, *__first);
    traits_type::assign(*__p, value_type());
}

template <class _CharT, class _Traits, class _Allocator>
template<class _InputIterator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>::basic_string(_InputIterator __first, _InputIterator __last)
{
    __init(__first, __last);
}

template <class _CharT, class _Traits, class _Allocator>
template<class _InputIterator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>::basic_string(_InputIterator __first, _InputIterator __last,
                                                        const allocator_type& __a)
    : __r_(__a)
{
    __init(__first, __last);
}

#ifndef _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>::basic_string(initializer_list<value_type> __il)
{
    __init(__il.begin(), __il.end());
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>::basic_string(initializer_list<value_type> __il, const allocator_type& __a)
    : __r_(__a)
{
    __init(__il.begin(), __il.end());
}

#endif  // _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS

template <class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>::~basic_string()
{
    __invalidate_all_iterators();
    if (__is_long())
        __alloc_traits::deallocate(__alloc(), __get_long_pointer(), __get_long_cap());
}

template <class _CharT, class _Traits, class _Allocator>
void
basic_string<_CharT, _Traits, _Allocator>::__grow_by_and_replace
    (size_type __old_cap, size_type __delta_cap, size_type __old_sz,
     size_type __n_copy,  size_type __n_del,     size_type __n_add, const_pointer __p_new_stuff)
{
    size_type __ms = max_size();
    if (__delta_cap > __ms - __old_cap - 1)
        this->__throw_length_error();
    pointer __old_p = __get_pointer();
    size_type __cap = __old_cap < __ms / 2 - __alignment ?
                          __recommend(_VSTD::max(__old_cap + __delta_cap, 2 * __old_cap)) :
                          __ms - 1;
    pointer __p = __alloc_traits::allocate(__alloc(), __cap+1);
    __invalidate_all_iterators();
    if (__n_copy != 0)
        traits_type::copy(__p, __old_p, __n_copy);
    if (__n_add != 0)
        traits_type::copy(__p + __n_copy, __p_new_stuff, __n_add);
    size_type __sec_cp_sz = __old_sz - __n_del - __n_copy;
    if (__sec_cp_sz != 0)
        traits_type::copy(__p + __n_copy + __n_add, __old_p + __n_copy + __n_del, __sec_cp_sz);
    if (__old_cap+1 != __min_cap)
        __alloc_traits::deallocate(__alloc(), __old_p, __old_cap+1);
    __set_long_pointer(__p);
    __set_long_cap(__cap+1);
    __old_sz = __n_copy + __n_add + __sec_cp_sz;
    __set_long_size(__old_sz);
    traits_type::assign(__p[__old_sz], value_type());
}

template <class _CharT, class _Traits, class _Allocator>
void
basic_string<_CharT, _Traits, _Allocator>::__grow_by(size_type __old_cap, size_type __delta_cap, size_type __old_sz,
                                                     size_type __n_copy,  size_type __n_del,     size_type __n_add)
{
    size_type __ms = max_size();
    if (__delta_cap > __ms - __old_cap - 1)
        this->__throw_length_error();
    pointer __old_p = __get_pointer();
    size_type __cap = __old_cap < __ms / 2 - __alignment ?
                          __recommend(_VSTD::max(__old_cap + __delta_cap, 2 * __old_cap)) :
                          __ms - 1;
    pointer __p = __alloc_traits::allocate(__alloc(), __cap+1);
    __invalidate_all_iterators();
    if (__n_copy != 0)
        traits_type::copy(__p, __old_p, __n_copy);
    size_type __sec_cp_sz = __old_sz - __n_del - __n_copy;
    if (__sec_cp_sz != 0)
        traits_type::copy(__p + __n_copy + __n_add, __old_p + __n_copy + __n_del, __sec_cp_sz);
    if (__old_cap+1 != __min_cap)
        __alloc_traits::deallocate(__alloc(), __old_p, __old_cap+1);
    __set_long_pointer(__p);
    __set_long_cap(__cap+1);
}

// assign

template <class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>&
basic_string<_CharT, _Traits, _Allocator>::assign(const_pointer __s, size_type __n)
{
#ifdef _LIBCPP_DEBUG
    assert(__s != 0);
#endif
    size_type __cap = capacity();
    if (__cap >= __n)
    {
        pointer __p = __get_pointer();
        traits_type::move(__p, __s, __n);
        traits_type::assign(__p[__n], value_type());
        __set_size(__n);
        __invalidate_iterators_past(__n);
    }
    else
    {
        size_type __sz = size();
        __grow_by_and_replace(__cap, __n - __cap, __sz, 0, __sz, __n, __s);
    }
    return *this;
}

template <class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>&
basic_string<_CharT, _Traits, _Allocator>::assign(size_type __n, value_type __c)
{
    size_type __cap = capacity();
    if (__cap < __n)
    {
        size_type __sz = size();
        __grow_by(__cap, __n - __cap, __sz, 0, __sz);
    }
    else
        __invalidate_iterators_past(__n);
    pointer __p = __get_pointer();
    traits_type::assign(__p, __n, __c);
    traits_type::assign(__p[__n], value_type());
    __set_size(__n);
    return *this;
}

template <class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>&
basic_string<_CharT, _Traits, _Allocator>::operator=(value_type __c)
{
    pointer __p;
    if (__is_long())
    {
        __p = __get_long_pointer();
        __set_long_size(1);
    }
    else
    {
        __p = __get_short_pointer();
        __set_short_size(1);
    }
    traits_type::assign(*__p, __c);
    traits_type::assign(*++__p, value_type());
    __invalidate_iterators_past(1);
    return *this;
}

template <class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>&
basic_string<_CharT, _Traits, _Allocator>::operator=(const basic_string& __str)
{
    if (this != &__str)
    {
        __copy_assign_alloc(__str);
        assign(__str);
    }
    return *this;
}

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
void
basic_string<_CharT, _Traits, _Allocator>::__move_assign(basic_string& __str, false_type)
{
    if (__alloc() != __str.__alloc())
        assign(__str);
    else
        __move_assign(__str, true_type());
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
void
basic_string<_CharT, _Traits, _Allocator>::__move_assign(basic_string& __str, true_type)
    _NOEXCEPT_(is_nothrow_move_assignable<allocator_type>::value)
{
    clear();
    shrink_to_fit();
    __r_.first() = __str.__r_.first();
    __move_assign_alloc(__str);
    __str.__zero();
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>&
basic_string<_CharT, _Traits, _Allocator>::operator=(basic_string&& __str)
    _NOEXCEPT_(__alloc_traits::propagate_on_container_move_assignment::value &&
               is_nothrow_move_assignable<allocator_type>::value)
{
    __move_assign(__str, integral_constant<bool,
          __alloc_traits::propagate_on_container_move_assignment::value>());
    return *this;
}

#endif

template <class _CharT, class _Traits, class _Allocator>
template<class _InputIterator>
typename enable_if
<
     __is_input_iterator  <_InputIterator>::value &&
    !__is_forward_iterator<_InputIterator>::value,
    basic_string<_CharT, _Traits, _Allocator>&
>::type
basic_string<_CharT, _Traits, _Allocator>::assign(_InputIterator __first, _InputIterator __last)
{
    clear();
    for (; __first != __last; ++__first)
        push_back(*__first);
    return *this;
}

template <class _CharT, class _Traits, class _Allocator>
template<class _ForwardIterator>
typename enable_if
<
    __is_forward_iterator<_ForwardIterator>::value,
    basic_string<_CharT, _Traits, _Allocator>&
>::type
basic_string<_CharT, _Traits, _Allocator>::assign(_ForwardIterator __first, _ForwardIterator __last)
{
    size_type __n = static_cast<size_type>(_VSTD::distance(__first, __last));
    size_type __cap = capacity();
    if (__cap < __n)
    {
        size_type __sz = size();
        __grow_by(__cap, __n - __cap, __sz, 0, __sz);
    }
    else
        __invalidate_iterators_past(__n);
    pointer __p = __get_pointer();
    for (; __first != __last; ++__first, ++__p)
        traits_type::assign(*__p, *__first);
    traits_type::assign(*__p, value_type());
    __set_size(__n);
    return *this;
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>&
basic_string<_CharT, _Traits, _Allocator>::assign(const basic_string& __str)
{
    return assign(__str.data(), __str.size());
}

template <class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>&
basic_string<_CharT, _Traits, _Allocator>::assign(const basic_string& __str, size_type __pos, size_type __n)
{
    size_type __sz = __str.size();
    if (__pos > __sz)
        this->__throw_out_of_range();
    return assign(__str.data() + __pos, _VSTD::min(__n, __sz - __pos));
}

template <class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>&
basic_string<_CharT, _Traits, _Allocator>::assign(const_pointer __s)
{
#ifdef _LIBCPP_DEBUG
    assert(__s != 0);
#endif
    return assign(__s, traits_type::length(__s));
}

// append

template <class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>&
basic_string<_CharT, _Traits, _Allocator>::append(const_pointer __s, size_type __n)
{
#ifdef _LIBCPP_DEBUG
    assert(__s != 0);
#endif
    size_type __cap = capacity();
    size_type __sz = size();
    if (__cap - __sz >= __n)
    {
        if (__n)
        {
            pointer __p = __get_pointer();
            traits_type::copy(__p + __sz, __s, __n);
            __sz += __n;
            __set_size(__sz);
            traits_type::assign(__p[__sz], value_type());
        }
    }
    else
        __grow_by_and_replace(__cap, __sz + __n - __cap, __sz, __sz, 0, __n, __s);
    return *this;
}

template <class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>&
basic_string<_CharT, _Traits, _Allocator>::append(size_type __n, value_type __c)
{
    if (__n)
    {
        size_type __cap = capacity();
        size_type __sz = size();
        if (__cap - __sz < __n)
            __grow_by(__cap, __sz + __n - __cap, __sz, __sz, 0);
        pointer __p = __get_pointer();
        traits_type::assign(__p + __sz, __n, __c);
        __sz += __n;
        __set_size(__sz);
        traits_type::assign(__p[__sz], value_type());
    }
    return *this;
}

template <class _CharT, class _Traits, class _Allocator>
void
basic_string<_CharT, _Traits, _Allocator>::push_back(value_type __c)
{
    size_type __cap = capacity();
    size_type __sz = size();
    if (__sz == __cap)
        __grow_by(__cap, 1, __sz, __sz, 0);
    pointer __p = __get_pointer() + __sz;
    traits_type::assign(*__p, __c);
    traits_type::assign(*++__p, value_type());
    __set_size(__sz+1);
}

template <class _CharT, class _Traits, class _Allocator>
template<class _InputIterator>
typename enable_if
<
     __is_input_iterator  <_InputIterator>::value &&
    !__is_forward_iterator<_InputIterator>::value,
    basic_string<_CharT, _Traits, _Allocator>&
>::type
basic_string<_CharT, _Traits, _Allocator>::append(_InputIterator __first, _InputIterator __last)
{
    for (; __first != __last; ++__first)
        push_back(*__first);
    return *this;
}

template <class _CharT, class _Traits, class _Allocator>
template<class _ForwardIterator>
typename enable_if
<
    __is_forward_iterator<_ForwardIterator>::value,
    basic_string<_CharT, _Traits, _Allocator>&
>::type
basic_string<_CharT, _Traits, _Allocator>::append(_ForwardIterator __first, _ForwardIterator __last)
{
    size_type __sz = size();
    size_type __cap = capacity();
    size_type __n = static_cast<size_type>(_VSTD::distance(__first, __last));
    if (__n)
    {
        if (__cap - __sz < __n)
            __grow_by(__cap, __sz + __n - __cap, __sz, __sz, 0);
        pointer __p = __get_pointer() + __sz;
        for (; __first != __last; ++__p, ++__first)
            traits_type::assign(*__p, *__first);
        traits_type::assign(*__p, value_type());
        __set_size(__sz + __n);
    }
    return *this;
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>&
basic_string<_CharT, _Traits, _Allocator>::append(const basic_string& __str)
{
    return append(__str.data(), __str.size());
}

template <class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>&
basic_string<_CharT, _Traits, _Allocator>::append(const basic_string& __str, size_type __pos, size_type __n)
{
    size_type __sz = __str.size();
    if (__pos > __sz)
        this->__throw_out_of_range();
    return append(__str.data() + __pos, _VSTD::min(__n, __sz - __pos));
}

template <class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>&
basic_string<_CharT, _Traits, _Allocator>::append(const_pointer __s)
{
#ifdef _LIBCPP_DEBUG
    assert(__s != 0);
#endif
    return append(__s, traits_type::length(__s));
}

// insert

template <class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>&
basic_string<_CharT, _Traits, _Allocator>::insert(size_type __pos, const_pointer __s, size_type __n)
{
#ifdef _LIBCPP_DEBUG
    assert(__s != 0);
#endif
    size_type __sz = size();
    if (__pos > __sz)
        this->__throw_out_of_range();
    size_type __cap = capacity();
    if (__cap - __sz >= __n)
    {
        if (__n)
        {
            pointer __p = __get_pointer();
            size_type __n_move = __sz - __pos;
            if (__n_move != 0)
            {
                if (__p + __pos <= __s && __s < __p + __sz)
                    __s += __n;
                traits_type::move(__p + __pos + __n, __p + __pos, __n_move);
            }
            traits_type::move(__p + __pos, __s, __n);
            __sz += __n;
            __set_size(__sz);
            traits_type::assign(__p[__sz], value_type());
        }
    }
    else
        __grow_by_and_replace(__cap, __sz + __n - __cap, __sz, __pos, 0, __n, __s);
    return *this;
}

template <class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>&
basic_string<_CharT, _Traits, _Allocator>::insert(size_type __pos, size_type __n, value_type __c)
{
    size_type __sz = size();
    if (__pos > __sz)
        this->__throw_out_of_range();
    if (__n)
    {
        size_type __cap = capacity();
        pointer __p;
        if (__cap - __sz >= __n)
        {
            __p = __get_pointer();
            size_type __n_move = __sz - __pos;
            if (__n_move != 0)
                traits_type::move(__p + __pos + __n, __p + __pos, __n_move);
        }
        else
        {
            __grow_by(__cap, __sz + __n - __cap, __sz, __pos, 0, __n);
            __p = __get_long_pointer();
        }
        traits_type::assign(__p + __pos, __n, __c);
        __sz += __n;
        __set_size(__sz);
        traits_type::assign(__p[__sz], value_type());
    }
    return *this;
}

template <class _CharT, class _Traits, class _Allocator>
template<class _InputIterator>
typename enable_if
<
     __is_input_iterator  <_InputIterator>::value &&
    !__is_forward_iterator<_InputIterator>::value,
    typename basic_string<_CharT, _Traits, _Allocator>::iterator
>::type
basic_string<_CharT, _Traits, _Allocator>::insert(const_iterator __pos, _InputIterator __first, _InputIterator __last)
{
    size_type __old_sz = size();
    difference_type __ip = __pos - begin();
    for (; __first != __last; ++__first)
        push_back(*__first);
    pointer __p = __get_pointer();
    _VSTD::rotate(__p + __ip, __p + __old_sz, __p + size());
    return iterator(__p + __ip);
}

template <class _CharT, class _Traits, class _Allocator>
template<class _ForwardIterator>
typename enable_if
<
    __is_forward_iterator<_ForwardIterator>::value,
    typename basic_string<_CharT, _Traits, _Allocator>::iterator
>::type
basic_string<_CharT, _Traits, _Allocator>::insert(const_iterator __pos, _ForwardIterator __first, _ForwardIterator __last)
{
    size_type __ip = static_cast<size_type>(__pos - begin());
    size_type __sz = size();
    size_type __cap = capacity();
    size_type __n = static_cast<size_type>(_VSTD::distance(__first, __last));
    if (__n)
    {
        pointer __p;
        if (__cap - __sz >= __n)
        {
            __p = __get_pointer();
            size_type __n_move = __sz - __ip;
            if (__n_move != 0)
                traits_type::move(__p + __ip + __n, __p + __ip, __n_move);
        }
        else
        {
            __grow_by(__cap, __sz + __n - __cap, __sz, __ip, 0, __n);
            __p = __get_long_pointer();
        }
        __sz += __n;
        __set_size(__sz);
        traits_type::assign(__p[__sz], value_type());
        for (__p += __ip; __first != __last; ++__p, ++__first)
            traits_type::assign(*__p, *__first);
    }
    return begin() + __ip;
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>&
basic_string<_CharT, _Traits, _Allocator>::insert(size_type __pos1, const basic_string& __str)
{
    return insert(__pos1, __str.data(), __str.size());
}

template <class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>&
basic_string<_CharT, _Traits, _Allocator>::insert(size_type __pos1, const basic_string& __str,
                                                  size_type __pos2, size_type __n)
{
    size_type __str_sz = __str.size();
    if (__pos2 > __str_sz)
        this->__throw_out_of_range();
    return insert(__pos1, __str.data() + __pos2, _VSTD::min(__n, __str_sz - __pos2));
}

template <class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>&
basic_string<_CharT, _Traits, _Allocator>::insert(size_type __pos, const_pointer __s)
{
#ifdef _LIBCPP_DEBUG
    assert(__s != 0);
#endif
    return insert(__pos, __s, traits_type::length(__s));
}

template <class _CharT, class _Traits, class _Allocator>
typename basic_string<_CharT, _Traits, _Allocator>::iterator
basic_string<_CharT, _Traits, _Allocator>::insert(const_iterator __pos, value_type __c)
{
    size_type __ip = static_cast<size_type>(__pos - begin());
    size_type __sz = size();
    size_type __cap = capacity();
    pointer __p;
    if (__cap == __sz)
    {
        __grow_by(__cap, 1, __sz, __ip, 0, 1);
        __p = __get_long_pointer();
    }
    else
    {
        __p = __get_pointer();
        size_type __n_move = __sz - __ip;
        if (__n_move != 0)
            traits_type::move(__p + __ip + 1, __p + __ip, __n_move);
    }
    traits_type::assign(__p[__ip], __c);
    traits_type::assign(__p[++__sz], value_type());
    __set_size(__sz);
    return begin() + static_cast<difference_type>(__ip);
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
typename basic_string<_CharT, _Traits, _Allocator>::iterator
basic_string<_CharT, _Traits, _Allocator>::insert(const_iterator __pos, size_type __n, value_type __c)
{
    difference_type __p = __pos - begin();
    insert(static_cast<size_type>(__p), __n, __c);
    return begin() + __p;
}

// replace

template <class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>&
basic_string<_CharT, _Traits, _Allocator>::replace(size_type __pos, size_type __n1, const_pointer __s, size_type __n2)
{
#ifdef _LIBCPP_DEBUG
    assert(__s != 0);
#endif
    size_type __sz = size();
    if (__pos > __sz)
        this->__throw_out_of_range();
    __n1 = _VSTD::min(__n1, __sz - __pos);
    size_type __cap = capacity();
    if (__cap - __sz + __n1 >= __n2)
    {
        pointer __p = __get_pointer();
        if (__n1 != __n2)
        {
            size_type __n_move = __sz - __pos - __n1;
            if (__n_move != 0)
            {
                if (__n1 > __n2)
                {
                    traits_type::move(__p + __pos, __s, __n2);
                    traits_type::move(__p + __pos + __n2, __p + __pos + __n1, __n_move);
                    goto __finish;
                }
                if (__p + __pos < __s && __s < __p + __sz)
                {
                    if (__p + __pos + __n1 <= __s)
                        __s += __n2 - __n1;
                    else // __p + __pos < __s < __p + __pos + __n1
                    {
                        traits_type::move(__p + __pos, __s, __n1);
                        __pos += __n1;
                        __s += __n2;
                        __n2 -= __n1;
                        __n1 = 0;
                    }
                }
                traits_type::move(__p + __pos + __n2, __p + __pos + __n1, __n_move);
            }
        }
        traits_type::move(__p + __pos, __s, __n2);
__finish:
        __sz += __n2 - __n1;
        __set_size(__sz);
        __invalidate_iterators_past(__sz);
        traits_type::assign(__p[__sz], value_type());
    }
    else
        __grow_by_and_replace(__cap, __sz - __n1 + __n2 - __cap, __sz, __pos, __n1, __n2, __s);
    return *this;
}

template <class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>&
basic_string<_CharT, _Traits, _Allocator>::replace(size_type __pos, size_type __n1, size_type __n2, value_type __c)
{
    size_type __sz = size();
    if (__pos > __sz)
        this->__throw_out_of_range();
    __n1 = _VSTD::min(__n1, __sz - __pos);
    size_type __cap = capacity();
    pointer __p;
    if (__cap - __sz + __n1 >= __n2)
    {
        __p = __get_pointer();
        if (__n1 != __n2)
        {
            size_type __n_move = __sz - __pos - __n1;
            if (__n_move != 0)
                traits_type::move(__p + __pos + __n2, __p + __pos + __n1, __n_move);
        }
    }
    else
    {
        __grow_by(__cap, __sz - __n1 + __n2 - __cap, __sz, __pos, __n1, __n2);
        __p = __get_long_pointer();
    }
    traits_type::assign(__p + __pos, __n2, __c);
    __sz += __n2 - __n1;
    __set_size(__sz);
    __invalidate_iterators_past(__sz);
    traits_type::assign(__p[__sz], value_type());
    return *this;
}

template <class _CharT, class _Traits, class _Allocator>
template<class _InputIterator>
typename enable_if
<
    __is_input_iterator<_InputIterator>::value,
    basic_string<_CharT, _Traits, _Allocator>&
>::type
basic_string<_CharT, _Traits, _Allocator>::replace(const_iterator __i1, const_iterator __i2,
                                                   _InputIterator __j1, _InputIterator __j2)
{
    for (; true; ++__i1, ++__j1)
    {
        if (__i1 == __i2)
        {
            if (__j1 != __j2)
                insert(__i1, __j1, __j2);
            break;
        }
        if (__j1 == __j2)
        {
            erase(__i1, __i2);
            break;
        }
        traits_type::assign(const_cast<value_type&>(*__i1), *__j1);
    }
    return *this;
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>&
basic_string<_CharT, _Traits, _Allocator>::replace(size_type __pos1, size_type __n1, const basic_string& __str)
{
    return replace(__pos1, __n1, __str.data(), __str.size());
}

template <class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>&
basic_string<_CharT, _Traits, _Allocator>::replace(size_type __pos1, size_type __n1, const basic_string& __str,
                                                   size_type __pos2, size_type __n2)
{
    size_type __str_sz = __str.size();
    if (__pos2 > __str_sz)
        this->__throw_out_of_range();
    return replace(__pos1, __n1, __str.data() + __pos2, _VSTD::min(__n2, __str_sz - __pos2));
}

template <class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>&
basic_string<_CharT, _Traits, _Allocator>::replace(size_type __pos, size_type __n1, const_pointer __s)
{
#ifdef _LIBCPP_DEBUG
    assert(__s != 0);
#endif
    return replace(__pos, __n1, __s, traits_type::length(__s));
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>&
basic_string<_CharT, _Traits, _Allocator>::replace(const_iterator __i1, const_iterator __i2, const basic_string& __str)
{
    return replace(static_cast<size_type>(__i1 - begin()), static_cast<size_type>(__i2 - __i1),
                   __str.data(), __str.size());
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>&
basic_string<_CharT, _Traits, _Allocator>::replace(const_iterator __i1, const_iterator __i2, const_pointer __s, size_type __n)
{
    return replace(static_cast<size_type>(__i1 - begin()), static_cast<size_type>(__i2 - __i1), __s, __n);
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>&
basic_string<_CharT, _Traits, _Allocator>::replace(const_iterator __i1, const_iterator __i2, const_pointer __s)
{
    return replace(static_cast<size_type>(__i1 - begin()), static_cast<size_type>(__i2 - __i1), __s);
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>&
basic_string<_CharT, _Traits, _Allocator>::replace(const_iterator __i1, const_iterator __i2, size_type __n, value_type __c)
{
    return replace(static_cast<size_type>(__i1 - begin()), static_cast<size_type>(__i2 - __i1), __n, __c);
}

// erase

template <class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>&
basic_string<_CharT, _Traits, _Allocator>::erase(size_type __pos, size_type __n)
{
    size_type __sz = size();
    if (__pos > __sz)
        this->__throw_out_of_range();
    if (__n)
    {
        pointer __p = __get_pointer();
        __n = _VSTD::min(__n, __sz - __pos);
        size_type __n_move = __sz - __pos - __n;
        if (__n_move != 0)
            traits_type::move(__p + __pos, __p + __pos + __n, __n_move);
        __sz -= __n;
        __set_size(__sz);
        __invalidate_iterators_past(__sz);
        traits_type::assign(__p[__sz], value_type());
    }
    return *this;
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
typename basic_string<_CharT, _Traits, _Allocator>::iterator
basic_string<_CharT, _Traits, _Allocator>::erase(const_iterator __pos)
{
    iterator __b = begin();
    size_type __r = static_cast<size_type>(__pos - __b);
    erase(__r, 1);
    return __b + static_cast<difference_type>(__r);
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
typename basic_string<_CharT, _Traits, _Allocator>::iterator
basic_string<_CharT, _Traits, _Allocator>::erase(const_iterator __first, const_iterator __last)
{
    iterator __b = begin();
    size_type __r = static_cast<size_type>(__first - __b);
    erase(__r, static_cast<size_type>(__last - __first));
    return __b + static_cast<difference_type>(__r);
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
void
basic_string<_CharT, _Traits, _Allocator>::pop_back()
{
#ifdef _LIBCPP_DEBUG
    assert(!empty());
#endif
    size_type __sz;
    if (__is_long())
    {
        __sz = __get_long_size() - 1;
        __set_long_size(__sz);
        traits_type::assign(*(__get_long_pointer() + __sz), value_type());
    }
    else
    {
        __sz = __get_short_size() - 1;
        __set_short_size(__sz);
        traits_type::assign(*(__get_short_pointer() + __sz), value_type());
    }
    __invalidate_iterators_past(__sz);
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
void
basic_string<_CharT, _Traits, _Allocator>::clear() _NOEXCEPT
{
    __invalidate_all_iterators();
    if (__is_long())
    {
        traits_type::assign(*__get_long_pointer(), value_type());
        __set_long_size(0);
    }
    else
    {
        traits_type::assign(*__get_short_pointer(), value_type());
        __set_short_size(0);
    }
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
void
basic_string<_CharT, _Traits, _Allocator>::__erase_to_end(size_type __pos)
{
    if (__is_long())
    {
        traits_type::assign(*(__get_long_pointer() + __pos), value_type());
        __set_long_size(__pos);
    }
    else
    {
        traits_type::assign(*(__get_short_pointer() + __pos), value_type());
        __set_short_size(__pos);
    }
    __invalidate_iterators_past(__pos);
}

template <class _CharT, class _Traits, class _Allocator>
void
basic_string<_CharT, _Traits, _Allocator>::resize(size_type __n, value_type __c)
{
    size_type __sz = size();
    if (__n > __sz)
        append(__n - __sz, __c);
    else
        __erase_to_end(__n);
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
typename basic_string<_CharT, _Traits, _Allocator>::size_type
basic_string<_CharT, _Traits, _Allocator>::max_size() const _NOEXCEPT
{
    size_type __m = __alloc_traits::max_size(__alloc());
#if _LIBCPP_BIG_ENDIAN
    return (__m <= ~__long_mask ? __m : __m/2) - 1;
#else
    return __m - 1;
#endif
}

template <class _CharT, class _Traits, class _Allocator>
void
basic_string<_CharT, _Traits, _Allocator>::reserve(size_type __res_arg)
{
    if (__res_arg > max_size())
        this->__throw_length_error();
    size_type __cap = capacity();
    size_type __sz = size();
    __res_arg = _VSTD::max(__res_arg, __sz);
    __res_arg = __recommend(__res_arg);
    if (__res_arg != __cap)
    {
        pointer __new_data, __p;
        bool __was_long, __now_long;
        if (__res_arg == __min_cap - 1)
        {
            __was_long = true;
            __now_long = false;
            __new_data = __get_short_pointer();
            __p = __get_long_pointer();
        }
        else
        {
            if (__res_arg > __cap)
                __new_data = __alloc_traits::allocate(__alloc(), __res_arg+1);
            else
            {
            #ifndef _LIBCPP_NO_EXCEPTIONS
                try
                {
            #endif  // _LIBCPP_NO_EXCEPTIONS
                    __new_data = __alloc_traits::allocate(__alloc(), __res_arg+1);
            #ifndef _LIBCPP_NO_EXCEPTIONS
                }
                catch (...)
                {
                    return;
                }
            #else  // _LIBCPP_NO_EXCEPTIONS
                if (__new_data == 0)
                    return;
            #endif  // _LIBCPP_NO_EXCEPTIONS
            }
            __now_long = true;
            __was_long = __is_long();
            __p = __get_pointer();
        }
        traits_type::copy(__new_data, __p, size()+1);
        if (__was_long)
            __alloc_traits::deallocate(__alloc(), __p, __cap+1);
        if (__now_long)
        {
            __set_long_cap(__res_arg+1);
            __set_long_size(__sz);
            __set_long_pointer(__new_data);
        }
        else
            __set_short_size(__sz);
        __invalidate_all_iterators();
    }
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
typename basic_string<_CharT, _Traits, _Allocator>::const_reference
basic_string<_CharT, _Traits, _Allocator>::operator[](size_type __pos) const
{
#ifdef __LIBCPP_DEBUG
    assert(__pos <= size());
#endif
    return *(data() + __pos);
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
typename basic_string<_CharT, _Traits, _Allocator>::reference
basic_string<_CharT, _Traits, _Allocator>::operator[](size_type __pos)
{
#ifdef __LIBCPP_DEBUG
    assert(__pos < size());
#endif
    return *(__get_pointer() + __pos);
}

template <class _CharT, class _Traits, class _Allocator>
typename basic_string<_CharT, _Traits, _Allocator>::const_reference
basic_string<_CharT, _Traits, _Allocator>::at(size_type __n) const
{
    if (__n >= size())
        this->__throw_out_of_range();
    return (*this)[__n];
}

template <class _CharT, class _Traits, class _Allocator>
typename basic_string<_CharT, _Traits, _Allocator>::reference
basic_string<_CharT, _Traits, _Allocator>::at(size_type __n)
{
    if (__n >= size())
        this->__throw_out_of_range();
    return (*this)[__n];
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
typename basic_string<_CharT, _Traits, _Allocator>::reference
basic_string<_CharT, _Traits, _Allocator>::front()
{
#ifdef _LIBCPP_DEBUG
    assert(!empty());
#endif
    return *__get_pointer();
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
typename basic_string<_CharT, _Traits, _Allocator>::const_reference
basic_string<_CharT, _Traits, _Allocator>::front() const
{
#ifdef _LIBCPP_DEBUG
    assert(!empty());
#endif
    return *data();
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
typename basic_string<_CharT, _Traits, _Allocator>::reference
basic_string<_CharT, _Traits, _Allocator>::back()
{
#ifdef _LIBCPP_DEBUG
    assert(!empty());
#endif
    return *(__get_pointer() + size() - 1);
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
typename basic_string<_CharT, _Traits, _Allocator>::const_reference
basic_string<_CharT, _Traits, _Allocator>::back() const
{
#ifdef _LIBCPP_DEBUG
    assert(!empty());
#endif
    return *(data() + size() - 1);
}

template <class _CharT, class _Traits, class _Allocator>
typename basic_string<_CharT, _Traits, _Allocator>::size_type
basic_string<_CharT, _Traits, _Allocator>::copy(pointer __s, size_type __n, size_type __pos) const
{
    size_type __sz = size();
    if (__pos > __sz)
        this->__throw_out_of_range();
    size_type __rlen = _VSTD::min(__n, __sz - __pos);
    traits_type::copy(__s, data() + __pos, __rlen);
    return __rlen;
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>
basic_string<_CharT, _Traits, _Allocator>::substr(size_type __pos, size_type __n) const
{
    return basic_string(*this, __pos, __n, __alloc());
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
void
basic_string<_CharT, _Traits, _Allocator>::swap(basic_string& __str)
        _NOEXCEPT_(!__alloc_traits::propagate_on_container_swap::value ||
                   __is_nothrow_swappable<allocator_type>::value)
{
    _VSTD::swap(__r_.first(), __str.__r_.first());
    __swap_alloc(__alloc(), __str.__alloc());
#ifdef _LIBCPP_DEBUG
    __invalidate_all_iterators();
    __str.__invalidate_all_iterators();
#endif  // _LIBCPP_DEBUG
}

// find

template <class _Traits>
struct _LIBCPP_HIDDEN __traits_eq
{
    typedef typename _Traits::char_type char_type;
    _LIBCPP_INLINE_VISIBILITY
    bool operator()(const char_type& __x, const char_type& __y) _NOEXCEPT
        {return _Traits::eq(__x, __y);}
};

template<class _CharT, class _Traits, class _Allocator>
typename basic_string<_CharT, _Traits, _Allocator>::size_type
basic_string<_CharT, _Traits, _Allocator>::find(const_pointer __s,
                                                size_type __pos,
                                                size_type __n) const _NOEXCEPT
{
#ifdef _LIBCPP_DEBUG
    assert(__s != 0);
#endif
    size_type __sz = size();
    if (__pos > __sz || __sz - __pos < __n)
        return npos;
    if (__n == 0)
        return __pos;
    const_pointer __p = data();
    const_pointer __r = _VSTD::search(__p + __pos, __p + __sz, __s, __s + __n,
                                     __traits_eq<traits_type>());
    if (__r == __p + __sz)
        return npos;
    return static_cast<size_type>(__r - __p);
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
typename basic_string<_CharT, _Traits, _Allocator>::size_type
basic_string<_CharT, _Traits, _Allocator>::find(const basic_string& __str,
                                                size_type __pos) const _NOEXCEPT
{
    return find(__str.data(), __pos, __str.size());
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
typename basic_string<_CharT, _Traits, _Allocator>::size_type
basic_string<_CharT, _Traits, _Allocator>::find(const_pointer __s,
                                                size_type __pos) const _NOEXCEPT
{
#ifdef _LIBCPP_DEBUG
    assert(__s != 0);
#endif
    return find(__s, __pos, traits_type::length(__s));
}

template<class _CharT, class _Traits, class _Allocator>
typename basic_string<_CharT, _Traits, _Allocator>::size_type
basic_string<_CharT, _Traits, _Allocator>::find(value_type __c,
                                                size_type __pos) const _NOEXCEPT
{
    size_type __sz = size();
    if (__pos >= __sz)
        return npos;
    const_pointer __p = data();
    const_pointer __r = traits_type::find(__p + __pos, __sz - __pos, __c);
    if (__r == 0)
        return npos;
    return static_cast<size_type>(__r - __p);
}

// rfind

template<class _CharT, class _Traits, class _Allocator>
typename basic_string<_CharT, _Traits, _Allocator>::size_type
basic_string<_CharT, _Traits, _Allocator>::rfind(const_pointer __s,
                                                 size_type __pos,
                                                 size_type __n) const _NOEXCEPT
{
#ifdef _LIBCPP_DEBUG
    assert(__s != 0);
#endif
    size_type __sz = size();
    __pos = _VSTD::min(__pos, __sz);
    if (__n < __sz - __pos)
        __pos += __n;
    else
        __pos = __sz;
    const_pointer __p = data();
    const_pointer __r = _VSTD::find_end(__p, __p + __pos, __s, __s + __n,
                                       __traits_eq<traits_type>());
    if (__n > 0 && __r == __p + __pos)
        return npos;
    return static_cast<size_type>(__r - __p);
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
typename basic_string<_CharT, _Traits, _Allocator>::size_type
basic_string<_CharT, _Traits, _Allocator>::rfind(const basic_string& __str,
                                                 size_type __pos) const _NOEXCEPT
{
    return rfind(__str.data(), __pos, __str.size());
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
typename basic_string<_CharT, _Traits, _Allocator>::size_type
basic_string<_CharT, _Traits, _Allocator>::rfind(const_pointer __s,
                                                 size_type __pos) const _NOEXCEPT
{
#ifdef _LIBCPP_DEBUG
    assert(__s != 0);
#endif
    return rfind(__s, __pos, traits_type::length(__s));
}

template<class _CharT, class _Traits, class _Allocator>
typename basic_string<_CharT, _Traits, _Allocator>::size_type
basic_string<_CharT, _Traits, _Allocator>::rfind(value_type __c,
                                                 size_type __pos) const _NOEXCEPT
{
    size_type __sz = size();
    if (__sz)
    {
        if (__pos < __sz)
            ++__pos;
        else
            __pos = __sz;
        const_pointer __p = data();
        for (const_pointer __ps = __p + __pos; __ps != __p;)
        {
            if (traits_type::eq(*--__ps, __c))
                return static_cast<size_type>(__ps - __p);
        }
    }
    return npos;
}

// find_first_of

template<class _CharT, class _Traits, class _Allocator>
typename basic_string<_CharT, _Traits, _Allocator>::size_type
basic_string<_CharT, _Traits, _Allocator>::find_first_of(const_pointer __s,
                                                         size_type __pos,
                                                         size_type __n) const _NOEXCEPT
{
#ifdef _LIBCPP_DEBUG
    assert(__s != 0);
#endif
    size_type __sz = size();
    if (__pos >= __sz || __n == 0)
        return npos;
    const_pointer __p = data();
    const_pointer __r = _VSTD::find_first_of(__p + __pos, __p + __sz, __s,
                                            __s + __n, __traits_eq<traits_type>());
    if (__r == __p + __sz)
        return npos;
    return static_cast<size_type>(__r - __p);
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
typename basic_string<_CharT, _Traits, _Allocator>::size_type
basic_string<_CharT, _Traits, _Allocator>::find_first_of(const basic_string& __str,
                                                         size_type __pos) const _NOEXCEPT
{
    return find_first_of(__str.data(), __pos, __str.size());
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
typename basic_string<_CharT, _Traits, _Allocator>::size_type
basic_string<_CharT, _Traits, _Allocator>::find_first_of(const_pointer __s,
                                                         size_type __pos) const _NOEXCEPT
{
#ifdef _LIBCPP_DEBUG
    assert(__s != 0);
#endif
    return find_first_of(__s, __pos, traits_type::length(__s));
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
typename basic_string<_CharT, _Traits, _Allocator>::size_type
basic_string<_CharT, _Traits, _Allocator>::find_first_of(value_type __c,
                                                         size_type __pos) const _NOEXCEPT
{
    return find(__c, __pos);
}

// find_last_of

template<class _CharT, class _Traits, class _Allocator>
typename basic_string<_CharT, _Traits, _Allocator>::size_type
basic_string<_CharT, _Traits, _Allocator>::find_last_of(const_pointer __s,
                                                        size_type __pos,
                                                        size_type __n) const _NOEXCEPT
{
#ifdef _LIBCPP_DEBUG
    assert(__s != 0);
#endif
    if (__n != 0)
    {
        size_type __sz = size();
        if (__pos < __sz)
            ++__pos;
        else
            __pos = __sz;
        const_pointer __p = data();
        for (const_pointer __ps = __p + __pos; __ps != __p;)
        {
            const_pointer __r = traits_type::find(__s, __n, *--__ps);
            if (__r)
                return static_cast<size_type>(__ps - __p);
        }
    }
    return npos;
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
typename basic_string<_CharT, _Traits, _Allocator>::size_type
basic_string<_CharT, _Traits, _Allocator>::find_last_of(const basic_string& __str,
                                                        size_type __pos) const _NOEXCEPT
{
    return find_last_of(__str.data(), __pos, __str.size());
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
typename basic_string<_CharT, _Traits, _Allocator>::size_type
basic_string<_CharT, _Traits, _Allocator>::find_last_of(const_pointer __s,
                                                        size_type __pos) const _NOEXCEPT
{
#ifdef _LIBCPP_DEBUG
    assert(__s != 0);
#endif
    return find_last_of(__s, __pos, traits_type::length(__s));
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
typename basic_string<_CharT, _Traits, _Allocator>::size_type
basic_string<_CharT, _Traits, _Allocator>::find_last_of(value_type __c,
                                                        size_type __pos) const _NOEXCEPT
{
    return rfind(__c, __pos);
}

// find_first_not_of

template<class _CharT, class _Traits, class _Allocator>
typename basic_string<_CharT, _Traits, _Allocator>::size_type
basic_string<_CharT, _Traits, _Allocator>::find_first_not_of(const_pointer __s,
                                                             size_type __pos,
                                                             size_type __n) const _NOEXCEPT
{
#ifdef _LIBCPP_DEBUG
    assert(__s != 0);
#endif
    size_type __sz = size();
    if (__pos < __sz)
    {
        const_pointer __p = data();
        const_pointer __pe = __p + __sz;
        for (const_pointer __ps = __p + __pos; __ps != __pe; ++__ps)
            if (traits_type::find(__s, __n, *__ps) == 0)
                return static_cast<size_type>(__ps - __p);
    }
    return npos;
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
typename basic_string<_CharT, _Traits, _Allocator>::size_type
basic_string<_CharT, _Traits, _Allocator>::find_first_not_of(const basic_string& __str,
                                                             size_type __pos) const _NOEXCEPT
{
    return find_first_not_of(__str.data(), __pos, __str.size());
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
typename basic_string<_CharT, _Traits, _Allocator>::size_type
basic_string<_CharT, _Traits, _Allocator>::find_first_not_of(const_pointer __s,
                                                             size_type __pos) const _NOEXCEPT
{
#ifdef _LIBCPP_DEBUG
    assert(__s != 0);
#endif
    return find_first_not_of(__s, __pos, traits_type::length(__s));
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
typename basic_string<_CharT, _Traits, _Allocator>::size_type
basic_string<_CharT, _Traits, _Allocator>::find_first_not_of(value_type __c,
                                                             size_type __pos) const _NOEXCEPT
{
    size_type __sz = size();
    if (__pos < __sz)
    {
        const_pointer __p = data();
        const_pointer __pe = __p + __sz;
        for (const_pointer __ps = __p + __pos; __ps != __pe; ++__ps)
            if (!traits_type::eq(*__ps, __c))
                return static_cast<size_type>(__ps - __p);
    }
    return npos;
}

// find_last_not_of

template<class _CharT, class _Traits, class _Allocator>
typename basic_string<_CharT, _Traits, _Allocator>::size_type
basic_string<_CharT, _Traits, _Allocator>::find_last_not_of(const_pointer __s,
                                                            size_type __pos,
                                                            size_type __n) const _NOEXCEPT
{
#ifdef _LIBCPP_DEBUG
    assert(__s != 0);
#endif
    size_type __sz = size();
    if (__pos < __sz)
        ++__pos;
    else
        __pos = __sz;
    const_pointer __p = data();
    for (const_pointer __ps = __p + __pos; __ps != __p;)
        if (traits_type::find(__s, __n, *--__ps) == 0)
            return static_cast<size_type>(__ps - __p);
    return npos;
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
typename basic_string<_CharT, _Traits, _Allocator>::size_type
basic_string<_CharT, _Traits, _Allocator>::find_last_not_of(const basic_string& __str,
                                                            size_type __pos) const _NOEXCEPT
{
    return find_last_not_of(__str.data(), __pos, __str.size());
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
typename basic_string<_CharT, _Traits, _Allocator>::size_type
basic_string<_CharT, _Traits, _Allocator>::find_last_not_of(const_pointer __s,
                                                            size_type __pos) const _NOEXCEPT
{
#ifdef _LIBCPP_DEBUG
    assert(__s != 0);
#endif
    return find_last_not_of(__s, __pos, traits_type::length(__s));
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
typename basic_string<_CharT, _Traits, _Allocator>::size_type
basic_string<_CharT, _Traits, _Allocator>::find_last_not_of(value_type __c,
                                                            size_type __pos) const _NOEXCEPT
{
    size_type __sz = size();
    if (__pos < __sz)
        ++__pos;
    else
        __pos = __sz;
    const_pointer __p = data();
    for (const_pointer __ps = __p + __pos; __ps != __p;)
        if (!traits_type::eq(*--__ps, __c))
            return static_cast<size_type>(__ps - __p);
    return npos;
}

// compare

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
int
basic_string<_CharT, _Traits, _Allocator>::compare(const basic_string& __str) const _NOEXCEPT
{
    size_t __lhs_sz = size();
    size_t __rhs_sz = __str.size();
    int __result = traits_type::compare(data(), __str.data(),
                                        _VSTD::min(__lhs_sz, __rhs_sz));
    if (__result != 0)
        return __result;
    if (__lhs_sz < __rhs_sz)
        return -1;
    if (__lhs_sz > __rhs_sz)
        return 1;
    return 0;
}

template <class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
int
basic_string<_CharT, _Traits, _Allocator>::compare(size_type __pos1,
                                                   size_type __n1,
                                                   const basic_string& __str) const
{
    return compare(__pos1, __n1, __str.data(), __str.size());
}

template <class _CharT, class _Traits, class _Allocator>
int
basic_string<_CharT, _Traits, _Allocator>::compare(size_type __pos1,
                                                   size_type __n1,
                                                   const basic_string& __str,
                                                   size_type __pos2,
                                                   size_type __n2) const
{
    size_type __sz = __str.size();
    if (__pos2 > __sz)
        this->__throw_out_of_range();
    return compare(__pos1, __n1, __str.data() + __pos2, _VSTD::min(__n2,
                                                                  __sz - __pos2));
}

template <class _CharT, class _Traits, class _Allocator>
int
basic_string<_CharT, _Traits, _Allocator>::compare(const_pointer __s) const _NOEXCEPT
{
#ifdef _LIBCPP_DEBUG
    assert(__s != 0);
#endif
    return compare(0, npos, __s, traits_type::length(__s));
}

template <class _CharT, class _Traits, class _Allocator>
int
basic_string<_CharT, _Traits, _Allocator>::compare(size_type __pos1,
                                                   size_type __n1,
                                                   const_pointer __s) const
{
#ifdef _LIBCPP_DEBUG
    assert(__s != 0);
#endif
    return compare(__pos1, __n1, __s, traits_type::length(__s));
}

template <class _CharT, class _Traits, class _Allocator>
int
basic_string<_CharT, _Traits, _Allocator>::compare(size_type __pos1,
                                                   size_type __n1,
                                                   const_pointer __s,
                                                   size_type __n2) const
{
#ifdef _LIBCPP_DEBUG
    assert(__s != 0);
#endif
    size_type __sz = size();
    if (__pos1 > __sz || __n2 == npos)
        this->__throw_out_of_range();
    size_type __rlen = _VSTD::min(__n1, __sz - __pos1);
    int __r = traits_type::compare(data() + __pos1, __s, _VSTD::min(__rlen, __n2));
    if (__r == 0)
    {
        if (__rlen < __n2)
            __r = -1;
        else if (__rlen > __n2)
            __r = 1;
    }
    return __r;
}

// __invariants

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
bool
basic_string<_CharT, _Traits, _Allocator>::__invariants() const
{
    if (size() > capacity())
        return false;
    if (capacity() < __min_cap - 1)
        return false;
    if (data() == 0)
        return false;
    if (data()[size()] != value_type(0))
        return false;
    return true;
}

// operator==

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
bool
operator==(const basic_string<_CharT, _Traits, _Allocator>& __lhs,
           const basic_string<_CharT, _Traits, _Allocator>& __rhs) _NOEXCEPT
{
    return __lhs.size() == __rhs.size() && _Traits::compare(__lhs.data(),
                                                            __rhs.data(),
                                                            __lhs.size()) == 0;
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
bool
operator==(const _CharT* __lhs,
           const basic_string<_CharT, _Traits, _Allocator>& __rhs) _NOEXCEPT
{
    return __rhs.compare(__lhs) == 0;
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
bool
operator==(const basic_string<_CharT,_Traits,_Allocator>& __lhs,
           const _CharT* __rhs) _NOEXCEPT
{
    return __lhs.compare(__rhs) == 0;
}

// operator!=

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
bool
operator!=(const basic_string<_CharT,_Traits,_Allocator>& __lhs,
           const basic_string<_CharT, _Traits, _Allocator>& __rhs) _NOEXCEPT
{
    return !(__lhs == __rhs);
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
bool
operator!=(const _CharT* __lhs,
           const basic_string<_CharT, _Traits, _Allocator>& __rhs) _NOEXCEPT
{
    return !(__lhs == __rhs);
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
bool
operator!=(const basic_string<_CharT, _Traits, _Allocator>& __lhs,
           const _CharT* __rhs) _NOEXCEPT
{
    return !(__lhs == __rhs);
}

// operator<

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
bool
operator< (const basic_string<_CharT, _Traits, _Allocator>& __lhs,
           const basic_string<_CharT, _Traits, _Allocator>& __rhs) _NOEXCEPT
{
    return __lhs.compare(__rhs) < 0;
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
bool
operator< (const basic_string<_CharT, _Traits, _Allocator>& __lhs,
           const _CharT* __rhs) _NOEXCEPT
{
    return __lhs.compare(__rhs) < 0;
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
bool
operator< (const _CharT* __lhs,
           const basic_string<_CharT, _Traits, _Allocator>& __rhs) _NOEXCEPT
{
    return __rhs.compare(__lhs) > 0;
}

// operator>

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
bool
operator> (const basic_string<_CharT, _Traits, _Allocator>& __lhs,
           const basic_string<_CharT, _Traits, _Allocator>& __rhs) _NOEXCEPT
{
    return __rhs < __lhs;
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
bool
operator> (const basic_string<_CharT, _Traits, _Allocator>& __lhs,
           const _CharT* __rhs) _NOEXCEPT
{
    return __rhs < __lhs;
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
bool
operator> (const _CharT* __lhs,
           const basic_string<_CharT, _Traits, _Allocator>& __rhs) _NOEXCEPT
{
    return __rhs < __lhs;
}

// operator<=

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
bool
operator<=(const basic_string<_CharT, _Traits, _Allocator>& __lhs,
           const basic_string<_CharT, _Traits, _Allocator>& __rhs) _NOEXCEPT
{
    return !(__rhs < __lhs);
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
bool
operator<=(const basic_string<_CharT, _Traits, _Allocator>& __lhs,
           const _CharT* __rhs) _NOEXCEPT
{
    return !(__rhs < __lhs);
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
bool
operator<=(const _CharT* __lhs,
           const basic_string<_CharT, _Traits, _Allocator>& __rhs) _NOEXCEPT
{
    return !(__rhs < __lhs);
}

// operator>=

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
bool
operator>=(const basic_string<_CharT, _Traits, _Allocator>& __lhs,
           const basic_string<_CharT, _Traits, _Allocator>& __rhs) _NOEXCEPT
{
    return !(__lhs < __rhs);
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
bool
operator>=(const basic_string<_CharT, _Traits, _Allocator>& __lhs,
           const _CharT* __rhs) _NOEXCEPT
{
    return !(__lhs < __rhs);
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
bool
operator>=(const _CharT* __lhs,
           const basic_string<_CharT, _Traits, _Allocator>& __rhs) _NOEXCEPT
{
    return !(__lhs < __rhs);
}

// operator +

template<class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>
operator+(const basic_string<_CharT, _Traits, _Allocator>& __lhs,
          const basic_string<_CharT, _Traits, _Allocator>& __rhs)
{
    basic_string<_CharT, _Traits, _Allocator> __r(__lhs.get_allocator());
    typename basic_string<_CharT, _Traits, _Allocator>::size_type __lhs_sz = __lhs.size();
    typename basic_string<_CharT, _Traits, _Allocator>::size_type __rhs_sz = __rhs.size();
    __r.__init(__lhs.data(), __lhs_sz, __lhs_sz + __rhs_sz);
    __r.append(__rhs.data(), __rhs_sz);
    return __r;
}

template<class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>
operator+(const _CharT* __lhs , const basic_string<_CharT,_Traits,_Allocator>& __rhs)
{
    basic_string<_CharT, _Traits, _Allocator> __r(__rhs.get_allocator());
    typename basic_string<_CharT, _Traits, _Allocator>::size_type __lhs_sz = _Traits::length(__lhs);
    typename basic_string<_CharT, _Traits, _Allocator>::size_type __rhs_sz = __rhs.size();
    __r.__init(__lhs, __lhs_sz, __lhs_sz + __rhs_sz);
    __r.append(__rhs.data(), __rhs_sz);
    return __r;
}

template<class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>
operator+(_CharT __lhs, const basic_string<_CharT,_Traits,_Allocator>& __rhs)
{
    basic_string<_CharT, _Traits, _Allocator> __r(__rhs.get_allocator());
    typename basic_string<_CharT, _Traits, _Allocator>::size_type __rhs_sz = __rhs.size();
    __r.__init(&__lhs, 1, 1 + __rhs_sz);
    __r.append(__rhs.data(), __rhs_sz);
    return __r;
}

template<class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>
operator+(const basic_string<_CharT, _Traits, _Allocator>& __lhs, const _CharT* __rhs)
{
    basic_string<_CharT, _Traits, _Allocator> __r(__lhs.get_allocator());
    typename basic_string<_CharT, _Traits, _Allocator>::size_type __lhs_sz = __lhs.size();
    typename basic_string<_CharT, _Traits, _Allocator>::size_type __rhs_sz = _Traits::length(__rhs);
    __r.__init(__lhs.data(), __lhs_sz, __lhs_sz + __rhs_sz);
    __r.append(__rhs, __rhs_sz);
    return __r;
}

template<class _CharT, class _Traits, class _Allocator>
basic_string<_CharT, _Traits, _Allocator>
operator+(const basic_string<_CharT, _Traits, _Allocator>& __lhs, _CharT __rhs)
{
    basic_string<_CharT, _Traits, _Allocator> __r(__lhs.get_allocator());
    typename basic_string<_CharT, _Traits, _Allocator>::size_type __lhs_sz = __lhs.size();
    __r.__init(__lhs.data(), __lhs_sz, __lhs_sz + 1);
    __r.push_back(__rhs);
    return __r;
}

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>
operator+(basic_string<_CharT, _Traits, _Allocator>&& __lhs, const basic_string<_CharT, _Traits, _Allocator>& __rhs)
{
    return _VSTD::move(__lhs.append(__rhs));
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>
operator+(const basic_string<_CharT, _Traits, _Allocator>& __lhs, basic_string<_CharT, _Traits, _Allocator>&& __rhs)
{
    return _VSTD::move(__rhs.insert(0, __lhs));
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>
operator+(basic_string<_CharT, _Traits, _Allocator>&& __lhs, basic_string<_CharT, _Traits, _Allocator>&& __rhs)
{
    return _VSTD::move(__lhs.append(__rhs));
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>
operator+(const _CharT* __lhs , basic_string<_CharT,_Traits,_Allocator>&& __rhs)
{
    return _VSTD::move(__rhs.insert(0, __lhs));
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>
operator+(_CharT __lhs, basic_string<_CharT,_Traits,_Allocator>&& __rhs)
{
    __rhs.insert(__rhs.begin(), __lhs);
    return _VSTD::move(__rhs);
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>
operator+(basic_string<_CharT, _Traits, _Allocator>&& __lhs, const _CharT* __rhs)
{
    return _VSTD::move(__lhs.append(__rhs));
}

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
basic_string<_CharT, _Traits, _Allocator>
operator+(basic_string<_CharT, _Traits, _Allocator>&& __lhs, _CharT __rhs)
{
    __lhs.push_back(__rhs);
    return _VSTD::move(__lhs);
}

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES

// swap

template<class _CharT, class _Traits, class _Allocator>
_LIBCPP_INLINE_VISIBILITY inline
void
swap(basic_string<_CharT, _Traits, _Allocator>& __lhs,
     basic_string<_CharT, _Traits, _Allocator>& __rhs)
     _NOEXCEPT_(_NOEXCEPT_(__lhs.swap(__rhs)))
{
    __lhs.swap(__rhs);
}

#ifndef _LIBCPP_HAS_NO_UNICODE_CHARS

typedef basic_string<char16_t> u16string;
typedef basic_string<char32_t> u32string;

#endif  // _LIBCPP_HAS_NO_UNICODE_CHARS

int                stoi  (const string& __str, size_t* __idx = 0, int __base = 10);
long               stol  (const string& __str, size_t* __idx = 0, int __base = 10);
unsigned long      stoul (const string& __str, size_t* __idx = 0, int __base = 10);
long long          stoll (const string& __str, size_t* __idx = 0, int __base = 10);
unsigned long long stoull(const string& __str, size_t* __idx = 0, int __base = 10);

float       stof (const string& __str, size_t* __idx = 0);
double      stod (const string& __str, size_t* __idx = 0);
long double stold(const string& __str, size_t* __idx = 0);

string to_string(int __val);
string to_string(unsigned __val);
string to_string(long __val);
string to_string(unsigned long __val);
string to_string(long long __val);
string to_string(unsigned long long __val);
string to_string(float __val);
string to_string(double __val);
string to_string(long double __val);

int                stoi  (const wstring& __str, size_t* __idx = 0, int __base = 10);
long               stol  (const wstring& __str, size_t* __idx = 0, int __base = 10);
unsigned long      stoul (const wstring& __str, size_t* __idx = 0, int __base = 10);
long long          stoll (const wstring& __str, size_t* __idx = 0, int __base = 10);
unsigned long long stoull(const wstring& __str, size_t* __idx = 0, int __base = 10);

float       stof (const wstring& __str, size_t* __idx = 0);
double      stod (const wstring& __str, size_t* __idx = 0);
long double stold(const wstring& __str, size_t* __idx = 0);

wstring to_wstring(int __val);
wstring to_wstring(unsigned __val);
wstring to_wstring(long __val);
wstring to_wstring(unsigned long __val);
wstring to_wstring(long long __val);
wstring to_wstring(unsigned long long __val);
wstring to_wstring(float __val);
wstring to_wstring(double __val);
wstring to_wstring(long double __val);

template<class _CharT, class _Traits, class _Allocator>
    const typename basic_string<_CharT, _Traits, _Allocator>::size_type
                   basic_string<_CharT, _Traits, _Allocator>::npos;

template<class _Ptr>
size_t _LIBCPP_INLINE_VISIBILITY __do_string_hash(_Ptr __p, _Ptr __e)
{
    typedef typename iterator_traits<_Ptr>::value_type value_type;
    return __murmur2_or_cityhash<size_t>()(__p, (__e-__p)*sizeof(value_type));
}

template<class _CharT, class _Traits, class _Allocator>
struct _LIBCPP_VISIBLE hash<basic_string<_CharT, _Traits, _Allocator> >
    : public unary_function<basic_string<_CharT, _Traits, _Allocator>, size_t>
{
    size_t
        operator()(const basic_string<_CharT, _Traits, _Allocator>& __val) const _NOEXCEPT;
};

template<class _CharT, class _Traits, class _Allocator>
size_t
hash<basic_string<_CharT, _Traits, _Allocator> >::operator()(
        const basic_string<_CharT, _Traits, _Allocator>& __val) const _NOEXCEPT
{
    return __do_string_hash(__val.data(), __val.data() + __val.size());
}

template<class _CharT, class _Traits, class _Allocator>
basic_ostream<_CharT, _Traits>&
operator<<(basic_ostream<_CharT, _Traits>& __os,
           const basic_string<_CharT, _Traits, _Allocator>& __str);

template<class _CharT, class _Traits, class _Allocator>
basic_istream<_CharT, _Traits>&
operator>>(basic_istream<_CharT, _Traits>& __is,
           basic_string<_CharT, _Traits, _Allocator>& __str);

template<class _CharT, class _Traits, class _Allocator>
basic_istream<_CharT, _Traits>&
getline(basic_istream<_CharT, _Traits>& __is,
        basic_string<_CharT, _Traits, _Allocator>& __str, _CharT __dlm);

template<class _CharT, class _Traits, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
basic_istream<_CharT, _Traits>&
getline(basic_istream<_CharT, _Traits>& __is,
        basic_string<_CharT, _Traits, _Allocator>& __str);

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

template<class _CharT, class _Traits, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
basic_istream<_CharT, _Traits>&
getline(basic_istream<_CharT, _Traits>&& __is,
        basic_string<_CharT, _Traits, _Allocator>& __str, _CharT __dlm);

template<class _CharT, class _Traits, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
basic_istream<_CharT, _Traits>&
getline(basic_istream<_CharT, _Traits>&& __is,
        basic_string<_CharT, _Traits, _Allocator>& __str);

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES

_LIBCPP_EXTERN_TEMPLATE(class basic_string<char>)
_LIBCPP_EXTERN_TEMPLATE(class basic_string<wchar_t>)

extern template
    string
    operator+<char, char_traits<char>, allocator<char> >(char const*, string const&);

_LIBCPP_END_NAMESPACE_STD

#endif  // _LIBCPP_STRING