//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Template definitions for the Trace class.

#ifndef OS_PORTABLE_DIAGNOSTICS_TRACE_CPP_H_
#define OS_PORTABLE_DIAGNOSTICS_TRACE_CPP_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_DIAGNOSTICS_TRACE) || defined(__DOXYGEN__)

#include "Trace.h"
#include "TraceConversions.cpp.h"

#include "portable/language/cpp/include/cstring.h"

namespace os
{
  namespace diag
  {

    // ========================================================================
    // TraceStreambufBase

// Do not enable it for __DOXYGEN__, the dependency graphs are too large
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS)

    /// \details
    /// Pass the implementation reference to the base streambuf.
    template<class Implementation_T>
    TTraceStreambufBase<Implementation_T>::TTraceStreambufBase(
        Implementation& implementation)
    : m_implementation(implementation)
      {
        // Do not call putConstructor() since the stream is not yet ready
      }

    template<class Implementation_T>
    TTraceStreambufBase<Implementation_T>::~TTraceStreambufBase()
      {
      }

    /// \details
    /// Currently the buffering is not enabled, so only the input
    /// parameter can be considered; if different from `traits::eof()`
    /// it is passed to the implementation `write()`.
    template<class Implementation_T>
    os::std::streambuf::int_type
    TTraceStreambufBase<Implementation_T>::overflow(int_type c)
      {
        if (c != traits_type::eof())
          {
            m_implementation.write(&c, 1);
          }
        return c;
      }

    // ========================================================================
    // TraceOstreamBase

    /// \details
    /// Initialise the streambuf with the reference to the parametrised
    /// implementation
    /// and initialise the parent ostream with the pointer to the local
    /// streambuf.
    template<class Streambuf_T, class Implementation_T>
    TTraceOstreamBase<Streambuf_T, Implementation_T>::TTraceOstreamBase(
        Implementation& implementation)
    : m_streambuf(implementation)
      {
        init(&m_streambuf);
        // this is the first time the ostream is properly initialised,
        // however it is recommended not to display anything yet.
      }

    template<class Streambuf_T, class Implementation_T>
    TTraceOstreamBase<Streambuf_T, Implementation_T>::~TTraceOstreamBase()
      {
      }

#endif

    // ========================================================================
    // TraceBase

    template<class Base_T, class Implementation_T>
      TTraceBase<Base_T, Implementation_T>::TTraceBase() :
          Base_T(m_implementation)
      {
      }

    template<class Base_T, class Implementation_T>
      TTraceBase<Base_T, Implementation_T>::~TTraceBase()
      {
      }

    /// \details
    /// Output the terminating character and flush the device.
    template<class Base_T, class Implementation_T>
      void
      TTraceBase<Base_T, Implementation_T>::putNewLine()
      {
        m_implementation.write("\n", 1);
        m_implementation.flush();
      }

    /// \details
    /// Output single character via the implementation `write()` function.
    template<class Base_T, class Implementation_T>
      inline
      void
      TTraceBase<Base_T, Implementation_T>::putChar(const char ch)
      {
        m_implementation.write(&ch, 1);
      }

    /// \details
    /// Output the entire string at once.
    template<class Base_T, class Implementation_T>
      void
      TTraceBase<Base_T, Implementation_T>::putString(const char* pStr)
      {
        // Silently ignore null strings.
        if (pStr == nullptr)
          return;

        m_implementation.write(pStr, strlen(pStr));
      }

    /// \details
    /// Output a string and an address, usually representing a function
    /// name and the `this` pointer of the current class.
    /// It is used to implement the
    /// `putConstructor()`, `putDestructor()` and `putMemberFunction()` macros.
    template<class Base_T, class Implementation_T>
      void
      TTraceBase<Base_T, Implementation_T>::putStringAndAddress(
          const char* pStr, void* addr)
      {
        putString(pStr);
        putString(" @");
        putHex(addr);
        putNewLine();
      }

