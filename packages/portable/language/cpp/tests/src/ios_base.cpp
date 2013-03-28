// -*- C++ -*-

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

// This test exercises the os::std::ios_base class.

// It is based on LLVM libcxx/test/input.output/iostream.base/ios.base/*

// ----------------------------------------------------------------------------

// To calibrate this test, first define this macro, to use the system std
// library versions.

// Note: Not all test branches are available when running in the
// host environment.

//#define OS_INCLUDE_STD_CALIBRATION

#ifdef OS_INCLUDE_STD_CALIBRATION

#include <ios>
using namespace std;

#else

#include "portable/language/cpp/include/ios.h"
#include "portable/language/cpp/include/streambuf.h"
using namespace os::std;

#endif

// ----------------------------------------------------------------------------

//#include "portable/language/cpp/include/type_traits.h"

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

os::infra::TestSuite_t ts;

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.base/stream.types/streamsize.pass.cpp

void
runTestStreamsizeTypes();

void
runTestStreamsizeTypes()
{
  ts.reportInfo("Test ios_base streamsize definitions");
    {
      ts.setFunctionNameOrPrefix("streamsize");

      ts.assertCondition((os::std::is_integral<streamsize>::value));
      ts.assertCondition((os::std::is_signed<streamsize>::value));
    }
}

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.base/ios.base/ios.types/ios_fmtflags/fmtflags.pass.cpp

void
runTestFmtflagsDefinitions();

