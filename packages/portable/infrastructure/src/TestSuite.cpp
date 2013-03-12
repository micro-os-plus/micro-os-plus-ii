//
//      Copyright (C) 2012-2013 Liviu Ionescu.
//
//      This file is part of the uOS++ distribution.
//

#include "portable/core/include/OS_Defines.h"

#if defined(OS_INCLUDE_PORTABLE_INFRASTRUCTURE_TESTSUITE) || defined(__DOXYGEN__)

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
    template<class ImplT>
      TestSuite<ImplT>::TestSuite()
          : m_implementation()
      {
        debug.putMethodNameWithAddress(__PRETTY_FUNCTION__, this);

        TestSuite<ImplT>::__init();
      }

    /// \details
    /// Create a test suite using the process parameters. The parameters
    /// are only passed to the implementation class.
    template<class ImplT>
      TestSuite<ImplT>::TestSuite(int argc, char* argv[])
          : m_implementation(argc, argv)
      {
        debug.putMethodNameWithAddress(__PRETTY_FUNCTION__, this);

        TestSuite<ImplT>::__init();
      }

    /// \details
    /// Clear all members, pointers and counters. Intended to be called
    /// from constructors.
    template<class ImplT>
      void
      TestSuite<ImplT>::__init(void)
      {
        m_pClassName = nullptr; // initialise pointer to class name
        m_pMethodName = nullptr; // initialise pointer to method name
        m_pInputValues = nullptr; // initialise pointer to input values
        m_pPreconditions = nullptr; // initialise pointer to preconditions

        m_countPassed = 0; // initialise count of passed tests
        m_countFailed = 0; // initialise count of failed tests

        m_isXmlOpened = false;
      }

    /// \details
    /// Cleanup the test suite.
    template<class ImplT>
      TestSuite<ImplT>::~TestSuite()
      {
        debug.putMethodNameWithAddress(__PRETTY_FUNCTION__, this);
      }

    template<class ImplT>
      void
      TestSuite<ImplT>::processMainParameters(int argc, char* argv[])
      {
        m_implementation.processMainParameters(argc, argv);
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
    template<class ImplT>
      void
      TestSuite<ImplT>::setClassName(const char* pName)
      {
        m_pClassName = pName;
        outputLine(OutputLineType::CLASS);

        setMethodNameOrPrefix(nullptr);
      }

    /// \details
    /// The Method name is used to prefix the test case message and is
    /// required to uniquely identify the current test
    /// case in an automated test environment that collects statistics
    /// based on the message.
    ///
    /// In practical terms, if you test the same condition multiple times,
    /// be sure you prefix it with different names, to make the string unique.
    ///
    /// \par Example
    ///
    /// ~~~{.cpp}
    /// setMethodNameOrPrefix("clear(iostate)");
    /// ~~~
    template<class ImplT>
      void
      TestSuite<ImplT>::setMethodNameOrPrefix(const char* pName)
      {
        m_pMethodName = pName;
        m_pInputValues = nullptr;
        m_pPreconditions = nullptr;
      }

    template<class ImplT>
      void
      TestSuite<ImplT>::setInputValues(const char* pStr)
      {
        m_pInputValues = pStr;
      }

    template<class ImplT>
      void
      TestSuite<ImplT>::setPreconditions(const char* pStr)
      {
        m_pPreconditions = pStr;
      }

    /// \details
    /// Generate an informative START line on the output device.
    template<class ImplT>
      void
      TestSuite<ImplT>::start(const char* pMessage)
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
    template<class ImplT>
      void
      TestSuite<ImplT>::reportPassed(const char* pMessage)
      {
        // increment early, to start the counter from 1
        ++(this->m_countPassed); // one more passed test
        outputLine(OutputLineType::PASS, pMessage);
        writeTestCaseToXmlFile(false, pMessage);
      }

    /// \details
    /// Generate a `FAIL` line on the output device. If the XML
    /// output is configured, the `<testcase>` element will include a
    /// `<failed/>` element.
    template<class ImplT>
      void
      TestSuite<ImplT>::reportFailed(const char* pMessage)
      {
        // increment early, to start the counter from 1
        ++(this->m_countFailed); // one more failed test

        outputLine(OutputLineType::FAIL, pMessage);
        writeTestCaseToXmlFile(true, pMessage);

      }

    /// \details
    /// Generate a `PASS/FAIL` line on the output device,
    /// based on the given boolean condition.
    template<class ImplT>
      void
      TestSuite<ImplT>::checkAndReport(bool expression, const char* pMessage)
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
    template<class ImplT>
      void
      TestSuite<ImplT>::reportInfo(const char* pMessage)
      {
        outputLine(OutputLineType::INFO, pMessage);
      }

    /// \details
    /// Generate an informative `STOP` line on the output device.
    template<class ImplT>
      void
      TestSuite<ImplT>::stop(const char* pMessage)
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
    ///
    /// For PASS/FAIL lines, the message is
    /// prefixed with the method name, input values and preconditions, if
    /// defined.

  template<class ImplT>
      void
      TestSuite<ImplT>::outputLine(OutputLineType_t lineType, const char* pMessage)
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
        if (lineType == OutputLineType::PASS
            || lineType == OutputLineType::FAIL)
          {
            putNumber(static_cast<int>(getCurrentTestCaseNumber()));
            putString(",");
          }
        putString("\"");

        if ((lineType == OutputLineType::PASS
            || lineType == OutputLineType::FAIL) && (m_pMethodName != nullptr))
          {
            putString(m_pMethodName);
            if (m_pInputValues != nullptr)
              {
                putString(" (");
                putString(m_pInputValues);
                putString(")");
              }
            if (m_pPreconditions != nullptr)
              {
                putString(" with ");
                putString(m_pPreconditions);
              }
            putString(" --- ");
          }

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
            if (m_countFailed == 0)
              {
                putString("Failed=");
                putNumber(static_cast<int>(m_countFailed));
                putString(", PASSED=");
                putNumber(static_cast<int>(m_countPassed));
                putString(", ALLES IN ORDNUNG! :-) +++++ :-) +++++ :-) ");
              }
            else
              {
                putString("FAILED=");
                putNumber(static_cast<int>(m_countFailed));
                putString(", Passed=");
                putNumber(static_cast<int>(m_countPassed));
                putString(", PROBLEMS?... :-( ----- :-( ----- :-( ");
              }
          }
        else if (lineType == OutputLineType::CLASS)
          {
            if (m_pClassName != nullptr)
              putString(m_pClassName);
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
    template<class ImplT>
      ssize_t
      TestSuite<ImplT>::writeStringToXmlFile(const char* pString)
      {
        if (pString == nullptr)
          return 0;

        size_t len = strlen(pString);
        if (len == 0)
          return 0;

        return m_implementation.writeToXmlFile(pString, len);
      }

    /// \details
    /// Convert the number to ASCII and write it to the XML file.
    template<class ImplT>
      ssize_t
      TestSuite<ImplT>::writeCounterToXmlFile(unsigned int number)
      {
        char buf[10];

        int i = sizeof(buf);
        buf[--i] = '\0';

        for (;;)
          {
            buf[--i] = ('0' + (number % 10));
            number = (number / 10);
            if (number == 0)
              break;

            if (i <= 1)
              break;
          }

        return writeStringToXmlFile(&buf[i]);

      }

    /// \details
    /// Compute the string length and send all the string characters,
    /// excluding the terminating '\0', to the test output device.
    template<class ImplT>
      ssize_t
      TestSuite<ImplT>::putString(const char* pString)
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
    template<class ImplT>
      void
      TestSuite<ImplT>::putNewLine(void)
      {
        return m_implementation.putNewLine();
      }

    /// \details
    /// Convert the integer to ASCII and send it to the test
    /// output device.
    template<class ImplT>
      ssize_t
      TestSuite<ImplT>::putNumber(int number)
      {
        char buf[10];

        bool isNegative;
        isNegative = false;

        if (number < 0)
          {
            isNegative = true;
            number = -number;
          }

        int i = sizeof(buf);
        buf[--i] = '\0';

        for (;;)
          {
            buf[--i] = ('0' + (number % 10));
            number = (number / 10);
            if (number == 0)
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
    template<class ImplT>
      void
      TestSuite<ImplT>::writeTestCaseToXmlFile(bool isFailure, const char* pMessage)
      {
        if (m_isXmlOpened)
          {
            writeStringToXmlFile("<testcase");

            if (m_pClassName)
              {
                writeStringToXmlFile(" classname=\"");
                writeStringToXmlFile(m_pClassName);
                writeStringToXmlFile("\"");
              }
            if (pMessage != nullptr)
              {
                writeStringToXmlFile(" name=\"");
                if (m_pMethodName != nullptr)
                  {
                    writeStringToXmlFile(m_pMethodName);
                    writeStringToXmlFile(" ");
                  }
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
    template<class ImplT>
      int
      TestSuite<ImplT>::getExitValue(void) const
      {
        return ((m_countFailed == 0) ? 0 : 1);
      }

    // ------------------------------------------------------------------------
    // Explicit instantiation of this template. This must come after
    // the template methods definitions.
    template class TestSuite<TestSuiteImplementation_t> ;

  } /* namespace infra */
} /* namespace os */

#endif /* defined(OS_INCLUDE_PORTABLE_INFRASTRUCTURE_TESTSUITE) */

