//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM) || defined(__DOXYGEN__)

//#include "portable/core/include/OS.h"

#include "../include/ArchitectureImplementation.h"

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

    }
  }
}


extern "C"
{

  int
  main(void);

  void
  _start()
  {
    main();
  }

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

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM)
