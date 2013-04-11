//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

//#include "portable/core/include/OS.h"

#include "portable/core/include/Platform.h"

#include "../include/ArchitectureImplementation.h"

#include "portable/infrastructure/include/CStartup.h"

#include "../ldscripts/LinkerScript.h"

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
      void
      Reset(void)
      {
        CStartup::initialiseDataAndBss();

        os::platform.initialiseSystem();

        CStartup::callStaticConstructors();

#if defined(DEBUG)
        if (constantMarker != CONSTANT_MARKER_MAGIC)
          {
            os::diag::trace.putString("copyInitialisedData() failed");
            os::diag::trace.putNewLine();
          }
#endif

        main();

        CStartup::callStaticDestructors();

#if defined(DEBUG)
        os::diag::trace.putString("looping after main()");
        os::diag::trace.putNewLine();

        for (;;)
          ;
#else
        os::platform.resetSystem();
#endif
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
