//
//      Copyright (C) 2012-2013 Liviu Ionescu.
//
//      This file is part of the uOS++ distribution.
//

#include "portable/core/include/OS.h"

#include "portable/infra/include/TestSuite.h"

// This test exercises the TestSuite methods.

int
main(int argc, char* argv[])
{
  // instantiate the TestSuite, passing the process parameters
  os::infra::TestSuite_t ts(argc, argv);

  // identify the class unter tests
  ts.setClassName("os::infra::TestSuite");

  // mark the start of the test suite
  ts.start(__FILE__);

  // exercise the method that check a boolean expression
  ts.checkAndReport(true, "check true constant");
  ts.checkAndReport(false, "check false constant");

  // exercise the methods that directly report
  ts.reportPassed("a passed test");
  ts.reportFailed("a failed test");

  // exercise the informative method
  ts.reportInfo("there should be 2 failed cases and 2 passed cases");

  // mark the stop of the test suite
  ts.stop(__FILE__);

  int retval;
  retval = ts.getExitValue();

  debug.putString(__PRETTY_FUNCTION__);
  debug.putString(" returns ");
  debug.putDec(retval);
  debug.putNewLine();

  // return 0 if there are no failed test cases
  return retval;
}

