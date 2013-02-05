//
//      Copyright (C) 2012-2013 Liviu Ionescu.
//
//      This file is part of the uOS++ distribution.
//

#include "portable/core/include/OS.h"

#include "portable/infra/include/TestSuite.h"


int
main(int argc, char* argv[])
{
  os::infra::TestSuite ts;

  ts.parseParameters(argc, argv);

  ts.setClassName("os::infra::TestSuite");

  ts.start(__FILE__);

  ts.checkAndReport(true, "check true constant");
  ts.checkAndReport(false, "check false constant");

  ts.reportPassed("a passed test");
  ts.reportFailed("a failed test");

  ts.reportInfo("there should be 2 failed cases and 2 passed cases");

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


