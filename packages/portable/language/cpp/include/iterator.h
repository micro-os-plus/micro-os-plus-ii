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

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_ITERATOR_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_ITERATOR_H_

#include "portable/core/include/OS_Defines.h"

#include "portable/language/cpp/include/internal/__config.h"
#include "portable/language/cpp/include/type_traits.h"
#include "portable/language/cpp/include/cstddef.h"
#include "portable/language/cpp/include/iosfwd.h"

namespace os
{
  namespace std
  {

    struct _LIBCPP_VISIBLE input_iterator_tag
    {

    };

    struct _LIBCPP_VISIBLE output_iterator_tag
    {

    };

    struct _LIBCPP_VISIBLE forward_iterator_tag : public input_iterator_tag
    {

    };

    struct _LIBCPP_VISIBLE bidirectional_iterator_tag : public forward_iterator_tag
    {

    };

    struct _LIBCPP_VISIBLE random_access_iterator_tag : public bidirectional_iterator_tag
    {

    };

    template<class _Tp>
      struct __has_iterator_category
      {
      private:
        struct __two
        {
          char __lx;
          char __lxx;
        };

#define TEST_THREE_POINTS __test(...)
        template<class _Up>
          static __two TEST_THREE_POINTS;

          template<class _Up>
          static char __test(typename _Up::iterator_category* = 0);

        public:
          static const bool value = sizeof(__test<_Tp>(0)) == 1;
        };

    template<class _Iter, bool>
      struct ____iterator_traits
      {

      };

    template<class _Iter>
      struct ____iterator_traits<_Iter, true>
      {
        typedef typename _Iter::difference_type difference_type;
        typedef typename _Iter::value_type value_type;
        typedef typename _Iter::pointer pointer;
        typedef typename _Iter::reference reference;
        typedef typename _Iter::iterator_category iterator_category;
      };

    template<class _Iter, bool>
      struct __iterator_traits
      {

      };

    template<class _Iter>
      struct __iterator_traits<_Iter, true> : ____iterator_traits<_Iter,
          is_convertible<typename _Iter::iterator_category, input_iterator_tag>::value
              || is_convertible<typename _Iter::iterator_category,
                  output_iterator_tag>::value>
      {

      };

    // iterator_traits<Iterator> will only have the nested types if Iterator::iterator_category
    //    exists.  Else iterator_traits<Iterator> will be an empty class.  This is a
    //    conforming extension which allows some programs to compile and behave as
    //    the client expects instead of failing at compile time.

    template<class _Iter>
      struct _LIBCPP_VISIBLE iterator_traits : __iterator_traits<_Iter,
          __has_iterator_category<_Iter>::value>
      {

      };

    template<class _Tp>
      struct _LIBCPP_VISIBLE iterator_traits<_Tp*>
      {
        typedef ptrdiff_t difference_type;
        typedef typename remove_const<_Tp>::type value_type;
        typedef _Tp* pointer;
        typedef _Tp& reference;
        typedef random_access_iterator_tag iterator_category;
      };

    template<class _Tp, class _Up, bool = __has_iterator_category<
        iterator_traits<_Tp> >::value>
      struct __has_iterator_category_convertible_to : public integral_constant<
          bool,
          is_convertible<typename iterator_traits<_Tp>::iterator_category, _Up>::value>
      {

      };

    template<class _Tp, class _Up>
      struct __has_iterator_category_convertible_to<_Tp, _Up, false> : public false_type
      {

      };

    template<class _Tp>
      struct __is_input_iterator : public __has_iterator_category_convertible_to<
          _Tp, input_iterator_tag>
      {

      };

    template<class _Tp>
      struct __is_forward_iterator : public __has_iterator_category_convertible_to<
          _Tp, forward_iterator_tag>
      {

      };

    template<class _Tp>
      struct __is_bidirectional_iterator : public __has_iterator_category_convertible_to<
          _Tp, bidirectional_iterator_tag>
      {

      };

    template<class _Tp>
      struct __is_random_access_iterator : public __has_iterator_category_convertible_to<
          _Tp, random_access_iterator_tag>
      {

      };

    template<class _Category, class _Tp, class _Distance = ptrdiff_t,
        class _Pointer = _Tp*, class _Reference = _Tp&>
      struct _LIBCPP_VISIBLE iterator
      {
        typedef _Tp value_type;
        typedef _Distance difference_type;
        typedef _Pointer pointer;
        typedef _Reference reference;
        typedef _Category iterator_category;
      };

    template<class _InputIter>
      inline _LIBCPP_INLINE_VISIBILITY
      void
      __advance(_InputIter& __i,
          typename iterator_traits<_InputIter>::difference_type __n,
          input_iterator_tag)
      {
        for (; __n > 0; --__n)
          ++__i;
      }

    template<class _BiDirIter>
      inline _LIBCPP_INLINE_VISIBILITY
      void
      __advance(_BiDirIter& __i,
          typename iterator_traits<_BiDirIter>::difference_type __n,
          bidirectional_iterator_tag)
      {
        if (__n >= 0)
          for (; __n > 0; --__n)
            ++__i;
        else
          for (; __n < 0; ++__n)
            --__i;
      }

    template<class _RandIter>
      inline _LIBCPP_INLINE_VISIBILITY
      void
      __advance(_RandIter& __i,
          typename iterator_traits<_RandIter>::difference_type __n,
          random_access_iterator_tag)
      {
        __i += __n;
      }

    template<class _InputIter>
      inline _LIBCPP_INLINE_VISIBILITY
      void
      advance(_InputIter& __i,
          typename iterator_traits<_InputIter>::difference_type __n)
      {
        __advance(__i, __n,
            typename iterator_traits<_InputIter>::iterator_category());
      }

    template<class _InputIter>
      inline _LIBCPP_INLINE_VISIBILITY
      typename iterator_traits<_InputIter>::difference_type
      __distance(_InputIter __first, _InputIter __last, input_iterator_tag)
        {
          typename iterator_traits<_InputIter>::difference_type __r(0);
          for (; __first != __last; ++__first)
          ++__r;
          return __r;
        }

    template<class _RandIter>
      inline _LIBCPP_INLINE_VISIBILITY
      typename iterator_traits<_RandIter>::difference_type
      __distance(_RandIter __first, _RandIter __last, random_access_iterator_tag)
        {
          return __last - __first;
        }

    template<class _InputIter>
      inline _LIBCPP_INLINE_VISIBILITY
      typename iterator_traits<_InputIter>::difference_type
      distance(_InputIter __first, _InputIter __last)
        {
          return __distance(__first, __last, typename iterator_traits<_InputIter>::iterator_category());
        }

    template<class _ForwardIter>
      inline _LIBCPP_INLINE_VISIBILITY
      _ForwardIter
      next(_ForwardIter __x,
          typename iterator_traits<_ForwardIter>::difference_type __n = 1,
          typename enable_if<__is_forward_iterator<_ForwardIter>::value>::type* =
              0)
      {
        _VSTD::advance(__x, __n);
        return __x;
      }

    template<class _BidiretionalIter>
      inline _LIBCPP_INLINE_VISIBILITY
      _BidiretionalIter
      prev(_BidiretionalIter __x,
          typename iterator_traits<_BidiretionalIter>::difference_type __n = 1,
          typename enable_if<
              __is_bidirectional_iterator<_BidiretionalIter>::value>::type* = 0)
      {
        _VSTD::advance(__x, -__n);
        return __x;
      }

