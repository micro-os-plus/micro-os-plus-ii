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

#include "portable/core/include/NamedObject.h"
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
  long deltaMicros = (endTime.tv_sec - begTime.tv_sec) * 1000000
      + (endTime.tv_usec - begTime.tv_usec);
  //int deltaMillis = (int)((deltaMicros + 500) / 1000);

  double deltaProcents = (deltaMicros - 1000000) * 100.0 / 1000000.0;

#if defined(DEBUG)
  os::diag::trace << os::std::endl << "sleep("
      << os::core::scheduler::TICKS_PER_SECOND << ") took " << deltaMicros
      << " micros" << os::std::endl;
#endif

  ts.assertCondition((-10.0 < deltaProcents) && (deltaProcents < 10.0));

}

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

class Task : public os::core::NamedObject
{
public:
  static constexpr unsigned int FROM = 1;
  static constexpr unsigned int TO = 10;
  static constexpr unsigned int REPEAT = 10;

  static constexpr unsigned int SUM = (TO - FROM + 1) * (FROM + TO) / 2 * REPEAT;

  Task(const char* pName);
  ~Task();

  void
  threadMain();

  os::core::Thread&
  getThread(void);

  int
  getCount(void);

  os::core::timer::ticks_t
  getDeltaTicks(void);

private:
  os::core::Stack::element_t m_stack[hal::arch::MIN_STACK_SIZE
      / sizeof(os::core::Stack::element_t)];

  os::core::Thread m_thread;

  int m_count;
  os::core::timer::ticks_t m_deltaTicks;
};

#pragma GCC diagnostic pop

Task::Task(const char* pName)
    : NamedObject(pName), m_thread(pName, [](Task* pTask)
      { pTask->threadMain();}, this, m_stack, sizeof(m_stack))
{
#if defined(DEBUG)
  os::diag::trace.putConstructor();
#endif
  m_count = 0;
  m_deltaTicks = 0;
}

Task::~Task()
{
#if defined(DEBUG)
  os::diag::trace.putDestructorWithName();
#endif
}

os::core::Thread&
Task::getThread(void)
{
  return m_thread;
}

int
Task::getCount(void)
{
  return m_count;
}

os::core::timer::ticks_t
Task::getDeltaTicks(void)
{
  return m_deltaTicks;
}

void
Task::threadMain(void)
{
#if defined(DEBUG)
  os::diag::trace.putMemberFunctionWithName();
#endif

  os::timerTicks.sleep(10);

  os::core::timer::ticks_t ticksBegin = os::timerTicks.getTicks();

  os::core::timer::ticks_t cnt;
  for (cnt = 1; cnt <= REPEAT; cnt++)
    {
      os::core::timer::ticks_t i;
      for (i = FROM; i <= TO; i++)
        {
          os::timerTicks.sleep(i);
          m_count += i;
        }
    }

  os::core::timer::ticks_t ticksEnd = os::timerTicks.getTicks();

  m_deltaTicks = ticksEnd - ticksBegin;

  os::timerTicks.sleep(50);

#if defined(DEBUG)
  os::diag::trace.putString("many sleeps, took ");
  os::diag::trace.putDec((int)m_deltaTicks);
  os::diag::trace.putString(" milliseconds, \"");
  os::diag::trace.putString(getThread().getName());
  os::diag::trace.putString("\"");
  os::diag::trace.putNewLine();
#endif

  //std::cout << "deltaTicks=" << m_deltaTicks << std::endl;

#if defined(_DEBUG)
  os::diag::trace.putString("m_count=");
  os::diag::trace.putDec(m_count);
  os::diag::trace.putString(" SUM=");
  os::diag::trace.putDec(SUM);
  os::diag::trace.putString(" deltaTicks=");
  os::diag::trace.putDec((int)m_deltaTicks);
#endif

}

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

static Task task1("T1");
static Task task2("T2");
static Task task3("T3");
static Task task4("T4");
static Task task5("T5");

#pragma GCC diagnostic pop

void
runTestMulti();

void
runTestMulti()
{
  Task* array[5] =
    { &task1, &task2, &task3, &task4, &task5 };

  unsigned int i;
  for (i = 0; i < sizeof(array) / sizeof(array[0]); ++i)
    {
      ts.assertCondition(array[i]->getCount() == 0);
    }

  for (i = 0; i < sizeof(array) / sizeof(array[0]); ++i)
    {
      array[i]->getThread().start();
    }

  for (i = 0; i < sizeof(array) / sizeof(array[0]); ++i)
    {
      array[i]->getThread().join();
    }

  for (i = 0; i < sizeof(array) / sizeof(array[0]); ++i)
    {
      ts.assertCondition(array[i]->getCount() == static_cast<int>(Task::SUM));
    }

  for (i = 0; i < sizeof(array) / sizeof(array[0]); ++i)
    {
      ts.assertCondition(array[i]->getDeltaTicks() == Task::SUM);
    }
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

