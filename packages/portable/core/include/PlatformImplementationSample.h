//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Sample of a platform implementation class.

#ifndef HAL_PLATFORM_XXXXX_PLATFORMIMPLEMENTATION_H_
#define HAL_PLATFORM_XXXXX_PLATFORMIMPLEMENTATION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_BOARD_XXXXX) || defined(__DOXYGEN__)

#include "portable/core/include/PlatformBase.h"

namespace hal
{
  namespace platform
  {
    namespace xxxxx
    {
      // ======================================================================

      /// \headerfile PlatformImplementationSample.h "portable/core/include/PlatformImplementationSample.h"
      /// \ingroup core
      /// \nosubgrouping
      ///
      /// \brief Sample for all platform implementation classes.
      class PlatformImplementation : public os::core::PlatformBase
      {
      public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Deleted constructor.
        PlatformImplementation(void) = default;

      /// @} end of name Constructors/destructor

        /// \name Public member functions
        /// @{

        /// \brief Initialise the hardware.
        ///
        /// \par Parameters
        ///    None.
        /// \par Returns
        ///    Nothing.
        static void
        initialiseSystem(void);

        /// \brief Software reset the processor.
        ///
        /// \par Parameters
        ///    None.
        /// \par Returns
        ///    Nothing.
        static void
        resetSystem(void);

        /// @} end of Public member functions
      };
    }

    // ------------------------------------------------------------------------

    /// Overwrite only if default architecture is not enough.
    inline void
    __attribute__((always_inline))
    PlatformImplementation::initialiseSystem(void)
    {
    }

    /// Overwrite only if default architecture is not enough.
    inline void
    __attribute__((always_inline))
    PlatformImplementation::resetSystem(void)
    {
    }

#if !defined(__DOXYGEN__)

    using PlatformImplementation = xxxx::PlatformImplementation;

#endif // !defined(__DOXYGEN__)

    // ========================================================================

  }
}

#endif // defined(OS_INCLUDE_HAL_BOARD_XXXXX)

#endif // HAL_PLATFORM_XXXXX_PLATFORMIMPLEMENTATION_H_
