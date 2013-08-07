//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/OS.h"

#include "portable/infrastructure/include/TestSuite.h"

// This stress test exercises the Mutex class.

// The method used is to issue random sleeps from multiple threads
// and to periodically collect statistics for all threads,
// to eventually detect hanged threads.

// ----------------------------------------------------------------------------

constexpr int MAX_RUN_SECONDS = 30;
//constexpr int MAX_RUN_SECONDS = 0;

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

//#include <iostream>
#include <sys/time.h>

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

os::core::Mutex mutex;

#pragma GCC diagnostic pop

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
  threadMain() __attribute__((noreturn));

  os::core::Thread&
  getThread(void);

  static uint16_t
  rand(void);

  static void
  seed(uint16_t val);

  uint32_t
  getCount(void);

  uint32_t
  getTicks(void);

  os::core::timer::ticks_t
  getMaxTicks(void);

  os::core::timer::ticks_t
  getMinTicks(void);

private:
  os::core::AllocatedStack m_stack;

  os::core::Thread m_thread;

  uint16_t m_minMicros;
  uint16_t m_maxMicros;
  uint16_t m_minTicks;
  uint16_t m_maxTicks;

  uint32_t m_count;

  os::core::timer::ticks_t m_ticks;

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

os::core::timer::ticks_t
Task::getMaxTicks(void)
{
  return m_maxTicks;
}

os::core::timer::ticks_t
Task::getMinTicks(void)
{
  return m_minTicks;
}

void
Task::threadMain(void)
{
#if defined(DEBUG)
  os::diag::trace.putMemberFunctionWithName();
#endif

  // thread endless loop
  for (;;)
    {
      uint16_t nBusy = (rand() % (m_maxMicros - m_minMicros)) + m_minMicros;
      uint16_t nSleep = (rand() % (m_maxTicks - m_minTicks)) + m_minTicks;

      // simulate a period of intense activity
      os::architecture.busyWaitMicros(nBusy);

      // simulate a period of waiting for an external event
      os::timerTicks.sleep(nSleep);
      m_ticks += nSleep;

      mutex.lock();
        {
          nBusy = (rand() % (m_maxMicros - m_minMicros)) + m_minMicros;
          nSleep = (rand() % (m_maxTicks - m_minTicks)) + m_minTicks;

          // simulate a period of intense activity
          os::architecture.busyWaitMicros(nBusy);

          // simulate a period of waiting for an external event
          os::timerTicks.sleep(nSleep);
          m_ticks += nSleep;

          m_count++;
        }
      mutex.unlock();
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
  threadMain();

  os::core::Thread&
  getThread(void);

private:
  os::core::AllocatedStack m_stack;

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
  int t = 0;
  for (;;)
    {
      os::timerTicks.sleep(5000);
      t += 5;
      if (MAX_RUN_SECONDS != 0 and t > MAX_RUN_SECONDS)
        break;

        {
          // ----- begin of critical section -----------------------------------
          os::core::scheduler::CriticalSection cs;

          int sum = 0;
          for (auto pTask : taskArray)
            {
              uint32_t cnt = pTask->getCount();
              sum += cnt;

              //os::core::timer::ticks_t ticks = pTask->getTicks();

              ts << pTask->getName() << ':';
              //ts << ticks << "/" ;
              ts << cnt << '\t';

            }
          ts << "sum=" << sum;
          int average = (sum
              + (((int) (sizeof(taskArray) / sizeof(taskArray[0]))) / 2))
              / ((int) (sizeof(taskArray) / sizeof(taskArray[0])));

          ts << " avg=" << average;

          int min = 0;
          int max = 0;

          for (auto pTask : taskArray)
            {
              int delta = (int) pTask->getCount();
              delta -= average;

              if (delta < min)
                min = delta;

              if (delta > max)
                max = delta;
            }

          ts << " delta in [" << min << "," << max << "]";
          ts << " [" << (min * 100 + average / 2) / average << "%,"
              << (max * 100 + average / 2) / average << "%]";

          ts << os::std::endl;

          // ----- end of critical section -------------------------------------
        }
    }

  os::core::scheduler::CriticalSection cs;

  ts.setFunctionNameOrPrefix("lock()/unlock()");

  int sum = 0;
  for (auto pTask : taskArray)
    {
      uint32_t cnt = pTask->getCount();
      sum += cnt;
    }

  int average = (sum + (((int) (sizeof(taskArray) / sizeof(taskArray[0]))) / 2))
      / ((int) (sizeof(taskArray) / sizeof(taskArray[0])));

  ts << "average=" << average << os::std::endl;

  for (auto pTask : taskArray)
    {

      int delta = (int) pTask->getCount();
      delta -= average;

      int deltaProcent = (delta * 100 + average / 2) / average;

      ts << pTask->getName() << ':' << delta << " " << deltaProcent << "%"
          << '\t';

      ts.setPreconditions(pTask->getName());
      ts.assertCondition((-33 <= deltaProcent && deltaProcent <= 33));
    }
  ts << os::std::endl;

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

  Task task0("t0", hal::arch::MIN_STACK_SIZE, 10, 90, 1, 800);
  Task task1("t1", hal::arch::MIN_STACK_SIZE, 10, 90, 1, 600);
  Task task2("t2", hal::arch::MIN_STACK_SIZE, 0, 50, 1, 150);
  Task task3("t3", hal::arch::MIN_STACK_SIZE, 30, 70, 1, 200);
  Task task4("t4", hal::arch::MIN_STACK_SIZE, 500, 2500, 1, 200);
  Task task5("t5", hal::arch::MIN_STACK_SIZE, 30, 70, 1, 100);
  Task task6("t6", hal::arch::MIN_STACK_SIZE, 0, 50, 1, 150);
  Task task7("t7", hal::arch::MIN_STACK_SIZE, 10, 90, 1, 400);
  Task task8("t8", hal::arch::MIN_STACK_SIZE, 10, 90, 1, 600);
  Task task9("t9", hal::arch::MIN_STACK_SIZE, 10, 90, 1, 800);

  taskArray[0] = &task0;
  taskArray[1] = &task1;
  taskArray[2] = &task2;
  taskArray[3] = &task3;
  taskArray[4] = &task4;
  taskArray[5] = &task5;
  taskArray[7] = &task7;
  taskArray[8] = &task8;
  taskArray[9] = &task9;

  taskP.getThread().start();

  task0.getThread().start();
  task1.getThread().start();
  task2.getThread().start();
  task3.getThread().start();
  task4.getThread().start();
  task5.getThread().start();
  task6.getThread().start();
  task7.getThread().start();
  task8.getThread().start();
  task9.getThread().start();

  // after MAX_RUN_SECONDS, the periodic thread terminates
  taskP.getThread().join();

  task0.getThread().stop();
  task1.getThread().stop();
  task2.getThread().stop();
  task3.getThread().stop();
  task4.getThread().stop();
  task5.getThread().stop();
  task6.getThread().stop();
  task7.getThread().stop();
  task8.getThread().stop();
  task9.getThread().stop();

}

// ============================================================================

// ----------------------------------------------------------------------------

int
main(int argc, char* argv[])
{
  // instantiate the TestSuite, passing the process parameters
  ts.processMainParameters(argc, argv);

  // mark the start of the test suite
  ts.start("portable/core/tests/src/mutexStress.cpp");

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

