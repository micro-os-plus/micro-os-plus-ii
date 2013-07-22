//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/OS.h"

#include "portable/infrastructure/include/TestSuite.h"

// This test exercises the creation of os::core::Thread objects.

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

static os::infra::TestSuite ts;

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------

#include "portable/core/include/Thread.h"

constexpr os::core::stack::size_t STACK_SIZE = 30;

// ----------------------------------------------------------------------------

typedef int count_t;

static count_t globalCount = 0;

count_t
getNextGlobalCountValue(void);

count_t
getNextGlobalCountValue(void)
{
  ++globalCount;
#if defined(DEBUG)
  os::diag::trace.putString("New global count=");
  os::diag::trace.putDec(globalCount);
  os::diag::trace.putNewLine();
#endif
  return globalCount;
}

// ----------------------------------------------------------------------------

// this value will be updated by the thread
static count_t cCount = 0;

void
threadCMain(void* pParam);

// Separate C-style thread; in general the parameter can be anything
// but is largely unused; here we pass the thread pointer.
void
threadCMain(void* pParam
#if !defined(DEBUG)
    __attribute__((unused))
#endif
    )
{
#if defined(DEBUG)
  os::diag::trace.putString(__PRETTY_FUNCTION__);
  os::diag::trace.putString(" ");
  os::diag::trace.putHex(pParam);
  os::diag::trace.putNewLine();
#endif
  cCount = getNextGlobalCountValue();
}

static os::core::stack::element_t stackC[hal::arch::MIN_STACK_SIZE
    / sizeof(os::core::stack::element_t)];

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

static os::core::Thread threadC("C", threadCMain, &threadC, stackC, sizeof(stackC));

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------

// C++ style common task, with 1 thread

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

class CommonTask
{
public:
  CommonTask(const char* pName);
  ~CommonTask();

  void
  threadMain(void);

  count_t
  getCount(void);

  os::core::Thread&
  getThread(void);

private:
  count_t m_count;
  os::core::stack::element_t m_stack[hal::arch::MIN_STACK_SIZE
      / sizeof(os::core::stack::element_t)];
  os::core::Thread m_thread;
};

#pragma GCC diagnostic pop

CommonTask::CommonTask(const char* pName)
    : m_thread(pName, [](CommonTask* pTask)
      { pTask->threadMain();}, this, m_stack, sizeof(m_stack))
{
#if defined(DEBUG)
  os::diag::trace.putConstructor();
#endif

  // clear test counter
  m_count = 0;
}

CommonTask::~CommonTask()
{
#if defined(DEBUG)
  os::diag::trace.putDestructor();
#endif
}

inline os::core::Thread&
CommonTask::getThread(void)
{
  return m_thread;
}

inline count_t
CommonTask::getCount(void)
{
#if defined(_DEBUG)
  os::diag::trace.putString("m_count=");
  os::diag::trace.putDec(m_count);
  os::diag::trace.putNewLine();
#endif
  return m_count;
}

void
CommonTask::threadMain(void)
{
#if defined(DEBUG)
  os::diag::trace.putMemberFunction();
#endif
  m_count = getNextGlobalCountValue();
}

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

static CommonTask commonTask1("CT1");
static CommonTask commonTask2("CT2");

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------

// C++ style complex task, with 4 threads

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

class MultiThreadedTask
{
public:
  MultiThreadedTask(void);
  ~MultiThreadedTask();

  static void
  threadMain1(void* pParam);

  // this count will be updated by the thread
  static count_t m_count1;

  void
  threadMain2(void);

  // this count will be updated by the thread
  count_t m_count2;

  // This member function will be used by two threads, called with
  // different parameters
  void
  threadMain3(int i);

  // these counts will be updated by the threads
  count_t m_count3[3];

public:
  os::core::stack::element_t m_stack1[hal::arch::MIN_STACK_SIZE
      / sizeof(os::core::stack::element_t)];
  os::core::Thread m_thread1;

  os::core::stack::element_t m_stack2[hal::arch::MIN_STACK_SIZE
      / sizeof(os::core::stack::element_t)];
  os::core::Thread m_thread2;

  os::core::stack::element_t m_stack3a[hal::arch::MIN_STACK_SIZE
      / sizeof(os::core::stack::element_t)];
  os::core::Thread m_thread3a;