    /// \details
    /// Output a string, an address and a name, usually representing a function
    /// name, the `this` pointer and the name of the current class.
    /// It is used to implement the
    /// `putConstructorWithName()` and `putDestructorWithName()` macros.
    template<class Base_T, class Implementation_T>
      void
      TTraceBase<Base_T, Implementation_T>::putStringAndAddress(
          const char* pStr, void* addr, const char* pName)
      {
        putString(pStr);
        putString(" @");
        putHex(addr);
        putString(" \"");
        putString(pName);
        putChar('"');
        putNewLine();
      }

    /// \details
    /// Output a string and a name, usually representing a function
    /// name and the name of the current class.
    /// It is used to implement the
    /// `putMemberFunctionWithName()` macro.
    template<class Base_T, class Implementation_T>
      void
      TTraceBase<Base_T, Implementation_T>::putStringAndName(const char* pStr,
          const char* pName)
      {
        putString(pStr);
        putString(" \"");
        putString(pName);
        putChar('"');
        putNewLine();
      }

    template<class Base_T, class Implementation_T>
      void
      TTraceBase<Base_T, Implementation_T>::putHex(unsigned char n)
      {
        // inline function template
        __putHex(m_implementation, n);
      }

    template<class Base_T, class Implementation_T>
      void
      TTraceBase<Base_T, Implementation_T>::putHex(unsigned int n)
      {
        // inline function template
        __putHex(m_implementation, n);
      }

    template<class Base_T, class Implementation_T>
      void
      TTraceBase<Base_T, Implementation_T>::putHex(unsigned short n)
      {
        // inline function template
        __putHex(m_implementation, n);
      }

    template<class Base_T, class Implementation_T>
      void
      TTraceBase<Base_T, Implementation_T>::putHex(unsigned long n)
      {
        // inline function template
        __putHex(m_implementation, n);
      }

    template<class Base_T, class Implementation_T>
      void
      TTraceBase<Base_T, Implementation_T>::putHex(unsigned long long n)
      {
        // inline function template
        __putHex(m_implementation, n);
      }

    /// \details
    /// Convert the pointer to a suitable unsigned and output it as hex.
    template<class Base_T, class Implementation_T>
      void
      TTraceBase<Base_T, Implementation_T>::putHex(void* ptr)
      {
#if __SIZEOF_POINTER__ == __SIZEOF_INT__

        unsigned int n;
        n = reinterpret_cast<unsigned int>(ptr);

#elif __SIZEOF_POINTER__ == __SIZEOF_LONG__

        unsigned long n;
        n = reinterpret_cast<unsigned long>(ptr);

#elif __SIZEOF_POINTER__ == __SIZEOF_LONG_LONG__

        unsigned long long n;
        n = reinterpret_cast<unsigned long long>(ptr);

#else
#error "Unsupported pointer size"
#endif

        putHex(n);
      }

    template<class Base_T, class Implementation_T>
      void
      TTraceBase<Base_T, Implementation_T>::putDec(int n)
      {
        // inline function template
        __putSigned(m_implementation, n);
      }

    template<class Base_T, class Implementation_T>
      void
      TTraceBase<Base_T, Implementation_T>::putDec(long n)
      {
        // inline function template
        __putSigned(m_implementation, n);
      }

    template<class Base_T, class Implementation_T>
      void
      TTraceBase<Base_T, Implementation_T>::putDec(unsigned int n)
      {
        // inline function template
        __putUnsigned(m_implementation, n);
      }

    template<class Base_T, class Implementation_T>
      void
      TTraceBase<Base_T, Implementation_T>::putDec(unsigned long n)
      {
        // inline function template
        __putUnsigned(m_implementation, n);
      }

  // ==========================================================================

  }// namespace diag
} // namespace os

#endif // defined(OS_INCLUDE_PORTABLE_DIAGNOSTICS_TRACE)
#endif // OS_PORTABLE_DIAGNOSTICS_TRACE_CPP_H_
