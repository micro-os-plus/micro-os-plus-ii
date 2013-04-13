//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Definitions of greeting strings.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_GREETING) || defined(__DOXYGEN__)

#include "portable/core/include/Greeting.h"

namespace os
{
  // Default greeting messages
  const char appGreeting[] = APP_STRING_GREETING;
  const char osGreeting[] = OS_STRING_GREETING;
}

#endif // defined(OS_INCLUDE_GREETING)
