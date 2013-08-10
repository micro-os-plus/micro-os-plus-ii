//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Core mutex.
///
/// \details
/// A mutex object facilitates protection against data races and
/// allows safe synchronisation of data between execution agents
/// (30.2.5). An execution agent owns a mutex from the time it
/// successfully calls one of the lock functions until it calls
/// unlock.

#ifndef OS_PORTABLE_CORE_MUTEX_H_
#define OS_PORTABLE_CORE_MUTEX_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include "portable/diagnostics/include/Trace.h"

//#include "portable/core/include/Architecture.h"

#include "portable/core/include/NamedObject.h"
#include "portable/core/include/Thread.h"
#include "portable/core/include/Scheduler.h"
#include "portable/core/include/TimerBase.h"
#include "portable/core/include/TimerTicks.h"
#include "portable/core/include/CriticalSections.h"
#include "portable/language/cpp/include/climits.h"

namespace os
{
  namespace core
  {
    namespace mutex
    {

      // ======================================================================

      typedef int count_t;

      // ======================================================================

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

      /// \class TNotifier Mutex.h "portable/core/include/Mutex.h"
      /// \ingroup core_synchro
      /// \nosubgrouping
      ///
      /// \brief Mutex notifier.
      template<int Size_T = os::core::scheduler::MAX_USER_THREADS>
        class TNotifier
        {
        public:
          /// \name Types and constants
          /// @{

          /// \brief The size of the internal array.
          static constexpr int NOTIFY_ARRAY_SIZE = (Size_T > 0) ? Size_T : 1;

          /// \brief Embedded class for storage elements.
          class Element
          {
          public:
            Thread* volatile pThread;

            inline
            __attribute__((always_inline))
            Element()
            {
              pThread = nullptr;
            }

            inline
            __attribute__((always_inline))
            Element(volatile Element& e)
            {
              pThread = e.pThread;
            }

            inline Element&
            __attribute__((always_inline))
            operator=(const Element& e)
            {
              pThread = e.pThread;
              return *this;
            }
          };

          /// @} end of name Types and constants

          /// \name Constructors/destructor
          /// @{

          /// \brief Default constructor.
          ///
          /// \par Parameters
          ///    None.
          TNotifier(void);

          /// \brief Destructor.
          ~TNotifier();

          /// \brief Deleted copy constructor.
          TNotifier(const TNotifier&) = delete;

          /// @} end of name Constructors/destructor

          /// \name Operators
          /// @{

          /// \brief Deleted assignment operator.
          TNotifier&
          operator=(const TNotifier&) = delete;

          /// \brief Subscripting operator.
          ///
          /// \param [in] index           The position of the element to return, starting from 0.
          /// \return                     The array element.
          Element&
          operator[](int index);

          /// @} end of name Operators

          /// \name Public member functions
          /// @{

          /// \brief Clear array.
          ///
          /// \par Parameters
          ///    None.
          /// \par Return
          ///   Nothing.
          void
          clear(void);

          /// \brief Get count.
          ///
          /// \par Parameters
          ///    None.
          /// \return                   The number of threads in the array.
          count_t
          getCount(void);

          /// \brief Add thread at the end of the array.
          ///
          /// \par Parameters
          ///    None.
          /// \retval true              The element was added.
          /// \retval false             There is no more space.
          bool
          pushBack(Thread* pThread);

          /// \brief Remove the thread from the array.
          ///
          /// \par Parameters
          ///    None.
          /// \par Return
          ///   Nothing.
          void
          remove(Thread* pThread);

          /// \brief Check if the thread is present in the array.
          ///
          /// \par Parameters
          ///    None.
          /// \retval true              The element is in the array.
          /// \retval false             Otherwise.
          bool
          hasElement(Thread* pThread);

          /// \brief Resume all threads present in the array.
          ///
          /// \par Parameters
          ///    None.
          /// \par Return
          ///   Nothing.
          void
          resumeAll(void);

