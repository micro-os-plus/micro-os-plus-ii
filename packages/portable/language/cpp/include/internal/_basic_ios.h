//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//
// [Partly inspired from the LLVM libcxx sources].
// Copyright (c) 2009-2013 by the contributors listed in
// 'LLVM libcxx Credits.txt'. See 'LLVM libcxx License.txt' for details.
//
// References are to ISO/IEC 14882:2011(E) Third edition (2011-09-01).
//

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INTERNAL_BASIC_IOS_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INTERNAL_BASIC_IOS_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS) || defined(__DOXYGEN__)

#include "portable/language/cpp/include/internal/__config.h"
#include "portable/language/cpp/include/iosfwd.h"
#include "portable/language/cpp/include/internal/_char_traits.h"
#include "portable/language/cpp/include/internal/_ios_base.h"

#include "portable/language/cpp/include/cstddef.h"

namespace os
{
  namespace std
  {

    // 27.5.5 Class template basic_ios

    /// \class basic_ios _basic_ios.h "portable/language/cpp/include/internal/_basic_ios.h"
    /// \ingroup std_io
    /// \nosubgrouping
    ///
    /// \brief Template class basic_ios, virtual base class for
    /// input and output streams.
    ///
    /// \tparam TChar_T  Type of character stream.
    /// \tparam TTraits_T  Traits for character type, defaults to
    ///                   char_traits<TChar_T> (default defined in iosfwd.h)
    ///
    /// \details
    /// Basically manages all common resources for derived streams, like
    /// pointer to the associated streambuf, status, exception status
    /// and the default fill character used for paddings.
    ///
    /// \example portable/language/cpp/tests/src/basic_ios.cpp

    template<class TChar_T, class TTraits_T>
      class _LIBCPP_VISIBLE basic_ios : public ios_base
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
        typedef TChar_T char_type;
        typedef TTraits_T traits_type;

        typedef typename traits_type::int_type int_type;
        typedef typename traits_type::pos_type pos_type;
        typedef typename traits_type::off_type off_type;
        /// @}

        // \name Flags functions (27.5.5.4)
        /// \name Flags member functions
        /// @{

        /// \brief  Check if the stream status is ok.
        ///
        /// \details This is a conversion operator.
        //_LIBCPP_ALWAYS_INLINE
        explicit
        operator bool() const;

        /// \brief  Check if the stream status is not ok.
        //_LIBCPP_ALWAYS_INLINE
        bool
        operator!() const;

        /// \brief  Get the error state of the stream buffer.
        ///
        /// \par Parameters
        /// None.
        /// \return  A bit pattern.
        //_LIBCPP_ALWAYS_INLINE
        iostate
        rdstate() const;

        /// \brief  [Re]set the error state.
        ///
        /// \param [in] state  The new state flag(s) to set.
        /// \par Returns
        /// Nothing.
        void
        clear(iostate state = goodbit);

        /// \brief  Set additional flags in the error state.
        ///
        /// \param [in] state  The additional state flag(s) to set.
        /// \par Returns
        /// Nothing.
        //_LIBCPP_ALWAYS_INLINE
        void
        setstate(iostate state);

        /// \brief  Check if no error.
        ///
        /// \par Parameters
        /// None.
        /// \return  True if no error flags are set.
        //_LIBCPP_ALWAYS_INLINE
        bool
        good() const;

        /// \brief  Check if `eofbit` is set.
        ///
        /// \par Parameters
        /// None.
        /// \return  True if the `eofbit` is set.
        //_LIBCPP_ALWAYS_INLINE
        bool
        eof() const;

        /// \brief  Check if error.
        ///
        /// \par Parameters
        /// None.
        /// \return  True if either the `badbit` or the `failbit` is set.
        //_LIBCPP_ALWAYS_INLINE
        bool
        fail() const;

        /// \brief  Check if the `badbit` is set.
        ///
        /// \par Parameters
        /// None.
        /// \return  True if the `badbit` is set.
        //_LIBCPP_ALWAYS_INLINE
        bool
        bad() const;

        /// \brief  Get the exceptions throwing flags.
        ///
        /// \par Parameters
        /// None.
        /// \return  The current exceptions mask.
        //_LIBCPP_ALWAYS_INLINE
        iostate
        exceptions() const;

