//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief ARM Cortex-M semihosting implementation (experimental).

#include "portable/core/include/ConfigDefines.h"

// ARM Compiler toolchain
// Developing Software for ARM Processors
// DUI 0471I

// TODO: try with inline BKPT

__attribute__((naked))
int
_BKPT(int op, void* p1, void* p2)
{
  register int r0 asm("r0");
  register int r1 asm("r1") __attribute__((unused));
  register int r2 asm("r2") __attribute__((unused));

  r0 = op;
  r1 = (int) p1;
  r2 = (int) p2;

  asm volatile(""
      " bkpt 0xAB \n"
      : "=r"(r0)
      :
      :
  );
  return r0;
}

void
shPutChar(char ch)
{
  _BKPT(0x03, (void*) (int) ch, 0);
}

void
shPutStr(char* pStr)
{
  _BKPT(0x04, pStr, 0);
}
