//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief QEMU Cortex-M semihosting declarations.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_QEMU_DIAGNOSTICS_SEMIHOSTING_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_QEMU_DIAGNOSTICS_SEMIHOSTING_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_QEMU_DIAGNOSTICS_SEMIHOSTING) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/diagnostics/include/SemiHosting.h"

#include <unistd.h>

namespace hal
{
  namespace qemu
  {
    namespace diag
    {
      // ======================================================================

      /// \headerfile SemiHosting.h "hal/architecture/arm/cortexm/qemu/diagnostics/include/SemiHosting.h"
      /// \ingroup qemu_diag
      /// \nosubgrouping
      ///
      /// \brief The semihosting interface as implemented by QEMU.
      ///
      /// \details
      /// This class implements a slightly modified version of
      /// the API, as supported by QEMU.
      class SemiHosting : public cortexm::diag::SemiHosting
      {
      public:

        /// \name Constructors/destructor
        /// @{

        /// \brief Default constructor.
        SemiHosting(void) = default;

        /// \brief Default destructor.
        ~SemiHosting(void) = default;

        /// @} end of name Constructors/destructor

        /// \name Public member functions
        /// @{

        /// \brief Exit process.
        ///
        /// \param code         Return code.
        /// \par Returns
        ///    Nothing.
        static void
        __attribute__((noreturn))
        exit(int code);

        // Not supported on QEMU
        static unsigned int
        getTickFrequency(void);

        /// @} end of Public member functions

      };

      inline unsigned int
      __attribute__((always_inline))
      SemiHosting::getTickFrequency(void)
      {
        return -1;
      }


    // ========================================================================

    }// namespace diag
  } // namespace qemu
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_QEMU_DIAGNOSTICS_SEMIHOSTING)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_QEMU_DIAGNOSTICS_SEMIHOSTING_H_