        /// \brief  Set the exceptions throwing flags.
        ///
        /// \param [in] except  The new exceptions mask.
        /// \par Returns
        /// Nothing.
        //_LIBCPP_ALWAYS_INLINE
        void
        exceptions(iostate except);

        /// @}

        // 27.5.5.2 Constructor/destructor:
        /// \name Constructors/destructor
        /// @{

        /// \brief  Constructor with initialisation.
        ///
        /// \param [in] sb  A pointer to the streambuf to use.
        //_LIBCPP_INLINE_VISIBILITY
        explicit
        basic_ios(basic_streambuf<TChar_T, TTraits_T>* sb);

        /// \brief  Destructor.
        virtual
        ~basic_ios();

        /// @}

        // 27.5.5.3 Members:

        // \name Member functions (27.5.5.3)
        /// \name Member functions
        /// @{

        /// \brief  Get the current \e tied stream.
        ///
        /// \par Parameters
        /// None.
        /// \return  A pointer to the tied stream, or NULL if the stream is
        ///          not tied.
        //_LIBCPP_INLINE_VISIBILITY
        basic_ostream<TChar_T, TTraits_T>*
        tie() const;

        /// \brief  Tie this stream to an output stream.
        ///
        /// \param [in] tiestr  The output stream.
        /// \return  The previously tied output stream, or NULL if the stream
        ///          was not tied.
        //_LIBCPP_INLINE_VISIBILITY
        basic_ostream<TChar_T, TTraits_T>*
        tie(basic_ostream<TChar_T, TTraits_T>* tiestr);

        /// \brief  Get the underlying buffer.
        ///
        /// \par Parameters
        /// None.
        /// \return  The current stream buffer.
        //_LIBCPP_INLINE_VISIBILITY
        basic_streambuf<TChar_T, TTraits_T>*
        rdbuf() const;

        /// \brief  Set the underlying buffer.
        ///
        /// \param [in] sb  The new stream buffer.
        /// \return  The previous stream buffer.
        //_LIBCPP_INLINE_VISIBILITY
        basic_streambuf<TChar_T, TTraits_T>*
        rdbuf(basic_streambuf<TChar_T, TTraits_T>* sb);

        /// \brief  Get the *fill* character.
        ///
        /// \par Parameters
        /// None.
        /// \return  The current fill character.
        //_LIBCPP_INLINE_VISIBILITY
        char_type
        fill() const;

        /// \brief  Set a new *fill* character.
        ///
        /// \par Parameters
        /// None.
        /// \param [in] ch  The new character.
        /// \return  The previous fill character.
        //_LIBCPP_INLINE_VISIBILITY
        char_type
        fill(char_type ch);

        // Locales:

        /// \brief  Set a new locale.
        ///
        /// \param [in] loc  The new locale.
        /// \return  The previous locale.
        //_LIBCPP_INLINE_VISIBILITY
        locale
        imbue(const locale& loc);

        /// \brief  Squeeze characters.
        ///
        /// \param [in] c  The character to narrow.
        /// \param [in] dfault  The default character.
        /// \return  The narrowed character.
        _LIBCPP_INLINE_VISIBILITY
        char
        narrow(char_type c, char dfault) const;

#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wattributes"

        /// \brief  Widen characters.
        ///
        /// \param [in] c  The character to widen.
        /// \return  The widened character.
        //_LIBCPP_INLINE_VISIBILITY
        char_type
        widen(char c) const;
#pragma GCC diagnostic pop

        /// @}

        /// \name Assign/swap/move member functions
        /// @{

        /// \brief  Copy fields of rhs into this.
        ///
        /// \param [in] rhs  The source values for the copies.
        /// \return  Reference to this object.
        basic_ios&
        copyfmt(const basic_ios& rhs);

        /// @}

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
        void
        __set_badbit_and_consider_rethrow();

        void
        __set_failbit_and_consider_rethrow();
#endif

      protected:

        // 27.5.5.2 Constructors/destructor (27.5.5.2)
        /// \name Constructors/destructor
        /// @{

