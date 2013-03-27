//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#ifndef OS_PORTABLE_DIAGNOSTICS_TRACE_H_
#define OS_PORTABLE_DIAGNOSTICS_TRACE_H_

#include "portable/core/include/OS_Defines.h"

#if defined(OS_INCLUDE_PORTABLE_DIAGNOSTICS_TRACE) || defined(__DOXYGEN__)

#include "TraceImplementation.h"

#include "portable/language/cpp/include/ostream.h"

namespace os
{
  namespace diag
  {

    // ========================================================================

    /// \class TraceStreambufBase Trace.h "portable/diagnostics/include/Trace.h"
    /// \ingroup diag
    /// \nosubgrouping
    ///
    /// \brief Trace streambuf class.
    ///
    /// \tparam TImplementation_T  Type of the implementation class.
    ///
    /// \details
    /// The TraceStreambufBase class implements a streambuf class
    /// to be used by the TraceOstreamBase class.
    ///
    /// \example portable/diagnostics/tests/src/trace.cpp

    template<class TImplementation_T>
      class TraceStreambufBase : public os::std::streambuf
      {
      public:

        /// \name Standard template types
        /// @{
        ///
        /// These types permit a standardised way of
        /// referring to names of (or names dependent on) the template
        /// parameters, which are specific to the implementation. Except
        /// when referring to the template, (in which case the templates
        /// parameters are required), use these types everywhere
        /// else instead of usual types.
        typedef TImplementation_T Implementation_t;
        /// @}

        /// \name Constructors/destructor
        /// @{

        /// \brief  Base constructor.
        ///
        /// \param [in] implementation Reference to the implementation class.
        TraceStreambufBase(Implementation_t& implementation);

        /// \brief  Base destructor.
        virtual
        ~TraceStreambufBase();

        /// @}

        /// \brief  Consume data from the buffer and write to the
        ///         output stream.
        ///
        /// \param [in]  c  An additional character to consume.
        /// \return  `traits::eof()` to indicate failure, something
        /// else (usually `c`, or not_eof()).
        virtual int_type
        overflow(int_type c);

      private:
        /// \name Private members
        /// @{

        /// \brief Pointer to the implementation class.
        Implementation_t& m_implementation;

        /// @}

      };

    // ------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-template-vtables"
#endif

    // Declare the template instantiation
    extern template class TraceStreambufBase<TraceImplementation_t> ;

#pragma GCC diagnostic pop

    // Define a type to the TraceStreambufBase class
    typedef TraceStreambufBase<TraceImplementation_t> TraceStreambuf_t;

    // ========================================================================

    /// \class TraceOstreamBase Trace.h "portable/diagnostics/include/Trace.h"
    /// \ingroup diag
    /// \nosubgrouping
    ///
    /// \brief Trace ostream class.
    ///
    /// \tparam TStreambuf_T  Type of the streambuf class.
    /// \tparam TImplementation_T  Type of the implementation class.
    ///
    /// \details
    /// The TraceOstreamBase class implements an ostream class
    /// to be used by the Trace class.
    template<class TStreambuf_T, class TImplementation_T>
      class TraceOstreamBase : public os::std::ostream
      {
      public:

        /// \name Standard template types
        /// @{
        ///
        /// These types permit a standardised way of
        /// referring to names of (or names dependent on) the template
        /// parameters, which are specific to the implementation. Except
        /// when referring to the template, (in which case the templates
        /// parameters are required), use these types everywhere
        /// else instead of usual types.
        typedef TImplementation_T Implementation_t;
        typedef TStreambuf_T Streambuf_t;
        /// @}

        /// \name Constructors/destructor
        /// @{

        /// \brief Base constructor.
        TraceOstreamBase(Implementation_t& implementation);

        /// \brief Base destructor.
        virtual
        ~TraceOstreamBase();

        /// @}

      private:
        /// \name Private members
        /// @{

        /// \brief Local streambuf object.
        Streambuf_t m_streambuf;

        /// @}

      };

    // ------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-template-vtables"
#endif

    // Declare the template instantiation
    extern template class TraceOstreamBase<TraceStreambuf_t,
        TraceImplementation_t> ;

#pragma GCC diagnostic pop

    // Define a type to the TraceOstreamBase class
    typedef TraceOstreamBase<TraceStreambuf_t, TraceImplementation_t> TraceOstreamBase_t;

    // ========================================================================

