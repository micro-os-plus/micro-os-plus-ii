//
//      Copyright (C) 2012-2013 Liviu Ionescu.
//
//      This file is part of the uOS++ distribution.
//

#include "portable/core/include/OS_Defines.h"

#if defined(OS_INCLUDE_PORTABLE_INFRASTRUCTURE_TESTSUITE) || defined(__DOXYGEN__)

#include "portable/core/include/OS.h"

#include "../include/TestSuite.h"
#include "../include/TestSuiteImplementation.h"

#include <string.h>

// We have a single instantiation of this template, so a separate
// header with the template implementation definitions is not needed,
// these definitions can be written directly in the .cpp file.

// However please remember that these are only template definitions,
// to become actual method definitions, the template needs to be
// instantiated (see at the end)

namespace os
{
  namespace infra
  {

    TestSuiteImplementation::TestSuiteImplementation()
    {
      debug.putMethodNameWithAddress(__PRETTY_FUNCTION__, this);
    }

    TestSuiteImplementation::TestSuiteImplementation(
        int argc __attribute__((unused)), char* argv[] __attribute__((unused)))
    {
      debug.putMethodNameWithAddress(__PRETTY_FUNCTION__, this);
    }

    TestSuiteImplementation::~TestSuiteImplementation()
    {
      debug.putMethodNameWithAddress(__PRETTY_FUNCTION__, this);
    }

  } /* namespace infra */
} /* namespace os */

#endif /* defined(OS_INCLUDE_PORTABLE_INFRASTRUCTURE_TESTSUITE) */