        /// \brief  Empty constructor.
        //_LIBCPP_ALWAYS_INLINE
        basic_ios();

        /// @}

        /// \name Member functions
        /// @{

        /// \brief  All setup is performed here.
        ///
        /// \param [in] sb A pointer to streambuf.
        /// \par Returns
        /// \par Returns
        /// Nothing.
        void
        init(basic_streambuf<TChar_T, TTraits_T>* sb);

        /// \brief  Set pointer to basic_streambuf.
        ///
        /// \param [in] sb A pointer to streambuf.
        /// \par Returns
        /// Nothing.
        //_LIBCPP_INLINE_VISIBILITY
        void
        set_rdbuf(basic_streambuf<TChar_T, TTraits_T>* sb);

        /// @}

        /// \name Assign/swap/move member functions
        /// @{

        /// \brief  Move all members.
        ///
        /// \param [in] rhs A reference to the right hand side basic_ios.
        /// \par Returns
        /// Nothing.
        //_LIBCPP_INLINE_VISIBILITY
        void
        move(basic_ios& rhs);

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
        /// \return Nothing
        //_LIBCPP_ALWAYS_INLINE
        void
        move(basic_ios&& rhs);
#endif

        /// \brief  Swap all members.
        ///
        /// \param [in,out] rhs A reference to the right hand side basic_ios.
        /// \par Returns
        /// Nothing.
        //_LIBCPP_INLINE_VISIBILITY
        void
        swap(basic_ios& rhs) _NOEXCEPT;

        /// @}

        // Data members
      private:

        /// \name Private members
        /// @{

        /// \brief Pointer to the associated stream buffer.
        basic_streambuf<TChar_T, TTraits_T>* m_rdbuf;

        /// \brief Pointer to the associated ostream, in case of istream.
        basic_ostream<TChar_T, TTraits_T>* m_tie;

        /// \brief IO state (values defined in ios_base).
        iostate m_rdstate;

        /// \brief IO state that trigger an exception.
        iostate m_exceptions;

        /// \brief The fill value.
        mutable int_type m_fill;

        /// @}

      };

    // ========================================================================
    // inline member functions

    // 27.5.5.2 basic_ios constructors

    /// \details
    /// Construct an object of class `basic_ios`, assigning initial
    /// values to its member objects by calling `init(sb)`.
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_ios<TChar_T, TTraits_T>::basic_ios(
          basic_streambuf<TChar_T, TTraits_T>* sb)
      {
        init(sb);
      }

    /// \details
    /// Construct an object of class `basic_ios` (27.5.3.7) leaving its
    /// member objects uninitialised. The object shall be initialised
    /// by calling `basic_ios::init()` before its first use or before it
    /// is destroyed, whichever comes first; otherwise the behaviour
    /// is undefined.
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_ios<TChar_T, TTraits_T>::basic_ios()
      {
        // purposefully does no initialisation
      }

    /// \details
    /// This allows you to write constructs such as
    /// `if (!a_stream) ...` and `while (a_stream) ...`
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_ALWAYS_INLINE
      basic_ios<TChar_T, TTraits_T>::operator bool() const
      {
        return !fail();
      }

    /// \details
    /// This allows you to write constructs such as
    /// `if (!a_stream) ...` and `while (a_stream) ...`
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_ALWAYS_INLINE
      bool
      basic_ios<TChar_T, TTraits_T>::operator!() const
      {
        return fail();
      }

    /// \details
    /// See `ios_base::iostate` for the possible bit values.  Most
    /// users will call one of the interpreting wrappers, e.g., `good()`.
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      ios_base::iostate
      basic_ios<TChar_T, TTraits_T>::rdstate() const
      {
        return m_rdstate;
      }

    /// \details
    /// See `ios_base::iostate` for the possible bit values.
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      void
      basic_ios<TChar_T, TTraits_T>::setstate(iostate state)
      {
        clear(m_rdstate | state);
      }

    /// \details
    /// A wrapper around `rdstate`.
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      basic_ios<TChar_T, TTraits_T>::good() const
      {
        return m_rdstate == 0;
      }

    /// \details
    /// Note that other `iostate` flags may also be set.
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      basic_ios<TChar_T, TTraits_T>::eof() const
      {
        return m_rdstate & eofbit;
      }

