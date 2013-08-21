//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F declarations of family base class.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_FAMILYIMPLEMENTATIONSELECTOR_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_FAMILYIMPLEMENTATIONSELECTOR_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F) || defined(__DOXYGEN__)

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F1)

#include "hal/architecture/arm/cortexm/stm32f/stm32f1/include/FamilyImplementation.h"

#elif defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4)

#include "hal/architecture/arm/cortexm/stm32f/stm32f4/include/FamilyImplementation.h"

#else

#error "missing FamilyImplementation.h"

#endif

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_FAMILYIMPLEMENTATIONSELECTOR_H_