    /// \class TraceLightBase Trace.h "portable/diagnostics/include/Trace.h"
    /// \ingroup diag
    /// \nosubgrouping
    ///
    /// \brief Trace light base class.
    ///
    /// This class provides no functionality, it is used only as a
    /// light alternative to TraceOstreamBase,
    template<class TImplementation_T>
      class TraceLightBase
      {
      public:
        /// \name Standard template types
        /// @{
        ///
        /// These types permit a standardised way of
        /// referring to names of (or names dependent on) the template
        /// parameters, which are specific to the implementation. Except
        /// when referring to the template, (in which case the templates
        /// parameters are required), use these types everywhere
        /// else instead of usual types.
        typedef TImplementation_T Implementation_t;
        /// @}

        /// \name Constructors/destructor
        /// @{

        /// \brief Constructor
        ///
        /// \param [in] implementation Unused reference to implementation.
        TraceLightBase(
            Implementation_t& implementation __attribute__((unused)));

        /// @}

      };

    // ------------------------------------------------------------------------
    // inline definitions

    /// \details
    /// The reference implementation is required only for compatibility
    /// with TraceOstreamBase, this class does not use it,
    /// as it has no functionality
    template<class TImplementation_T>
      inline
      TraceLightBase<TImplementation_T>::TraceLightBase(
          Implementation_t& implementation __attribute__((unused)))
      {
      }

    // ------------------------------------------------------------------------

    // Declare the template instantiation
    extern template class TraceLightBase<TraceImplementation_t> ;

    typedef TraceLightBase<TraceImplementation_t> TraceLightBase_t;


    // ========================================================================

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
//#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

    /// \class TraceBase Trace.h "portable/diagnostics/include/Trace.h"
    /// \ingroup diag
    /// \nosubgrouping
    ///
    /// \brief Trace base class.
    ///
    /// \tparam TBase_T  Type of the base class.
    /// \tparam TImplementation_T  Type of the implementation class.
    ///
    /// \details
    /// This class implements the light versions of the trace output.
    /// All required conversions are available with simple functions,
    /// instead of the (heavier) ostream inserters.
    template<class TBase_T, class TImplementation_T>
      class TraceBase : public TBase_T
      {
      public:
        /// \name Standard template types
        /// @{
        ///
        /// These types permit a standardised way of
        /// referring to names of (or names dependent on) the template
        /// parameters, which are specific to the implementation. Except
        /// when referring to the template, (in which case the templates
        /// parameters are required), use these types everywhere
        /// else instead of usual types.
        typedef TBase_T Base_t;
        typedef TImplementation_T Implementation_t;

        /// @}

        /// \name Constructors/destructor
        /// @{

        /// \brief Base constructor.
        TraceBase();

        /// \brief Base destructor.
        virtual
        ~TraceBase();

        /// @}

        /// \name Light functions.
        /// @{
        ///
        /// These functions directly output to the trace device
        /// without passing via the ostream code.
        /// They are intended to time critical situations (like
        /// interrupt code) when the ostream overhead might have
        /// an impact on latency.

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
        /// \param [in] ch A character.
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
        /// \param [in] ch A character.
        /// \par Returns
        ///     Nothing.
        void
        putChar(const unsigned char ch);

        /// \brief Put string.
        ///
        /// \param [in] pStr A pointer to string.
        /// \par Returns
        ///     Nothing.
        void
        putString(const char* pStr);

        /// \brief Put non const string.
        ///
        /// \param [in] pStr A pointer to string.
        /// \par Returns
        ///     Nothing.
        void
        putString(char* pStr);

        /// \brief Put signed string.
        ///
        /// \param [in] pStr A pointer to string.
        /// \par Returns
        ///     Nothing.
        void
        putString(const signed char* pStr);

        /// \brief Put signed string.
        ///
        /// \param [in] pStr A pointer to string.
        /// \par Returns
        ///     Nothing.
        void
        putString(const unsigned char* pStr);

        /// \brief Put unsigned char hex.
        ///
        /// \param [in] n An unsigned number.
        /// \par Returns
        ///     Nothing.
        void
        putHex(unsigned char n);

        /// \brief Put unsigned short hex.
        ///
        /// \param [in] n An unsigned number.
        /// \par Returns
        ///     Nothing.
        void
        putHex(unsigned short n);

        /// \brief Put unsigned int hex.
        ///
        /// \param [in] n An unsigned number.
        /// \par Returns
        ///     Nothing.
        void
        putHex(unsigned int n);

        /// \brief Put unsigned long hex.
        ///
        /// \param [in] n An unsigned number.
        /// \par Returns
        ///     Nothing.
        void
        putHex(unsigned long n);

        /// \brief Put unsigned long long hex.
        ///
        /// \param [in] n An unsigned number.
        /// \par Returns
        ///     Nothing.
        void
        putHex(unsigned long long n);

        /// \brief Put pointer.
        ///
        /// \param [in] ptr A generic pointer.
        /// \par Returns
        ///     Nothing.
        void
        putHex(void* ptr);