    /// \details
    /// Checking the `badbit` in `fail()` is historical practice.
    /// Note that other `iostate` flags may also be set.
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      basic_ios<TChar_T, TTraits_T>::fail() const
      {
        return m_rdstate & (failbit | badbit);
      }

    /// \details
    /// Note that other `iostate` flags may also be set.
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      basic_ios<TChar_T, TTraits_T>::bad() const
      {
        return m_rdstate & badbit;
      }

    /// \details
    /// This changes nothing in the stream.  See the one-argument version
    /// of `exceptions(iostate)` for the meaning of the return value.
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      ios_base::iostate
      basic_ios<TChar_T, TTraits_T>::exceptions() const
      {
        return m_exceptions;
      }

    /// \details
    /// By default, error flags are set silently.  You can set an
    /// exceptions mask for each stream; if a bit in the mask becomes set
    /// in the error flags, then an exception of type
    /// `ios_base::failure` is thrown.
    ///
    /// If the error flag is already set when the exceptions mask is
    /// added, the exception is immediately thrown.
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      void
      basic_ios<TChar_T, TTraits_T>::exceptions(iostate except)
      {
        m_exceptions = except;
        clear(m_rdstate);
      }

    // 27.5.5.3 Member functions
    /// \details
    /// A stream may be *tied* (or synchronized) to a second output
    /// stream.  When this stream performs any I/O, the tied stream is
    /// first flushed.  For example, `std::cin` is tied to `std::cout`.
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_ostream<TChar_T, TTraits_T>*
      basic_ios<TChar_T, TTraits_T>::tie() const
      {
        return m_tie;
      }

    /// \details
    /// This sets up a new tie. If `tiestr` is not null, `tiestr` must not
    /// be reachable by traversing the linked list of tied stream objects
    /// starting from `tiestr->tie()`.
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_ostream<TChar_T, TTraits_T>*
      basic_ios<TChar_T, TTraits_T>::tie(basic_ostream<TChar_T, TTraits_T>* tiestr)
      {
        basic_ostream<TChar_T, TTraits_T>* r = m_tie;
        m_tie = tiestr;
        return r;
      }

    /// \details
    /// This does not change the state of the stream.
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_streambuf<TChar_T, TTraits_T>*
      basic_ios<TChar_T, TTraits_T>::rdbuf() const
      {
        return m_rdbuf;
      }

    /// \details
    /// Associate a new buffer with the current stream, and clear the
    /// error state.
    ///
    /// Due to historical accidents which the LWG refuses to correct, the
    /// I/O library suffers from a design error:  this function is hidden
    /// in derived classes by overrides of the zero-argument `rdbuf()`,
    /// which is non-virtual for hysterical reasons.  As a result, you
    /// must use explicit qualifications to access this function via any
    /// derived class.  For example:
    ///
    /// ~~~
    /// std::fstream     foo;         // or some other derived type
    /// std::streambuf*  p = .....;
    ///
    /// foo.ios::rdbuf(p);            // ios == basic_ios<char>
    /// ~~~
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_streambuf<TChar_T, TTraits_T>*
      basic_ios<TChar_T, TTraits_T>::rdbuf(basic_streambuf<TChar_T, TTraits_T>* sb)
      {
        basic_streambuf<TChar_T, TTraits_T>* r = rdbuf();
        m_rdbuf = sb;
        clear();
        return r;
      }

    /// \details
    /// Associate the `basic_streambuf` object pointed to by `sb`
    /// with this stream without calling `clear()`.
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      void
      basic_ios<TChar_T, TTraits_T>::set_rdbuf(
          basic_streambuf<TChar_T, TTraits_T>* sb)
      {
        m_rdbuf = sb;
      }

    /// \details
    /// Call `ios_base::imbue(loc)`, and if a stream buffer is associated
    /// with this stream, call that buffer's `pubimbue(loc)`.
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      locale
      basic_ios<TChar_T, TTraits_T>::imbue(const locale& loc)
      {
        locale r = getloc();
        ios_base::imbue(loc);
        if (rdbuf())
          {
            rdbuf()->pubimbue(loc);
          }
        return r;
      }

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

