// -*- C++ -*-

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

// This test exercises the os::std::streambuf class.

// It is based on LLVM libcxx/test/input.output/stream.buffers/streambuf/*

// ----------------------------------------------------------------------------

// To calibrate this test, first define this macro, to use the system std
// library versions.

// Note: Not all test branches are available when running in the
// host environment.

//#define OS_INCLUDE_STD_CALIBRATION

#ifdef OS_INCLUDE_STD_CALIBRATION

#include <streambuf>
using namespace std;

#else

#include "portable/language/cpp/include/streambuf.h"
using namespace os::std;

#endif

// ----------------------------------------------------------------------------

#include "portable/language/cpp/include/type_traits.h"

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

os::infra::TestSuite_t ts;

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------

void
runTestTypes(void);

void
runTestTypes(void)
{
  // from LLVM input.output/stream.buffers/streambuf/types.pass.cpp
  ts.reportInfo("Test if types are properly expanded");
    {
      ts.setFunctionNameOrPrefix("types");

      ts.assertCondition((os::std::is_same<streambuf::char_type, char>::value));
      ts.assertCondition((os::std::is_same<streambuf::traits_type, char_traits<char> >::value));
      ts.assertCondition((os::std::is_same<streambuf::int_type, char_traits<char>::int_type>::value));
      ts.assertCondition((os::std::is_same<streambuf::pos_type, char_traits<char>::pos_type>::value));
      ts.assertCondition((os::std::is_same<streambuf::off_type, char_traits<char>::off_type>::value));

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

      ts.assertCondition((os::std::is_same<wstreambuf::char_type, wchar_t>::value));
      ts.assertCondition((os::std::is_same<wstreambuf::traits_type, char_traits<wchar_t> >::value));
      ts.assertCondition((os::std::is_same<wstreambuf::int_type, char_traits<wchar_t>::int_type>::value));
      ts.assertCondition((os::std::is_same<wstreambuf::pos_type, char_traits<wchar_t>::pos_type>::value));
      ts.assertCondition((os::std::is_same<wstreambuf::off_type, char_traits<wchar_t>::off_type>::value));

#endif
    }
}

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

template<class CharT>
  class TestConstructor : public basic_streambuf<CharT>
  {
  public:
    TestConstructor()
    {
      // At this point the parent constructor was executed, so  all
      // pointers should be initialised to nullptr.

      // Check one by one.
      ts.assertCondition(this->eback() == nullptr);
      ts.assertCondition(this->gptr() == nullptr);
      ts.assertCondition(this->egptr() == nullptr);
      ts.assertCondition(this->pbase() == nullptr);
      ts.assertCondition(this->pptr() == nullptr);
      ts.assertCondition(this->epptr() == nullptr);
    }
  };

#pragma GCC diagnostic pop

void
runTestConstructor(void);

void
runTestConstructor(void)
{
  // 27.6.3.1 basic_streambuf constructors
  // basic_streambuf();
  // — all its pointer member objects to null pointers,
  ts.reportInfo("Test if constructor clears pointer members");
    {
      ts.setFunctionNameOrPrefix("basic_streambuf()");

      TestConstructor<char> t;
    }
}

// ----------------------------------------------------------------------------

#if !defined(OS_INCLUDE_STD_CALIBRATION)

// The libstdc++v3 basic_streambuf() constructors are private, not protected
// as in C++11

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

// inspired from LLVM libcxx
// test/input.output/stream.buffers/streambuf/streambuf.cons/copy.pass.cpp

template<class CharT>
  class TestCopyConstructor : public basic_streambuf<CharT>
  {
  public:
    typedef basic_streambuf<CharT> base;
    TestCopyConstructor()
    {
      ;
    }

    TestCopyConstructor(const TestCopyConstructor& t)
        : basic_streambuf<CharT>(t)
    {
      // At this point the parent constructor was executed, so all
      // pointers should be initialised to the same values as the
      // input class.

      // Check one by one.
      ts.assertCondition(this->eback() == t.eback());
      ts.assertCondition(this->gptr() == t.gptr());
      ts.assertCondition(this->egptr() == t.egptr());
      ts.assertCondition(this->pbase() == t.pbase());
      ts.assertCondition(this->pptr() == t.pptr());
      ts.assertCondition(this->epptr() == t.epptr());

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      ts.assertCondition(this->getloc() == t.getloc());
#endif
    }

    // These two are needed since base:setg() and base::setp() are private
    void
    setg(CharT* gbeg, CharT* gnext, CharT* gend)
    {
      base::setg(gbeg, gnext, gend);
    }

    void
    setp(CharT* pbeg, CharT* pend)
    {
      base::setp(pbeg, pend);
    }

  };

#pragma GCC diagnostic pop

void
runTestCopyConstructor(void);

void
runTestCopyConstructor(void)
{

  // basic_streambuf(const basic_streambuf& rhs);
  // Postconditions: ...
  ts.reportInfo("Test copy constructor with default pointer members");
    {
      ts.setFunctionNameOrPrefix("basic_streambuf(&)");
      ts.setPreconditions("default");

      TestCopyConstructor<char> t;
      TestCopyConstructor<char> t2 = t;
    }

  ts.reportInfo("Test copy constructor with different pointer members");
    {
      ts.setFunctionNameOrPrefix("basic_streambuf(&)");
      ts.setPreconditions("different");

      char g1, g2, g3, p1, p3;
      TestCopyConstructor<char> t;
      t.setg(&g1, &g2, &g3);
      t.setp(&p1, &p3);

      TestCopyConstructor<char> t2 = t;
    }
}