          /// @} end of Public member functions

          /// \name Iterators
          /// @{

          /// \brief Iterator begin.
          ///
          /// \par Parameters
          ///    None.
          /// \return                     A pointer to the first element.
          Element volatile*
          begin(void);

          /// \brief Iterator end.
          ///
          /// \par Parameters
          ///    None.
          /// \return                     A pointer <b>after</b> the last element.
          Element volatile*
          end(void);

          /// @} end of Iterators

        protected:

          /// \name Private member variables
          /// @{

          /// \brief Array of pointer to threads waiting to acquire mutex.
          Element volatile m_array[NOTIFY_ARRAY_SIZE];

          /// \brief Counter for the threads waiting to acquire mutex.
          count_t volatile m_count;

          /// @} end of Private member variables

        };

#pragma GCC diagnostic pop

      // ------------------------------------------------------------------------

      template<int Size_T>
        inline
        __attribute__((always_inline))
        TNotifier<Size_T>::TNotifier(void)
        {
          m_count = 0;
        }

      template<int Size_T>
        inline
        __attribute__((always_inline))
        TNotifier<Size_T>::~TNotifier()
        {
        }

      template<int Size_T>
        inline void
        __attribute__((always_inline))
        TNotifier<Size_T>::clear(void)
        {
          m_count = 0;
        }

      /// \details
      /// Return the actual number of elements in the array.
      template<int Size_T>
        inline mutex::count_t
        __attribute__((always_inline))
        TNotifier<Size_T>::getCount(void)
        {
          return m_count;
        }

      /// \details
      /// Return a reference to the i-th element of the array.
      template<int Size_T>
        inline typename TNotifier<Size_T>::Element&
        __attribute__((always_inline))
        TNotifier<Size_T>::operator[](int index)
        {
          return m_array[index];
        }

      /// \details
      /// Return the beginning of the array.
      template<int Size_T>
        inline typename TNotifier<Size_T>::Element volatile*
        __attribute__((always_inline))
        TNotifier<Size_T>::begin(void)
        {
          return &m_array[0];
        }

      /// \details
      /// Return the end of the array.
      /// The end is given by the actual content, not by the array size.
      template<int Size_T>
        inline typename TNotifier<Size_T>::Element volatile*
        __attribute__((always_inline))
        TNotifier<Size_T>::end(void)
        {
          return &m_array[m_count];
        }

      /// \details
      /// Add an element at the end of the array, if not full.
      template<int Size_T>
        bool
        TNotifier<Size_T>::pushBack(Thread* pThread)
        {
          // Add pThread to the list of suspended threads
          if (m_count >= NOTIFY_ARRAY_SIZE)
            {
              return false;
            }

          m_array[m_count].pThread = pThread;
          ++m_count;

          return true;
        }

      template<int Size_T>
        void
        TNotifier<Size_T>::remove(Thread* pThread)
        {

          timer::count_t count = m_count;

          // Check if there are any elements in the array
          if (count == 0)
            {
              // There are not, nothing to do
              return;
            }

          // Try to find the location of the thread in the array
          // volatile does not matter here, we are ina critical region
          Element* p = const_cast<Element*>(&m_array[0]);

          int index;
          for (index = 0; index < count; ++index, ++p)
            {
              if (pThread == p->pThread)
                {
                  // Got it, index remembers the position
                  break;
                }
            }

          // If we reached the end of the world, the thread is not in,
          // so nothing to remove
          if (index == count)
            return;

          if (count > 1)
            {
              // If at least two elements, we might need to move
              // part of the array

              // The search left the pointer on the element we
              // want to remove, p = &m_pArray[index];

              for (; index < count - 1; index++, p++)
                {
                  // Move remaining elements one step to the left
                  *p = *(p + 1);
                }
            }

          // We removed one element, the count is decremented
          m_count--;

        }

