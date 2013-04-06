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
    template<typename TLinkAlign_T>
      class CStartup
      {
      public:

        typedef TLinkAlign_T LinkAlign_t;

        static void
        copyInitialisedData(LinkAlign_t* fromBegin, LinkAlign_t* toBegin, LinkAlign_t* toEnd);

        static void
        clearBss(LinkAlign_t* bssBegin, LinkAlign_t* bssEnd);

        static void
        callStaticInitialisers(LinkAlign_t* arrayBegin, LinkAlign_t* arrayEnd);

      };

    template<typename TLinkAlign_T>
      inline __attribute__((always_inline))
      void
      CStartup<TLinkAlign_T>::copyInitialisedData(LinkAlign_t* fromBegin, LinkAlign_t* toBegin,
          LinkAlign_t* toEnd)
      {
        // Copy the data segment initialisers from flash to RAM
        LinkAlign_t* pSrc = fromBegin;
        LinkAlign_t* pDest = toBegin;
        for (; pDest < toEnd;)
          {
            *(pDest++) = *(pSrc++);
          }
      }

    template<typename TLinkAlign_T>
      inline __attribute__((always_inline))
      void
      CStartup<TLinkAlign_T>::clearBss(LinkAlign_t* bssBegin, LinkAlign_t* bssEnd)
      {
        // Zero fill the bss segment.
        LinkAlign_t* pDest = bssBegin;
        for (; pDest < bssEnd;)
          {
            *(pDest++) = 0;
          }
      }

    template<typename TLinkAlign_T>
      void
      CStartup<TLinkAlign_T>::callStaticInitialisers(LinkAlign_t* arrayBegin,
          LinkAlign_t* arrayEnd)
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
  }
}

#endif // OS_PORTABLE_INFRASTRUCTURE_CSTARTUP_H_