    template<class _Iter>
      class _LIBCPP_VISIBLE reverse_iterator : public iterator<
          typename iterator_traits<_Iter>::iterator_category,
          typename iterator_traits<_Iter>::value_type,
          typename iterator_traits<_Iter>::difference_type,
          typename iterator_traits<_Iter>::pointer,
          typename iterator_traits<_Iter>::reference>
      {
      private:
        mutable _Iter __t;
      protected:
        _Iter current;
      public:
        typedef _Iter iterator_type;
        typedef typename iterator_traits<_Iter>::difference_type difference_type;
        typedef typename iterator_traits<_Iter>::reference reference;
        typedef typename iterator_traits<_Iter>::pointer pointer;

        _LIBCPP_INLINE_VISIBILITY
        reverse_iterator()
            : current()
        {

        }

        _LIBCPP_INLINE_VISIBILITY explicit
        reverse_iterator(_Iter __x)
            : __t(__x), current(__x)
        {

        }

        template<class _Up>
          _LIBCPP_INLINE_VISIBILITY
          reverse_iterator(const reverse_iterator<_Up>& __u)
              : __t(__u.base()), current(__u.base())
          {

          }

        _LIBCPP_INLINE_VISIBILITY _Iter
        base() const
        {
          return current;
        }

        _LIBCPP_INLINE_VISIBILITY reference
        operator*() const
        {
          __t = current;
          return *--__t;
        }

        _LIBCPP_INLINE_VISIBILITY pointer
        operator->() const
        {
          return &(operator*());
        }

        _LIBCPP_INLINE_VISIBILITY reverse_iterator&
        operator++()
        {
          --current;
          return *this;
        }

        _LIBCPP_INLINE_VISIBILITY reverse_iterator
        operator++(int)
        {
          reverse_iterator __tmp(*this);
          --current;
          return __tmp;
        }

        _LIBCPP_INLINE_VISIBILITY reverse_iterator&
        operator--()
        {
          ++current;
          return *this;
        }

        _LIBCPP_INLINE_VISIBILITY reverse_iterator
        operator--(int)
        {
          reverse_iterator __tmp(*this);
          ++current;
          return __tmp;
        }

        _LIBCPP_INLINE_VISIBILITY reverse_iterator
        operator+(difference_type __n) const
        {
          return reverse_iterator(current - __n);
        }

        _LIBCPP_INLINE_VISIBILITY reverse_iterator&
        operator+=(difference_type __n)
        {
          current -= __n;
          return *this;
        }

        _LIBCPP_INLINE_VISIBILITY reverse_iterator
        operator-(difference_type __n) const
        {
          return reverse_iterator(current + __n);
        }

        _LIBCPP_INLINE_VISIBILITY reverse_iterator&
        operator-=(difference_type __n)
        {
          current += __n;
          return *this;
        }

        _LIBCPP_INLINE_VISIBILITY reference
        operator[](difference_type __n) const
        {
          return current[-__n - 1];
        }
      };

    template<class _Iter1, class _Iter2>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      operator==(const reverse_iterator<_Iter1>& __x,
          const reverse_iterator<_Iter2>& __y)
      {
        return __x.base() == __y.base();
      }

    template<class _Iter1, class _Iter2>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      operator<(const reverse_iterator<_Iter1>& __x,
          const reverse_iterator<_Iter2>& __y)
      {
        return __x.base() > __y.base();
      }

    template<class _Iter1, class _Iter2>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      operator!=(const reverse_iterator<_Iter1>& __x,
          const reverse_iterator<_Iter2>& __y)
      {
        return __x.base() != __y.base();
      }

    template<class _Iter1, class _Iter2>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      operator>(const reverse_iterator<_Iter1>& __x,
          const reverse_iterator<_Iter2>& __y)
      {
        return __x.base() < __y.base();
      }

    template<class _Iter1, class _Iter2>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      operator>=(const reverse_iterator<_Iter1>& __x,
          const reverse_iterator<_Iter2>& __y)
      {
        return __x.base() <= __y.base();
      }

    template<class _Iter1, class _Iter2>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      operator<=(const reverse_iterator<_Iter1>& __x,
          const reverse_iterator<_Iter2>& __y)
      {
        return __x.base() >= __y.base();
      }

