//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/OS.h"

#include "portable/infrastructure/include/TestSuite.h"

// This test exercises the timerTicks.sleep() call.

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

static os::infra::TestSuite ts;

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------

#include "portable/core/include/Scheduler.h"
#include "portable/core/include/Thread.h"
#include "portable/core/include/TimerTicks.h"
#include "portable/core/include/CriticalSections.h"

// ----------------------------------------------------------------------------

#include <iostream>
#include <sys/time.h>

// ----------------------------------------------------------------------------

void
runTestAccuracy();

void
runTestAccuracy()
{
  ts.setClassName("os::core::TimerTicks");
  ts.setFunctionNameOrPrefix("sleep()");

  os::timerTicks.sleep(1);

  timeval begTime;
  gettimeofday(&begTime, 0);

  os::timerTicks.sleep(os::core::scheduler::TICKS_PER_SECOND);

  timeval endTime;
  gettimeofday(&endTime, 0);
  long deltaMicros = (endTime.tv_sec - begTime.tv_sec) * 1000000 + (endTime.tv_usec - begTime.tv_usec);
  //int deltaMillis = (int)((deltaMicros + 500) / 1000);

  double deltaProcents = (deltaMicros - 1000000) * 100.0 / 1000000.0;

  std::cout << std::endl << "sleep(" << os::core::scheduler::TICKS_PER_SECOND
      << ") took " << deltaMicros << " micros, delta=" << deltaProcents << "%"
      << std::endl;

  ts.assertCondition((-10.0 < deltaProcents) && (deltaProcents < 10.0));
}

// ----------------------------------------------------------------------------

class Task
{
public:
  Task(const char* pName);
  ~Task();

  void
  threadMain();

  os::core::Thread&
  getThread(void);

private:
  os::core::Stack::element_t m_stack[hal::arch::MIN_STACK_SIZE/sizeof(os::core::Stack::element_t)];

  os::core::Thread m_thread;

};

Task::Task(const char* pName)
    : m_thread(pName, [](Task* pTask)
      { pTask->threadMain();}, this, m_stack,
        sizeof(m_stack))
{
#if defined(DEBUG)
  os::diag::trace.putConstructor();
#endif
  m_thread.suspend();
}

Task::~Task()
{
#if defined(DEBUG)
  os::diag::trace.putDestructor();
#endif
}

os::core::Thread&
Task::getThread(void)
{
  return m_thread;
}

void
Task::threadMain(void)
{
#if defined(DEBUG)
  os::diag::trace.putMemberFunction();
#endif

#if 0
  os::core::timer::ticks_t i;
  for (i = 1; i < 10; i++)
    {
      os::timerTicks.sleep(i);
    }
#endif
}

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

static Task task1("T1");
static Task task2("T2");

#pragma GCC diagnostic pop

void
runTestMulti();

void
runTestMulti()
{
  {
    os::core::scheduler::CriticalSection cs;

    task1.getThread().resume();
    task2.getThread().resume();
  }

  task1.getThread().join();
  task2.getThread().join();
}

// ----------------------------------------------------------------------------

int
main(int argc, char* argv[])
{
  // instantiate the TestSuite, passing the process parameters
  ts.processMainParameters(argc, argv);

  // mark the start of the test suite
  ts.start("portable/core/tests/src/sleep.cpp");

  os::scheduler.start();

  runTestAccuracy();

  runTestMulti();

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

