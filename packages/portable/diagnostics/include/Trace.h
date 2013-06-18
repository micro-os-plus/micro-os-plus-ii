//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Template declarations for the Trace class.

#ifndef OS_PORTABLE_DIAGNOSTICS_TRACE_H_
#define OS_PORTABLE_DIAGNOSTICS_TRACE_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_DIAGNOSTICS_TRACE) || defined(__DOXYGEN__)

#include "hal/architecture/diagnostics/include/TraceImplementation.h"

// Do not enable it for __DOXYGEN__, the dependency graphs are too large
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS)

#include "portable/language/cpp/include/ostream.h"
#include "portable/language/cpp/include/iomanip.h"

namespace os
{
  namespace diag
  {

    // ========================================================================

    /// \headerfile Trace.h "portable/diagnostics/include/Trace.h"
    /// \ingroup diag
    /// \nosubgrouping
    ///
    /// \brief Trace streambuf class.
    ///
    /// \tparam Implementation_T  Type of the implementation class.
    ///
    /// \details
    /// The TTraceStreambufBase class implements a streambuf class
    /// to be used by the TTraceOstreamBase class.
    ///
    /// \example portable/diagnostics/tests/src/trace.cpp

    template<class Implementation_T>
      class TTraceStreambufBase : public os::std::streambuf
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

        /// \brief  Base constructor.
        ///
        /// \param [in] implementation Reference to the implementation class.
        TTraceStreambufBase(Implementation& implementation);

        /// \brief  Base destructor.
        virtual
        ~TTraceStreambufBase();

        /// @} end of name Constructors/destructor

        /// \brief  Consume data from the buffer and write to the
        ///         output stream.
        ///
        /// \param [in]  c      An additional character to consume.
        /// \return  `traits::eof()` to indicate failure, something
        /// else (usually `c`, or not_eof()).
        virtual int_type
        overflow(int_type c);

      private:
        /// \name Private members
        /// @{

        /// \brief Pointer to the implementation class.
        Implementation& m_implementation;

        /// @} end of name Private members

      };

    // ========================================================================

    /// \headerfile Trace.h "portable/diagnostics/include/Trace.h"
    /// \ingroup diag
    /// \nosubgrouping
    ///
    /// \brief Trace ostream class.
    ///
    /// \tparam Streambuf_T  Type of the streambuf class.
    /// \tparam Implementation_T  Type of the implementation class.
    ///
    /// \details
    /// The TTraceOstreamBase class implements an ostream class
    /// to be used by the Trace class.
    template<class Streambuf_T, class Implementation_T>
      class TTraceOstreamBase : public os::std::ostream
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
        typedef Streambuf_T Streambuf;

        /// @} end of name Standard template types

        /// \name Constructors/destructor
        /// @{

        /// \brief Base constructor.
        TTraceOstreamBase(Implementation& implementation);

        /// \brief Base destructor.
        virtual
        ~TTraceOstreamBase();

        /// @}end of name Constructors/destructor

      private:
        /// \name Private members
        /// @{

        /// \brief Local streambuf object.
        Streambuf m_streambuf;

        /// @} end of name Private members

      };
}
}

#endif // defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS)

namespace os
{
  namespace diag
  {
    // ========================================================================

    /// \headerfile Trace.h "portable/diagnostics/include/Trace.h"
    /// \ingroup diag
    /// \nosubgrouping
    ///
    /// \brief Trace light base class.
    ///
    /// \tparam Implementation_T  Type of the implementation class.
    ///
    /// \details
    /// This class provides no functionality, it is used only as a
    /// light alternative to TTraceOstreamBase.
    template<class Implementation_T>
      class TTraceLightBase
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

        /// \brief Constructor.
        ///
        /// \param [in] implementation  Unused reference to implementation.
        TTraceLightBase(
            Implementation& implementation __attribute__((unused)));

        /// @} end of name Constructors/destructor

      };

    // ------------------------------------------------------------------------
    // inline definitions

    /// \details
    /// The reference implementation is required only for compatibility
    /// with TTraceOstreamBase, this class does not use it,
    /// as it has no functionality
    template<class Implementation_T>
      inline
      TTraceLightBase<Implementation_T>::TTraceLightBase(
          Implementation& implementation __attribute__((unused)))
      {
      }

    // ========================================================================

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
//#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

    /// \headerfile Trace.h "portable/diagnostics/include/Trace.h"
    /// \ingroup diag
    /// \nosubgrouping
    ///
    /// \brief Trace base class.
    ///
    /// \tparam Base_T                  Type of the base class.
    /// \tparam Implementation_T        Type of the implementation class.
    ///
    /// \details
    /// This class implements the light versions of the trace output.
    /// All required conversions are available with simple functions,
    /// instead of the (heavier) ostream inserters.
    template<class Base_T, class Implementation_T>
      class TTraceBase : public Base_T
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

