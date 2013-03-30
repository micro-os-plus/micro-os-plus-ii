//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#ifndef OS_PORTABLE_CORE_ARCHITECTUREIMPLEMENTATIONSELECTOR_H_
#define OS_PORTABLE_CORE_ARCHITECTUREIMPLEMENTATIONSELECTOR_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX)

#include "hal/architecture/synthetic/posix/include/ArchitectureImplementation.h"

#else

#error "Missing ArchitectureImplementation.h"

#endif


#endif // OS_PORTABLE_CORE_ARCHITECTUREIMPLEMENTATIONSELECTOR_H_