        /// \brief Put int decimal.
        ///
        /// \param [in] n A number.
        /// \par Returns
        ///     Nothing.
        void
        putDec(int n);

        /// \brief Put long decimal.
        ///
        /// \param [in] n A number.
        /// \par Returns
        ///     Nothing.
        void
        putDec(long n);

        /// \brief Put name and address.
        ///
        /// \param [in] pStr A pointer to string.
        /// \param [in] addr An address.
        /// \par Returns
        ///     Nothing.
        void
        putNameAndAddress(const char* pStr, void* addr);

#if defined(DEBUG)
        /// \brief Put constructor.
#define putConstructor()        putNameAndAddress(__PRETTY_FUNCTION__, this)
        /// \brief Put destructor.
#define putDestructor()         putNameAndAddress(__PRETTY_FUNCTION__, this)
        /// \brief Put member function.
#define putMemberFunction()     putNameAndAddress(__PRETTY_FUNCTION__, this)

#else
#define putMemberFunction()
#endif

        /// @}

        Implementation_t&
        getImplementation(void);

      protected:
        /// \name Protected members
        /// @{

        /// \brief Implementation object.
        Implementation_t m_implementation;

        /// @}

      };

#pragma GCC diagnostic pop

    // ------------------------------------------------------------------------
    // inlines

    template<class TBase_T, class TImplementation_T>
      inline
      typename TraceBase<TBase_T, TImplementation_T>::Implementation_t&
      TraceBase<TBase_T, TImplementation_T>::getImplementation(void)
      {
        return m_implementation;
      }

    template<class TBase_T, class TImplementation_T>
      inline
      void
      TraceBase<TBase_T, TImplementation_T>::putChar(const signed char ch)
      {
        putChar(static_cast<char>(ch));
      }

    template<class TBase_T, class TImplementation_T>
      inline
      void
      TraceBase<TBase_T, TImplementation_T>::putChar(const unsigned char ch)
      {
        putChar(static_cast<char>(ch));
      }

    template<class TBase_T, class TImplementation_T>
      inline
      void
      TraceBase<TBase_T, TImplementation_T>::putString(char* pStr)
      {
        putString(const_cast<const char*>(pStr));
      }

    template<class TBase_T, class TImplementation_T>
      inline
      void
      TraceBase<TBase_T, TImplementation_T>::putString(const signed char* pStr)
      {
        putString(reinterpret_cast<const char*>(pStr));
      }

    template<class TBase_T, class TImplementation_T>
      inline
      void
      TraceBase<TBase_T, TImplementation_T>::putString(
          const unsigned char* pStr)
      {
        putString(reinterpret_cast<const char*>(pStr));
      }


#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-template-vtables"
#endif

    // Declare the template instantiation
    extern template class TraceBase<TraceOstreamBase_t, TraceImplementation_t> ;
    extern template class TraceBase<TraceLightBase_t, TraceImplementation_t> ;

#pragma GCC diagnostic pop

#if defined(OS_INCLUDE_PORTABLE_DIAGNOSTICS_TRACE_OSTREAM_BASE)
    typedef TraceBase<TraceOstreamBase_t, TraceImplementation_t> TraceBase_t;
#else
    typedef TraceBase<TraceLightBase_t, TraceImplementation_t> TraceBase_t;
#endif

    // ========================================================================

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
//#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

    /// \class Trace Trace.h "portable/diagnostics/include/Trace.h"
    /// \ingroup diag
    /// \nosubgrouping
    ///
    /// \brief Diagnostics Trace output class.
    ///
    /// Basically a TraceBase with early initialisations.
    ///
    /// \warning Do not manually create further instances of this class!
    /// If you need this for testing, use the base classes.
    class Trace : public TraceBase_t
    {
    public:

      /// \name Constructors/destructor
      /// @{

      /// \brief Constructor
      Trace();

      /// \brief Destructor
      virtual
      ~Trace();

      /// @}

      /// \brief Called only once during early initialisations.
      static void
      earlyInitialise(void);
    };

#pragma GCC diagnostic pop

    /// \details
    /// Call the implementation early initialisations.
    inline
    void
    Trace::earlyInitialise(void)
    {
      Implementation_t::earlyInitialise();
    }

    // ------------------------------------------------------------------------

    // declare the trace object.
    // it is statically instantiated in EarlyInitialisations.cpp
    extern Trace trace;

  // ========================================================================

  }// namespace diag
} // namespace os

#endif // defined(OS_INCLUDE_PORTABLE_DIAGNOSTICS_TRACE)
#endif // OS_PORTABLE_DIAGNOSTICS_TRACE_H_
