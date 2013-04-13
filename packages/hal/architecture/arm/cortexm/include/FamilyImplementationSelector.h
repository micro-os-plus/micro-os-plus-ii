//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief ARM Cortex-M family implementation selector.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_FAMILYIMPLEMENTATIONSELECTOR_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_FAMILYIMPLEMENTATIONSELECTOR_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F)

#include "hal/architecture/arm/cortexm/stm32f/include/FamilyImplementation.h"

#else

#error "Missing ARM Cortex-M FamilyImplementation.h"

#endif

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_ARCHITECTUREIMPLEMENTATION_H_
