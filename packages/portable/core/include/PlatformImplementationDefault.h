//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Default platform implementation class.

// WARNING: This file is copied to the build folder, be sure you
// edit the original and not the copy!

#ifndef OS_PORTABLE_CORE_PLATFORMIMPLEMENTATION_H_
#define OS_PORTABLE_CORE_PLATFORMIMPLEMENTATION_H_

#include "portable/core/include/ConfigDefines.h"

#include "portable/core/include/PlatformBase.h"

// ----------------------------------------------------------------------------

// As default, the base definitions are enough, if you need more
// just derive your own class from PlatformBase and add the
// specifics (see PlatformImplementationSample.h).

// ----------------------------------------------------------------------------

namespace hal
{
  namespace platform
  {
    // ------------------------------------------------------------------------

#if !defined(__DOXYGEN__)

    using PlatformImplementation = os::core::PlatformBase;

#endif // !defined(__DOXYGEN__)
  // --------------------------------------------------------------------------
  }// namespace platform
} // namespace hal

#endif // OS_PORTABLE_CORE_PLATFORMIMPLEMENTATION_H_
