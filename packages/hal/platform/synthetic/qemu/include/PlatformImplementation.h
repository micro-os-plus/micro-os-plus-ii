//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief QEMU declarations for the platform implementation.

#ifndef HAL_PATFORM_SYNTHETIC_QEMU_PLATFORMIMPLEMENTATION_H_
#define HAL_PATFORM_SYNTHETIC_QEMU_PLATFORMIMPLEMENTATION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_PLATFORM_SYNTHETIC_QEMU) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/include/PlatformBase.h"
#include "hal/architecture/arm/cortexm/qemu/diagnostics/include/SemiHosting.h"

namespace hal
{
  namespace qemu
  {
    // ========================================================================

    /// \headerfile PlatformImplementation.h "hal/platform/synthetic/qemu/include/PlatformImplementation.h"
    /// \ingroup qemu
    /// \nosubgrouping
    ///
    /// \brief QEMU platform implementation classes.
    ///
    /// \details
    /// The QEMU environment is slightly richer than bare metal platforms,
    /// and for testability these extra features may be useful. For
    /// example we can pass back to the operating system a status code
    /// to tell if the test passed.
    class PlatformImplementation : public hal::cortexm::PlatformBase
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Constructor.
      PlatformImplementation(void);

      // \brief Destructor
      ~PlatformImplementation(void);

      /// @} end of name Constructors/destructor

      /// \name Public member functions
      /// @{

      /// \brief Execute the main() function.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      executeMain(void);

      /// \brief Pass the main() return code to the calling environment.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      exit(void);

      /// @} end of Public member functions

    private:

      int m_returnCode;
    };

    inline
    __attribute__((always_inline))
    PlatformImplementation::PlatformImplementation(void)
    {
#if defined(DEBUG)
      os::diag::trace.putConstructor();
#endif
      m_returnCode = 0;
    }

    inline
    __attribute__((always_inline))
    PlatformImplementation::~PlatformImplementation()
    {
#if defined(DEBUG)
      os::diag::trace.putDestructor();
#endif
    }

    /// \details
    /// Call the application main() function and store the
    /// return code for later exit() usage.
    inline void
    __attribute__((always_inline))
    PlatformImplementation::executeMain(void)
    {
#if false && defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_DIAGNOSTICS_SEMIHOSTING)

      diag::SemiHosting::CommandLineBlock commandLineBlock;
      char commandLine[100];

      commandLineBlock.pCommandLine = commandLine;
      commandLineBlock.size = sizeof(commandLine);

      int ret = diag::SemiHosting::getCommandLine(&commandLineBlock);
      if (ret == 0)
        {
#if defined(DEBUG)
          os::diag::trace.putString("command line=\"");
          os::diag::trace.putString(commandLineBlock.pCommandLine);
          os::diag::trace.putString("\", length=");
          os::diag::trace.putDec(commandLineBlock.size);
          os::diag::trace.putNewLine();
#endif // defined(DEBUG)
        }
      else
        {
#if defined(DEBUG)
          os::diag::trace.putString("getCommandLine() failed");
          os::diag::trace.putNewLine();
#endif // defined(DEBUG)
        }

#if defined(DEBUG)
          os::diag::trace.putString("seconds=");
          os::diag::trace.putDec(diag::SemiHosting::getTimeSeconds());
          os::diag::trace.putNewLine();
#endif // defined(DEBUG)

#if defined(DEBUG)
          os::diag::trace.putString("centiseconds=");
          os::diag::trace.putDec(diag::SemiHosting::getTimeCentiseconds());
          os::diag::trace.putNewLine();
#endif // defined(DEBUG)

#if defined(DEBUG)
          os::diag::trace.putString("ticks=");
          os::diag::trace.putDec(diag::SemiHosting::getTickFrequency());
          os::diag::trace.putNewLine();
#endif // defined(DEBUG)
#endif

      m_returnCode = main(0, &"");
    }

    /// \details
    /// Pass the return code to the semi-hosting exit() function,
    /// to tell the operating system if this test was successful or not.
    inline void
    __attribute__((always_inline))
    __attribute__((noreturn))
    PlatformImplementation::exit(void)
    {
#if defined(DEBUG) && defined(OS_DEBUG_PLATFORMIMPLEMENTATION)
      // Although tracing is no longer available here,
      // we can use the semi-hosting functions.
      hal::qemu::diag::SemiHosting::writeString(__PRETTY_FUNCTION__);
      hal::qemu::diag::SemiHosting::writeString("\n");
#endif // define(DEBUG)
      hal::qemu::diag::SemiHosting::writeString("\n");
      hal::qemu::diag::SemiHosting::exit(m_returnCode);
    }

  // ==========================================================================

  }// namespace qemu
} // namespace hal

// ----------------------------------------------------------------------------
#if !defined(__DOXYGEN__)
namespace hal
{
  namespace platform
  {
    using PlatformImplementation = hal::qemu::PlatformImplementation;
  } // namespace platform
} // namespace hal
#endif // !defined(__DOXYGEN__)
// ----------------------------------------------------------------------------

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
#endif // HAL_PATFORM_SYNTHETIC_QEMU_PLATFORMIMPLEMENTATION_H_
