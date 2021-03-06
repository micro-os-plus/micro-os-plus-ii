//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/OS.h"

#include "portable/infrastructure/include/TestSuite.h"

// This test exercises the TestSuite member functions.

int
main(int argc, char* argv[])
{
  // instantiate the TestSuite, passing the process parameters
  os::infra::TestSuite ts(argc, argv);

  // identify the class unter tests
  ts.setClassName("os::infra::TestSuite");

  // mark the start of the test suite
  ts.start(__FILE__);

  // exercise the member function that check a boolean expression
  ts.checkAndReport(true, "check true constant");
  ts.checkAndReport(false, "check false constant");

  // exercise the member functions that directly report
  ts.reportPassed("a passed test");
  ts.reportFailed("a failed test");

  // exercise the informative member function
  ts.reportInfo("there should be 2 failed cases and 2 passed cases");

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

