//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief C++ Startup template.

#ifndef OS_PORTABLE_INFRASTRUCTURE_CPPSTARTUP_H_
#define OS_PORTABLE_INFRASTRUCTURE_CPPSTARTUP_H_

//#include "portable/core/include/ConfigDefines.h"

namespace os
{
  namespace infra
  {
    // ========================================================================

    template<class LinkerScript_T,
        typename linkerAlign_T = typename LinkerScript_T::linkerAlign_t>
      class TCppStartup
      {
      public:

        typedef LinkerScript_T LinkerScript;
        typedef linkerAlign_T linkerAlign_t;

        static void
        copyInitialisedData(linkerAlign_t* fromBegin, linkerAlign_t* toBegin,
            linkerAlign_t* toEnd);

        static void
        clearBss(linkerAlign_t* bssBegin, linkerAlign_t* bssEnd);

        static void
        callStaticFunctionsAscending(linkerAlign_t* arrayBegin,
            linkerAlign_t* arrayEnd);

        static void
        callStaticFunctionsDescending(linkerAlign_t* arrayBegin,
            linkerAlign_t* arrayEnd);

        static void
        initialiseDataAndBss(void);

        static void
        callStaticConstructors(void);

        static void
        callStaticDestructors(void);

      };

    template<class LinkerScript_T, typename linkerAlign_T>
      inline void
      __attribute__((always_inline))
      TCppStartup<LinkerScript_T, linkerAlign_T>::copyInitialisedData(
          linkerAlign_t* fromBegin, linkerAlign_t* toBegin,
          linkerAlign_t* toEnd)
      {
        // Copy the data segment initialisers from flash to RAM
        linkerAlign_t* pSrc = fromBegin;
        linkerAlign_t* pDest = toBegin;
        for (; pDest < toEnd;)
          {
            *(pDest++) = *(pSrc++);
          }
      }

    template<class LinkerScript_T, typename linkerAlign_T>
      inline void
      __attribute__((always_inline))
      TCppStartup<LinkerScript_T, linkerAlign_T>::clearBss(
          linkerAlign_t* bssBegin, linkerAlign_t* bssEnd)
      {
        // Zero fill the bss segment.
        linkerAlign_t* pDest = bssBegin;
        for (; pDest < bssEnd;)
          {
            *(pDest++) = 0;
          }
      }

    template<class LinkerScript_T, typename linkerAlign_T>
      void
      TCppStartup<LinkerScript_T, linkerAlign_T>::callStaticFunctionsAscending(
          linkerAlign_t* arrayBegin, linkerAlign_t* arrayEnd)
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

    template<class LinkerScript_T, typename linkerAlign_T>
      void
      TCppStartup<LinkerScript_T, linkerAlign_T>::callStaticFunctionsDescending(
          linkerAlign_t* arrayBegin, linkerAlign_t* arrayEnd)
      {
        typedef void
        (*pFunc_t)(void);

        int count = arrayEnd - arrayBegin;
        pFunc_t* p = (pFunc_t*) arrayEnd;
        for (; count > 0; count--)
          {
            --p; // pre-decrement, we started with the address AFTER
            // call the function through the pointer
            (*(*p))();
          }
      }

    template<class LinkerScript_T, typename linkerAlign_T>
      inline void
      __attribute__((always_inline))
      TCppStartup<LinkerScript_T, linkerAlign_T>::initialiseDataAndBss(void)
      {
        copyInitialisedData(LinkerScript::getFlashDataBegin(),
            LinkerScript::getRamDataBegin(), LinkerScript::getRamDataEnd());

        clearBss(LinkerScript::getBssBegin(), LinkerScript::getBssEnd());
      }

    template<class LinkerScript_T, typename linkerAlign_T>
      inline void
      __attribute__((always_inline))
      TCppStartup<LinkerScript_T, linkerAlign_T>::callStaticConstructors(void)
      {
        callStaticFunctionsAscending(LinkerScript::getInitArrayBegin(),
            LinkerScript::getInitArrayEnd());
      }

    template<class LinkerScript_T, typename linkerAlign_T>
      inline void
      __attribute__((always_inline))
      TCppStartup<LinkerScript_T, linkerAlign_T>::callStaticDestructors(void)
      {
        callStaticFunctionsDescending(LinkerScript::getFiniArrayBegin(),
            LinkerScript::getFiniArrayEnd());
      }

  // ==========================================================================

  } // namespace infra
} // namespace os

#endif // OS_PORTABLE_INFRASTRUCTURE_CPPSTARTUP_H_
