//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Scheduler critical sections.

#ifndef OS_PORTABLE_CORE_CRITICALSECTION_H_
#define OS_PORTABLE_CORE_CRITICALSECTION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)
#include "portable/core/include/Scheduler.h"
#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)

namespace os
{
  namespace core
  {
    namespace scheduler
    {

      // ======================================================================

      class CriticalSection
      {
      public:
        CriticalSection(void);

        ~CriticalSection();
      };

      inline
      __attribute__((always_inline))
      CriticalSection::CriticalSection(void)
      {
#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)
        os::scheduler.lock();
#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
      }

      inline
      __attribute__((always_inline))
      CriticalSection::~CriticalSection()
      {
#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)
        os::scheduler.unlock();
        os::scheduler.yield();
#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
      }

      // ======================================================================

      // TODO: make an empty instance available always
#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)
      typedef hal::arch::InterruptsCriticalSection InterruptsCriticalSection;
#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)

    // ========================================================================
    }// namespace scheduler
  } // namespace core
} // namespace os

#endif // OS_PORTABLE_CORE_CRITICALSECTION_H_
