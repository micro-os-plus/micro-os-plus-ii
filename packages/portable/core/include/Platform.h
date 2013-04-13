//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Portable platform (board/synthetic) definitions.
///
/// \details
/// Include this file to access the `os::platform` object.
/// Usually its member functions are static, but it is still recommended to
/// address them as object functions:
/// \code{.cpp}
/// os::platform.initialiseSystem();
/// \endcode

#ifndef OS_PORTABLE_CORE_PLATFORM_H_
#define OS_PORTABLE_CORE_PLATFORM_H_

#include "portable/core/include/ConfigDefines.h"

// Select one of the supported architectures, based on configuration
// variables.
#include "portable/core/include/PlatformImplementationSelector.h"

namespace os
{
  // The object instantiation is in EarlyInitialisations.cpp
  extern hal::platform::PlatformImplementation platform;
}

#endif // OS_PORTABLE_CORE_PLATFORM_H_
