//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include "portable/core/include/OS.h"

#include "portable/infrastructure/include/TestSuite.h"

// This test exercises the Mutex class.

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

static os::infra::TestSuiteOstream ts;

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------

#include "portable/core/include/NamedObject.h"
#include "portable/core/include/Scheduler.h"
#include "portable/core/include/Thread.h"
#include "portable/core/include/TimerTicks.h"
#include "portable/core/include/CriticalSections.h"
#include "portable/core/include/Mutex.h"

// ----------------------------------------------------------------------------

#include <sys/time.h>


// ----------------------------------------------------------------------------

namespace thread
{
  namespace mutex
  {

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

    os::core::Mutex m("m1");

#pragma GCC diagnostic pop

    constexpr os::core::timer::ticks_t INTERVAL = 100;

    void f(void);

    void
    f(void)
    {
#if defined(DEBUG)
  os::diag::trace.putString(__PRETTY_FUNCTION__);
  os::diag::trace.putNewLine();
#endif
      os::core::timer::ticks_t t0 = os::timerTicks.getTicks();

      m.lock();

      os::core::timer::ticks_t t1 = os::timerTicks.getTicks();

      m.unlock();

      os::core::timer::ticks_t d = t1-t0 ;
      if (d >= INTERVAL)
        d -= INTERVAL;
      else
        d = (INTERVAL - d);

      //ts << d << os::std::endl;

      ts.setFunctionNameOrPrefix("unlock()");
      ts.assertCondition(d < (INTERVAL/10));
    }


  }
}
void
runTestMutex();

void
runTestMutex()
{
#if defined(DEBUG)
  os::diag::trace.putString(__PRETTY_FUNCTION__);
  os::diag::trace.putNewLine();
#endif

  ts.setClassName("os::core::Mutex");

  os::core::AllocatedStack stack;
  os::core::Thread th1("t1", thread::mutex::f, stack);

  thread::mutex::m.lock();

  th1.start();

  os::timerTicks.sleep(thread::mutex::INTERVAL);

  thread::mutex::m.unlock();

  th1.join();
}

// ----------------------------------------------------------------------------

namespace thread
{
  namespace recursivemutex
  {

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

    os::core::RecursiveMutex rm("rm1");

#pragma GCC diagnostic pop

    constexpr os::core::timer::ticks_t INTERVAL = 100;

    void f(void);

    void
    f(void)
    {
#if defined(DEBUG)
  os::diag::trace.putString(__PRETTY_FUNCTION__);
  os::diag::trace.putNewLine();
#endif
      os::core::timer::ticks_t t0 = os::timerTicks.getTicks();

      rm.lock();

      os::core::timer::ticks_t t1 = os::timerTicks.getTicks();

      rm.unlock();

      os::core::timer::ticks_t d = t1-t0 ;
      if (d >= INTERVAL)
        d -= INTERVAL;
      else
        d = (INTERVAL - d);

      //ts << d << os::std::endl;

      ts.setFunctionNameOrPrefix("unlock()");
      ts.assertCondition(d < (INTERVAL/10));
    }

  }
}
void
runTestRecursiveMutex();

void
runTestRecursiveMutex()
{
#if defined(DEBUG)
  os::diag::trace.putString(__PRETTY_FUNCTION__);
  os::diag::trace.putNewLine();
#endif

  ts.setClassName("os::core::RecursiveMutex");

  os::core::AllocatedStack stack;
  os::core::Thread th1("tr1", thread::recursivemutex::f, stack);

  // first lock
  thread::recursivemutex::rm.lock();

  th1.start();

  os::timerTicks.sleep(thread::recursivemutex::INTERVAL/3);

  // second lock
  thread::recursivemutex::rm.lock();

  os::timerTicks.sleep(thread::recursivemutex::INTERVAL/3);

  // first unlock
  thread::recursivemutex::rm.unlock();

  os::timerTicks.sleep(thread::recursivemutex::INTERVAL/3);

  // second unlock
  thread::recursivemutex::rm.unlock();

  th1.join();
}

// ----------------------------------------------------------------------------

int
main(int argc, char* argv[])
{
  // instantiate the TestSuite, passing the process parameters
  ts.processMainParameters(argc, argv);

  // mark the start of the test suite
  ts.start("portable/core/tests/src/mutex.cpp");

  os::scheduler.start();

  runTestMutex();

  runTestRecursiveMutex();

  os::scheduler.stop();

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

