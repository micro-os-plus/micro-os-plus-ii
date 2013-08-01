//
// This file is part of the µOS++ distribution.
//
// [Original LLVM sources]
//      Copyright (c) 2009-2013 by the contributors listed in
//      'LLVM libcxx Credits.txt'. See 'LLVM libcxx License.txt' for details.
// [The µOS++ changes]
//      Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/OS.h"

#include "portable/infrastructure/include/TestSuite.h"

// This test exercises the os::std::string class.

// It is based on LLVM libcxx/test/input.output/iostream.format/output.stream/*

// ----------------------------------------------------------------------------

#include "portable/language/cpp/include/string.h"
#include "portable/language/cpp/include/climits.h"
#include "portable/language/cpp/include/iterator.h"

#include "portable/language/cpp/include/malloc.h"

using namespace os::std;

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

static os::infra::TestSuite ts;

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/strings/basic.string/test_traits.h
// test/strings/basic.string/test_allocator.h

template<class charT>
  struct test_traits
  {
    typedef charT char_type;
  };

class test_alloc_base
{
protected:
  static int count;
public:
  static int throw_after;
};

int test_alloc_base::count = 0;
int test_alloc_base::throw_after = INT_MAX;

template<class T>
  class test_allocator : public test_alloc_base
  {
    int data_;

    template<class U>
      friend class test_allocator;
  public:

    typedef unsigned size_type;
    typedef int difference_type;
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef typename add_lvalue_reference<value_type>::type reference;
    typedef typename add_lvalue_reference<const value_type>::type const_reference;

    template<class U>
      struct rebind
      {
        typedef test_allocator<U> other;
      };

    test_allocator() throw ()
        : data_(-1)
    {
    }

    explicit
    test_allocator(int i) throw ()
        : data_(i)
    {
    }

    test_allocator(const test_allocator& a) throw ()
        : data_(a.data_)
    {
    }

    template<class U>
      test_allocator(const test_allocator<U>& a) throw ()
          : data_(a.data_)
      {
      }

    ~test_allocator() throw ()
    {
      data_ = 0;
    }

    pointer
    address(reference x) const
    {
      return &x;
    }

    const_pointer
    address(const_reference x) const
    {
      return &x;
    }

    pointer
    allocate(size_type n, const void* = 0)
    {
      if (count >= throw_after)
        {
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
          throw bad_alloc();
#else
          assert_always("bad_alloc()");
#endif
        }
      ++count;
#ifndef      OS_INCLUDE_STD_CALIBRATION
      return (pointer) os::std::malloc(n * sizeof(T));
#else
      return (pointer) std::malloc(n * sizeof(T));
#endif
    }

    void
    deallocate(pointer p, size_type)
    {
#ifndef      OS_INCLUDE_STD_CALIBRATION
      os::std::free(p);
#else
      std::free(p);
#endif
    }

    size_type
    max_size() const throw ()
    {
      return UINT_MAX / sizeof(T);
    }

    void
    construct(pointer p, const T& val)
    {
      ::new (p) T(val);
    }

    void
    destroy(pointer p)
    {
      p->~T();
    }

    friend bool
    operator==(const test_allocator& x, const test_allocator& y)
    {
      return x.data_ == y.data_;
    }

    friend bool
    operator!=(const test_allocator& x, const test_allocator& y)
    {
      return !(x == y);
    }
  };

template<class It>
  class input_iterator
  {
  private:
    It it_;

  public:
    typedef input_iterator_tag iterator_category;
    typedef typename iterator_traits<It>::value_type value_type;
    typedef typename iterator_traits<It>::difference_type difference_type;
    typedef It pointer;
    typedef typename iterator_traits<It>::reference reference;

    input_iterator()
        : it_()
    {
    }

    explicit
    input_iterator(It it)
        : it_(it)
    {
    }

    reference
    operator*() const
    {
      return *it_;
    }

    pointer
    operator->() const
    {
      return it_;
    }

    input_iterator&
    operator++()
    {
      ++it_;
      return *this;
    }

    input_iterator
    operator++(int)
    {
      input_iterator tmp(*this);
      ++(*this);
      return tmp;
    }

    friend bool
    operator==(const input_iterator& x, const input_iterator& y)
    {
      return x.it_ == y.it_;
    }

    friend bool
    operator!=(const input_iterator& x, const input_iterator& y)
    {
      return !(x == y);
    }
  };

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/strings/basic.string/types.pass.cpp