void
runTestFmtflagsDefinitions()
{
  ts.reportInfo("Test ios_base fmtflags definitions");
    {
      ts.setFunctionNameOrPrefix("fmtflags");

      // Test if each of these flags is non zero
      ts.assertCondition(ios_base::boolalpha != 0);
      ts.assertCondition(ios_base::dec != 0);
      ts.assertCondition(ios_base::fixed != 0);
      ts.assertCondition(ios_base::hex != 0);
      ts.assertCondition(ios_base::internal != 0);
      ts.assertCondition(ios_base::left != 0);
      ts.assertCondition(ios_base::oct != 0);
      ts.assertCondition(ios_base::right != 0);
      ts.assertCondition(ios_base::scientific != 0);
      ts.assertCondition(ios_base::showbase != 0);
      ts.assertCondition(ios_base::showpoint != 0);
      ts.assertCondition(ios_base::showpos != 0);
      ts.assertCondition(ios_base::skipws != 0);
      ts.assertCondition(ios_base::unitbuf != 0);
      ts.assertCondition(ios_base::uppercase != 0);

      // Test if all are different (test each pair)
      ts.assertCondition(ios_base::boolalpha != ios_base::dec);
      ts.assertCondition(ios_base::boolalpha != ios_base::fixed);
      ts.assertCondition(ios_base::boolalpha != ios_base::hex);
      ts.assertCondition(ios_base::boolalpha != ios_base::internal);
      ts.assertCondition(ios_base::boolalpha != ios_base::left);
      ts.assertCondition(ios_base::boolalpha != ios_base::oct);
      ts.assertCondition(ios_base::boolalpha != ios_base::right);
      ts.assertCondition(ios_base::boolalpha != ios_base::scientific);
      ts.assertCondition(ios_base::boolalpha != ios_base::showbase);
      ts.assertCondition(ios_base::boolalpha != ios_base::showpoint);
      ts.assertCondition(ios_base::boolalpha != ios_base::showpos);
      ts.assertCondition(ios_base::boolalpha != ios_base::skipws);
      ts.assertCondition(ios_base::boolalpha != ios_base::unitbuf);
      ts.assertCondition(ios_base::boolalpha != ios_base::uppercase);

      ts.assertCondition(ios_base::dec != ios_base::fixed);
      ts.assertCondition(ios_base::dec != ios_base::hex);
      ts.assertCondition(ios_base::dec != ios_base::internal);
      ts.assertCondition(ios_base::dec != ios_base::left);
      ts.assertCondition(ios_base::dec != ios_base::oct);
      ts.assertCondition(ios_base::dec != ios_base::right);
      ts.assertCondition(ios_base::dec != ios_base::scientific);
      ts.assertCondition(ios_base::dec != ios_base::showbase);
      ts.assertCondition(ios_base::dec != ios_base::showpoint);
      ts.assertCondition(ios_base::dec != ios_base::showpos);
      ts.assertCondition(ios_base::dec != ios_base::skipws);
      ts.assertCondition(ios_base::dec != ios_base::unitbuf);
      ts.assertCondition(ios_base::dec != ios_base::uppercase);

      ts.assertCondition(ios_base::fixed != ios_base::hex);
      ts.assertCondition(ios_base::fixed != ios_base::internal);
      ts.assertCondition(ios_base::fixed != ios_base::left);
      ts.assertCondition(ios_base::fixed != ios_base::oct);
      ts.assertCondition(ios_base::fixed != ios_base::right);
      ts.assertCondition(ios_base::fixed != ios_base::scientific);
      ts.assertCondition(ios_base::fixed != ios_base::showbase);
      ts.assertCondition(ios_base::fixed != ios_base::showpoint);
      ts.assertCondition(ios_base::fixed != ios_base::showpos);
      ts.assertCondition(ios_base::fixed != ios_base::skipws);
      ts.assertCondition(ios_base::fixed != ios_base::unitbuf);
      ts.assertCondition(ios_base::fixed != ios_base::uppercase);

      ts.assertCondition(ios_base::hex != ios_base::internal);
      ts.assertCondition(ios_base::hex != ios_base::left);
      ts.assertCondition(ios_base::hex != ios_base::oct);
      ts.assertCondition(ios_base::hex != ios_base::right);
      ts.assertCondition(ios_base::hex != ios_base::scientific);
      ts.assertCondition(ios_base::hex != ios_base::showbase);
      ts.assertCondition(ios_base::hex != ios_base::showpoint);
      ts.assertCondition(ios_base::hex != ios_base::showpos);
      ts.assertCondition(ios_base::hex != ios_base::skipws);
      ts.assertCondition(ios_base::hex != ios_base::unitbuf);
      ts.assertCondition(ios_base::hex != ios_base::uppercase);

      ts.assertCondition(ios_base::internal != ios_base::left);
      ts.assertCondition(ios_base::internal != ios_base::oct);
      ts.assertCondition(ios_base::internal != ios_base::right);
      ts.assertCondition(ios_base::internal != ios_base::scientific);
      ts.assertCondition(ios_base::internal != ios_base::showbase);
      ts.assertCondition(ios_base::internal != ios_base::showpoint);
      ts.assertCondition(ios_base::internal != ios_base::showpos);
      ts.assertCondition(ios_base::internal != ios_base::skipws);
      ts.assertCondition(ios_base::internal != ios_base::unitbuf);
      ts.assertCondition(ios_base::internal != ios_base::uppercase);

      ts.assertCondition(ios_base::left != ios_base::oct);
      ts.assertCondition(ios_base::left != ios_base::right);
      ts.assertCondition(ios_base::left != ios_base::scientific);
      ts.assertCondition(ios_base::left != ios_base::showbase);
      ts.assertCondition(ios_base::left != ios_base::showpoint);
      ts.assertCondition(ios_base::left != ios_base::showpos);
      ts.assertCondition(ios_base::left != ios_base::skipws);
      ts.assertCondition(ios_base::left != ios_base::unitbuf);
      ts.assertCondition(ios_base::left != ios_base::uppercase);

      ts.assertCondition(ios_base::oct != ios_base::right);
      ts.assertCondition(ios_base::oct != ios_base::scientific);
      ts.assertCondition(ios_base::oct != ios_base::showbase);
      ts.assertCondition(ios_base::oct != ios_base::showpoint);
      ts.assertCondition(ios_base::oct != ios_base::showpos);
      ts.assertCondition(ios_base::oct != ios_base::skipws);
      ts.assertCondition(ios_base::oct != ios_base::unitbuf);
      ts.assertCondition(ios_base::oct != ios_base::uppercase);

      ts.assertCondition(ios_base::right != ios_base::scientific);
      ts.assertCondition(ios_base::right != ios_base::showbase);
      ts.assertCondition(ios_base::right != ios_base::showpoint);
      ts.assertCondition(ios_base::right != ios_base::showpos);
      ts.assertCondition(ios_base::right != ios_base::skipws);
      ts.assertCondition(ios_base::right != ios_base::unitbuf);
      ts.assertCondition(ios_base::right != ios_base::uppercase);

      ts.assertCondition(ios_base::scientific != ios_base::showbase);
      ts.assertCondition(ios_base::scientific != ios_base::showpoint);
      ts.assertCondition(ios_base::scientific != ios_base::showpos);
      ts.assertCondition(ios_base::scientific != ios_base::skipws);
      ts.assertCondition(ios_base::scientific != ios_base::unitbuf);
      ts.assertCondition(ios_base::scientific != ios_base::uppercase);

      ts.assertCondition(ios_base::showbase != ios_base::showpoint);
      ts.assertCondition(ios_base::showbase != ios_base::showpos);
      ts.assertCondition(ios_base::showbase != ios_base::skipws);
      ts.assertCondition(ios_base::showbase != ios_base::unitbuf);
      ts.assertCondition(ios_base::showbase != ios_base::uppercase);

      ts.assertCondition(ios_base::showpoint != ios_base::showpos);
      ts.assertCondition(ios_base::showpoint != ios_base::skipws);
      ts.assertCondition(ios_base::showpoint != ios_base::unitbuf);
      ts.assertCondition(ios_base::showpoint != ios_base::uppercase);

      ts.assertCondition(ios_base::showpos != ios_base::skipws);
      ts.assertCondition(ios_base::showpos != ios_base::unitbuf);
      ts.assertCondition(ios_base::showpos != ios_base::uppercase);

      ts.assertCondition(ios_base::skipws != ios_base::unitbuf);
      ts.assertCondition(ios_base::skipws != ios_base::uppercase);

      ts.assertCondition(ios_base::unitbuf != ios_base::uppercase);

      ts.assertCondition(ios_base::adjustfield == (ios_base::left
              | ios_base::right
              | ios_base::internal));
      ts.assertCondition(ios_base::basefield == (ios_base::dec
              | ios_base::oct
              | ios_base::hex));
      ts.assertCondition(ios_base::floatfield == (ios_base::scientific
              | ios_base::fixed));
    }
}

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.base/ios.base/ios.types/ios_iostate/iostate.pass.cpp