        typedef Base_T Base;
        typedef Implementation_T Implementation;

        /// @} end of name Standard template types

        /// \name Constructors/destructor
        /// @{

        /// \brief Base constructor.
        TTraceBase();

        /// \brief Base destructor.
        virtual
        ~TTraceBase();

        /// @} end of name Constructors/destructor

        /// \name Light functions.
        ///
        /// These functions directly output to the trace device
        /// without passing via the ostream code.
        /// They are intended to time critical situations (like
        /// interrupt code) when the ostream overhead might have
        /// an impact on latency.
        /// @{

        /// \brief Put new line.
        ///
        /// \par Parameters
        ///     None.
        /// \par Returns
        ///     Nothing.
        void
        putNewLine(void);

        /// \brief Put character.
        ///
        /// \param [in] ch      A character.
        /// \par Returns
        ///     Nothing.
        void
        putChar(const char ch);

        /// \brief Put signed character.
        ///
        /// \param [in] ch A character.
        /// \par Returns
        ///     Nothing.
        void
        putChar(const signed char ch);

        /// \brief Put unsigned character.
        ///
        /// \param [in] ch      A character.
        /// \par Returns
        ///     Nothing.
        void
        putChar(const unsigned char ch);

        /// \brief Put string.
        ///
        /// \param [in] pStr    A pointer to string.
        /// \par Returns
        ///     Nothing.
        void
        putString(const char* pStr);

        /// \brief Put non const string.
        ///
        /// \param [in] pStr    A pointer to string.
        /// \par Returns
        ///     Nothing.
        void
        putString(char* pStr);

        /// \brief Put signed string.
        ///
        /// \param [in] pStr    A pointer to string.
        /// \par Returns
        ///     Nothing.
        void
        putString(const signed char* pStr);

        /// \brief Put signed string.
        ///
        /// \param [in] pStr    A pointer to string.
        /// \par Returns
        ///     Nothing.
        void
        putString(const unsigned char* pStr);

        /// \brief Put unsigned char hex.
        ///
        /// \param [in] n       An unsigned number.
        /// \par Returns
        ///     Nothing.
        void
        putHex(unsigned char n);

        /// \brief Put unsigned short hex.
        ///
        /// \param [in] n       An unsigned number.
        /// \par Returns
        ///     Nothing.
        void
        putHex(unsigned short n);

        /// \brief Put unsigned int hex.
        ///
        /// \param [in] n       An unsigned number.
        /// \par Returns
        ///     Nothing.
        void
        putHex(unsigned int n);

        /// \brief Put unsigned long hex.
        ///
        /// \param [in] n       An unsigned number.
        /// \par Returns
        ///     Nothing.
        void
        putHex(unsigned long n);

        /// \brief Put unsigned long long hex.
        ///
        /// \param [in] n       An unsigned number.
        /// \par Returns
        ///     Nothing.
        void
        putHex(unsigned long long n);

        /// \brief Put pointer.
        ///
        /// \param [in] ptr     A generic pointer.
        /// \par Returns
        ///     Nothing.
        void
        putHex(void* ptr);

        /// \brief Put int decimal.
        ///
        /// \param [in] n       A number.
        /// \par Returns
        ///     Nothing.
        void
        putDec(int n);

        /// \brief Put long decimal.
        ///
        /// \param [in] n       A number.
        /// \par Returns
        ///     Nothing.
        void
        putDec(long n);

        /// \brief Put string and address.
        ///
        /// \param [in] pStr    A pointer to string.
        /// \param [in] addr    An address.
        /// \par Returns
        ///     Nothing.
        void
        putStringAndAddress(const char* pStr, void* addr);

        /// \brief Put string and address and name.
        ///
        /// \param [in] pStr    A pointer to string.
        /// \param [in] addr    An address.
        /// \param [in] pName   A pointer to name string.
        /// \par Returns
        ///     Nothing.
        void
        putStringAndAddress(const char* pStr, void* addr, const char* pName);

#if defined(DEBUG)
        /// \brief Put constructor.
#define putConstructor()        putStringAndAddress(__PRETTY_FUNCTION__, this)
        /// \brief Put destructor.
#define putDestructor()         putStringAndAddress(__PRETTY_FUNCTION__, this)
        /// \brief Put member function.
#define putMemberFunction()     putStringAndAddress(__PRETTY_FUNCTION__, this)

#define putConstructorWithName()        putStringAndAddress(__PRETTY_FUNCTION__, this, getName())
#define putDestructorWithName()         putStringAndAddress(__PRETTY_FUNCTION__, this, getName())
#define putMemberFunctionWithName()     putStringAndAddress(__PRETTY_FUNCTION__, this, getName())

#else
//#define putMemberFunction()
#endif

        /// @} end of name Light functions.

        Implementation&
        getImplementation(void);

      protected:
        /// \name Protected members
        /// @{

