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

// This test exercises the os::std::basic_ios class.

// It is based on LLVM libcxx/test/input.output/iostream.base/ios/*

// ----------------------------------------------------------------------------

// To calibrate this test, first define this macro, to use the system std
// library versions.

// Note: Not all test branches are available when running in the
// host environment.

//#define OS_INCLUDE_STD_CALIBRATION

#ifdef OS_INCLUDE_STD_CALIBRATION

#include <ios>
using namespace std;

#else

#include "portable/language/cpp/include/ios.h"
#include "portable/language/cpp/include/streambuf.h"
using namespace os::std;

#endif

// ----------------------------------------------------------------------------

//#include "portable/language/cpp/include/type_traits.h"

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

os::infra::TestSuite ts;

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.base/ios/types.pass.cpp

void
runTestTypes();

void
runTestTypes()
{
  ts.reportInfo("Test basic_ios types definitions");

  ts.setFunctionNameOrPrefix("types");

  ts.assertCondition((os::std::is_base_of<ios_base, basic_ios<char> >::value));
  ts.assertCondition((os::std::is_same<basic_ios<char>::char_type, char>::value));
  ts.assertCondition((os::std::is_same<basic_ios<char>::traits_type, char_traits<char> >::value));
  ts.assertCondition((os::std::is_same<basic_ios<char>::int_type, char_traits<char>::int_type>::value));
  ts.assertCondition((os::std::is_same<basic_ios<char>::pos_type, char_traits<char>::pos_type>::value));
  ts.assertCondition((os::std::is_same<basic_ios<char>::off_type, char_traits<char>::off_type>::value));
}

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.base/ios/basic.ios.cons/ctor_streambuf.pass.cpp

void
runTestConstructors();

void
runTestConstructors()
{
  ts.reportInfo("Test basic_ios initialisations");

    {
      ts.setFunctionNameOrPrefix("basic_ios()");
      ts.setInputValues("0");

      streambuf* sb = 0;
      basic_ios<char> ios(sb);
      ts.assertCondition(ios.rdbuf() == sb);
      ts.assertCondition(ios.tie() == 0);
      ts.assertCondition(ios.rdstate() == ios::badbit);
      ts.assertCondition(ios.exceptions() == ios::goodbit);
      ts.assertCondition(ios.flags() == (ios::skipws | ios::dec));
      ts.assertCondition(ios.width() == 0);
      ts.assertCondition(ios.precision() == 6);
      ts.assertCondition(ios.fill() == ' ');
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      assert(ios.getloc() == locale());
#endif
    }
    {
      ts.setFunctionNameOrPrefix("basic_ios()");
      ts.setInputValues("1");

      streambuf* sb = (streambuf*) 1;
      basic_ios<char> ios(sb);
      ts.assertCondition(ios.rdbuf() == sb);
      ts.assertCondition(ios.tie() == 0);
      ts.assertCondition(ios.rdstate() == ios::goodbit);
      ts.assertCondition(ios.exceptions() == ios::goodbit);
      ts.assertCondition(ios.flags() == (ios::skipws | ios::dec));
      ts.assertCondition(ios.width() == 0);
      ts.assertCondition(ios.precision() == 6);
      ts.assertCondition(ios.fill() == ' ');
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      assert(ios.getloc() == locale());
#endif
    }
}

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.base/ios/iostate.flags/bad.pass.cpp
// test/input.output/iostream.base/ios/iostate.flags/bool.pass.cpp
// test/input.output/iostream.base/ios/iostate.flags/clear.pass.cpp
// test/input.output/iostream.base/ios/iostate.flags/eof.pass.cpp
// test/input.output/iostream.base/ios/iostate.flags/exceptions_iostate.pass.cpp
// test/input.output/iostream.base/ios/iostate.flags/exceptions.pass.cpp
// test/input.output/iostream.base/ios/iostate.flags/fail.pass.cpp
// test/input.output/iostream.base/ios/iostate.flags/good.pass.cpp
// test/input.output/iostream.base/ios/iostate.flags/not.pass.cpp
// test/input.output/iostream.base/ios/iostate.flags/rdstate.pass.cpp
// test/input.output/iostream.base/ios/iostate.flags/setstate.pass.cpp

void
runTestIostateFlags();

