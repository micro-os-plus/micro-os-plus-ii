//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Cortex-M memory map.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_MEMORYMAP_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_MEMORYMAP_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/include/ArchitectureDefinitions.h"

namespace hal
{
  namespace cortexm
  {
    // ------------------------------------------------------------------------

    /// \ingroup arm_cm
    /// \headerfile MemoryMap.h "hal/architecture/arm/cortexm/include/MemoryMap.h"
    /// \nosubgrouping
    ///
    /// \brief Cortex-M memory map.

    class MemoryMap
    {
    public:

      /// ITM (Instrumentation Trace Macrocell) Base Address
      static const hal::cortexm::address_t ITM_BASE_ADDRESS =
          0xE0000000UL;

      /// DWT (Data Watchpoint and Trace) Base Address
      static const hal::cortexm::address_t DWT_BASE_ADDRESS =
          0xE0001000UL;

      /// SCS (System Control Space) Base Address
      static const hal::cortexm::address_t SCS_BASE_ADDRESS =
          0xE000E000UL;

      /// SysTick Base Address
      static const hal::cortexm::address_t SysTick_BASE_ADDRESS =
          (SCS_BASE_ADDRESS+0x0010UL);

      /// NVIC (Nested Vectored Interrupt Controller) Base Address
      static const hal::cortexm::address_t NVIC_BASE_ADDRESS =
          (SCS_BASE_ADDRESS+0x0100UL);

      /// SCB (System Control Block) Base Address
      static const hal::cortexm::address_t SCB_BASE_ADDRESS =
          (SCS_BASE_ADDRESS+0x0D00UL);

#if (OS_BOOL_HAL_ARCHITECTURE_ARM_CORTEX_M_HAS_MPU)
      /// MPU (Memory Protection Unit) Base Address
      static const hal::cortexm::address_t MPU_BASE_ADDRESS =
          (SCS_BASE_ADDRESS+0x0D90UL);
#endif

      /// Core Debug Base Address
      static const hal::cortexm::address_t CoreDebug_BASE_ADDRESS =
          (SCS_BASE_ADDRESS+0x0DF0UL);

#if (OS_BOOL_HAL_ARCHITECTURE_ARM_CORTEX_M_HAS_FPU)
      /// FPU (Floating Point Unit) Base Address
      static const hal::cortexm::address_t MPU_BASE_ADDRESS =
          (SCS_BASE_ADDRESS+0x0D90UL);
#endif

      /// TPI (Trace Port Interface) Base Address
      static const hal::cortexm::address_t TPI_BASE_ADDRESS =
          0xE0040000UL;

    };

  } // namespace cortexm

// --------------------------------------------------------------------------
}

#endif // OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_MEMORYMAP_H_
