//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#ifndef OS_PORTABLE_CORE_PLATFORMBASE_H_
#define OS_PORTABLE_CORE_PLATFORMBASE_H_

#include "portable/core/include/ConfigDefines.h"

#include "portable/core/include/Architecture.h"

namespace os
{
  namespace core
  {
    class PlatformBase
    {
    public:

      static void
      initialiseSystem(void);

      static void
      resetSystem(void);

#if defined(DEBUG)
      static void
      putGreeting(void);
#endif

    };

    inline __attribute__((always_inline))
    void
    PlatformBase::initialiseSystem(void)
    {
      os::architecture.initialiseSystem();
    }

    inline __attribute__((always_inline))
    void
    PlatformBase::resetSystem(void)
    {
      os::architecture.resetSystem();
    }

  }
}

#endif // OS_PORTABLE_CORE_PLATFORMBASE_H_