void
runTestIostateFlags()
{
  ts.reportInfo("Test basic_ios iostate flags");

  class testbuf : public streambuf
  {
  };

    {
      ts.setFunctionNameOrPrefix("bad()");
      ts.setPreconditions("ios(0)");

      ios ios(0);
      ts.assertConditionWithDetails(ios.bad(), "constructor");
      ios.setstate(ios::eofbit);
      ts.assertConditionWithDetails(ios.bad(), "setstate(ios::eofbit)");
    }
    {
      ts.setFunctionNameOrPrefix("bad()");
      ts.setPreconditions("ios(&)");

      testbuf sb;
      ios ios(&sb);
      ts.assertConditionWithDetails(!ios.bad(), "constructor");
      ios.setstate(ios::eofbit);
      ts.assertConditionWithDetails(!ios.bad(), "setstate(ios::eofbit)");
      ios.setstate(ios::failbit);
      ts.assertConditionWithDetails(!ios.bad(), "setstate(ios::failbit)");
      ios.setstate(ios::badbit);
      ts.assertConditionWithDetails(ios.bad(), "setstate(ios::badbit)");
    }
    {
      ts.setFunctionNameOrPrefix("bool()");

      ios ios(0);
      ts.assertConditionWithDetails(static_cast<bool>(ios) == !ios.fail(), "constructor");
      ios.setstate(ios::failbit);
      ts.assertConditionWithDetails(static_cast<bool>(ios) == !ios.fail(), "setstate(ios::failbit)");
    }
  // TODO: add exception case
    {
      ts.setFunctionNameOrPrefix("clear()");
      ts.setPreconditions("ios(&)");

      testbuf sb;
      ios ios(&sb);
      ios.clear();
      ts.assertCondition(ios.rdstate() == ios::goodbit);
      ios.exceptions(ios::badbit);
      ios.clear();
      ts.assertConditionWithDetails(ios.rdstate() == ios::goodbit, "exceptions(ios::badbit)");
      ios.clear(ios::eofbit);
      ts.assertCondition(ios.rdstate() == ios::eofbit);
    }
    {
      ts.setFunctionNameOrPrefix("eof()");
      ts.setPreconditions("ios(0)");

      ios ios(0);
      ts.assertCondition(!ios.eof());
      ios.setstate(ios::eofbit);
      ts.assertConditionWithDetails(ios.eof(), "setstate(ios::eofbit)");
    }
    {
      ts.setFunctionNameOrPrefix("eof()");
      ts.setPreconditions("ios(&)");

      testbuf sb;
      ios ios(&sb);
      ts.assertCondition(!ios.eof());
      ios.setstate(ios::eofbit);
      ts.assertConditionWithDetails(ios.eof(), "setstate(ios::eofbit)");
    }
  // TODO: add exception case
    {
      ts.setFunctionNameOrPrefix("exceptions()");
      ts.setPreconditions("ios(&)");

      testbuf sb;
      ios ios(&sb);
      ts.assertCondition(ios.exceptions() == ios::goodbit);
      ios.exceptions(ios::eofbit);
      ts.assertCondition(ios.exceptions() == ios::eofbit);
      ios.exceptions(ios::badbit);
      ts.assertCondition(ios.exceptions() == ios::badbit);
    }
    {
      ts.setFunctionNameOrPrefix("fail()");
      ts.setPreconditions("ios(0)");

      ios ios(0);
      ts.assertConditionWithDetails(ios.fail(), "constructor");
      ios.setstate(ios::eofbit);
      ts.assertConditionWithDetails(ios.fail(), "setstate(ios::eofbit)");
    }
    {
      ts.setFunctionNameOrPrefix("fail()");
      ts.setPreconditions("ios(&)");

      testbuf sb;
      ios ios(&sb);
      ts.assertConditionWithDetails(!ios.fail(), "constructor");
      ios.setstate(ios::eofbit);
      ts.assertConditionWithDetails(!ios.fail(), "setstate(ios::eofbit)");
      ios.setstate(ios::badbit);
      ts.assertConditionWithDetails(ios.fail(), "setstate(ios::badbit)");
      ios.setstate(ios::failbit);
      ts.assertConditionWithDetails(ios.fail(), "setstate(ios::failbit)");
    }
    {
      ts.setFunctionNameOrPrefix("good()");
      ts.setPreconditions("ios(0)");

      ios ios(0);
      ts.assertCondition(!ios.good());
    }
    {
      ts.setFunctionNameOrPrefix("good()");
      ts.setPreconditions("ios(&)");

      testbuf sb;
      ios ios(&sb);
      ts.assertCondition(ios.good());
      ios.setstate(ios::eofbit);
      ts.assertCondition(!ios.good());
    }
    {
      ts.setFunctionNameOrPrefix("not()");
      ts.setPreconditions("ios(0)");

      ios ios(0);
      ts.assertConditionWithDetails(!ios == ios.fail(), "constructor");
      ios.setstate(ios::failbit);
      ts.assertConditionWithDetails(!ios == ios.fail(), "setstate(ios::failbit)");
    }
    {
      ts.setFunctionNameOrPrefix("rdstate()");
      ts.setPreconditions("ios(0)");

      ios ios(0);
      ts.assertConditionWithDetails(ios.rdstate() == ios::badbit, "constructor");
      ios.setstate(ios::failbit);
      ts.assertConditionWithDetails(ios.rdstate() == (ios::failbit | ios::badbit), "setstate(ios::failbit)");
    }
  // TODO: add exceptions case
    {
      ts.setFunctionNameOrPrefix("setstate()");
      ts.setPreconditions("ios(&)");

      testbuf sb;
      ios ios(&sb);
      ios.setstate(ios::goodbit);
      ts.assertCondition(ios.rdstate() == ios::goodbit);
      ios.setstate(ios::eofbit);
      ts.assertCondition(ios.rdstate() == ios::eofbit);
      ios.setstate(ios::failbit);
      ts.assertCondition(ios.rdstate() == (ios::eofbit | ios::failbit));
    }

}

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.base/ios/basic.ios.members/fill_char_type.pass.cpp
// test/input.output/iostream.base/ios/basic.ios.members/fill.pass.cpp
// test/input.output/iostream.base/ios/basic.ios.members/narrow.pass.cpp
// test/input.output/iostream.base/ios/basic.ios.members/tie.pass.cpp

