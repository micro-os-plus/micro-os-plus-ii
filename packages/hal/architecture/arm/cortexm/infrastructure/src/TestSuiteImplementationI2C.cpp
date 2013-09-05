//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief I2C definitions of the test suite implementation class.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_INFRASTRUCTURE_TESTSUITEIMPLEMENTATIONI2C) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/infrastructure/include/TestSuiteImplementationI2C.h"
#include "portable/diagnostics/include/Trace.h"

// Platform headers
//#include <iostream>
//#include <fcntl.h>

namespace hal
{
  namespace cortexm
  {
    namespace infra
    {
      // ----------------------------------------------------------------------

      /// \details
      /// Initialise the object without XML output.
      TestSuiteImplementationI2C::TestSuiteImplementationI2C(void)
      {
#if defined(DEBUG)
        os::diag::trace.putConstructor();
#endif

        m_xmlFileDescriptor = -1;
        m_filePath = nullptr;
        m_verbosity = 0;
      }

      /// \details
      /// Process the command line parameters using `processMainParameters()`.
      TestSuiteImplementationI2C::TestSuiteImplementationI2C(int argc,
          char* argv[])
      {
#if defined(DEBUG)
        os::diag::trace.putConstructor();
#endif

        processMainParameters(argc, argv);
      }

      TestSuiteImplementationI2C::~TestSuiteImplementationI2C()
      {
#if defined(DEBUG)
        os::diag::trace.putDestructor();
#endif
      }

      /// \details
      /// Process the command line parameters. If `-x filename` is
      /// encountered, a pointer to the given file path is stored in
      /// m_filePath. Count all occurrences of `-v` as verbosity level.
      /// If errors occur, the process is abruptly terminated.
      void
      TestSuiteImplementationI2C::processMainParameters(
          int argc __attribute__((unused)),
          char* argv[] __attribute__((unused)))
      {
      }

      /// \details
      /// Create the file (open as new), truncate if present.
      int
      TestSuiteImplementationI2C::createXmlFile(void)
      {
        return m_xmlFileDescriptor;
      }

      /// \details
      /// Call the system function to write a sequence of bytes to the
      /// XML file.
      ssize_t
      TestSuiteImplementationI2C::writeToXmlFile(
          const void *cpBuf __attribute__((unused)),
          size_t numBytes __attribute__((unused)))
      {
        if (m_xmlFileDescriptor == -1)
          return -1;

        return -1;
      }

      /// \details
      /// Call the system function to close the XML file. Then
      /// invalidate the file descriptor.
      int
      TestSuiteImplementationI2C::closeXmlFile(void)
      {
        if (m_xmlFileDescriptor == -1)
          return -1;

        int ret;
        ret = -1;

        m_xmlFileDescriptor = -1;

        return ret;
      }

      /// \details
      /// Call the system function to write the new line to the
      /// standard output.
      void
      TestSuiteImplementationI2C::putNewLine(void)
      {
        putBytes("\n", 1);
        return;
      }

      /// \details
      /// Call the system function to write the sequence of bytes to the
      /// standard output. The operation is atomic.
      ssize_t
      TestSuiteImplementationI2C::putBytes(
          const void* cpBuf __attribute__((unused)),
          size_t numBytes __attribute__((unused)))
      {
        return m_implementation.write(cpBuf, numBytes);
      }

    // ----------------------------------------------------------------------

    }// namespace infra
  } // namespace cortexm
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_INFRASTRUCTURE_TESTSUITEIMPLEMENTATIONI2C)