        /// \brief Implementation object.
        Implementation m_implementation;

        /// @} end of name Protected members

      };

#pragma GCC diagnostic pop

    // ------------------------------------------------------------------------
    // inlines

    template<class Base_T, class Implementation_T>
      inline typename TTraceBase<Base_T, Implementation_T>::Implementation&
      TTraceBase<Base_T, Implementation_T>::getImplementation(void)
      {
        return m_implementation;
      }

    template<class Base_T, class Implementation_T>
      inline
      void
      TTraceBase<Base_T, Implementation_T>::putChar(const signed char ch)
      {
        putChar(static_cast<char>(ch));
      }

    template<class Base_T, class Implementation_T>
      inline
      void
      TTraceBase<Base_T, Implementation_T>::putChar(const unsigned char ch)
      {
        putChar(static_cast<char>(ch));
      }

    template<class Base_T, class Implementation_T>
      inline
      void
      TTraceBase<Base_T, Implementation_T>::putString(char* pStr)
      {
        putString(const_cast<const char*>(pStr));
      }

    template<class Base_T, class Implementation_T>
      inline
      void
      TTraceBase<Base_T, Implementation_T>::putString(const signed char* pStr)
      {
        putString(reinterpret_cast<const char*>(pStr));
      }

    template<class Base_T, class Implementation_T>
      inline
      void
      TTraceBase<Base_T, Implementation_T>::putString(
          const unsigned char* pStr)
      {
        putString(reinterpret_cast<const char*>(pStr));
      }

// ============================================================================

#if defined(DEBUG)

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS) || defined(__DOXYGEN__)

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-template-vtables"
#endif

  // Declare the template instantiation
  extern template class TTraceStreambufBase<TraceImplementation>;

#pragma GCC diagnostic pop

  // Define a type to the TTraceStreambufBase class
  typedef TTraceStreambufBase<TraceImplementation> TraceStreambuf;

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-template-vtables"
#endif

  // Declare the template instantiation
  extern template class TTraceOstreamBase<TraceStreambuf,
  TraceImplementation>;

#pragma GCC diagnostic pop

  // Define a type to the TTraceOstreamBase class
  typedef TTraceOstreamBase<TraceStreambuf, TraceImplementation> TraceOstreamBase;

#endif // defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS)

// ----------------------------------------------------------------------------

  // Declare the template instantiation
  extern template class TTraceLightBase<TraceImplementation>;

  typedef TTraceLightBase<TraceImplementation> TraceLightBase;

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-template-vtables"
#endif

  // Declare the template instantiation
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS) || defined(__DOXYGEN__)
  extern template class TTraceBase<TraceOstreamBase, TraceImplementation>;
#endif
  extern template class TTraceBase<TraceLightBase, TraceImplementation>;

#pragma GCC diagnostic pop

#if defined(OS_INCLUDE_PORTABLE_DIAGNOSTICS_TRACE_OSTREAM_BASE)
  typedef TTraceBase<TraceOstreamBase, TraceImplementation> TraceBase;
#else
  typedef TTraceBase<TraceLightBase, TraceImplementation> TraceBase;
#endif

// ----------------------------------------------------------------------------

#endif

// ============================================================================

#if defined(DEBUG)

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
//#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

  /// \headerfile Trace.h "portable/diagnostics/include/Trace.h"
  /// \ingroup diag
  /// \nosubgrouping
  ///
  /// \brief Diagnostics Trace output class.
  ///
  /// \details
  /// Basically a TTraceBase with hardware power up/down.
  ///
  /// \warning Do not manually create further instances of this class!
  /// If you need this for testing, use the base classes.
  class Trace : public TraceBase
    {
    public:

      /// \name Constructors/destructor
      /// @{

      /// \brief Constructor.
      Trace();

      /// \brief Destructor.
      virtual
      ~Trace();

      /// @} end of name Constructors/destructor

      /// \name Static member functions
      /// @{

      /// \brief Called only once during early initialisations.
      static void
      powerUp(void);

      /// \brief Called only once during late cleanup.
      static void
      powerDown(void);

      /// @} end of name Static member functions
    };

#pragma GCC diagnostic pop

  /// \details
  /// Call the implementation power up code.
  inline
  void
  Trace::powerUp(void)
    {
      Implementation::powerUp();
    }

  /// \details
  /// Call the implementation power down code.
  inline
  void
  Trace::powerDown(void)
    {
      Implementation::powerDown();
    }

  // --------------------------------------------------------------------------

  // declare the trace object.
  // it is statically instantiated in EarlyInitialisations.cpp
  extern Trace trace;

#endif

// ============================================================================

}
 // namespace diag
}// namespace os

#endif // defined(OS_INCLUDE_PORTABLE_DIAGNOSTICS_TRACE)
#endif // OS_PORTABLE_DIAGNOSTICS_TRACE_H_