template<class Traits, class Allocator>
  void
  testTypes()
  {
    typedef basic_string<typename Traits::char_type, Traits, Allocator> S;

    ts.assertCondition((is_same<typename S::traits_type, Traits>::value));
    ts.assertCondition((is_same<typename S::value_type, typename Traits::char_type>::value));
    ts.assertCondition((is_same<typename S::value_type, typename Allocator::value_type>::value));
    ts.assertCondition((is_same<typename S::allocator_type, Allocator>::value));
    ts.assertCondition((is_same<typename S::size_type, typename Allocator::size_type>::value));
    ts.assertCondition((is_same<typename S::difference_type, typename Allocator::difference_type>::value));
    ts.assertCondition((is_same<typename S::reference, typename Allocator::reference>::value));
    ts.assertCondition((is_same<typename S::const_reference, typename Allocator::const_reference>::value));
    ts.assertCondition((is_same<typename S::pointer, typename Allocator::pointer>::value));
    ts.assertCondition((is_same<typename S::const_pointer, typename Allocator::const_pointer>::value));
    ts.assertCondition((is_same<
            typename iterator_traits<typename S::iterator>::iterator_category,
            random_access_iterator_tag>::value));
    ts.assertCondition((is_same<
            typename iterator_traits<typename S::const_iterator>::iterator_category,
            random_access_iterator_tag>::value));
    ts.assertCondition((is_same<
            typename S::reverse_iterator,
            reverse_iterator<typename S::iterator> >::value));
    ts.assertCondition((is_same<
            typename S::const_reverse_iterator,
            reverse_iterator<typename S::const_iterator> >::value));
    ts.assertCondition(S::npos == static_cast<typename S::size_type>(-1));
  }

void
runTestTypes();

void
runTestTypes()
{
  ts.reportInfo("Test string types");
    {
      ts.setFunctionNameOrPrefix("types");

      ts.setPreconditions("test_*<char>");
      testTypes<test_traits<char>, test_allocator<char> >();

      ts.setPreconditions("char_traits<char>");
      testTypes<char_traits<char>, allocator<char> >();

      ts.assertCondition((is_same<basic_string<char>::traits_type,
              char_traits<char> >::value));
      ts.assertCondition((is_same<basic_string<char>::allocator_type,
              allocator<char> >::value));

      ts.setPreconditions("char_traits<wchar_t>");
      testTypes<char_traits<wchar_t>, allocator<wchar_t> >();
    }
}

// ----------------------------------------------------------------------------

namespace cons
{
  namespace alloc
  {
    // inspired from LLVM libcxx
    // test/strings/basic.string/string.cons/alloc.pass.cpp

    template<class S>
      void
      test1()
      {
          {
            S s;
            ts.assertCondition(s.__invariants());
            ts.assertCondition(s.data());
            ts.assertCondition(s.size() == 0);
            ts.assertCondition(s.capacity() >= s.size());
            ts.assertCondition(s.get_allocator() == typename S::allocator_type());
          }
      }

    template<class S>
      void
      test2()
      {
          {
            S s(typename S::allocator_type(5));
            ts.assertCondition(s.__invariants());
            ts.assertCondition(s.data());
            ts.assertCondition(s.size() == 0);
            ts.assertCondition(s.capacity() >= s.size());
            ts.assertCondition(s.get_allocator() == typename S::allocator_type(5));
          }
      }
  } // namespace alloc
} // namespace cons

void
runTestConstructorsAlloc();

void
runTestConstructorsAlloc()
{

  ts.reportInfo("Test string constructors alloc");
    {
      ts.setFunctionNameOrPrefix("basic_string()");

      cons::alloc::test1<
          basic_string<char, char_traits<char>, test_allocator<char> > >();
    }

    {
      ts.setFunctionNameOrPrefix("basic_string(typename S::allocator_type(5))");

      cons::alloc::test2<
          basic_string<char, char_traits<char>, test_allocator<char> > >();
    }
}

// ----------------------------------------------------------------------------

namespace cons
{
  namespace size_char_alloc
  {
    // inspired from LLVM libcxx
    // test/strings/basic.string/string.cons/size_char_allocs.pass.cpp

