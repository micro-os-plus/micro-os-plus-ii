//
// This file is part of the µOS++ distribution.
//
// [Original LLVM sources]
//      Copyright (c) 2009-2013 by the contributors listed in
//      'LLVM libcxx Credits.txt'. See 'LLVM libcxx License.txt' for details.
// [The µOS++ changes]
//      Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/OS.h"

#include "portable/infrastructure/include/TestSuite.h"

// This test exercises the os::std::ostream class.

// It is based on LLVM libcxx/test/input.output/iostream.format/output.stream/*

// ----------------------------------------------------------------------------

// To calibrate this test, first define this macro, to use the system std
// library versions.

// Note: Not all test branches are available when running in the
// host environment.

//#define OS_INCLUDE_STD_CALIBRATION

#if defined(OS_INCLUDE_STD_CALIBRATION)

#include <ostream>
#include "portable/language/cpp/include/type_traits.h"
#include <cstdint>
using namespace std;

#else

#include "portable/language/cpp/include/ostream.h"
#include "portable/language/cpp/include/iomanip.h"
#include "portable/language/cpp/include/cstdint.h"
using namespace os::std;

#endif

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

static os::infra::TestSuite ts;

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

template<class CharT>
  class testbufCharArray : public basic_streambuf<CharT>
  {
    typedef basic_streambuf<CharT> base;

  public:
    testbufCharArray()
    {
      sync_called = 0;
      for (size_t i = 0; i < (sizeof(array) / sizeof(CharT)); ++i)
        array[i] = getDefaultChar();

      array[sizeof(array) - 1] = '\0';
      count = 0;
    }

    virtual
    ~testbufCharArray()
    {
    }

    CharT
    getDefaultChar(void)
    {
      return '*';
    }

    CharT array[100];
    size_t count;

    int sync_called;

  protected:

    virtual typename base::int_type
    overflow(typename base::int_type __c = base::traits_type::eof())
    {
      if (__c != base::traits_type::eof())
        {
          if (count < (sizeof(array) / sizeof(CharT)))
            {
              array[count++] = static_cast<CharT>(__c);
            }
        }
      return __c;
    }

    virtual int
    sync()
    {
      ++sync_called;
      return 0;
    }
  };

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------

void
runTestCompile();

void
runTestCompile()
{
  ostream os((streambuf*) 0);

  uint16_t us16 = 12345;
  os << us16;

  int16_t s16 = 12345;
  os << s16;

  uint32_t us32 = 1234567890;
  os << us32;

  int32_t s32 = 1234567890;
  os << s32;

  uint64_t us64 = 1234567890123456789LL;
  os << us64;

  int64_t s64 = 1234567890123456789LL;
  os << s64;

}

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.format/output.streams/ostream.formatted/ostream.inserters.arithmetic/bool.pass.cpp

void
runTestInsertersBool();