#endif

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

template<class CharT>
  class TestPositioning : public basic_streambuf<CharT>
  {
  public:
    TestPositioning()
    {
    }
  };

#pragma GCC diagnostic pop

void
runTestPositioning(void);

void
runTestPositioning(void)
{
  // inspired from LLVM libcxx
  // test/input.output/stream.buffers/streambuf/streambuf.cons/pubseekoff.pass.cpp
  ts.reportInfo("Test initial streambuf::pubseekoff()");
    {
      ts.setFunctionNameOrPrefix("pubseekoff()");

      TestPositioning<char> t;
      ts.assertCondition(t.pubseekoff(0, ios_base::beg) == -1);
      ts.assertCondition(t.pubseekoff(0, ios_base::beg, ios_base::app) == -1);
    }

  // inspired from LLVM libcxx
  // test/input.output/stream.buffers/streambuf/streambuf.cons/pubseekpos.pass.cpp
  ts.reportInfo("Test initial streambuf::pubseekpos()");
    {
      ts.setFunctionNameOrPrefix("pubseekpos()");

      TestPositioning<char> t;
      ts.assertCondition(t.pubseekpos(0, ios_base::app) == -1);
    }

  // inspired from LLVM libcxx
  // test/input.output/stream.buffers/streambuf/streambuf.cons/pubsetbuf.pass.cpp
  ts.reportInfo("Test initial streambuf::pubsetbuf()");
  ts.setFunctionNameOrPrefix("pubsetbuf()");
    {
      TestPositioning<char> t;
      ts.assertCondition(t.pubsetbuf(0, 0) == &t);
    }

  // inspired from LLVM libcxx
  // test/input.output/stream.buffers/streambuf/streambuf.cons/pubsync.pass.cpp
  ts.reportInfo("Test initial streambuf::pubsync()");
    {
      ts.setFunctionNameOrPrefix("pubsync()");

      TestPositioning<char> t;
      ts.assertCondition(t.pubsync() == 0);
    }
}

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

// inspired from LLVM libcxx
// test/input.output/stream.buffers/streambuf/streambuf.pub.get/in_avail.pass.cpp

template<class CharT>
  class TestInAvail : public basic_streambuf<CharT>
  {
  public:
    typedef basic_streambuf<CharT> base;

    TestInAvail()
    {
      showmanyc_called = 0;
    }

    void
    setg(CharT* gbeg, CharT* gnext, CharT* gend)
    {
      base::setg(gbeg, gnext, gend);
    }

    int showmanyc_called;

  protected:
    streamsize
    showmanyc()
    {
      ++showmanyc_called;
      return 5;
    }
  };

#pragma GCC diagnostic pop

void
runTestInAvail(void);

void
runTestInAvail(void)
{
  ts.reportInfo("Test streambuf::in_avail()");
    {
      ts.setFunctionNameOrPrefix("in_avail()");

      TestInAvail<char> t;
      ts.assertCondition(t.in_avail() == 5);
      ts.assertCondition(t.showmanyc_called == 1);
      char in[5];
      t.setg(in, in + 2, in + 5);
      ts.assertCondition(t.in_avail() == 3);
    }
}

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

// inspired from LLVM libcxx
// test/input.output/stream.buffers/streambuf/streambuf.pub.get/sbumpc.pass.cpp

class TestSbumpc : public basic_streambuf<char>
{
public:
  typedef basic_streambuf<char> base;

  TestSbumpc()
  {
    uflow_called = 0;
  }

  void
  setg(char* gbeg, char* gnext, char* gend)
  {
    base::setg(gbeg, gnext, gend);
  }

  int uflow_called;

protected:
  int_type
  uflow()
  {
    ++uflow_called;
    return 'a';
  }
};

#pragma GCC diagnostic pop

void
runTestSbumpc(void);

void
runTestSbumpc(void)
{
  ts.reportInfo("Test streambuf::sbumpc()");
    {
      ts.setFunctionNameOrPrefix("sbumpc()");

      TestSbumpc t;
      ts.assertCondition(t.uflow_called == 0);
      ts.assertCondition(t.sbumpc() == 'a');
      ts.assertCondition(t.uflow_called == 1);
      char in[] = "ABC";
      t.setg(in, in, in + sizeof(in));
      ts.assertCondition(t.sbumpc() == 'A');
      ts.assertCondition(t.uflow_called == 1);
      ts.assertCondition(t.sbumpc() == 'B');
      ts.assertCondition(t.uflow_called == 1);
    }
}

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

// inspired from LLVM libcxx
// test/input.output/stream.buffers/streambuf/streambuf.pub.get/sgetc.pass.cpp

class TestSgetc : public basic_streambuf<char>
{
public:
  typedef basic_streambuf<char> base;

  TestSgetc()
  {
    underflow_called = 0;
  }

  void
  setg(char* gbeg, char* gnext, char* gend)
  {
    base::setg(gbeg, gnext, gend);
  }

  int underflow_called;

protected:
  int_type
  underflow()
  {
    ++underflow_called;
    return 'a';
  }
};

#pragma GCC diagnostic pop

void
runTestSgetc(void);

