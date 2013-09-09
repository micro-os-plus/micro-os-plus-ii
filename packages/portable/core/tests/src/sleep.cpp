//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include "portable/core/include/OS.h"

#include "portable/infrastructure/include/TestSuite.h"

// This test exercises the thread.sleep() call using timerTicks.

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
#include "portable/core/include/MainThread.h"

// ----------------------------------------------------------------------------

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX)
#define HAS_GETTIMEOFDAY (1)
#endif

// ----------------------------------------------------------------------------

#if defined(HAS_GETTIMEOFDAY)
#include <sys/time.h>
#endif

// ----------------------------------------------------------------------------

void
toString(int value, char* pBuffer, ssize_t sz);

void
toString(int value, char* pBuffer, ssize_t sz)
{
  pBuffer[sz - 1] = '\0';
  ssize_t pos;

  for (pos = sz - 1; pos != 0;)
    {
      char ch = (value % 10) + '0';
      pBuffer[--pos] = ch;
      value /= 10;
      if (value == 0)
        break;
    }

  if (pos == 0)
    return;

  ssize_t i;
  for (i = 0; pos < sz;)
    {
      pBuffer[i++] = pBuffer[pos++];
    }
}

// ----------------------------------------------------------------------------

void
runTestAccuracy();

#if 1
#define TICKS_TO_MEASURE_ACCURACY os::core::scheduler::TICKS_PER_SECOND
#else
#define TICKS_TO_MEASURE_ACCURACY 10
#endif

void
runTestAccuracy()
{
#if defined(DEBUG)
  os::diag::trace.putString(__PRETTY_FUNCTION__);
  os::diag::trace.putNewLine();
#endif

  ts.setClassName("os::core::Thread");
  ts.setFunctionNameOrPrefix("sleep()");

  os::core::Thread& thread = os::mainThread;

  //os::timerTicks.sleep(1);
  thread.sleepFor(1);

  os::core::timer::ticks_t ticksBegin = os::timerTicks.getCurrentTicks();

#if defined(HAS_GETTIMEOFDAY)
  timeval begTime;
  gettimeofday(&begTime, 0);
#endif

  //os::timerTicks.sleep(os::core::scheduler::TICKS_PER_SECOND);
  thread.sleepFor(TICKS_TO_MEASURE_ACCURACY);

  os::core::timer::ticks_t ticksEnd = os::timerTicks.getCurrentTicks();

#if defined(HAS_GETTIMEOFDAY)
  timeval endTime;
  gettimeofday(&endTime, 0);

  long deltaMicros = (endTime.tv_sec - begTime.tv_sec) * 1000000
  + (endTime.tv_usec - begTime.tv_usec);
  //int deltaMillis = (int)((deltaMicros + 500) / 1000);

  double deltaProcents = (deltaMicros - 1000000) * 100.0 / 1000000.0;
#endif

  os::core::timer::ticks_t deltaTicks = ticksEnd - ticksBegin;

  ts.setFunctionNameOrPrefix("sleep()");

  char tmp[10];
  toString(TICKS_TO_MEASURE_ACCURACY, tmp, sizeof(tmp));
  ts.setInputValues(tmp);

  ts.assertCondition(((deltaTicks - TICKS_TO_MEASURE_ACCURACY) <= 1));

  ts << os::std::endl << "sleep(" << TICKS_TO_MEASURE_ACCURACY<< ") took " << deltaTicks << " ticks";
#if defined(HAS_GETTIMEOFDAY)
  ts << ", " << deltaMicros << " real time micros, accuracy "
  << (long) (deltaProcents * 1000) << "/1000 %";
#endif
  ts << os::std::endl;

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

  static constexpr unsigned int SUM = (TO - FROM + 1) * (FROM + TO) / 2
      * REPEAT;

  Task(const char* pName, os::core::stack::size_t stackSizeBytes);
  ~Task();

  void
  threadMain();

  os::core::Thread&
  getThread(void);

  os::core::timer::ticks_t
  getCount(void);

  os::core::timer::ticks_t
  getDeltaTicks(void);

  unsigned int
  getSleepCalls(void);

private:
  // since it is passed to Thread, must be initialised before
  os::core::AllocatedStack m_stack;
  os::core::Thread m_thread;

  os::core::timer::ticks_t m_count;
  os::core::timer::ticks_t m_deltaTicks;
  unsigned int m_sleepCalls;
};

#pragma GCC diagnostic pop

Task::Task(const char* pName, os::core::stack::size_t stackSizeBytes) :
    NamedObject(pName), //
    m_stack(stackSizeBytes), //
    m_thread(pName, [](Task* pTask)
      { pTask->threadMain();}, this, m_stack)
{
#if defined(DEBUG)
  os::diag::trace.putConstructor();
#endif
  m_count = 0;
  m_deltaTicks = 0;
  m_sleepCalls = 0;
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

os::core::timer::ticks_t
Task::getCount(void)
{
  return m_count;
}

os::core::timer::ticks_t
Task::getDeltaTicks(void)
{
  return m_deltaTicks;
}

unsigned int
Task::getSleepCalls(void)
{
  return m_sleepCalls;
}

void
Task::threadMain(void)
{
#if defined(DEBUG)
  os::diag::trace.putMemberFunctionWithName();
#endif

  //os::timerTicks.sleep(10);
  m_thread.sleepFor(10);

  os::core::timer::ticks_t ticksBegin = os::timerTicks.getCurrentTicks();

  os::core::timer::ticks_t cnt;
  for (cnt = 1; cnt <= REPEAT; cnt++)
    {
      os::core::timer::ticks_t i;
      for (i = FROM; i <= TO; i++)
        {
          //os::timerTicks.sleep(i);
          m_thread.sleepFor(i);

          m_count += i;
          ++m_sleepCalls;
        }
    }

  os::core::timer::ticks_t ticksEnd = os::timerTicks.getCurrentTicks();

  m_deltaTicks = ticksEnd - ticksBegin;

  //os::timerTicks.sleep(50);
  m_thread.sleepFor(50);

  ts << "Multiple sleeps of " << SUM << " ticks took " << m_deltaTicks
      << " counted ticks, \"" << getThread().getName() << "\"" << os::std::endl;

}

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

#pragma GCC diagnostic pop

void
runTestMulti();

void
runTestMulti()
{
#if defined(DEBUG)
  os::diag::trace.putString(__PRETTY_FUNCTION__);
  os::diag::trace.putNewLine();
#endif

  ts.setClassName("os::core::Thread");
  ts.setFunctionNameOrPrefix("sleep()");

  Task task1("T1", hal::arch::MIN_STACK_SIZE);
  Task task2("T2", hal::arch::MIN_STACK_SIZE);
  Task task3("T3", hal::arch::MIN_STACK_SIZE);
  Task task4("T4", hal::arch::MIN_STACK_SIZE);
  Task task5("T5", hal::arch::MIN_STACK_SIZE);

  Task* taskArray[5] =
    { &task1, &task2, &task3, &task4, &task5 };

  for (auto pTask : taskArray)
    {
      ts.setPreconditions(pTask->getName());
      ts.assertCondition(pTask->getCount() == 0);
    }

  for (auto pTask : taskArray)
    {
      ts.assertCondition(pTask->getThread().start());
    }

  for (auto pTask : taskArray)
    {
      pTask->getThread().join();
    }

  for (auto pTask : taskArray)
    {
      ts.setPreconditions(pTask->getName());
      ts.assertCondition(
          ((pTask->getDeltaTicks() - pTask->getCount())
              <= pTask->getSleepCalls()));
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

  os::scheduler.setPreemptive(false);
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