void
runTestInsertersBool()
{
  ts.reportInfo("Test ostream inserters arithmetic bool");

    {
      ts.setFunctionNameOrPrefix("operator<<(bool)");
      ts.setPreconditions("os(0)");

      ostream os((streambuf*) 0);
      bool b = false;
      os << b;
      ts.assertCondition(os.bad());
      ts.assertCondition(os.fail());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(bool)");
      ts.setInputValues("false");

      testbufCharArray<char> sb;
      ostream os(&sb);
      bool b = false;
      os << b;
      //ts.assertCondition(sb.str() == "0");
      ts.assertCondition(sb.count == 1);
      ts.assertCondition(sb.array[0] == '0');
      ts.assertCondition(sb.array[1] == sb.getDefaultChar());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(bool)");
      ts.setInputValues("true");

      testbufCharArray<char> sb;
      ostream os(&sb);
      bool b = true;
      os << b;
      //ts.assertCondition(sb.str() == "1");
      ts.assertCondition(sb.count == 1);
      ts.assertCondition(sb.array[0] == '1');
      ts.assertCondition(sb.array[1] == sb.getDefaultChar());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(bool)");
      ts.setInputValues("true");
      ts.setPreconditions("width(3) right");

      testbufCharArray<char> sb;
      ostream os(&sb);
      bool b = true;
      os.width(3);
      os << b;
      //ts.assertCondition(sb.str() == "1");
      ts.assertCondition(sb.count == 3);
      ts.assertCondition(sb.array[0] == ' ');
      ts.assertCondition(sb.array[1] == ' ');
      ts.assertCondition(sb.array[2] == '1');
      ts.assertCondition(sb.array[3] == sb.getDefaultChar());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(bool)");
      ts.setInputValues("true");
      ts.setPreconditions("width(3) left");

      testbufCharArray<char> sb;
      ostream os(&sb);
      bool b = true;
      os.width(3);
      left(os);
      os << b;
      //ts.assertCondition(sb.str() == "1");
      ts.assertCondition(sb.count == 3);
      ts.assertCondition(sb.array[0] == '1');
      ts.assertCondition(sb.array[1] == ' ');
      ts.assertCondition(sb.array[2] == ' ');
      ts.assertCondition(sb.array[3] == sb.getDefaultChar());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(bool)");
      ts.setInputValues("true");
      ts.setPreconditions("boolalpha()");

      testbufCharArray<char> sb;
      ostream os(&sb);
      boolalpha(os);
      bool b = true;
      os << b;
      //ts.assertCondition(sb.str() == "true");
      ts.assertCondition(sb.count == 4);
      ts.assertCondition(sb.array[0] == 't');
      ts.assertCondition(sb.array[1] == 'r');
      ts.assertCondition(sb.array[2] == 'u');
      ts.assertCondition(sb.array[3] == 'e');
      ts.assertCondition(sb.array[4] == sb.getDefaultChar());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(bool)");
      ts.setInputValues("false");
      ts.setPreconditions("boolalpha()");

      testbufCharArray<char> sb;
      ostream os(&sb);
      boolalpha(os);
      bool b = false;
      os << b;
      //ts.assertCondition(sb.str() == "false");
      ts.assertCondition(sb.count == 5);
      ts.assertCondition(sb.array[0] == 'f');
      ts.assertCondition(sb.array[1] == 'a');
      ts.assertCondition(sb.array[2] == 'l');
      ts.assertCondition(sb.array[3] == 's');
      ts.assertCondition(sb.array[4] == 'e');
      ts.assertCondition(sb.array[5] == sb.getDefaultChar());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(bool)");
      ts.setInputValues("true");
      ts.setPreconditions("boolalpha() width(5) right");

      testbufCharArray<char> sb;
      ostream os(&sb);
      boolalpha(os);
      bool b = true;
      os.width(5);
      os << b;
      //ts.assertCondition(sb.str() == "true");
      ts.assertCondition(sb.count == 5);
      ts.assertCondition(sb.array[0] == ' ');
      ts.assertCondition(sb.array[1] == 't');
      ts.assertCondition(sb.array[2] == 'r');
      ts.assertCondition(sb.array[3] == 'u');
      ts.assertCondition(sb.array[4] == 'e');
      ts.assertCondition(sb.array[5] == sb.getDefaultChar());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(bool)");
      ts.setInputValues("true");
      ts.setPreconditions("boolalpha() width(5) left");

      testbufCharArray<char> sb;
      ostream os(&sb);
      boolalpha(os);
      bool b = true;
      os.width(5);
      left(os);
      os << b;
      //ts.assertCondition(sb.str() == "true");
      ts.assertCondition(sb.count == 5);
      ts.assertCondition(sb.array[0] == 't');
      ts.assertCondition(sb.array[1] == 'r');
      ts.assertCondition(sb.array[2] == 'u');
      ts.assertCondition(sb.array[3] == 'e');
      ts.assertCondition(sb.array[4] == ' ');
      ts.assertCondition(sb.array[5] == sb.getDefaultChar());
    }

}

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.format/output.streams/ostream.formatted/ostream.inserters.arithmetic/short.pass.cpp

void
runTestInsertersShort();

