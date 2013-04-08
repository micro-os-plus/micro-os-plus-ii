//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

//#include "portable/core/include/OS.h"

#include "../include/ArchitectureImplementation.h"

#include "portable/infrastructure/include/CStartup.h"

#include "../ldscripts/LinkerScript.h"

#include "portable/language/cpp/include/iterator.h"

namespace hal
{
  namespace arch
  {
    namespace cortexm
    {
      // ----------------------------------------------------------------------

#if defined(DEBUG)
      void
      ArchitectureImplementation::putGreeting(void)
      {
        os::diag::trace.putString("ARM Cortex M");
        os::diag::trace.putNewLine();
      }
#endif

    // ------------------------------------------------------------------------
    }
  }
}


typedef hal::arch::cortexm::LinkerScript::LinkerAlign_t LinkerAlign_t;
typedef hal::arch::cortexm::LinkerScript LinkerScript_t;

template class os::infra::CStartup<LinkerScript_t>;
typedef os::infra::CStartup<LinkerScript_t> CStartup_t;

#if defined(DEBUG)
typedef unsigned int ConstantMarker_t;

static const ConstantMarker_t CONSTANT_MARKER_MAGIC = 0x12345678;
static volatile ConstantMarker_t constantMarker = CONSTANT_MARKER_MAGIC;
#endif

extern "C"
{
  int
  main(void);

  void
  Reset_Handler(void);
}

void
Reset_Handler(void)
{

  CStartup_t::initialiseAndCallStaticConstructors();

#if defined(DEBUG)
  if (constantMarker != CONSTANT_MARKER_MAGIC)
    {
      os::diag::trace.putString("copyInitialisedData() failed");
      os::diag::trace.putNewLine();
    }
#endif

  main();

  CStartup_t::callStaticDestructors();

  // TODO: soft reset to restart
  for (;;)
    ;
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
    return 0;
  }

  void
  __cxa_pure_virtual(void)
  {
  }
}

void
operator
delete(void* p __attribute__((unused)))
{
}
// ----------------------------------------------------------------------------

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
