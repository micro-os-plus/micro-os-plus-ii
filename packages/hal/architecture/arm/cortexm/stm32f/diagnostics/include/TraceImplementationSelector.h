//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F selector of the trace implementation class.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_DIAGNOSTICS_TRACEIMPLEMENTATIONSELECTOR_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_DIAGNOSTICS_TRACEIMPLEMENTATIONSELECTOR_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F) || defined(__DOXYGEN__)

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F1_DIAGNOSTICS_TRACEIMPLEMENTATION)

#include "hal/architecture/arm/cortexm/stm32f/stm32f1/diagnostics/include/TraceImplementation.h"

#elif defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_DIAGNOSTICS_TRACEIMPLEMENTATION)

#include "hal/architecture/arm/cortexm/stm32f/stm32f4/diagnostics/include/TraceImplementation.h"

#else

#error "missing STM32F TraceImplementation.h"

#endif

#endif // OS_INCLUDE_HAL_MCU_FAMILY_STM32F
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_DIAGNOSTICS_TRACEIMPLEMENTATIONSELECTOR_H_