void
runTestInsertersShort()
{
  ts.reportInfo("Test ostream inserters arithmetic short");

    {
      ts.setFunctionNameOrPrefix("operator<<(short)");
      ts.setPreconditions("os(0)");

      ostream os((streambuf*) 0);
      short n = 0;
      os << n;
      ts.assertCondition(os.bad());
      ts.assertCondition(os.fail());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(short)");
      ts.setInputValues("0");

      testbufCharArray<char> sb;
      ostream os(&sb);
      short n = 0;
      os << n;
      ts.assertCondition(sb.count == 1);
      ts.assertCondition(sb.array[0] == '0');
      ts.assertCondition(sb.array[1] == sb.getDefaultChar());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(short)");
      ts.setInputValues("123");

      testbufCharArray<char> sb;
      ostream os(&sb);
      short n = 123;
      os << n;
      ts.assertCondition(sb.count == 3);
      ts.assertCondition(sb.array[0] == '1');
      ts.assertCondition(sb.array[1] == '2');
      ts.assertCondition(sb.array[2] == '3');
      ts.assertCondition(sb.array[3] == sb.getDefaultChar());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(short)");
      ts.setInputValues("123");
      ts.setPreconditions("width(5) right");

      testbufCharArray<char> sb;
      ostream os(&sb);
      short n = 123;
      os.width(5);
      os << n;
      ts.assertCondition(sb.count == 5);
      ts.assertCondition(sb.array[0] == ' ');
      ts.assertCondition(sb.array[1] == ' ');
      ts.assertCondition(sb.array[2] == '1');
      ts.assertCondition(sb.array[3] == '2');
      ts.assertCondition(sb.array[4] == '3');
      ts.assertCondition(sb.array[5] == sb.getDefaultChar());
      ts.assertCondition(os.width() == 0);
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(short)");
      ts.setInputValues("123");
      ts.setPreconditions("showpos width(5) right");

      testbufCharArray<char> sb;
      ostream os(&sb);
      short n = 123;
      os.width(5);
      showpos(os);
      os << n;
      ts.assertCondition(sb.count == 5);
      ts.assertCondition(sb.array[0] == ' ');
      ts.assertCondition(sb.array[1] == '+');
      ts.assertCondition(sb.array[2] == '1');
      ts.assertCondition(sb.array[3] == '2');
      ts.assertCondition(sb.array[4] == '3');
      ts.assertCondition(sb.array[5] == sb.getDefaultChar());
      ts.assertCondition(os.width() == 0);
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(short)");
      ts.setInputValues("123");
      ts.setPreconditions("showpos width(5) intern");

      testbufCharArray<char> sb;
      ostream os(&sb);
      short n = 123;
      os.width(5);
      showpos(os);
      internal(os);
      os << n;
      ts.assertCondition(sb.count == 5);
      ts.assertCondition(sb.array[0] == '+');
      ts.assertCondition(sb.array[1] == ' ');
      ts.assertCondition(sb.array[2] == '1');
      ts.assertCondition(sb.array[3] == '2');
      ts.assertCondition(sb.array[4] == '3');
      ts.assertCondition(sb.array[5] == sb.getDefaultChar());
      ts.assertCondition(os.width() == 0);
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(short)");
      ts.setInputValues("123");
      ts.setPreconditions("width(5) left");

      testbufCharArray<char> sb;
      ostream os(&sb);
      short n = 123;
      os.width(5);
      left(os);
      os << n;
      ts.assertCondition(sb.count == 5);
      ts.assertCondition(sb.array[0] == '1');
      ts.assertCondition(sb.array[1] == '2');
      ts.assertCondition(sb.array[2] == '3');
      ts.assertCondition(sb.array[3] == ' ');
      ts.assertCondition(sb.array[4] == ' ');
      ts.assertCondition(sb.array[5] == sb.getDefaultChar());
      ts.assertCondition(os.width() == 0);
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(short)");
      ts.setInputValues("-123");

      testbufCharArray<char> sb;
      ostream os(&sb);
      short n = -123;
      os << n;
      ts.assertCondition(sb.count == 4);
      ts.assertCondition(sb.array[0] == '-');
      ts.assertCondition(sb.array[1] == '1');
      ts.assertCondition(sb.array[2] == '2');
      ts.assertCondition(sb.array[3] == '3');
      ts.assertCondition(sb.array[4] == sb.getDefaultChar());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(short)");
      ts.setInputValues("-123");
      ts.setPreconditions("width(5) right");

      testbufCharArray<char> sb;
      ostream os(&sb);
      short n = -123;
      os.width(5);
      os << n;
      ts.assertCondition(sb.count == 5);
      ts.assertCondition(sb.array[0] == ' ');
      ts.assertCondition(sb.array[1] == '-');
      ts.assertCondition(sb.array[2] == '1');
      ts.assertCondition(sb.array[3] == '2');
      ts.assertCondition(sb.array[4] == '3');
      ts.assertCondition(sb.array[5] == sb.getDefaultChar());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(short)");
      ts.setInputValues("-123");
      ts.setPreconditions("width(5) left");

      testbufCharArray<char> sb;
      ostream os(&sb);
      short n = -123;
      os.width(5);
      left(os);
      os << n;
      ts.assertCondition(sb.count == 5);
      ts.assertCondition(sb.array[0] == '-');
      ts.assertCondition(sb.array[1] == '1');
      ts.assertCondition(sb.array[2] == '2');
      ts.assertCondition(sb.array[3] == '3');
      ts.assertCondition(sb.array[4] == ' ');
      ts.assertCondition(sb.array[5] == sb.getDefaultChar());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(short)");
      ts.setInputValues("-123");
      ts.setPreconditions("width(5) intern");

      testbufCharArray<char> sb;
      ostream os(&sb);
      short n = -123;
      os.width(5);
      internal(os);
      os << n;
      ts.assertCondition(sb.count == 5);
      ts.assertCondition(sb.array[0] == '-');
      ts.assertCondition(sb.array[1] == ' ');
      ts.assertCondition(sb.array[2] == '1');
      ts.assertCondition(sb.array[3] == '2');
      ts.assertCondition(sb.array[4] == '3');
      ts.assertCondition(sb.array[5] == sb.getDefaultChar());
    }

  // hex
    {
      ts.setFunctionNameOrPrefix("operator<<(short)");
      ts.setInputValues("0x19af");
      ts.setPreconditions("hex");

      testbufCharArray<char> sb;
      ostream os(&sb);
      hex(os);
      short n = 0x19af;
      os << n;
      ts.assertCondition(sb.count == 4);
      ts.assertCondition(sb.array[0] == '1');
      ts.assertCondition(sb.array[1] == '9');
      ts.assertCondition(sb.array[2] == 'a');
      ts.assertCondition(sb.array[3] == 'f');
      ts.assertCondition(sb.array[4] == sb.getDefaultChar());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(short)");
      ts.setInputValues("0x10af");
      ts.setPreconditions("hex width(7) right");

      testbufCharArray<char> sb;
      ostream os(&sb);
      hex(os);
      short n = 0x10af;
      os.width(7);
      showbase(os);
      os << n;
      ts.assertCondition(sb.count == 7);
      ts.assertCondition(sb.array[0] == ' ');
      ts.assertCondition(sb.array[1] == '0');
      ts.assertCondition(sb.array[2] == 'x');
      ts.assertCondition(sb.array[3] == '1');
      ts.assertCondition(sb.array[4] == '0');
      ts.assertCondition(sb.array[5] == 'a');
      ts.assertCondition(sb.array[6] == 'f');
      ts.assertCondition(sb.array[7] == sb.getDefaultChar());
    }

    {
      ts.setFunctionNameOrPrefix("operator<<(short)");
      ts.setInputValues("0x10af");
      ts.setPreconditions("hex width(7) left base upper");

      testbufCharArray<char> sb;
      ostream os(&sb);
      hex(os);
      short n = 0x10af;
      os.width(7);
      left(os);
      showbase(os);
      uppercase(os);
      os << n;
      ts.assertCondition(sb.count == 7);
      ts.assertCondition(sb.array[0] == '0');
      ts.assertCondition(sb.array[1] == 'X');
      ts.assertCondition(sb.array[2] == '1');
      ts.assertCondition(sb.array[3] == '0');
      ts.assertCondition(sb.array[4] == 'A');
      ts.assertCondition(sb.array[5] == 'F');
      ts.assertCondition(sb.array[6] == ' ');
      ts.assertCondition(sb.array[7] == sb.getDefaultChar());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(short)");
      ts.setInputValues("0x123");
      ts.setPreconditions("hex width(5) right");

      testbufCharArray<char> sb;
      ostream os(&sb);
      hex(os);
      short n = 0x0123;
      os.width(5);
      os << n;
      ts.assertCondition(sb.count == 5);
      ts.assertCondition(sb.array[0] == ' ');
      ts.assertCondition(sb.array[1] == ' ');
      ts.assertCondition(sb.array[2] == '1');
      ts.assertCondition(sb.array[3] == '2');
      ts.assertCondition(sb.array[4] == '3');
      ts.assertCondition(sb.array[5] == sb.getDefaultChar());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(short)");
      ts.setInputValues("-10");
      ts.setPreconditions("hex");

      testbufCharArray<char> sb;
      ostream os(&sb);
      hex(os);
      short n = -10;
      os << n;
      ts.assertCondition(sb.count == 4);
      ts.assertCondition(sb.array[0] == 'f');
      ts.assertCondition(sb.array[1] == 'f');
      ts.assertCondition(sb.array[2] == 'f');
      ts.assertCondition(sb.array[3] == '6');
      ts.assertCondition(sb.array[4] == sb.getDefaultChar());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(short)");
      ts.setInputValues("-10");
      ts.setPreconditions("hex width(5) right");

      testbufCharArray<char> sb;
      ostream os(&sb);
      hex(os);
      short n = -10;
      os.width(5);
      os << n;
      ts.assertCondition(sb.count == 5);
      ts.assertCondition(sb.array[0] == ' ');
      ts.assertCondition(sb.array[1] == 'f');
      ts.assertCondition(sb.array[2] == 'f');
      ts.assertCondition(sb.array[3] == 'f');
      ts.assertCondition(sb.array[4] == '6');
      ts.assertCondition(sb.array[5] == sb.getDefaultChar());
    }

  // octal
    {
      ts.setFunctionNameOrPrefix("operator<<(short)");
      ts.setInputValues("0123");
      ts.setPreconditions("oct");

      testbufCharArray<char> sb;
      ostream os(&sb);
      oct(os);
      short n = 0123;
      os << n;
      ts.assertCondition(sb.count == 3);
      ts.assertCondition(sb.array[0] == '1');
      ts.assertCondition(sb.array[1] == '2');
      ts.assertCondition(sb.array[2] == '3');
      ts.assertCondition(sb.array[3] == sb.getDefaultChar());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(short)");
      ts.setInputValues("0123");
      ts.setPreconditions("oct width(5) right");

      testbufCharArray<char> sb;
      ostream os(&sb);
      oct(os);
      short n = 0123;
      os.width(5);
      os << n;
      ts.assertCondition(sb.count == 5);
      ts.assertCondition(sb.array[0] == ' ');
      ts.assertCondition(sb.array[1] == ' ');
      ts.assertCondition(sb.array[2] == '1');
      ts.assertCondition(sb.array[3] == '2');
      ts.assertCondition(sb.array[4] == '3');
      ts.assertCondition(sb.array[5] == sb.getDefaultChar());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(short)");
      ts.setInputValues("0123");
      ts.setPreconditions("oct width(5) left");

      testbufCharArray<char> sb;
      ostream os(&sb);
      oct(os);
      short n = 0123;
      os.width(5);
      left(os);
      os << n;
      ts.assertCondition(sb.count == 5);
      ts.assertCondition(sb.array[0] == '1');
      ts.assertCondition(sb.array[1] == '2');
      ts.assertCondition(sb.array[2] == '3');
      ts.assertCondition(sb.array[3] == ' ');
      ts.assertCondition(sb.array[4] == ' ');
      ts.assertCondition(sb.array[5] == sb.getDefaultChar());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(short)");
      ts.setInputValues("-10");
      ts.setPreconditions("oct");

      testbufCharArray<char> sb;
      ostream os(&sb);
      oct(os);
      short n = -10;
      os << n;
      //ts.assertCondition(sb.str() == "177766");
      ts.assertCondition(sb.count == 6);
      ts.assertCondition(sb.array[0] == '1');
      ts.assertCondition(sb.array[1] == '7');
      ts.assertCondition(sb.array[2] == '7');
      ts.assertCondition(sb.array[3] == '7');
      ts.assertCondition(sb.array[4] == '6');
      ts.assertCondition(sb.array[5] == '6');
      ts.assertCondition(sb.array[6] == sb.getDefaultChar());
    }

  // - temporary, to be deleted after int tests are added
    {
      ts.setFunctionNameOrPrefix("operator<<(int)");
      ts.setInputValues("123");

      testbufCharArray<char> sb;
      ostream os(&sb);
      int n = 123;
      os << n;
      ts.assertCondition(sb.count == 3);
      ts.assertCondition(sb.array[0] == '1');
      ts.assertCondition(sb.array[1] == '2');
      ts.assertCondition(sb.array[2] == '3');
      ts.assertCondition(sb.array[3] == sb.getDefaultChar());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(uint)");
      ts.setInputValues("123");

      testbufCharArray<char> sb;
      ostream os(&sb);
      unsigned int n = 123;
      os << n;
      ts.assertCondition(sb.count == 3);
      ts.assertCondition(sb.array[0] == '1');
      ts.assertCondition(sb.array[1] == '2');
      ts.assertCondition(sb.array[2] == '3');
      ts.assertCondition(sb.array[3] == sb.getDefaultChar());
    }

}

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.format/output.streams/ostream.formatted/ostream.inserters.arithmetic/unsigned short.pass.cpp

