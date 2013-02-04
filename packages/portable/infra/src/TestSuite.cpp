/*
 *      Copyright (C) 2012-2013 Liviu Ionescu.
 *
 *      This file is part of the uOS++ distribution.
 */

#include "portable/core/include/OS_Defines.h"

#if defined(OS_INCLUDE_PORTABLE_INFRA_TESTSUITE)

#include "../include/TestSuite.h"
#include "../include/TestSuiteImplementation.h"

#include "portable/core/include/OS.h"

//#include "portable/devices/debug/include/Debug.h"

#include <string.h>

namespace os
{
  namespace infra
  {

    TestSuite::TestSuite()
    {
      debug.putMethodNameWithAddress(__PRETTY_FUNCTION__, this);

      this->pClassName = 0;     // initialise pointer to class name

      this->countPassed = 0;    // initialise count of passed tests
      this->countFailed = 0;    // initialise count of failed tests

      this->xmlFileDescriptor = -1; // set file descriptor to none
    }

    TestSuite::~TestSuite()
    {
      if (this->xmlFileDescriptor != -1)
        {
          // if the file descriptor was opened, close it now
          os::infra::TestSuiteImplementation::closeFile(
              this->xmlFileDescriptor);
        }
      debug.putMethodNameWithAddress(__PRETTY_FUNCTION__, this);
    }

    void
    TestSuite::parseParameters(int argc, char* argv[])
    {
      char* fileName = 0;
      fileName = os::infra::TestSuiteImplementation::getFileNamePointer(argc,
          argv);
      // Warning: the pointer is to the argv array, bu this is not fatal, since
      // the array is static.

      if (fileName != 0)
        {
          int fd;
          fd = os::infra::TestSuiteImplementation::createFile(fileName);
          if (fd != -1)
            {
              this->xmlFileDescriptor = fd;
            }
        }
    }

    void
    TestSuite::start(const char* pMessage) const
    {
      outputLine(OutputLineType::START, pMessage);

      if (this->xmlFileDescriptor != -1)
        {
          // open the jUnit XML elements
          writeStringToFile("<testsuites><testsuite>\n");
        }
    }

    void
    TestSuite::pass(const char* pMessage)
    {
      outputLine(OutputLineType::PASS, pMessage);
      writeToXmlFile(false, pMessage);

      ++(this->countPassed); // one more passed test
    }

    void
    TestSuite::fail(const char* pMessage)
    {
      outputLine(OutputLineType::FAIL, pMessage);
      writeToXmlFile(true, pMessage);

      ++(this->countFailed); // one more failed test
    }

    void
    TestSuite::check(bool expression, const char* pMessage)
    {
      if (expression)
        {
          pass(pMessage);
        }
      else
        {
          fail(pMessage);
        }
    }

    void
    TestSuite::info(const char* pMessage) const
    {
      outputLine(OutputLineType::INFO, pMessage);
    }

    void
    TestSuite::stop(const char* pMessage) const
    {
      outputLine(OutputLineType::STAT, 0);
      outputLine(OutputLineType::STOP, pMessage);

      if (this->xmlFileDescriptor != -1)
        {
          // close the elements opened at START
          writeStringToFile("</testsuite></testsuites>\n");
        }
    }

    void
    TestSuite::outputLine(OutputLineType_t lineType, const char* pMessage) const
    {
      const char* pStr;
      switch (lineType)
        {
      case OutputLineType::START:
        pStr = "START";
        break;
      case OutputLineType::STOP:
        pStr = "STOP";
        break;
      case OutputLineType::PASS:
        pStr = "PASS";
        break;
      case OutputLineType::FAIL:
        pStr = "FAIL";
        break;
      case OutputLineType::INFO:
        pStr = "INFO";
        break;
      case OutputLineType::STAT:
        pStr = "STAT";
        break;
      default:
        pStr = "????";
        break;
        }

      putString(pStr);
      putString(":");
      putString("\"");
      if (lineType == OutputLineType::START)
        {
          putString("Starting tests from '");
          putString(pMessage);
          putString("'");
        }
      else if (lineType == OutputLineType::STOP)
        {
          putString("Completing tests from '");
          putString(pMessage);
          putString("'");
        }
      else if (lineType == OutputLineType::STAT)
        {
          putString("Failed=");
          putNumber(this->countFailed);
          putString(", Passed=");
          putNumber(this->countPassed);
        }
      else
        {
          putString(pMessage);
        }
      putString("\"");
      putNewLine();
    }

