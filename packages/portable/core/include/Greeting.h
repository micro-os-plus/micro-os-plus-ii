/*
 *      Copyright (C) 2012-2013 Liviu Ionescu.
 *
 *      This file is part of the uOS++ distribution.
 */

#ifndef OS_PORTABLE_CORE_INCLUDE_OS_GREETING_H_
#define OS_PORTABLE_CORE_INCLUDE_OS_GREETING_H_

#include "portable/core/include/OS_Defines.h"

#if defined(OS_INCLUDE_GREETING)

#include "portable/core/include/XCDL_Greeting_Defines.h"

#if defined(APP_INTEGER_VERSION_MAJOR) && defined(APP_INTEGER_VERSION_MINOR) && defined(APP_INTEGER_VERSION_REVISION)

// Strings
#define APP_STRING_VERSION_MAJOR        OS_MACRO_STRINGIFY(APP_INTEGER_VERSION_MAJOR)
#define APP_STRING_VERSION_MINOR        OS_MACRO_STRINGIFY(APP_INTEGER_VERSION_MINOR)
#define APP_STRING_VERSION_REVISION     OS_MACRO_STRINGIFY(APP_INTEGER_VERSION_REVISION)

#define APP_STRING_VERSION              APP_STRING_VERSION_MAJOR "." APP_STRING_VERSION_MINOR "." APP_STRING_VERSION_REVISION

#if defined(APP_STRING_APPLICATION_NAME) && defined(APP_STRING_APPLICATION_MANUFACTURER)

#define APP_STRING_GREETING     APP_STRING_APPLICATION_MANUFACTURER \
  " / " APP_STRING_APPLICATION_NAME " v" APP_STRING_VERSION ", " __DATE__ " " __TIME__

#endif /* defined(APP_STRING_APPLICATION_NAME) && .. */

#endif /* defined(APP_INTEGER_VERSION_MAJOR) && .. */

#if !defined(APP_STRING_GREETING)

// Default greeting message, will be used in OSDeviceDebug.cpp
#define APP_STRING_GREETING "uOS++ app"

#endif /* !defined(APP_STRING_GREETING) */

namespace os
{
  extern const char appGreeting[] __attribute__((weak));
  extern const char osGreeting[] __attribute__((weak));
}

#endif /* defined(OS_INCLUDE_GREETING) */

#endif /* OS_PORTABLE_CORE_INCLUDE_OS_GREETING_H_ */
