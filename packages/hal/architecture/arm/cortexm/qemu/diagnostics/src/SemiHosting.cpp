//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief QEMU Cortex-M semihosting definitions.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_QEMU_DIAGNOSTICS_SEMIHOSTING) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/qemu/diagnostics/include/SemiHosting.h"

namespace hal
{
  namespace qemu
  {
    namespace diag
    {
      // ======================================================================

      /// \details
      /// Emulate the POSIX exit() code.
      /// This is not exactly standard, but it uses
      void
      SemiHosting::exit(int code)
      {
        if (code == 0)
          {
            // ADP_Stopped_ApplicationExit
            // (qemu ignores this value)
            BKPT(0x18, (void*) 0x20026, (void*) 0);
          }
        else
          {
            // Generate an unsupported call, to force qemu to quit.
            BKPT(0xF0 + code, (void*) 0, (void*) 0);
          }
        for (;;)
          ;
      }

    // ========================================================================

    }// namespace diag
  } // namespace qemu
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_QEMU_DIAGNOSTICS_SEMIHOSTING)