void
runTestInsertersUnsignedShort();

void
runTestInsertersUnsignedShort()
{
  ts.reportInfo("Test ostream inserters arithmetic unsigned short");

    {
      ts.setFunctionNameOrPrefix("operator<<(ushort)");
      ts.setPreconditions("os(0)");

      ostream os((streambuf*) 0);
      unsigned short n = 0;
      os << n;
      ts.assertCondition(os.bad());
      ts.assertCondition(os.fail());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(ushort)");
      ts.setInputValues("0");

      testbufCharArray<char> sb;
      ostream os(&sb);
      unsigned short n = 0;
      os << n;
      ts.assertCondition(sb.count == 1);
      ts.assertCondition(sb.array[0] == '0');
      ts.assertCondition(sb.array[1] == sb.getDefaultChar());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(ushort)");
      ts.setInputValues("123");

      testbufCharArray<char> sb;
      ostream os(&sb);
      unsigned short n = 123;
      os << n;
      ts.assertCondition(sb.count == 3);
      ts.assertCondition(sb.array[0] == '1');
      ts.assertCondition(sb.array[1] == '2');
      ts.assertCondition(sb.array[2] == '3');
      ts.assertCondition(sb.array[3] == sb.getDefaultChar());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(ushort)");
      ts.setInputValues("123");
      ts.setPreconditions("width(5) right");

      testbufCharArray<char> sb;
      ostream os(&sb);
      unsigned short n = 123;
      os.width(5);
      os << n;
      ts.assertCondition(sb.count == 5);
      ts.assertCondition(sb.array[0] == ' ');
      ts.assertCondition(sb.array[1] == ' ');
      ts.assertCondition(sb.array[2] == '1');
      ts.assertCondition(sb.array[3] == '2');
      ts.assertCondition(sb.array[4] == '3');
      ts.assertCondition(sb.array[5] == sb.getDefaultChar());
      ts.assertCondition(os.width() == 0);
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(ushort)");
      ts.setInputValues("123");
      ts.setPreconditions("width(5) showpos right");

      testbufCharArray<char> sb;
      ostream os(&sb);
      unsigned short n = 123;
      os.width(5);
      showpos(os);
      os << n;
      ts.assertCondition(sb.count == 5);
      ts.assertCondition(sb.array[0] == ' ');
      ts.assertCondition(sb.array[1] == '+');
      ts.assertCondition(sb.array[2] == '1');
      ts.assertCondition(sb.array[3] == '2');
      ts.assertCondition(sb.array[4] == '3');
      ts.assertCondition(sb.array[5] == sb.getDefaultChar());
      ts.assertCondition(os.width() == 0);
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(ushort)");
      ts.setInputValues("123");
      ts.setPreconditions("width(5) showpos intern");

      testbufCharArray<char> sb;
      ostream os(&sb);
      unsigned short n = 123;
      os.width(5);
      showpos(os);
      internal(os);
      os << n;
      ts.assertCondition(sb.count == 5);
      ts.assertCondition(sb.array[0] == '+');
      ts.assertCondition(sb.array[1] == ' ');
      ts.assertCondition(sb.array[2] == '1');
      ts.assertCondition(sb.array[3] == '2');
      ts.assertCondition(sb.array[4] == '3');
      ts.assertCondition(sb.array[5] == sb.getDefaultChar());
      ts.assertCondition(os.width() == 0);
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(ushort)");
      ts.setInputValues("123");
      ts.setPreconditions("width(5) left");

      testbufCharArray<char> sb;
      ostream os(&sb);
      unsigned short n = 123;
      os.width(5);
      left(os);
      os << n;
      ts.assertCondition(sb.count == 5);
      ts.assertCondition(sb.array[0] == '1');
      ts.assertCondition(sb.array[1] == '2');
      ts.assertCondition(sb.array[2] == '3');
      ts.assertCondition(sb.array[3] == ' ');
      ts.assertCondition(sb.array[4] == ' ');
      ts.assertCondition(sb.array[5] == sb.getDefaultChar());
      ts.assertCondition(os.width() == 0);
    }

  // hex
    {
      ts.setFunctionNameOrPrefix("operator<<(ushort)");
      ts.setInputValues("0x19af");
      ts.setPreconditions("hex");

      testbufCharArray<char> sb;
      ostream os(&sb);
      hex(os);
      unsigned short n = 0x19af;
      os << n;
      ts.assertCondition(sb.count == 4);
      ts.assertCondition(sb.array[0] == '1');
      ts.assertCondition(sb.array[1] == '9');
      ts.assertCondition(sb.array[2] == 'a');
      ts.assertCondition(sb.array[3] == 'f');
      ts.assertCondition(sb.array[4] == sb.getDefaultChar());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(ushort)");
      ts.setInputValues("0x10af");
      ts.setPreconditions("hex width(7) right");

      testbufCharArray<char> sb;
      ostream os(&sb);
      hex(os);
      unsigned short n = 0x10af;
      os.width(7);
      showbase(os);
      os << n;
      ts.assertCondition(sb.count == 7);
      ts.assertCondition(sb.array[0] == ' ');
      ts.assertCondition(sb.array[1] == '0');
      ts.assertCondition(sb.array[2] == 'x');
      ts.assertCondition(sb.array[3] == '1');
      ts.assertCondition(sb.array[4] == '0');
      ts.assertCondition(sb.array[5] == 'a');
      ts.assertCondition(sb.array[6] == 'f');
      ts.assertCondition(sb.array[7] == sb.getDefaultChar());
    }

    {
      ts.setFunctionNameOrPrefix("operator<<(ushort)");
      ts.setInputValues("0x10af");
      ts.setPreconditions("hex width(7) left upper");

      testbufCharArray<char> sb;
      ostream os(&sb);
      hex(os);
      unsigned short n = 0x10af;
      os.width(7);
      left(os);
      showbase(os);
      uppercase(os);
      os << n;
      ts.assertCondition(sb.count == 7);
      ts.assertCondition(sb.array[0] == '0');
      ts.assertCondition(sb.array[1] == 'X');
      ts.assertCondition(sb.array[2] == '1');
      ts.assertCondition(sb.array[3] == '0');
      ts.assertCondition(sb.array[4] == 'A');
      ts.assertCondition(sb.array[5] == 'F');
      ts.assertCondition(sb.array[6] == ' ');
      ts.assertCondition(sb.array[7] == sb.getDefaultChar());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(ushort)");
      ts.setInputValues("0x123");
      ts.setPreconditions("hex width(5) right");

      testbufCharArray<char> sb;
      ostream os(&sb);
      hex(os);
      unsigned short n = 0x0123;
      os.width(5);
      os << n;
      ts.assertCondition(sb.count == 5);
      ts.assertCondition(sb.array[0] == ' ');
      ts.assertCondition(sb.array[1] == ' ');
      ts.assertCondition(sb.array[2] == '1');
      ts.assertCondition(sb.array[3] == '2');
      ts.assertCondition(sb.array[4] == '3');
      ts.assertCondition(sb.array[5] == sb.getDefaultChar());
    }

  // octal
    {
      ts.setFunctionNameOrPrefix("operator<<(ushort)");
      ts.setInputValues("0123");
      ts.setPreconditions("oct");

      testbufCharArray<char> sb;
      ostream os(&sb);
      oct(os);
      unsigned short n = 0123;
      os << n;
      ts.assertCondition(sb.count == 3);
      ts.assertCondition(sb.array[0] == '1');
      ts.assertCondition(sb.array[1] == '2');
      ts.assertCondition(sb.array[2] == '3');
      ts.assertCondition(sb.array[3] == sb.getDefaultChar());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(ushort)");
      ts.setInputValues("0123");
      ts.setPreconditions("oct width(5) right");

      testbufCharArray<char> sb;
      ostream os(&sb);
      oct(os);
      unsigned short n = 0123;
      os.width(5);
      os << n;
      ts.assertCondition(sb.count == 5);
      ts.assertCondition(sb.array[0] == ' ');
      ts.assertCondition(sb.array[1] == ' ');
      ts.assertCondition(sb.array[2] == '1');
      ts.assertCondition(sb.array[3] == '2');
      ts.assertCondition(sb.array[4] == '3');
      ts.assertCondition(sb.array[5] == sb.getDefaultChar());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(ushort)");
      ts.setInputValues("0123");
      ts.setPreconditions("oct width(5) left");

      testbufCharArray<char> sb;
      ostream os(&sb);
      oct(os);
      unsigned short n = 0123;
      os.width(5);
      left(os);
      os << n;
      ts.assertCondition(sb.count == 5);
      ts.assertCondition(sb.array[0] == '1');
      ts.assertCondition(sb.array[1] == '2');
      ts.assertCondition(sb.array[2] == '3');
      ts.assertCondition(sb.array[3] == ' ');
      ts.assertCondition(sb.array[4] == ' ');
      ts.assertCondition(sb.array[5] == sb.getDefaultChar());
    }

}

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.format/output.streams/ostream.formatted/ostream.inserters.arithmetic/pointer.pass.cpp

