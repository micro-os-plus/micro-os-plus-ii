/*
 *	Copyright (C) 2012 Liviu Ionescu.
 *
 *	This file is part of the uOS++ distribution.
 */

#include "portable/kernel/include/OS_Defines.h"

#include "portable/kernel/include/OS_Greeting.h"

#include "../include/Debug.h"

#if defined(OS_INCLUDE_HAL_ARCH_SYNTHETIC_OSX_DEVICES_DEBUGIMPLEMENTATION)
#include "hal/arch/synthetic/osx/devices/debug/include/DebugImplementation.h"
#else
#error "Missing DebugImplementation"
#endif

#include <stdio.h>
#include <string.h>


namespace os
{
  namespace device
  {

    Debug::Debug()
    {
      putConstructor("os::device::Debug::Debug", this);
    }

    Debug::~Debug()
    {
      putDestructor("os::device::Debug::~Debug", this);
    }

    void
    Debug::earlyInitialise(void)
    {
      os::hal::device::debug::Implementation::earlyInitialise();

      os::hal::device::debug::Implementation::putNewLine();
      os::hal::device::debug::Implementation::putNewLine();
      os::hal::device::debug::Implementation::putBytes(os::greeting, strlen(os::greeting));
      os::hal::device::debug::Implementation::putNewLine();
    }

    void
    Debug::putNewLine()
    {
      os::hal::device::debug::Implementation::putNewLine();
    }

    void
    Debug::putChar(char c)
    {
      os::hal::device::debug::Implementation::putBytes(&c, 1);
    }

    void
    Debug::putString(const char* cpStr)
    {
      if (cpStr == 0)
        return;

      os::hal::device::debug::Implementation::putBytes(cpStr, strlen(cpStr));
    }


    void
    Debug::putHex(uint32_t v, size_t n)
    {
      unsigned char buff[sizeof(v) * 2];

      for (int i = n; i > 0;)
        {
          unsigned char b;
          unsigned char c;
          b = v;
          c = (b & 0xF);
          buff[--i] = c < 10 ? c + '0' : c + 'A' - 10;
          c = ((b >> 4) & 0x0F);
          buff[--i] = c < 10 ? c + '0' : c + 'A' - 10;

          v >>= 8;
        }

      os::hal::device::debug::Implementation::putBytes(buff, n);
    }


    void
    Debug::putHex(uint64_t v)
    {
      unsigned char buff[sizeof(v) * 2];

      for (int i = sizeof(buff); i > 0;)
        {
          unsigned char b;
          unsigned char c;
          b = v;
          c = (b & 0xF);
          buff[--i] = c < 10 ? c + '0' : c + 'A' - 10;
          c = ((b >> 4) & 0x0F);
          buff[--i] = c < 10 ? c + '0' : c + 'A' - 10;

          v >>= 8;
        }

      os::hal::device::debug::Implementation::putBytes(buff, sizeof(buff));
    }


    void
    Debug::putDec(uint32_t v, size_t n)
    {
      int i; // must be signed
      unsigned char buff[10];

      for (i = sizeof(buff) - 1; i >= 0; i--)
        {
          buff[i] = (v % 10) + '0';
          v /= 10;
        }

      if (0 < n && n <= (int) sizeof(buff))
        i = (int) sizeof(buff) - n;
      else
        {
          for (i = 0; i < (int) sizeof(buff) - 1; ++i)
            if (buff[i] != '0')
              break;
        }
      if (i < (int) sizeof(buff))
        {
          os::hal::device::debug::Implementation::putBytes((const char*) &buff[i],
              (int) sizeof(buff) - i);
        }
    }

    void
    Debug::putDec(int32_t v, size_t n)
    {
      if (v < 0)
        {
          putChar('-');
          v = -v;
        }

      putDec((uint32_t)v, n);
    }

    void
    Debug::putDec(uint64_t v, size_t n)
    {
      int i; // must be signed
      unsigned char buff[20];

      for (i = sizeof(buff) - 1; i >= 0; i--)
        {
          buff[i] = (v % 10) + '0';
          v /= 10;
        }

      if (0 < n && n <= (int) sizeof(buff))
        i = (int) sizeof(buff) - n;
      else
        {
          for (i = 0; i < (int) sizeof(buff) - 1; ++i)
            if (buff[i] != '0')
              break;
        }
      if (i < (int) sizeof(buff))
        {
          os::hal::device::debug::Implementation::putBytes((const char*) &buff[i],
              (int) sizeof(buff) - i);
        }
    }


    void
    Debug::putDec(int64_t v, size_t n)
    {
      if (v < 0)
        {
          putChar('-');
          v = -v;
        }

      putDec((uint64_t)v, n);
    }

    // Constructors and destructors

    void
    Debug::putConstructor(const char* pcStr, const void* pcAddr)
    {
      putString(pcStr);
      putString("() @0x");
      putAddress(pcAddr);
      putNewLine();
    }

    void
    Debug::putConstructorWithIndex(const char* pcStr, uint16_t i,
        const void* pcAddr)
    {
      putString(pcStr);
      putChar('(');
      putDec(i);
      putString(") @0x");
      putAddress(pcAddr);
      putNewLine();
    }

    void
    Debug::putDestructor(const char* pcStr, const void* pc)
    {
      putString(pcStr);
      putString("() @0x");
      putAddress(pc);
      putNewLine();
    }

    // Assert details

    void
    Debug::assert(const char* pcFunc, const char* pcFile, unsigned int lineno, const char* pcSexp)
    {
          putString("assertion '");
          putString(pcSexp);
          putString("' failed in '");
          putString(pcFunc);
          putString("', file '");
          putString(pcFile);
          putString("' at line ");
          putDec(lineno);
          putNewLine();

          for (;;)
            ; //DeviceDebugImpl_t::implWDReset();
    }

  } /* namespace device */
} /* namespace os */