void
runTestIostateDefinitions();

void
runTestIostateDefinitions()
{
  ts.reportInfo("Test ios_base iostate definitions");
    {
      ts.setFunctionNameOrPrefix("iostate");

      // Test if each of these flags is non zero
      ts.assertCondition(ios_base::badbit != 0);
      ts.assertCondition(ios_base::eofbit != 0);
      ts.assertCondition(ios_base::failbit != 0);
      ts.assertCondition(ios_base::goodbit == 0);

      // Test if all are different (test each pair)
      ts.assertCondition(ios_base::badbit != ios_base::eofbit);
      ts.assertCondition(ios_base::badbit != ios_base::failbit);
      ts.assertCondition(ios_base::eofbit != ios_base::failbit);
    }
}

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.base/ios.base/ios.types/ios_openmode/openmode.pass.cpp

void
runTestOpenmodeDefinitions();

void
runTestOpenmodeDefinitions()
{
  ts.reportInfo("Test ios_base openmode definitions");
    {
      ts.setFunctionNameOrPrefix("openmode");

      // Test if each of these flags is non zero
      ts.assertCondition(ios_base::app != 0);
      ts.assertCondition(ios_base::ate != 0);
      ts.assertCondition(ios_base::binary != 0);
      ts.assertCondition(ios_base::in != 0);
      ts.assertCondition(ios_base::out != 0);
      ts.assertCondition(ios_base::trunc != 0);

      // Test if all are different (test each pair)
      ts.assertCondition(ios_base::app != ios_base::ate);
      ts.assertCondition(ios_base::app != ios_base::binary);
      ts.assertCondition(ios_base::app != ios_base::in);
      ts.assertCondition(ios_base::app != ios_base::out);
      ts.assertCondition(ios_base::app != ios_base::trunc);

      ts.assertCondition(ios_base::ate != ios_base::binary);
      ts.assertCondition(ios_base::ate != ios_base::in);
      ts.assertCondition(ios_base::ate != ios_base::out);
      ts.assertCondition(ios_base::ate != ios_base::trunc);

      ts.assertCondition(ios_base::binary != ios_base::in);
      ts.assertCondition(ios_base::binary != ios_base::out);
      ts.assertCondition(ios_base::binary != ios_base::trunc);

      ts.assertCondition(ios_base::in != ios_base::out);
      ts.assertCondition(ios_base::in != ios_base::trunc);

      ts.assertCondition(ios_base::out != ios_base::trunc);
    }
}

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.base/ios.base/ios.types/ios_seekdir/seekdir.pass.cpp

