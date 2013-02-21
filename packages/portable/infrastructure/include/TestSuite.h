//
//      Copyright (C) 2012-2013 Liviu Ionescu.
//
//      This file is part of the uOS++ distribution.
//

#ifndef OS_PORTABLE_INFRASTRUCTURE_TESTSUITE_H_
#define OS_PORTABLE_INFRASTRUCTURE_TESTSUITE_H_

#include "portable/core/include/OS_Defines.h"

#if defined(OS_INCLUDE_PORTABLE_INFRASTRUCTURE_TESTSUITE) || defined(__DOXYGEN__)

#include "TestSuiteImplementation.h"

#include <stdint.h>

namespace os
{
  namespace infra
  {

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"

    /// \example portable/infrastructure/tests/TestSuite/src/main.cpp
    /// This test exercises all TestSuite methods. It currently runs on
    /// OS X, as a 64 bit process.
    ///
    /// The program was called with the following arguments:
    /// ~~~
    /// $ testsuite -x junit.xml
    /// ~~~
    ///
    /// The output produced by the Release build was:
    /// ~~~
    /// CLASS:"os::infra::TestSuite"
    /// START:"Starting tests from '/Users/ilg/My Files/MacBookPro Projects/uOS/micro-os-plus-se.git/packages/portable/infrastructure/tests/TestSuite/src/main.cpp'"
    /// PASS:"check true constant"
    /// FAIL:"check false constant"
    /// PASS:"a passed test"
    /// FAIL:"a failed test"
    /// INFO:"there should be 2 failed cases and 2 passed cases"
    /// STAT:"Failed=2, Passed=2"
    /// STOP:"Completing tests from '/Users/ilg/My Files/MacBookPro Projects/uOS/micro-os-plus-se.git/packages/portable/infrastructure/tests/TestSuite/src/main.cpp'"
    /// ~~~
    ///
    /// The XML output was:
    /// ~~~
    /// <testsuites><testsuite>
    /// <testcase classname="os::infra::TestSuite" name="check true constant"/>
    /// <testcase classname="os::infra::TestSuite" name="check false constant"><failure/></testcase>
    /// <testcase classname="os::infra::TestSuite" name="a passed test"/>
    /// <testcase classname="os::infra::TestSuite" name="a failed test"><failure/></testcase>
    /// </testsuite></testsuites>
    /// ~~~
    /// The process exit value was 1 (failed).

    /// \class TestSuite TestSuite.h "portable/infrastructure/include/TestSuite.h"
    /// \brief Simple test suite class.

    /// \details
    /// The TestSuite class implements a light test framework, designed for
    /// the µOS++ unit tests. The test will generally run on synthetic
    /// platforms, as regular user processes.

    template<class T>
      class TestSuite
      {

      public:

        /// \brief Simple constructor.
        /// \par Parameters
        ///       None
        TestSuite();

        /// \brief Constructor with main() style parameters
        ///
        /// \param [in] argc count of arguments.
        /// \param [in] argv array of pointer to strings.
        TestSuite(int argc, char* argv[]);

        /// \brief Destructor.
        ~TestSuite();

        /// \brief Process main() style parameters
        ///
        /// \param [in] argc count of arguments.
        /// \param [in] argv array of pointer to strings.
        void
        processMainParameters(int argc, char* argv[]);

        /// \brief Set the name of the tested class.
        ///
        /// \param [in] pName a string containing the class name, usually with
        /// full name space definitions.
        /// \par Returns
        ///       Nothing
        void
        setClassName(const char* pName);

        /// \brief Report the start of the test suite.
        ///
        /// \param [in] pMessage a string identifying the test suite, usually
        /// the compiler `__FILE__` builtin macro definition.
        /// \par Returns
        ///       Nothing
        void
        start(const char* pMessage);

