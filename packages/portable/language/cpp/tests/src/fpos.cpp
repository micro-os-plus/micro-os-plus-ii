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

// This test exercises the os::std::fpos class.

// It is based on LLVM libcxx/test/input.output/iostream.base/fpos/*

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
using namespace os::std;

#endif

typedef fpos<mbstate_t> P;

// ----------------------------------------------------------------------------

//#include "portable/language/cpp/include/type_traits.h"

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

os::infra::TestSuite_t ts;

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.base/fpos/fpos.members/state.pass.cpp

void
runTestState();

void
runTestState()
{
  ts.reportInfo("Test fpos::state()");
    {
      ts.setFunctionNameOrPrefix("state()");

      fpos<int> f;
      f.state(3);
      ts.assertCondition(f.state() == 3);
    }
}

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.base/fpos/fpos.operations/ctor_init.pass.cpp

void
runTestCtor();

void
runTestCtor()
{
  ts.reportInfo("Test fpos::fpos()");
    {
      ts.setFunctionNameOrPrefix("fpos(streamoff)");

      P p(5);
      ts.assertCondition(p == P(5));
    }
}

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.base/fpos/fpos.operations/addition.pass.cpp

void
runTestAddition();

void
runTestAddition()
{
  ts.reportInfo("Test fpos::operator+=()");
    {
      P p(5);
      streamoff o(6);

      ts.setFunctionNameOrPrefix("operator+()");
      P q = p + o;
      ts.assertCondition(q == P(11));

      ts.setFunctionNameOrPrefix("operator+=()");
      p += o;
      ts.assertCondition(p == q);
    }
}

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.base/fpos/fpos.operations/subtraction.pass.cpp

void
runTestSubtraction();

void
runTestSubtraction()
{
  ts.reportInfo("Test fpos::operator -=()");
    {
      P p(11);
      streamoff o(6);

      ts.setFunctionNameOrPrefix("operator-()");
      P q = p - o;
      ts.assertCondition(q == P(5));

      ts.setFunctionNameOrPrefix("operator-=()");
      p -= o;
      ts.assertCondition(p == q);
    }
}

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.base/fpos/fpos.operations/difference.pass.cpp

void
runTestDifference();

void
runTestDifference()
{
  ts.reportInfo("Test fpos::operator-()");
    {
      P p(11);
      P q(6);

      ts.setFunctionNameOrPrefix("operator-()");
      streamoff o = p - q;
      ts.assertCondition(o == 5);
    }
}

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.base/fpos/fpos.operations/eq_int.pass.cpp

void
runTestEqual();

void
runTestEqual()
{
  ts.reportInfo("Test fpos::operator==()");
    {
      P p(5);
      P q(6);

      ts.setFunctionNameOrPrefix("operator==()");
      ts.assertCondition(p == p);

      ts.setFunctionNameOrPrefix("operator!=()");
      ts.assertCondition(p != q);
    }
}

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.base/fpos/fpos.operations/offset.pass.cpp

void
runTestOffset();

void
runTestOffset()
{
  ts.reportInfo("Test fpos::operator streamoff()");
    {
      P p(streamoff(7));
      streamoff offset(p);

      ts.setFunctionNameOrPrefix("offset()");
      ts.assertCondition(offset == 7);
    }
}

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.base/fpos/fpos.operations/offset.pass.cpp

void
runTestStreamsize();

void
runTestStreamsize()
{
  ts.reportInfo("Test streamsize()");
    {
      streamoff o(5);
#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#endif
      streamsize sz(o);
#pragma GCC diagnostic pop

      ts.setFunctionNameOrPrefix("streamsize()");
      ts.assertCondition(sz == 5);
      streamoff o2(sz);
      ts.assertCondition(o == o2);
    }
}

// ============================================================================

int
main(int argc, char* argv[])
{
  // instantiate the TestSuite, passing the process parameters
  ts.processMainParameters(argc, argv);

  // mark the start of the test suite
  ts.start("portable/language/cpp/tests/src/fpos.cpp");

  // identify the class under tests
#ifdef OS_INCLUDE_STD_CALIBRATION
  ts.setClassName("std::fpos");
  ts.reportInfo("calibration run");
#else
  ts.setClassName("os::std::fpos");
#endif

  runTestState();

  runTestCtor();

  runTestAddition();

  runTestSubtraction();

  runTestDifference();

  runTestEqual();

  runTestStreamsize();

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
