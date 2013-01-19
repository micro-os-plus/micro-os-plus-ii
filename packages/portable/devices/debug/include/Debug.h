/*
 *	Copyright (C) 2012-2013 Liviu Ionescu.
 *
 *	This file is part of the uOS++ distribution.
 */

#ifndef OS_PORTABLE_DEVICES_DEBUG_H_
#define OS_PORTABLE_DEVICES_DEBUG_H_

#include <stdint.h>
#include <unistd.h>

namespace os
{
  namespace device
  {

    class Debug
    {
    public:

#if defined(DEBUG)

      // Constructor/Destructor are used only for informative purposes
      // if DEBUG is enabled.
      Debug();
      ~Debug();

#endif /* defined(DEBUG) */

      static void
      earlyInitialise(void);

      static void
      putNewLine(void);

      static void
      putChar(char c);

      // All strings
      static void
      putString(const char* cpStr);

      static void
      putString(char* cpStr);

      static void
      putString(const signed char* cpStr);

      static void
      putString(signed char* cpStr);

      static void
      putString(const unsigned char* cpStr);

      static void
      putString(unsigned char* cpStr);

      // A generic address, based on machine pointer size
      static void
      putAddress(const void* pc);

      static void
      putHex(uint8_t v);

      static void
      putHex(uint16_t v);

      static void
      putHex(uint32_t v);

      static void
      putHex(uint64_t v);

#if (__SIZEOF_SIZE_T__ == 8)
      static void
      putHex(uintmax_t v);
#endif

      static void
      putDec(uint8_t v, size_t n = 0);

      static void
      putDec(uint16_t v, size_t n = 0);

      static void
      putDec(uint32_t v, size_t n = 0);

      static void
      putDec(uint64_t v, size_t n = 0);

#if (__SIZEOF_SIZE_T__ == 8)
      static void
      putDec(uintmax_t v, size_t n = 0);
#endif

      static void
      putDec(int8_t v, size_t n = 0);

      static void
      putDec(int16_t v, size_t n = 0);

      static void
      putDec(int32_t v, size_t n = 0);

      static void
      putDec(int64_t v, size_t n = 0);

#if (__SIZEOF_SIZE_T__ == 8)
      static void
      putDec(intmax_t v, size_t n = 0);
#endif

      static void
      putConstructor(const char* pcStr, const void* pcAddr);

      static void
      putConstructorWithIndex(const char* pcStr, uint16_t i,
          const void* pcAddr);

      static void
      putDestructor(const char* pcStr, const void* pcAddr);

      static void
      flush(void);

      static void
      assert(const char* pcFunc, const char* pcFile, unsigned int lineno,
          const char* pcSexp);

    private:
      static void
      putHex(uint32_t v, size_t n);

    };

    inline void
    Debug::putString(char* cpStr)
    {
      putString((const char*) cpStr);
    }

    inline void
    Debug::putString(const signed char* cpStr)
    {
      putString((const char*) cpStr);
    }

    inline void
    Debug::putString(signed char* cpStr)
    {
      putString((const char*) cpStr);
    }

    inline void
    Debug::putString(const unsigned char* cpStr)
    {
      putString((const char*) cpStr);
    }

    inline void
    Debug::putString(unsigned char* cpStr)
    {
      putString((const char*) cpStr);
    }

    inline void
    Debug::putAddress(const void* pc)
    {
#if (__SIZEOF_POINTER__ == 2)
      putHex((const uint16_t) pc);
#elif (__SIZEOF_POINTER__ == 4)
      putHex((const uint32_t) pc);
#elif (__SIZEOF_POINTER__ == 8)
      putHex((uint64_t) pc);
#else
#error "Unsupported __SIZEOF_POINTER__"
#endif
    }

    inline void
    Debug::putHex(uint8_t v)
    {
      putHex(v, 2);
    }

    inline void
    Debug::putHex(uint16_t v)
    {
      putHex(v, 4);
    }

    inline void
    Debug::putHex(uint32_t v)
    {
      putHex(v, 8);
    }

#if (__SIZEOF_SIZE_T__ == 8)
    inline void
    Debug::putHex(uintmax_t v)
      {
        putHex((uint64_t) v);
      }
#endif

    inline void
    Debug::putDec(uint8_t v, size_t n)
    {
      putDec((uint32_t) v, n);
    }

    inline void
    Debug::putDec(uint16_t v, size_t n)
    {
      putDec((uint32_t) v, n);
    }

#if (__SIZEOF_SIZE_T__ == 8)
    inline void
    Debug::putDec(uintmax_t v, size_t n)
      {
        putDec((uint64_t) v, n);
      }
#endif

    inline void
    Debug::putDec(int8_t v, size_t n)
    {
      putDec((int32_t) v, n);
    }

    inline void
    Debug::putDec(int16_t v, size_t n)
    {
      putDec((uint32_t) v, n);
    }

#if (__SIZEOF_SIZE_T__ == 8)
    inline void
    Debug::putDec(intmax_t v, size_t n)
      {
        putDec((int64_t) v, n);
      }
#endif

#if !defined(DEBUG)

    // ----- Inline section ---------------------------------------------------
    // If DEBUG is disabled, all methods defined in Debug.cpp
    // should have an empty equivalent.

    inline void
    Debug::earlyInitialise(void)
    {
      ;
    }

    inline void
    Debug::putNewLine()
    {
      ;
    }

    inline void
    Debug::putChar(char c)
    {
      ;
    }

    inline void
    Debug::putString(const char* cpStr)
    {
      ;
    }

    inline void
    Debug::putHex(uint32_t v, size_t n)
    {
      ;
    }

    inline void
    Debug::putHex(uint64_t v)
    {
      ;
    }

    inline void
    Debug::putDec(uint32_t v, size_t n)
    {
      ;
    }

    inline void
    Debug::putDec(int32_t v, size_t n)
    {
      ;
    }

    inline void
    Debug::putDec(uint64_t v, size_t n)
    {
      ;
    }

    inline void
    Debug::putDec(int64_t v, size_t n)
    {
      ;
    }

    // Constructors and destructors

    inline void
    Debug::putConstructor(const char* pcStr, const void* pcAddr)
    {
      ;
    }

    inline void
    Debug::putConstructorWithIndex(const char* pcStr, uint16_t i,
        const void* pcAddr)
    {
      ;
    }

    inline void
    Debug::putDestructor(const char* pcStr, const void* pc)
    {
      ;
    }

    // Assert details

    inline void
    Debug::assert(const char* pcFunc, const char* pcFile, unsigned int lineno,
        const char* pcSexp)
    {
      ;
    }

#endif /* !defined(DEBUG) */

  }
/* namespace device */
} /* namespace os */

#endif /* OS_PORTABLE_DEVICES_DEBUG_H_ */