void
runTestSeekdirDefinitions();

void
runTestSeekdirDefinitions()
{
  ts.reportInfo("Test ios_base seekdir definitions");
    {
      ts.setFunctionNameOrPrefix("seekdir");

      ts.assertCondition(ios_base::beg != ios_base::cur);
      ts.assertCondition(ios_base::beg != ios_base::end);
      ts.assertCondition(ios_base::cur != ios_base::end);
    }
}

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.base/ios.base/fmtflags.state/flags.pass.cpp
// test/input.output/iostream.base/ios.base/fmtflags.state/flags_fmtflags.pass.cpp
// test/input.output/iostream.base/ios.base/fmtflags.state/setf_fmtflags.pass.cpp
// test/input.output/iostream.base/ios.base/fmtflags.state/setf_fmtflags_mask.pass.cpp
// test/input.output/iostream.base/ios.base/fmtflags.state/unsetf_mask.pass.cpp

void
runTestFlags();

void
runTestFlags()
{
#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

  class test : public ios
  {
  public:
    test()
    {
      init(0);
    }
  };

#pragma GCC diagnostic pop

  ts.reportInfo("Test ios_base flags initialisations");
    {
      const test t;

      ts.setFunctionNameOrPrefix("flags()");
      ts.setPreconditions("init(0)");
      ts.assertCondition(t.flags() == (test::skipws | test::dec));
    }

  ts.reportInfo("Test ios_base flags settings");
    {
      test t;

      ts.setFunctionNameOrPrefix("flags(fmtflags)");

      // check initial values set by constructor
      ts.assertCondition(t.flags() == (test::skipws | test::dec));

      // set new values and get old ones
      test::fmtflags oldflags = t.flags(test::hex | test::right);

      // check if old ones are as expected
      ts.assertCondition(oldflags == (test::skipws | test::dec));

      // finally check if the new values were set
      ts.assertCondition(t.flags() == (test::hex | test::right));
    }

  ts.reportInfo("Test ios_base flags OR settings");
    {
      test t;

      ts.setFunctionNameOrPrefix("setf(fmtflags)");

      // check initial values set by constructor
      ts.assertCondition(t.flags() == (test::skipws | test::dec));

      // set new values and get old ones
      test::fmtflags oldflags = t.setf(test::hex | test::right);

      // check if old ones are as expected
      ts.assertCondition(oldflags == (test::skipws | test::dec));

      // finally check if the new values were set
      ts.assertCondition(t.flags() == (test::skipws | test::dec |
              test::hex | test::right));
    }

  ts.reportInfo("Test ios_base flags with mask settings");
    {
      test t;

      ts.setFunctionNameOrPrefix("setf(fmtflags,fmtflags)");

      // check initial values set by constructor
      ts.assertCondition(t.flags() == (test::skipws | test::dec));

      // set new values and get old ones
      test::fmtflags oldflags = t.setf(test::hex | test::right,
          test::dec | test::right);

      // check if old ones are as expected
      ts.assertCondition(oldflags == (test::skipws | test::dec));

      // finally check if the new values were set
      ts.assertCondition(t.flags() == (test::skipws | test::right));
    }

  ts.reportInfo("Test ios_base flags unsettings");
    {
      test t;

      ts.setFunctionNameOrPrefix("unsetf(fmtflags)");

      // check initial values set by constructor
      ts.assertCondition(t.flags() == (test::skipws | test::dec));

      // unset values
      t.unsetf(test::dec | test::right);

      // check if the new values were set
      ts.assertCondition(t.flags() == test::skipws);
    }
}

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.base/ios.base/fmtflags.state/precission.pass.cpp
// test/input.output/iostream.base/ios.base/fmtflags.state/precission_streamsize.pass.cpp

