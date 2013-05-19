//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Cortex-M default interrupt handler.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

#include "portable/core/include/OS.h"

#include "portable/core/include/Platform.h"

namespace hal
{
  namespace cortexm
  {
    namespace InterruptHandler
    {
      /// \ingroup arm_cm_irq
      /// \name Interrupt handlers
      /// \brief Default interrupt handler.
      ///
      /// \details
      /// All undefined interrupt handlers are routed to this function,
      /// via weak references.
      void
      Default(void)
      {
#if defined(DEBUG)

        os::diag::trace.putNewLine();
        os::diag::trace.putString(__PRETTY_FUNCTION__);
        os::diag::trace.putNewLine();

        for (;;)
        ;
#else
        // soft reset
        os::platform.resetSystem();
#endif
      }

    } // namespace InterruptHandler
  } // namespace cortexm
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
