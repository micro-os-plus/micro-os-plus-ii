/*
 *      Copyright (C) 2012 Liviu Ionescu.
 *
 *      This file is part of the uOS++ distribution.
 */

#include "portable/kernel/include/OS_Defines.h"

#if defined(OS_INCLUDE_GREETING)

#include "../include/OSGreeting.h"

namespace os
{
  // Default greeting message
  const char greeting[] = APP_STRING_GREETING;
}

#endif /* defined(DEBUG) || defined(OS_INCLUDE_GREETING) */
