//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_GREETING) || defined(__DOXYGEN__)

#include "../include/Greeting.h"

namespace os
{
  // Default greeting messages
  const char appGreeting[] = APP_STRING_GREETING;
  const char osGreeting[] = OS_STRING_GREETING;
}

#endif // defined(OS_INCLUDE_GREETING)
