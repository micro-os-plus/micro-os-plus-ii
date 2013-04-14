//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Portable declarations related to the architecture.

#ifndef OS_PORTABLE_CORE_ARCHITECTURE_H_
#define OS_PORTABLE_CORE_ARCHITECTURE_H_

#include "portable/core/include/ConfigDefines.h"

// Select one of the supported architectures, based on configuration
// variables.
#include "portable/core/include/ArchitectureImplementationSelector.h"

namespace os
{
  /// \brief Declaration of the external instantiation of `architecture`.
  /// The object instantiation is in `EarlyInitialisations.cpp`.
  extern hal::arch::ArchitectureImplementation architecture;
}

#endif // OS_PORTABLE_CORE_ARCHITECTURE_H_
