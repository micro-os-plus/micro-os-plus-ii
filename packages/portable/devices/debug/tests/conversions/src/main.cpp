/*
 *      Copyright (C) 2012-2013 Liviu Ionescu.
 *
 *      This file is part of the uOS++ distribution.
 */


#include "portable/core/include/OS.h"

int
main()
{
  debug.putNewLine();
  debug.putString("main()");
  debug.putNewLine();
  debug.putString("Test various conversions implemented by the Debug() class");
  debug.putNewLine();

  debug.putNewLine();

  debug.putString("* Size of different variables");
  debug.putNewLine();

  debug.putString("sizeof(void*): ");
  debug.putDec(sizeof(void*));
  debug.putNewLine();

  debug.putString("sizeof(size_t): ");
  debug.putDec(sizeof(size_t));
  debug.putNewLine();

  debug.putString("sizeof(short): ");
  debug.putDec(sizeof(short));
  debug.putNewLine();

  debug.putString("sizeof(int): ");
  debug.putDec(sizeof(int));
  debug.putNewLine();

  debug.putString("sizeof(long): ");
  debug.putDec(sizeof(long));
  debug.putNewLine();

  debug.putString("sizeof(uintmax_t): ");
  debug.putDec(sizeof(uintmax_t));
  debug.putNewLine();

  debug.putNewLine();

  debug.putString("* Char variables");
  debug.putNewLine();

  debug.putString("char: ");
  debug.putChar('a');
  debug.putNewLine();

  debug.putString("char: ");
  char ch1 = 'b';
  debug.putChar(ch1);
  debug.putNewLine();

  debug.putString("unsigned char: ");
  unsigned char ch2 = 'c';
  debug.putChar(ch2);
  debug.putNewLine();

  debug.putString("const char: ");
  const char ch3 = 'd';
  debug.putChar(ch3);
  debug.putNewLine();

  debug.putString("const unsigned char: ");
  const unsigned char ch4 = 'e';
  debug.putChar(ch4);
  debug.putNewLine();

  debug.putNewLine();

  debug.putString("* Array of characters");
  debug.putNewLine();

  unsigned char buff1[] = "unsigned char[]";
  debug.putString(buff1);
  debug.putNewLine();

  signed char buff2[] = "signed char[]";
  debug.putString(buff2);
  debug.putNewLine();

  char buff3[] = "char[]";
  debug.putString(buff3);
  debug.putNewLine();

  const unsigned char buff4[] = "const unsigned char[]";
  debug.putString(buff4);
  debug.putNewLine();

  const signed char buff5[] = "const signed char[]";
  debug.putString(buff5);
  debug.putNewLine();

  const char buff6[] = "const char[]";
  debug.putString(buff6);
  debug.putNewLine();

  debug.putNewLine();

  debug.putString("* Unsigned variables, as hex");
  debug.putNewLine();

  uint8_t u8 = 0x12;
  debug.putString("uint8_t: 0x");
  debug.putHex(u8);
  debug.putNewLine();

  uint16_t u16 = 0x1234;
  debug.putString("uint16_t: 0x");
  debug.putHex(u16);
  debug.putNewLine();

  unsigned short ushort = 0x1234;
  debug.putString("unsigned short: 0x");
  debug.putHex(ushort);
  debug.putNewLine();

  unsigned int uint = 0x1234;
  debug.putString("unsigned int: 0x");
  debug.putHex(uint);
  debug.putNewLine();

  uint32_t u32 = 0x12345678;
  debug.putString("uint32_t: 0x");
  debug.putHex(u32);
  debug.putNewLine();

  unsigned long ulong = 0x12345678;
  debug.putString("unsigned long: 0x");
  debug.putHex(ulong);
  debug.putNewLine();

  uint64_t u64 = 0x123456789ABCDEF0;
  debug.putString("uint64_t: 0x");
  debug.putHex(u64);
  debug.putNewLine();

  uintmax_t umax = 0x0;
  debug.putString("uintmax_t: 0x");
  debug.putHex(umax);
  debug.putNewLine();

  debug.putNewLine();

  debug.putString("* Unsigned variables, as decimal");
  debug.putNewLine();

  u8 = 123;
  debug.putString("uint8_t: ");
  debug.putDec(u8);
  debug.putNewLine();

  u16 = 12345;
  debug.putString("uint16_t: ");
  debug.putDec(u16);
  debug.putNewLine();

  ushort = 12345;
  debug.putString("unsigned short: ");
  debug.putDec(ushort);
  debug.putNewLine();

  uint = 12345;
  debug.putString("unsigned int: ");
  debug.putDec(uint);
  debug.putNewLine();

  u32 = 1234567890;
  debug.putString("uint32_t: ");
  debug.putDec(u32);
  debug.putNewLine();

  debug.putString("unsigned long: ");
  ulong = 1234567890;
  debug.putDec(ulong);
  debug.putNewLine();

  u64 = 12345678901234567890u;
  debug.putString("uint64_t: ");
  debug.putDec(u64);
  debug.putNewLine();

  umax = 0;
  debug.putString("uintmax_t: ");
  debug.putDec(umax);
  debug.putNewLine();

  debug.putNewLine();

  debug.putString("* Signed variables, as decimal, with various lengths");
  debug.putNewLine();

  int8_t i8 = 123;
  debug.putString("int8_t: ");
  debug.putDec(i8);
  debug.putChar(' ');
  debug.putDec(i8, 2);
  debug.putChar(' ');
  debug.putDec(i8, 3);
  debug.putChar(' ');
  debug.putDec(i8, 4);
  i8 = -123;
  debug.putChar(' ');
  debug.putDec(i8);
  debug.putChar(' ');
  debug.putDec(i8,2);
  debug.putChar(' ');
  debug.putDec(i8,3);
  debug.putChar(' ');
  debug.putDec(i8,4);
  debug.putNewLine();

  int16_t i16 = 12345;
  debug.putString("int16_t: ");
  debug.putDec(i16);
  debug.putChar(' ');
  debug.putDec(i16, 4);
  debug.putChar(' ');
  debug.putDec(i16, 5);
  debug.putChar(' ');
  debug.putDec(i16, 6);
  i16 = -12345;
  debug.putChar(' ');
  debug.putDec(i16);
  debug.putChar(' ');
  debug.putDec(i16,4);
  debug.putChar(' ');
  debug.putDec(i16,5);
  debug.putChar(' ');
  debug.putDec(i16,6);
  debug.putNewLine();

  int32_t i32 = 123456789;
  debug.putString("int32_t: ");
  debug.putDec(i32);
  debug.putChar(' ');
  debug.putDec(i32, 8);
  debug.putChar(' ');
  debug.putDec(i32, 9);
  debug.putChar(' ');
  debug.putDec(i32, 10);
  i32 = -123456789;
  debug.putChar(' ');
  debug.putDec(i32);
  debug.putChar(' ');
  debug.putDec(i32,8);
  debug.putChar(' ');
  debug.putDec(i32,9);
  debug.putChar(' ');
  debug.putDec(i32,10);
  debug.putNewLine();

  int64_t i64 = 1234567890123456789;
  debug.putString("int64_t: ");
  debug.putDec(i64);
  debug.putChar(' ');
  debug.putDec(i64, 18);
  debug.putChar(' ');
  debug.putDec(i64, 19);
  debug.putChar(' ');
  debug.putDec(i64, 20);
  i64 = -1234567890123456789;
  debug.putChar(' ');
  debug.putDec(i64);
  debug.putChar(' ');
  debug.putDec(i64,18);
  debug.putChar(' ');
  debug.putDec(i64,19);
  debug.putChar(' ');
  debug.putDec(i64,20);
  debug.putNewLine();

  debug.putNewLine();

  debug.putString("* Done");
  debug.putNewLine();

  debug.putNewLine();

  return 0;
}


class OtherClass
{
public:
  OtherClass();
  ~OtherClass();
};

OtherClass::OtherClass()
{
  debug.putConstructor("OtherClass::OtherClass", this);
}

OtherClass::~OtherClass()
{
  debug.putDestructor("OtherClass::~OtherClass", this);
}


OtherClass otherObject;