      /// \details
      /// Iterate the active part of the array and try to identify
      /// the thread.
      template<int Size_T>
        bool
        TNotifier<Size_T>::hasElement(Thread* pThread)
        {
#if 1
          // Note: object copy constructor
          for (Element element : *this)
            {
              if (element.pThread == pThread)
                return true;
            }
#else
          count_t i;
          for (i = 0; i < m_count; ++i)
            {
              // check if the thread is already in the list
              if (m_array[i].pThread == pThread)
              return true;
            }
#endif
          return false;
        }

      /// \details
      /// Iterate the active part of the array and resume all
      /// threads waiting to acquire the mutex.
      template<int Size_T>
        void
        TNotifier<Size_T>::resumeAll(void)
        {
          // Resume all waiting threads
#if 1
          for (Element element : *this)
            {
              element.pThread->resume(
                  ResumeDetails::REGULAR | ResumeDetails::MUTEX);
            }

#else
          for (count_t i = 0; i < m_count; ++i)
            {
              // no context switches will happen inside critical section
              m_array[i].pThread->resume(ResumeDetails::REGULAR | ResumeDetails::MUTEX);
            }
#endif
        }

      // ========================================================================

      /// \class RecursivePolicy Mutex.h "portable/core/include/Mutex.h"
      /// \ingroup core_synchro
      /// \nosubgrouping
      ///
      /// \brief Policy used to implement a recursive mutex.
      ///
      /// Basically a managed counter, to keep track of the recursion depth.
      class RecursivePolicy
      {
      public:
        static constexpr count_t MAX_COUNT = INT_MAX;

        /// \name Constructors/destructor
        /// @{

        /// \brief Default constructor.
        ///
        /// \par Parameters
        ///    None.
        RecursivePolicy(void);

        /// \brief Destructor.
        ~RecursivePolicy() = default;

        /// \brief Deleted copy constructor.
        RecursivePolicy(const RecursivePolicy&) = delete;

        /// @} end of name Constructors/destructor

        /// \name Operators
        /// @{

        /// \brief Deleted assignment operator.
        RecursivePolicy&
        operator=(const RecursivePolicy&) = delete;

        /// @} end of name Operators

        /// \name Public member functions
        /// @{

        /// \brief Initialise the recursion depth counter.
        ///
        /// \par Parameters
        ///    None.
        /// \par Return
        ///   Nothing.
        void
        initialise(void);

        /// \brief Check if lock() is possible.
        ///
        /// \par Parameters
        ///    None.
        /// \retval true              The embedded lock() is possible.
        /// \retval false             Otherwise.
        bool
        isRecursiveLockPossible(void);

        /// \brief Perform the recursive lock().
        ///
        /// \par Parameters
        ///    None.
        /// \par Return
        ///   Nothing.
        void
        recursiveLock(void);

        /// \brief Check if unlock() is possible.
        ///
        /// \par Parameters
        ///    None.
        /// \retval true              The embedded unlock() is possible.
        /// \retval false             Otherwise.
        bool
        isRecursiveUnlockPossible(void);

        /// \brief Perform the recursive unlock().
        ///
        /// \par Parameters
        ///    None.
        /// \par Return
        ///   Nothing.
        void
        recursiveUnlock(void);

        /// \brief Check if unlock() is complete.
        ///
        /// \par Parameters
        ///    None.
        /// \retval true              The embedded unlock() is complete.
        /// \retval false             Otherwise.
        bool
        isRecursiveUnlockComplete(void);

      private:

        /// \name Private member variables
        /// @{

        /// \brief Counter for the recursion depth.
        count_t volatile m_count;

        /// @} end of Private member variables

      };

      inline
      __attribute__((always_inline))
      RecursivePolicy::RecursivePolicy(void)
      {
        m_count = 0;
      }

      /// \details
      /// Reset the counter to zero.
      inline
      void
      __attribute__((always_inline))
      RecursivePolicy::initialise(void)
      {
        m_count = 0;
      }

