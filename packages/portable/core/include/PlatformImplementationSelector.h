//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Selector of one of the architecture classes.

#ifndef OS_PORTABLE_CORE_PLATFORMIMPLEMENTATIONSELECTOR_H_
#define OS_PORTABLE_CORE_PLATFORMIMPLEMENTATIONSELECTOR_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_PLATFORM_SYNTHETIC_OSX)

#include "hal/platform/synthetic/osx/include/PlatformImplementation.h"

#elif defined(OS_INCLUDE_HAL_PLATFORM_SYNTHETIC_LINUX)

#include "hal/platform/synthetic/linux/include/PlatformImplementation.h"

#elif defined(OS_INCLUDE_HAL_BOARD_OLIMEX_STM32H103)

#include "hal/platform/olimex/stm32h103/include/PlatformImplementation.h"

#else

#error "Missing PlatformImplementation.h"

#endif


#endif // OS_PORTABLE_CORE_PLATFORMIMPLEMENTATIONSELECTOR_H_