    template<class charT>
      void
      test(unsigned n, charT c)
      {
        typedef basic_string<charT, char_traits<charT>, test_allocator<charT> > S;
        //typedef typename S::traits_type T;
        typedef typename S::allocator_type A;
        typedef typename S::value_type value_type;

        ts.setPreconditions("t1");

        S s2(n, c);
        ts.assertCondition(s2.__invariants());
        ts.assertCondition(s2.size() == n);
        if (n > 0)
          {
            // check first char
            ts.assertCondition(s2[0] == c);
            // check last char
            ts.assertCondition(s2[n-1] == c);
            // check if end of string is there
            ts.assertCondition(s2[n] == value_type());
          }
        ts.assertCondition(s2.get_allocator() == A());
        ts.assertCondition(s2.capacity() >= s2.size());
      }

    template<class charT>
      void
      test(unsigned n, charT c, const test_allocator<charT>& a)
      {
        typedef basic_string<charT, char_traits<charT>, test_allocator<charT> > S;
        // typedef typename S::traits_type T;
        // typedef typename S::allocator_type A;
        typedef typename S::value_type value_type;

        ts.setPreconditions("t2");

        S s2(n, c, a);
        ts.assertCondition(s2.__invariants());
        ts.assertCondition(s2.size() == n);
        if (n > 0)
          {
            ts.assertCondition(s2[0] == c);
            ts.assertCondition(s2[n-1] == c);
            ts.assertCondition(s2[n] == value_type());
          }
        ts.assertCondition(s2.get_allocator() == a);
        ts.assertCondition(s2.capacity() >= s2.size());
      }

    template<class Tp>
      void
      test(Tp n, Tp c)
      {
        typedef char charT;
        typedef basic_string<charT, char_traits<charT>, test_allocator<charT> > S;
        // typedef typename S::traits_type T;
        typedef typename S::allocator_type A;
        typedef typename S::value_type value_type;

        ts.setPreconditions("t3");

        S s2(n, c);
        ts.assertCondition(s2.__invariants());
        ts.assertCondition(s2.size() == (unsigned)n);
        if (n > 0)
          {
            ts.assertCondition(s2[0] == c);
            ts.assertCondition(s2[n-1] == c);
            ts.assertCondition(s2[n] == value_type());
          }
        ts.assertCondition(s2.get_allocator() == A());
        ts.assertCondition(s2.capacity() >= s2.size());
      }

    template<class Tp>
      void
      test(Tp n, Tp c, const test_allocator<char>& a)
      {
        typedef char charT;
        typedef basic_string<charT, char_traits<charT>, test_allocator<charT> > S;
        // typedef typename S::traits_type T;
        // typedef typename S::allocator_type A;
        typedef typename S::value_type value_type;

        ts.setPreconditions("t4");

        S s2(n, c, a);
        ts.assertCondition(s2.__invariants());
        ts.assertCondition(s2.size() == (unsigned)n);
        if (n > 0)
          {
            ts.assertCondition(s2[0] == c);
            ts.assertCondition(s2[n-1] == c);
            ts.assertCondition(s2[n] == value_type());
          }
        ts.assertCondition(s2.get_allocator() == a);
        ts.assertCondition(s2.capacity() >= s2.size());
      }
  } // namespace size_char_alloc
} // namespace cons

void
runTestConstructorsSizeCharAlloc();

void
runTestConstructorsSizeCharAlloc()
{

  ts.reportInfo("Test string constructors size_char_alloc");
    {
      using namespace cons::size_char_alloc;

      typedef test_allocator<char> A;
      // typedef basic_string<char, char_traits<char>, A> S;

      ts.setFunctionNameOrPrefix("basic_string(n,c)");
      ts.setInputValues("0,'a'");
      test(0, 'a');

      ts.setFunctionNameOrPrefix("basic_string(n,c,a)");
      ts.setInputValues("0,'a',A(2)");
      test(0, 'a', A(2));

      ts.setFunctionNameOrPrefix("basic_string(n,c)");
      ts.setInputValues("1,'a'");
      test(1, 'a');

      ts.setFunctionNameOrPrefix("basic_string(n,c,a)");
      ts.setInputValues("1,'a',A(2)");
      test(1, 'a', A(2));

      ts.setFunctionNameOrPrefix("basic_string(n,c)");
      ts.setInputValues("10,'a'");
      test(10, 'a');

      ts.setFunctionNameOrPrefix("basic_string(n,c,a)");
      ts.setInputValues("10,'a',A(2)");
      test(10, 'a', A(2));

      ts.setFunctionNameOrPrefix("basic_string(n,c)");
      ts.setInputValues("100,'a'");
      test(100, 'a');

      ts.setFunctionNameOrPrefix("basic_string(n,c,a)");
      ts.setInputValues("100,'a',A(2)");
      test(100, 'a', A(2));

#if 0
      // matches the Iterator constructor and
      // triggers some warnings, to be investigated

      ts.setFunctionNameOrPrefix("basic_string(n,c)");
      ts.setInputValues("100,65");
      test(100, 65);

      test(100, 65, A(3));
#endif
    }
}