    /// \details
    /// Maps a character of `char_type` to a character of `char`,
    /// if possible.
    ///
    /// Returns the result of
    /// ~~~
    ///   use_facet<ctype<TChar_T> >(getloc()).narrow(c,dfault)
    /// ~~~
    template <class TChar_T, class TTraits_T>
    inline _LIBCPP_INLINE_VISIBILITY
    char
    basic_ios<TChar_T, TTraits_T>::narrow(char_type __c, char __dfault) const
      {
        return use_facet<ctype<char_type> >(getloc()).narrow(__c, __dfault);
      }

    /// \details
    /// Maps a character of `char` to a character of `char_type`.
    ///
    /// Returns the result of
    /// ~~~
    ///   use_facet<ctype<char_type> >(getloc()).widen(c)
    /// ~~~
    template <class TChar_T, class TTraits_T>
    inline _LIBCPP_INLINE_VISIBILITY
    TChar_T
    basic_ios<TChar_T, TTraits_T>::widen(char __c) const
      {
        return use_facet<ctype<char_type> >(getloc()).widen(__c);
      }

#else

    // Tiny version, without locales

    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      char
      basic_ios<TChar_T, TTraits_T>::narrow(char_type c, char dfault) const
      {
        // TODO: extend this test according to locale
        if (c == '\xFE')
          {
            return dfault;
          }
        else
          {
            return static_cast<char>(c);
          }
      }

    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      TChar_T
      basic_ios<TChar_T, TTraits_T>::widen(char c) const
      {
        return static_cast<TChar_T>(c);
      }

#endif

    /// \details
    /// It defaults to a space (' ') in the current locale.
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      TChar_T
      basic_ios<TChar_T, TTraits_T>::fill() const
      {
        if (traits_type::eq_int_type(traits_type::eof(), m_fill))
          {
            m_fill = widen(' ');
          }
        // cast required since m_fill is an int_type
        return (TChar_T) m_fill;
      }

    /// \details
    /// The fill character is used to fill out space when P+ characters
    /// have been requested (e.g., via setw), Q characters are actually
    /// used, and Q<P.  It defaults to a space (' ') in the current locale.
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      TChar_T
      basic_ios<TChar_T, TTraits_T>::fill(char_type ch)
      {
        // cast required since m_fill is an int_type
        char_type r = (char_type) m_fill;
        m_fill = ch;
        return r;
      }

    /// \details
    /// *this shall have the state that rhs had before the function
    /// call, except that rdbuf() shall return 0. rhs shall be in a
    /// valid but unspecified state, except that rhs.rdbuf() shall
    /// return the same value as it returned before the function call,
    /// and rhs.tie() shall return 0.
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      void
      basic_ios<TChar_T, TTraits_T>::move(basic_ios& rhs)
      {
        ios_base::move(rhs);

        m_rdstate = rhs.m_rdstate;
        m_exceptions = rhs.m_exceptions;
        m_rdbuf = 0;

        m_tie = rhs.m_tie;
        rhs.m_tie = 0;
        m_fill = rhs.m_fill;
      }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
    template<class TChar_T, class TTraits_T>
    inline _LIBCPP_INLINE_VISIBILITY
    void
    basic_ios<TChar_T, TTraits_T>::move(basic_ios&& rhs)
      {
        move(rhs);
      }
#endif

    /// \details
    /// The states of *this and rhs shall be exchanged, except that
    /// rdbuf() shall return the same value as it returned before
    /// the function call, and rhs.rdbuf() shall return the same
    /// value as it returned before the function call.
    ///
    /// Use the parent swap() than the
    /// namespace function for individual fields
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      void
      basic_ios<TChar_T, TTraits_T>::swap(basic_ios& rhs)
      _NOEXCEPT
      {
        // use the parent function
        ios_base::swap(rhs);

        // use the namespace functions for individual fields
        os::std::swap(m_rdstate, rhs.m_rdstate);
        os::std::swap(m_exceptions, rhs.m_exceptions);

        os::std::swap(m_tie, rhs.m_tie);
        os::std::swap(m_fill, rhs.m_fill);
      }

  }
}

#endif // defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS)
#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INTERNAL_BASIC_IOS_H_