      /// \details
      /// If the counter reached the maximum allowed value, return false.
      inline
      bool
      __attribute__((always_inline))
      RecursivePolicy::isRecursiveLockPossible(void)
      {
        if (m_count != MAX_COUNT)
          {
            return true;
          }
        return false;
      }

      /// \details
      /// Increment the recursion counter.
      inline
      void
      __attribute__((always_inline))
      RecursivePolicy::recursiveLock(void)
      {
        m_count++;
      }

      /// \details
      /// Validate the configuration, the counter should not be zero.
      inline
      bool
      __attribute__((always_inline))
      RecursivePolicy::isRecursiveUnlockPossible(void)
      {
        if (m_count == 0)
          {
            // Error, counter out of sync
            return false;
          }
        return true;
      }

      /// \details
      /// Decrement the recursion counter.
      inline
      void
      __attribute__((always_inline))
      RecursivePolicy::recursiveUnlock(void)
      {
        --m_count;
      }

      /// \details
      /// The recursion ends when the counter returns to zero.
      inline
      bool
      __attribute__((always_inline))
      RecursivePolicy::isRecursiveUnlockComplete(void)
      {
        if (m_count == 0)
          {
            return true;
          }

        // More levels of ownership to be released
        return false;
      }

      // ========================================================================

      /// \class NonRecursivePolicy Mutex.h "portable/core/include/Mutex.h"
      /// \ingroup core_synchro
      /// \nosubgrouping
      ///
      /// \brief Policy used to implement a non-recursive mutex.
      ///
      /// \details
      /// Basically an empty class.
      class NonRecursivePolicy
      {
      public:
        /// \name Constructors/destructor
        /// @{

        /// \brief Default constructor.
        ///
        /// \par Parameters
        ///    None.
        NonRecursivePolicy(void);

        /// \brief Destructor.
        ~NonRecursivePolicy() = default;

        /// \brief Deleted copy constructor.
        NonRecursivePolicy(const NonRecursivePolicy&) = delete;

        /// @} end of name Constructors/destructor

        /// \name Operators
        /// @{

        /// \brief Deleted assignment operator.
        NonRecursivePolicy&
        operator=(const NonRecursivePolicy&) = delete;

        /// @} end of name Operators

        /// \name Public member functions
        /// @{

        /// \brief Initialise the recursion depth counter.
        ///
        /// \par Parameters
        ///    None.
        /// \par Return
        ///   Nothing.
        void
        initialise(void);

        /// \brief Check if lock() is possible.
        ///
        /// \par Parameters
        ///    None.
        /// \retval true              The embedded lock() is possible.
        /// \retval false             Otherwise.
        bool
        isRecursiveLockPossible(void);

        /// \brief Perform the recursive lock().
        ///
        /// \par Parameters
        ///    None.
        /// \par Return
        ///   Nothing.
        void
        recursiveLock(void);

        /// \brief Check if unlock() is possible.
        ///
        /// \par Parameters
        ///    None.
        /// \retval true              The embedded unlock() is possible.
        /// \retval false             Otherwise.
        bool
        isRecursiveUnlockPossible(void);

        /// \brief Perform the recursive unlock().
        ///
        /// \par Parameters
        ///    None.
        /// \par Return
        ///   Nothing.
        void
        recursiveUnlock(void);

        /// \brief Check if unlock() is complete.
        ///
        /// \par Parameters
        ///    None.
        /// \retval true              The embedded unlock() is complete.
        /// \retval false             Otherwise.
        bool
        isRecursiveUnlockComplete(void);

      private:

        /// \name Private member variables
        /// @{

        /// @} end of Private member variables

      };

      inline
      __attribute__((always_inline))
      NonRecursivePolicy::NonRecursivePolicy(void)
      {
      }

      inline
      void
      __attribute__((always_inline))
      NonRecursivePolicy::initialise(void)
      {
      }

