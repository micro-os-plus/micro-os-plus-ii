//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#ifndef OS_PORTABLE_CORE_PLATFORMBASE_H_
#define OS_PORTABLE_CORE_PLATFORMBASE_H_

#include "portable/core/include/ConfigDefines.h"

namespace os
{
  namespace core
  {
    class PlatformBase
    {
    public:

#if defined(DEBUG)
      static
      void
      putGreeting(void);
#endif

    };
  }
}

#endif // OS_PORTABLE_CORE_PLATFORMBASE_H_
