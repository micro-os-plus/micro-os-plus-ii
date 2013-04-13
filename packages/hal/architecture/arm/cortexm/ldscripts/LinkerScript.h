//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_LDSCRIPT_LINKERSCRIPT_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_LDSCRIPT_LINKERSCRIPT_H_

#include "portable/core/include/ConfigDefines.h"

#include "portable/core/include/OS.h"

namespace hal
{
  namespace cortexm
  {
    // ========================================================================

    typedef uint32_t interruptVector_t;

    /// \headerfile LinkerScript.h "hal/architecture/arm/cortexm/ldscript/LinkerScript.h"
    /// \ingroup arm_cm
    /// \nosubgrouping
    ///
    /// \brief Cortex-M linker script definitions.
    ///
    /// \details
    /// This class provides a kind of portable access to
    /// linker script definitions.
    class LinkerScript
    {
    public:

      typedef unsigned int linkerAlign_t;

      /// \name Constructors/destructor
      /// @{

      /// \brief Deleted constructor.
      LinkerScript() = delete;

      /// @} end of name Constructors/destructor

      /// \name Public member functions
      /// @{

      /// \brief Get BSS begin address in RAM.
      ///
      /// \par Parameters
      ///    None.
      /// \return Pointer to RAM.
      static linkerAlign_t*
      getBssBegin(void);

      /// \brief Get BSS end address in RAM.
      ///
      /// \par Parameters
      ///    None.
      /// \return Pointer to RAM.
      static linkerAlign_t*
      getBssEnd(void);

      /// \brief Get initialised data begin address in flash.
      ///
      /// \par Parameters
      ///    None.
      /// \return Pointer to flash.
      static linkerAlign_t*
      getFlashDataBegin(void);

      /// \brief Get initialised data begin address in ram.
      ///
      /// \par Parameters
      ///    None.
      /// \return Pointer to ram.
      static linkerAlign_t*
      getRamDataBegin(void);

      /// \brief Get initialised data end address in ram.
      ///
      /// \par Parameters
      ///    None.
      /// \return Pointer to ram.
      static linkerAlign_t*
      getRamDataEnd(void);

      /// \brief Get init array begin address in flash.
      ///
      /// \par Parameters
      ///    None.
      /// \return Pointer to flash.
      static linkerAlign_t*
      getInitArrayBegin(void);

      /// \brief Get init array end address in flash.
      ///
      /// \par Parameters
      ///    None.
      /// \return Pointer to flash.
      static linkerAlign_t*
      getInitArrayEnd(void);

      /// \brief Get fini array begin address in flash.
      ///
      /// \par Parameters
      ///    None.
      /// \return Pointer to flash.
      static linkerAlign_t*
      getFiniArrayBegin(void);

      /// \brief Get fini array end address in flash.
      ///
      /// \par Parameters
      ///    None.
      /// \return Pointer to flash.
      static linkerAlign_t*
      getFiniArrayEnd(void);

      /// @} end of name Public member functions

    };
  // ========================================================================
  }// namespace cortexm
} // namespace hal

extern "C"
{
  // local type to shorten definitions.
  typedef hal::cortexm::LinkerScript::linkerAlign_t linkerAlign_t;

  // External references to actual symbols defined in the linker script.

  extern linkerAlign_t __bss_start__;
  extern linkerAlign_t __bss_end__;

  extern linkerAlign_t __etext;

  extern linkerAlign_t __data_start__;
  extern linkerAlign_t __data_end__;

  extern linkerAlign_t __init_array_start;
  extern linkerAlign_t __init_array_end;

  extern linkerAlign_t __fini_array_start;
  extern linkerAlign_t __fini_array_end;

  extern linkerAlign_t __stack;

}

namespace hal
{
  namespace cortexm
  {
    inline __attribute__((always_inline))      //
    LinkerScript::linkerAlign_t*
    LinkerScript::getBssBegin(void)
    {
      return (&__bss_start__);
    }

    inline __attribute__((always_inline))      //
    LinkerScript::linkerAlign_t*
    LinkerScript::getBssEnd(void)
    {
      return (&__bss_end__);
    }

    inline __attribute__((always_inline))      //
    LinkerScript::linkerAlign_t*
    LinkerScript::getFlashDataBegin(void)
    {
      // the initialised data starts at the end of the text section (in flash)
      return (&__etext);
    }

    inline __attribute__((always_inline))      //
    LinkerScript::linkerAlign_t*
    LinkerScript::getRamDataBegin(void)
    {
      return (&__data_start__);
    }

    inline __attribute__((always_inline))      //
    LinkerScript::linkerAlign_t*
    LinkerScript::getRamDataEnd(void)
    {
      return (&__data_end__);
    }

    inline __attribute__((always_inline))      //
    LinkerScript::linkerAlign_t*
    LinkerScript::getInitArrayBegin(void)
    {
      return (&__init_array_start);
    }

    inline __attribute__((always_inline))      //
    LinkerScript::linkerAlign_t*
    LinkerScript::getInitArrayEnd(void)
    {
      return (&__init_array_end);
    }

    inline __attribute__((always_inline))      //
    LinkerScript::linkerAlign_t*
    LinkerScript::getFiniArrayBegin(void)
    {
      return (&__fini_array_start);
    }

    inline __attribute__((always_inline))      //
    LinkerScript::linkerAlign_t*
    LinkerScript::getFiniArrayEnd(void)
    {
      return (&__fini_array_end);
    }

  } // namespace cortexm
} // namespace hal

#endif // HAL_ARCHITECTURE_ARM_CORTEXM_LDSCRIPT_LINKERSCRIPT_H_