void
runTestPrecision();

void
runTestPrecision()
{
#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

  class test : public ios
  {
  public:
    test()
    {
      init(0);
    }
  };

#pragma GCC diagnostic pop

  ts.reportInfo("Test ios_base precision initialisations");
    {
      const test t;

      ts.setFunctionNameOrPrefix("precision()");
      ts.setPreconditions("init(0)");

      ts.assertCondition(t.precision() == 6);

    }

  ts.reportInfo("Test ios_base precision settings");
    {
      test t;

      ts.setFunctionNameOrPrefix("precision(streamsize)");

      // check initial values set by constructor
      ts.assertCondition(t.precision() == 6);

      // set new values and get old ones
      streamsize oldprecision = t.precision(10);

      // check if old ones are as expected
      ts.assertCondition(oldprecision == 6);

      // finally check if the new values were set
      ts.assertCondition(t.precision() == 10);
    }
}

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.base/ios.base/fmtflags.state/width.pass.cpp
// test/input.output/iostream.base/ios.base/fmtflags.state/width_streamsize.pass.cpp

void
runTestWidth();

void
runTestWidth()
{
#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

  class test : public ios
  {
  public:
    test()
    {
      init(0);
    }
  };

#pragma GCC diagnostic pop

  ts.reportInfo("Test ios_base width initialisations");
    {
      const test t;

      ts.setFunctionNameOrPrefix("width()");
      ts.setPreconditions("init(0)");

      ts.assertCondition(t.width() == 0);

    }

  ts.reportInfo("Test ios_base width settings");
    {
      test t;

      ts.setFunctionNameOrPrefix("width(streamsize)");

      // check initial values set by constructor
      ts.assertCondition(t.width() == 0);

      // set new values and get old ones
      streamsize w = t.width(4);

      // check if old ones are as expected
      ts.assertCondition(w == 0);

      // finally check if the new values were set
      ts.assertCondition(t.width() == 4);
    }
}

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.base/ios.base/ios.members.static/sync_with_stdio.pass.cpp

void
runTestStatic();

