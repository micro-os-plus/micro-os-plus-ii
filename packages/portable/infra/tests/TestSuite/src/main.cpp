/*
 *      Copyright (C) 2012-2013 Liviu Ionescu.
 *
 *      This file is part of the uOS++ distribution.
 */

#include "portable/core/include/OS.h"

#include "portable/infra/include/TestSuite.h"

namespace os
{
  namespace infra
  {

    void
    TestSuite::run(void)
    {
      setClassName("os::infra::TestSuite");

      start(__FILE__);

      checkAndReport(true, "check true constant");
      checkAndReport(false, "check false constant");

      reportPassed("a passed test");
      reportFailed("a failed test");

      reportInfo("there should be 2 failed cases and 2 passed cases");

      stop(__FILE__);
    }

  } /* namespace infra */
} /* namespace os */
