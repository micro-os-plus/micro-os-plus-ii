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
  os::infra::TestSuite t;

  t.parseParameters(argc, argv);

  t.setClassName("os::infra::TestSuite");

  t.start(__FILE__);

  t.checkAndReport(true, "check true constant");
  t.checkAndReport(false, "check false constant");

  t.reportPassed("a passed test");
  t.reportFailed("a failed test");

  t.reportInfo("there should be 2 failed cases and 2 passed cases");

  t.stop(__FILE__);

  int retval;
  retval = t.getExitValue();

  debug.putString(__PRETTY_FUNCTION__);
  debug.putString(" returns ");
  debug.putDec(retval);
  debug.putNewLine();

  // return 0 if there are no failed test cases
  return retval;
}


