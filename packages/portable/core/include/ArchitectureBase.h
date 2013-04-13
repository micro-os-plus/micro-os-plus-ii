//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#ifndef OS_PORTABLE_CORE_ARCHITECTUREBASE_H_
#define OS_PORTABLE_CORE_ARCHITECTUREBASE_H_

#include "portable/core/include/ConfigDefines.h"

namespace os
{
  namespace core
  {
    // ========================================================================

    /// \headerfile ArchitectureBase.h "portable/core/include/ArchitectureBase.h"
    /// \ingroup core
    /// \nosubgrouping
    ///
    /// \brief Base for all architecture implementation classes.
    ///
    /// \details
    /// This class is used only to provide default empty functions,
    /// so that specific architecture implementations need to overwrite
    /// only functions that provide functionality.
    class ArchitectureBase
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Deleted constructor.
      ArchitectureBase() = default;

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

      /// \brief Put architecture greeting.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      static void
      putGreeting(void);

      /// @} end of Public member functions

    };

    // ------------------------------------------------------------------------

    /// \details
    /// Empty inline function, so no code is generated. Overwrite this
    /// with actual architecture specific system initialisation code.
    inline __attribute__((always_inline))
    void
    ArchitectureBase::initialiseSystem(void)
    {
    }

    /// \details
    /// Empty inline function, so no code is generated. Overwrite this
    /// with actual architecture specific system reset code.
    inline __attribute__((always_inline))
    void
    ArchitectureBase::resetSystem(void)
    {
    }

    /// \details
    /// Empty inline function, so no code is generated. Overwrite this
    /// with actual architecture specific code.
    inline __attribute__((always_inline))
    void
    ArchitectureBase::putGreeting(void)
    {
    }

    // ========================================================================

  }// namespace core
} // namespace os

#endif // OS_PORTABLE_CORE_ARCHITECTUREBASE_H_
