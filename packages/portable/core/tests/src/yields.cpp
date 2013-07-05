//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/OS.h"

#include "portable/infrastructure/include/TestSuite.h"

// This test exercises the scheduler.yield() call.

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

os::infra::TestSuite ts;

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------

#include "portable/core/include/Thread.h"

static const os::core::Stack::size_t STACK_SIZE = 30;

typedef int count_t;

// ----------------------------------------------------------------------------

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

// C++ style common task, with 1 thread

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

class Task
{
public:
  Task(const char* pName);
  ~Task();

  void
  threadMain();

  count_t
  getCount1(void);

  count_t
  getCount2(void);

  os::core::Thread&
  getThread(void);

private:
  count_t m_count1;
  count_t m_count2;

  os::core::Stack::element_t m_stack[STACK_SIZE];
  os::core::Thread m_thread;
};

#pragma GCC diagnostic pop

Task::Task(const char* pName)
    : m_thread(pName, [](Task* pTask)
      { pTask->threadMain();}, this, m_stack,
        sizeof(m_stack) / sizeof(m_stack[0]))
{
#if defined(DEBUG)
  os::diag::trace.putConstructor();
#endif

  // clear test counter
  m_count1 = 0;
  m_count2 = 0;
}

Task::~Task()
{
#if defined(DEBUG)
  os::diag::trace.putDestructor();
#endif
}

inline count_t
Task::getCount1(void)
{
#if defined(_DEBUG)
  os::diag::trace.putString("m_count1=");
  os::diag::trace.putDec(m_count1);
  os::diag::trace.putNewLine();
#endif
  return m_count1;
}

inline count_t
Task::getCount2(void)
{
#if defined(_DEBUG)
  os::diag::trace.putString("m_count2=");
  os::diag::trace.putDec(m_count2);
  os::diag::trace.putNewLine();
#endif
  return m_count2;
}

void
Task::threadMain(void)
{
#if defined(DEBUG)
  os::diag::trace.putMemberFunction();
#endif

  m_count1 = getNextGlobalCountValue();
  os::scheduler.yield();
  m_count2 = getNextGlobalCountValue();
  os::scheduler.yield();
}

os::core::Thread&
Task::getThread(void)
{
  return m_thread;
}

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

Task task1("T1");
Task task2("T2");
Task task3("T3");

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------

int
main(int argc, char* argv[])
{
  // instantiate the TestSuite, passing the process parameters
  ts.processMainParameters(argc, argv);

  // mark the start of the test suite
  ts.start("portable/core/tests/src/yields.cpp");

  ts.setClassName("os::core::Thread");

  ts.assertCondition(task1.getCount1() == 0);
  ts.assertCondition(task1.getCount2() == 0);
  ts.assertCondition(task2.getCount1() == 0);
  ts.assertCondition(task2.getCount2() == 0);
  ts.assertCondition(task3.getCount1() == 0);
  ts.assertCondition(task3.getCount2() == 0);

  os::scheduler.run();

  task1.getThread().join();
  task2.getThread().join();
  task3.getThread().join();


#if defined(DEBUG)
  os::diag::trace << os::std::dec << task1.getCount1() << " "
      << task1.getCount2() << os::std::endl;
  os::diag::trace << os::std::dec << task2.getCount1() << " "
      << task2.getCount2() << os::std::endl;
  os::diag::trace << os::std::dec << task3.getCount1() << " "
      << task3.getCount2() << os::std::endl;
#endif

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

