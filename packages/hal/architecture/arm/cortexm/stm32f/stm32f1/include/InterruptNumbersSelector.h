//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F10X Selector of sub-family interrupt numbers.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F1_INTERRUPTNUMBERSSELECTOR_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F1_INTERRUPTNUMBERSSELECTOR_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F1) || defined(__DOXYGEN__)

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X_LD)

#include "InterruptNumbersLD.h"

#elif defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X_LD_VL)

#include "InterruptNumbersLDVL.h"

#elif defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X_MD)

#include "InterruptNumbersMD.h"

#elif defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X_MD_VL)

#include "InterruptNumbersMDVL.h"

#elif defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X_HD)

#include "InterruptNumbersHD.h"

#elif defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X_HD_VL)

#include "InterruptNumbersHDVL.h"

#elif defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X_XL)

#include "InterruptNumbersXL.h"

#elif defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X_CL)

#include "InterruptNumbersCL.h"

#else

#error "No specific STM32F device"

#endif

#endif // OS_INCLUDE_HAL_MCU_FAMILY_STM32F1
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F1_INTERRUPTNUMBERSSELECTOR_H_