void
runTestSgetc(void)
{
  ts.reportInfo("Test streambuf::sgetc()");
    {
      ts.setFunctionNameOrPrefix("sgetc()");

      TestSgetc t;
      ts.assertCondition(t.underflow_called == 0);
      ts.assertCondition(t.sgetc() == 'a');
      ts.assertCondition(t.underflow_called == 1);
      char in[] = "ABC";
      t.setg(in, in, in + sizeof(in));
      ts.assertCondition(t.sgetc() == 'A');
      ts.assertCondition(t.underflow_called == 1);
      ts.assertCondition(t.sgetc() == 'A');
      ts.assertCondition(t.underflow_called == 1);
    }
}

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

// inspired from LLVM libcxx
// test/from LLVM input.output/stream.buffers/streambuf/streambuf.pub.get/sgetn.pass.cpp

class TestSgetn : public basic_streambuf<char>
{
public:
  TestSgetn()
  {
    xsgetn_called = 0;
  }

  int xsgetn_called;

protected:
  streamsize
  xsgetn(char_type* s __attribute__((unused)),
      streamsize n __attribute__((unused)))
  {
    ++xsgetn_called;
    return 10;
  }
};

#pragma GCC diagnostic pop

void
runTestSgetn(void);

void
runTestSgetn(void)
{
  ts.reportInfo("Test streambuf::sgetn()");
    {
      ts.setFunctionNameOrPrefix("sgetn()");

      TestSgetn t;
      ts.assertCondition(t.xsgetn_called == 0);
      ts.assertCondition(t.sgetn(0, 0) == 10);
      ts.assertCondition(t.xsgetn_called == 1);
    }
}

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

// inspired from LLVM libcxx
// test/input.output/stream.buffers/streambuf/streambuf.pub.get/snextc.pass.cpp

class TestSnextc : public basic_streambuf<char>
{
public:
  typedef basic_streambuf<char> base;

  TestSnextc()
  {
    uflow_called = 0;
  }

  void
  setg(char* gbeg, char* gnext, char* gend)
  {
    base::setg(gbeg, gnext, gend);
  }

  int uflow_called;

protected:
  int_type
  uflow()
  {
    ++uflow_called;
    return 'a';
  }
};

#pragma GCC diagnostic pop

void
runTestSnextc(void);

void
runTestSnextc(void)
{
  ts.reportInfo("Test streambuf::snextc()");
    {
      ts.setFunctionNameOrPrefix("snextc()");

      TestSnextc t;
      ts.assertCondition(t.uflow_called == 0);
      ts.assertCondition(t.snextc() == -1);
      ts.assertCondition(t.uflow_called == 1);
      char in[] = "ABC";
      t.setg(in, in, in + sizeof(in));
      ts.assertCondition(t.snextc() == 'B');
      ts.assertCondition(t.uflow_called == 1);
      ts.assertCondition(t.snextc() == 'C');
      ts.assertCondition(t.uflow_called == 1);
    }
}

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

// inspired from LLVM libcxx
// test/input.output/stream.buffers/streambuf/streambuf.pub.pback/sputbackc.pass.cpp

class TestSputback : public basic_streambuf<char>
{
public:
  typedef basic_streambuf<char> base;

  TestSputback()
  {
    pbackfail_called = 0;
  }

  void
  setg(char* gbeg, char* gnext, char* gend)
  {
    base::setg(gbeg, gnext, gend);
  }

  int pbackfail_called;

protected:
  int_type
  pbackfail(int_type c __attribute__((unused)) = traits_type::eof())
  {
    ++pbackfail_called;
    return 'a';
  }
};

#pragma GCC diagnostic pop

void
runTestSputback(void);

void
runTestSputback(void)
{
  ts.reportInfo("Test streambuf::sputbackc()");
    {
      ts.setFunctionNameOrPrefix("sputbackc()");

      TestSputback t;
      ts.assertCondition(t.pbackfail_called == 0);
      ts.assertCondition(t.sputbackc('A') == 'a');
      ts.assertCondition(t.pbackfail_called == 1);
      char in[] = "ABC";
      t.setg(in, in + 1, in + sizeof(in));
      ts.assertCondition(t.sputbackc('A') == 'A');
      ts.assertCondition(t.pbackfail_called == 1);
      ts.assertCondition(t.sputbackc('A') == 'a');
      ts.assertCondition(t.pbackfail_called == 2);
    }
}

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

// inspired from LLVM libcxx
// test/input.output/stream.buffers/streambuf/streambuf.pub.pback/sungetc.pass.cpp

class TestSungetc : public basic_streambuf<char>
{
public:
  typedef basic_streambuf<char> base;

  TestSungetc()
  {
    pbackfail_called = 0;
  }

  void
  setg(char* gbeg, char* gnext, char* gend)
  {
    base::setg(gbeg, gnext, gend);
  }

  int pbackfail_called;

protected:
  int_type
  pbackfail(int_type c __attribute__((unused)) = traits_type::eof())
  {
    ++pbackfail_called;
    return 'a';
  }
};

#pragma GCC diagnostic pop

void
runTestSungetc(void);

