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
#include "portable/core/include/MainThread.h"

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
  os::core::timer::ticks_t delta = endTs - beginTs;

  os::core::timer::ticks_t abs;

  // compute abs(d-interval)
  if (delta >= interval)
    abs = delta - interval;
  else
    abs = (interval - delta);

  int proc = (int) ((abs * 100 + interval / 2) / interval);

#if 0
  ts << endTs << "-" << beginTs << "=" << delta << " abs=" << abs << " " << proc
      << "% of " << interval << os::std::endl;
#endif

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

    os::core::Mutex m3("m3");

    os::core::Mutex m4("m4");

#pragma GCC diagnostic pop

    constexpr os::core::timer::ticks_t INTERVAL = 100;

    constexpr os::core::timer::ticks_t INTERVAL_SHORT = 100;
    constexpr os::core::timer::ticks_t INTERVAL_LONG = INTERVAL_SHORT + 50;

    void
    fLock(void);

    void
    fLock(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString(__PRETTY_FUNCTION__);
      os::diag::trace.putNewLine();
#endif
      os::core::timer::ticks_t t0 = os::timerTicks.getCurrentTicks();

      m1.lock();

      os::core::timer::ticks_t t1 = os::timerTicks.getCurrentTicks();

      m1.unlock();

      int proc = computeAbsoluteProcent(t0, t1, INTERVAL);

      ts.setFunctionNameOrPrefix("lock()");
      ts.assertCondition(proc < 10);
    }

    void
    fTryLock(void);

    void
    fTryLock(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString(__PRETTY_FUNCTION__);
      os::diag::trace.putNewLine();
#endif
      os::core::timer::ticks_t t0 = os::timerTicks.getCurrentTicks();

      // initially should not lock
      ts.assertCondition(m2.tryLock() == false);
      ts.assertCondition(m2.tryLock() == false);

      os::core::Thread* thread = os::scheduler.getCurrentThread();

      while (!m2.tryLock())
      {
        thread->sleepFor(1);
      }
      os::core::timer::ticks_t t1 = os::timerTicks.getCurrentTicks();

      m2.unlock();

      int proc = computeAbsoluteProcent(t0, t1, INTERVAL);

      ts.setFunctionNameOrPrefix("tryLock()");
      ts.assertCondition(proc < 10);
    }

    void
    fTryForNoTimeout(void);

    void
    fTryForNoTimeout(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString(__PRETTY_FUNCTION__);
      os::diag::trace.putNewLine();
#endif
      os::core::timer::ticks_t t0 = os::timerTicks.getCurrentTicks();

      ts.assertCondition((m3.tryLock() == false));

      // try for more than INTERVAL_SHORT ticks, should succeed
      ts.assertCondition((m3.tryLockFor(INTERVAL_LONG) == true));

      os::core::timer::ticks_t t1 = os::timerTicks.getCurrentTicks();
      m3.unlock();

      int proc = computeAbsoluteProcent(t0, t1, INTERVAL_SHORT);

      ts.setFunctionNameOrPrefix("tryLockFor()");
      ts.setPreconditions("no timeout");
      ts.assertCondition(proc < 10);
    }

    void
    fTryForTimeout(void);

    void
    fTryForTimeout(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString(__PRETTY_FUNCTION__);
      os::diag::trace.putNewLine();
#endif
      os::core::timer::ticks_t t0 = os::timerTicks.getCurrentTicks();

      ts.assertCondition((m4.tryLock() == false));

      // try less than INTERVAL_LONG ticks, should not succeed
      ts.assertCondition((m4.tryLockFor(INTERVAL_SHORT) == false));

      os::core::timer::ticks_t t1 = os::timerTicks.getCurrentTicks();
      int proc = computeAbsoluteProcent(t0, t1, INTERVAL_SHORT);

      ts.setFunctionNameOrPrefix("tryLockFor()");
      ts.setPreconditions("with timeout");
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
      os::core::Thread th1("t1", thread::mutex::fLock, stack);

      thread::mutex::m1.lock();

      th1.start();

      os::core::Thread& thread = os::mainThread;
      thread.sleepFor(thread::mutex::INTERVAL);

      thread::mutex::m1.unlock();

      th1.join();
    }

    {
      os::core::AllocatedStack stack;
      os::core::Thread th2("t2", thread::mutex::fTryLock, stack);

      thread::mutex::m2.lock();

      th2.start();

      os::core::Thread& thread = os::mainThread;
      thread.sleepFor(thread::mutex::INTERVAL);

      thread::mutex::m2.unlock();

      th2.join();
    }

    {
      os::core::AllocatedStack stack;
      os::core::Thread th3("t3", thread::mutex::fTryForNoTimeout, stack);

      thread::mutex::m3.lock();
      th3.start();

      // sleep less than tryLockFor(INTERVAL_LONG)
      os::core::Thread& thread = os::mainThread;
      thread.sleepFor(thread::mutex::INTERVAL_SHORT);

      thread::mutex::m3.unlock();
      th3.join();
    }

    {
      os::core::AllocatedStack stack;
      os::core::Thread th4("t4", thread::mutex::fTryForTimeout, stack);

      thread::mutex::m4.lock();
      th4.start();

      // sleep longer than tryLock(INTERVAL_SHORT)
      os::core::Thread& thread = os::mainThread;
      thread.sleepFor(thread::mutex::INTERVAL_LONG);

      thread::mutex::m4.unlock();
      th4.join();
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

    os::core::RecursiveMutex rm3("rm3");

    os::core::RecursiveMutex rm4("rm4");

#pragma GCC diagnostic pop

    constexpr os::core::timer::ticks_t INTERVAL = 100;

    constexpr os::core::timer::ticks_t INTERVAL_SHORT = 100;
    constexpr os::core::timer::ticks_t INTERVAL_LONG = INTERVAL_SHORT + 50;

    void
    fLock(void);

    void
    fLock(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString(__PRETTY_FUNCTION__);
      os::diag::trace.putNewLine();
#endif
      os::core::timer::ticks_t t0 = os::timerTicks.getCurrentTicks();

      rm1.lock();

      os::core::timer::ticks_t t1 = os::timerTicks.getCurrentTicks();

      rm1.unlock();

      int proc = computeAbsoluteProcent(t0, t1, INTERVAL);

      ts.setFunctionNameOrPrefix("lock()");
      ts.assertCondition(proc < 10);
    }

    void
    fTryLock(void);

    void
    fTryLock(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString(__PRETTY_FUNCTION__);
      os::diag::trace.putNewLine();
#endif
      os::core::timer::ticks_t t0 = os::timerTicks.getCurrentTicks();

      // initially should not lock
      ts.assertCondition(rm2.tryLock() == false);
      ts.assertCondition(rm2.tryLock() == false);
      ts.assertCondition(rm2.tryLock() == false);

      os::core::Thread* thread = os::scheduler.getCurrentThread();

      while (!rm2.tryLock())
        {
          thread->sleepFor(1);
        }

      os::core::timer::ticks_t t1 = os::timerTicks.getCurrentTicks();

      // this time it should lock
      ts.assertCondition(rm2.tryLock() == true);

      rm2.unlock();
      rm2.unlock();

      int proc = computeAbsoluteProcent(t0, t1, INTERVAL);

      ts.setFunctionNameOrPrefix("tryLock()");
      ts.assertCondition(proc < 10);
    }

    void
    fTryForNoTimeout(void);

    void
    fTryForNoTimeout(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString(__PRETTY_FUNCTION__);
      os::diag::trace.putNewLine();
#endif
      os::core::timer::ticks_t t0 = os::timerTicks.getCurrentTicks();

      ts.assertCondition((rm3.tryLock() == false));

      // try for more than INTERVAL_SHORT ticks, should succeed
      ts.assertCondition((rm3.tryLockFor(INTERVAL_LONG) == true));

      os::core::timer::ticks_t t1 = os::timerTicks.getCurrentTicks();

      ts.assertCondition((rm3.tryLock() == true));

      rm3.unlock();
      rm3.unlock();

      int proc = computeAbsoluteProcent(t0, t1, INTERVAL_SHORT);

      ts.setFunctionNameOrPrefix("tryLockFor()");
      ts.setPreconditions("no timeout");
      ts.assertCondition(proc < 10);
    }

    void
    fTryForTimeout(void);

    void
    fTryForTimeout(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString(__PRETTY_FUNCTION__);
      os::diag::trace.putNewLine();
#endif
      os::core::timer::ticks_t t0 = os::timerTicks.getCurrentTicks();

      ts.assertCondition((rm4.tryLock() == false));

      // try less than INTERVAL_LONG ticks, should not succeed
      ts.assertCondition((rm4.tryLockFor(INTERVAL_SHORT) == false));

      os::core::timer::ticks_t t1 = os::timerTicks.getCurrentTicks();
      int proc = computeAbsoluteProcent(t0, t1, INTERVAL_SHORT);

      ts.setFunctionNameOrPrefix("tryLockFor()");
      ts.setPreconditions("with timeout");
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
      os::core::Thread th1("tr1", thread::recursivemutex::fLock, stack);

      // first lock
      thread::recursivemutex::rm1.lock();

      th1.start();

      os::core::Thread& thread = os::mainThread;
      thread.sleepFor(thread::recursivemutex::INTERVAL / 3);
        {
          // second lock
          thread::recursivemutex::rm1.lock();

          thread.sleepFor(thread::recursivemutex::INTERVAL / 3);

          // first unlock
          thread::recursivemutex::rm1.unlock();
        }
      thread.sleepFor(thread::recursivemutex::INTERVAL / 3);

      // second unlock
      thread::recursivemutex::rm1.unlock();

      th1.join();
    }

    {
      os::core::AllocatedStack stack;
      os::core::Thread th2("tr2", thread::recursivemutex::fTryLock, stack);

      // first lock
      thread::recursivemutex::rm2.lock();

      th2.start();

      os::core::Thread& thread = os::mainThread;
      thread.sleepFor(thread::recursivemutex::INTERVAL / 3);
        {
          // second lock
          thread::recursivemutex::rm2.lock();

          thread.sleepFor(thread::recursivemutex::INTERVAL / 3);

          // first unlock
          thread::recursivemutex::rm2.unlock();
        }
      thread.sleepFor(thread::recursivemutex::INTERVAL / 3);

      // second unlock
      thread::recursivemutex::rm2.unlock();

      th2.join();
    }

    {
      os::core::AllocatedStack stack;
      os::core::Thread th3("tr3", thread::recursivemutex::fTryForNoTimeout,
          stack);

      // first lock
      thread::recursivemutex::rm3.lock();

      th3.start();

      os::core::Thread& thread = os::mainThread;
      thread.sleepFor(thread::recursivemutex::INTERVAL_SHORT / 3);
        {
          // second lock
          thread::recursivemutex::rm3.lock();

          thread.sleepFor(thread::recursivemutex::INTERVAL_SHORT / 3);

          // first unlock
          thread::recursivemutex::rm3.unlock();
        }
      thread.sleepFor(thread::recursivemutex::INTERVAL_SHORT / 3);

      // second unlock
      thread::recursivemutex::rm3.unlock();

      th3.join();
    }

    {
      os::core::AllocatedStack stack;
      os::core::Thread th4("tr4", thread::recursivemutex::fTryForTimeout,
          stack);

      // first lock
      thread::recursivemutex::rm4.lock();

      th4.start();

      os::core::Thread& thread = os::mainThread;
      thread.sleepFor(thread::recursivemutex::INTERVAL_LONG / 3);
        {
          // second lock
          thread::recursivemutex::rm4.lock();

          thread.sleepFor(thread::recursivemutex::INTERVAL_LONG / 3);

          // first unlock
          thread::recursivemutex::rm4.unlock();
        }
      thread.sleepFor(thread::recursivemutex::INTERVAL_LONG / 3);

      // second unlock
      thread::recursivemutex::rm4.unlock();

      th4.join();
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