    ssize_t
    TestSuite::writeStringToFile(const char* pString) const
    {
      if (pString == 0)
        return 0;

      size_t len = strlen(pString);
      if (len == 0)
        return 0;

      return os::infra::TestSuiteImplementation::writeFile(
          this->xmlFileDescriptor, pString, len);
    }

    ssize_t
    TestSuite::putString(const char* pString) const
    {
      if (pString == 0)
        return 0;

      size_t len = strlen(pString);
      if (len == 0)
        return 0;

      return os::infra::TestSuiteImplementation::putBytes(pString,
          strlen(pString));
    }

    void
    TestSuite::putNewLine(void) const
    {
      return os::infra::TestSuiteImplementation::putNewLine();
    }

    ssize_t
    TestSuite::putNumber(int n) const
    {
      char buf[10];

      bool isNegative;
      isNegative = false;

      if (n < 0)
        {
          isNegative = true;
          n = -n;
        }

      int i = sizeof(buf);
      buf[--i] = '\0';

      for (;;)
        {
          buf[--i] = ('0' + (n % 10));
          n = (n / 10);
          if (n == 0)
            break;

          if (i <= 1)
            break;
        }

      if (isNegative)
        {
          buf[--i] = '-';
        }

      return putString(&buf[i]);
    }

    /// The JUnit XML looks like this:
    ///
    /// ~~~
    /// <testsuites><testsuite>
    ///   <testcase classname="os::infra::TestSuite" name="check true constant"/>
    ///   <testcase classname="os::infra::TestSuite" name="check false constant"><failure/></testcase>
    ///   <testcase classname="os::infra::TestSuite" name="a passed test"/>
    ///   <testcase classname="os::infra::TestSuite" name="a failed test"><failure/></testcase>
    /// </testsuite></testsuites>
    /// ~~~

    void
    TestSuite::writeToXmlFile(bool isFailure, const char* pMessage)
    {
      if (this->xmlFileDescriptor != -1)
        {
          writeStringToFile("<testcase");

          if (this->pClassName)
            {
              writeStringToFile(" classname=\"");
              writeStringToFile(this->pClassName);
              writeStringToFile("\"");
            }
          if (pMessage != 0)
            {
              writeStringToFile(" name=\"");
              writeStringToFile(pMessage);
              writeStringToFile("\"");
            }

          if (isFailure)
            {
              writeStringToFile("><failure/></testcase>\n");
            }
          else
            {
              writeStringToFile("/>\n");
            }
        }
    }

    // return 0 if there are no failed test cases
    int
    TestSuite::getExitValue(void) const
    {
      return ((this->countFailed == 0) ? 0 : 1);
    }

  } /* namespace infra */
} /* namespace os */

// The test main() function.
// It creates a test class instance and all
// actions happen within its context, in the run() method.

int
main(int argc, char* argv[])
{
  os::infra::TestSuite testSuite;

  testSuite.parseParameters(argc, argv);

  testSuite.run();

  int retval;
  retval = testSuite.getExitValue();

  debug.putString("::main() returns ");
  debug.putDec(retval);
  debug.putNewLine();

  // return 0 if there are no failed test cases
  return retval;
}

#endif /* defined(OS_INCLUDE_PORTABLE_INFRA_TESTSUITE) */

