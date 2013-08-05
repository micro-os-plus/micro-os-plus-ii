//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Mutex definitions.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include "portable/core/include/Mutex.h"
//#include "portable/core/include/Scheduler.h"
//#include "portable/core/include/CriticalSections.h"

//#include "portable/core/include/PlatformBase.h"
//#include "portable/core/include/Architecture.h"

namespace os
{
  namespace core
  {
    // ------------------------------------------------------------------------

    /// \details
    /// Construct an anonymous mutex.
    ///
    /// \note Provided only to meet the C++11 requirement
    /// that the mutex type shall be DefaultConstructible.
    /// Not recommended for regular applications, use the named
    /// constructor instead.
    template<class CriticalSectionLock_T>
      TRecursiveMutex<CriticalSectionLock_T>::TRecursiveMutex(void)
          : NamedObject()
      {
      }

    /// \details
    /// Construct a named mutex.
    template<class CriticalSectionLock_T>
      TRecursiveMutex<CriticalSectionLock_T>::TRecursiveMutex(
          const char* const pName)
          : NamedObject(pName)
      {
      }

    template<class CriticalSectionLock_T>
      TRecursiveMutex<CriticalSectionLock_T>::~TRecursiveMutex()
      {
      }

    template<class CriticalSectionLock_T>
      void
      TRecursiveMutex<CriticalSectionLock_T>::lock(void)
      {
      }

    template<class CriticalSectionLock_T>
      void
      TRecursiveMutex<CriticalSectionLock_T>::tryLock(void) noexcept
      {
      }

    template<class CriticalSectionLock_T>
      void
      TRecursiveMutex<CriticalSectionLock_T>::unlock(void) noexcept
      {
      }

    template<class CriticalSectionLock_T>
      bool
      TRecursiveMutex<CriticalSectionLock_T>::tryLockFor(
          timer::ticks_t ticks __attribute__((unused)),
          TimerBase& timer __attribute__((unused)))
      {
        return true;
      }

  // ------------------------------------------------------------------------
  }// namespace core
} //namespace os

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
