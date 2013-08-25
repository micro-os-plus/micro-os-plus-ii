//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Portable platform (board/synthetic) definitions.
///
/// \details
/// Include this file to access the `os::platform` object.
/// Usually its member functions are static, but this is not
/// mandatory, so it is highly recommended to
/// address them as object functions:
/// \code{.cpp}
/// os::platform.initialiseSystem();
/// \endcode

#ifndef OS_PORTABLE_CORE_PLATFORM_H_
#define OS_PORTABLE_CORE_PLATFORM_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_CORE_PLATFORMIMPLEMENTATIONDEFAULT)

#include "portable/core/include/PlatformImplementationDefault.h"

#elif defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_PLATFORMIMPLEMENTATIONDEFAULT)

#include "hal/architecture/arm/cortexm/include/PlatformImplementationDefault.h"

#elif defined(OS_PATH_HAL_PLATFORM_PLATFORMIMPLEMENTATION)

// Not very usual, but less problematic then all other solutions tested
// (countless #ifs, xcdl copyFiles)
#include OS_PATH_HAL_PLATFORM_PLATFORMIMPLEMENTATION

#else

#error "Missing PlatformImplementation.h"

#endif

namespace os
{
  // The object instantiation is in EarlyInitialisations.cpp
  extern hal::platform::PlatformImplementation platform;
}

#endif // OS_PORTABLE_CORE_PLATFORM_H_
