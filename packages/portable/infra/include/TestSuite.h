//
//      Copyright (C) 2012-2013 Liviu Ionescu.
//
//      This file is part of the uOS++ distribution.
//

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

    class TestSuite
    {

    public:
      /// \brief Simple constructor.
      TestSuite();

      /// \brief Simple destructor.
      ~TestSuite();

      /// \brief Set the name of the tested class.
      ///
      /// \param [in] pName a string containing the class name, usually with
      /// full name space definitions.
      void
      setClassName(const char* pName);

      /// \brief Report the start of the test suite.
      ///
      /// \param [in] pMessage a string identifying the test suite, usually
      /// the compiler `__FILE__` builtin macro definition.
      void
      start(const char* pMessage) const;

      /// \brief Check condition and report a test case result.
      ///
      /// \param [in] expression the boolean condition to be tested.
      /// \param [in] pMessage a string identifying the test case.
      void
      checkAndReport(bool expression, const char* pMessage);

      /// \brief Report a successful test case.
      ///
      /// \param [in] pMessage a string identifying the test case.
      void
      reportPassed(const char* pMessage);

      /// \brief Report a failed test case.
      ///
      /// \param [in] pMessage a string identifying the test case.
      void
      reportFailed(const char* pMessage);

      /// \brief Display an informative line.
      ///
      /// \param [in] pMessage a string with the informative message.
      void
      reportInfo(const char* pMessage) const;

      /// \brief Report the completion of the test suite.
      ///
      /// \param [in] pMessage a string identifying the test suite, usually
      /// the compiler `__FILE__` builtin macro definition.
      void
      stop(const char* pMessage) const;

      /// \brief Parse command line parameters.
      ///
      /// \param [in] argc count of arguments.
      /// \param [in] argv array of pointer to strings.
      void
      parseParameters(int argc, char* argv[]);

      /// \brief Compute the process return value.
      ///
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

      /// \brief Enumeration of line types.
      enum OutputLineType
        : OutputLineType_t
          {
            START = 1, INFO, PASS, FAIL, STAT, CLASS, STOP
      };

      /// \brief Generate a test case line on the output device.
      ///
      /// \param [in] lineType a constant to specify the line prefix.
      /// \param [in] pMessage a string containing the line message.
      void
      outputLine(OutputLineType_t lineType,
          const char* pMessage = nullptr) const;

      /// \brief Generate a test case XML element in the configured file.
      ///
      /// \param [in] isFailure mark this test case as a failure.
      /// \param [in] pMessage a string containing the test case message.
      void
      writeToXmlFile(bool isFailure, const char* pMessage);

      /// \brief Write a null terminated string to the XML file.
      ///
      /// \param [in] pString a string.
      ///
      /// \return The actual number of bytes written to the file.
      ssize_t
      writeStringToFile(const char* pString) const;

      /// \brief Display a null terminated string to the test output device.
      ///
      /// \param [in] pString a string.
      ///
      /// \return The actual number of bytes written to the output device.
      ssize_t
      putString(const char* pString) const;

      /// \brief Display a decimal integer to the test output device.
      ///
      /// \param [in] n an integer number.
      ///
      /// \return The actual number of bytes written to the output device.
      ssize_t
      putNumber(int n) const;

      /// \brief Send a new line to the test output device.
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

#pragma GCC diagnostic pop

  } // namespace infra
} // namespace os

#endif /* #define OS_PORTABLE_INFRA_TESTSUITE_H_ */
