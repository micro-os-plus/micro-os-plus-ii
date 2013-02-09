//
//      Copyright (C) 2012-2013 Liviu Ionescu.
//
//      This file is part of the uOS++ distribution.
//

#include "portable/core/include/OS_Defines.h"

#if defined(OS_INCLUDE_PORTABLE_INFRA_TESTSUITE)

#include "portable/core/include/OS.h"

#include "../include/TestSuite.h"
#include "../include/TestSuiteImplementation.h"

#include <string.h>

// We have a single instantiation of this template, so a separate
// header with the template implementation definitions is not needed,
// these definitions can be written directly in the .cpp file.

// However please remember that these are only template definitions,
// to become actual method definitions, the template needs to be
// instantiated (see at the end)

namespace os
{
  namespace infra
  {

    /// \class TestSuite
    ///
    /// \details
    /// Functionality is striped to the bare essential: a `PASS/FAIL`
    /// message in the console and a `<testcase>` line in an XML file,
    /// to be used by continuous integration tools like Jenkins.

    /// \details
    /// Create the default test suite.
    template<class T>
      TestSuite<T>::TestSuite()
          : m_implementation()
      {
        debug.putMethodNameWithAddress(__PRETTY_FUNCTION__, this);

        this->m_pClassName = nullptr; // initialise pointer to class name

        this->m_countPassed = 0; // initialise count of passed tests
        this->m_countFailed = 0; // initialise count of failed tests

        this->m_isXmlOpened = false;
      }

    /// \details
    /// Create a test suite using the process parameters. The parameters
    /// are only passed to the implementation class.
    template<class T>
      TestSuite<T>::TestSuite(int argc, char* argv[])
          : m_implementation(argc, argv)
      {
        debug.putMethodNameWithAddress(__PRETTY_FUNCTION__, this);

        this->m_pClassName = nullptr; // initialise pointer to class name

        this->m_countPassed = 0; // initialise count of passed tests
        this->m_countFailed = 0; // initialise count of failed tests

        this->m_isXmlOpened = false;
      }

    /// \details
    /// Cleanup the test suite.
    template<class T>
      TestSuite<T>::~TestSuite()
      {
        debug.putMethodNameWithAddress(__PRETTY_FUNCTION__, this);
      }

    /// \details
    /// The class name is required to identify the current test
    /// suite in an automated test environment.
    ///
    /// \par Example
    ///
    /// ~~~{.cpp}
    /// setClassName("os::infra::TestSuite");
    /// ~~~
    template<class T>
      void
      TestSuite<T>::setClassName(const char* pName)
      {
        this->m_pClassName = pName;
        outputLine(OutputLineType::CLASS);
      }

    /// \details
    /// Generate an informative START line on the output device.
    template<class T>
      void
      TestSuite<T>::start(const char* pMessage)
      {
        outputLine(OutputLineType::START, pMessage);

        if (m_implementation.createXmlFile() != -1)
          {
            m_isXmlOpened = true;

            // open the jUnit XML elements
            writeStringToXmlFile("<testsuites><testsuite>\n");
          }
      }

    /// \details
    /// Generate a `PASS` line on the output device. If the XML
    ///  output is configured, the `<testcase>` element will be generated.
    template<class T>
      void
      TestSuite<T>::reportPassed(const char* pMessage)
      {
        outputLine(OutputLineType::PASS, pMessage);
        writeToXmlFile(false, pMessage);

        ++(this->m_countPassed); // one more passed test
      }

    /// \details
    /// Generate a `FAIL` line on the output device. If the XML
    /// output is configured, the `<testcase>` element will include a
    /// `<failed/>` element.
    template<class T>
      void
      TestSuite<T>::reportFailed(const char* pMessage)
      {
        outputLine(OutputLineType::FAIL, pMessage);
        writeToXmlFile(true, pMessage);

        ++(this->m_countFailed); // one more failed test
      }

    /// \details
    /// Generate a `PASS/FAIL` line on the output device,
    /// based on the given boolean condition.
    template<class T>
      void
      TestSuite<T>::checkAndReport(bool expression, const char* pMessage)
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

