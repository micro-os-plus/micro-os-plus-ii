//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/OS.h"

#include "portable/infrastructure/include/TestSuite.h"

#include "portable/diagnostics/include/Trace.h"
#include "portable/diagnostics/include/Trace.cpp.h"

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

static os::infra::TestSuite ts;

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------

class TraceImplementationCharArray
{
public:
  TraceImplementationCharArray();

  ~TraceImplementationCharArray();

  ssize_t
  write(const void* pBuf, size_t numBytes);

  void
  flush(void);

  char
  getDefaultChar(void);

  // public variables, will be used directly in tests
  char array[1024];
  size_t count;
  size_t flushCount;
};

TraceImplementationCharArray::TraceImplementationCharArray()
{
  for (size_t i = 0; i < sizeof(array); ++i)
    array[i] = getDefaultChar();

  count = 0;
  flushCount = 0;
}

TraceImplementationCharArray::~TraceImplementationCharArray()
{
}

ssize_t
TraceImplementationCharArray::write(const void* pBuf, size_t numBytes)
{
  if ((count + numBytes) < sizeof(array))
    {
      memcpy(&array[count], pBuf, numBytes);
      count += numBytes;

      return static_cast<ssize_t>(numBytes);
    }
  else
    {
#if defined(DEBUG)
      os::diag::trace << "--- overflow ---" << os::std::endl;
#endif
      return -1;
    }
}

void
TraceImplementationCharArray::flush(void)
{
  ++flushCount;
}

inline char
TraceImplementationCharArray::getDefaultChar(void)
{
  return '*';
}

//typedef TraceImplementationCharArray TraceImplementationCharArray;

// ----------------------------------------------------------------------------

template class os::diag::TTraceLightBase<TraceImplementationCharArray>;

typedef os::diag::TTraceLightBase<TraceImplementationCharArray> TraceLightBaseCharArray;

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wweak-template-vtables"
#endif

template class os::diag::TTraceBase<TraceLightBaseCharArray,
    TraceImplementationCharArray>;

#pragma GCC diagnostic pop

typedef os::diag::TTraceBase<TraceLightBaseCharArray,
    TraceImplementationCharArray> TraceBaseCharArray;

// ----------------------------------------------------------------------------

void
runTestCompile();

void
runTestCompile()
{
    {
      // test if the class accepts all these data types
      // (compile time tests, runtime validations below)

      TraceBaseCharArray t;

      t.putNewLine();

      // const chars
      const char c1 = 'A';
      t.putChar(c1);

      const signed char c2 = 'B';
      t.putChar(c2);

      const signed char c3 = 'C';
      t.putChar(c3);

      // non const chars
      char c4 = 'D';
      t.putChar(c4);

      signed char c5 = 'E';
      t.putChar(c5);

      unsigned char c6 = 'F';
      t.putChar(c6);

      // strings
      t.putString("str");

      const char s1[] = "s1";
      t.putString(s1);

      char s2[] = "s2";
      t.putString(s2);

      const signed char s3[] = "s3";
      t.putString(s3);

      const unsigned char s4[] = "s4";
      t.putString(s4);

      void* p = 0;
      t.putStringAndAddress(s1, p);

      unsigned int un1 = 0x12;
      t.putHex(un1);

      unsigned long un2 = 0x12;
      t.putHex(un2);

      unsigned short un3 = 0x12;
      t.putHex(un3);

      unsigned char un4 = 0x12;
      t.putHex(un4);

      unsigned long un5 = 0x12;
      t.putHex(un5);

      t.putHex(p);

      int sn1 = 0;
      t.putDec(sn1);

      long sn2 = 0;
      t.putDec(sn2);

      //t.putDec(un1);
      //t.putDec(un2);
      t.putDec(un3);

      ts.reportPassed("compile test passed");
    }
}

// ----------------------------------------------------------------------------

void
runTestConstructor();

void
runTestConstructor()
{
    {
      TraceBaseCharArray t;
      TraceImplementationCharArray& ti = t.getImplementation();

      ts.setFunctionNameOrPrefix("TraceImplementationCharArray()");

      ts.assertCondition(ti.count == 0);
      ts.assertCondition(ti.flushCount == 0);
      ts.assertCondition(ti.array[0] == ti.getDefaultChar());
      ts.assertCondition(ti.array[sizeof(ti.array)-1] == ti.getDefaultChar());
    }
}