void
runTestSungetc(void)
{
  ts.reportInfo("Test streambuf::sungetc()");
    {
      ts.setFunctionNameOrPrefix("sungetc()");

      TestSungetc t;
      ts.assertCondition(t.pbackfail_called == 0);
      ts.assertCondition(t.sungetc() == 'a');
      ts.assertCondition(t.pbackfail_called == 1);
      char in[] = "ABC";
      t.setg(in, in + 1, in + sizeof(in));
      ts.assertCondition(t.sungetc() == 'A');
      ts.assertCondition(t.pbackfail_called == 1);
      ts.assertCondition(t.sungetc() == 'a');
      ts.assertCondition(t.pbackfail_called == 2);
    }
}

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

// inspired from LLVM libcxx
// test/input.output/stream.buffers/streambuf/streambuf.pub.put/sputc.pass.cpp

class TestSputc : public basic_streambuf<char>
{
public:
  typedef basic_streambuf<char> base;

  TestSputc()
  {
    overflow_called = 0;
  }

  void
  setg(char* gbeg, char* gnext, char* gend)
  {
    base::setg(gbeg, gnext, gend);
  }

  void
  setp(char* pbeg, char* pend)
  {
    base::setp(pbeg, pend);
  }

  int overflow_called;

protected:
  int_type
  overflow(int_type c __attribute__((unused)) = traits_type::eof())
  {
    ++overflow_called;
    return 'a';
  }
};

#pragma GCC diagnostic pop

void
runTestSputc(void);

void
runTestSputc(void)
{
  ts.reportInfo("Test streambuf::sputc()");
    {
      ts.setFunctionNameOrPrefix("sputc()");
      ts.setPreconditions("nosetp");

      TestSputc t;
      ts.assertCondition(t.overflow_called == 0);
      ts.assertCondition(t.sputc('A') == 'a');
      ts.assertCondition(t.overflow_called == 1);
      char out[3] =
        { 0 };
      ts.setFunctionNameOrPrefix("sputc()_setp_A");
      t.setp(out, out + sizeof(out));
      ts.assertCondition(t.sputc('A') == 'A');
      ts.assertCondition(t.overflow_called == 1);
      ts.assertCondition(out[0] == 'A');
      ts.setFunctionNameOrPrefix("sputc()_setp_B");
      ts.assertCondition(t.sputc('B') == 'B');
      ts.assertCondition(t.overflow_called == 1);
      ts.assertCondition(out[0] == 'A');
      ts.assertCondition(out[1] == 'B');
    }
}

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

// inspired from LLVM libcxx
// test/input.output/stream.buffers/streambuf/streambuf.pub.put/sputn.pass.cpp

class TestSputn : public basic_streambuf<char>
{
public:
  TestSputn()
  {
    xsputn_called = 0;
  }

  int xsputn_called;

protected:
  streamsize
  xsputn(const char_type* s __attribute__((unused)),
      streamsize n __attribute__((unused)))
  {
    ++xsputn_called;
    return 5;
  }
};

#pragma GCC diagnostic pop

void
runTestSputn(void);

void
runTestSputn(void)
{
  ts.reportInfo("Test streambuf::sputn()");
    {
      ts.setFunctionNameOrPrefix("sputn()");

      TestSputn t;
      ts.assertCondition(t.xsputn_called == 0);
      ts.assertCondition(t.sputn(0, 0) == 5);
      ts.assertCondition(t.xsputn_called == 1);
    }
}

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

// inspired from LLVM libcxx
// TestAssignOperator/input.output/stream.buffers/streambuf/streambuf.assign/assign.pass.cpp

template<class CharT>
  class TestAssignOperator : public basic_streambuf<CharT>
  {
  public:
    typedef basic_streambuf<CharT> base;
    TestAssignOperator()
    {
    }

    TestAssignOperator&
    operator=(const TestAssignOperator& t)
    {
      base::operator=(t);
      ts.assertCondition(this->eback() == t.eback());
      ts.assertCondition(this->gptr() == t.gptr());
      ts.assertCondition(this->egptr() == t.egptr());
      ts.assertCondition(this->pbase() == t.pbase());
      ts.assertCondition(this->pptr() == t.pptr());
      ts.assertCondition(this->epptr() == t.epptr());
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      ts.assertCondition(this->getloc() == t.getloc());
#endif
      return *this;
    }

    void
    setg(CharT* gbeg, CharT* gnext, CharT* gend)
    {
      base::setg(gbeg, gnext, gend);
    }

    void
    setp(CharT* pbeg, CharT* pend)
    {
      base::setp(pbeg, pend);
    }
  };

#pragma GCC diagnostic pop

void
runTestAssignOperator(void);

void
runTestAssignOperator(void)
{
    {
      ts.reportInfo("Test streambuf::operator=() with default members");
        {
          ts.setFunctionNameOrPrefix("operator=()");
          ts.setPreconditions("default");

          TestAssignOperator<char> t;
          TestAssignOperator<char> t2;
          t2 = t;
        }

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
        {
          TestAssignOperator<wchar_t> t;
          TestAssignOperator<wchar_t> t2;
          t2 = t;
        }
#endif

      ts.reportInfo("Test streambuf::operator=() with different members");
        {
          ts.setFunctionNameOrPrefix("operator=()");
          ts.setPreconditions("different");

          char g1, g2, g3, p1, p3;
          TestAssignOperator<char> t;
          t.setg(&g1, &g2, &g3);
          t.setp(&p1, &p3);
          TestAssignOperator<char> t2;
          t2 = t;
        }

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
        {
          wchar_t g1, g2, g3, p1, p3;
          TestAssignOperator<wchar_t> t;
          t.setg(&g1, &g2, &g3);
          t.setp(&p1, &p3);
          TestAssignOperator<wchar_t> t2;
          t2 = t;
        }
#endif

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      ts.reportInfo("Test streambuf::operator=() with different locale");
      locale::global(locale(LOCALE_en_US_UTF_8));
        {
          TestAssignOperator<char> t;
          TestAssignOperator<char> t2;
          t2 = t;
        }

        {
          TestAssignOperator<wchar_t> t;
          TestAssignOperator<wchar_t> t2;
          t2 = t;
        }
#endif
    }
}

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

