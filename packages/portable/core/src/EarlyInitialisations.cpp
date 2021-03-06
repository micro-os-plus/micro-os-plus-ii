//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Special class used to perform early initialisations/late cleanups.

#include "portable/core/include/ConfigDefines.h"

#include "portable/core/include/Architecture.h"
#include "portable/core/include/Platform.h"

#include "portable/diagnostics/include/Trace.h"
#include "portable/core/include/Greeting.h"

#include "portable/core/include/Scheduler.h"
#include "portable/core/include/MainThread.h"
#include "portable/core/include/IdleThread.h"
#include "portable/core/include/TimerTicks.h"
#include "portable/core/include/TimerSeconds.h"

#include "portable/core/include/Error.h"

namespace os
{
  namespace core
  {
    // ========================================================================

    /// \ingroup core
    /// \nosubgrouping
    ///
    /// \brief Special class used to perform early initialisations and
    /// late cleanups.
    ///
    /// \details
    /// Embedded systems require some specific hardware initialisations
    /// to be performed preferably as early as possible
    /// (for example switching the clock from slow internal RC to fast
    /// external crystal). Unfortunately there is no
    /// portable method to insert initialisation code before `main()`
    /// during the startup sequence. The most portable solution is to run
    /// the hardware initialisations at the beginning of `main()`, but since
    /// in C++ static initialisers are executed before `main()`, this
    /// has the disadvantage of running the constructors before the
    /// hardware initialisations (for example at low speed).
    ///
    /// The next option is to run the initialisations
    /// during the first static constructor. C++ does guarantee that
    /// *constructors for nonlocal objects in a translation unit are executed
    /// in the order their definitions occur*. Unfortunately *no implementation
    /// independent guarantees are made about the order of construction
    /// of nonlocal objects in different compilation units* [Stroustrup,
    /// The C++ Programming Language].
    ///
    /// In real life things are not that bad, and workarounds can most of
    /// the time be imagined.
    ///
    /// For example, with the current versions of GNU GCC and LLVM CLANG,
    /// the linker builds the list of nonlocal objects constructors in the
    /// same order as it processes input object files, so by arranging that
    /// this file is encountered
    /// first, we (more or less) guarantee that the initialisation
    /// code is executed before other constructors.
    ///
    /// Symmetrically, the destructor of this class should be called
    /// after all other static destructors, to cleanup the mess and
    /// reset the platform.
    ///
    /// \note Under normal circumstances, embedded applications usually
    /// do not return from `main()`,
    /// so the static destructors are not executed; this class
    /// has a destructor for just in case, to try to recover gracefully
    /// from possible errors.
    class EarlyInitialisations
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief This constructor should be executed before all others.
      EarlyInitialisations();

      /// \brief This destructor should be executed after all others
      ~EarlyInitialisations();

      /// @} end of name Constructors/destructor

    };

    /// \details
    /// All hardware initialisations are performed here, in the desired
    /// order.
    /// \note The Trace object is not yet initialised
    /// and no trace calls should be issued here.
    EarlyInitialisations::EarlyInitialisations()
    {
      // WARNING: no trace available yet, wait for the
      // Trace object to be initialised later!

      os::platform.initialiseSystem();

#if defined(DEBUG)
      // power up (initialise) the trace device
      os::diag::Trace::powerUp();
#endif
    }

    /// \details
    /// All hardware cleanups and finally the call to reset the
    /// platform are performed here.
    EarlyInitialisations::~EarlyInitialisations()
    {
#if defined(DEBUG)
      // Power down the trace device
      os::diag::Trace::powerDown();
#endif
      // On platforms like Posix this is empty, 
      // since the process must run its cleaup code.
      // On bare metal this shall reset the system.
      os::platform.exit();
    }

  // ==========================================================================

  }// namespace core
} // namespace os

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

