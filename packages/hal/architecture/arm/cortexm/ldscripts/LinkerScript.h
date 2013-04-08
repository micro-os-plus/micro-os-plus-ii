//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_LDSCRIPT_LINKERSCRIPT_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_LDSCRIPT_LINKERSCRIPT_H_

#include "portable/core/include/ConfigDefines.h"

namespace hal
{
  namespace arch
  {
    namespace cortexm
    {

      class LinkerScript
      {
      public:

        typedef unsigned int LinkerAlign_t;

        static LinkerAlign_t*
        getBssBegin(void);

        static LinkerAlign_t*
        getBssEnd(void);

        static LinkerAlign_t*
        getFlashDataBegin(void);

        static LinkerAlign_t*
        getRamDataBegin(void);

        static LinkerAlign_t*
        getRamDataEnd(void);

        static LinkerAlign_t*
        getInitArrayStart(void);

        static LinkerAlign_t*
        getInitArrayEnd(void);

        static LinkerAlign_t*
        getFiniArrayStart(void);

        static LinkerAlign_t*
        getFiniArrayEnd(void);

      };
    }
  }
}

extern "C"
{
  extern hal::arch::cortexm::LinkerScript::LinkerAlign_t __bss_start__;
  extern hal::arch::cortexm::LinkerScript::LinkerAlign_t __bss_end__;

  extern hal::arch::cortexm::LinkerScript::LinkerAlign_t __etext;

  extern hal::arch::cortexm::LinkerScript::LinkerAlign_t __data_start__;
  extern hal::arch::cortexm::LinkerScript::LinkerAlign_t __data_end__;

  extern hal::arch::cortexm::LinkerScript::LinkerAlign_t __init_array_start;
  extern hal::arch::cortexm::LinkerScript::LinkerAlign_t __init_array_end;

  extern hal::arch::cortexm::LinkerScript::LinkerAlign_t __fini_array_start;
  extern hal::arch::cortexm::LinkerScript::LinkerAlign_t __fini_array_end;
}

namespace hal
{
  namespace arch
  {
    namespace cortexm
    {
      inline __attribute__((always_inline))   //
      LinkerScript::LinkerAlign_t*
      LinkerScript::getBssBegin(void)
      {
        return (&__bss_start__);
      }

      inline __attribute__((always_inline))   //
      LinkerScript::LinkerAlign_t*
      LinkerScript::getBssEnd(void)
      {
        return (&__bss_end__);
      }

      inline __attribute__((always_inline))   //
      LinkerScript::LinkerAlign_t*
      LinkerScript::getFlashDataBegin(void)
      {
        // the initialised data starts at the end of the text section (in flash)
        return (&__etext);
      }

      inline __attribute__((always_inline))   //
      LinkerScript::LinkerAlign_t*
      LinkerScript::getRamDataBegin(void)
      {
        return (&__data_start__);
      }

      inline __attribute__((always_inline))   //
      LinkerScript::LinkerAlign_t*
      LinkerScript::getRamDataEnd(void)
      {
        return (&__data_end__);
      }

      inline __attribute__((always_inline))   //
      LinkerScript::LinkerAlign_t*
      LinkerScript::getInitArrayStart(void)
      {
        return (&__init_array_start);
      }

      inline __attribute__((always_inline))   //
      LinkerScript::LinkerAlign_t*
      LinkerScript::getInitArrayEnd(void)
      {
        return (&__init_array_end);
      }

      inline __attribute__((always_inline))   //
      LinkerScript::LinkerAlign_t*
      LinkerScript::getFiniArrayStart(void)
      {
        return (&__fini_array_start);
      }

      inline __attribute__((always_inline))   //
      LinkerScript::LinkerAlign_t*
      LinkerScript::getFiniArrayEnd(void)
      {
        return (&__fini_array_end);
      }

    }
  }
}

#endif // HAL_ARCHITECTURE_ARM_CORTEXM_LDSCRIPT_LINKERSCRIPT_H_