// inspired from LLVM libcxx
// TestAssignOperator/input.output/stream.buffers/streambuf/streambuf.assign/swap.pass.cpp

template<class CharT>
  class TestSwap : public basic_streambuf<CharT>
  {
  public:
    typedef basic_streambuf<CharT> base;
    TestSwap()
    {
      swap_count = 0;
    }

    void
    swap(TestSwap& t)
    {
      TestSwap old_this(*this);
      TestSwap old_that(t);

      base::swap(t);

      ts.assertCondition(this->eback() == old_that.eback());
      ts.assertCondition(this->gptr() == old_that.gptr());
      ts.assertCondition(this->egptr() == old_that.egptr());
      ts.assertCondition(this->pbase() == old_that.pbase());
      ts.assertCondition(this->pptr() == old_that.pptr());
      ts.assertCondition(this->epptr() == old_that.epptr());
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      ts.assertCondition(this->getloc() == old_that.getloc());
#endif

      ts.assertCondition(t.eback() == old_this.eback());
      ts.assertCondition(t.gptr() == old_this.gptr());
      ts.assertCondition(t.egptr() == old_this.egptr());
      ts.assertCondition(t.pbase() == old_this.pbase());
      ts.assertCondition(t.pptr() == old_this.pptr());
      ts.assertCondition(t.epptr() == old_this.epptr());
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      ts.assertCondition(t.getloc() == old_this.getloc());
#endif

      ++swap_count;
    }

    void
    setg(CharT* gbeg, CharT* gnext, CharT* gend)
    {
      base::setg(gbeg, gnext, gend);
    }

    void
    setp(CharT* pbeg, CharT* pend)
    {
      base::setp(pbeg, pend);
    }

    int swap_count;
  };

void
runTestSwap(void);

void
runTestSwap(void)
{
  ts.reportInfo("Test streambuf::swap() with default members");
    {
      ts.setFunctionNameOrPrefix("swap()");
      ts.setPreconditions("default");

      TestSwap<char> t;
      TestSwap<char> t2;

      ts.assertCondition(t.swap_count == 0);
      ts.assertCondition(t2.swap_count == 0);

#if defined(USE_BINARY_SWAP)
      swap(t2, t);
#else
      t.swap(t2);
#endif

      ts.assertCondition(t.swap_count == 1);
      ts.assertConditionWithDetails(t2.swap_count == 0, "untouched");
    }

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
    {
      TestSwap<wchar_t> t;
      TestSwap<wchar_t> t2;
#if defined(USE_BINARY_SWAP)
      swap(t2, t);
#else
      t.swap(t2);
#endif
    }
#endif

  ts.reportInfo("Test streambuf::swap() with different members");
    {
      ts.setFunctionNameOrPrefix("swap()");
      ts.setPreconditions("different");

      char g1, g2, g3, p1, p3;
      TestSwap<char> t;
      t.setg(&g1, &g2, &g3);
      t.setp(&p1, &p3);
      TestSwap<char> t2;

      ts.assertCondition(t.swap_count == 0);
      ts.assertCondition(t2.swap_count == 0);

#if defined(USE_BINARY_SWAP)
      swap(t2, t);
#else
      t.swap(t2);
#endif

      ts.assertCondition(t.swap_count == 1);
      ts.assertConditionWithDetails(t2.swap_count == 0, "untouched");
    }

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
    {
      wchar_t g1, g2, g3, p1, p3;
      TestSwap<wchar_t> t;
      t.setg(&g1, &g2, &g3);
      t.setp(&p1, &p3);
      TestSwap<wchar_t> t2;
#if defined(USE_BINARY_SWAP)
      swap(t2, t);
#else
      t.swap(t2);
#endif
    }
#endif

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
  ts.reportInfo("Test streambuf::swap() with different locale");
  locale::global(locale(LOCALE_en_US_UTF_8));
    {
      TestSwap<char> t;
      TestSwap<char> t2;
#if defined(USE_BINARY_SWAP)
      swap(t2, t);
#else
      t.swap(t2);
#endif
    }
    {
      TestSwap<wchar_t> t;
      TestSwap<wchar_t> t2;
#if defined(USE_BINARY_SWAP)
      swap(t2, t);
#else
      t.swap(t2);
#endif
    }
#endif
}

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

// inspired from LLVM libcxx
// TestAssignOperator/input.output/stream.buffers/streambuf/streambuf.get.area/gbump.pass.cpp

template<class CharT>
  class TestGbump : public basic_streambuf<CharT>
  {
  public:
    typedef basic_streambuf<CharT> base;

    TestGbump()
    {
    }

    void
    setg(CharT* gbeg, CharT* gnext, CharT* gend)
    {
      base::setg(gbeg, gnext, gend);
    }

    void
    gbump(int n)
    {
      CharT* gbeg = base::eback();
      CharT* gnext = base::gptr();
      CharT* gend = base::egptr();
      base::gbump(n);

      ts.assertCondition(base::eback() == gbeg);
      ts.assertCondition(base::gptr() == gnext+n);
      ts.assertCondition(base::egptr() == gend);
    }
  };