// ----------------------------------------------------------------------------

void
runTestChars();

void
runTestChars()
{
    {
      TraceBaseCharArray t;
      TraceImplementationCharArray& ti = t.getImplementation();

      ts.setFunctionNameOrPrefix("putNewLine()");

      ts.assertCondition(ti.array[0] == ti.getDefaultChar());

      t.putNewLine();
      ts.assertCondition(ti.count == 1);
      ts.assertCondition(ti.array[0] == '\n');
      ts.assertCondition(ti.array[1] == ti.getDefaultChar());
      ts.assertCondition(ti.flushCount == 1);
    }

    {
      TraceBaseCharArray t;
      TraceImplementationCharArray& ti = t.getImplementation();

      ts.setFunctionNameOrPrefix("putChar(const char)");

      ts.assertCondition(ti.array[0] == ti.getDefaultChar());

      const char ch = 'A';
      t.putChar(ch);

      ts.assertCondition(ti.count == 1);
      ts.assertCondition(ti.array[0] == 'A');
      ts.assertCondition(ti.array[1] == ti.getDefaultChar());
    }

    {
      TraceBaseCharArray t;
      TraceImplementationCharArray& ti = t.getImplementation();

      ts.setFunctionNameOrPrefix("putChar(const signed char)");

      ts.assertCondition(ti.array[0] == ti.getDefaultChar());

      const signed char ch = 'B';
      t.putChar(ch);

      ts.assertCondition(ti.count == 1);
      ts.assertCondition(ti.array[0] == 'B');
      ts.assertCondition(ti.array[1] == ti.getDefaultChar());
    }

    {
      TraceBaseCharArray t;
      TraceImplementationCharArray& ti = t.getImplementation();

      ts.setFunctionNameOrPrefix("putChar(const unsigned char)");

      ts.assertCondition(ti.array[0] == ti.getDefaultChar());

      const unsigned char ch = 'C';
      t.putChar(ch);

      ts.assertCondition(ti.count == 1);
      ts.assertCondition(ti.array[0] == 'C');
      ts.assertCondition(ti.array[1] == ti.getDefaultChar());
    }
}

// ----------------------------------------------------------------------------

void
runTestStrings();

void
runTestStrings()
{
    {
      TraceBaseCharArray t;
      TraceImplementationCharArray& ti = t.getImplementation();

      ts.setFunctionNameOrPrefix("putString(const char*)");

      ts.assertCondition(ti.array[0] == ti.getDefaultChar());

      const char s[] = "abc";
      t.putString(s);

      ts.assertCondition(ti.count == 3);
      ts.assertCondition(ti.array[0] == 'a');
      ts.assertCondition(ti.array[1] == 'b');
      ts.assertCondition(ti.array[2] == 'c');
      ts.assertCondition(ti.array[3] == ti.getDefaultChar());
    }

    {
      TraceBaseCharArray t;
      TraceImplementationCharArray& ti = t.getImplementation();

      ts.setFunctionNameOrPrefix("putString(char*)");

      ts.assertCondition(ti.array[0] == ti.getDefaultChar());
      char s[] = "bcd";

      t.putString(s);
      ts.assertCondition(ti.count == 3);
      ts.assertCondition(ti.array[0] == 'b');
      ts.assertCondition(ti.array[1] == 'c');
      ts.assertCondition(ti.array[2] == 'd');
      ts.assertCondition(ti.array[3] == ti.getDefaultChar());
    }

    {
      TraceBaseCharArray t;
      TraceImplementationCharArray& ti = t.getImplementation();

      ts.setFunctionNameOrPrefix("putString(const signed char*)");

      ts.assertCondition(ti.array[0] == ti.getDefaultChar());
      const signed char s[] = "cde";

      t.putString(s);
      ts.assertCondition(ti.count == 3);
      ts.assertCondition(ti.array[0] == 'c');
      ts.assertCondition(ti.array[1] == 'd');
      ts.assertCondition(ti.array[2] == 'e');
      ts.assertCondition(ti.array[3] == ti.getDefaultChar());
    }

    {
      TraceBaseCharArray t;
      TraceImplementationCharArray& ti = t.getImplementation();

      ts.setFunctionNameOrPrefix("putString(const unsigned char*)");

      ts.assertCondition(ti.array[0] == ti.getDefaultChar());
      const unsigned char s[] = "def";

      t.putString(s);
      ts.assertCondition(ti.count == 3);
      ts.assertCondition(ti.array[0] == 'd');
      ts.assertCondition(ti.array[1] == 'e');
      ts.assertCondition(ti.array[2] == 'f');
      ts.assertCondition(ti.array[3] == ti.getDefaultChar());
    }
}

