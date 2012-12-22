/*
 *      Copyright (C) 2012 Liviu Ionescu.
 *
 *      This file is part of the uOS++ distribution.
 */

#ifndef OS_PORTABLE_KERNEL_INCLUDE_OS_GREETING_H_
#define OS_PORTABLE_KERNEL_INCLUDE_OS_GREETING_H_

#include "portable/kernel/include/OS_Defines.h"

#if defined(DEBUG) || defined(OS_INCLUDE_GREETING)

#include "xcdl/OS_App_Defines.h"

#if defined(APP_CFGINT_VERSION_MAJOR) && defined(APP_CFGINT_VERSION_MINOR) && defined(APP_CFGINT_VERSION_REVISION)

// Strings
#define APP_CFGSTR_VERSION_MAJOR        OS_CFGSTR_STRINGIFY(APP_CFGINT_VERSION_MAJOR)
#define APP_CFGSTR_VERSION_MINOR        OS_CFGSTR_STRINGIFY(APP_CFGINT_VERSION_MINOR)
#define APP_CFGSTR_VERSION_REVISION     OS_CFGSTR_STRINGIFY(APP_CFGINT_VERSION_REVISION)

#define APP_CFGSTR_VERSION      APP_CFGSTR_VERSION_MAJOR "." APP_CFGSTR_VERSION_MINOR "." APP_CFGSTR_VERSION_REVISION

#if defined(APP_CFGSTR_APPLICATION_NAME) && defined(APP_CFGSTR_APPLICATION_MANUFACTURER)

#define APP_CFGSTR_GREETING     APP_CFGSTR_APPLICATION_MANUFACTURER \
  " / " APP_CFGSTR_APPLICATION_NAME " v" APP_CFGSTR_VERSION ", " __DATE__ " " __TIME__

#endif /* defined(APP_CFGSTR_APPLICATION_NAME) && .. */

#endif /* defined(APP_CFGINT_VERSION_MAJOR) && .. */

#if !defined(APP_CFGSTR_GREETING)

// Default greeting message, will be used in OSDeviceDebug.cpp
#define APP_CFGSTR_GREETING "uOS++ app"

#endif /* !defined(APP_CFGSTR_GREETING) */

namespace os
{
  extern const char greeting[] __attribute__((weak));
}

#endif /* defined(DEBUG) || defined(OS_INCLUDE_GREETING) */

#endif /* OS_PORTABLE_KERNEL_INCLUDE_OS_GREETING_H_ */