void
runTestStatic()
{

  ts.reportInfo("Test ios_base width initialisations");
    {
      ts.setFunctionNameOrPrefix("sync_with_stdio(bool)");

      // The function returns the old value
      ts.assertCondition( ios_base::sync_with_stdio(false));
      ts.assertCondition(!ios_base::sync_with_stdio(false));
      ts.assertCondition(!ios_base::sync_with_stdio(true));
      ts.assertCondition( ios_base::sync_with_stdio(true));
      ts.assertCondition( ios_base::sync_with_stdio());
      ts.assertCondition( ios_base::sync_with_stdio(false));
      ts.assertCondition(!ios_base::sync_with_stdio());
      ts.assertCondition( ios_base::sync_with_stdio());
    }
}

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.base/std.ios.manip/fmtflags.manip/boolalpha.pass.cpp
// test/input.output/iostream.base/std.ios.manip/fmtflags.manip/noboolalpha.pass.cpp
// test/input.output/iostream.base/std.ios.manip/fmtflags.manip/noshowbase.pass.cpp
// test/input.output/iostream.base/std.ios.manip/fmtflags.manip/noshowpoint.pass.cpp
// test/input.output/iostream.base/std.ios.manip/fmtflags.manip/noshowpos.pass.cpp
// test/input.output/iostream.base/std.ios.manip/fmtflags.manip/noskipws.pass.cpp
// test/input.output/iostream.base/std.ios.manip/fmtflags.manip/nounitbuf.pass.cpp
// test/input.output/iostream.base/std.ios.manip/fmtflags.manip/nouppercase.pass.cpp
// test/input.output/iostream.base/std.ios.manip/fmtflags.manip/showbase.pass.cpp
// test/input.output/iostream.base/std.ios.manip/fmtflags.manip/showpoint.pass.cpp
// test/input.output/iostream.base/std.ios.manip/fmtflags.manip/showpos.pass.cpp
// test/input.output/iostream.base/std.ios.manip/fmtflags.manip/skipws.pass.cpp
// test/input.output/iostream.base/std.ios.manip/fmtflags.manip/unitbuf.pass.cpp
// test/input.output/iostream.base/std.ios.manip/fmtflags.manip/uppercase.pass.cpp

void
runTestFmtflagsManip();

