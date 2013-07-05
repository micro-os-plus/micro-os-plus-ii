//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief TestSuite template declarations.

#ifndef OS_PORTABLE_INFRASTRUCTURE_TESTSUITE_H_
#define OS_PORTABLE_INFRASTRUCTURE_TESTSUITE_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_INFRASTRUCTURE_TESTSUITE) || defined(__DOXYGEN__)

#include "hal/architecture/infrastructure/include/TestSuiteImplementation.h"

#include <stdint.h>

namespace os
{
  namespace infra
  {

    // ========================================================================

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

    /// This test exercises all TestSuite member functions. It currently
    /// runs on
    /// OS X, as a 64 bit process.
    ///
    /// The program was called with the following arguments:
    /// \code{.cpp}
    /// $ testsuite -x junit.xml
    /// \endcode
    ///
    /// The output produced by the Release build was:
    /// \code{.cpp}
    /// CLASS:"os::infra::TestSuite"
    /// START:"Starting tests from '/Users/ilg/My Files/MacBookPro Projects/uOS/micro-os-plus-se.git/packages/portable/infrastructure/tests/src/testsuite.cpp'"
    /// PASS:"check true constant"
    /// FAIL:"check false constant"
    /// PASS:"a passed test"
    /// FAIL:"a failed test"
    /// INFO:"there should be 2 failed cases and 2 passed cases"
    /// STAT:"Failed=2, Passed=2"
    /// STOP:"Completing tests from '/Users/ilg/My Files/MacBookPro Projects/uOS/micro-os-plus-se.git/packages/portable/infrastructure/tests/src/testsuite.cpp'"
    /// \endcode
    ///
    /// The XML output was:
    /// \code{.cpp}
    /// <testsuites><testsuite>
    /// <testcase classname="os::infra::TestSuite" name="check true constant"/>
    /// <testcase classname="os::infra::TestSuite" name="check false constant"><failure/></testcase>
    /// <testcase classname="os::infra::TestSuite" name="a passed test"/>
    /// <testcase classname="os::infra::TestSuite" name="a failed test"><failure/></testcase>
    /// </testsuite></testsuites>
    /// \endcode
    /// The process exit value was 1 (failed).

    /// \headerfile TestSuite.h "portable/infrastructure/include/TestSuite.h"
    /// \nosubgrouping
    /// \brief Simple test suite template base.
    ///
    /// \details
    /// The TestSuite class implements a light test framework, designed for
    /// the µOS++ unit tests. The test will generally run on synthetic
    /// platforms, as regular user processes.
    ///
    /// When using automated testing frameworks, like Jenkins, it is
    /// important to generate unique test case descriptions. To help this
    /// the test condition can be prefixed with the member function name,
    /// a list
    /// of input values used to call the member function, and a list
    /// of preconditions
    /// used. Currently it is the responsibility of the user to keep
    /// these strings unique, the framework does not check this condition.
    ///
    /// \example portable/infrastructure/tests/src/testsuite.cpp

    template<class Implementation_T>
      class TTestSuiteBase
      {

      public:
        /// \name Standard template types
        ///
        /// These types permit a standardised way of
        /// referring to names of (or names dependent on) the template
        /// parameters, which are specific to the implementation. Except
        /// when referring to the template, (in which case the templates
        /// parameters are required), use these types everywhere
        /// else instead of usual types.
        /// @{

        typedef Implementation_T Implementation;

        /// @} end of name Standard template types

        /// \name Constructors/destructor
        /// @{

        /// \brief Simple constructor.
        /// \par Parameters
        ///     None.
        TTestSuiteBase(void);

        /// \brief Constructor with main() style parameters
        ///
        /// \param [in] argc    Count of arguments.
        /// \param [in] argv    Array of pointer to strings.
        TTestSuiteBase(int argc, char* argv[]);

        /// \brief Destructor.
        ~TTestSuiteBase();

        /// @} end of name Constructors/destructor

        /// \name Public member functions
        /// @{

        /// \brief Process main() style parameters.
        ///
        /// \param [in] argc    Aount of arguments.
        /// \param [in] argv    Array of pointer to strings.
        void
        processMainParameters(int argc, char* argv[]);

        /// \brief Set the name of the tested class.
        ///
        /// \param [in] pName   A string containing the class name, usually with
        ///                     full name space definitions.
        /// \par Returns
        ///     Nothing.
        void
        setClassName(const char* pName);

