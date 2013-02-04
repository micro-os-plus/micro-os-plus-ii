/*       Copyright (C) 2012-2013 Liviu Ionescu.
 *
 *      This file is part of the uOS++ distribution.
 */

#ifndef OS_PORTABLE_INFRA_TESTSUITE_H_
#define OS_PORTABLE_INFRA_TESTSUITE_H_

#include <stdint.h>
#include <unistd.h>

namespace os
{
  namespace infra
  {

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"

    /// \class TestSuite TestSuite.h "portable/infra/include/TestSuite.h"
    /// \brief Simple test suite class.
    ///
    /// This class implements a simple test suite, to be used by µOS++ unit
    /// tests.
    ///
    /// Functionality is striped to the bare essential: a `PASS/FAIL`
    /// message in the console and a `<testcase>` line in an XML file, to be used by
    /// continuous integration tools like Jenkins.

    class TestSuite
    {

    public:
      /// \brief Default constructor.
      ///
      /// Create the test suite
      /// - clear counters,
      /// - pointer to class name,
      /// - file descriptor
      TestSuite();

      /// \brief Default destructor.
      ///
      /// Cleanup the test suite, eventually close the XML file.
      ~TestSuite();

      /// \brief Run the test suite.
      ///
      /// This method is the only one that must be implemented by the unit
      /// test developer, the rest is done automatically by the test suite
      /// framework.
      void
      run(void);

      /// \brief Set the name of the tested class.
      ///
      /// The class name is required to identify the current test suite
      /// in an automated test environment.
      ///
      /// \param [in] pName a string containing the class name, usually with
      /// full name space definitions.
      void
      setClassName(const char* pName);

      /// \brief Report the start of the test suite.
      ///
      /// Generate an informative START line on the output device.
      ///
      /// \param [in] pMessage a string identifying the test suite, usually
      /// the compiler `__FILE__` builtin macro definition.
      void
      start(const char* pMessage) const;

      /// \brief Check condition and report a test case result.
      ///
      /// Generate a `PASS/FAIL` line on the output device, based on the given
      /// boolean condition.
      ///
      /// \param [in] expression the boolean condition to be tested.
      /// \param [in] pMessage a string identifying the test case.
      void
      check(bool expression, const char* pMessage);

      /// \brief Report a successful test case.
      ///
      /// Generate a `PASS` line on the output device. If the XML output is
      /// configured, the `<testcase>` element will be generated.
      ///
      /// \param [in] pMessage a string identifying the test case.
      void
      pass(const char* pMessage);

      /// \brief Report a failed test case.
      ///
      /// Generate a `FAIL` line on the output device. If the XML output is
      /// configured, the `<testcase>` element will include a `<failed/>`
      /// element.
      ///
      /// \param [in] pMessage a string identifying the test case.
      void
      fail(const char* pMessage);

      /// \brief Display an informative line.
      ///
      /// Generate an `INFO` line on the output device.
      ///
      /// \param [in] pMessage a string with the informative message.
      void
      info(const char* pMessage) const;

      /// \brief Report the completion of the test suite.
      ///
      /// Generate an informative `STOP` line on the output device.
      ///
      /// \param [in] pMessage a string identifying the test suite, usually
      /// the compiler `__FILE__` builtin macro definition.
      void
      stop(const char* pMessage) const;

      /// \brief Parse command line parameters.
      ///
      /// Process the command line parameters. If `-j filename` is encountered,
      /// the given file is used to output the XML formated test suite results.
      ///
      /// \param [in] argc count of arguments.
      /// \param [in] argv array of pointer to strings.
      void
      parseParameters(int argc, char* argv[]);

      /// \brief Compute the process return value.
      ///
      /// The test suite process shall return 0 if all test cases passed, and 1
      /// if at least one failed. This method checks the count of failed
      /// test cases and returns 0 if none.
      ///
      /// \retval 0 Test suite succeeded.
      /// \retval 1 Test suite failed.
      int
      getExitValue(void) const;

    private:

      /// \brief Define the type of the line to display.
      ///
      /// Used as parameter for outputLine() to add a prefix for each
      /// line generated.
      typedef int OutputLineType_t;

      /// \brief Enumeration of line types.
      enum OutputLineType
        : OutputLineType_t
          {
            START = 1, INFO, PASS, FAIL, STAT, STOP
      };

      /// \brief Generate a test case line on the output device.
      ///
      /// Prefix the message with a word defining the line type and
      /// send it to the output device.
      ///
      /// \param [in] lineType a constant to specify the line prefix.
      /// \param [in] pMessage a string containing the line message.
      void
      outputLine(OutputLineType_t lineType, const char* pMessage) const;

      /// \brief Generate a test case XML element in the configured file.
      ///
      /// The format used for the XML is the one defined in JUnit.
      ///
      /// \param [in] isFailure mark this test case as a failure.
      /// \param [in] pMessage a string containing the test case message.
      void
      writeToXmlFile(bool isFailure, const char* pMessage);

      /// \brief Write a null terminated string to the XML file.
      ///
      /// Compute the string length and write all the string characters,
      /// excluding the terminating '\0' into the XML file.
      ///
      /// \param [in] pString a string.
      ///
      /// \return The actual number of bytes written to the file.
      ssize_t
      writeStringToFile(const char* pString) const;

      /// \brief Display a null terminated string to the test output device.
      ///
      /// Compute the string length and send all the string characters,
      /// excluding the terminating '\0', to the test output device.
      ///
      /// \param [in] pString a string.
      ///
      /// \return The actual number of bytes written to the output device.
      ssize_t
      putString(const char* pString) const;

      /// \brief Display a decimal integer to the test output device.
      ///
      /// Convert the integer to ascii and send it to the test output device.
      ///
      /// \param [in] n an integer number.
      ///
      /// \return The actual number of bytes written to the output device.
      ssize_t
      putNumber(int n) const;

      /// \brief Send a new line to the test output device.
      ///
      /// Inform the output device that the current line is completed and
      /// request to flush all output and pass to the next one.
      void
      putNewLine(void) const;

      /// \brief A pointer to the class name string.
      const char* pClassName;

      /// \brief The number of passed test cases.
      int countPassed;

      /// \brief The number of failed test cases.
      int countFailed;

      /// \brief The file descriptor of the XML output file.
      int xmlFileDescriptor;

    };
    // class TestSuite

#pragma GCC diagnostic push

    inline void
    TestSuite::setClassName(const char* pName)
    {
      this->pClassName = pName;
    }

  } // namespace infra
} // namespace os

#endif /* #define OS_PORTABLE_INFRA_TESTSUITE_H_ */
