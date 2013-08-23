//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Cortex-M semihosting definitions.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_DIAGNOSTICS_SEMIHOSTING) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/diagnostics/include/SemiHosting.h"

namespace hal
{
  namespace cortexm
  {
    namespace diag
    {

      // ======================================================================
      int
      SemiHosting::BKPT(int op, void* p1, void* p2)
      {
        register int r0 asm("r0");
        register int r1 asm("r1") __attribute__((unused));
        register int r2 asm("r2") __attribute__((unused));

        r0 = op;
        r1 = (int) p1;
        r2 = (int) p2;

        asm volatile(""
            " bkpt 0xAB \n"
            : "=r"(r0)
            :
            :
        );
        return r0;
      }

    // ========================================================================

    }// namespace diag
  } // namespace cortexm
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_DIAGNOSTICS_SEMIHOSTING)
