
#include "portable/core/include/OS.h"

#include "portable/infrastructure/include/TestSuite.h"

#include "portable/diagnostics/include/Trace.h"

int
main(int argc, char* argv[])
{
  // instantiate the TestSuite, passing the process parameters
  os::infra::TestSuite_t ts(argc, argv);

  // identify the class unter tests
  ts.setClassName("os::diag::Trace");

  // mark the start of the test suite
  ts.start(__FILE__);

  ts.reportPassed("a passed test");

  {
    os::diag::TraceBase_t trace;

#if defined(OS_INCLUDE_PORTABLE_DIAGNOSTICS_TRACE_OSTREAM_BASE)
    trace << "Baburiba" << os::std::endl;
#endif
    trace.putString("Hey ");
    trace.putDec(-12345);
    trace.putChar(' ');
    trace.putHex((unsigned int)0x1234567);

    const unsigned char ustr[] = " unsigned char* ";
    trace.putString(ustr);

    trace.putNewLine();

#if defined(OS_INCLUDE_PORTABLE_DIAGNOSTICS_TRACE_OSTREAM_BASE)
    os::diag::trace << "HeyHey " << 123 << os::std::endl;
#endif
  }

  // mark the stop of the test suite
  ts.stop(__FILE__);

  int retval;
  retval = ts.getExitValue();

#if defined(OS_INCLUDE_PORTABLE_DIAGNOSTICS_TRACE_OSTREAM_BASE)
  os::diag::trace << __PRETTY_FUNCTION__ << " returns " << retval << os::std::endl;
#else
  os::diag::trace.putString(__PRETTY_FUNCTION__);
  os::diag::trace.putString(" returns ");
  os::diag::trace.putDec(retval);
  os::diag::trace.putNewLine();
#endif

  // return 0 if there are no failed test cases
  return retval;
}
