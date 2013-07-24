//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/OS.h"

#include "portable/infrastructure/include/TestSuite.h"

// This stress test exercises the timerTicks.sleep() call and if the
// scheduler and timer internal structures are properly protected by
// critical sections.

// The method used is to issue random sleeps from multiple threads
// and to periodically collect statistics for all threads,
// to eventually detect hanged threads.

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

  Task(const char* pName, os::core::stack::size_t stackSizeBytes,
      uint16_t minMicros, uint16_t maxMicros, uint16_t minTicks,
      uint16_t maxTicks);

  ~Task();

  void
  threadMain()[[noreturn]];

  os::core::Thread&
  getThread(void);

  static uint16_t
  rand(void);

  static void
  seed(uint16_t val);

  uint32_t
  getCount(void);

  os::core::timer::ticks_t
  getTicks(void);

  void
  resetCount(void);

  void
  resetTicks(void);

  int32_t
  getDelta(void);

private:
  os::core::StackWithAllocator m_stack;

  os::core::Thread m_thread;

  uint16_t m_minMicros;
  uint16_t m_maxMicros;
  uint16_t m_minTicks;
  uint16_t m_maxTicks;

  uint32_t m_count;
  os::core::timer::ticks_t m_ticks;

  uint32_t m_averageCount;
  os::core::timer::ticks_t m_averageTicksSum;

  static uint32_t ms_rand;
  static uint32_t ms_lineLength;
};

#pragma GCC diagnostic pop

uint32_t Task::ms_rand;
uint32_t Task::ms_lineLength;