// ----------------------------------------------------------------------------

void
runTestHex();

void
runTestHex()
{
  ts.reportInfo("hex numbers");
    {
      TraceBaseCharArray t;
      TraceImplementationCharArray& ti = t.getImplementation();

      ts.reportInfo("char first digits");
      ts.setFunctionNameOrPrefix("putHex(unsigned char)");
      ts.setInputValues("0x12");

      ts.assertCondition(ti.array[0] == ti.getDefaultChar());

      unsigned char un = 0x01;
      t.putHex(un);

      ts.assertCondition(ti.count == 2);
      ts.assertCondition(ti.array[0] == '0');
      ts.assertCondition(ti.array[1] == '1');
      ts.assertCondition(ti.array[2] == ti.getDefaultChar());
    }

    {
      TraceBaseCharArray t;
      TraceImplementationCharArray& ti = t.getImplementation();

      ts.reportInfo("char middle digits");
      ts.setFunctionNameOrPrefix("putHex(unsigned char)");
      ts.setInputValues("0x9A");

      ts.assertCondition(ti.array[0] == ti.getDefaultChar());

      unsigned char un = 0x9A;
      t.putHex(un);

      ts.assertCondition(ti.count == 2);
      ts.assertCondition(ti.array[0] == '9');
      ts.assertCondition(ti.array[1] == 'A');
      ts.assertCondition(ti.array[2] == ti.getDefaultChar());
    }

    {
      TraceBaseCharArray t;
      TraceImplementationCharArray& ti = t.getImplementation();

      ts.reportInfo("char last digits");
      ts.setFunctionNameOrPrefix("putHex(unsigned char)");
      ts.setInputValues("0xEF");

      ts.assertCondition(ti.array[0] == ti.getDefaultChar());

      unsigned char un = 0xEF;
      t.putHex(un);

      ts.assertCondition(ti.count == 2);
      ts.assertCondition(ti.array[0] == 'E');
      ts.assertCondition(ti.array[1] == 'F');
      ts.assertCondition(ti.array[2] == ti.getDefaultChar());
    }

    {
      TraceBaseCharArray t;
      TraceImplementationCharArray& ti = t.getImplementation();

      ts.reportInfo("short");
      ts.setFunctionNameOrPrefix("putHex(unsigned short)");

      ts.assertCondition(ti.array[0] == ti.getDefaultChar());

#if __SIZEOF_SHORT__ == 2
      unsigned short un = 0x1234;
      t.putHex(un);

      ts.assertCondition(ti.count == 4);
      ts.assertCondition(ti.array[0] == '1');
      ts.assertCondition(ti.array[1] == '2');
      ts.assertCondition(ti.array[2] == '3');
      ts.assertCondition(ti.array[3] == '4');
      ts.assertCondition(ti.array[4] == ti.getDefaultChar());
#else
#error "unsupported size of short"
#endif
    }

    {
      TraceBaseCharArray t;
      TraceImplementationCharArray& ti = t.getImplementation();

      ts.reportInfo("int");
      ts.setFunctionNameOrPrefix("putHex(unsigned int)");

      ts.assertCondition(ti.array[0] == ti.getDefaultChar());

#if __SIZEOF_INT__ == 4
      unsigned int un = 0x12345678;
      t.putHex(un);

      ts.assertCondition(ti.count == 8);
      ts.assertCondition(ti.array[0] == '1');
      ts.assertCondition(ti.array[1] == '2');
      ts.assertCondition(ti.array[2] == '3');
      ts.assertCondition(ti.array[3] == '4');
      ts.assertCondition(ti.array[4] == '5');
      ts.assertCondition(ti.array[5] == '6');
      ts.assertCondition(ti.array[6] == '7');
      ts.assertCondition(ti.array[7] == '8');
      ts.assertCondition(ti.array[8] == ti.getDefaultChar());
#else
#error "unsupported size of int"
#endif
    }

    {
      TraceBaseCharArray t;
      TraceImplementationCharArray& ti = t.getImplementation();

      ts.reportInfo("long");
      ts.setFunctionNameOrPrefix("putHex(unsigned long)");

      ts.assertCondition(ti.array[0] == ti.getDefaultChar());

#if __SIZEOF_LONG__ == 4
      unsigned long un = 0x12345678L;
      t.putHex(un);

      ts.assertCondition(ti.count == 8);
      ts.assertCondition(ti.array[0] == '1');
      ts.assertCondition(ti.array[1] == '2');
      ts.assertCondition(ti.array[2] == '3');
      ts.assertCondition(ti.array[3] == '4');
      ts.assertCondition(ti.array[4] == '5');
      ts.assertCondition(ti.array[5] == '6');
      ts.assertCondition(ti.array[6] == '7');
      ts.assertCondition(ti.array[7] == '8');
      ts.assertCondition(ti.array[8] == ti.getDefaultChar());
#elif __SIZEOF_LONG__ == 8
      unsigned long un = 0x123456789ABCDEF0L;
      t.putHex(un);

      ts.assertCondition(ti.count == 16);
      ts.assertCondition(ti.array[0] == '1');
      ts.assertCondition(ti.array[1] == '2');
      ts.assertCondition(ti.array[2] == '3');
      ts.assertCondition(ti.array[3] == '4');
      ts.assertCondition(ti.array[4] == '5');
      ts.assertCondition(ti.array[5] == '6');
      ts.assertCondition(ti.array[6] == '7');
      ts.assertCondition(ti.array[7] == '8');
      ts.assertCondition(ti.array[8] == '9');
      ts.assertCondition(ti.array[9] == 'A');
      ts.assertCondition(ti.array[10] == 'B');
      ts.assertCondition(ti.array[11] == 'C');
      ts.assertCondition(ti.array[12] == 'D');
      ts.assertCondition(ti.array[13] == 'E');
      ts.assertCondition(ti.array[14] == 'F');
      ts.assertCondition(ti.array[15] == '0');
      ts.assertCondition(ti.array[16] == ti.getDefaultChar());
#else
#error "unsupported sizeof long"
#endif
    }

    {
      TraceBaseCharArray t;
      TraceImplementationCharArray& ti = t.getImplementation();

      ts.reportInfo("long long");
      ts.setFunctionNameOrPrefix("putHex(unsigned long long)");

      ts.assertCondition(ti.array[0] == ti.getDefaultChar());

#if __SIZEOF_LONG_LONG__ == 8
      unsigned long long un = 0x123456789ABCDEF0L;
      t.putHex(un);

      ts.assertCondition(ti.count == 16);
      ts.assertCondition(ti.array[0] == '1');
      ts.assertCondition(ti.array[1] == '2');
      ts.assertCondition(ti.array[2] == '3');
      ts.assertCondition(ti.array[3] == '4');
      ts.assertCondition(ti.array[4] == '5');
      ts.assertCondition(ti.array[5] == '6');
      ts.assertCondition(ti.array[6] == '7');
      ts.assertCondition(ti.array[7] == '8');
      ts.assertCondition(ti.array[8] == '9');
      ts.assertCondition(ti.array[9] == 'A');
      ts.assertCondition(ti.array[10] == 'B');
      ts.assertCondition(ti.array[11] == 'C');
      ts.assertCondition(ti.array[12] == 'D');
      ts.assertCondition(ti.array[13] == 'E');
      ts.assertCondition(ti.array[14] == 'F');
      ts.assertCondition(ti.array[15] == '0');
      ts.assertCondition(ti.array[16] == ti.getDefaultChar());
#else
#error "unsupported sizeof long long"
#endif
    }

    {
      TraceBaseCharArray t;
      TraceImplementationCharArray& ti = t.getImplementation();

      ts.reportInfo("void*");
      ts.setFunctionNameOrPrefix("putHex(void*)");

      ts.assertCondition(ti.array[0] == ti.getDefaultChar());

#if __SIZEOF_POINTER__ == 4
      void* ptr = (void*)0x12345678;
      t.putHex(ptr);

      ts.assertCondition(ti.count == 8);
      ts.assertCondition(ti.array[0] == '1');
      ts.assertCondition(ti.array[1] == '2');
      ts.assertCondition(ti.array[2] == '3');
      ts.assertCondition(ti.array[3] == '4');
      ts.assertCondition(ti.array[4] == '5');
      ts.assertCondition(ti.array[5] == '6');
      ts.assertCondition(ti.array[6] == '7');
      ts.assertCondition(ti.array[7] == '8');
      ts.assertCondition(ti.array[16] == ti.getDefaultChar());
#elif __SIZEOF_POINTER__ == 8
      void* ptr = (void*) 0x123456789ABCDEF0L;
      t.putHex(ptr);

      ts.assertCondition(ti.count == 16);
      ts.assertCondition(ti.array[0] == '1');
      ts.assertCondition(ti.array[1] == '2');
      ts.assertCondition(ti.array[2] == '3');
      ts.assertCondition(ti.array[3] == '4');
      ts.assertCondition(ti.array[4] == '5');
      ts.assertCondition(ti.array[5] == '6');
      ts.assertCondition(ti.array[6] == '7');
      ts.assertCondition(ti.array[7] == '8');
      ts.assertCondition(ti.array[8] == '9');
      ts.assertCondition(ti.array[9] == 'A');
      ts.assertCondition(ti.array[10] == 'B');
      ts.assertCondition(ti.array[11] == 'C');
      ts.assertCondition(ti.array[12] == 'D');
      ts.assertCondition(ti.array[13] == 'E');
      ts.assertCondition(ti.array[14] == 'F');
      ts.assertCondition(ti.array[15] == '0');
      ts.assertCondition(ti.array[16] == ti.getDefaultChar());
#else
#error "unsupported sizeof ptr"
#endif
    }
}

