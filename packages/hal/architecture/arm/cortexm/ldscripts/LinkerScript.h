//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_LDSCRIPTS_LINKERSCRIPT_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_LDSCRIPTS_LINKERSCRIPT_H_

#include "portable/core/include/ConfigDefines.h"



namespace hal
{
  namespace arch
  {
    namespace cortexm
    {

      template<typename TLinkAlign_T>
        class LinkerScript
        {
        public:

          typedef TLinkAlign_T LinkAlign_t;

          static LinkAlign_t*
          getBssBegin(void);

          static LinkAlign_t*
          getBssEnd(void);

          static LinkAlign_t*
          getFlashDataBegin(void);

          static LinkAlign_t*
          getRamDataBegin(void);

          static LinkAlign_t*
          getRamDataEnd(void);

          static LinkAlign_t*
          getInitArrayStart(void);

          static LinkAlign_t*
          getInitArrayEnd(void);

          static LinkAlign_t*
          getFiniArrayStart(void);

          static LinkAlign_t*
          getFiniArrayEnd(void);

        };
    }
  }
}

extern "C"
{
  extern int __bss_start__;
  extern int __bss_end__;
  extern int __etext;
  extern int __data_start__;
  extern int __data_end__;
  extern int __init_array_start;
  extern int __init_array_end;
  extern int __fini_array_start;
  extern int __fini_array_end;
}

namespace hal
{
  namespace arch
  {
    namespace cortexm
    {
      template<typename TLinkAlign_T>
        inline __attribute__((always_inline))         //
        typename LinkerScript<TLinkAlign_T>::LinkAlign_t*
        LinkerScript<TLinkAlign_T>::getBssBegin(void)
        {
          return reinterpret_cast<LinkAlign_t*>(&__bss_start__);
        }

      template<typename TLinkAlign_T>
        inline __attribute__((always_inline))         //
        typename LinkerScript<TLinkAlign_T>::LinkAlign_t*
        LinkerScript<TLinkAlign_T>::getBssEnd(void)
        {
          return reinterpret_cast<LinkAlign_t*>(&__bss_end__);
        }

      template<typename TLinkAlign_T>
        inline __attribute__((always_inline))         //
        typename LinkerScript<TLinkAlign_T>::LinkAlign_t*
        LinkerScript<TLinkAlign_T>::getFlashDataBegin(void)
        {
          // the initialised data starts at the end of the text section (in flash)
          return reinterpret_cast<LinkAlign_t*>(&__etext);
        }

      template<typename TLinkAlign_T>
        inline __attribute__((always_inline))         //
        typename LinkerScript<TLinkAlign_T>::LinkAlign_t*
        LinkerScript<TLinkAlign_T>::getRamDataBegin(void)
        {
          return reinterpret_cast<LinkAlign_t*>(&__data_start__);
        }

      template<typename TLinkAlign_T>
        inline __attribute__((always_inline))         //
        typename LinkerScript<TLinkAlign_T>::LinkAlign_t*
        LinkerScript<TLinkAlign_T>::getRamDataEnd(void)
        {
          return reinterpret_cast<LinkAlign_t*>(&__data_end__);
        }

      template<typename TLinkAlign_T>
        inline __attribute__((always_inline))         //
        typename LinkerScript<TLinkAlign_T>::LinkAlign_t*
        LinkerScript<TLinkAlign_T>::getInitArrayStart(void)
        {
          return reinterpret_cast<LinkAlign_t*>(&__init_array_start);
        }

      template<typename TLinkAlign_T>
        inline __attribute__((always_inline))         //
        typename LinkerScript<TLinkAlign_T>::LinkAlign_t*
        LinkerScript<TLinkAlign_T>::getInitArrayEnd(void)
        {
          return reinterpret_cast<LinkAlign_t*>(&__init_array_end);
        }

      template<typename TLinkAlign_T>
        inline __attribute__((always_inline))         //
        typename LinkerScript<TLinkAlign_T>::LinkAlign_t*
        LinkerScript<TLinkAlign_T>::getFiniArrayStart(void)
        {
          return reinterpret_cast<LinkAlign_t*>(&__fini_array_start);
        }

      template<typename TLinkAlign_T>
        inline __attribute__((always_inline))         //
        typename LinkerScript<TLinkAlign_T>::LinkAlign_t*
        LinkerScript<TLinkAlign_T>::getFiniArrayEnd(void)
        {
          return reinterpret_cast<LinkAlign_t*>(&__fini_array_end);
        }

    }
  }
}

#endif // HAL_ARCHITECTURE_ARM_CORTEXM_LDSCRIPTS_LINKERSCRIPT_H_