void
runTestGbump(void);

void
runTestGbump(void)
{
  ts.reportInfo("Test streambuf::gbump()");
    {
      ts.setFunctionNameOrPrefix("gbump()");

      TestGbump<char> t;
      char in[] = "ABCDE";
      t.setg(in, in + 1, in + sizeof(in) / sizeof(in[0]));
      t.gbump(2);
    }

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
    {
      TestGbump<wchar_t> t;
      wchar_t in[] = L"ABCDE";
      t.setg(in, in+1, in+sizeof(in)/sizeof(in[0]));
      t.gbump(3);
    }
#endif
}

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

// inspired from LLVM libcxx
// TestAssignOperator/input.output/stream.buffers/streambuf/streambuf.get.area/setg.pass.cpp

template<class CharT>
  class TestSetg : public basic_streambuf<CharT>
  {
  public:
    typedef basic_streambuf<CharT> base;

    TestSetg()
    {
    }

    void
    setg(CharT* gbeg, CharT* gnext, CharT* gend)
    {
      base::setg(gbeg, gnext, gend);

      ts.assertCondition(base::eback() == gbeg);
      ts.assertCondition(base::gptr() == gnext);
      ts.assertCondition(base::egptr() == gend);
    }
  };

void
runTestSetg(void);

void
runTestSetg(void)
{
  ts.reportInfo("Test streambuf::setg()");
    {
      ts.setFunctionNameOrPrefix("setg()");

      TestSetg<char> t;
      char in[] = "ABC";
      t.setg(in, in + 1, in + sizeof(in) / sizeof(in[0]));
    }

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
    {
      TestSetg<wchar_t> t;
      wchar_t in[] = L"ABC";
      t.setg(in, in + 1, in + sizeof(in) / sizeof(in[0]));
    }
#endif
}

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

// inspired from LLVM libcxx
// TestAssignOperator/input.output/stream.buffers/streambuf/streambuf.put.area/pbump.pass.cpp

template<class CharT>
  class TestPbump : public basic_streambuf<CharT>
  {
  public:
    typedef basic_streambuf<CharT> base;

    TestPbump()
    {
    }

    void
    setp(CharT* pbeg, CharT* pend)
    {
      base::setp(pbeg, pend);
    }

    void
    pbump(int n)
    {
      CharT* pbeg = base::pbase();
      CharT* pnext = base::pptr();
      CharT* pend = base::epptr();

      base::pbump(n);

      ts.assertCondition(base::pbase() == pbeg);
      ts.assertCondition(base::pptr() == pnext + n);
      ts.assertCondition(base::epptr() == pend);
    }
  };

void
runTestPbump(void);

void
runTestPbump(void)
{
  ts.reportInfo("Test streambuf::pbump()");
    {
      TestPbump<char> t;
      char in[] = "ABCDE";
      t.setp(in, in + sizeof(in) / sizeof(in[0]));

      ts.setFunctionNameOrPrefix("pbump()");
      ts.setInputValues("2");

      t.pbump(2);

      ts.setFunctionNameOrPrefix("pbump()");
      ts.setInputValues("1");

      t.pbump(1);
    }

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
    {
      TestPbump<wchar_t> t;
      wchar_t in[] = L"ABCDE";
      t.setp(in, in + sizeof(in) / sizeof(in[0]));
      t.pbump(3);
      t.pbump(1);
    }
#endif
}

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

// inspired from LLVM libcxx
// TestAssignOperator/input.output/stream.buffers/streambuf/streambuf.put.area/setp.pass.cpp

template<class CharT>
  class TestSetp : public basic_streambuf<CharT>
  {
  public:
    typedef basic_streambuf<CharT> base;

    TestSetp()
    {
    }

    void
    setp(CharT* pbeg, CharT* pend)
    {
      base::setp(pbeg, pend);

      ts.assertCondition(base::pbase() == pbeg);
      ts.assertCondition(base::pptr() == pbeg);
      ts.assertCondition(base::epptr() == pend);
    }
  };

void
runTestSetp();

void
runTestSetp()
{
  ts.reportInfo("Test streambuf::setp()");
    {
      ts.setFunctionNameOrPrefix("setp()");

      TestSetp<char> t;
      char in[] = "ABC";
      t.setp(in, in + sizeof(in) / sizeof(in[0]));
    }

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
    {
      TestSetp<wchar_t> t;
      wchar_t in[] = L"ABC";
      t.setp(in, in + sizeof(in) / sizeof(in[0]));
    }
#endif
}

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

// inspired from LLVM libcxx
// TestAssignOperator/input.output/stream.buffers/streambuf/streambuf.virtuals/streambuf.virt.get/showmanyc.pass.cpp

template<class CharT>
  class TestShowmanycBase : public basic_streambuf<CharT>
  {
  public:
    TestShowmanycBase()
    {
    }

  };

