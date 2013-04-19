//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32 F4 class to access the GNU linker script definitions.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_LDSCRIPT_LINKERSCRIPT_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_LDSCRIPT_LINKERSCRIPT_H_

#include "portable/core/include/ConfigDefines.h"

#include <stdint.h>

#include "hal/architecture/arm/cortexm/ldscripts/LinkerScript.h"

//#include "portable/core/include/OS.h"

namespace hal
{
  namespace stm32f4
  {
    // ========================================================================

    typedef uint32_t interruptVector_t;

    /// \headerfile LinkerScript.h "hal/architecture/arm/cortexm/stm32f/stm32f4/ldscript/LinkerScript.h"
    /// \ingroup arm_cm
    /// \nosubgrouping
    ///
    /// \brief STM32 F4 linker script definitions.
    ///
    /// \details
    /// This class provides a kind of portable access to
    /// linker script definitions.
    class LinkerScript : public hal::cortexm::LinkerScript
    {
    public:

      /// \name Constructors/destructor
      /// @{

      /// \brief Deleted constructor.
      LinkerScript() = delete;

      /// @} end of name Constructors/destructor

    };
  // ========================================================================
  }// namespace stm32f4
} // namespace hal

#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_LDSCRIPT_LINKERSCRIPT_H_