// ----------------------------------------------------------------------------

namespace cons
{
  namespace char_assignment
  {
    // inspired from LLVM libcxx
    // test/strings/basic.string/string.cons/size_char_allocs.pass.cpp
    template<class S>
      void
      test(S s1, typename S::value_type s2)
      {
        typedef typename S::traits_type T;
        typedef typename S::value_type value_type;

        s1 = s2;
        ts.assertCondition(s1.__invariants());
        ts.assertCondition(s1.size() == 1);
        // check the first and only char
        ts.assertCondition(T::eq(s1[0], s2));
        // check if end of string is there
        ts.assertCondition(T::eq(s1[1], value_type()));
        ts.assertCondition(s1.capacity() >= s1.size());
      }

  } // namespace char_assignment
} // namespace cons

void
runTestConstructorsCharAssignment();

void
runTestConstructorsCharAssignment()
{

  ts.reportInfo("Test string constructors char_assignment");

    {
      using namespace cons::char_assignment;

      typedef string S;

      ts.setFunctionNameOrPrefix("operator=(value_type)");
      ts.setInputValues("S(),'a'");
      test(S(), 'a');

      ts.setInputValues("S(\"1\"),'a'");
      test(S("1"), 'a');

      ts.setInputValues("S(\"123456789\"),'a'");
      test(S("123456789"), 'a');

      ts.setInputValues(
          "S(\"1234567890123456789012345678901234567890123456789012345678901234567890\"),'a'");
      test(
          S(
              "1234567890123456789012345678901234567890123456789012345678901234567890"),
          'a');

    }
}

// ----------------------------------------------------------------------------

namespace cons
{
  namespace copy_alloc
  {
    // inspired from LLVM libcxx
    // test/strings/basic.string/string.cons/copy_alloc.pass.cpp

    template<class S>
      void
      test(S s1, const typename S::allocator_type& a)
      {
        S s2(s1, a);
        ts.assertCondition(s2.__invariants());
        ts.assertCondition(s2 == s1);
        ts.assertCondition(s2.capacity() >= s2.size());
        ts.assertCondition(s2.get_allocator() == a);
      }
  } // namespace copy_alloc
} // namespace cons

void
runTestConstructorsCopyAlloc();

void
runTestConstructorsCopyAlloc()
{

  ts.reportInfo("Test string constructors copy_alloc");
    {
      using namespace cons::copy_alloc;

      typedef test_allocator<char> A;
      typedef basic_string<char, char_traits<char>, A> S;

      ts.setFunctionNameOrPrefix(
          "basic_string(basic_string&, allocator_type&)");

      ts.setInputValues("S(), A(3)");
      test(S(), A(3));

      ts.setInputValues("S(\"1\"), A(5)");
      test(S("1"), A(5));

      ts.setInputValues(
          "S(\"1234567890123456789012345678901234567890123456789012345678901234567890\"), A(7)");
      test(
          S(
              "1234567890123456789012345678901234567890123456789012345678901234567890"),
          A(7));

    }
}

// ----------------------------------------------------------------------------

namespace cons
{
  namespace copy_assignment
  {
    // inspired from LLVM libcxx
    // test/strings/basic.string/string.cons/copy_assignment.pass.cpp

    template<class S>
      void
      test(S s1, const S& s2)
      {
        s1 = s2;
        ts.assertCondition(s1.__invariants());
        ts.assertCondition(s1 == s2);
        ts.assertCondition(s1.capacity() >= s1.size());
      }

  } // namespace copy_assignment
} // namespace cons

void
runTestConstructorsCopyAssignment();