// ----------------------------------------------------------------------------

void
runTestDec();

void
runTestDec()
{
  ts.reportInfo("decimal numbers");

    {
      TraceBaseCharArray t;
      TraceImplementationCharArray& ti = t.getImplementation();

      ts.reportInfo("int");
      ts.setFunctionNameOrPrefix("putDec(int n)");

#if __SIZEOF_INT__ == 4
      ts.setInputValues("1234567890");

      ts.assertCondition(ti.array[0] == ti.getDefaultChar());

      int sn = 1234567890;
      t.putDec(sn);

      ts.assertCondition(ti.count == 10);
      ts.assertCondition(ti.array[0] == '1');
      ts.assertCondition(ti.array[1] == '2');
      ts.assertCondition(ti.array[2] == '3');
      ts.assertCondition(ti.array[3] == '4');
      ts.assertCondition(ti.array[4] == '5');
      ts.assertCondition(ti.array[5] == '6');
      ts.assertCondition(ti.array[6] == '7');
      ts.assertCondition(ti.array[7] == '8');
      ts.assertCondition(ti.array[8] == '9');
      ts.assertCondition(ti.array[9] == '0');
      ts.assertCondition(ti.array[10] == ti.getDefaultChar());
#else
#error "unsupported sizeof int"
#endif
    }

    {
      TraceBaseCharArray t;
      TraceImplementationCharArray& ti = t.getImplementation();

      ts.reportInfo("int");
      ts.setFunctionNameOrPrefix("putDec(int n)");

#if __SIZEOF_INT__ == 4
      ts.setInputValues("-1234567890");

      ts.assertCondition(ti.array[0] == ti.getDefaultChar());

      int sn = -1234567890;
      t.putDec(sn);

      ts.assertCondition(ti.count == 11);
      ts.assertCondition(ti.array[0] == '-');
      ts.assertCondition(ti.array[1] == '1');
      ts.assertCondition(ti.array[2] == '2');
      ts.assertCondition(ti.array[3] == '3');
      ts.assertCondition(ti.array[4] == '4');
      ts.assertCondition(ti.array[5] == '5');
      ts.assertCondition(ti.array[6] == '6');
      ts.assertCondition(ti.array[7] == '7');
      ts.assertCondition(ti.array[8] == '8');
      ts.assertCondition(ti.array[9] == '9');
      ts.assertCondition(ti.array[10] == '0');
      ts.assertCondition(ti.array[11] == ti.getDefaultChar());
#else
#error "unsupported sizeof int"
#endif
    }

    {
      TraceBaseCharArray t;
      TraceImplementationCharArray& ti = t.getImplementation();

      ts.reportInfo("unsigned int");
      ts.setFunctionNameOrPrefix("putDec(unsigned int n)");

#if __SIZEOF_INT__ == 4
      ts.setInputValues("1234567890");

      ts.assertCondition(ti.array[0] == ti.getDefaultChar());

      unsigned int un = 1234567890;
      t.putDec(un);

      ts.assertCondition(ti.count == 10);
      ts.assertCondition(ti.array[0] == '1');
      ts.assertCondition(ti.array[1] == '2');
      ts.assertCondition(ti.array[2] == '3');
      ts.assertCondition(ti.array[3] == '4');
      ts.assertCondition(ti.array[4] == '5');
      ts.assertCondition(ti.array[5] == '6');
      ts.assertCondition(ti.array[6] == '7');
      ts.assertCondition(ti.array[7] == '8');
      ts.assertCondition(ti.array[8] == '9');
      ts.assertCondition(ti.array[9] == '0');
      ts.assertCondition(ti.array[10] == ti.getDefaultChar());
#else
#error "unsupported sizeof int"
#endif
    }

    {
      TraceBaseCharArray t;
      TraceImplementationCharArray& ti = t.getImplementation();

      ts.reportInfo("long");
      ts.setFunctionNameOrPrefix("putDec(long n)");

#if __SIZEOF_LONG__ == 4
      ts.setInputValues("123456789");

      ts.assertCondition(ti.array[0] == ti.getDefaultChar());

      long sn = 123456789;
      t.putDec(sn);

      ts.assertCondition(ti.count == 9);
      ts.assertCondition(ti.array[0] == '1');
      ts.assertCondition(ti.array[1] == '2');
      ts.assertCondition(ti.array[2] == '3');
      ts.assertCondition(ti.array[3] == '4');
      ts.assertCondition(ti.array[4] == '5');
      ts.assertCondition(ti.array[5] == '6');
      ts.assertCondition(ti.array[6] == '7');
      ts.assertCondition(ti.array[7] == '8');
      ts.assertCondition(ti.array[8] == '9');
      ts.assertCondition(ti.array[9] == ti.getDefaultChar());
#elif __SIZEOF_LONG__ == 8
      ts.setInputValues("1234567890123456789");

      ts.assertCondition(ti.array[0] == ti.getDefaultChar());

      long sn = 1234567890123456789L;
      t.putDec(sn);

      ts.assertCondition(ti.count == 19);
      ts.assertCondition(ti.array[0] == '1');
      ts.assertCondition(ti.array[1] == '2');
      ts.assertCondition(ti.array[2] == '3');
      ts.assertCondition(ti.array[3] == '4');
      ts.assertCondition(ti.array[4] == '5');
      ts.assertCondition(ti.array[5] == '6');
      ts.assertCondition(ti.array[6] == '7');
      ts.assertCondition(ti.array[7] == '8');
      ts.assertCondition(ti.array[8] == '9');
      ts.assertCondition(ti.array[9] == '0');
      ts.assertCondition(ti.array[10] == '1');
      ts.assertCondition(ti.array[11] == '2');
      ts.assertCondition(ti.array[12] == '3');
      ts.assertCondition(ti.array[13] == '4');
      ts.assertCondition(ti.array[14] == '5');
      ts.assertCondition(ti.array[15] == '6');
      ts.assertCondition(ti.array[16] == '7');
      ts.assertCondition(ti.array[17] == '8');
      ts.assertCondition(ti.array[18] == '9');
      ts.assertCondition(ti.array[19] == ti.getDefaultChar());
#else
#error "unsupported sizeof long"
#endif
    }

    {
      TraceBaseCharArray t;
      TraceImplementationCharArray& ti = t.getImplementation();

      ts.reportInfo("long");
      ts.setFunctionNameOrPrefix("putDec(long n)");

#if __SIZEOF_LONG__ == 4
      ts.setInputValues("-123456789");

      ts.assertCondition(ti.array[0] == ti.getDefaultChar());

      long sn = -123456789;
      t.putDec(sn);

      ts.assertCondition(ti.count == 10);
      ts.assertCondition(ti.array[0] == '-');
      ts.assertCondition(ti.array[1] == '1');
      ts.assertCondition(ti.array[2] == '2');
      ts.assertCondition(ti.array[3] == '3');
      ts.assertCondition(ti.array[4] == '4');
      ts.assertCondition(ti.array[5] == '5');
      ts.assertCondition(ti.array[6] == '6');
      ts.assertCondition(ti.array[7] == '7');
      ts.assertCondition(ti.array[8] == '8');
      ts.assertCondition(ti.array[9] == '9');
      ts.assertCondition(ti.array[10] == ti.getDefaultChar());
#elif __SIZEOF_LONG__ == 8
      ts.setInputValues("-1234567890123456789");

      ts.assertCondition(ti.array[0] == ti.getDefaultChar());

      long sn = -1234567890123456789L;
      t.putDec(sn);

      ts.assertCondition(ti.count == 20);
      ts.assertCondition(ti.array[0] == '-');
      ts.assertCondition(ti.array[1] == '1');
      ts.assertCondition(ti.array[2] == '2');
      ts.assertCondition(ti.array[3] == '3');
      ts.assertCondition(ti.array[4] == '4');
      ts.assertCondition(ti.array[5] == '5');
      ts.assertCondition(ti.array[6] == '6');
      ts.assertCondition(ti.array[7] == '7');
      ts.assertCondition(ti.array[8] == '8');
      ts.assertCondition(ti.array[9] == '9');
      ts.assertCondition(ti.array[10] == '0');
      ts.assertCondition(ti.array[11] == '1');
      ts.assertCondition(ti.array[12] == '2');
      ts.assertCondition(ti.array[13] == '3');
      ts.assertCondition(ti.array[14] == '4');
      ts.assertCondition(ti.array[15] == '5');
      ts.assertCondition(ti.array[16] == '6');
      ts.assertCondition(ti.array[17] == '7');
      ts.assertCondition(ti.array[18] == '8');
      ts.assertCondition(ti.array[19] == '9');
      ts.assertCondition(ti.array[20] == ti.getDefaultChar());
#else
#error "unsupported sizeof long"
#endif
    }

    {
      TraceBaseCharArray t;
      TraceImplementationCharArray& ti = t.getImplementation();

      ts.reportInfo("unsigned long");
      ts.setFunctionNameOrPrefix("putDec(unsigned long n)");

#if __SIZEOF_LONG__ == 4
      ts.setInputValues("123456789");

      ts.assertCondition(ti.array[0] == ti.getDefaultChar());

      unsigned long un = 123456789;
      t.putDec(un);

      ts.assertCondition(ti.count == 9);
      ts.assertCondition(ti.array[0] == '1');
      ts.assertCondition(ti.array[1] == '2');
      ts.assertCondition(ti.array[2] == '3');
      ts.assertCondition(ti.array[3] == '4');
      ts.assertCondition(ti.array[4] == '5');
      ts.assertCondition(ti.array[5] == '6');
      ts.assertCondition(ti.array[6] == '7');
      ts.assertCondition(ti.array[7] == '8');
      ts.assertCondition(ti.array[8] == '9');
      ts.assertCondition(ti.array[9] == ti.getDefaultChar());
#elif __SIZEOF_LONG__ == 8
      ts.setInputValues("1234567890123456789");

      ts.assertCondition(ti.array[0] == ti.getDefaultChar());

      unsigned long un = 1234567890123456789L;
      t.putDec(un);

      ts.assertCondition(ti.count == 19);
      ts.assertCondition(ti.array[0] == '1');
      ts.assertCondition(ti.array[1] == '2');
      ts.assertCondition(ti.array[2] == '3');
      ts.assertCondition(ti.array[3] == '4');
      ts.assertCondition(ti.array[4] == '5');
      ts.assertCondition(ti.array[5] == '6');
      ts.assertCondition(ti.array[6] == '7');
      ts.assertCondition(ti.array[7] == '8');
      ts.assertCondition(ti.array[8] == '9');
      ts.assertCondition(ti.array[9] == '0');
      ts.assertCondition(ti.array[10] == '1');
      ts.assertCondition(ti.array[11] == '2');
      ts.assertCondition(ti.array[12] == '3');
      ts.assertCondition(ti.array[13] == '4');
      ts.assertCondition(ti.array[14] == '5');
      ts.assertCondition(ti.array[15] == '6');
      ts.assertCondition(ti.array[16] == '7');
      ts.assertCondition(ti.array[17] == '8');
      ts.assertCondition(ti.array[18] == '9');
      ts.assertCondition(ti.array[19] == ti.getDefaultChar());
#else
#error "unsupported sizeof long"
#endif
    }

}

