//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_LDSCRIPT_LINKERSCRIPT_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_LDSCRIPT_LINKERSCRIPT_H_

#include "portable/core/include/ConfigDefines.h"

namespace hal
{
  namespace cortexm
  {

    typedef uint32_t interruptVector_t;

    class LinkerScript
    {
    public:

      typedef unsigned int linkerAlign_t;

      /// \brief Deleted constructor
      LinkerScript() = delete;

      static linkerAlign_t*
      getBssBegin(void);

      static linkerAlign_t*
      getBssEnd(void);

      static linkerAlign_t*
      getFlashDataBegin(void);

      static linkerAlign_t*
      getRamDataBegin(void);

      static linkerAlign_t*
      getRamDataEnd(void);

      static linkerAlign_t*
      getInitArrayStart(void);

      static linkerAlign_t*
      getInitArrayEnd(void);

      static linkerAlign_t*
      getFiniArrayStart(void);

      static linkerAlign_t*
      getFiniArrayEnd(void);

    };
  }
}

extern "C"
{
  typedef hal::cortexm::LinkerScript::linkerAlign_t linkerAlign_t;

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
    inline __attribute__((always_inline))     //
    LinkerScript::linkerAlign_t*
    LinkerScript::getBssBegin(void)
    {
      return (&__bss_start__);
    }

    inline __attribute__((always_inline))     //
    LinkerScript::linkerAlign_t*
    LinkerScript::getBssEnd(void)
    {
      return (&__bss_end__);
    }

    inline __attribute__((always_inline))     //
    LinkerScript::linkerAlign_t*
    LinkerScript::getFlashDataBegin(void)
    {
      // the initialised data starts at the end of the text section (in flash)
      return (&__etext);
    }

    inline __attribute__((always_inline))     //
    LinkerScript::linkerAlign_t*
    LinkerScript::getRamDataBegin(void)
    {
      return (&__data_start__);
    }

    inline __attribute__((always_inline))     //
    LinkerScript::linkerAlign_t*
    LinkerScript::getRamDataEnd(void)
    {
      return (&__data_end__);
    }

    inline __attribute__((always_inline))     //
    LinkerScript::linkerAlign_t*
    LinkerScript::getInitArrayStart(void)
    {
      return (&__init_array_start);
    }

    inline __attribute__((always_inline))     //
    LinkerScript::linkerAlign_t*
    LinkerScript::getInitArrayEnd(void)
    {
      return (&__init_array_end);
    }

    inline __attribute__((always_inline))     //
    LinkerScript::linkerAlign_t*
    LinkerScript::getFiniArrayStart(void)
    {
      return (&__fini_array_start);
    }

    inline __attribute__((always_inline))     //
    LinkerScript::linkerAlign_t*
    LinkerScript::getFiniArrayEnd(void)
    {
      return (&__fini_array_end);
    }

  }
}

#endif // HAL_ARCHITECTURE_ARM_CORTEXM_LDSCRIPT_LINKERSCRIPT_H_