void
runTestConstructorsCopyAssignment()
{

  ts.reportInfo("Test string constructors copy_assignment");
    {
      using namespace cons::copy_assignment;

      typedef string S;

      ts.setFunctionNameOrPrefix("operator=(basic_string&)");

      ts.setInputValues("S(), S()");
      test(S(), S());

      ts.setInputValues("S(\"1\"), S()");
      test(S("1"), S());

      ts.setInputValues("S(), S(\"1\")");
      test(S(), S("1"));

      ts.setInputValues("S(\"1\"), S(\"2\")");
      test(S("1"), S("2"));

      //test(S("1"), S("2"));

      ts.setInputValues("S(), S(\"a...z\")");
      test(S(),
          S(
              "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"));

      ts.setInputValues("S(\"123456789\"), S(\"a...z\")");
      test(S("123456789"),
          S(
              "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"));

      ts.setInputValues("S(\"12345...80...67890\"), S(\"a...z\")");
      test(
          S(
              "1234567890123456789012345678901234567890123456789012345678901234567890"),
          S(
              "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"));

      ts.setInputValues("S(\"12345...160...67890\"), S(\"a...z\")");
      test(
          S(
              "1234567890123456789012345678901234567890123456789012345678901234567890"
                  "1234567890123456789012345678901234567890123456789012345678901234567890"),
          S(
              "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"));

    }
}

// ----------------------------------------------------------------------------

namespace cons
{
  namespace copy
  {
    // inspired from LLVM libcxx
    // test/strings/basic.string/string.cons/copy.pass.cpp

    template<class S>
      void
      test(S s1)
      {
        S s2 = s1;
        ts.assertCondition(s2.__invariants());
        ts.assertCondition(s2 == s1);
        ts.assertCondition(s2.capacity() >= s2.size());
        ts.assertCondition(s2.get_allocator() == s1.get_allocator());
      }

  } // namespace copy
} // namespace cons

void
runTestConstructorsCopy();

void
runTestConstructorsCopy()
{

  ts.reportInfo("Test string constructors copy");
    {
      using namespace cons::copy;

      typedef test_allocator<char> A;
      typedef basic_string<char, char_traits<char>, A> S;

      ts.setFunctionNameOrPrefix("basic_string(basic_string&)");

      ts.setInputValues("S(A(3))");
      test(S(A(3)));

      ts.setInputValues("S(\"1\", A(5))");
      test(S("1", A(5)));

      ts.setInputValues("S(\"12345...80...67890\", A(7))");
      test(
          S(
              "1234567890123456789012345678901234567890123456789012345678901234567890",
              A(7)));

    }
}

// ----------------------------------------------------------------------------

void
runTestConstructorsInitializerListAssignment();

void
runTestConstructorsInitializerListAssignment()
{

#ifndef _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS
  ts.reportInfo("Test string constructors initializer_list_assignment");

  // apparently initialiser lists are not supported.
    {
      ts.setFunctionNameOrPrefix("basic_string(initializer_list<value_type>)");

      //string s;
      ts.setInputValues("{'a', 'b', 'c'}");
      s =
        { 'a', 'b', 'c'};
      ts.assertCondition(s == "abc");
    }
#endif
}

// ----------------------------------------------------------------------------

namespace cons
{
  namespace iter_alloc
  {
    // inspired from LLVM libcxx
    // test/strings/basic.string/string.cons/iter_alloc.pass.cpp

    template<class It>
      void
      test(It first, It last)
      {
        typedef typename iterator_traits<It>::value_type charT;
        typedef basic_string<charT, char_traits<charT>, test_allocator<charT> > S;
        typedef typename S::traits_type T;
        typedef typename S::allocator_type A;
        S s2(first, last);
        ts.assertCondition(s2.__invariants());
        ts.assertCondition(s2.size() == distance(first, last));
        unsigned i = 0;
        for (It it = first; it != last; ++it, ++i)
          ts.assertCondition(s2[i] == *it);
        ts.assertCondition(s2.get_allocator() == A());
        ts.assertCondition(s2.capacity() >= s2.size());
      }

    template<class It>
      void
      test(It first, It last,
          const test_allocator<typename iterator_traits<It>::value_type>& a)
      {
        typedef typename iterator_traits<It>::value_type charT;
        typedef basic_string<charT, char_traits<charT>, test_allocator<charT> > S;
        typedef typename S::traits_type T;
        typedef typename S::allocator_type A;
        S s2(first, last, a);
        ts.assertCondition(s2.__invariants());
        ts.assertCondition(s2.size() == distance(first, last));
        unsigned i = 0;
        for (It it = first; it != last; ++it, ++i)
          ts.assertCondition(s2[i] == *it);
        ts.assertCondition(s2.get_allocator() == a);
        ts.assertCondition(s2.capacity() >= s2.size());
      }

  } // namespace iter_alloc
} // namespace cons

