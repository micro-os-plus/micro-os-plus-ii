/*
 *      Copyright (C) 2012-2013 Liviu Ionescu.
 *
 *      This file is part of the uOS++ distribution.
 */

#include "portable/core/include/OS_Defines.h"

#if defined(OS_INCLUDE_GREETING)

#include "../include/Greeting.h"

namespace os
{
  // Default greeting messages
  const char appGreeting[] = APP_STRING_GREETING;
  const char osGreeting[] = OS_STRING_GREETING;
}

#endif /* defined(DEBUG) || defined(OS_INCLUDE_GREETING) */
