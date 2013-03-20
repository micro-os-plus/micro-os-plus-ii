//
//      Copyright (C) 2012-2013 Liviu Ionescu.
//
//      This file is part of the uOS++ distribution.
//

#ifndef OS_PORTABLE_INFRASTRUCTURE_TESTSUITEIMPLEMENTATION_H_
#define OS_PORTABLE_INFRASTRUCTURE_TESTSUITEIMPLEMENTATION_H_

#include "portable/core/include/OS_Defines.h"

#if defined(OS_INCLUDE_PORTABLE_INFRASTRUCTURE_TESTSUITE) || defined(__DOXYGEN__)

namespace os
{
  namespace infra
  {
    /// \class TestSuiteImplementation TestSuiteImplementation.h "portable/infrastructure/include/TestSuiteImplementation.h"
    /// \brief The model for platform specific TestSuiteImplementation.
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
    ///  `os::infra::TestSuiteImplementation_t` similar to the below
    /// definition, but pointing to the actual class, since this is how
    /// it is referred from the TestSuite member function.
    /// ~~~
    /// typedef os::infra::TestSuiteImplementation TestSuiteImplementation_t;
    /// ~~~

    class TestSuiteImplementation
    {
    public:

      /// \brief Simple constructor.
      TestSuiteImplementation();

      /// \brief Constructor with process parameters
      ///
      /// \param [in] argc count of arguments.
      /// \param [in] argv array of pointer to strings.
      TestSuiteImplementation(int argc, char* argv[]);

      /// \brief Destructor.
      ~TestSuiteImplementation();

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

    };
  // class TestSuiteImplementation

  }// namespace infra
} // namespace os

// This is the place where the actual TestSuiteImplementation is
// selected, based on various preprocessor definitions.

#if defined(OS_INCLUDE_HAL_ARCH_SYNTHETIC_POSIX_INFRASTRUCTURE_TESTSUITEIMPLEMENTATION)

#include "hal/arch/synthetic/posix/infrastructure/include/TestSuiteImplementation.h"

#elif defined(__DOXYGEN__)

namespace os
  {
    namespace infra
      {
        typedef os::infra::TestSuiteImplementation TestSuiteImplementation_t;
      } // namespace infra
  } // namespace os

#else

#error "Missing TestSuiteImplementation.h"

#endif /* architecture selection */

#endif /* defined(OS_INCLUDE_PORTABLE_INFRASTRUCTURE_TESTSUITE) */

#endif /* OS_PORTABLE_INFRASTRUCTURE_TESTSUITEIMPLEMENTATION_H_ */
