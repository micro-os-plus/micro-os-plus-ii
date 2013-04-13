//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/ConfigDefines.h"

#include "portable/core/include/Architecture.h"
#include "portable/core/include/Platform.h"

#include "portable/diagnostics/include/Trace.h"
#include "portable/core/include/Greeting.h"

namespace os
{
  namespace core
  {

    // ========================================================================

    /// \brief Special class used to perform early initialisations.
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

    class EarlyInitialisations
    {
    public:
      /// \brief This constructor will be executed before all others.
      EarlyInitialisations();
      ~EarlyInitialisations();
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
      // initialise the trace device
      os::diag::Trace::initialiseEarly();
#endif
    }

    EarlyInitialisations::~EarlyInitialisations()
    {
      os::platform.resetSystem();
    }

    // ========================================================================

  }
}

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

/// \brief Single static instance of the EarlyInitialisations class.
///
/// \details
/// This must be the first static object in this file, to guarantee
/// that the constructor is called before others.
static os::core::EarlyInitialisations earlyInitialisations;

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------

#if defined(DEBUG)

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

#endif

// ----------------------------------------------------------------------------

#if defined(DEBUG)

namespace os
{
  namespace core
  {

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

      // than with HAL (platform, that will architecture)
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
  }
}

#endif

// ----------------------------------------------------------------------------

#if defined(DEBUG)

#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wunknown-pragmas"
//#pragma GCC diagnostic ignored "-Wpragmas"
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

/// \brief Single static instance of the EarlyInitialisation class.
///
/// \details
/// The must be the first static object in this file, to guarantee
/// that the constructor is called before others.
static os::core::EarlyGreetings earlyGreetings;

#pragma GCC diagnostic pop

#endif

// ----------------------------------------------------------------------------

namespace os
{
  // The order might be important, first architecture, then platform.
  // However, most of the implementations will be static, so
  // it will not matter.
  hal::arch::ArchitectureImplementation architecture;
  hal::platform::PlatformImplementation platform;
}

// ----------------------------------------------------------------------------