void
runTestFmtflagsManip()
{
  class testbuf : public streambuf
  {
  };

  ts.reportInfo("Test ios_base fmtflags manipulators");
    {
      ts.setFunctionNameOrPrefix("boolalpha()");

      testbuf sb;
      ios ios(&sb);
      ios_base& r = boolalpha(ios);
      ts.assertCondition(&r == &ios);
      ts.assertCondition(ios.flags() & ios::boolalpha);
    }

    {
      ts.setFunctionNameOrPrefix("noboolalpha()");

      testbuf sb;
      ios ios(&sb);
      boolalpha(ios);
      ios_base& r = noboolalpha(ios);
      ts.assertCondition(&r == &ios);
      ts.assertCondition(!(ios.flags() & ios::boolalpha));
    }

    {
      ts.setFunctionNameOrPrefix("noshowbase()");

      testbuf sb;
      ios ios(&sb);
      showbase(ios);
      ios_base& r = noshowbase(ios);
      ts.assertCondition(&r == &ios);
      ts.assertCondition(!(ios.flags() & ios::showbase));
    }

    {
      ts.setFunctionNameOrPrefix("noshowpoint()");

      testbuf sb;
      ios ios(&sb);
      showpoint(ios);
      ios_base& r = noshowpoint(ios);
      ts.assertCondition(&r == &ios);
      ts.assertCondition(!(ios.flags() & ios::showpoint));
    }

    {
      ts.setFunctionNameOrPrefix("noshowpos()");

      testbuf sb;
      ios ios(&sb);
      showpos(ios);
      ios_base& r = noshowpos(ios);
      ts.assertCondition(&r == &ios);
      ts.assertCondition(!(ios.flags() & ios::showpos));
    }

    {
      ts.setFunctionNameOrPrefix("noskipws()");

      testbuf sb;
      ios ios(&sb);
      skipws(ios);
      ios_base& r = noskipws(ios);
      ts.assertCondition(&r == &ios);
      ts.assertCondition(!(ios.flags() & ios::skipws));
    }

    {
      ts.setFunctionNameOrPrefix("nounitbuf()");

      testbuf sb;
      ios ios(&sb);
      unitbuf(ios);
      ios_base& r = nounitbuf(ios);
      ts.assertCondition(&r == &ios);
      ts.assertCondition(!(ios.flags() & ios::unitbuf));
    }

    {
      ts.setFunctionNameOrPrefix("nouppercase()");

      testbuf sb;
      ios ios(&sb);
      uppercase(ios);
      ios_base& r = nouppercase(ios);
      ts.assertCondition(&r == &ios);
      ts.assertCondition(!(ios.flags() & ios::uppercase));
    }

    {
      ts.setFunctionNameOrPrefix("showbase()");

      testbuf sb;
      ios ios(&sb);
      ios_base& r = showbase(ios);
      ts.assertCondition(&r == &ios);
      ts.assertCondition(ios.flags() & ios::showbase);
    }

    {
      ts.setFunctionNameOrPrefix("showpoint()");

      testbuf sb;
      ios ios(&sb);
      ios_base& r = showpoint(ios);
      ts.assertCondition(&r == &ios);
      ts.assertCondition(ios.flags() & ios::showpoint);
    }

    {
      ts.setFunctionNameOrPrefix("showpos()");

      testbuf sb;
      ios ios(&sb);
      ios_base& r = showpos(ios);
      ts.assertCondition(&r == &ios);
      ts.assertCondition(ios.flags() & ios::showpos);
    }

    {
      ts.setFunctionNameOrPrefix("skipws()");

      testbuf sb;
      ios ios(&sb);
      ios_base& r = skipws(ios);
      ts.assertCondition(&r == &ios);
      ts.assertCondition(ios.flags() & ios::skipws);
    }

    {
      ts.setFunctionNameOrPrefix("unitbuf()");

      testbuf sb;
      ios ios(&sb);
      ios_base& r = unitbuf(ios);
      ts.assertCondition(&r == &ios);
      ts.assertCondition(ios.flags() & ios::unitbuf);
    }

    {
      ts.setFunctionNameOrPrefix("uppercase()");

      testbuf sb;
      ios ios(&sb);
      ios_base& r = uppercase(ios);
      ts.assertCondition(&r == &ios);
      ts.assertCondition(ios.flags() & ios::uppercase);
    }

}

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.base/std.ios.manip/adjustfield.manip/internal.pass.cpp
// test/input.output/iostream.base/std.ios.manip/adjustfield.manip/left.pass.cpp
// test/input.output/iostream.base/std.ios.manip/adjustfield.manip/right.pass.cpp

void
runTestAdjustfieldManip();

void
runTestAdjustfieldManip()
{
  class testbuf : public streambuf
  {
  };

  ts.reportInfo("Test ios_base adjustfield manipulators");
    {
      ts.setFunctionNameOrPrefix("internal()");

      testbuf sb;
      ios ios(&sb);
      ios_base& r = internal(ios);
      ts.assertCondition(&r == &ios);
      ts.assertCondition(ios.flags() & ios::internal);
    }

    {
      ts.setFunctionNameOrPrefix("left()");

      testbuf sb;
      ios ios(&sb);
      ios_base& r = left(ios);
      ts.assertCondition(&r == &ios);
      ts.assertCondition(ios.flags() & ios::left);
    }

    {
      ts.setFunctionNameOrPrefix("right()");

      testbuf sb;
      ios ios(&sb);
      ios_base& r = right(ios);
      ts.assertCondition(&r == &ios);
      ts.assertCondition(ios.flags() & ios::right);
    }

}

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.base/std.ios.manip/basefield.manip/dec.pass.cpp
// test/input.output/iostream.base/std.ios.manip/basefield.manip/hex.pass.cpp
// test/input.output/iostream.base/std.ios.manip/basefield.manip/right.pass.cpp

