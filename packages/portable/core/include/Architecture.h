//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Portable declarations related to the architecture.

#ifndef OS_PORTABLE_CORE_ARCHITECTURE_H_
#define OS_PORTABLE_CORE_ARCHITECTURE_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(___)

// Include one of the supported architectures,
// copied to the build folder by the XCDL procedure.
#include "hal/architecture/include/ArchitectureImplementation.h"

#elif defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX)

#include "hal/architecture/synthetic/posix/include/ArchitectureImplementation.h"

#endif

namespace os
{
  // Declaration of the external instantiation of `architecture`.
  // The object instantiation is in `EarlyInitialisations.cpp`.
  extern hal::arch::ArchitectureImplementation architecture;
}

#endif // OS_PORTABLE_CORE_ARCHITECTURE_H_
