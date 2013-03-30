//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#ifndef OS_PORTABLE_CORE_PLATFORM_H_
#define OS_PORTABLE_CORE_PLATFORM_H_

#include "portable/core/include/ConfigDefines.h"

#include "portable/core/include/PlatformImplementationSelector.h"

namespace os
{
  extern hal::platform::PlatformImplementation_t platform;
}

#endif // OS_PORTABLE_CORE_PLATFORM_H_