void
runTestConstructorsIterAlloc();

void
runTestConstructorsIterAlloc()
{

  ts.reportInfo("Test string constructors iter_alloc");

    {
      using namespace cons::iter_alloc;

      typedef test_allocator<char> A;
      const char* s = "12345678901234567890123456789012345678901234567890";

      test(s, s);
      test(s, s, A(2));

      test(s, s + 1);
      test(s, s + 1, A(2));

      test(s, s + 10);
      test(s, s + 10, A(2));

      test(s, s + 50);
      test(s, s + 50, A(2));

      test(input_iterator<const char*>(s), input_iterator<const char*>(s));
      test(input_iterator<const char*>(s), input_iterator<const char*>(s),
          A(2));

      test(input_iterator<const char*>(s), input_iterator<const char*>(s + 1));
      test(input_iterator<const char*>(s), input_iterator<const char*>(s + 1),
          A(2));

      test(input_iterator<const char*>(s), input_iterator<const char*>(s + 10));
      test(input_iterator<const char*>(s), input_iterator<const char*>(s + 10),
          A(2));

      test(input_iterator<const char*>(s), input_iterator<const char*>(s + 50));
      test(input_iterator<const char*>(s), input_iterator<const char*>(s + 50),
          A(2));

    }
}

// ----------------------------------------------------------------------------

namespace cons
{
  namespace pointer_alloc
  {
    // inspired from LLVM libcxx
    // test/strings/basic.string/string.cons/pointer_alloc.pass.cpp

    template<class charT>
      void
      test(const charT* s)
      {
        typedef basic_string<charT, char_traits<charT>, test_allocator<charT> > S;
        typedef typename S::traits_type T;
        typedef typename S::allocator_type A;
        unsigned n = (unsigned) T::length(s);
        S s2(s);
        ts.assertCondition(s2.__invariants());
        ts.assertCondition(s2.size() == n);
        ts.assertCondition(T::compare(s2.data(), s, n) == 0);
        ts.assertCondition(s2.get_allocator() == A());
        ts.assertCondition(s2.capacity() >= s2.size());
      }

    template<class charT>
      void
      test(const charT* s, const test_allocator<charT>& a)
      {
        typedef basic_string<charT, char_traits<charT>, test_allocator<charT> > S;
        typedef typename S::traits_type T;
        typedef typename S::allocator_type A;
        unsigned n = (unsigned) T::length(s);
        S s2(s, a);
        ts.assertCondition(s2.__invariants());
        ts.assertCondition(s2.size() == n);
        ts.assertCondition(T::compare(s2.data(), s, n) == 0);
        ts.assertCondition(s2.get_allocator() == a);
        ts.assertCondition(s2.capacity() >= s2.size());
      }

  } // namespace pointer_alloc
} // namespace cons

void
runTestConstructorsPointerAlloc();

void
runTestConstructorsPointerAlloc()
{

  ts.reportInfo("Test string constructors pointer_alloc");

    {
      using namespace cons::pointer_alloc;

      typedef test_allocator<char> A;
      typedef basic_string<char, char_traits<char>, A> S;

      test("");
      test("", A(2));

      test("1");
      test("1", A(2));

      test("1234567980");
      test("1234567980", A(2));

      test("123456798012345679801234567980123456798012345679801234567980");
      test("123456798012345679801234567980123456798012345679801234567980",
          A(2));

    }
}

// ----------------------------------------------------------------------------

namespace cons
{
  namespace pointer_assignment
  {
    // inspired from LLVM libcxx
    // test/strings/basic.string/string.cons/pointer_assignment.pass.cpp

    template<class S>
      void
      test(S s1, const typename S::value_type* s2)
      {
        typedef typename S::traits_type T;
        s1 = s2;
        ts.assertCondition(s1.__invariants());
        ts.assertCondition(s1.size() == T::length(s2));
        ts.assertCondition(T::compare(s1.data(), s2, s1.size()) == 0);
        ts.assertCondition(s1.capacity() >= s1.size());
      }

  } // namespace pointer_assignment
} // namespace cons

void
runTestConstructorsPointerAssignment();