    template<class _Iter1, class _Iter2>
      inline _LIBCPP_INLINE_VISIBILITY
      typename reverse_iterator<_Iter1>::difference_type
      operator-(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
        {
          return __y.base() - __x.base();
        }

    template<class _Iter>
      inline _LIBCPP_INLINE_VISIBILITY
      reverse_iterator<_Iter>
      operator+(typename reverse_iterator<_Iter>::difference_type __n,
          const reverse_iterator<_Iter>& __x)
      {
        return reverse_iterator<_Iter>(__x.base() - __n);
      }

    template<class _Container>
      class _LIBCPP_VISIBLE back_insert_iterator : public iterator<
          output_iterator_tag, void, void, void,
          back_insert_iterator<_Container>&>
      {
      protected:
        _Container* container;
      public:
        typedef _Container container_type;

        _LIBCPP_INLINE_VISIBILITY explicit
        back_insert_iterator(_Container& __x)
            : container(&__x)
        {
          ;
        }

        _LIBCPP_INLINE_VISIBILITY
        back_insert_iterator&
        operator=(const typename _Container::value_type& __value_)
        {
          container->push_back(__value_);
          return *this;
        }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
        _LIBCPP_INLINE_VISIBILITY
        back_insert_iterator&
        operator=(typename _Container::value_type&& __value_)
          {
            container->push_back(_VSTD::move(__value_));
            return *this;
          }
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES

            _LIBCPP_INLINE_VISIBILITY
            back_insert_iterator&
            operator*()
              {
                return *this;
              }

            _LIBCPP_INLINE_VISIBILITY
            back_insert_iterator&
            operator++()
              {
                return *this;
              }

            _LIBCPP_INLINE_VISIBILITY
            back_insert_iterator
            operator++(int)
              {
                return *this;
              }
          };

    template<class _Container>
      inline _LIBCPP_INLINE_VISIBILITY
      back_insert_iterator<_Container>
      back_inserter(_Container& __x)
      {
        return back_insert_iterator<_Container>(__x);
      }

    template<class _Container>
      class _LIBCPP_VISIBLE front_insert_iterator : public iterator<
          output_iterator_tag, void, void, void,
          front_insert_iterator<_Container>&>
      {
      protected:
        _Container* container;

      public:
        typedef _Container container_type;

        _LIBCPP_INLINE_VISIBILITY explicit
        front_insert_iterator(_Container& __x)
            : container(&__x)
        {
          ;
        }

        _LIBCPP_INLINE_VISIBILITY
        front_insert_iterator&
        operator=(const typename _Container::value_type& __value_)
        {
          container->push_front(__value_);
          return *this;
        }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
        _LIBCPP_INLINE_VISIBILITY
        front_insert_iterator&
        operator=(typename _Container::value_type&& __value_)
          {
            container->push_front(_VSTD::move(__value_));
            return *this;
          }
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
            _LIBCPP_INLINE_VISIBILITY
            front_insert_iterator&
            operator*()
              {
                return *this;
              }

            _LIBCPP_INLINE_VISIBILITY
            front_insert_iterator&
            operator++()
              {
                return *this;
              }

            _LIBCPP_INLINE_VISIBILITY
            front_insert_iterator
            operator++(int)
              {
                return *this;
              }
          };

    template<class _Container>
      inline _LIBCPP_INLINE_VISIBILITY
      front_insert_iterator<_Container>
      front_inserter(_Container& __x)
      {
        return front_insert_iterator<_Container>(__x);
      }

    template<class _Container>
      class _LIBCPP_VISIBLE insert_iterator : public iterator<
          output_iterator_tag, void, void, void, insert_iterator<_Container>&>
      {
      protected:
        _Container* container;
        typename _Container::iterator iter;
      public:
        typedef _Container container_type;

        _LIBCPP_INLINE_VISIBILITY
        insert_iterator(_Container& __x, typename _Container::iterator __i)
            : container(&__x), iter(__i)
        {
          ;
        }

        _LIBCPP_INLINE_VISIBILITY insert_iterator&
        operator=(const typename _Container::value_type& __value_)
        {
          iter = container->insert(iter, __value_);
          ++iter;
          return *this;
        }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
        _LIBCPP_INLINE_VISIBILITY insert_iterator&
        operator=(typename _Container::value_type&& __value_)
          { iter = container->insert(iter, _VSTD::move(__value_)); ++iter; return *this;}
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
        _LIBCPP_INLINE_VISIBILITY insert_iterator&
        operator*()
          {
            return *this;
          }

        _LIBCPP_INLINE_VISIBILITY insert_iterator&
        operator++()
          {
            return *this;
          }

        _LIBCPP_INLINE_VISIBILITY insert_iterator&
        operator++(int)
          {
            return *this;
          }
      };

    template<class _Container>
      inline _LIBCPP_INLINE_VISIBILITY
      insert_iterator<_Container>
      inserter(_Container& __x, typename _Container::iterator __i)
      {
        return insert_iterator<_Container>(__x, __i);
      }

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
    template<class _Tp, class _CharT = char,
        class _Traits = char_traits<_CharT>, class _Distance = ptrdiff_t>
      class _LIBCPP_VISIBLE istream_iterator : public iterator<
          input_iterator_tag, _Tp, _Distance, const _Tp*, const _Tp&>
      {
      public:
        typedef _CharT char_type;
        typedef _Traits traits_type;
        typedef basic_istream<_CharT, _Traits> istream_type;
      private:
        istream_type* __in_stream_;
        _Tp __value_;
      public:
        _LIBCPP_INLINE_VISIBILITY
        istream_iterator()
            : __in_stream_(0)
        {
          ;
        }

        _LIBCPP_INLINE_VISIBILITY
        istream_iterator(istream_type& __s)
            : __in_stream_(&__s)
        {
          if (!(*__in_stream_ >> __value_))
            __in_stream_ = 0;
        }

        _LIBCPP_INLINE_VISIBILITY const _Tp&
        operator*() const
        {
          return __value_;
        }

        _LIBCPP_INLINE_VISIBILITY const _Tp*
        operator->() const
        {
          return &(operator*());
        }

        _LIBCPP_INLINE_VISIBILITY istream_iterator&
        operator++()
        {
          if (!(*__in_stream_ >> __value_))
            __in_stream_ = 0;
          return *this;
        }

        _LIBCPP_INLINE_VISIBILITY istream_iterator
        operator++(int)
        {
          istream_iterator __t(*this);
          ++(*this);
          return __t;
        }

        friend _LIBCPP_INLINE_VISIBILITY
        bool
        operator==(const istream_iterator& __x, const istream_iterator& __y)
        {
          return __x.__in_stream_ == __y.__in_stream_;
        }

        friend _LIBCPP_INLINE_VISIBILITY
        bool
        operator!=(const istream_iterator& __x, const istream_iterator& __y)
        {
          return !(__x == __y);
        }
      };
#endif

    template<class _Tp, class _CharT = char, class _Traits = char_traits<_CharT> >
      class _LIBCPP_VISIBLE ostream_iterator : public iterator<
          output_iterator_tag, void, void, void, void>
      {
      public:
        typedef _CharT char_type;
        typedef _Traits traits_type;
        typedef basic_ostream<_CharT, _Traits> ostream_type;
      private:
        ostream_type* __out_stream_;
        const char_type* __delim_;
      public:
        _LIBCPP_INLINE_VISIBILITY
        ostream_iterator(ostream_type& __s)
            : __out_stream_(&__s), __delim_(0)
        {
          ;
        }

        _LIBCPP_INLINE_VISIBILITY
        ostream_iterator(ostream_type& __s, const _CharT* __delimiter)
            : __out_stream_(&__s), __delim_(__delimiter)
        {
          ;
        }

        _LIBCPP_INLINE_VISIBILITY ostream_iterator&
        operator=(const _Tp& __value_)
        {
          *__out_stream_ << __value_;
          if (__delim_)
            *__out_stream_ << __delim_;
          return *this;
        }

        _LIBCPP_INLINE_VISIBILITY ostream_iterator&
        operator*()
        {
          return *this;
        }

        _LIBCPP_INLINE_VISIBILITY ostream_iterator&
        operator++()
        {
          return *this;
        }

        _LIBCPP_INLINE_VISIBILITY ostream_iterator&
        operator++(int)
        {
          return *this;
        }
      };

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
    template<class _CharT, class _Traits>
      class _LIBCPP_VISIBLE istreambuf_iterator : public iterator<
          input_iterator_tag, _CharT, typename _Traits::off_type, _CharT*,
          _CharT>
      {
      public:
        typedef _CharT char_type;
        typedef _Traits traits_type;
        typedef typename _Traits::int_type int_type;
        typedef basic_streambuf<_CharT, _Traits> streambuf_type;
        typedef basic_istream<_CharT, _Traits> istream_type;
      private:
        mutable streambuf_type* __sbuf_;

        class __proxy
        {
          char_type __keep_;
          streambuf_type* __sbuf_;_LIBCPP_INLINE_VISIBILITY
          __proxy(char_type __c, streambuf_type* __s)
              : __keep_(__c), __sbuf_(__s)
          {
            ;
          }

          friend class istreambuf_iterator;
        public:
          _LIBCPP_INLINE_VISIBILITY char_type
          operator*() const
          {
            return __keep_;
          }
        };

        _LIBCPP_INLINE_VISIBILITY
        bool
        __test_for_eof() const
        {
          if (__sbuf_
              && traits_type::eq_int_type(__sbuf_->sgetc(), traits_type::eof()))
            __sbuf_ = 0;
          return __sbuf_ == 0;
        }

      public:
        _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
        istreambuf_iterator() _NOEXCEPT
            : __sbuf_(0)
        {
          ;
        }

        _LIBCPP_INLINE_VISIBILITY
        istreambuf_iterator(istream_type& __s) _NOEXCEPT
            : __sbuf_(__s.rdbuf())
        {
          ;
        }

        _LIBCPP_INLINE_VISIBILITY
        istreambuf_iterator(streambuf_type* __s) _NOEXCEPT
            : __sbuf_(__s)
        {
          ;
        }

        _LIBCPP_INLINE_VISIBILITY
        istreambuf_iterator(const __proxy& __p) _NOEXCEPT
        : __sbuf_(__p.__sbuf_)
          {
            ;
          }

        _LIBCPP_INLINE_VISIBILITY
        char_type operator*() const
          {
            return static_cast<char_type>(__sbuf_->sgetc());
          }

        _LIBCPP_INLINE_VISIBILITY char_type* operator->() const
          {
            return nullptr;
          }

        _LIBCPP_INLINE_VISIBILITY istreambuf_iterator& operator++()
          {
            __sbuf_->sbumpc();
            return *this;
          }

        _LIBCPP_INLINE_VISIBILITY __proxy operator++(int)
          {
            return __proxy(__sbuf_->sbumpc(), __sbuf_);
          }

        _LIBCPP_INLINE_VISIBILITY bool equal(const istreambuf_iterator& __b)const
        {
          return __test_for_eof() == __b.__test_for_eof();
        }
};

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      operator==(const istreambuf_iterator<_CharT, _Traits>& __a,
          const istreambuf_iterator<_CharT, _Traits>& __b)
      {
        return __a.equal(__b);
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      operator!=(const istreambuf_iterator<_CharT, _Traits>& __a,
          const istreambuf_iterator<_CharT, _Traits>& __b)
      {
        return !__a.equal(__b);
      }
#endif

    template<class _CharT, class _Traits>
      class _LIBCPP_VISIBLE ostreambuf_iterator : public iterator<
          output_iterator_tag, void, void, void, void>
      {
      public:
        typedef _CharT char_type;
        typedef _Traits traits_type;
        typedef basic_streambuf<_CharT, _Traits> streambuf_type;
        typedef basic_ostream<_CharT, _Traits> ostream_type;
      private:
        streambuf_type* __sbuf_;
      public:
        _LIBCPP_INLINE_VISIBILITY
        ostreambuf_iterator(ostream_type& __s) _NOEXCEPT
            : __sbuf_(__s.rdbuf())
        {
          ;
        }

        _LIBCPP_INLINE_VISIBILITY
        ostreambuf_iterator(streambuf_type* __s) _NOEXCEPT
            : __sbuf_(__s)
        {
          ;
        }

        _LIBCPP_INLINE_VISIBILITY ostreambuf_iterator&
        operator=(_CharT __c)
        {
          if ((__sbuf_ != 0)
              && traits_type::eq_int_type(__sbuf_->sputc(__c),
                  traits_type::eof()))
            __sbuf_ = 0;
          return *this;
        }

        _LIBCPP_INLINE_VISIBILITY ostreambuf_iterator&
        operator*()
        {
          return *this;
        }

        _LIBCPP_INLINE_VISIBILITY ostreambuf_iterator&
        operator++()
        {
          return *this;
        }

        _LIBCPP_INLINE_VISIBILITY ostreambuf_iterator&
        operator++(int)
        {
          return *this;
        }

        _LIBCPP_INLINE_VISIBILITY bool
        failed() const _NOEXCEPT
        {
          return __sbuf_ == 0;
        }

#if !defined(__APPLE__) || \
    (defined(__MAC_OS_X_VERSION_MIN_REQUIRED) && __MAC_OS_X_VERSION_MIN_REQUIRED > __MAC_10_8) || \
    (defined(__IPHONE_OS_VERSION_MIN_REQUIRED) && __IPHONE_OS_VERSION_MIN_REQUIRED > __IPHONE_6_0)

        template<class _Ch, class _Tr>
        friend _LIBCPP_HIDDEN
        ostreambuf_iterator<_Ch, _Tr>
        __pad_and_output(ostreambuf_iterator<_Ch, _Tr> __s, const _Ch* __ob,
            const _Ch* __op, const _Ch* __oe, ios_base& __iob, _Ch __fl);
#endif
      };

    template<class _Iter>
      class _LIBCPP_VISIBLE move_iterator
      {
      private:
        _Iter __i;
      public:
        typedef _Iter iterator_type;
        typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
        typedef typename iterator_traits<iterator_type>::value_type value_type;
        typedef typename iterator_traits<iterator_type>::difference_type difference_type;
        typedef typename iterator_traits<iterator_type>::pointer pointer;
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
        typedef value_type&& reference;
#else
        typedef typename iterator_traits<iterator_type>::reference reference;
#endif

        _LIBCPP_INLINE_VISIBILITY
        move_iterator()
        : __i()
          {
            ;
          }

        _LIBCPP_INLINE_VISIBILITY explicit
        move_iterator(_Iter __x)
        : __i(__x)
          {
            ;
          }

        template<class _Up>
        _LIBCPP_INLINE_VISIBILITY
        move_iterator(const move_iterator<_Up>& __u)
        : __i(__u.base())
          {
            ;
          }

        _LIBCPP_INLINE_VISIBILITY _Iter
        base() const
          {
            return __i;
          }

        _LIBCPP_INLINE_VISIBILITY reference
        operator*() const
          {
            return static_cast<reference>(*__i);
          }

        _LIBCPP_INLINE_VISIBILITY pointer
        operator->() const
          {
            typename iterator_traits<iterator_type>::reference __ref = *__i;
            return &__ref;
          }

        _LIBCPP_INLINE_VISIBILITY move_iterator&
        operator++()
          {
            ++__i;
            return *this;
          }

        _LIBCPP_INLINE_VISIBILITY move_iterator
        operator++(int)
          {
            move_iterator __tmp(*this);
            ++__i;
            return __tmp;
          }

        _LIBCPP_INLINE_VISIBILITY move_iterator&
        operator--()
          {
            --__i;
            return *this;
          }

        _LIBCPP_INLINE_VISIBILITY move_iterator
        operator--(int)
          {
            move_iterator __tmp(*this);
            --__i;
            return __tmp;
          }

        _LIBCPP_INLINE_VISIBILITY move_iterator
        operator+(difference_type __n) const
          {
            return move_iterator(__i + __n);
          }

        _LIBCPP_INLINE_VISIBILITY move_iterator&
        operator+=(difference_type __n)
          {
            __i += __n;
            return *this;
          }

        _LIBCPP_INLINE_VISIBILITY move_iterator
        operator-(difference_type __n) const
          {
            return move_iterator(__i - __n);
          }

        _LIBCPP_INLINE_VISIBILITY move_iterator&
        operator-=(difference_type __n)
          {
            __i -= __n;
            return *this;
          }

        _LIBCPP_INLINE_VISIBILITY reference
        operator[](difference_type __n) const
          {
            return static_cast<reference>(__i[__n]);
          }
      };

    template<class _Iter1, class _Iter2>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      operator==(const move_iterator<_Iter1>& __x,
          const move_iterator<_Iter2>& __y)
      {
        return __x.base() == __y.base();
      }

    template<class _Iter1, class _Iter2>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      operator<(const move_iterator<_Iter1>& __x,
          const move_iterator<_Iter2>& __y)
      {
        return __x.base() < __y.base();
      }

    template<class _Iter1, class _Iter2>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      operator!=(const move_iterator<_Iter1>& __x,
          const move_iterator<_Iter2>& __y)
      {
        return __x.base() != __y.base();
      }

    template<class _Iter1, class _Iter2>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      operator>(const move_iterator<_Iter1>& __x,
          const move_iterator<_Iter2>& __y)
      {
        return __x.base() > __y.base();
      }

    template<class _Iter1, class _Iter2>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      operator>=(const move_iterator<_Iter1>& __x,
          const move_iterator<_Iter2>& __y)
      {
        return __x.base() >= __y.base();
      }

    template<class _Iter1, class _Iter2>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      operator<=(const move_iterator<_Iter1>& __x,
          const move_iterator<_Iter2>& __y)
      {
        return __x.base() <= __y.base();
      }

    template<class _Iter1, class _Iter2>
      inline _LIBCPP_INLINE_VISIBILITY
      typename move_iterator<_Iter1>::difference_type
      operator-(const move_iterator<_Iter1>& __x, const move_iterator<_Iter2>& __y)
        {
          return __x.base() - __y.base();
        }

    template<class _Iter>
      inline _LIBCPP_INLINE_VISIBILITY
      move_iterator<_Iter>
      operator+(typename move_iterator<_Iter>::difference_type __n,
          const move_iterator<_Iter>& __x)
      {
        return move_iterator<_Iter>(__x.base() + __n);
      }

    template<class _Iter>
      inline _LIBCPP_INLINE_VISIBILITY
      move_iterator<_Iter>
      make_move_iterator(const _Iter& __i)
      {
        return move_iterator<_Iter>(__i);
      }

    // __wrap_iter

    template<class _Iter>
      class __wrap_iter;

    template<class _Iter1, class _Iter2>
      _LIBCPP_INLINE_VISIBILITY
      bool
      operator==(const __wrap_iter <_Iter1>&, const __wrap_iter <_Iter2>&)
          _NOEXCEPT;

    template<class _Iter1, class _Iter2>
      _LIBCPP_INLINE_VISIBILITY
      bool
      operator<(const __wrap_iter <_Iter1>&, const __wrap_iter <_Iter2>&)
          _NOEXCEPT;

    template<class _Iter1, class _Iter2>
      _LIBCPP_INLINE_VISIBILITY
      bool
      operator!=(const __wrap_iter <_Iter1>&, const __wrap_iter <_Iter2>&)
          _NOEXCEPT;

    template<class _Iter1, class _Iter2>
      _LIBCPP_INLINE_VISIBILITY
      bool
      operator>(const __wrap_iter <_Iter1>&, const __wrap_iter <_Iter2>&)
          _NOEXCEPT;

    template<class _Iter1, class _Iter2>
      _LIBCPP_INLINE_VISIBILITY
      bool
      operator>=(const __wrap_iter <_Iter1>&, const __wrap_iter <_Iter2>&)
          _NOEXCEPT;

    template<class _Iter1, class _Iter2>
      _LIBCPP_INLINE_VISIBILITY
      bool
      operator<=(const __wrap_iter <_Iter1>&, const __wrap_iter <_Iter2>&)
          _NOEXCEPT;

    template<class _Iter1, class _Iter2>
      _LIBCPP_INLINE_VISIBILITY
      typename __wrap_iter<_Iter1>::difference_type
      operator-(const __wrap_iter <_Iter1>&, const __wrap_iter <_Iter2>&)
          _NOEXCEPT;

    template<class _Iter>
      _LIBCPP_INLINE_VISIBILITY
      __wrap_iter<_Iter>
      operator+(typename __wrap_iter<_Iter>::difference_type,
          __wrap_iter <_Iter>) _NOEXCEPT;

    template<class _Ip, class _Op>
      _Op _LIBCPP_INLINE_VISIBILITY
      copy(_Ip, _Ip, _Op);

    template<class _B1, class _B2>
      _B2 _LIBCPP_INLINE_VISIBILITY
      copy_backward(_B1, _B1, _B2);

    template<class _Ip, class _Op>
      _Op _LIBCPP_INLINE_VISIBILITY
      move(_Ip, _Ip, _Op);

    template<class _B1, class _B2>
      _B2 _LIBCPP_INLINE_VISIBILITY
      move_backward(_B1, _B1, _B2);

    template<class _Tp>
      _LIBCPP_INLINE_VISIBILITY
      typename enable_if<is_trivially_copy_assignable<_Tp>::value, _Tp*>::type
      __unwrap_iter(__wrap_iter <_Tp*>);

    template<class _Iter>
      class __wrap_iter
      {
      public:
        typedef _Iter iterator_type;
        typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
        typedef typename iterator_traits<iterator_type>::value_type value_type;
        typedef typename iterator_traits<iterator_type>::difference_type difference_type;
        typedef typename iterator_traits<iterator_type>::pointer pointer;
        typedef typename iterator_traits<iterator_type>::reference reference;
      private:
        iterator_type __i;
      public:
        _LIBCPP_INLINE_VISIBILITY
        __wrap_iter() _NOEXCEPT
        {
#if _LIBCPP_DEBUG_LEVEL >= 2
          __get_db()->__insert_i(this);
#endif
        }
        template<class _Up>
          _LIBCPP_INLINE_VISIBILITY
          __wrap_iter(const __wrap_iter <_Up>& __u,
              typename enable_if<is_convertible<_Up, iterator_type>::value>::type* =
                  0) _NOEXCEPT
              : __i(__u.base())
          {
#if _LIBCPP_DEBUG_LEVEL >= 2
            __get_db()->__iterator_copy(this, &__u);
#endif
          }
#if _LIBCPP_DEBUG_LEVEL >= 2
        _LIBCPP_INLINE_VISIBILITY
        __wrap_iter(const __wrap_iter& __x)
        : __i(__x.base())
          {
            __get_db()->__iterator_copy(this, &__x);
          }
        _LIBCPP_INLINE_VISIBILITY
        __wrap_iter& operator=(const __wrap_iter& __x)
          {
            if (this != &__x)
              {
                __get_db()->__iterator_copy(this, &__x);
                __i = __x.__i;
              }
            return *this;
          }
        _LIBCPP_INLINE_VISIBILITY
        ~__wrap_iter()
          {
            __get_db()->__erase_i(this);
          }
#endif

        _LIBCPP_INLINE_VISIBILITY
        reference
        operator*() const _NOEXCEPT
        {
#if _LIBCPP_DEBUG_LEVEL >= 2
          _LIBCPP_ASSERT(__get_const_db()->__dereferenceable(this),
              "Attempted to dereference a non-dereferenceable iterator");
#endif
          return *__i;
        }

        _LIBCPP_INLINE_VISIBILITY
        pointer
        operator->() const _NOEXCEPT
        {
          return &(operator*());
        }

        _LIBCPP_INLINE_VISIBILITY
        __wrap_iter&
        operator++() _NOEXCEPT
        {
#if _LIBCPP_DEBUG_LEVEL >= 2
          _LIBCPP_ASSERT(__get_const_db()->__dereferenceable(this),
              "Attempted to increment non-incrementable iterator");
#endif
          ++__i;
          return *this;
        }

        _LIBCPP_INLINE_VISIBILITY
        __wrap_iter
        operator++(int) _NOEXCEPT
        {
          __wrap_iter                  __tmp(*this); ++(*this);
          return __tmp;
        }

      _LIBCPP_INLINE_VISIBILITY
      __wrap_iter&
      operator--() _NOEXCEPT
        {
#if _LIBCPP_DEBUG_LEVEL >= 2
          _LIBCPP_ASSERT(__get_const_db()->__decrementable(this),
              "Attempted to decrement non-decrementable iterator");
#endif
          --__i;
          return *this;
        }

      _LIBCPP_INLINE_VISIBILITY __wrap_iter operator--(int) _NOEXCEPT
        { __wrap_iter __tmp(*this); --(*this); return __tmp;}

      _LIBCPP_INLINE_VISIBILITY __wrap_iter operator+ (difference_type __n) const _NOEXCEPT
        { __wrap_iter __w(*this); __w += __n; return __w;}

      _LIBCPP_INLINE_VISIBILITY __wrap_iter& operator+=(difference_type __n) _NOEXCEPT
        {
#if _LIBCPP_DEBUG_LEVEL >= 2
          _LIBCPP_ASSERT(__get_const_db()->__addable(this, __n),
              "Attempted to add/subtract iterator outside of valid range");
#endif
          __i += __n;
          return *this;
        }

      _LIBCPP_INLINE_VISIBILITY __wrap_iter operator- (difference_type __n) const _NOEXCEPT
        { return *this + (-__n);}

      _LIBCPP_INLINE_VISIBILITY __wrap_iter& operator-=(difference_type __n) _NOEXCEPT
        { *this += -__n; return *this;}

      _LIBCPP_INLINE_VISIBILITY reference operator[](difference_type __n) const _NOEXCEPT
        {
#if _LIBCPP_DEBUG_LEVEL >= 2
          _LIBCPP_ASSERT(__get_const_db()->__subscriptable(this, __n),
              "Attempted to subscript iterator outside of valid range");
#endif
          return __i[__n];
        }

      _LIBCPP_INLINE_VISIBILITY iterator_type base() const _NOEXCEPT
        { return __i;}

    private:
      _LIBCPP_INLINE_VISIBILITY __wrap_iter(iterator_type __x) _NOEXCEPT : __i(__x)
        {}
#if _LIBCPP_DEBUG_LEVEL >= 2
      _LIBCPP_INLINE_VISIBILITY __wrap_iter(const void* __p, iterator_type __x) : __i(__x)
        {
          __get_db()->__insert_ic(this, __p);
        }
#endif

      template <class _Up> friend class __wrap_iter;
      template <class _CharT, class _Traits, class _Alloc> friend class basic_string;
      template <class _Tp, class _Alloc> friend class vector;

      template <class _Iter1, class _Iter2>
      friend
      bool
      operator==(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

      template <class _Iter1, class _Iter2>
      friend
      bool
      operator<(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

      template <class _Iter1, class _Iter2>
      friend
      bool
      operator!=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

      template <class _Iter1, class _Iter2>
      friend
      bool
      operator>(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

      template <class _Iter1, class _Iter2>
      friend
      bool
      operator>=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

      template <class _Iter1, class _Iter2>
      friend
      bool
      operator<=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

      template <class _Iter1, class _Iter2>
      friend
      typename __wrap_iter<_Iter1>::difference_type
      operator-(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

      template <class _Iter1>
      friend
      __wrap_iter<_Iter1>
      operator+(typename __wrap_iter<_Iter1>::difference_type, __wrap_iter<_Iter1>) _NOEXCEPT;

      template <class _Ip, class _Op> friend _Op copy(_Ip, _Ip, _Op);
      template <class _B1, class _B2> friend _B2 copy_backward(_B1, _B1, _B2);
      template <class _Ip, class _Op> friend _Op move(_Ip, _Ip, _Op);
      template <class _B1, class _B2> friend _B2 move_backward(_B1, _B1, _B2);

      template <class _Tp>
      friend
      typename enable_if
      <
      is_trivially_copy_assignable<_Tp>::value,
      _Tp*
      >::type
      __unwrap_iter(__wrap_iter<_Tp*>);
    };

    template<class _Iter1, class _Iter2>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      operator==(const __wrap_iter <_Iter1>& __x,
          const __wrap_iter <_Iter2>& __y) _NOEXCEPT
      {
#if _LIBCPP_DEBUG_LEVEL >= 2
        _LIBCPP_ASSERT(__get_const_db()->__comparable(&__x, &__y),
            "Attempted to compare incomparable iterators");
#endif
        return __x.base() == __y.base();
      }

    template<class _Iter1, class _Iter2>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      operator<(const __wrap_iter <_Iter1>& __x,
          const __wrap_iter <_Iter2>& __y) _NOEXCEPT
      {
#if _LIBCPP_DEBUG_LEVEL >= 2
        _LIBCPP_ASSERT(__get_const_db()->__comparable(&__x, &__y),
            "Attempted to compare incomparable iterators");
#endif
        return __x.base() < __y.base();
      }

    template<class _Iter1, class _Iter2>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      operator!=(const __wrap_iter <_Iter1>& __x,
          const __wrap_iter <_Iter2>& __y) _NOEXCEPT
      {
        return !(__x == __y);
      }

    template<class _Iter1, class _Iter2>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      operator>(const __wrap_iter <_Iter1>& __x,
          const __wrap_iter <_Iter2>& __y) _NOEXCEPT
      {
        return __y < __x;
      }

    template<class _Iter1, class _Iter2>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      operator>=(const __wrap_iter <_Iter1>& __x,
          const __wrap_iter <_Iter2>& __y) _NOEXCEPT
      {
        return !(__x < __y);
      }

    template<class _Iter1, class _Iter2>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      operator<=(const __wrap_iter <_Iter1>& __x,
          const __wrap_iter <_Iter2>& __y) _NOEXCEPT
      {
        return !(__y < __x);
      }

    template<class _Iter1>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      operator!=(const __wrap_iter <_Iter1>& __x,
          const __wrap_iter <_Iter1>& __y) _NOEXCEPT
      {
        return !(__x == __y);
      }

    template<class _Iter1>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      operator>(const __wrap_iter <_Iter1>& __x,
          const __wrap_iter <_Iter1>& __y) _NOEXCEPT
      {
        return __y < __x;
      }

    template<class _Iter1>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      operator>=(const __wrap_iter <_Iter1>& __x,
          const __wrap_iter <_Iter1>& __y) _NOEXCEPT
      {
        return !(__x < __y);
      }

    template<class _Iter1>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      operator<=(const __wrap_iter <_Iter1>& __x,
          const __wrap_iter <_Iter1>& __y) _NOEXCEPT
      {
        return !(__y < __x);
      }

    template<class _Iter1, class _Iter2>
      inline _LIBCPP_INLINE_VISIBILITY
      typename __wrap_iter<_Iter1>::difference_type
      operator-(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
        {
#if _LIBCPP_DEBUG_LEVEL >= 2
          _LIBCPP_ASSERT(__get_const_db()->__comparable(&__x, &__y),
              "Attempted to subtract incompatible iterators");
#endif
          return __x.base() - __y.base();
        }

    template<class _Iter>
      inline _LIBCPP_INLINE_VISIBILITY
      __wrap_iter<_Iter>
      operator+(typename __wrap_iter<_Iter>::difference_type __n,
          __wrap_iter <_Iter> __x) _NOEXCEPT
      {
        __x += __n;
        return __x;
      }

#ifdef _LIBCPP_DEBUG

// __debug_iter

    template <class _Container, class _Iter> class __debug_iter;

    template <class _Container, class _Iter1, class _Iter2>
    _LIBCPP_INLINE_VISIBILITY
    bool
    operator==(const __debug_iter<_Container, _Iter1>&, const __debug_iter<_Container, _Iter2>&);

    template <class _Container, class _Iter1, class _Iter2>
    _LIBCPP_INLINE_VISIBILITY
    bool
    operator<(const __debug_iter<_Container, _Iter1>&, const __debug_iter<_Container, _Iter2>&);

    template <class _Container, class _Iter1, class _Iter2>
    _LIBCPP_INLINE_VISIBILITY
    bool
    operator!=(const __debug_iter<_Container, _Iter1>&, const __debug_iter<_Container, _Iter2>&);

    template <class _Container, class _Iter1, class _Iter2>
    _LIBCPP_INLINE_VISIBILITY
    bool
    operator>(const __debug_iter<_Container, _Iter1>&, const __debug_iter<_Container, _Iter2>&);

    template <class _Container, class _Iter1, class _Iter2>
    _LIBCPP_INLINE_VISIBILITY
    bool
    operator>=(const __debug_iter<_Container, _Iter1>&, const __debug_iter<_Container, _Iter2>&);

    template <class _Container, class _Iter1, class _Iter2>
    _LIBCPP_INLINE_VISIBILITY
    bool
    operator<=(const __debug_iter<_Container, _Iter1>&, const __debug_iter<_Container, _Iter2>&);

    template <class _Container, class _Iter1, class _Iter2>
    _LIBCPP_INLINE_VISIBILITY
    typename __debug_iter<_Container, _Iter1>::difference_type
    operator-(const __debug_iter<_Container, _Iter1>&, const __debug_iter<_Container, _Iter2>&);

    template <class _Container, class _Iter>
    _LIBCPP_INLINE_VISIBILITY
    __debug_iter<_Container, _Iter>
    operator+(typename __debug_iter<_Container, _Iter>::difference_type, const __debug_iter<_Container, _Iter>&);

    template <class _Container, class _Iter>
    class __debug_iter
      {
      public:
        typedef _Iter iterator_type;
        typedef _Container __container_type;
        typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
        typedef typename iterator_traits<iterator_type>::value_type value_type;
        typedef typename iterator_traits<iterator_type>::difference_type difference_type;
        typedef typename iterator_traits<iterator_type>::pointer pointer;
        typedef typename iterator_traits<iterator_type>::reference reference;
      private:
        iterator_type __i;
        __debug_iter* __next;
        __container_type* __cont;

      public:
        _LIBCPP_INLINE_VISIBILITY __debug_iter() : __next(0), __cont(0)
          {}
        _LIBCPP_INLINE_VISIBILITY __debug_iter(const __debug_iter& __x)
        : __i(__x.base()), __next(0), __cont(0)
          { __set_owner(__x.__cont);}
        __debug_iter& operator=(const __debug_iter& __x);
        template <class _Up> _LIBCPP_INLINE_VISIBILITY __debug_iter(const __debug_iter<_Container, _Up>& __u,
            typename enable_if<is_convertible<_Up, iterator_type>::value>::type* = 0)
        : __i(__u.base()), __next(0), __cont(0)
          { __set_owner(__u.__cont);}
        _LIBCPP_INLINE_VISIBILITY ~__debug_iter()
          { __remove_owner();}
        _LIBCPP_INLINE_VISIBILITY reference operator*() const
          { assert(__is_deref()); return *__i;}
        _LIBCPP_INLINE_VISIBILITY pointer operator->() const
          { return &(operator*());}
        _LIBCPP_INLINE_VISIBILITY __debug_iter& operator++()
          { assert(__can_increment()); ++__i; return *this;}
        _LIBCPP_INLINE_VISIBILITY __debug_iter operator++(int)
          { __debug_iter __tmp(*this); operator++(); return __tmp;}
        _LIBCPP_INLINE_VISIBILITY __debug_iter& operator--()
          { assert(__can_decrement()); --__i; return *this;}
        _LIBCPP_INLINE_VISIBILITY __debug_iter operator--(int)
          { __debug_iter __tmp(*this); operator--(); return __tmp;}
        _LIBCPP_INLINE_VISIBILITY __debug_iter operator+ (difference_type __n) const
          { __debug_iter __t(*this); __t += __n; return __t;}
        __debug_iter& operator+=(difference_type __n);
        _LIBCPP_INLINE_VISIBILITY __debug_iter operator- (difference_type __n) const
          { __debug_iter __t(*this); __t -= __n; return __t;}
        _LIBCPP_INLINE_VISIBILITY __debug_iter& operator-=(difference_type __n)
          { *this += -__n; return *this;}
        _LIBCPP_INLINE_VISIBILITY reference operator[](difference_type __n) const
          { return *(*this + __n);}

      private:
        _LIBCPP_INLINE_VISIBILITY __debug_iter(const __container_type* __c, iterator_type __x)
        : __i(__x), __next(0), __cont(0)
          { __set_owner(__c);}
        _LIBCPP_INLINE_VISIBILITY iterator_type base() const
          { return __i;}

        void __set_owner(const __container_type* __c);
        void __remove_owner();
        static void __remove_all(__container_type* __c);
        static void swap(__container_type* __x, __container_type* __y);

        _LIBCPP_INLINE_VISIBILITY bool __is_deref() const
          { return __is_deref(__is_random_access_iterator<iterator_type>());}
        bool __is_deref(false_type) const;
        bool __is_deref(true_type) const;
        _LIBCPP_INLINE_VISIBILITY bool __can_decrement() const
          { return __can_decrement(integral_constant<int, is_pointer<iterator_type>::value ? 2:
                __is_random_access_iterator<iterator_type>::value ? 1 : 0>());}
        bool __can_decrement(integral_constant<int, 0>) const;
        bool __can_decrement(integral_constant<int, 1>) const;
        bool __can_decrement(integral_constant<int, 2>) const;
        _LIBCPP_INLINE_VISIBILITY bool __can_increment() const
          { return __can_increment(integral_constant<int, is_pointer<iterator_type>::value ? 2:
                __is_random_access_iterator<iterator_type>::value ? 1 : 0>());}
        bool __can_increment(integral_constant<int, 0>) const;
        bool __can_increment(integral_constant<int, 1>) const;
        bool __can_increment(integral_constant<int, 2>) const;

        _LIBCPP_INLINE_VISIBILITY bool __can_add(difference_type __n) const
          { return __can_add(__n, is_pointer<iterator_type>());}
        bool __can_add(difference_type __n, false_type) const;
        bool __can_add(difference_type __n, true_type) const;

        template <class _Cp, class _Up> friend class __debug_iter;
        friend class _Container::__self;

        template <class _Cp, class _Iter1, class _Iter2>
        friend
        bool
        operator==(const __debug_iter<_Cp, _Iter1>&, const __debug_iter<_Cp, _Iter2>&);

        template <class _Cp, class _Iter1, class _Iter2>
        friend
        bool
        operator<(const __debug_iter<_Cp, _Iter1>&, const __debug_iter<_Cp, _Iter2>&);

        template <class _Cp, class _Iter1, class _Iter2>
        friend
        bool
        operator!=(const __debug_iter<_Cp, _Iter1>&, const __debug_iter<_Cp, _Iter2>&);

        template <class _Cp, class _Iter1, class _Iter2>
        friend
        bool
        operator>(const __debug_iter<_Cp, _Iter1>&, const __debug_iter<_Cp, _Iter2>&);

        template <class _Cp, class _Iter1, class _Iter2>
        friend
        bool
        operator>=(const __debug_iter<_Cp, _Iter1>&, const __debug_iter<_Cp, _Iter2>&);

        template <class _Cp, class _Iter1, class _Iter2>
        friend
        bool
        operator<=(const __debug_iter<_Cp, _Iter1>&, const __debug_iter<_Cp, _Iter2>&);

        template <class _Cp, class _Iter1, class _Iter2>
        friend
        typename __debug_iter<_Cp, _Iter1>::difference_type
        operator-(const __debug_iter<_Cp, _Iter1>&, const __debug_iter<_Cp, _Iter2>&);

        template <class _Cp, class _Iter1>
        friend
        __debug_iter<_Cp, _Iter1>
        operator+(typename __debug_iter<_Cp, _Iter1>::difference_type, const __debug_iter<_Cp, _Iter1>&);
      };

    template <class _Container, class _Iter>
    __debug_iter<_Container, _Iter>&
    __debug_iter<_Container, _Iter>::operator=(const __debug_iter& __x)
      {
        if (this != &__x)
          {
            __remove_owner();
            __i = __x.__i;
            __set_owner(__x.__cont);
          }
        return *this;
      }

    template <class _Container, class _Iter>
    void
    __debug_iter<_Container, _Iter>::__set_owner(const __container_type* __c)
      {
        __cont = const_cast<__container_type*>(__c);
        __debug_iter*& __head = __cont->__get_iterator_list(this);
        __next = __head;
        __head = this;
      }

    template <class _Container, class _Iter>
    void
    __debug_iter<_Container, _Iter>::__remove_owner()
      {
        if (__cont)
          {
            __debug_iter*& __head = __cont->__get_iterator_list(this);
            if (__head == this)
            __head = __next;
            else
              {
                __debug_iter* __prev = __head;
                for (__debug_iter* __p = __head->__next; __p != this; __p = __p->__next)
                __prev = __p;
                __prev->__next = __next;
              }
            __cont = 0;
          }
      }

    template <class _Container, class _Iter>
    void
    __debug_iter<_Container, _Iter>::__remove_all(__container_type* __c)
      {
        __debug_iter*& __head = __c->__get_iterator_list((__debug_iter*)0);
        __debug_iter* __p = __head;
        __head = 0;
        while (__p)
          {
            __p->__cont = 0;
            __debug_iter* __n = __p->__next;
            __p->__next = 0;
            __p = __n;
          }
      }

    template <class _Container, class _Iter>
    void
    __debug_iter<_Container, _Iter>::swap(__container_type* __x, __container_type* __y)
      {
        __debug_iter*& __head_x = __x->__get_iterator_list((__debug_iter*)0);
        __debug_iter*& __head_y = __y->__get_iterator_list((__debug_iter*)0);
        __debug_iter* __p = __head_x;
        __head_x = __head_y;
        __head_y = __p;
        for (__p = __head_x; __p; __p = __p->__next)
        __p->__cont = __x;
        for (__p = __head_y; __p; __p = __p->__next)
        __p->__cont = __y;
      }

    template <class _Container, class _Iter>
    bool
    __debug_iter<_Container, _Iter>::__is_deref(false_type) const
      {
        if (__cont == 0)
        return false;
        return __i != __cont->end().base();
      }

    template <class _Container, class _Iter>
    bool
    __debug_iter<_Container, _Iter>::__is_deref(true_type) const
      {
        if (__cont == 0)
        return false;
        return __i < __cont->end().base();
      }

    template <class _Container, class _Iter>
    bool
    __debug_iter<_Container, _Iter>::__can_decrement(integral_constant<int, 0>) const
      {
        if (__cont == 0)
        return false;
        return __i != __cont->begin().base();
      }

    template <class _Container, class _Iter>
    bool
    __debug_iter<_Container, _Iter>::__can_decrement(integral_constant<int, 1>) const
      {
        if (__cont == 0)
        return false;
        iterator_type __b = __cont->begin().base();
        return __b < __i && __i <= __b + __cont->size();
      }

    template <class _Container, class _Iter>
    bool
    __debug_iter<_Container, _Iter>::__can_decrement(integral_constant<int, 2>) const
      {
        if (__cont == 0)
        return false;
        iterator_type __b = __cont->begin().base();
        return __b < __i && __i <= __b + __cont->size();
      }

    template <class _Container, class _Iter>
    bool
    __debug_iter<_Container, _Iter>::__can_increment(integral_constant<int, 0>) const
      {
        if (__cont == 0)
        return false;
        return __i != __cont->end().base();
      }

    template <class _Container, class _Iter>
    bool
    __debug_iter<_Container, _Iter>::__can_increment(integral_constant<int, 1>) const
      {
        if (__cont == 0)
        return false;
        iterator_type __b = __cont->begin().base();
        return __b <= __i && __i < __b + __cont->size();
      }

    template <class _Container, class _Iter>
    bool
    __debug_iter<_Container, _Iter>::__can_increment(integral_constant<int, 2>) const
      {
        if (__cont == 0)
        return false;
        iterator_type __b = __cont->begin().base();
        return __b <= __i && __i < __b + __cont->size();
      }

    template <class _Container, class _Iter>
    bool
    __debug_iter<_Container, _Iter>::__can_add(difference_type __n, false_type) const
      {
        if (__cont == 0)
        return false;
        iterator_type __b = __cont->begin().base();
        iterator_type __j = __i + __n;
        return __b <= __j && __j <= __b + __cont->size();
      }

    template <class _Container, class _Iter>
    bool
    __debug_iter<_Container, _Iter>::__can_add(difference_type __n, true_type) const
      {
        if (__cont == 0)
        return false;
        iterator_type __b = __cont->begin().base();
        iterator_type __j = __i + __n;
        return __b <= __j && __j <= __b + __cont->size();
      }

    template <class _Container, class _Iter>
    __debug_iter<_Container, _Iter>&
    __debug_iter<_Container, _Iter>::operator+=(difference_type __n)
      {
        assert(__can_add(__n));
        __i += __n;
        return *this;
      }

    template <class _Container, class _Iter1, class _Iter2>
    inline _LIBCPP_INLINE_VISIBILITY
    bool
    operator==(const __debug_iter<_Container, _Iter1>& __x, const __debug_iter<_Container, _Iter2>& __y)
      {
        assert(__x.__cont && __x.__cont == __y.__cont);
        return __x.base() == __y.base();
      }

    template <class _Container, class _Iter1, class _Iter2>
    inline _LIBCPP_INLINE_VISIBILITY
    bool
    operator!=(const __debug_iter<_Container, _Iter1>& __x, const __debug_iter<_Container, _Iter2>& __y)
      {
        return !(__x == __y);
      }

    template <class _Container, class _Iter1, class _Iter2>
    inline _LIBCPP_INLINE_VISIBILITY
    bool
    operator<(const __debug_iter<_Container, _Iter1>& __x, const __debug_iter<_Container, _Iter2>& __y)
      {
        assert(__x.__cont && __x.__cont == __y.__cont);
        return __x.base() < __y.base();
      }

    template <class _Container, class _Iter1, class _Iter2>
    inline _LIBCPP_INLINE_VISIBILITY
    bool
    operator>(const __debug_iter<_Container, _Iter1>& __x, const __debug_iter<_Container, _Iter2>& __y)
      {
        return __y < __x;
      }

    template <class _Container, class _Iter1, class _Iter2>
    inline _LIBCPP_INLINE_VISIBILITY
    bool
    operator>=(const __debug_iter<_Container, _Iter1>& __x, const __debug_iter<_Container, _Iter2>& __y)
      {
        return !(__x < __y);
      }

    template <class _Container, class _Iter1, class _Iter2>
    inline _LIBCPP_INLINE_VISIBILITY
    bool
    operator<=(const __debug_iter<_Container, _Iter1>& __x, const __debug_iter<_Container, _Iter2>& __y)
      {
        return !(__y < __x);
      }

    template <class _Container, class _Iter1, class _Iter2>
    inline _LIBCPP_INLINE_VISIBILITY
    typename __debug_iter<_Container, _Iter1>::difference_type
    operator-(const __debug_iter<_Container, _Iter1>& __x, const __debug_iter<_Container, _Iter2>& __y)
      {
        assert(__x.__cont && __x.__cont == __y.__cont);
        return __x.base() - __y.base();
      }

    template <class _Container, class _Iter>
    inline _LIBCPP_INLINE_VISIBILITY
    __debug_iter<_Container, _Iter>
    operator+(typename __debug_iter<_Container, _Iter>::difference_type __n,
        const __debug_iter<_Container, _Iter>& __x)
      {
        return __x + __n;
      }

#endif  // _LIBCPP_DEBUG
#if !defined(_LIBCPP_HAS_NO_RVALUE_REFERENCES) && !defined(_LIBCPP_HAS_NO_TRAILING_RETURN)

    template<class _Cp>
      inline _LIBCPP_INLINE_VISIBILITY
      auto
      begin(_Cp& __c) -> decltype(__c.begin())
      {
        return __c.begin();
      }

    template<class _Cp>
      inline _LIBCPP_INLINE_VISIBILITY
      auto
      begin(const _Cp& __c) -> decltype(__c.begin())
      {
        return __c.begin();
      }

    template<class _Cp>
      inline _LIBCPP_INLINE_VISIBILITY
      auto
      end(_Cp& __c) -> decltype(__c.end())
      {
        return __c.end();
      }

    template<class _Cp>
      inline _LIBCPP_INLINE_VISIBILITY
      auto
      end(const _Cp& __c) -> decltype(__c.end())
      {
        return __c.end();
      }

#else  // !defined(_LIBCPP_HAS_NO_RVALUE_REFERENCES) && !defined(_LIBCPP_HAS_NO_TRAILING_RETURN)
    template<class _Cp>
    inline _LIBCPP_INLINE_VISIBILITY
    typename _Cp::iterator
    begin(_Cp& __c)
      {
        return __c.begin();
      }

    template<class _Cp>
    inline _LIBCPP_INLINE_VISIBILITY
    typename _Cp::const_iterator
    begin(const _Cp& __c)
      {
        return __c.begin();
      }

    template<class _Cp>
    inline _LIBCPP_INLINE_VISIBILITY
    typename _Cp::iterator
    end(_Cp& __c)
      {
        return __c.end();
      }

    template<class _Cp>
    inline _LIBCPP_INLINE_VISIBILITY
    typename _Cp::const_iterator
    end(const _Cp& __c)
      {
        return __c.end();
      }

#endif  // !defined(_LIBCPP_HAS_NO_RVALUE_REFERENCES) && !defined(_LIBCPP_HAS_NO_TRAILING_RETURN)
    template<class _Tp, size_t _Np>
      inline _LIBCPP_INLINE_VISIBILITY
      _Tp*
      begin(_Tp (&__array)[_Np])
      {
        return __array;
      }

    template<class _Tp, size_t _Np>
      inline _LIBCPP_INLINE_VISIBILITY
      _Tp*
      end(_Tp (&__array)[_Np])
      {
        return __array + _Np;
      }

//_LIBCPP_END_NAMESPACE_STD
  }
}

#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_ITERATOR_H_