template<class CharT>
  class TestShowmanycCustom : public basic_streambuf<CharT>
  {
  public:
    typedef basic_streambuf<CharT> base;

    TestShowmanycCustom()
    {
      showmanyc_called = 0;
    }

    virtual
    ~TestShowmanycCustom()
    {
    }

    int showmanyc_called;

    virtual streamsize
    showmanyc()
    {
      ++showmanyc_called;
      return base::showmanyc();
    }
  };

void
runTestShowmanyc();

void
runTestShowmanyc()
{
  ts.reportInfo("Test streambuf::showmanyc()");
    {
      ts.setFunctionNameOrPrefix("showmanyc()");

      TestShowmanycBase<char> t;

      // This class does not overwrite showmanyc(), it should use the
      // default one provided by basic_streambuf, which returns 0
      ts.assertCondition(t.in_avail() == 0);
    }

    {
      ts.setFunctionNameOrPrefix("showmanyc()");
      ts.setPreconditions("reference");

      TestShowmanycCustom<char> t;
      basic_streambuf<char>& t2 = t;

      ts.assertCondition(t.showmanyc_called == 0);
      // Call it via reference to base class, to check both virtual call
      // and further call to base class member function
      ts.assertCondition(t2.in_avail() == 0);
      ts.assertCondition(t.showmanyc_called == 1);
    }
}

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

// inspired from LLVM libcxx
// TestAssignOperator/input.output/stream.buffers/streambuf/streambuf.virtuals/streambuf.virt.get/uflow.pass.cpp

class TestUflowBase : public basic_streambuf<char>
{
public:
  TestUflowBase()
  {
  }
};

class TestUflowCustom : public basic_streambuf<char>
{
public:
  typedef basic_streambuf<char> base;

  TestUflowCustom()
  {
    uflow_count = 0;
  }

  virtual
  ~TestUflowCustom()
  {
  }

  int uflow_count;

  virtual int_type
  uflow()
  {
    ++uflow_count;
    return base::uflow();
  }
};

void
runTestUflow(void);

void
runTestUflow(void)
{
  ts.reportInfo("Test streambuf::uflow()");
    {
      ts.setFunctionNameOrPrefix("uflow()");

      TestUflowBase t;
      // This class does not overwrite uflow(), it should use the
      // default one provided by basic_streambuf, which returns eof()
      ts.assertCondition(t.sbumpc() == char_traits<char>::eof());
    }

    {
      ts.setFunctionNameOrPrefix("uflow()");
      ts.setPreconditions("reference");

      TestUflowCustom t;
      basic_streambuf<char>& t2 = t;
      ts.assertCondition(t.uflow_count == 0);
      // Call it via reference to base class, to check both virtual call
      // and further call to base class member function
      ts.assertCondition(t2.sbumpc() == char_traits<char>::eof());
      ts.assertCondition(t.uflow_count == 1);
    }
}

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

// inspired from LLVM libcxx
// TestAssignOperator/input.output/stream.buffers/streambuf/streambuf.virtuals/streambuf.virt.get/underflow.pass.cpp

class TestUnderflowBase : public basic_streambuf<char>
{
public:
  TestUnderflowBase()
  {
  }
};

class TestUnderflowCustom : public basic_streambuf<char>
{
public:
  typedef basic_streambuf<char> base;

  TestUnderflowCustom()
  {
    underflow_count = 0;
  }

  virtual
  ~TestUnderflowCustom()
  {
  }

  int underflow_count;

  virtual int_type
  underflow()
  {
    ++underflow_count;
    return base::underflow();
  }
};

void
runTestUnderflow();

void
runTestUnderflow()
{
  ts.reportInfo("Test streambuf::underflow()");
    {
      ts.setFunctionNameOrPrefix("underflow()");

      TestUnderflowBase t;
      ts.assertCondition(t.sgetc() == char_traits<char>::eof());
    }

    {
      ts.setFunctionNameOrPrefix("underflow()");
      ts.setPreconditions("reference");

      TestUnderflowCustom t;
      basic_streambuf<char>& t2 = t;

      ts.assertCondition(t.underflow_count == 0);
      // Call it via reference to base class, to check both virtual call
      // and further call to base class member function
      ts.assertCondition(t2.sgetc() == char_traits<char>::eof());
      ts.assertCondition(t.underflow_count == 1);
    }
}

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

// inspired from LLVM libcxx
// TestAssignOperator/input.output/stream.buffers/streambuf/streambuf.virtuals/streambuf.virt.get/xsgetn.pass.cpp

class TestXsgetn : public basic_streambuf<char>
{
public:
  typedef basic_streambuf<char> base;

  TestXsgetn()
  {
  }

  void
  setg(char* gbeg, char* gnext, char* gend)
  {
    base::setg(gbeg, gnext, gend);
  }
};

void
runTestXsgetn(void);

void
runTestXsgetn(void)
{
  ts.reportInfo("Test streambuf::xsgetn()");
    {
      ts.setFunctionNameOrPrefix("xsgetn()");

      TestXsgetn t;
      char input[7] = "123456";
      t.setg(input, input, input + 7);
      char output[sizeof(input)] =
        { 0 };
      ts.assertCondition(t.sgetn(output, 10) == 7);
      ts.assertCondition(strcmp(input, output) == 0);
    }
}

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

// inspired from LLVM libcxx
// TestAssignOperator/input.output/stream.buffers/streambuf/streambuf.virtuals/streambuf.virt.pback/pbackfail.pass.cpp

class TestPbackfailBase : public basic_streambuf<char>
{
public:
  TestPbackfailBase()
  {
  }
};