void
runTestBasefieldManip();

void
runTestBasefieldManip()
{
  class testbuf : public streambuf
  {
  };

  ts.reportInfo("Test ios_base basefield manipulators");
    {
      ts.setFunctionNameOrPrefix("dec()");

      testbuf sb;
      ios ios(&sb);
      ios_base& r = dec(ios);
      ts.assertCondition(&r == &ios);
      ts.assertCondition(ios.flags() & ios::dec);
    }

    {
      ts.setFunctionNameOrPrefix("hex()");

      testbuf sb;
      ios ios(&sb);
      ios_base& r = hex(ios);
      ts.assertCondition(&r == &ios);
      ts.assertCondition(ios.flags() & ios::hex);
    }

    {
      ts.setFunctionNameOrPrefix("oct()");

      testbuf sb;
      ios ios(&sb);
      ios_base& r = oct(ios);
      ts.assertCondition(&r == &ios);
      ts.assertCondition(ios.flags() & ios::oct);
    }

}

// ----------------------------------------------------------------------------

// inspired from LLVM libcxx
// test/input.output/iostream.base/std.ios.manip/floatfield.manip/fixed.pass.cpp
// test/input.output/iostream.base/std.ios.manip/floatfield.manip/scientific.pass.cpp
// test/input.output/iostream.base/std.ios.manip/floatfield.manip/defaultfloat.pass.cpp
// test/input.output/iostream.base/std.ios.manip/floatfield.manip/defaultfloat.pass.cpp

void
runTestFloatfieldManip();

void
runTestFloatfieldManip()
{
  class testbuf : public streambuf
  {
  };

  ts.reportInfo("Test ios_base floatfield manipulators");
    {
      ts.setFunctionNameOrPrefix("fixed()");

      testbuf sb;
      ios ios(&sb);
      ios_base& r = fixed(ios);
      ts.assertCondition(&r == &ios);
      ts.assertCondition(ios.flags() & ios::fixed);
    }

    {
      ts.setFunctionNameOrPrefix("scientific()");

      testbuf sb;
      ios ios(&sb);
      ios_base& r = scientific(ios);
      ts.assertCondition(&r == &ios);
      ts.assertCondition(ios.flags() & ios::scientific);
    }

    {
      ts.setFunctionNameOrPrefix("defaultfloat()");

      testbuf sb;
      ios ios(&sb);
      ios_base& r = defaultfloat(ios);
      ts.assertCondition(&r == &ios);
      ts.assertCondition(!(ios.flags() & ios::fixed));
      ts.assertCondition(!(ios.flags() & ios::scientific));
    }

    {
      ts.setFunctionNameOrPrefix("hexfloat()");

      testbuf sb;
      ios ios(&sb);
      ios_base& r = hexfloat(ios);
      ts.assertCondition(&r == &ios);
      ts.assertCondition((ios.flags() & ios::fixed));
      ts.assertCondition((ios.flags() & ios::scientific));
    }

}

// ============================================================================

int
main(int argc, char* argv[])
{
  // instantiate the TestSuite, passing the process parameters
  ts.processMainParameters(argc, argv);

  // mark the start of the test suite
  ts.start("portable/language/cpp/tests/src/ios_base.cpp");

  // identify the class under tests
#ifdef OS_INCLUDE_STD_CALIBRATION
  ts.setClassName("std::ios_base");
  ts.reportInfo("calibration run");
#else
  ts.setClassName("os::std::ios_base");
#endif

  runTestStreamsizeTypes();

  runTestFmtflagsDefinitions();

  runTestIostateDefinitions();

  runTestOpenmodeDefinitions();

  runTestSeekdirDefinitions();

  runTestFlags();

  runTestPrecision();

  runTestWidth();

  runTestStatic();

  runTestFmtflagsManip();

  runTestAdjustfieldManip();

  runTestBasefieldManip();

  runTestFloatfieldManip();

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