Task::Task(const char* pName, os::core::stack::size_t stackSizeBytes,
    uint16_t minMicros, uint16_t maxMicros, uint16_t minTicks,
    uint16_t maxTicks)
    : NamedObject(pName), //
    m_stack(stackSizeBytes), //
    m_thread(pName, [](Task* pTask)
      { pTask->threadMain();}, this, m_stack)
{
#if defined(DEBUG)
  os::diag::trace.putConstructorWithName();
#endif

  m_count = 0;
  m_ticks = 0;
  m_averageCount = 0;
  m_averageTicksSum = 0;

  m_minMicros = minMicros;
  m_maxMicros = maxMicros;
  m_minTicks = minTicks;
  m_maxTicks = maxTicks;
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

uint32_t
Task::getCount(void)
{
  return m_count;
}

os::core::timer::ticks_t
Task::getTicks(void)
{
  return m_ticks;
}

void
Task::resetCount(void)
{
  m_count = 0;
}

void
Task::resetTicks(void)
{
  m_ticks = 0;
}

int32_t
Task::getDelta(void)
{
  int ret = (int32_t)(m_averageTicksSum/m_averageCount);
  return ret - (m_maxTicks-m_minTicks)/2;
}

void
Task::threadMain(void)
{
#if defined(DEBUG)
  os::diag::trace.putMemberFunctionWithName();
#endif

  uint16_t nBusy, nSleep;
  uint16_t nCnt;
  nCnt = 0;

  // thread endless loop
  for (;;)
    {
      nBusy = (rand() % (m_maxMicros - m_minMicros)) + m_minMicros;
      nSleep = (rand() % (m_maxTicks - m_minTicks)) + m_minTicks;

      // simulate a period of intense activity
      os::architecture.busyWaitMicros(nBusy);

      // simulate a period of waiting for an external event
      os::timerTicks.sleep(nSleep);

      m_count++;
      m_ticks += nSleep;

      m_averageCount++;
      m_averageTicksSum += (m_ticks / m_count);

      nCnt += nSleep;
      if (nCnt >= 1000)
        {
          nCnt -= 1000;
        }
    }
}

void
Task::seed(uint16_t val)
{
  ms_rand = val;
}

uint16_t
Task::rand(void)
{
#if false
  return 9;
#else
  uint16_t ret;
  os::core::scheduler::CriticalSection cs;
  //os.sched.critical.enter();
    {
      ms_rand = ms_rand * 214013L + 2531011L;
#if (__SIZEOF_INT__ == 2) && false
      ret = (ms_rand & 0x7fff);
#else
      ret = ((ms_rand >> 16) & 0x7fff);
#endif
    }

  return ret;
#endif
}

// ============================================================================

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

class TaskPeriodic : public os::core::NamedObject
{
public:
  TaskPeriodic(const char* pName, os::core::stack::size_t stackSizeBytes);

  ~TaskPeriodic();

  void
  threadMain()[[noreturn]];

  os::core::Thread&
  getThread(void);

private:
  os::core::StackWithAllocator m_stack;

  os::core::Thread m_thread;

};

#pragma GCC diagnostic pop

TaskPeriodic::TaskPeriodic(const char* pName,
    os::core::stack::size_t stackSizeBytes)
    : NamedObject(pName), //
    m_stack(stackSizeBytes), //
    m_thread(pName, [](TaskPeriodic* pTask)
      { pTask->threadMain();}, this, m_stack,
        os::core::scheduler::DEFAULT_PRIORITY + 1)
{
#if defined(DEBUG)
  os::diag::trace.putConstructorWithName();
#endif

}

TaskPeriodic::~TaskPeriodic()
{
#if defined(DEBUG)
  os::diag::trace.putDestructorWithName();
#endif
}

os::core::Thread&
TaskPeriodic::getThread(void)
{
  return m_thread;
}

Task* taskArray[10];

void
TaskPeriodic::threadMain(void)
{
#if defined(DEBUG)
  os::diag::trace.putMemberFunctionWithName();
#endif

  // thread endless loop
  for (;;)
    {
      os::timerTicks.sleep(5000);

      os::core::scheduler::CriticalSection cs;

#if defined(DEBUG)
      os::diag::trace.putNewLine();
      for (size_t i = 0; i < sizeof(taskArray) / sizeof(taskArray[0]); ++i)
        {
          Task* pTask = taskArray[i];
          os::diag::trace.putString(pTask->getName());
          os::diag::trace.putChar(':');
          os::diag::trace.putDec(pTask->getTicks());
          os::diag::trace.putChar('/');
          os::diag::trace.putDec(pTask->getCount());
          os::diag::trace.putChar('=');
          os::diag::trace.putDec(pTask->getTicks() / pTask->getCount());
          os::diag::trace.putChar('(');
          os::diag::trace.putDec(pTask->getDelta());
          os::diag::trace.putChar(')');
          os::diag::trace.putChar('\t');

          pTask->resetCount();
          pTask->resetTicks();
        }
      //os::diag::trace.putNewLine();
#endif
    }
}

// ============================================================================

void
runTestStress();

void
runTestStress()
{
#if defined(DEBUG)
  os::diag::trace.putString(__PRETTY_FUNCTION__);
  os::diag::trace.putNewLine();
#endif

  Task::seed((uint16_t) time(NULL));

  TaskPeriodic taskP("P", hal::arch::MIN_STACK_SIZE);
  Task task0("0", hal::arch::MIN_STACK_SIZE, 0, 50, 1, 150);
  Task task1("1", hal::arch::MIN_STACK_SIZE, 0, 50, 1, 150);
  Task task2("2", hal::arch::MIN_STACK_SIZE, 0, 50, 1, 150);
  Task task3("3", hal::arch::MIN_STACK_SIZE, 30, 70, 1, 200);
  Task task4("4", hal::arch::MIN_STACK_SIZE, 500, 2500, 1, 200);
  Task task5("5", hal::arch::MIN_STACK_SIZE, 30, 70, 1, 100);
  Task task6("6", hal::arch::MIN_STACK_SIZE, 10, 90, 1, 200);
  Task task7("7", hal::arch::MIN_STACK_SIZE, 10, 90, 1, 400);
  Task task8("8", hal::arch::MIN_STACK_SIZE, 10, 90, 1, 600);
  Task task9("9", hal::arch::MIN_STACK_SIZE, 10, 90, 1, 800);

  taskP.getThread().start();

  taskArray[0] = &task0;
  task0.getThread().start();
  taskArray[1] = &task1;
  task1.getThread().start();
  taskArray[2] = &task2;
  task2.getThread().start();
  taskArray[3] = &task3;
  task3.getThread().start();
  taskArray[4] = &task4;
  task4.getThread().start();
  taskArray[5] = &task5;
  task5.getThread().start();
  taskArray[6] = &task6;
  task6.getThread().start();
  taskArray[7] = &task7;
  task7.getThread().start();
  taskArray[8] = &task8;
  task8.getThread().start();
  taskArray[9] = &task9;
  task9.getThread().start();

  // since threads loop forever, this will never return
  taskP.getThread().join();
}

// ============================================================================

// ----------------------------------------------------------------------------

int
main(int argc, char* argv[])
{
  // instantiate the TestSuite, passing the process parameters
  ts.processMainParameters(argc, argv);

  // mark the start of the test suite
  ts.start("portable/core/tests/src/sleepStress.cpp");

  os::scheduler.start();

  runTestStress();

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