void
runTestConstructorsPointerAssignment()
{

  ts.reportInfo("Test string constructors pointer_assignment");

    {
      using namespace cons::pointer_assignment;

      typedef string S;
      test(S(), "");
      test(S("1"), "");
      test(S(), "1");
      test(S("1"), "2");
      test(S("1"), "2");

      test(S(),
          "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");
      test(S("123456789"),
          "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");
      test(
          S(
              "1234567890123456789012345678901234567890123456789012345678901234567890"),
          "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");
      test(
          S(
              "1234567890123456789012345678901234567890123456789012345678901234567890"
                  "1234567890123456789012345678901234567890123456789012345678901234567890"),
          "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");

    }
}

// ----------------------------------------------------------------------------

namespace cons
{
  namespace pointer_size_alloc
  {
    // inspired from LLVM libcxx
    // test/strings/basic.string/string.cons/pointer_size_alloc.pass.cpp

    template <class charT>
    void
    test(const charT* s, unsigned n)
    {
        typedef basic_string<charT, char_traits<charT>, test_allocator<charT> > S;
        typedef typename S::traits_type T;
        typedef typename S::allocator_type A;
        S s2(s, n);
        ts.assertCondition(s2.__invariants());
        ts.assertCondition(s2.size() == n);
        ts.assertCondition(T::compare(s2.data(), s, n) == 0);
        ts.assertCondition(s2.get_allocator() == A());
        ts.assertCondition(s2.capacity() >= s2.size());
    }


    template <class charT>
    void
    test(const charT* s, unsigned n, const test_allocator<charT>& a)
    {
        typedef basic_string<charT, char_traits<charT>, test_allocator<charT> > S;
        typedef typename S::traits_type T;
        typedef typename S::allocator_type A;
        S s2(s, n, a);
        ts.assertCondition(s2.__invariants());
        ts.assertCondition(s2.size() == n);
        ts.assertCondition(T::compare(s2.data(), s, n) == 0);
        ts.assertCondition(s2.get_allocator() == a);
        ts.assertCondition(s2.capacity() >= s2.size());
    }

  } // namespace pointer_size_alloc
} // namespace cons

void
runTestConstructorsPointerSizeAlloc();

void
runTestConstructorsPointerSizeAlloc()
{

  ts.reportInfo("Test string constructors pointer_size_alloc");

    {
      using namespace cons::pointer_size_alloc;

      typedef test_allocator<char> A;
      typedef basic_string<char, char_traits<char>, A> S;

      test("", 0);
      test("", 0, A(2));

      test("1", 1);
      test("1", 1, A(2));

      test("1234567980", 10);
      test("1234567980", 10, A(2));

      test("123456798012345679801234567980123456798012345679801234567980", 60);
      test("123456798012345679801234567980123456798012345679801234567980", 60, A(2));
    }
}

// ----------------------------------------------------------------------------

namespace cons
{
  namespace substr
  {
    // inspired from LLVM libcxx
    // test/strings/basic.string/string.cons/substr.pass.cpp

    template <class S>
    void
    test(S str, unsigned pos)
    {
        typedef typename S::traits_type T;
        typedef typename S::allocator_type A;
        try
        {
            S s2(str, pos);
            ts.assertCondition(s2.__invariants());
            ts.assertCondition(pos <= str.size());
            unsigned rlen = str.size() - pos;
            ts.assertCondition(s2.size() == rlen);
            ts.assertCondition(T::compare(s2.data(), str.data() + pos, rlen) == 0);
            ts.assertCondition(s2.get_allocator() == A());
            ts.assertCondition(s2.capacity() >= s2.size());
        }
        catch (out_of_range&)
        {
            ts.assertCondition(pos > str.size());
        }
    }

    template <class S>
    void
    test(S str, unsigned pos, unsigned n)
    {
        typedef typename S::traits_type T;
        typedef typename S::allocator_type A;
        try
        {
            S s2(str, pos, n);
            ts.assertCondition(s2.__invariants());
            ts.assertCondition(pos <= str.size());
            unsigned rlen = min(str.size() - pos, n);
            ts.assertCondition(s2.size() == rlen);
            ts.assertCondition(T::compare(s2.data(), str.data() + pos, rlen) == 0);
            ts.assertCondition(s2.get_allocator() == A());
            ts.assertCondition(s2.capacity() >= s2.size());
        }
        catch (out_of_range&)
        {
            ts.assertCondition(pos > str.size());
        }
    }