  os::core::stack::element_t m_stack3b[hal::arch::MIN_STACK_SIZE
      / sizeof(os::core::stack::element_t)];
  os::core::Thread m_thread3b;
};

#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif

// Interestingly enough, this has a global constructor (as the manual says)
auto th2 = [](MultiThreadedTask* pTask)
  { pTask->threadMain2();};

#pragma GCC diagnostic pop

MultiThreadedTask::MultiThreadedTask(void)
    : m_thread1("MT1", &threadMain1, this, m_stack1, sizeof(m_stack1)), // with static function
    m_thread2("MT2", th2, this, m_stack2, sizeof(m_stack2)), // with separate lambda
    m_thread3a("MT3A", [](MultiThreadedTask* pTask)
      { pTask->threadMain3(1);}, this, m_stack3a, sizeof(m_stack3a)), // with inline lambda with more params
    m_thread3b("MT3B", [](MultiThreadedTask* pTask)
      { pTask->threadMain3(2);}, this, m_stack3b, sizeof(m_stack3b)) // with inline lambda with more params
{
#if defined(DEBUG)
  os::diag::trace.putConstructor();
#endif

  // clear all test counters
  m_count2 = 0;
  for (size_t i = 0; i < sizeof(m_count3) / sizeof(m_count3[0]); ++i)
    m_count3[i] = 0;
}

MultiThreadedTask::~MultiThreadedTask()
{
#if defined(DEBUG)
  os::diag::trace.putDestructor();
#endif
}

void
MultiThreadedTask::threadMain1(void* pParam
#if !defined(DEBUG)
    __attribute__((unused))
#endif
    )
{
#if defined(DEBUG)
  os::diag::trace.putString(__PRETTY_FUNCTION__);
  os::diag::trace.putString(" ");
  os::diag::trace.putHex(pParam);
  os::diag::trace.putNewLine();
#endif
  m_count1 = getNextGlobalCountValue();
}

void
MultiThreadedTask::threadMain2(void)
{
#if defined(DEBUG)
  os::diag::trace.putMemberFunction();
#endif
  m_count2 = getNextGlobalCountValue();
}

void
MultiThreadedTask::threadMain3(int i)
{
#if defined(DEBUG)
  os::diag::trace.putString(__PRETTY_FUNCTION__);
  os::diag::trace.putString(" ");
  os::diag::trace.putHex(this);
  os::diag::trace.putString(" ");
  os::diag::trace.putDec(i);
  os::diag::trace.putNewLine();
#endif
  if (((size_t) i) < sizeof(m_count3) / sizeof(m_count3[0]))
    m_count3[i] = getNextGlobalCountValue();
}

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

static MultiThreadedTask multiThreadedTask;
count_t MultiThreadedTask::m_count1 = 0;

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------

int
main(int argc, char* argv[])
{
  // instantiate the TestSuite, passing the process parameters
  ts.processMainParameters(argc, argv);

  // mark the start of the test suite
  ts.start("portable/core/tests/src/threads.cpp");

  ts.setClassName("os::core::Thread");

  ts.assertCondition(cCount == 0);
  ts.assertCondition(commonTask1.getCount() == 0);
  ts.assertCondition(commonTask2.getCount() == 0);
  ts.assertCondition(multiThreadedTask.m_count1 == 0);
  ts.assertCondition(multiThreadedTask.m_count2 == 0);
  ts.assertCondition(multiThreadedTask.m_count3[1] == 0);
  ts.assertCondition(multiThreadedTask.m_count3[2] == 0);

  // this order is mandatory, and must match the test below
  threadC.start();
  commonTask1.getThread().start();
  commonTask2.getThread().start();
  multiThreadedTask.m_thread1.start();
  multiThreadedTask.m_thread2.start();
  multiThreadedTask.m_thread3a.start();
  multiThreadedTask.m_thread3b.start();

  os::scheduler.start();

  os::scheduler.stop();

  ts.assertCondition(cCount == 1);
  ts.assertCondition(commonTask1.getCount() == 2);
  ts.assertCondition(commonTask2.getCount() == 3);
  ts.assertCondition(multiThreadedTask.m_count1 == 4);
  ts.assertCondition(multiThreadedTask.m_count2 == 5);
  ts.assertCondition(multiThreadedTask.m_count3[1] == 6);
  ts.assertCondition(multiThreadedTask.m_count3[2] == 7);

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

