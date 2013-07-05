//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Sample implementation for the TestSuite class.

#ifndef OS_PORTABLE_INFRASTRUCTURE_TESTSUITEIMPLEMENTATIONSAMPLE_H_
#define OS_PORTABLE_INFRASTRUCTURE_TESTSUITEIMPLEMENTATIONSAMPLE_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_INFRASTRUCTURE_TESTSUITE) || defined(__DOXYGEN__)

namespace os
{
  namespace infra
  {
    /// \class TestSuiteImplementationSample TestSuiteImplementationSample.h "portable/infrastructure/include/TestSuiteImplementationSample.h"
    /// \brief A sample platform specific TestSuiteImplementation class.
    ///
    /// \details
    /// This class can be used as a template for all platform specific
    /// TestSuiteImplementation classes.
    ///
    /// It should be seen as a functionally equivalent abstract class
    /// to be used as base class for all actual implementations, just that
    /// inheritance is done at compile time, not at run time, and since
    /// none of these member functions need to preserve any status between calls,
    /// all are implemented as static member functions.
    ///
    /// This class should provide support for two output channels:
    /// - the test output device
    /// - the file where to write the XML test output
    ///
    /// On synthetic platforms, the test output device is usually
    /// implemented via the process standard output. On embedded platforms
    /// it can be implemented over hosting/tracing channels.
    ///
    /// The XML support member functions (file create/write/close) are easily
    /// available on synthetic platforms
    /// but hosting implementations might also be imagined for
    /// embedded platforms.
    ///
    /// The architecture implementation must also define the type name
    ///  `os::infra::TestSuiteImplementation` similar to the below
    /// definition, but pointing to the actual class, since this is how
    /// it is referred from the TestSuite member function.
    /// \code{.cpp}
    /// typedef os::infra::TestSuiteImplementation TestSuiteImplementation;
    /// \endcode
    class TestSuiteImplementationSample
    {
    public:

      /// \name Constructors/destructor
      /// @{

      /// \brief Simple constructor.
      TestSuiteImplementationSample(void);

      /// \brief Constructor with process parameters
      ///
      /// \param [in] argc count of arguments.
      /// \param [in] argv array of pointer to strings.
      TestSuiteImplementationSample(int argc, char* argv[]);

      /// \brief Destructor.
      ~TestSuiteImplementationSample();

      /// @}

      /// \name Public function members
      /// @{

      /// \brief Process main() style parameters
      ///
      /// \param [in] argc count of arguments.
      /// \param [in] argv array of pointer to strings.
      void
      processMainParameters(int argc, char* argv[]);

      /// \brief Create the XML file.
      ///
      /// \par Parameters
      ///     None
      ///
      /// \return If successful, it returns a non-negative integer,
      /// termed a file descriptor.  It returns -1 on failure.
      int
      createXmlFile(void);

      /// \brief Write an array of bytes to the XML file.
      ///
      /// \param [in] cpBuf pointer to the array of bytes
      /// \param [in] numBytes the length of the array of bytes
      ///
      /// \return Upon successful completion the number of bytes which
      /// were written is  returned.  Otherwise, a -1 is returned
      ssize_t
      writeToXmlFile(const void *cpBuf, size_t numBytes);

      /// \brief Close the XML file.
      ///
      /// \par Parameters
      ///    None
      ///
      /// \return  Upon successful completion, a value of 0 is returned.
      /// Otherwise, a value of -1 is returned.
      int
      closeXmlFile(void);

      /// \brief Send a new line to the test output device.
      /// \par Parameters
      /// None
      /// \par Returns
      /// Nothing
      void
      putNewLine(void);

      /// \brief Write an array of bytes to the test output device.
      ///
      /// \param [in] cpBuf pointer to the array of bytes
      /// \param [in] numBytes the length of the array of bytes
      ///
      /// \return The actual number of bytes written to the output device.
      ssize_t
      putBytes(const void* cpBuf, size_t numBytes);

      /// \brief Get the verbosity level.
      ///
      /// \par Parameters
      ///     None.
      /// \return The verbosity level.
      size_t
      getVerbosity(void) const;

      /// @}

    };

    // ------------------------------------------------------------------------
    // sample inline definitions

    inline
    TestSuiteImplementationSample::TestSuiteImplementationSample(void)
    {
    }

    inline
    TestSuiteImplementationSample::TestSuiteImplementationSample(
        int argc __attribute__((unused)), char* argv[] __attribute__((unused)))
    {
    }

    inline
    TestSuiteImplementationSample::~TestSuiteImplementationSample()
    {
    }

    inline
    void
    TestSuiteImplementationSample::processMainParameters(
        int argc __attribute__((unused)), char* argv[] __attribute__((unused)))
    {
    }

    inline
    int
    TestSuiteImplementationSample::createXmlFile(void)
    {
    }

    inline ssize_t
    TestSuiteImplementationSample::writeToXmlFile(
        const void *cpBuf __attribute__((unused)),
        size_t numBytes __attribute__((unused)))
    {
    }

    inline
    int
    TestSuiteImplementationSample::closeXmlFile(void)
    {
    }

    inline
    void
    TestSuiteImplementationSample::putNewLine(void)
    {
    }

    inline ssize_t
    TestSuiteImplementationSample::putBytes(
        const void* cpBuf __attribute__((unused)),
        size_t numBytes __attribute__((unused)))
    {
    }

    size_t
    TestSuiteImplementationSample::getVerbosity(void) const
    {
    }

  }      // namespace infra
} // namespace os

#endif // defined(OS_INCLUDE_PORTABLE_INFRASTRUCTURE_TESTSUITE)

#endif // OS_PORTABLE_INFRASTRUCTURE_TESTSUITEIMPLEMENTATIONSAMPLE_H_