        /// \brief Set the name of the tested member function.
        ///
        /// \param [in] pName   A string containing the prefix to be added
        ///                     to each test case, usually the name
        ///                     of the member function
        ///                     under test.
        /// \par Returns
        ///     Nothing.
        void
        setFunctionNameOrPrefix(const char* pName);

        /// \brief Define the input values used when calling the tested.
        /// member function.
        ///
        /// \param [in] pStr    A string containing the relevant values
        ///                     used when calling the member function
        ///                     exercised by the following
        ///                     test cases. Cleared by setFunctionNameOrPrefix().
        /// \par Returns
        ///     Nothing.
        void
        setInputValues(const char* pStr);

        /// \brief Define the preconditions used when calling the
        /// tested member function.
        ///
        /// \param [in] pStr    A string containing the relevant preconditions
        ///                     used when calling the member function
        ///                     exercised by the following
        ///                     test cases. Cleared by setFunctionNameOrPrefix().
        /// \par Returns
        ///     Nothing.
        void
        setPreconditions(const char* pStr);

        /// \brief Report the start of the test suite.
        ///
        /// \param [in] pMessage        A string identifying the test suite, usually
        ///                             the compiler `__FILE__` builtin macro definition.
        /// \par Returns
        ///     Nothing.
        void
        start(const char* pMessage);

        /// \brief Check condition and report a test case result.
        ///
        /// \param [in] expression      The boolean condition to be tested.
        /// \param [in] pMessage        A string identifying the test case.
        /// \par Returns
        ///     Nothing.
        void
        checkAndReport(bool expression, const char* pMessage);

/// \brief Check expression and report an result identical to the expression.
/// \details This is one of the few cases when macros are really needed,
/// to avoid writing the expression twice, first as expression and
/// then as string.
#define assertCondition(e) checkAndReport((e), #e)
#define assertConditionWithDetails(e, s) checkAndReport((e), #e " " s)

        /// \brief Report a successful test case.
        ///
        /// \param [in] pMessage        A string identifying the test case.
        /// \par Returns
        ///     Nothing.
        void
        reportPassed(const char* pMessage);

        /// \brief Report a failed test case.
        ///
        /// \param [in] pMessage a string identifying the test case.
        /// \par Returns
        ///     Nothing.
        void
        reportFailed(const char* pMessage);

        /// \brief Display an informative line.
        ///
        /// \param [in] pMessage        A string with the informative message.
        /// \par Returns
        ///     Nothing.
        void
        reportInfo(const char* pMessage);

        /// \brief Report the completion of the test suite.
        ///
        /// \par Parameters
        ///     None.
        /// \par Returns
        ///     Nothing.
        void
        stop(void);

        /// \brief Compute the value to be returned by main().
        ///
        /// \par Parameters
        ///     None.
        /// \retval 0 Test suite succeeded.
        /// \retval 1 Test suite failed.
        int
        getExitValue(void) const;

        /// \brief Compute how many test cases were performed.
        ///
        /// \par Parameters
        ///     None.
        /// \return The number of test cases that were performed.
        unsigned int
        getCurrentTestCaseNumber(void) const;

        /// \brief Get the verbosity level.
        ///
        /// \par Parameters
        ///     None.
        /// \return The verbosity level.
        size_t
        getVerbosity(void) const;

        /// @} end of name Public member functions

      private:

        /// \name Private constants
        /// @{

        /// \brief Define the type of the line to display.
        ///
        /// \details Used as parameter for outputLine() to add a prefix
        /// for each line generated.
        typedef int outputLineType_t;

        /// \brief Enumerate all known line types.
        enum OutputLineType
          : outputLineType_t
            {
              START = 1, INFO, PASS, FAIL, STAT, CLASS, STOP
        };

        /// @} end of name Private constants

        /// \name Private member functions
        /// @{

        /// \brief Generate a test case line and send it to the output device.
        ///
        /// \param [in] lineType        A constant to specify the line prefix.
        /// \param [in] pMessage        A string containing the line message.
        /// \par Returns
        ///     Nothing
        void
        outputLine(outputLineType_t lineType, const char* pMessage = nullptr);

        /// \brief Generate a test case XML element and write it to the
        /// configured file.
        ///
        /// \param [in] isFailure       Mark this test case as a failure.
        /// \param [in] pMessage        A string containing the test case message.
        /// \par Returns
        ///     Nothing
        void
        writeTestCaseToXmlFile(bool isFailure, const char* pMessage);

