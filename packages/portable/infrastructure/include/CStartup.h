//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#ifndef OS_PORTABLE_INFRASTRUCTURE_CSTARTUP_H_
#define OS_PORTABLE_INFRASTRUCTURE_CSTARTUP_H_

//#include "portable/core/include/ConfigDefines.h"

namespace os
{
  namespace infra
  {
    template<class TLinkerScript_T,
        typename TLinkerAlign_T = typename TLinkerScript_T::LinkerAlign_t>
      class CStartup
      {
      public:

        typedef TLinkerScript_T LinkerScript_t;
        typedef TLinkerAlign_T LinkerAlign_t;

        static void
        copyInitialisedData(LinkerAlign_t* fromBegin, LinkerAlign_t* toBegin,
            LinkerAlign_t* toEnd);

        static void
        clearBss(LinkerAlign_t* bssBegin, LinkerAlign_t* bssEnd);

        static void
        callStaticInitialisers(LinkerAlign_t* arrayBegin,
            LinkerAlign_t* arrayEnd);

        static void
        initialiseAndCallStaticConstructors(void);

        static void
        callStaticDestructors(void);

      };

    template<class TLinkerScript_T, typename TLinkerAlign_T>
      inline __attribute__((always_inline))
      void
      CStartup<TLinkerScript_T, TLinkerAlign_T>::copyInitialisedData(
          LinkerAlign_t* fromBegin, LinkerAlign_t* toBegin,
          LinkerAlign_t* toEnd)
      {
        // Copy the data segment initialisers from flash to RAM
        LinkerAlign_t* pSrc = fromBegin;
        LinkerAlign_t* pDest = toBegin;
        for (; pDest < toEnd;)
          {
            *(pDest++) = *(pSrc++);
          }
      }

    template<class TLinkerScript_T, typename TLinkerAlign_T>
      inline __attribute__((always_inline))
      void
      CStartup<TLinkerScript_T, TLinkerAlign_T>::clearBss(
          LinkerAlign_t* bssBegin, LinkerAlign_t* bssEnd)
      {
        // Zero fill the bss segment.
        LinkerAlign_t* pDest = bssBegin;
        for (; pDest < bssEnd;)
          {
            *(pDest++) = 0;
          }
      }

    template<class TLinkerScript_T, typename TLinkerAlign_T>
      void
      CStartup<TLinkerScript_T, TLinkerAlign_T>::callStaticInitialisers(
          LinkerAlign_t* arrayBegin, LinkerAlign_t* arrayEnd)
      {
        typedef void
        (*pFunc_t)(void);

        pFunc_t* p = (pFunc_t*) arrayBegin;
        for (; p < (pFunc_t*) arrayEnd; ++p)
          {
            // call the function through the pointer
            (*(*p))();
          }
      }

    template<class TLinkerScript_T, typename TLinkerAlign_T>
      inline __attribute__((always_inline))
      void
      CStartup<TLinkerScript_T, TLinkerAlign_T>::initialiseAndCallStaticConstructors(
          void)
      {
        copyInitialisedData(LinkerScript_t::getFlashDataBegin(),
            LinkerScript_t::getRamDataBegin(), LinkerScript_t::getRamDataEnd());

        clearBss(LinkerScript_t::getBssBegin(), LinkerScript_t::getBssEnd());

        callStaticInitialisers(LinkerScript_t::getInitArrayStart(),
            LinkerScript_t::getInitArrayEnd());
      }

    template<class TLinkerScript_T, typename TLinkerAlign_T>
      inline __attribute__((always_inline))
      void
      CStartup<TLinkerScript_T, TLinkerAlign_T>::callStaticDestructors(void)
      {
        callStaticInitialisers(LinkerScript_t::getFiniArrayStart(),
            LinkerScript_t::getFiniArrayEnd());
      }

  }
}

#endif // OS_PORTABLE_INFRASTRUCTURE_CSTARTUP_H_
