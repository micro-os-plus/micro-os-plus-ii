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

// This test exercises the exception classes.

// It is based on LLVM libcxx/test/language.support/support.exception/*

// ----------------------------------------------------------------------------

#include "portable/language/cpp/include/exception.h"
#include "portable/language/cpp/include/type_traits.h"

using namespace os::std;

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

static os::infra::TestSuite ts;

#pragma GCC diagnostic pop

// ============================================================================

void
runTestExceptionClasses();

void
runTestExceptionClasses()
{

  ts.reportInfo("Test exception classes");

    {
      ts.setClassName("os::std::exception");

      ts.assertCondition(is_polymorphic<exception>::value);

      ts.setFunctionNameOrPrefix("exception()");
      exception b;
      ts.assertCondition(strcmp(b.what(), "os::std::exception") == 0);

      ts.setFunctionNameOrPrefix("exception(exception&)");
      exception b2 = b;
      ts.assertCondition(strcmp(b2.what(), b.what()) == 0);

      ts.setFunctionNameOrPrefix("operator=(exception&)");
      b2 = b;
      ts.assertCondition(strcmp(b2.what(), b.what()) == 0);
    }

    {
      ts.setClassName("os::std::bad_exception");

      ts.assertCondition((is_base_of<exception, bad_exception>::value));
      ts.assertCondition(is_polymorphic<bad_exception>::value);

      ts.setFunctionNameOrPrefix("bad_exception()");
      bad_exception b;
      ts.assertCondition(strcmp(b.what(), "os::std::bad_exception") == 0);

      ts.setFunctionNameOrPrefix("bad_exception(bad_exception&)");
      bad_exception b2 = b;
      ts.assertCondition(strcmp(b2.what(), "os::std::bad_exception") == 0);

      ts.setFunctionNameOrPrefix("operator=(bad_exception&)");
      b2 = b;
      ts.assertCondition(strcmp(b2.what(), b.what()) == 0);
    }
}

// ============================================================================

int
main(int argc, char* argv[])
{
  // instantiate the TestSuite, passing the process parameters
  ts.processMainParameters(argc, argv);

  // mark the start of the test suite
  ts.start("portable/language/cpp/tests/src/exception.cpp");

  // identify the class under tests
  ts.setClassName("os::std::exception");

  runTestExceptionClasses();

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