    /// \details
    /// Generate an `INFO` line on the output device.
    template<class T>
      void
      TestSuite<T>::reportInfo(const char* pMessage)
      {
        outputLine(OutputLineType::INFO, pMessage);
      }

    /// \details
    /// Generate an informative `STOP` line on the output device.
    template<class T>
      void
      TestSuite<T>::stop(const char* pMessage)
      {
        outputLine(OutputLineType::STAT);
        outputLine(OutputLineType::STOP, pMessage);

        if (m_isXmlOpened)
          {
            // close the elements opened at START
            writeStringToXmlFile("</testsuite></testsuites>\n");

            m_implementation.closeXmlFile();
            m_isXmlOpened = false;
          }
      }

    /// \details
    /// Prefix the message with a word defining the line type and
    /// send it to the output device.
    template<class T>
      void
      TestSuite<T>::outputLine(OutputLineType_t lineType, const char* pMessage)
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
            putNumber(this->m_countFailed);
            putString(", Passed=");
            putNumber(this->m_countPassed);
          }
        else if (lineType == OutputLineType::CLASS)
          {
            if (m_pClassName != nullptr)
              putString(this->m_pClassName);
          }
        else
          {
            putString(pMessage);
          }
        putString("\"");
        putNewLine();
      }

    /// \details
    /// Compute the string length and write all the string
    /// characters, excluding the terminating '\0' into the XML file.
    template<class T>
      ssize_t
      TestSuite<T>::writeStringToXmlFile(const char* pString)
      {
        if (pString == nullptr)
          return 0;

        size_t len = strlen(pString);
        if (len == 0)
          return 0;

        return m_implementation.writeToXmlFile(pString, len);
      }

    /// \details
    /// Compute the string length and send all the string characters,
    /// excluding the terminating '\0', to the test output device.
    template<class T>
      ssize_t
      TestSuite<T>::putString(const char* pString)
      {
        if (pString == nullptr)
          return 0;

        size_t len = strlen(pString);
        if (len == 0)
          return 0;

        return m_implementation.putBytes(pString, strlen(pString));
      }

    /// \details
    /// Inform the output device that the current line is
    /// completed and request to flush all output and pass to the next line.
    template<class T>
      void
      TestSuite<T>::putNewLine(void)
      {
        return m_implementation.putNewLine();
      }

    /// \details
    /// Convert the integer to ASCII and send it to the test
    /// output device.
    template<class T>
      ssize_t
      TestSuite<T>::putNumber(int n)
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
    template<class T>
      void
      TestSuite<T>::writeToXmlFile(bool isFailure, const char* pMessage)
      {
        if (m_isXmlOpened)
          {
            writeStringToXmlFile("<testcase");

            if (this->m_pClassName)
              {
                writeStringToXmlFile(" classname=\"");
                writeStringToXmlFile(this->m_pClassName);
                writeStringToXmlFile("\"");
              }
            if (pMessage != nullptr)
              {
                writeStringToXmlFile(" name=\"");
                writeStringToXmlFile(pMessage);
                writeStringToXmlFile("\"");
              }

            if (isFailure)
              {
                writeStringToXmlFile("><failure/></testcase>\n");
              }
            else
              {
                writeStringToXmlFile("/>\n");
              }
          }
      }

    /// \details
    /// When integrated in a test environment, the test suite
    /// process shall return 0 if all test cases
    /// passed, and 1 if at least one failed. \n
    /// This method checks the count of failed test cases
    ///  and, if 0, it returns 0, otherwise it return 1.
    template<class T>
      int
      TestSuite<T>::getExitValue(void) const
      {
        return ((m_countFailed == 0) ? 0 : 1);
      }

    // ------------------------------------------------------------------------
    // Explicit instantiation of this template. This must come after
    // the template methods definitions.
    template class TestSuite<TestSuiteImplementation_t> ;

  } /* namespace infra */
} /* namespace os */

#endif /* defined(OS_INCLUDE_PORTABLE_INFRA_TESTSUITE) */

