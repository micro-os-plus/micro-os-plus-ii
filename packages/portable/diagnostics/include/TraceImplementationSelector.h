//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Selector for the Trace class implementation.

#ifndef OS_PORTABLE_DIAGNOSTICS_TRACEIMPLEMENTATIONSELECTOR_H_
#define OS_PORTABLE_DIAGNOSTICS_TRACEIMPLEMENTATIONSELECTOR_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_DIAGNOSTICS_TRACE) || defined(__DOXYGEN__)

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX_DIAGNOSTICS_TRACEIMPLEMENTATION)

#include "hal/architecture/synthetic/posix/diagnostics/include/TraceImplementation.h"

#elif defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F10X_DIAGNOSTICS_TRACEIMPLEMENTATION)

#include "hal/architecture/arm/cortexm/stm32f/stm32f10x/diagnostics/include/TraceImplementation.h"

#elif defined(OS_INCLUDE_HAL_BOARD_OLIMEX_STM32H103)

#include "hal/platform/olimex/stm32h103/diagnostics/include/TraceImplementation.h"

#else

#error "Missing TraceImplementation.h"

#endif // architecture selection

#endif // defined(OS_INCLUDE_PORTABLE_DIAGNOSTICS_TRACE)
#endif // OS_PORTABLE_DIAGNOSTICS_TRACEIMPLEMENTATIONSELECTOR_H_