    template <class S>
    void
    test(S str, unsigned pos, unsigned n, const typename S::allocator_type& a)
    {
        typedef typename S::traits_type T;
        typedef typename S::allocator_type A;
        try
        {
            S s2(str, pos, n, a);
            ts.assertCondition(s2.__invariants());
            ts.assertCondition(pos <= str.size());
            unsigned rlen = min(str.size() - pos, n);
            ts.assertCondition(s2.size() == rlen);
            ts.assertCondition(T::compare(s2.data(), str.data() + pos, rlen) == 0);
            ts.assertCondition(s2.get_allocator() == a);
            ts.assertCondition(s2.capacity() >= s2.size());
        }
        catch (out_of_range&)
        {
            ts.assertCondition(pos > str.size());
        }
    }

  } // namespace substr
} // namespace cons

void
runTestConstructorsSubstr();

void
runTestConstructorsSubstr()
{

  ts.reportInfo("Test string constructors substr");

    {
      using namespace cons::substr;

      typedef test_allocator<char> A;
      typedef basic_string<char, char_traits<char>, A> S;

      test(S(A(3)), 0);
      test(S(A(3)), 1);
      test(S("1", A(5)), 0);
      test(S("1", A(5)), 1);
      test(S("1", A(5)), 2);
      test(S("1234567890123456789012345678901234567890123456789012345678901234567890", A(7)), 0);
      test(S("1234567890123456789012345678901234567890123456789012345678901234567890", A(7)), 5);
      test(S("1234567890123456789012345678901234567890123456789012345678901234567890", A(7)), 50);
      test(S("1234567890123456789012345678901234567890123456789012345678901234567890", A(7)), 500);

      test(S(A(3)), 0, 0);
      test(S(A(3)), 0, 1);
      test(S(A(3)), 1, 0);
      test(S(A(3)), 1, 1);
      test(S(A(3)), 1, 2);
      test(S("1", A(5)), 0, 0);
      test(S("1", A(5)), 0, 1);
      test(S("1234567890123456789012345678901234567890123456789012345678901234567890", A(7)), 50, 0);
      test(S("1234567890123456789012345678901234567890123456789012345678901234567890", A(7)), 50, 1);
      test(S("1234567890123456789012345678901234567890123456789012345678901234567890", A(7)), 50, 10);
      test(S("1234567890123456789012345678901234567890123456789012345678901234567890", A(7)), 50, 100);

      test(S(A(3)), 0, 0, A(4));
      test(S(A(3)), 0, 1, A(4));
      test(S(A(3)), 1, 0, A(4));
      test(S(A(3)), 1, 1, A(4));
      test(S(A(3)), 1, 2, A(4));
      test(S("1", A(5)), 0, 0, A(6));
      test(S("1", A(5)), 0, 1, A(6));
      test(S("1234567890123456789012345678901234567890123456789012345678901234567890", A(7)), 50, 0, A(8));
      test(S("1234567890123456789012345678901234567890123456789012345678901234567890", A(7)), 50, 1, A(8));
      test(S("1234567890123456789012345678901234567890123456789012345678901234567890", A(7)), 50, 10, A(8));
      test(S("1234567890123456789012345678901234567890123456789012345678901234567890", A(7)), 50, 100, A(8));
    }
}

// ============================================================================

int
main(int argc, char* argv[])
{
  // instantiate the TestSuite, passing the process parameters
  ts.processMainParameters(argc, argv);

  // mark the start of the test suite
  ts.start("portable/language/cpp/tests/src/string.cpp");

  // identify the class under tests
#ifdef OS_INCLUDE_STD_CALIBRATION
  ts.setClassName("std::string");
  ts.reportInfo("calibration run");
#else
  ts.setClassName("os::std::string");
#endif

  runTestTypes();

  runTestConstructorsAlloc();
  runTestConstructorsSizeCharAlloc();
  runTestConstructorsCharAssignment();
  runTestConstructorsCopyAlloc();
  runTestConstructorsCopyAssignment();
  runTestConstructorsCopy();
  runTestConstructorsInitializerListAssignment();
  runTestConstructorsIterAlloc();
  runTestConstructorsPointerAlloc();
  runTestConstructorsPointerAssignment();
  runTestConstructorsPointerSizeAlloc();
  runTestConstructorsSubstr();

  // mark the stop of the test suite
  ts.stop();

  int retval;
  retval = ts.getExitValue();

#if defined(DEBUG)
  os::diag::trace << __PRETTY_FUNCTION__ << " returns " << retval
      << os::std::endl;
#endif

  // return 0 if there are no failed test cases
  return retval;
}

// ============================================================================