        /// \brief Check condition and report a test case result.
        ///
        /// \param [in] expression the boolean condition to be tested.
        /// \param [in] pMessage a string identifying the test case.
        /// \par Returns
        ///       Nothing
        void
        checkAndReport(bool expression, const char* pMessage);

/// \brief Check expression and report an result identical to the expression.
/// \details This is one of the few cases when macros are really needed,
/// to avoid writing the expression twice, first as expression and
/// then as string.
#define assertCondition(e) checkAndReport((e), #e)

        /// \brief Report a successful test case.
        ///
        /// \param [in] pMessage a string identifying the test case.
        /// \par Returns
        ///       Nothing
        void
        reportPassed(const char* pMessage);

        /// \brief Report a failed test case.
        ///
        /// \param [in] pMessage a string identifying the test case.
        /// \par Returns
        ///       Nothing
        void
        reportFailed(const char* pMessage);

        /// \brief Display an informative line.
        ///
        /// \param [in] pMessage a string with the informative message.
        /// \par Returns
        ///       Nothing
        void
        reportInfo(const char* pMessage);

        /// \brief Report the completion of the test suite.
        ///
        /// \param [in] pMessage a string identifying the test suite, usually
        /// the compiler `__FILE__` builtin macro definition.
        /// \par Returns
        ///       Nothing
        void
        stop(const char* pMessage);

        /// \brief Compute the value to be returned by main().
        ///
        /// \par Parameters
        /// None
        /// \retval 0 Test suite succeeded.
        /// \retval 1 Test suite failed.
        int
        getExitValue(void) const;

      private:

        /// \brief Define the type of the line to display.
        ///
        /// \details Used as parameter for outputLine() to add a prefix
        /// for each line generated.
        typedef int OutputLineType_t;

        /// \brief Enumerate all known line types.
        enum OutputLineType
          : OutputLineType_t
            {
              START = 1, INFO, PASS, FAIL, STAT, CLASS, STOP
        };

        /// \brief Generate a test case line and send it to the output device.
        ///
        /// \param [in] lineType a constant to specify the line prefix.
        /// \param [in] pMessage a string containing the line message.
        /// \par Returns
        ///       Nothing
        void
        outputLine(OutputLineType_t lineType, const char* pMessage = nullptr);

        /// \brief Generate a test case XML element and write it to the
        /// configured file.
        ///
        /// \param [in] isFailure mark this test case as a failure.
        /// \param [in] pMessage a string containing the test case message.
        /// \par Returns
        ///       Nothing
        void
        writeToXmlFile(bool isFailure, const char* pMessage);

        /// \brief Write a null terminated string to the XML file.
        ///
        /// \param [in] pString a string.
        ///
        /// \return The actual number of bytes written to the file.
        ssize_t
        writeStringToXmlFile(const char* pString);

        /// \brief Display a null terminated string to the test output device.
        ///
        /// \param [in] pString a string.
        ///
        /// \return The actual number of bytes written to the output device.
        ssize_t
        putString(const char* pString);

        /// \brief Display a decimal integer to the test output device.
        ///
        /// \param [in] number an integer number.
        ///
        /// \return The actual number of bytes written to the output device.
        ssize_t
        putNumber(int number);

        /// \brief Send a new line to the test output device.
        /// \par Parameters
        ///       None
        /// \par Returns
        ///       Nothing
        void
        putNewLine(void);

        /// \brief The pointer to the class name string.
        const char* m_pClassName;

        /// \brief The accumulated number of passed test cases.
        int m_countPassed;

        /// \brief The accumulated number of failed test cases.
        int m_countFailed;

        /// \brief The boolean status of XML output.
        bool m_isXmlOpened;

        /// \brief The actual platform implementation.
        T m_implementation;
      };
    // class TestSuite

    //------------------------------------------------------------------------
    /// \brief Define a TestSuite type based on the template.
    typedef TestSuite<TestSuiteImplementation_t> TestSuite_t;

#pragma GCC diagnostic pop

  } // namespace infra
} // namespace os

#endif /* defined(OS_INCLUDE_PORTABLE_INFRASTRUCTURE_TESTSUITE) */

#endif /* #define OS_PORTABLE_INFRASTRUCTURE_TESTSUITE_H_ */