void
runTestMembers();

void
runTestMembers()
{
  ts.reportInfo("Test basic_ios members");

    {
      ts.setFunctionNameOrPrefix("fill()");
      ts.setPreconditions("ios(0)");

      const ios ios(0);
      ts.assertCondition(ios.fill() == ' ');
    }
    {
      ts.setFunctionNameOrPrefix("fill('*')");
      ts.setPreconditions("ios(0)");

      ios ios(0);
      ts.assertCondition(ios.fill() == ' ');
      char c = ios.fill('*');
      ts.assertCondition(c == ' ');
      ts.assertCondition(ios.fill() == '*');
    }
    {
      ts.setFunctionNameOrPrefix("narrow()");
      ts.setPreconditions("ios(0)");

      const ios ios(0);
      ts.assertCondition(ios.narrow('c', '*') == 'c');
      ts.assertCondition(ios.narrow('\xFE', '*') == '*');
    }
    {
      ts.setFunctionNameOrPrefix("rdbuf()");
      ts.setPreconditions("ios(0)");

      const ios ios(0);
      ts.assertCondition(ios.rdbuf() == 0);
    }
    {
      ts.setFunctionNameOrPrefix("rdbuf()");
      ts.setPreconditions("ios(&)");

      streambuf* sb = (streambuf*) 1;
      const ios ios(sb);
      ts.assertCondition(ios.rdbuf() == sb);
    }
    {
      ts.setFunctionNameOrPrefix("rdbuf(&)");
      ts.setPreconditions("streambuf_ios(0)");

      ios ios(0);
      ts.assertCondition(ios.rdbuf() == 0);
      ts.assertCondition(!ios.good());
      streambuf* sb = (streambuf*) 1;
      streambuf* sb2 = ios.rdbuf(sb);
      ts.assertCondition(sb2 == 0);
      ts.assertCondition(ios.rdbuf() == sb);
      ts.assertCondition(ios.good());

      ts.setFunctionNameOrPrefix("rdbuf(&)");
      ts.setInputValues("0");
      ts.setPreconditions("streambuf_ios(0)");

      sb2 = ios.rdbuf(0);
      ts.assertCondition(sb2 == (streambuf*)1);
      ts.assertCondition(ios.rdbuf() == 0);
      ts.assertCondition(ios.bad());
    }
    {
      ts.setFunctionNameOrPrefix("tie()");
      ts.setPreconditions("ios(0)");

      const basic_ios<char> ios(0);
      ts.assertCondition(ios.tie() == 0);
    }
    {
      ts.setFunctionNameOrPrefix("widen(ch)");
      ts.setPreconditions("ios(0)");

      const ios ios(0);
      ts.assertCondition(ios.widen('c') == 'c');
    }
}

// ============================================================================

int
main(int argc, char* argv[])
{
  // instantiate the TestSuite, passing the process parameters
  ts.processMainParameters(argc, argv);

  // mark the start of the test suite
  ts.start("portable/language/cpp/tests/src/basic_ios.cpp");

  // identify the class under tests
#ifdef OS_INCLUDE_STD_CALIBRATION
  ts.setClassName("std::basic_ios");
  ts.reportInfo("calibration run");
#else
  ts.setClassName("os::std::basic_ios");
#endif

  runTestTypes();

  runTestConstructors();

  runTestIostateFlags();

  runTestMembers();

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
