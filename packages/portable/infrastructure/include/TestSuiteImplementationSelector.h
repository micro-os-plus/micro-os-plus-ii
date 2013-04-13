//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Selector of one TestSuite implementation.

#ifndef OS_PORTABLE_INFRASTRUCTURE_TESTSUITEIMPLEMENTATION_H_
#define OS_PORTABLE_INFRASTRUCTURE_TESTSUITEIMPLEMENTATION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_INFRASTRUCTURE_TESTSUITE)

// This is the place where the actual TestSuiteImplementation is
// selected, based on various preprocessor definitions.

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX_INFRASTRUCTURE_TESTSUITEIMPLEMENTATION)

#include "hal/architecture/synthetic/posix/infrastructure/include/TestSuiteImplementation.h"

#else

#error "Missing TestSuiteImplementation.h"

#endif // architecture selection

#endif // defined(OS_INCLUDE_PORTABLE_INFRASTRUCTURE_TESTSUITE)

#endif // OS_PORTABLE_INFRASTRUCTURE_TESTSUITEIMPLEMENTATION_H_
