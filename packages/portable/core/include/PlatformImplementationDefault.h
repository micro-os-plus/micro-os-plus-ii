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

#if !defined(__DOXYGEN__)
namespace hal
{
  namespace platform
  {
    using PlatformImplementation = os::core::PlatformBase;
  } // namespace platform
} // namespace hal
#endif // !defined(__DOXYGEN__)
#endif // OS_PORTABLE_CORE_PLATFORMIMPLEMENTATION_H_
