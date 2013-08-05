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

      /// \class CriticalSection CriticalSections.h "portable/core/include/CriticalSections.h"
      /// \ingroup core
      /// \nosubgrouping
      ///
      /// \brief Scheduler critical section.
      ///
      /// \details
      /// A guard lock that allows safe synchronisation of data between
      /// threads by locking/unlocking the scheduler, i.e. by blocking
      /// context switches between threads.
      ///
      /// Since the scheduler meets the requirements of a recursive lock,
      /// this class can also be used recursively.
      ///
      /// \note There is no implicit yield() performed after the
      /// critical section is finished, applications that require it
      /// must perform it explicitly.
      class CriticalSection
      {
      public:
        /// \name Constructors/destructor
        /// @{

        /// \brief Default constructor.
        ///
        /// \par Parameters
        ///    None.
        CriticalSection(void);

        /// \brief Destructor.
        ~CriticalSection();

        /// @} end of name Constructors/destructor

      };

      /// \details
      /// Lock the scheduler.
      inline
      __attribute__((always_inline))
      CriticalSection::CriticalSection(void)
      {
#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)
        os::scheduler.lock();
#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
      }

      /// \details
      /// Unlock the scheduler.
      inline
      __attribute__((always_inline))
      CriticalSection::~CriticalSection()
      {
#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)
        os::scheduler.unlock();
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
