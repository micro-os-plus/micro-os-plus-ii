//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#ifndef HAL_ARCHITECTURE_SYNTHETIC_POSIX_ARCHITECTUREIMPLEMENTATION_H_
#define HAL_ARCHITECTURE_SYNTHETIC_POSIX_ARCHITECTUREIMPLEMENTATION_H_

#include "portable/core/include/OS_Defines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX) || defined(__DOXYGEN__)

#include "portable/core/include/OS.h"

namespace hal
{
  namespace arch
  {
    namespace posix
    {
      class ArchitectureImplementation
      {
      public:

#if defined(DEBUG)
        static void
        putGreeting(void);
#endif
      };
    }

    typedef posix::ArchitectureImplementation ArchitectureImplementation_t;
  }
}

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX)

#endif // HAL_ARCHITECTURE_SYNTHETIC_POSIX_ARCHITECTUREIMPLEMENTATION_H_