void
runTestInsertersPointer();

void
runTestInsertersPointer()
{
  ts.reportInfo("Test ostream inserters arithmetic pointer");

    {
      ts.setFunctionNameOrPrefix("operator<<(void*)");
      ts.setPreconditions("os(0)");

      ostream os((streambuf*) 0);
      const void* n = 0;
      os << n;
      ts.assertCondition(os.bad());
      ts.assertCondition(os.fail());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(void*)");
      ts.setInputValues("0");

      testbufCharArray<char> sb;
      ostream os(&sb);
      const void* n = 0;
      os << n;

#if !defined(OS_INCLUDE_STD_CALIBRATION)

#if __SIZEOF_POINTER__ == 8
          ts.assertCondition(sb.count == 18);
          ts.assertCondition(sb.array[0] == '0');
          ts.assertCondition(sb.array[1] == 'x');
          ts.assertCondition(sb.array[2] == '0');
          ts.assertCondition(sb.array[3] == '0');
          ts.assertCondition(sb.array[4] == '0');
          ts.assertCondition(sb.array[5] == '0');
          ts.assertCondition(sb.array[6] == '0');
          ts.assertCondition(sb.array[7] == '0');
          ts.assertCondition(sb.array[8] == '0');
          ts.assertCondition(sb.array[9] == '0');
          ts.assertCondition(sb.array[10] == '0');
          ts.assertCondition(sb.array[11] == '0');
          ts.assertCondition(sb.array[12] == '0');
          ts.assertCondition(sb.array[13] == '0');
          ts.assertCondition(sb.array[14] == '0');
          ts.assertCondition(sb.array[15] == '0');
          ts.assertCondition(sb.array[16] == '0');
          ts.assertCondition(sb.array[17] == '0');
          ts.assertCondition(sb.array[18] == sb.getDefaultChar());
#elif __SIZEOF_POINTER__ == 4
          ts.assertCondition(sb.count == 10);
          ts.assertCondition(sb.array[0] == '0');
          ts.assertCondition(sb.array[1] == 'x');
          ts.assertCondition(sb.array[2] == '0');
          ts.assertCondition(sb.array[3] == '0');
          ts.assertCondition(sb.array[4] == '0');
          ts.assertCondition(sb.array[5] == '0');
          ts.assertCondition(sb.array[6] == '0');
          ts.assertCondition(sb.array[7] == '0');
          ts.assertCondition(sb.array[8] == '0');
          ts.assertCondition(sb.array[9] == '0');
          ts.assertCondition(sb.array[10] == sb.getDefaultChar());
#elif __SIZEOF_POINTER__ == 2
          ts.assertCondition(sb.count == 6);
          ts.assertCondition(sb.array[0] == '0');
          ts.assertCondition(sb.array[1] == 'x');
          ts.assertCondition(sb.array[2] == '0');
          ts.assertCondition(sb.array[3] == '0');
          ts.assertCondition(sb.array[4] == '0');
          ts.assertCondition(sb.array[5] == '0');
          ts.assertCondition(sb.array[6] == sb.getDefaultChar());
#endif

#else
      debug.putString(sb.array);
      debug.putNewLine();
#endif
      ts.assertCondition(os.good());
    }
    {
      ts.setFunctionNameOrPrefix("operator<<(void*)");
      ts.setInputValues("&");

      testbufCharArray<char> sb;
      ostream os(&sb);
      const void* n = &sb;
      os << n;
#if !defined(OS_INCLUDE_STD_CALIBRATION)

#if __SIZEOF_POINTER__ == 8
      ts.assertCondition(sb.count == 18);
      ts.assertCondition(sb.array[0] == '0');
      ts.assertCondition(sb.array[1] == 'x');
      ts.assertCondition(sb.array[2] != sb.getDefaultChar());
      ts.assertCondition(sb.array[3] != sb.getDefaultChar());
      ts.assertCondition(sb.array[4] != sb.getDefaultChar());
      ts.assertCondition(sb.array[5] != sb.getDefaultChar());
      ts.assertCondition(sb.array[6] != sb.getDefaultChar());
      ts.assertCondition(sb.array[7] != sb.getDefaultChar());
      ts.assertCondition(sb.array[8] != sb.getDefaultChar());
      ts.assertCondition(sb.array[9] != sb.getDefaultChar());
      ts.assertCondition(sb.array[10] != sb.getDefaultChar());
      ts.assertCondition(sb.array[11] != sb.getDefaultChar());
      ts.assertCondition(sb.array[12] != sb.getDefaultChar());
      ts.assertCondition(sb.array[13] != sb.getDefaultChar());
      ts.assertCondition(sb.array[14] != sb.getDefaultChar());
      ts.assertCondition(sb.array[15] != sb.getDefaultChar());
      ts.assertCondition(sb.array[16] != sb.getDefaultChar());
      ts.assertCondition(sb.array[17] != sb.getDefaultChar());
      ts.assertCondition(sb.array[18] == sb.getDefaultChar());
#elif __SIZEOF_POINTER__ == 4
      ts.assertCondition(sb.count == 10);
      ts.assertCondition(sb.array[0] == '0');
      ts.assertCondition(sb.array[1] == 'x');
      ts.assertCondition(sb.array[2] != sb.getDefaultChar());
      ts.assertCondition(sb.array[3] != sb.getDefaultChar());
      ts.assertCondition(sb.array[4] != sb.getDefaultChar());
      ts.assertCondition(sb.array[5] != sb.getDefaultChar());
      ts.assertCondition(sb.array[6] != sb.getDefaultChar());
      ts.assertCondition(sb.array[7] != sb.getDefaultChar());
      ts.assertCondition(sb.array[8] != sb.getDefaultChar());
      ts.assertCondition(sb.array[9] != sb.getDefaultChar());
      ts.assertCondition(sb.array[10] == sb.getDefaultChar());
#elif __SIZEOF_POINTER__ == 2
      ts.assertCondition(sb.count == 6);
      ts.assertCondition(sb.array[0] == '0');
      ts.assertCondition(sb.array[1] == 'x');
      ts.assertCondition(sb.array[2] != sb.getDefaultChar());
      ts.assertCondition(sb.array[3] != sb.getDefaultChar());
      ts.assertCondition(sb.array[4] != sb.getDefaultChar());
      ts.assertCondition(sb.array[5] != sb.getDefaultChar());
      ts.assertCondition(sb.array[6] == sb.getDefaultChar());
#endif
#else
      debug.putString(sb.array);
      debug.putNewLine();
#endif
      ts.assertCondition(os.good());
    }

}

// ============================================================================

int
main(int argc, char* argv[])
{
  // instantiate the TestSuite, passing the process parameters
  ts.processMainParameters(argc, argv);

  // mark the start of the test suite
  ts.start("portable/language/cpp/tests/src/ostreamConversions.cpp");

  // identify the class under tests
#ifdef OS_INCLUDE_STD_CALIBRATION
  ts.setClassName("std::ostream");
  ts.reportInfo("calibration run");
#else
  ts.setClassName("os::std::ostream");
#endif

  runTestCompile();

  runTestInsertersBool();

  runTestInsertersShort();

  runTestInsertersUnsignedShort();

  runTestInsertersPointer();

  // mark the stop of the test suite
  ts.stop();

  int retval;
  retval = ts.getExitValue();

#if defined(DEBUG)
  os::diag::trace << __PRETTY_FUNCTION__ << " returns " << os::std::dec
      << retval << os::std::endl;
#endif

  // return 0 if there are no failed test cases
  return retval;
}

// ============================================================================
