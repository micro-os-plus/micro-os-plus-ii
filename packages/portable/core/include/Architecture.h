//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Portable declarations related to the architecture.

#ifndef OS_PORTABLE_CORE_ARCHITECTURE_H_
#define OS_PORTABLE_CORE_ARCHITECTURE_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)

#include "hal/architecture/arm/cortexm/include/ArchitectureImplementation.h"

#elif defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX)

#include "hal/architecture/synthetic/posix/include/ArchitectureImplementation.h"

#elif defined(OS_INCLUDE_HAL_ARCHITECTURE_CUSTOM)

// Include one of the supported architectures,
// copied to the build folder by the XCDL procedure.

#include "hal/architecture/include/ArchitectureImplementation.h"

// In order for this to happen, you should enable
//
//      'enable("component.os.hal.architecture.custom")',
//
// and you should have an XCDL file to do the following:
//
// copyFiles=[
//      ('../include/ArchitectureImplementation.h','include/hal/architecture/include/ArchitectureImplementation.h'),
// ],
//
// implements=[
//      # mark this is an architecture
//      'interface.os.architecture',
// ],
//

#else

#error "undefined ArchitectureImplementation.h"

#endif

namespace os
{
  // Declaration of the external instantiation of `architecture`.
  // The object instantiation is in `EarlyInitialisations.cpp`.
  extern hal::arch::ArchitectureImplementation architecture;
}

#endif // OS_PORTABLE_CORE_ARCHITECTURE_H_