        /// \brief Write a null terminated string to the XML file.
        ///
        /// \param [in] pString         A string.
        ///
        /// \return The actual number of bytes written to the file.
        ssize_t
        writeStringToXmlFile(const char* pString);

        /// \brief Write an unsigned number to the XML file.
        ///
        /// \param [in] number          An unsigned number.
        ///
        /// \return The actual number of bytes written to the file.
        ssize_t
        writeCounterToXmlFile(unsigned int number);

        /// \brief Display a null terminated string to the test output device.
        ///
        /// \param [in] pString         A string.
        ///
        /// \return The actual number of bytes written to the output device.
        ssize_t
        putString(const char* pString);

        /// \brief Display a decimal integer to the test output device.
        ///
        /// \param [in] number  An integer number.
        ///
        /// \return The actual number of bytes written to the output device.
        ssize_t
        putNumber(int number);

        /// \brief Send a new line to the test output device.
        /// \par Parameters
        ///     None.
        /// \par Returns
        ///     Nothing.
        void
        putNewLine(void);

        /// \brief Get the number of passed test cases.
        /// \par Parameters
        ///     None.
        /// \return The accumulated number of passed test cases.
        unsigned int
        getCountPassed(void);

        /// \brief Get the number of failed test cases.
        /// \par Parameters
        ///     None.
        /// \return The accumulated number of failed test cases.
        unsigned int
        getCountFailed(void);

        /// @} end of name Private member functions

      private:

        /// \brief The accumulated number of passed test cases.
        unsigned int m_countPassed;

        /// \brief The accumulated number of failed test cases.
        unsigned int m_countFailed;

        /// \brief Initialise members.
        /// \par Parameters
        ///     None
        /// \par Returns
        ///     Nothing
        void
        __init(void);

        /// \brief The pointer to the class name string.
        const char* m_pClassName;

        /// \brief The pointer to the member function name string.
        const char* m_pFunctionName;

        /// \brief The pointer to the input values string.
        const char* m_pInputValues;

        /// \brief The pointer to the preconditions string.
        const char* m_pPreconditions;

        /// \brief The pointer to the preconditions string.
        const char* m_pStartMessage;

        /// \brief The boolean status of XML output.
        bool m_isXmlOpened;

        /// \brief The actual platform implementation.
        Implementation m_implementation;
      };

#pragma GCC diagnostic pop

    // ------------------------------------------------------------------------
    // inline member functions

    template<class Implementation_T>
      inline
      unsigned int
      TTestSuiteBase<Implementation_T>::getCountPassed(void)
      {
        return m_countPassed;
      }

    template<class Implementation_T>
      inline
      unsigned int
      TTestSuiteBase<Implementation_T>::getCountFailed(void)
      {
        return m_countFailed;
      }

    template<class Implementation_T>
      inline
      unsigned int
      TTestSuiteBase<Implementation_T>::getCurrentTestCaseNumber(void) const
      {
        return m_countPassed + m_countFailed;
      }

    template<class Implementation_T>
      inline
      size_t
      TTestSuiteBase<Implementation_T>::getVerbosity(void) const
      {
        return m_implementation.getVerbosity();
      }

    // ------------------------------------------------------------------------
    /// \brief Define a TestSuite type based on the template.
    typedef TTestSuiteBase<TestSuiteImplementation> TestSuiteBase;

    // ========================================================================

    /// \headerfile TestSuite.h "portable/infrastructure/include/TestSuite.h"
    /// \nosubgrouping
    /// \brief Test suite class.

    class TestSuite : public TestSuiteBase
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Simple constructor.
      /// \par Parameters
      ///       None.
      TestSuite();

      /// \brief Constructor with main() style parameters
      ///
      /// \param [in] argc count of arguments.
      /// \param [in] argv array of pointer to strings.
      TestSuite(int argc, char* argv[]);

      /// \brief Destructor.
      ~TestSuite();

      /// @}


    };


    // ========================================================================

  } // namespace infra
} // namespace os

#endif // defined(OS_INCLUDE_PORTABLE_INFRASTRUCTURE_TESTSUITE)
#endif // #define OS_PORTABLE_INFRASTRUCTURE_TESTSUITE_H_