// ----------------------------------------------------------------------------

void
runTestStringAndAddress();

void
runTestStringAndAddress()
{
  ts.reportInfo("string and address");

    {
      TraceBaseCharArray t;
      TraceImplementationCharArray& ti = t.getImplementation();

      ts.reportInfo("putStringAndAddress");
      ts.setFunctionNameOrPrefix("putStringAndAddress()");

      const char* s = "abc";
      void* ptr = (void*) 0x1234;

      ts.assertCondition(ti.array[0] == ti.getDefaultChar());

      t.putStringAndAddress(s, ptr);

#if __SIZEOF_POINTER__ == 4
      ts.assertCondition(ti.count == 13);
      ts.assertCondition(ti.array[0] == 'a');
      ts.assertCondition(ti.array[1] == 'b');
      ts.assertCondition(ti.array[2] == 'c');
      ts.assertCondition(ti.array[3] == ' ');
      ts.assertCondition(ti.array[4] == '@');
      ts.assertCondition(ti.array[5] == '0');
      ts.assertCondition(ti.array[6] == '0');
      ts.assertCondition(ti.array[7] == '0');
      ts.assertCondition(ti.array[8] == '0');
      ts.assertCondition(ti.array[9] == '1');
      ts.assertCondition(ti.array[10] == '2');
      ts.assertCondition(ti.array[11] == '3');
      ts.assertCondition(ti.array[12] == '4');
      ts.assertCondition(ti.array[13] == ti.getDefaultChar());
#elif __SIZEOF_POINTER__ == 8
      ts.assertCondition(ti.count == 17);
      ts.assertCondition(ti.array[0] == 'a');
      ts.assertCondition(ti.array[1] == 'b');
      ts.assertCondition(ti.array[2] == 'c');
      ts.assertCondition(ti.array[3] == ' ');
      ts.assertCondition(ti.array[4] == '@');
      ts.assertCondition(ti.array[5] == '0');
      ts.assertCondition(ti.array[6] == '0');
      ts.assertCondition(ti.array[7] == '0');
      ts.assertCondition(ti.array[8] == '0');
      ts.assertCondition(ti.array[9] == '0');
      ts.assertCondition(ti.array[10] == '0');
      ts.assertCondition(ti.array[11] == '0');
      ts.assertCondition(ti.array[12] == '0');
      ts.assertCondition(ti.array[13] == '0');
      ts.assertCondition(ti.array[14] == '0');
      ts.assertCondition(ti.array[15] == '0');
      ts.assertCondition(ti.array[16] == '0');
      ts.assertCondition(ti.array[17] == '1');
      ts.assertCondition(ti.array[18] == '2');
      ts.assertCondition(ti.array[19] == '3');
      ts.assertCondition(ti.array[20] == '4');
      ts.assertCondition(ti.array[21] == ti.getDefaultChar());
#else
#error "unsupported sizeof pointer"
#endif
    }

}

// ----------------------------------------------------------------------------

int
main(int argc, char* argv[])
{
  // initialise the TestSuite with the process parameters
  ts.processMainParameters(argc, argv);

  // mark the start of the test suite
  ts.start("portable/diagnostics/tests/src/trace.cpp");

  // identify the class unter tests
  ts.setClassName("os::diag::TraceBase");

  runTestCompile();

  runTestConstructor();

  runTestChars();

  runTestStrings();

  runTestHex();

  runTestDec();

  // mark the stop of the test suite
  ts.stop();

  int retval;
  retval = ts.getExitValue();

#if defined(DEBUG)
  os::diag::trace << __PRETTY_FUNCTION__ << " returns " << retval
      << os::std::endl;
#endif

  // return 0 if there are no failed test cases
  return retval;
}