      inline
      bool
      __attribute__((always_inline))
      NonRecursivePolicy::isRecursiveLockPossible(void)
      {
        return false;
      }

      inline
      void
      __attribute__((always_inline))
      NonRecursivePolicy::recursiveLock(void)
      {
      }

      inline
      bool
      __attribute__((always_inline))
      NonRecursivePolicy::isRecursiveUnlockPossible(void)
      {
        return true;
      }

      inline
      void
      __attribute__((always_inline))
      NonRecursivePolicy::recursiveUnlock(void)
      {
      }

      inline
      bool
      __attribute__((always_inline))
      NonRecursivePolicy::isRecursiveUnlockComplete(void)
      {
        return true;
      }

    // ========================================================================

    }// namespace mutex

    // ========================================================================

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

    /// \class TGenericMutex Mutex.h "portable/core/include/Mutex.h"
    /// \ingroup core_synchro
    /// \nosubgrouping
    ///
    /// \brief Core recursive mutex template.
    /// \tparam CriticalSectionLock_T   Type of the critical section lock.
    /// \tparam Notifier_T              Type of the thread notifier.
    /// \tparam Policy_T                Type of the policy used to implement recursion.
    ///
    /// \details
    /// The TGenericMutex template provides a generic
    /// recursive/non-recursive mutex with
    /// exclusive ownership semantics. The specific recursive/non-recursive
    /// behaviour is implemented as a separate policy class.
    ///
    /// If one thread owns a TGenericMutex
    /// object, attempts by another thread to acquire ownership of
    /// that object will fail (for tryLock()) or block (for lock())
    /// until the first thread has completely released ownership.
    ///
    /// A thread that owns a recursive TGenericMutex may acquire
    /// additional levels of ownership by calling lock() or tryLock()
    /// on that object. It is unspecified how many levels of ownership
    /// may be acquired by a single thread. However this limit is specified
    /// in the Policy_T implementation. A thread shall call unlock()
    /// once for each level of ownership acquired by calls to lock()
    /// and tryLock(). Only when all levels of ownership have been
    /// released may ownership be acquired by another thread.
    ///
    /// The behaviour of a program is undefined if:
    /// - it destroys a TRecursiveMutex object owned/locked by any thread or
    /// - a thread terminates while owning a TRecursiveMutex object.
    template<class CriticalSectionLock_T, class Notifier_T, class Policy_T>
      class TGenericMutex : public NamedObject
      {
      public:
        /// \name Types and constants
        /// @{

        typedef CriticalSectionLock_T CriticalSectionLock;

        typedef Notifier_T Notifier;

        typedef Policy_T Policy;

        /// @} end of name Types and constants

        /// \name Constructors/destructor
        /// @{

        /// \brief Default constructor.
        ///
        /// \par Parameters
        ///    None.
        TGenericMutex(void);

        /// \brief Constructor.
        ///
        /// \param [in] pName           Pointer to the null terminated mutex name.
        TGenericMutex(const char* const pName);

        /// \brief Destructor.
        ~TGenericMutex();

        /// \brief Deleted copy constructor.
        TGenericMutex(const TGenericMutex&) = delete;

        /// @} end of name Constructors/destructor

        /// \name Operators
        /// @{

        /// \brief Deleted assignment operator.

        TGenericMutex&
        operator=(const TGenericMutex&) = delete;

        /// @} end of name Operators

        /// \name Public member functions
        /// @{

        /// \brief Lock the mutex.
        ///
        /// \par Parameters
        ///    None.
        /// \par Return
        ///   Nothing.
        /// \par Errors
        ///     - SUCCEEDED - the mutex was acquired.
        ///     - CANCELLED - the operation was cancelled due
        ///                   to an attention request.
        ///     - RECURSION_DEPTH_EXCEEDED - too many recursive calls.
        ///     - INTERNAL_SIZE_EXCEEDED - the size of the array to store
        ///                                threads to notify was exceeded.
        void
        lock(void);

