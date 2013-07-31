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

// To calibrate this test, first define this macro, to use the system std
// library versions.

// Note: Not all test branches are available when running in the
// host environment.

//#define OS_INCLUDE_STD_CALIBRATION

#ifdef OS_INCLUDE_STD_CALIBRATION

#include <string>
#include <climits>
using namespace std;

#else

#include "portable/language/cpp/include/string.h"
#include "portable/language/cpp/include/climits.h"
using namespace os::std;

#endif

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
      return (pointer) malloc(n * sizeof(T));
    }

    void
    deallocate(pointer p, size_type)
    {
      free(p);
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
#if 0
// inspired from LLVM libcxx
// test/input.output/iostream.format/output.stream/ostream/streambuf.pass.cpp

void
runTestConstructor();

void
runTestConstructor()
  {

    ts.reportInfo("Test ostream constructor");
      {
        ts.setFunctionNameOrPrefix("basic_ostream<char>(&)");

        testbuf<char> sb;
        basic_ostream<char> os(&sb);
        ts.assertCondition(os.rdbuf() == &sb);
        ts.assertCondition(os.tie() == 0);
        ts.assertCondition(os.fill() == ' ');
        ts.assertCondition(os.rdstate() == os.goodbit);
        ts.assertCondition(os.exceptions() == os.goodbit);
        ts.assertCondition(os.flags() == (os.skipws | os.dec));
        ts.assertCondition(os.precision() == 6);
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
        ts.assertCondition(os.getloc().name() == "C");
#endif
      }

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      {
        testbuf<wchar_t> sb;
        std::basic_ostream<wchar_t> os(&sb);
        ts.assertCondition(os.rdbuf() == &sb);
        ts.assertCondition(os.tie() == 0);
        ts.assertCondition(os.fill() == L' ');
        ts.assertCondition(os.rdstate() == os.goodbit);
        ts.assertCondition(os.exceptions() == os.goodbit);
        ts.assertCondition(os.flags() == (os.skipws | os.dec));
        ts.assertCondition(os.precision() == 6);
        ts.assertCondition(os.getloc().name() == "C");
      }
#endif
  }

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.format/output.stream/ostream/move.pass.cpp

template<class CharT>
class test_ostream_move : public basic_ostream<CharT>
  {
  public:
    typedef basic_ostream<CharT> base;
    test_ostream_move(testbuf<CharT>* sb)
    : base(sb)
      {
      }

    test_ostream_move(test_ostream_move&& s)
    : base(move(s))
      {}
  };

void
runTestMove();

void
runTestMove()
  {
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
    ts.reportInfo("Test ostream move");

      {
        testbuf<char> sb;
        test_ostream<char> os1(&sb);
        test_ostream<char> os(std::move(os1));
        assert(os1.rdbuf() == &sb);
        assert(os.rdbuf() == 0);
        assert(os.tie() == 0);
        assert(os.fill() == ' ');
        assert(os.rdstate() == os.goodbit);
        assert(os.exceptions() == os.goodbit);
        assert(os.flags() == (os.skipws | os.dec));
        assert(os.precision() == 6);
        assert(os.getloc().name() == "C");
      }
      {
        testbuf<wchar_t> sb;
        test_ostream<wchar_t> os1(&sb);
        test_ostream<wchar_t> os(std::move(os1));
        assert(os1.rdbuf() == &sb);
        assert(os.rdbuf() == 0);
        assert(os.tie() == 0);
        assert(os.fill() == L' ');
        assert(os.rdstate() == os.goodbit);
        assert(os.exceptions() == os.goodbit);
        assert(os.flags() == (os.skipws | os.dec));
        assert(os.precision() == 6);
        assert(os.getloc().name() == "C");
      }
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
  }

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.format/output.stream/ostream/member-swap.pass.cpp

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

template<class CharT>
class test_ostream_swap : public basic_ostream<CharT>
  {
  public:
    typedef basic_ostream<CharT> base;
    test_ostream_swap(testbuf<CharT>* sb)
    : base(sb)
      {
      }

    virtual
    ~test_ostream_swap()
      {
      }

    void
    swap(test_ostream_swap& s)
      {
        base::swap(s);
      }
  };

#pragma GCC diagnostic pop

void
runTestSwap();

void
runTestSwap()
  {
    ts.reportInfo("Test ostream swap");
      {
        ts.setFunctionNameOrPrefix("swap<char>()");

        testbuf<char> sb1;
        testbuf<char> sb2;
        test_ostream_swap<char> os1(&sb1);
        test_ostream_swap<char> os2(&sb2);
        os1.swap(os2);
        ts.assertCondition(os1.rdbuf() == &sb1);
        ts.assertCondition(os1.tie() == 0);
        ts.assertCondition(os1.fill() == ' ');
        ts.assertCondition(os1.rdstate() == os1.goodbit);
        ts.assertCondition(os1.exceptions() == os1.goodbit);
        ts.assertCondition(os1.flags() == (os1.skipws | os1.dec));
        ts.assertCondition(os1.precision() == 6);
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
        ts.assertCondition(os1.getloc().name() == "C");
#endif
        ts.assertCondition(os2.rdbuf() == &sb2);
        ts.assertCondition(os2.tie() == 0);
        ts.assertCondition(os2.fill() == ' ');
        ts.assertCondition(os2.rdstate() == os2.goodbit);
        ts.assertCondition(os2.exceptions() == os2.goodbit);
        ts.assertCondition(os2.flags() == (os2.skipws | os2.dec));
        ts.assertCondition(os2.precision() == 6);
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
        ts.assertCondition(os2.getloc().name() == "C");
#endif
      }

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      {
        testbuf<wchar_t> sb1;
        testbuf<wchar_t> sb2;
        test_ostream_swap<wchar_t> os1(&sb1);
        test_ostream_swap<wchar_t> os2(&sb2);
        os1.swap(os2);
        ts.assertCondition(os1.rdbuf() == &sb1);
        ts.assertCondition(os1.tie() == 0);
        ts.assertCondition(os1.fill() == ' ');
        ts.assertCondition(os1.rdstate() == os1.goodbit);
        ts.assertCondition(os1.exceptions() == os1.goodbit);
        ts.assertCondition(os1.flags() == (os1.skipws | os1.dec));
        ts.assertCondition(os1.precision() == 6);
        ts.assertCondition(os1.getloc().name() == "C");
        ts.assertCondition(os2.rdbuf() == &sb2);
        ts.assertCondition(os2.tie() == 0);
        ts.assertCondition(os2.fill() == ' ');
        ts.assertCondition(os2.rdstate() == os2.goodbit);
        ts.assertCondition(os2.exceptions() == os2.goodbit);
        ts.assertCondition(os2.flags() == (os2.skipws | os2.dec));
        ts.assertCondition(os2.precision() == 6);
        ts.assertCondition(os2.getloc().name() == "C");
      }
#endif

  }

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

template<class CharT>
class testbuf_array : public basic_streambuf<CharT>
  {
    typedef basic_streambuf<CharT> base;

  public:
    testbuf_array()
      {
        sync_called = 0;
        for (size_t i = 0; i < (sizeof(array) / sizeof(CharT)); ++i)
        array[i] = getDefaultChar();

        count = 0;
      }

    virtual
    ~testbuf_array()
      {
      }

    CharT
    getDefaultChar(void)
      {
        return '*';
      }

    CharT array[100];
    size_t count;

    int sync_called;

  protected:

    virtual typename base::int_type
    overflow(typename base::int_type __c = base::traits_type::eof())
      {
        if (__c != base::traits_type::eof())
          {
            if (count < (sizeof(array) / sizeof(CharT)))
              {
                array[count++] = static_cast<CharT>(__c);
              }
          }
        return __c;
      }

    virtual int
    sync()
      {
        ++sync_called;
        return 0;
      }
  };

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.format/output.stream/ostream.unformatted/put.pass.cpp
// test/input.output/iostream.format/output.stream/ostream.unformatted/write.pass.cpp
// test/input.output/iostream.format/output.stream/ostream.unformatted/flush.pass.cpp

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

template<class CharT>
class testbuf_unformatted : public basic_streambuf<CharT>
  {
  public:
    testbuf_unformatted()
      {
        sync_called = 0;
      }

    virtual
    ~testbuf_unformatted()
      {
      }

    int sync_called;

  protected:

    virtual int
    sync()
      {
        if (sync_called++ == 1)
        return -1;
        return 0;
      }
  };

#pragma GCC diagnostic pop

void
runTestUnformatted();

void
runTestUnformatted()
  {
    ts.reportInfo("Test ostream unformatted");

      {
        ts.setFunctionNameOrPrefix("put()");
        ts.setPreconditions("nosbuff");

        ostream os((streambuf*) 0);
        char c = 'a';
        os.put(c);
        ts.assertCondition(os.bad());
      }
      {
        ts.setFunctionNameOrPrefix("put()");

        testbuf_array<char> sb;
        ostream os(&sb);
        char c = 'a';
        os.put(c);
        ts.assertCondition(sb.count == 1);
        ts.assertCondition(sb.array[0] == 'a');
        ts.assertCondition(sb.array[1] == sb.getDefaultChar());
        ts.assertCondition(os.good());
      }
    // TODO: add wide support

      {
        ts.setFunctionNameOrPrefix("write()");
        ts.setPreconditions("nosbuff");

        ostream os((streambuf*) 0);
        const char s[] = "0123456789";
        // -1 is for the terminating \0
        os.write(s, static_cast<streamsize>(sizeof(s) / sizeof(s[0]) - 1));
        ts.assertCondition(os.bad());
      }
      {
        ts.setFunctionNameOrPrefix("write()");
        ts.setPreconditions("nosbuff");

        testbuf_array<char> sb;
        ostream os(&sb);
        const char s[] = "0123456789";
        // -1 is for the terminating \0
        size_t len = sizeof(s) / sizeof(s[0]) - 1;
        os.write(s, static_cast<streamsize>(len));
        ts.assertCondition(sb.count == len);
        ts.assertCondition(sb.array[0] == '0');
        ts.assertCondition(sb.array[len-1] == '9');
        ts.assertCondition(sb.array[len] == sb.getDefaultChar());
        ts.assertCondition(os.good());
      }
    // TODO: add wide support

      {
        ts.setFunctionNameOrPrefix("flush()");

        testbuf_unformatted<char> sb;
        ostream os(&sb);
        os.flush();
        ts.assertCondition(os.good());
        ts.assertCondition(sb.sync_called == 1);
        os.flush();
        ts.assertCondition(os.bad());
        ts.assertCondition(sb.sync_called == 2);
      }

  }

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.format/output.stream/ostream.manip/endl.pass.cpp
// test/input.output/iostream.format/output.stream/ostream.manip/ends.pass.cpp
// test/input.output/iostream.format/output.stream/ostream.manip/flush.pass.cpp

void
runTestManip();

void
runTestManip()
  {
    ts.reportInfo("Test ostream manipulators");

      {
        ts.setFunctionNameOrPrefix("endl()");

        testbuf_array<char> sb;
        ostream os(&sb);

        ts.assertCondition(sb.array[0] == sb.getDefaultChar());
        endl(os);
        ts.assertCondition(sb.array[0] == '\n');
        ts.assertCondition(sb.array[1] == sb.getDefaultChar());
        ts.assertCondition(sb.sync_called == 1);
        ts.assertCondition(os.good());
      }

    // TODO: add wchar_t

      {
        ts.setFunctionNameOrPrefix("ends()");

        testbuf_array<char> sb;
        ostream os(&sb);
        ts.assertCondition(sb.array[0] == sb.getDefaultChar());
        ends(os);
        ts.assertCondition(sb.array[0] == '\0');
        ts.assertCondition(sb.array[1] == sb.getDefaultChar());
        ts.assertCondition(os.good());
      }

    // TODO: add wchar_t

      {
        ts.setFunctionNameOrPrefix("flush()");

        testbuf_array<char> sb;
        ostream os(&sb);
        flush(os);
        ts.assertCondition(sb.sync_called == 1);
        ts.assertCondition(os.good());
      }

    // TODO: add wchar_t

  }

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.format/output.stream/ostream.seeks/seekp.pass.cpp
// test/input.output/iostream.format/output.stream/ostream.seeks/seekp2.pass.cpp
// test/input.output/iostream.format/output.stream/ostream.seeks/tellp.pass.cpp

static int seekpos_called;
static int seekoff_called = 0;

template<class CharT>
struct testbuf_seeks : public basic_streambuf<CharT>
  {
    typedef basic_streambuf<CharT> base;
    testbuf_seeks()
      {
      }
    virtual
    ~testbuf_seeks()
      {
      }

    typedef typename base::pos_type pos_type;
    typedef typename base::off_type off_type;

  protected:

    virtual typename base::pos_type
    seekpos(typename base::pos_type sp, ios_base::openmode which)
      {
        ++seekpos_called;
        if (sp != pos_type(-1))
          {
            // effective only for the first call
            ts.assertCondition(which == ios_base::out);
          }
        return sp;
      }

    virtual typename base::pos_type
    seekoff(typename base::off_type off, ios_base::seekdir way,
        ios_base::openmode which)
      {
        ++seekoff_called;
        if (off != off_type(-1))
          {
            ts.assertCondition(way == ios_base::beg);
            ts.assertCondition(which == ios_base::out);
          }
        return off;
      }

  };

template<class CharT>
struct testbuf_tellp : public basic_streambuf<CharT>
  {
    typedef basic_streambuf<CharT> base;
    testbuf_tellp()
      {
      }
    virtual
    ~testbuf_tellp()
      {
      }

  protected:

    typename base::pos_type
    seekoff(typename base::off_type off, ios_base::seekdir way,
        ios_base::openmode which)
      {
        ts.assertCondition(off == 0);
        ts.assertCondition(way == ios_base::cur);
        ts.assertCondition(which == ios_base::out);
        ++seekoff_called;
        return 10;
      }
  };

void
runTestSeeks();

void
runTestSeeks()
  {
    ts.reportInfo("Test ostream seeks");

      {
        ts.setFunctionNameOrPrefix("seekp(n)");
        ts.setPreconditions("os(0)");

        seekpos_called = 0;

        ostream os((streambuf*) 0);
        ts.assertCondition(&os.seekp(5) == &os);
        ts.assertCondition(seekpos_called == 0);
        ts.assertCondition(os.fail());
      }
      {
        ts.setFunctionNameOrPrefix("seekp(n)");

        seekpos_called = 0;

        testbuf_seeks<char> sb;
        ostream os(&sb);
        ts.assertCondition(&os.seekp(10) == &os);
        ts.assertCondition(seekpos_called == 1);
        ts.assertCondition(os.good());
        ts.assertCondition(&os.seekp(-1) == &os);
        ts.assertCondition(seekpos_called == 2);
        ts.assertCondition(os.fail());
      }

      {
        ts.setFunctionNameOrPrefix("seekp(n,d)");
        ts.setPreconditions("os(0)");

        seekoff_called = 0;

        ostream os((streambuf*) 0);
        ts.assertCondition(&os.seekp(5, ios_base::beg) == &os);
        ts.assertCondition(seekoff_called == 0);
        ts.assertCondition(os.fail());
      }

      {
        ts.setFunctionNameOrPrefix("seekp(n,d)");

        seekoff_called = 0;

        testbuf_seeks<char> sb;
        ostream os(&sb);
        ts.assertCondition(&os.seekp(10, ios_base::beg) == &os);
        ts.assertCondition(seekoff_called == 1);
        ts.assertConditionWithDetails(os.good(), "10");
        ts.assertCondition(&os.seekp(-1, ios_base::beg) == &os);
        ts.assertCondition(seekoff_called == 2);
        ts.assertConditionWithDetails(os.good(), "-1");
      }

      {
        ts.setFunctionNameOrPrefix("tellp()");
        ts.setPreconditions("os(0)");

        seekoff_called = 0;

        ostream os((streambuf*) 0);
        ts.assertCondition(os.tellp() == -1);
        ts.assertCondition(os.fail());
      }
      {
        ts.setFunctionNameOrPrefix("tellp()");

        seekoff_called = 0;

        testbuf_tellp<char> sb;
        ostream os(&sb);
        ts.assertCondition(os.tellp() == 10);
        ts.assertCondition(seekoff_called == 1);
        ts.assertCondition(os.good());
      }

  }

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.format/output.stream/ostream.sentry/construct.pass.cpp
// test/input.output/iostream.format/output.stream/ostream.sentry/destruct.pass.cpp

void
runTestSentry();

void
runTestSentry()
  {
    ts.reportInfo("Test ostream sentry");

    global_sync_called = 0;

      {
        ts.setFunctionNameOrPrefix("sentry");
        ts.setPreconditions("os(0)");

        ostream os((streambuf*) 0);
        ostream::sentry s(os);
        ts.assertCondition(!bool(s));
      }
    ts.assertCondition(global_sync_called == 0);

      {
        ts.setFunctionNameOrPrefix("sentry");

        testbuf<char> sb;
        ostream os(&sb);
        ostream::sentry s(os);
        ts.assertCondition(bool(s));
      }
    ts.assertCondition(global_sync_called == 0);

      {
        ts.setFunctionNameOrPrefix("sentry");
        ts.setPreconditions("tie()");

        testbuf<char> sb;
        ostream os(&sb);
        testbuf<char> sb2;
        ostream os2(&sb2);
        os.tie(&os2);
        ts.assertCondition(global_sync_called == 0);
        ostream::sentry s(os);
        ts.assertCondition(bool(s));
        ts.assertCondition(global_sync_called == 1);
      }

    global_sync_called = 0;

      {
        ts.setFunctionNameOrPrefix("sentry");
        ts.setPreconditions("unitbuf");

        testbuf<char> sb;
        ostream os(&sb);
        ostream::sentry s(os);
        ts.assertCondition(bool(s));
        unitbuf(os);
      }
    ts.assertCondition(global_sync_called == 1);

  }

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.format/std.manip/resetiosflags.pass.cpp
// test/input.output/iostream.format/std.manip/setbase.pass.cpp
// test/input.output/iostream.format/std.manip/setfill.pass.cpp
// test/input.output/iostream.format/std.manip/setiosflags.pass.cpp
// test/input.output/iostream.format/std.manip/setprecision.pass.cpp
// test/input.output/iostream.format/std.manip/setw.pass.cpp

void
runTestStdManip();

void
runTestStdManip()
  {
    ts.reportInfo("Test ostream std manip");

      {
        ts.setFunctionNameOrPrefix("resetiosflags()");

        testbuf<char> sb;
        ostream os(&sb);
        ts.assertCondition(os.flags() & ios_base::skipws);
        os << resetiosflags(ios_base::skipws);
        ts.assertCondition(!(os.flags() & ios_base::skipws));
      }
    // TODO: add wide support

      {
        ts.setFunctionNameOrPrefix("setbase()");

        testbuf<char> sb;
        ostream os(&sb);
        os << setbase(8);
        ts.assertCondition((os.flags() & ios_base::basefield) == ios_base::oct);
        os << setbase(10);
        ts.assertCondition((os.flags() & ios_base::basefield) == ios_base::dec);
        os << setbase(16);
        ts.assertCondition((os.flags() & ios_base::basefield) == ios_base::hex);
        os << setbase(15);
        ts.assertCondition((os.flags() & ios_base::basefield) == 0);
      }

      {
        ts.setFunctionNameOrPrefix("setfill()");

        testbuf<char> sb;
        ostream os(&sb);
        os << setfill('*');
        ts.assertCondition(os.fill() == '*');
      }

      {
        ts.setFunctionNameOrPrefix("setiosflags()");

        testbuf<char> sb;
        ostream os(&sb);
        ts.assertCondition(!(os.flags() & ios_base::oct));
        os << setiosflags(ios_base::oct);
        ts.assertCondition(os.flags() & ios_base::oct);
      }

      {
        ts.setFunctionNameOrPrefix("setprecision()");

        testbuf<char> sb;
        ostream os(&sb);
        os << setprecision(10);
        ts.assertCondition(os.precision() == 10);
      }

      {
        ts.setFunctionNameOrPrefix("setw()");

        testbuf<char> sb;
        ostream os(&sb);
        os << setw(10);
        ts.assertCondition(os.width() == 10);
      }
  }

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.format/output.streams/ostream.formatted/ostream.inserters.character/char.pass.cpp
// test/input.output/iostream.format/output.streams/ostream.formatted/ostream.inserters.character/char_pointer.pass.cpp
// test/input.output/iostream.format/output.streams/ostream.formatted/ostream.inserters.character/signed_char.pass.cpp
// test/input.output/iostream.format/output.streams/ostream.formatted/ostream.inserters.character/signed_char_pointer.pass.cpp
// test/input.output/iostream.format/output.streams/ostream.formatted/ostream.inserters.character/unsigned_char.pass.cpp
// test/input.output/iostream.format/output.streams/ostream.formatted/ostream.inserters.character/unsigned_char_pointer.pass.cpp

void
runTestInsertersCharacter();

void
runTestInsertersCharacter()
  {
    ts.reportInfo("Test ostream inserters character");

      {
        ts.setFunctionNameOrPrefix("operator<<(char)");
        ts.setPreconditions("os(0)");

        ostream os((streambuf*) 0);
        char c = 'a';
        os << c;
        ts.assertCondition(os.bad());
        ts.assertCondition(os.fail());
      }
      {
        ts.setFunctionNameOrPrefix("operator<<(char)");

        testbuf_array<char> sb;
        ostream os(&sb);
        char c = 'a';
        os << c;
        ts.assertCondition(sb.count == 1);
        ts.assertCondition(sb.array[0] == 'a');
        ts.assertCondition(sb.array[1] == sb.getDefaultChar());
      }
      {
        ts.setFunctionNameOrPrefix("operator<<(char)");
        ts.setPreconditions("width(2) right");

        testbuf_array<char> sb;
        ostream os(&sb);
        os.width(2);
        char c = 'a';
        os << c;
        ts.assertCondition(sb.count == 2);
        ts.assertCondition(sb.array[0] == ' ');
        ts.assertCondition(sb.array[1] == 'a');
        ts.assertCondition(sb.array[2] == sb.getDefaultChar());
        ts.assertCondition(os.width() == 0);
      }
      {
        ts.setFunctionNameOrPrefix("operator<<(char)");
        ts.setPreconditions("width(2) left");

        testbuf_array<char> sb;
        ostream os(&sb);
        os.width(2);
        left(os);
        char c = 'a';
        os << c;
        ts.assertCondition(sb.count == 2);
        ts.assertCondition(sb.array[0] == 'a');
        ts.assertCondition(sb.array[1] == ' ');
        ts.assertCondition(sb.array[2] == sb.getDefaultChar());
        ts.assertCondition(os.width() == 0);
      }
      {
        ts.setFunctionNameOrPrefix("operator<<(char)");
        ts.setPreconditions("width(5) right");

        testbuf_array<char> sb;
        ostream os(&sb);
        os.width(5);
        char c = 'a';
        os << c;
        ts.assertCondition(sb.count == 5);
        ts.assertCondition(sb.array[0] == ' ');
        ts.assertCondition(sb.array[1] == ' ');
        ts.assertCondition(sb.array[2] == ' ');
        ts.assertCondition(sb.array[3] == ' ');
        ts.assertCondition(sb.array[4] == 'a');
        ts.assertCondition(sb.array[5] == sb.getDefaultChar());
        ts.assertCondition(os.width() == 0);
      }
      {
        ts.setFunctionNameOrPrefix("operator<<(char)");
        ts.setPreconditions("width(5) left");

        testbuf_array<char> sb;
        ostream os(&sb);
        os.width(5);
        left(os);
        char c = 'a';
        os << c;
        ts.assertCondition(sb.count == 5);
        ts.assertCondition(sb.array[0] == 'a');
        ts.assertCondition(sb.array[1] == ' ');
        ts.assertCondition(sb.array[2] == ' ');
        ts.assertCondition(sb.array[3] == ' ');
        ts.assertCondition(sb.array[4] == ' ');
        ts.assertCondition(sb.array[5] == sb.getDefaultChar());
        ts.assertCondition(os.width() == 0);
      }

      {
        ts.setFunctionNameOrPrefix("operator<<(const_char*)");
        ts.setPreconditions("os(0)");

        ostream os((streambuf*) 0);
        const char* c = "123";
        os << c;
        ts.assertCondition(os.bad());
        ts.assertCondition(os.fail());
      }

      {
        ts.setFunctionNameOrPrefix("operator<<(const_char*)");
        ts.setPreconditions("width(3)");

        testbuf_array<char> sb;
        ostream os(&sb);
        const char* c = "123";
        os << c;
        ts.assertCondition(sb.count == 3);
        ts.assertCondition(sb.array[0] == '1');
        ts.assertCondition(sb.array[1] == '2');
        ts.assertCondition(sb.array[2] == '3');
        ts.assertCondition(sb.array[3] == sb.getDefaultChar());
      }
      {
        ts.setFunctionNameOrPrefix("operator<<(const_char*)");
        ts.setPreconditions("width(5) right");

        testbuf_array<char> sb;
        ostream os(&sb);
        os.width(5);
        const char* c = "123";
        os << c;
        ts.assertCondition(sb.count == 5);
        ts.assertCondition(sb.array[0] == ' ');
        ts.assertCondition(sb.array[1] == ' ');
        ts.assertCondition(sb.array[2] == '1');
        ts.assertCondition(sb.array[3] == '2');
        ts.assertCondition(sb.array[4] == '3');
        ts.assertCondition(sb.array[5] == sb.getDefaultChar());
        ts.assertCondition(os.width() == 0);
      }
      {
        ts.setFunctionNameOrPrefix("operator<<(const_char*)");
        ts.setPreconditions("width(5) left");

        testbuf_array<char> sb;
        ostream os(&sb);
        os.width(5);
        left(os);
        const char* c = "123";
        os << c;
        ts.assertCondition(sb.count == 5);
        ts.assertCondition(sb.array[0] == '1');
        ts.assertCondition(sb.array[1] == '2');
        ts.assertCondition(sb.array[2] == '3');
        ts.assertCondition(sb.array[3] == ' ');
        ts.assertCondition(sb.array[4] == ' ');
        ts.assertCondition(sb.array[5] == sb.getDefaultChar());
        ts.assertCondition(os.width() == 0);
      }

    // --- signed char

      {
        ts.setFunctionNameOrPrefix("operator<<(signed_char)");
        ts.setPreconditions("os(0)");

        ostream os((streambuf*) 0);
        signed char c = 'a';
        os << c;
        ts.assertCondition(os.bad());
        ts.assertCondition(os.fail());
      }
      {
        ts.setFunctionNameOrPrefix("operator<<(signed_char)");

        testbuf_array<char> sb;
        ostream os(&sb);
        signed char c = 'a';
        os << c;
        ts.assertCondition(sb.count == 1);
        ts.assertCondition(sb.array[0] == 'a');
        ts.assertCondition(sb.array[1] == sb.getDefaultChar());
      }
      {
        ts.setFunctionNameOrPrefix("operator<<(signed_char)");
        ts.setPreconditions("width(5) right");

        testbuf_array<char> sb;
        ostream os(&sb);
        os.width(5);
        signed char c = 'a';
        os << c;
        ts.assertCondition(sb.count == 5);
        ts.assertCondition(sb.array[0] == ' ');
        ts.assertCondition(sb.array[1] == ' ');
        ts.assertCondition(sb.array[2] == ' ');
        ts.assertCondition(sb.array[3] == ' ');
        ts.assertCondition(sb.array[4] == 'a');
        ts.assertCondition(sb.array[5] == sb.getDefaultChar());
        ts.assertCondition(os.width() == 0);
      }
      {
        ts.setFunctionNameOrPrefix("operator<<(signed_char)");
        ts.setPreconditions("width(5) left");

        testbuf_array<char> sb;
        ostream os(&sb);
        os.width(5);
        left(os);
        signed char c = 'a';
        os << c;
        ts.assertCondition(sb.count == 5);
        ts.assertCondition(sb.array[0] == 'a');
        ts.assertCondition(sb.array[1] == ' ');
        ts.assertCondition(sb.array[2] == ' ');
        ts.assertCondition(sb.array[3] == ' ');
        ts.assertCondition(sb.array[4] == ' ');
        ts.assertCondition(sb.array[5] == sb.getDefaultChar());
        ts.assertCondition(os.width() == 0);
      }

      {
        ts.setFunctionNameOrPrefix("operator<<(const_signed_char*)");
        ts.setPreconditions("os(0)");

        ostream os((streambuf*) 0);
        const signed char* c = (const signed char*) "123";
        os << c;
        ts.assertCondition(os.bad());
        ts.assertCondition(os.fail());
      }

      {
        ts.setFunctionNameOrPrefix("operator<<(const_signed_char*)");
        ts.setPreconditions("width(3)");

        testbuf_array<char> sb;
        ostream os(&sb);
        const signed char* c = (const signed char*) "123";
        os << c;
        ts.assertCondition(sb.count == 3);
        ts.assertCondition(sb.array[0] == '1');
        ts.assertCondition(sb.array[1] == '2');
        ts.assertCondition(sb.array[2] == '3');
        ts.assertCondition(sb.array[3] == sb.getDefaultChar());
      }
      {
        ts.setFunctionNameOrPrefix("operator<<(const_signed_char*)");
        ts.setPreconditions("width(5) right");

        testbuf_array<char> sb;
        ostream os(&sb);
        os.width(5);
        const signed char* c = (const signed char*) "123";
        os << c;
        ts.assertCondition(sb.count == 5);
        ts.assertCondition(sb.array[0] == ' ');
        ts.assertCondition(sb.array[1] == ' ');
        ts.assertCondition(sb.array[2] == '1');
        ts.assertCondition(sb.array[3] == '2');
        ts.assertCondition(sb.array[4] == '3');
        ts.assertCondition(sb.array[5] == sb.getDefaultChar());
        ts.assertCondition(os.width() == 0);
      }
      {
        ts.setFunctionNameOrPrefix("operator<<(const_signed_char*)");
        ts.setPreconditions("width(5) left");

        testbuf_array<char> sb;
        ostream os(&sb);
        os.width(5);
        left(os);
        const signed char* c = (const signed char*) "123";
        os << c;
        ts.assertCondition(sb.count == 5);
        ts.assertCondition(sb.array[0] == '1');
        ts.assertCondition(sb.array[1] == '2');
        ts.assertCondition(sb.array[2] == '3');
        ts.assertCondition(sb.array[3] == ' ');
        ts.assertCondition(sb.array[4] == ' ');
        ts.assertCondition(sb.array[5] == sb.getDefaultChar());
        ts.assertCondition(os.width() == 0);
      }

    // --- unsigned char

      {
        ts.setFunctionNameOrPrefix("operator<<(unsigned_char)");
        ts.setPreconditions("os(0)");

        ostream os((streambuf*) 0);
        unsigned char c = 'a';
        os << c;
        ts.assertCondition(os.bad());
        ts.assertCondition(os.fail());
      }
      {
        ts.setFunctionNameOrPrefix("operator<<(unsigned_char)");

        testbuf_array<char> sb;
        ostream os(&sb);
        unsigned char c = 'a';
        os << c;
        ts.assertCondition(sb.count == 1);
        ts.assertCondition(sb.array[0] == 'a');
        ts.assertCondition(sb.array[1] == sb.getDefaultChar());
      }
      {
        ts.setFunctionNameOrPrefix("operator<<(unsigned_char)");
        ts.setPreconditions("width(5) right");

        testbuf_array<char> sb;
        ostream os(&sb);
        os.width(5);
        unsigned char c = 'a';
        os << c;
        ts.assertCondition(sb.count == 5);
        ts.assertCondition(sb.array[0] == ' ');
        ts.assertCondition(sb.array[1] == ' ');
        ts.assertCondition(sb.array[2] == ' ');
        ts.assertCondition(sb.array[3] == ' ');
        ts.assertCondition(sb.array[4] == 'a');
        ts.assertCondition(sb.array[5] == sb.getDefaultChar());
        ts.assertCondition(os.width() == 0);
      }
      {
        ts.setFunctionNameOrPrefix("operator<<(unsigned_char)");
        ts.setPreconditions("width(5) left");

        testbuf_array<char> sb;
        ostream os(&sb);
        os.width(5);
        left(os);
        unsigned char c = 'a';
        os << c;
        ts.assertCondition(sb.count == 5);
        ts.assertCondition(sb.array[0] == 'a');
        ts.assertCondition(sb.array[1] == ' ');
        ts.assertCondition(sb.array[2] == ' ');
        ts.assertCondition(sb.array[3] == ' ');
        ts.assertCondition(sb.array[4] == ' ');
        ts.assertCondition(sb.array[5] == sb.getDefaultChar());
        ts.assertCondition(os.width() == 0);
      }

      {
        ts.setFunctionNameOrPrefix("operator<<(const_unsigned_char*)");
        ts.setPreconditions("os(0)");

        ostream os((streambuf*) 0);
        const unsigned char* c = (const unsigned char*) "123";
        os << c;
        ts.assertCondition(os.bad());
        ts.assertCondition(os.fail());
      }

      {
        ts.setFunctionNameOrPrefix("operator<<(const_unsigned_char*)");
        ts.setPreconditions("width(3)");

        testbuf_array<char> sb;
        ostream os(&sb);
        const unsigned char* c = (const unsigned char*) "123";
        os << c;
        ts.assertCondition(sb.count == 3);
        ts.assertCondition(sb.array[0] == '1');
        ts.assertCondition(sb.array[1] == '2');
        ts.assertCondition(sb.array[2] == '3');
        ts.assertCondition(sb.array[3] == sb.getDefaultChar());
      }
      {
        ts.setFunctionNameOrPrefix("operator<<(const_unsigned_char*)");
        ts.setPreconditions("width(5) right");

        testbuf_array<char> sb;
        ostream os(&sb);
        os.width(5);
        const unsigned char* c = (const unsigned char*) "123";
        os << c;
        ts.assertCondition(sb.count == 5);
        ts.assertCondition(sb.array[0] == ' ');
        ts.assertCondition(sb.array[1] == ' ');
        ts.assertCondition(sb.array[2] == '1');
        ts.assertCondition(sb.array[3] == '2');
        ts.assertCondition(sb.array[4] == '3');
        ts.assertCondition(sb.array[5] == sb.getDefaultChar());
        ts.assertCondition(os.width() == 0);
      }
      {
        ts.setFunctionNameOrPrefix("operator<<(const_unsigned_char*)");
        ts.setPreconditions("width(5) left");

        testbuf_array<char> sb;
        ostream os(&sb);
        os.width(5);
        left(os);
        const unsigned char* c = (const unsigned char*) "123";
        os << c;
        ts.assertCondition(sb.count == 5);
        ts.assertCondition(sb.array[0] == '1');
        ts.assertCondition(sb.array[1] == '2');
        ts.assertCondition(sb.array[2] == '3');
        ts.assertCondition(sb.array[3] == ' ');
        ts.assertCondition(sb.array[4] == ' ');
        ts.assertCondition(sb.array[5] == sb.getDefaultChar());
        ts.assertCondition(os.width() == 0);
      }

  }
#endif

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

#if 0
  runTestConstructor();

  runTestMove();

  runTestSwap();

  runTestUnformatted();

  runTestManip();

  runTestSeeks();

  runTestSentry();

  runTestStdManip();

  runTestInsertersCharacter();
#endif
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