/// \brief Single static instance of the `os::core::EarlyInitialisations` class.
///
/// \details
/// The must be the first static object in this file, to guarantee
/// that the initialisations performed by its constructor are
/// called before others, and the cleanups performed by its
/// destructor are performed right at the end.
static os::core::EarlyInitialisations earlyInitialisations;

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------

#if defined(DEBUG) || defined(__DOXYGEN__)

namespace os
{
  namespace diag
  {
#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

    // the trace object instantiation
    /// \ingroup diag
    /// \details
    /// The diagnostics trace object.
    os::diag::Trace trace;

#pragma GCC diagnostic pop

  } // namespace diag
} // namspace os

#endif // defined(DEBUG)
// ----------------------------------------------------------------------------

#if defined(DEBUG) || defined(__DOXYGEN__)

namespace os
{
  namespace core
  {

    /// \ingroup core
    /// \nosubgrouping
    ///
    /// \brief Special class used to display greetings.
    class EarlyGreetings
    {
    public:
      /// \brief This constructor will be executed right.
      /// after the Trace is constructed.
      EarlyGreetings();

      ~EarlyGreetings();

    };

    /// \details
    /// Once the early initialisations are done and the Trace
    /// object is constructed, we can display the greeting
    /// messages.
    EarlyGreetings::EarlyGreetings()
    {
      // start with application greeting
      os::diag::trace.putNewLine();
      os::diag::trace.putString(os::appGreeting);
      os::diag::trace.putNewLine();

      // continue with OS greeting
      os::diag::trace.putString(os::osGreeting);
      os::diag::trace.putNewLine();

      // then with HAL (platform, that will call architecture)
      os::platform.putGreeting();

      os::diag::trace.putNewLine();
    }

    EarlyGreetings::~EarlyGreetings()
    {
      // The opposite of early, i.e. late greeting, used for bood bye
      os::diag::trace.putNewLine();
      os::diag::trace.putString("Hasta la vista, baby!");
      os::diag::trace.putNewLine();
    }
  } // namespace core
} // namespace os

#endif // defined(DEBUG)
// ----------------------------------------------------------------------------

#if defined(DEBUG) || defined(__DOXYGEN__)

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

/// \ingroup core
/// \brief Single static instance of the `os::core::EarlyInitialisations` class.
///
/// \details
/// This must be the second static object in this file,
/// to guarantee that it is executed right after the early initialisations.
static os::core::EarlyGreetings earlyGreetings;

#pragma GCC diagnostic pop

#endif

// ----------------------------------------------------------------------------

namespace os
{
  // The order might be important, first architecture, then platform.

  /// \ingroup core_port
  /// @{

  /// \brief The portable `architecture` object. Use it even if
  /// on most architectures its functions are static.
  hal::arch::ArchitectureImplementation architecture;

  /// \brief The portable `platform` object. Use it even if
  /// on most platforms its functions are static.
  hal::platform::PlatformImplementation platform;

  /// @} end of ingroup core_port

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

  /// \ingroup core
  /// @{

  /// \brief The scheduler object.
  /// \note Since the scheduler is used in Thread constructors/destructors to
  /// register/deregister threads, the scheduler object
  /// must be constructed before any Thread object.
  os::core::Scheduler scheduler;

  /// \brief The thread associated with the main() function.
  ///
  /// \details
  /// Must be placed after the scheduler is constructed.
  os::core::MainThread mainThread;

  /// \brief The thread associated with idle process.
  ///
  /// \details
  /// Must be placed after the scheduler is constructed.
  os::core::IdleThread idleThread;

  /// \brief The timer counting scheduler ticks.
  os::core::TimerTicks timerTicks;

  /// \brief The timer counting scheduler seconds.
  os::core::TimerSeconds timerSeconds;

  /// \brief A redirection to the current thread error code.
  os::core::Error error;

/// @} end of ingroup core

#pragma GCC diagnostic pop

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
}  // namespace os

// ----------------------------------------------------------------------------