        /// \brief Try to lock the mutex and return immediately.
        ///
        /// \par Parameters
        ///    None.
        /// \retval true        If the ownership of the mutex was
        ///                     obtained for the calling thread.
        /// \retval false       Otherwise.
        /// \par Errors
        ///     - SUCCEEDED - the mutex was acquired.
        ///     - BUSY - the mutex is owned by another thread.
        ///     - CANCELLED - the operation was cancelled due
        ///                   to an attention request.
        ///     - RECURSION_DEPTH_EXCEEDED - too many recursive calls.
        bool
        tryLock(void) noexcept;

        /// \brief Try to lock the mutex, blocking for a period of time.
        ///
        /// \param [in] ticks   The number of counter ticks.
        /// \param [in] timer   The timer to use (default the ticks timer).
        /// \retval true        If the ownership of the mutex was
        ///                     obtained for the calling thread.
        /// \retval false       Otherwise.
        /// \par Errors
        ///     - SUCCEEDED - the mutex was acquired.
        ///     - TIMEOUT - the mutex could not be acquired in the given period.
        ///     - CANCELLED - the operation was cancelled due
        ///                   to an attention request.
        ///     - RECURSION_DEPTH_EXCEEDED - too many recursive calls.
        ///     - INTERNAL_SIZE_EXCEEDED - the size of the array to store
        ///                                threads to notify was exceeded.
        bool
        tryLockFor(timer::ticks_t ticks, TimerBase& timer = os::timerTicks);

        /// \brief Unlock the mutex.
        ///
        /// \par Parameters
        ///    None.
        /// \par Return
        ///   Nothing.
        /// \par Errors
        ///     - SUCCEEDED - the mutex was acquired.
        ///     - NOT_OWNER - the mutex is now owned by the current thread.
        ///     - OUT_OF_SYNC - validity recursion checks failed.
        void
        unlock(void) noexcept;

        /// @} end of Public member functions

      private:

        /// \name Private member variables
        /// @{

        /// \brief Pointer to the owner of the mutex or nullptr.
        Thread* volatile m_owningThread = nullptr;

        /// \brief The object used to keep track of the threads waiting to
        /// acquire the mutex, in the call order.
        Notifier m_notifier;

        /// \brief Specific recursive/non-recursive policy.
        Policy m_policy;

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

    /// \ingroup core_synchro
    /// @{

    /// \brief Tag to defer lock.
    constexpr defer_lock_t defer_lock = defer_lock_t();

    /// \brief Tag to try to lock.
    constexpr try_to_lock_t try_to_lock = try_to_lock_t();

    /// \brief Tag to adopt an existing lock.
    constexpr adopt_lock_t adopt_lock = adopt_lock_t();

    /// @} end of ingroup core_synchro

    // ------------------------------------------------------------------------

    /// \class TLockGuard Mutex.h "portable/core/include/Mutex.h"
    /// \ingroup core_synchro
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

        /// \brief A reference to the lockable object.
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

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

    // Declare the template instantiation

    extern template class TGenericMutex<scheduler::CriticalSection,
        mutex::TNotifier<>, mutex::RecursivePolicy> ;
    extern template class TGenericMutex<scheduler::CriticalSection,
        mutex::TNotifier<>, mutex::NonRecursivePolicy> ;

#pragma GCC diagnostic pop

    /// \brief Common non-recursive mutex instantiation.
    /// \ingroup core_synchro
    using Mutex = TGenericMutex<scheduler::CriticalSection,
    mutex::TNotifier<>, mutex::NonRecursivePolicy>;

    /// \brief Common recursive mutex instantiation
    /// \ingroup core_synchro
    using RecursiveMutex = TGenericMutex<scheduler::CriticalSection,
    mutex::TNotifier<>, mutex::RecursivePolicy>;

  // ========================================================================

  }// namespace core
} // namespace os

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
#endif // OS_PORTABLE_CORE_MUTEX_H_
