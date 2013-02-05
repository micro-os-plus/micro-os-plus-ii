//
//      Copyright (C) 2012-2013 Liviu Ionescu.
//
//      This file is part of the uOS++ distribution.
//

#include "portable/core/include/OS_Defines.h"

#include "portable/devices/debug/include/Debug.h"

namespace os
{
  namespace core
  {

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
    /// The next option is to arrange to run the initialisations
    /// during the first static constructor. C++ does guarantee that
    /// constructors for nonlocal objects in a translation unit are executed
    /// in the order their definitions occur. Unfortunately no implementation
    /// independent guarantees are made about the order of construction
    /// of nonlocal objects in different compilation units.
    ///
    /// In real life things are not that bad, and workarounds can most of
    /// the time be imagined.
    ///
    /// For example, with the current versions of GNU GCC and LLVM CLANG,
    /// the linker builds the list of nonlocal objects constructors in the
    /// order of processing objects, so by enforcing this file as the
    /// first object, we guarantee more or less that the initialisation
    /// code is executed before other constructors.

    class EarlyInitialisation
    {
    public:
      EarlyInitialisation();
    };

    /// \brief The constructor to be executed before all others.
    ///
    /// \details
    /// All hardware initialisations must be listed here, in the desired
    /// order.
    EarlyInitialisation::EarlyInitialisation()
    {
      // TODO: clock init
      os::device::Debug::earlyInitialise();
      // TODO: other inits
    }
  }
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wglobal-constructors"
#pragma GCC diagnostic ignored "-Wexit-time-destructors"

/// \brief Single static instance of the EarlyInitialisation class.
///
/// \details
/// The must be the first static object in this file, to guarantee
/// that the constructor is called before others.
static os::core::EarlyInitialisation earlyInitialisation;

// For convenience, the debug constructor is also called early
os::device::Debug debug;

#pragma GCC diagnostic pop

