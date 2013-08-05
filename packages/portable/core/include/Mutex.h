//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Core mutex.

#ifndef OS_PORTABLE_CORE_MUTEX_H_
#define OS_PORTABLE_CORE_MUTEX_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include "portable/diagnostics/include/Trace.h"

//#include "portable/core/include/Architecture.h"

#include "portable/core/include/NamedObject.h"
//#include "portable/core/include/Stack.h"
//#include "portable/core/include/Scheduler.h"
#include "portable/core/include/TimerBase.h"
#include "portable/core/include/TimerTicks.h"
#include "portable/core/include/CriticalSections.h"

namespace os
{
  namespace core
  {
    // ========================================================================

#pragma GCC diagnostic push
#if defined(__clang__)
//#pragma clang diagnostic ignored "-Wpadded"
#endif

    /// \class TRecursiveMutex Mutex.h "portable/core/include/Mutex.h"
    /// \ingroup core
    /// \nosubgrouping
    ///
    /// \brief Core recursive mutex template.
    /// \tparam CriticalSectionLock_T  Type of the critical section lock.
    ///
    /// \details
    /// A mutex object facilitates protection against data races and
    /// allows safe synchronisation of data between execution agents
    /// (30.2.5). An execution agent owns a mutex from the time it
    /// successfully calls one of the lock functions until it calls
    /// unlock. The TRecursiveMutex template provides a recursive mutex with
    /// exclusive ownership semantics. If one thread owns a TRecursiveMutex
    /// object, attempts by another thread to acquire ownership of
    /// that object will fail (for tryLock()) or block (for lock())
    /// until the first thread has completely released ownership.
    ///
    /// A thread that owns a recursive_mutex object may acquire
    /// additional levels of ownership by calling lock() or tryLock()
    /// on that object. It is unspecified how many levels of ownership
    /// may be acquired by a single thread. A thread shall call unlock()
    /// once for each level of ownership acquired by calls to lock()
    /// and tryLock(). Only when all levels of ownership have been
    /// released may ownership be acquired by another thread.
    ///
    /// The behaviour of a program is undefined if:
    /// - it destroys a TRecursiveMutex object owned by any thread or
    /// - a thread terminates while owning a TRecursiveMutex object.
    template<class CriticalSectionLock_T>
      class TRecursiveMutex : public NamedObject
      {
      public:
        /// \name Types and constants
        /// @{

        /// @} end of name Types and constants

        /// \name Constructors/destructor
        /// @{

        /// \brief Default constructor.
        ///
        /// \par Parameters
        ///    None.
        TRecursiveMutex(void);

        /// \brief Constructor.
        ///
        /// \param [in] pName             Pointer to the null terminated mutex name.
        TRecursiveMutex(const char* const pName);

        /// \brief Destructor.
        ~TRecursiveMutex();

        /// \brief Deleted copy constructor.
        TRecursiveMutex(const TRecursiveMutex&) = delete;

        /// @} end of name Constructors/destructor

        /// \name Operators
        /// @{

        /// \brief Deleted assignment operator.

        TRecursiveMutex&
        operator=(const TRecursiveMutex&) = delete;

        /// @} end of name Operators

        /// \name Public member functions
        /// @{

        /// \brief Lock the mutex.
        void
        lock(void);

        /// \brief Unlock the mutex.
        void
        unlock(void) noexcept;

        /// \brief Try to lock the mutex indefinitely.
        void
        tryLock(void) noexcept;

        /// \brief Try to lock the mutex for a given period of time.
        bool
        tryLockFor(timer::ticks_t ticks, TimerBase& timer = os::timerTicks);

        /// @} end of Public member functions

      private:

        /// \name Private friends
        /// @{

        //friend Scheduler;

        /// @} end of Private friends

        /// \name Private member functions
        /// @{

        /// @} end of Private member functions

        /// \name Private member variables
        /// @{

        /// @} end of Private member variables

      };

#pragma GCC diagnostic pop

    // ------------------------------------------------------------------------

    // inlines

    // ========================================================================

    struct defer_lock_t
    {
    };

    struct try_to_lock_t
    {
    };

    struct adopt_lock_t
    {
    };

    constexpr defer_lock_t defer_lock = defer_lock_t();
    constexpr try_to_lock_t try_to_lock = try_to_lock_t();
    constexpr adopt_lock_t adopt_lock = adopt_lock_t();

    // ------------------------------------------------------------------------

    /// \class TLockGuard Mutex.h "portable/core/include/Mutex.h"
    /// \ingroup core
    /// \nosubgrouping
    ///
    /// \brief Lock guard template.
    ///
    /// \tparam Lockable_T  Type of the lockable object.
    ///
    /// \details
    /// An object of type TLockGuard controls the ownership of a lockable
    /// object within a scope. A TLockGuard object maintains ownership
    /// of a lockable object throughout the TLockGuard object’s
    /// lifetime (3.8). The behavior of a program is undefined if
    /// the lockable object referenced by m_lockable does not exist for
    /// the entire lifetime of the lock_guard object. The supplied
    /// Lockable_T type shall meet the BasicLockable requirements (30.2.5.2).
    /// \note This template is based on the standard C++11 lock_guard template.
    template<class Lockable_T>
      class TLockGuard
      {
      public:
        /// \name Types and constants
        /// @{

        /// \brief Local copy of the template lockable type.
        typedef Lockable_T Lockable;

        /// @} end of name Types and constants

      public:

        /// \name Constructors/destructor
        /// @{

        /// \brief Constructor.
        ///
        /// \param [in] lockable             Basic lockable object.
        explicit
        TLockGuard(Lockable& lockable);

        /// \brief Constructor.
        ///
        /// \param [in] lockable             Basic lockable object.
        TLockGuard(Lockable& lockable, adopt_lock_t);

        /// \brief Destructor.
        ~TLockGuard();

        /// \brief Deleted copy constructor.
        TLockGuard(TLockGuard const&) = delete;

        /// @} end of name Constructors/destructor

        /// \name Operators
        /// @{

        /// \brief Deleted assignment operator.

        TLockGuard&
        operator=(TLockGuard const&) = delete;

        /// @} end of name Operators

      private:
        /// \name Private member variables
        /// @{

        Lockable& m_lockable;

        /// @} end of Private member variables
      };

    // ------------------------------------------------------------------------

    /// \details
    /// Perform lockable.lock() to acquire the lock.
    ///
    /// \warning If Lockable is not a recursive mutex,
    /// the calling thread should not already own the mutex.
    template<class Lockable_T>
      inline
      __attribute__((always_inline))
      TLockGuard<Lockable_T>::TLockGuard(Lockable& lockable)
          : m_lockable(lockable)
      {
        m_lockable.lock();
      }

    /// \details
    /// If the calling thread already owns the lockable, just adopt it,
    /// without calling lock() to acquire it.
    template<class Lockable_T>
      inline
      __attribute__((always_inline))
      TLockGuard<Lockable_T>::TLockGuard(Lockable& lockable, adopt_lock_t)
          : m_lockable(lockable)
      {
        // nothing to do
      }

    /// \details
    /// Perform m_lockable.unlock() and give ownership of the lockable.
    template<class Lockable_T>
      inline
      __attribute__((always_inline))
      TLockGuard<Lockable_T>::~TLockGuard()
      {
        m_lockable.unlock();
      }

    // ========================================================================

    // Declare the template instantiation
    extern template class TRecursiveMutex<scheduler::CriticalSection> ;

  // ========================================================================

  }// namespace core
} // namespace os

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
#endif // OS_PORTABLE_CORE_MUTEX_H_
