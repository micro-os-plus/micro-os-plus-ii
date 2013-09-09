//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Cortex-M semihosting declarations.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_DIAGNOSTICS_SEMIHOSTING_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_DIAGNOSTICS_SEMIHOSTING_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_DIAGNOSTICS_SEMIHOSTING) || defined(__DOXYGEN__)

#include <unistd.h>

namespace hal
{
  namespace cortexm
  {
    namespace diag
    {

      // ======================================================================

      /// \headerfile SemiHosting.h "hal/architecture/arm/cortexm/diagnostics/include/SemiHosting.h"
      /// \ingroup cm3_diag
      /// \nosubgrouping
      ///
      /// \brief The standard semihosting interface.
      ///
      /// \details
      /// This class defines
      /// the semihosting interface, as specified in
      ///  ARM Compiler toolchain Version 5.03 - Developing Software for ARM Processors
      ///  DUI 0471I, Chapter 8 - Semihosting
      class SemiHosting
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

        /// \brief SYS_WRITE0 Write a string to the debug channel.
        ///
        /// \param pString         Pointer to null terminated string.
        /// \par Returns
        ///    Nothing.
        static void
        writeString(const char* pString);

        // qemu specifics

        /// \brief SYS_WRITEC Write a character to the debug channel.
        ///
        /// \param ch         Character to write.
        /// \par Returns
        ///    Nothing.
        static void
        writeChar(char ch);

        /// @} end of Public member functions

      protected:
        /// \name Protected member functions
        /// @{

        static int
        BKPT(int op, void* p1, void* p2);

        /// @} end of Protected member functions

      };

      /// \details
      /// Write a character byte, to the debug channel.
      /// When executed under an ARM
      /// debugger, the character appears on the host debugger console.
      inline void
      __attribute__((always_inline))
      SemiHosting::writeChar(char ch)
      {
        // Pass the address of the character
        BKPT(0x03, (void*) &ch, (void*) 0);
      }

      /// \details
      /// Write a null-terminated string to the debug channel.
      /// When executed under an ARM debugger,
      /// the characters appear on the host debugger console.
      inline void
      __attribute__((always_inline))
      SemiHosting::writeString(const char* pString)
      {
        BKPT(0x04, (void*) pString, (void*) 0);
      }

    // ========================================================================

    }// namespace diag
  } // namespace cortexm
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_DIAGNOSTICS_SEMIHOSTING)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_DIAGNOSTICS_SEMIHOSTING_H_
