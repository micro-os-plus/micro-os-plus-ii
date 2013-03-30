//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#ifndef OS_PORTABLE_DIAGNOSTICS_TRACEIMPLEMENTATION_H_
#define OS_PORTABLE_DIAGNOSTICS_TRACEIMPLEMENTATION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_DIAGNOSTICS_TRACE) || defined(__DOXYGEN__)

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX_DIAGNOSTICS_TRACEIMPLEMENTATION)

#include "hal/architecture/synthetic/posix/diagnostics/include/TraceImplementation.h"

#else

#error "Missing TraceImplementation.h"

#endif /* architecture selection */

#endif // defined(OS_INCLUDE_PORTABLE_DIAGNOSTICS_TRACE)
#endif // OS_PORTABLE_DIAGNOSTICS_TRACEIMPLEMENTATION_H_
