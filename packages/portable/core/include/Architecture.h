//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#ifndef OS_PORTABLE_CORE_ARCHITECTURE_H_
#define OS_PORTABLE_CORE_ARCHITECTURE_H_

#include "portable/core/include/ConfigDefines.h"

#include "portable/core/include/ArchitectureImplementationSelector.h"

namespace os
{
  extern hal::arch::ArchitectureImplementation_t architecture;
}

#endif // OS_PORTABLE_CORE_ARCHITECTURE_H_
