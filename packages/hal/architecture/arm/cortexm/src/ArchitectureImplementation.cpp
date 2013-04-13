//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

//#include "portable/core/include/OS.h"

#include "portable/core/include/Platform.h"

#include "hal/architecture/arm/cortexm/include/ArchitectureImplementation.h"

#include "portable/infrastructure/include/CStartup.h"

#include "hal/architecture/arm/cortexm/ldscripts/LinkerScript.h"

#include "portable/language/cpp/include/iterator.h"

namespace hal
{
  namespace cortexm
  {
    // ------------------------------------------------------------------------

#if defined(DEBUG)
    void
    ArchitectureImplementation::putGreeting(void)
    {
      os::diag::trace.putString("ARM Cortex M");
      os::diag::trace.putNewLine();
    }
#endif

  // --------------------------------------------------------------------------
  }
}

typedef hal::cortexm::LinkerScript LinkerScript;
template class os::infra::TCStartup<LinkerScript>;

extern int
main(void);

namespace hal
{
  namespace cortexm
  {
// ------------------------------------------------------------------------

    typedef os::infra::TCStartup<LinkerScript> CStartup;

#if defined(DEBUG)
    typedef unsigned int constantMarker_t;

    static const constantMarker_t CONSTANT_MARKER_MAGIC = 0x12345678;
    static volatile constantMarker_t constantMarker = CONSTANT_MARKER_MAGIC;
#endif

    namespace InterruptHandler
    {

      /// \ingroup arm_cm3_irq
      /// \details
      /// All ARM Cortex-M architectures jump to this the entry point
      /// via the pointer located in the second word of the interrupt
      /// table for reset events.
      ///
      /// This function starts with the reset settings, i.e. low speed and
      /// peripherals disabled, and will later initialise the
      /// hardware for a higher frequency.
      void
      Reset(void)
      {
        CStartup::initialiseDataAndBss();

        // The os::platform::initialiseSystem() will be called
        // by the first constructor (EarlyInitialisations())
        CStartup::callStaticConstructors();

#if defined(DEBUG)
        // Trace is available only after first constructors are called,
        // do not move this from here.
        if (constantMarker != CONSTANT_MARKER_MAGIC)
          {
            os::diag::trace.putString("copyInitialisedData() failed");
            os::diag::trace.putNewLine();
          }
#endif

        // Everything should be ready, the show can start
        main();

        // Not usual in embedded environments, but if the application
        // terminates gracefully, run the destructors.
        // The last destructor (~EarlyInitialisations()) should
        // call os::platform::resetSystem().
        CStartup::callStaticDestructors();

#if defined(DEBUG)

        // normally should not reach this
        os::diag::trace.putString("looping after main()");
        os::diag::trace.putNewLine();

#endif
        for (;;)
          ;
      }
    }

  // ------------------------------------------------------------------------
  }
}

// ----------------------------------------------------------------------------
// Patches to make the code compile.
// Probably will be further refined.

extern "C"
{
  void*
  _sbrk();

  void
  __cxa_pure_virtual(void);

  void*
  _sbrk()
  {
    // not yet implemented
    // TODO: allocate space on heap
    return 0;
  }

  void
  __cxa_pure_virtual(void)
  {
    // not yet implemented
    // TODO: trace message and restart
  }
}

void
operator
delete(void* p __attribute__((unused)))
{
  // not yet implemented
}

// ----------------------------------------------------------------------------

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
