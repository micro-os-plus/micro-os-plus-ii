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
        os::scheduler.lock();
      }

      inline
      __attribute__((always_inline))
      CriticalSection::~CriticalSection()
      {
        os::scheduler.unlock();
      }

      // ========================================================================

      class InterruptsCriticalSection
      {
      public:
        InterruptsCriticalSection(void);

        ~InterruptsCriticalSection();

      private:
        // TODO: add location to store interrupt status
      };

      inline
      __attribute__((always_inline))
      InterruptsCriticalSection::InterruptsCriticalSection(void)
      {
        // TODO: save status
      }

      inline
      __attribute__((always_inline))
      InterruptsCriticalSection::~InterruptsCriticalSection()
      {
        // TODO: restore status
      }

    // ========================================================================
    }// namespace scheduler
  } // namespace core
} // namespace os

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)

#endif // OS_PORTABLE_CORE_CRITICALSECTION_H_
