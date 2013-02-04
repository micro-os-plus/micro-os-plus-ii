//
//      Copyright (C) 2012-2013 Liviu Ionescu.
//
//      This file is part of the uOS++ distribution.
//

#include "portable/core/include/OS_Defines.h"

#if defined(OS_INCLUDE_PORTABLE_INFRA_TESTSUITE)

#include "../include/TestSuite.h"
#include "../include/TestSuiteImplementation.h"

#include "portable/core/include/OS.h"

/// \class os::infra::TestSuite
///
/// This class implements a simple test suite, to be used by µOS++ unit
/// tests.
///
/// Functionality is striped to the bare essential: a `PASS/FAIL`
/// message in the console and a `<testcase>` line in an XML file,
/// to be used by
/// continuous integration tools like Jenkins.
/// ___
#include <string.h>

namespace os
{
  namespace infra
  {

    /// \par Description
    ///
    /// \details
    /// Create the test suite, clear all fields.
    /// ___
    TestSuite::TestSuite()
    {
      debug.putMethodNameWithAddress(__PRETTY_FUNCTION__, this);

      this->pClassName = nullptr; // initialise pointer to class name

      this->countPassed = 0;    // initialise count of passed tests
      this->countFailed = 0;    // initialise count of failed tests

      this->xmlFileDescriptor = -1; // set file descriptor to none
    }

    /// \par Description
    ///
    /// \details
    /// Cleanup the test suite, eventually close the XML file.
    /// ___
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

    /// \par Description
    ///
    /// \details
    /// Process the command line parameters. If `-j filename` is
    /// encountered, the given file is used to output the XML formated test
    /// suite results.
    /// ___
    void
    TestSuite::parseParameters(int argc, char* argv[])
    {
      char* fileName = nullptr;
      fileName = os::infra::TestSuiteImplementation::getFileNamePointer(argc,
          argv);
      // Warning: the pointer is to the argv array, bu this is not fatal, since
      // the array is static.

      if (fileName != nullptr)
        {
          int fd;
          fd = os::infra::TestSuiteImplementation::createFile(fileName);
          if (fd != -1)
            {
              this->xmlFileDescriptor = fd;
            }
        }
    }

    /// \par Description
    ///
    /// \details
    /// The class name is required to identify the current test
    /// suite in an automated test environment.
    ///
    /// \par Example
    ///
    /// ~~~{.cpp}
    /// setClassName("os::infra::TestSuite");
    /// ~~~
    /// ___
    void
    TestSuite::setClassName(const char* pName)
    {
      this->pClassName = pName;
      outputLine(OutputLineType::CLASS);
    }

    /// \par Description
    ///
    /// \details
    /// Generate an informative START line on the output device.
    /// ___
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

    /// \par Description
    ///
    /// \details
    /// Generate a `PASS` line on the output device. If the XML
    ///  output is configured, the `<testcase>` element will be generated.
    /// ___
    void
    TestSuite::reportPassed(const char* pMessage)
    {
      outputLine(OutputLineType::PASS, pMessage);
      writeToXmlFile(false, pMessage);

      ++(this->countPassed); // one more passed test
    }

    /// \par Description
    ///
    /// \details
    /// Generate a `FAIL` line on the output device. If the XML
    /// output is configured, the `<testcase>` element will include a
    /// `<failed/>` element.
    /// ___
    void
    TestSuite::reportFailed(const char* pMessage)
    {
      outputLine(OutputLineType::FAIL, pMessage);
      writeToXmlFile(true, pMessage);

      ++(this->countFailed); // one more failed test
    }

    /// \par Description
    ///
    /// \details
    /// Generate a `PASS/FAIL` line on the output device,
    /// based on the given boolean condition.
    /// ___
    void
    TestSuite::checkAndReport(bool expression, const char* pMessage)
    {
      if (expression)
        {
          reportPassed(pMessage);
        }
      else
        {
          reportFailed(pMessage);
        }
    }

    /// \par Description
    ///
    /// \details
    /// Generate an `INFO` line on the output device.
    /// ___
    void
    TestSuite::reportInfo(const char* pMessage) const
    {
      outputLine(OutputLineType::INFO, pMessage);
    }

    /// \par Description
    ///
    /// \details
    /// Generate an informative `STOP` line on the output device.
    /// ___
    void
    TestSuite::stop(const char* pMessage) const
    {
      outputLine(OutputLineType::STAT);
      outputLine(OutputLineType::STOP, pMessage);

      if (this->xmlFileDescriptor != -1)
        {
          // close the elements opened at START
          writeStringToFile("</testsuite></testsuites>\n");
        }
    }

    /// \par Description
    ///
    /// \details
    /// Prefix the message with a word defining the line type and
    /// send it to the output device.
    /// ___
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
      case OutputLineType::CLASS:
        pStr = "CLASS";
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
      else if (lineType == OutputLineType::CLASS)
        {
          if (pClassName != nullptr)
            putString(this->pClassName);
        }
      else
        {
          putString(pMessage);
        }
      putString("\"");
      putNewLine();
    }

    /// \par Description
    ///
    /// \details
    /// Compute the string length and write all the string
    /// characters, excluding the terminating '\0' into the XML file.
    /// ___
    ssize_t
    TestSuite::writeStringToFile(const char* pString) const
    {
      if (pString == nullptr)
        return 0;

      size_t len = strlen(pString);
      if (len == 0)
        return 0;

      return os::infra::TestSuiteImplementation::writeFile(
          this->xmlFileDescriptor, pString, len);
    }

    /// \par Description
    ///
    /// \details
    /// Compute the string length and send all the string characters,
    /// excluding the terminating '\0', to the test output device.
    /// ___
    ssize_t
    TestSuite::putString(const char* pString) const
    {
      if (pString == nullptr)
        return 0;

      size_t len = strlen(pString);
      if (len == 0)
        return 0;

      return os::infra::TestSuiteImplementation::putBytes(pString,
          strlen(pString));
    }

    /// \par Description
    ///
    /// \details
    /// Inform the output device that the current line is
    /// completed and request to flush all output and pass to the next one.
    /// ___
    void
    TestSuite::putNewLine(void) const
    {
      return os::infra::TestSuiteImplementation::putNewLine();
    }

    /// \par Description
    ///
    /// \details
    /// Convert the integer to ascii and send it to the test
    /// output device.
    /// ___
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

    /// \par Description
    ///
    /// \details
    /// The format used for the XML is the one defined in JUnit.
    ///
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
    ///
    /// ___
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
          if (pMessage != nullptr)
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

    /// \par Description
    ///
    /// \details The test suite process shall return 0 if all test cases
    /// passed, and 1 if at least one failed. This method checks the
    /// count of failed test cases and returns 0 if none.
    /// ___
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

