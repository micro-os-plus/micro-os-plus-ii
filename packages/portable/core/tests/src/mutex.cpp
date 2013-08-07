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

int
computeAbsoluteProcent(os::core::timer::ticks_t beginTs,
    os::core::timer::ticks_t endTs, os::core::timer::ticks_t interval);

int
computeAbsoluteProcent(os::core::timer::ticks_t beginTs,
    os::core::timer::ticks_t endTs, os::core::timer::ticks_t interval)
{
  os::core::timer::ticks_t d = endTs - beginTs;

  if (d >= interval)
    d -= interval;
  else
    d = (interval - d);

  int proc = (int)((d * 100 + interval / 2) / interval);

  return proc;
}

namespace thread
{
  namespace mutex
  {

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

    os::core::Mutex m1("m1");

    os::core::Mutex m2("m2");

#pragma GCC diagnostic pop

    constexpr os::core::timer::ticks_t INTERVAL = 100;

    void
    f(void);

    void
    f(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString(__PRETTY_FUNCTION__);
      os::diag::trace.putNewLine();
#endif
      os::core::timer::ticks_t t0 = os::timerTicks.getTicks();

      m1.lock();

      os::core::timer::ticks_t t1 = os::timerTicks.getTicks();

      m1.unlock();

      int proc = computeAbsoluteProcent(t0, t1, INTERVAL);
      //ts << d << os::std::endl;

      ts.setFunctionNameOrPrefix("lock()");
      ts.assertCondition(proc < 10);
    }

    void
    fTry(void);

    void
    fTry(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString(__PRETTY_FUNCTION__);
      os::diag::trace.putNewLine();
#endif
      os::core::timer::ticks_t t0 = os::timerTicks.getTicks();

      while (!m2.tryLock())
        os::timerTicks.sleep(1);

      os::core::timer::ticks_t t1 = os::timerTicks.getTicks();

      m2.unlock();

      int proc = computeAbsoluteProcent(t0, t1, INTERVAL);
      //ts << d << os::std::endl;

      ts.setFunctionNameOrPrefix("tryLock()");
      ts.assertCondition(proc < 10);
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

    {
      os::core::AllocatedStack stack;
      os::core::Thread th1("t1", thread::mutex::f, stack);

      thread::mutex::m1.lock();

      th1.start();

      os::timerTicks.sleep(thread::mutex::INTERVAL);

      thread::mutex::m1.unlock();

      th1.join();
    }

    {
      os::core::AllocatedStack stack;
      os::core::Thread th2("t2", thread::mutex::fTry, stack);

      thread::mutex::m2.lock();

      th2.start();

      os::timerTicks.sleep(thread::mutex::INTERVAL);

      thread::mutex::m2.unlock();

      th2.join();
    }

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

    os::core::RecursiveMutex rm1("rm1");

    os::core::RecursiveMutex rm2("rm2");

#pragma GCC diagnostic pop

    constexpr os::core::timer::ticks_t INTERVAL = 100;

    void
    f(void);

    void
    f(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString(__PRETTY_FUNCTION__);
      os::diag::trace.putNewLine();
#endif
      os::core::timer::ticks_t t0 = os::timerTicks.getTicks();

      rm1.lock();

      os::core::timer::ticks_t t1 = os::timerTicks.getTicks();

      rm1.unlock();

      int proc = computeAbsoluteProcent(t0, t1, INTERVAL);
      //ts << d << os::std::endl;

      ts.setFunctionNameOrPrefix("lock()");
      ts.assertCondition(proc < 10);
    }

    void
    fTry(void);

    void
    fTry(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString(__PRETTY_FUNCTION__);
      os::diag::trace.putNewLine();
#endif
      os::core::timer::ticks_t t0 = os::timerTicks.getTicks();

      while (!rm2.tryLock())
        os::timerTicks.sleep(1);

      os::core::timer::ticks_t t1 = os::timerTicks.getTicks();

      rm2.unlock();

      int proc = computeAbsoluteProcent(t0, t1, INTERVAL);
      //ts << d << " " << proc << os::std::endl;

      ts.setFunctionNameOrPrefix("tryLock()");
      ts.assertCondition(proc < 10);
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

    {
      os::core::AllocatedStack stack;
      os::core::Thread th1("tr1", thread::recursivemutex::f, stack);

      // first lock
      thread::recursivemutex::rm1.lock();

      th1.start();

      os::timerTicks.sleep(thread::recursivemutex::INTERVAL / 3);

      // second lock
      thread::recursivemutex::rm1.lock();

      os::timerTicks.sleep(thread::recursivemutex::INTERVAL / 3);

      // first unlock
      thread::recursivemutex::rm1.unlock();

      os::timerTicks.sleep(thread::recursivemutex::INTERVAL / 3);

      // second unlock
      thread::recursivemutex::rm1.unlock();

      th1.join();
    }

    {
      os::core::AllocatedStack stack;
      os::core::Thread th2("tr2", thread::recursivemutex::fTry, stack);

      // first lock
      thread::recursivemutex::rm2.lock();

      th2.start();

      os::timerTicks.sleep(thread::recursivemutex::INTERVAL / 3);

      // second lock
      thread::recursivemutex::rm2.lock();

      os::timerTicks.sleep(thread::recursivemutex::INTERVAL / 3);

      // first unlock
      thread::recursivemutex::rm2.unlock();

      os::timerTicks.sleep(thread::recursivemutex::INTERVAL / 3);

      // second unlock
      thread::recursivemutex::rm2.unlock();

      th2.join();
    }

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