class TestPbackfailCustom : public basic_streambuf<char>
{
public:
  typedef basic_streambuf<char> base;

  TestPbackfailCustom()
  {
    pbackfail_called = 0;
  }

  virtual
  ~TestPbackfailCustom()
  {
  }

  int pbackfail_called;

  virtual int_type
  pbackfail(int_type n)
  {
    ++pbackfail_called;

    return base::pbackfail(n);
  }
};

void
runTestPbackfail(void);

void
runTestPbackfail(void)
{
  ts.reportInfo("Test streambuf::pbackfail()");
    {
      ts.setFunctionNameOrPrefix("pbackfail()");

      TestPbackfailBase t;
      ts.assertCondition(t.sputbackc('A') == char_traits<char>::eof());
    }

    {
      ts.setFunctionNameOrPrefix("pbackfail()");
      ts.setPreconditions("reference");

      TestPbackfailCustom t;
      basic_streambuf<char>& t2 = t;
      ts.assertCondition(t.pbackfail_called == 0);
      // Call it via reference to base class, to check both virtual call
      // and further call to base class member function
      ts.assertCondition(t2.sputbackc('A') == char_traits<char>::eof());
      ts.assertCondition(t.pbackfail_called == 1);
    }
}

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

// inspired from LLVM libcxx
// TestAssignOperator/input.output/stream.buffers/streambuf/streambuf.virtuals/streambuf.virt.put/overflow.pass.cpp

class TestOverflowBase : public basic_streambuf<char>
{
public:
  TestOverflowBase()
  {
  }
};

class TestOverflowCustom : public basic_streambuf<char>
{
public:
  typedef basic_streambuf<char> base;

  TestOverflowCustom()
  {
    overflow_count = 0;
  }

  virtual
  ~TestOverflowCustom()
  {
  }

  int overflow_count;

  virtual int_type
  overflow(int_type n)
  {
    ++overflow_count;

    return base::overflow(n);
  }

};

void
runTestOverflow(void);

void
runTestOverflow(void)
{
  ts.reportInfo("Test streambuf::overflow()");
    {
      ts.setFunctionNameOrPrefix("overflow()");

      TestOverflowBase t;
      ts.assertCondition(t.sputc('A') == char_traits<char>::eof());
    }

    {
      ts.setFunctionNameOrPrefix("overflow()");
      ts.setPreconditions("reference");

      TestOverflowCustom t;
      basic_streambuf<char>& t2 = t;
      ts.assertCondition(t.overflow_count == 0);
      // Call it via reference to base class, to check both virtual call
      // and further call to base class member function
      ts.assertCondition(t2.sputc('A') == char_traits<char>::eof());
      ts.assertCondition(t.overflow_count == 1);
    }
}

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

// inspired from LLVM libcxx
// TestAssignOperator/input.output/stream.buffers/streambuf/streambuf.virtuals/streambuf.virt.put/xsputn.pass.cpp

class TestXsputn : public basic_streambuf<char>
{
public:
  typedef basic_streambuf<char> base;

  TestXsputn()
  {
  }

  void
  setp(char* pbeg, char* pend)
  {
    base::setp(pbeg, pend);
  }
};

void
runTestXsputn();

void
runTestXsputn()
{
  ts.reportInfo("Test streambuf::xsputn()");
    {
      ts.setFunctionNameOrPrefix("xsputn()");

      TestXsputn t;
      char in[] = "123456";
      ts.assertCondition(t.sputn(in, sizeof(in)) == 0);
      char out[sizeof(in)] =
        { 0 };
      t.setp(out, out + sizeof(out));
      ts.assertCondition(t.sputn(in, sizeof(in)) == sizeof(in));
      ts.assertCondition(strcmp(in, out) == 0);
    }
}

// ============================================================================

int
main(int argc, char* argv[])
{
  // instantiate the TestSuite, passing the process parameters
  ts.processMainParameters(argc, argv);

  // mark the start of the test suite
  ts.start("portable/language/cpp/tests/src/streambuf.cpp");

  // identify the class under tests
#ifdef OS_INCLUDE_STD_CALIBRATION
  ts.setClassName("std::streambuf");
  ts.reportInfo("calibration run");
#else
  ts.setClassName("os::std::streambuf");
#endif

  runTestTypes();

  runTestConstructor();

#if !defined(OS_INCLUDE_STD_CALIBRATION)
  runTestCopyConstructor();
#endif

  runTestPositioning();

  runTestInAvail();

  runTestSbumpc();

  runTestSgetc();

  runTestSgetn();

  runTestSnextc();

  runTestSputback();

  runTestSungetc();

  runTestSputc();

  runTestSputn();

  runTestAssignOperator();

  runTestSwap();

  runTestGbump();

  runTestSetg();

  runTestPbump();

  runTestSetp();

  runTestShowmanyc();

  runTestUflow();

  runTestUnderflow();

  runTestXsgetn();

  runTestPbackfail();

  runTestOverflow();

  runTestXsputn();

  // mark the stop of the test suite
  ts.stop();

  int retval;
  retval = ts.getExitValue();

#if defined(DEBUG)
  os::diag::trace << __PRETTY_FUNCTION__ << " returns " << os::std::dec
      << retval << os::std::endl;
#endif

  // return 0 if there are no failed test cases
  return retval;
}

// ============================================================================
