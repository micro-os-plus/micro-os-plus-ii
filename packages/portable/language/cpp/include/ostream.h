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

/// \file
/// \brief Output streams.

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_OSTREAM_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_OSTREAM_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS) || defined(__DOXYGEN__)

#include "portable/language/cpp/include/internal/__config.h"
#include "portable/language/cpp/include/ios.h"
#include "portable/language/cpp/include/streambuf.h"
#include "portable/language/cpp/include/locale.h"
//#include "portable/language/cpp/include/type_traits.h"
#include "portable/language/cpp/include/internal/_fpos.h"

namespace os
{
  namespace std
  {
    // 27.7.3.1 Class template basic_ostream

    /// \class basic_ostream ostream.h "portable/language/cpp/include/ostream.h"
    /// \ingroup std_io
    /// \nosubgrouping
    ///
    /// \brief Class template basic_ostream.
    ///
    /// \tparam TChar_T         Type of character stream.
    /// \tparam TTraits_T       Traits for character type, defaults to
    ///                         char_traits<TChar_T>.
    ///
    /// \details
    /// This is the base class for all output streams.  It provides text
    /// formatting of all builtin types, and communicates with any class
    /// derived from basic_streambuf to do the actual output.
    ///
    /// The class basic_ostream defines a number of member function
    /// signatures that assist in formatting and writing output to
    /// output sequences controlled by a stream buff er.
    ///
    /// Two groups of member function signatures share common
    /// properties: the formatted output functions (or inserters)
    /// and the unformatted output functions. Both groups of output
    /// functions generate (or insert) output characters by actions
    /// equivalent to calling rdbuf()->sputc(int_type). They may
    /// use other public members of `basic_ostream` except that they
    /// shall not invoke any virtual members of `rdbuf()` except
    /// `overflow()`, `xsputn()`, and `sync()`.
    ///
    /// If one of these called functions throws an exception,
    /// then unless explicitly noted otherwise the output function
    /// sets `badbit` in error state. If `badbit` is on in `exceptions()`,
    /// the output function rethrows the exception without completing
    /// its actions, otherwise it does not throw anything and
    /// treat as an error.
    /// \sa ostreamInserters, ostreamManipulators
    ///
    /// \example portable/language/cpp/tests/src/ostream.cpp
    /// \example portable/language/cpp/tests/src/ostreamConversions.cpp

    template<class TChar_T, class TTraits_T>
      class _LIBCPP_VISIBLE basic_ostream : virtual public basic_ios<TChar_T,
          TTraits_T>
      {
      public:
        // types (inherited from basic_ios (27.5.5)):

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

        /// @} end of name Standard template types

        // 27.7.3.2 Constructor/destructor:

        /// \name Constructors/destructor
        /// @{

        /// \brief  Base constructor.
        ///
        /// \param sb Pointer to streambuf.
        explicit
        basic_ostream(basic_streambuf<TChar_T, TTraits_T>* sb);

        /// \brief  Base (empty) destructor.
        virtual
        ~basic_ostream();

        /// @} end of name Constructors/destructor

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif
        // 27.7.3.4 Prefix/suffix

        /// \brief Safe prefix/suffix operations.
        class _LIBCPP_VISIBLE sentry;

#pragma GCC diagnostic pop

        // 27.7.3.6 Formatted output

        // \name Interfaces for manipulators (27.7.3.6.3).
        /// \name Interfaces for manipulator functions
        /// @{
        ///
        /// Manipulators such as `endl` and `hex` use these
        /// functions in constructs like `std::cout << std::endl`.  For more
        /// information, see the `iomanip.h` header.
        ///
        /// This inserters do not behave as formatted output
        /// functions (as described in 27.7.3.6.1), i.e. do not use
        /// `sentry` objects.

        /// \brief  Interface for basic_ostream manipulators.
        ///
        /// \param pf  A pointer to the basic_ostream manipulator.
        /// \return  This output stream.
        basic_ostream&
        operator<<(basic_ostream&
        (*pf)(basic_ostream&));

        /// \brief  Interface for basic_ios manipulators.
        ///
        /// \param pf  A pointer to the basic_ios manipulator.
        /// \return  This output stream.
        basic_ostream&
        operator<<(basic_ios<TChar_T, TTraits_T>&
        (*pf)(basic_ios<TChar_T, TTraits_T>&));

        /// \brief  Interface for ios_base manipulators.
        ///
        /// \param pf  A pointer to the ios_base manipulator.
        /// \return  This output stream.
        basic_ostream&
        operator<<(ios_base&
        (*pf)(ios_base&));

        /// @} end of name Interfaces for manipulator functions

        // Inserter functions (27.7.3.6.2)

        /// \name Inserter operators
        /// @{
        ///
        /// All the `operator<<` functions (aka *formatted output
        /// functions*) have the some common behavior.
        /// Each formatted output function begins execution by
        /// constructing an object of class `sentry`. If this object
        /// returns true when converted to a value of type `bool`,
        /// the function endeavours to generate the requested output.
        /// If the generation fails, then the formatted output
        /// function does `setstate(ios_base::failbit)`, which might
        /// throw an exception. If an exception is thrown during
        /// output, then `ios::badbit` is turned on326 in `*this`’s
        /// error state. If `(exceptions()&badbit) != 0` then the
        /// exception is rethrown. Whether or not an exception is
        /// thrown, the sentry object is destroyed before leaving
        /// the formatted output function. If no exception is
        /// thrown, the result of the formatted output function is `*this`.
        ///
        /// These functions use the stream's current locale (specifically, the
        /// `num_put` facet) to perform numeric formatting.
        ///
        /// When the value is of type bool, long, unsigned long, long long,
        /// unsigned long long, double, long double, or const void*,
        /// the formatting conversion occurs as if it performed the
        /// following code fragment:
        /// \code{.cpp}
        /// bool failed = use_facet<
        /// num_put<charT,ostreambuf_iterator<charT,traits> >
        ///   >(getloc()).put(*this, *this, fill(), val).failed();
        /// \endcode
        ///
        /// The first argument provides an object of the
        /// `ostreambuf_iterator<>` class which is an iterator for
        /// `class basic_ostream<>`. It bypasses ostreams and uses
        /// streambufs directly. Class locale relies on these types
        /// as its interface to iostreams, since for flexibility it
        /// has been abstracted away from direct dependence on ostream.
        /// The second parameter is a reference to the base subobject
        /// of type ios_base. It provides formatting specifications
        /// such as field width, and a locale from which to obtain
        /// other facets. If failed is true then does `setstate(badbit)`,
        /// which may throw an exception, and returns.

        /// \brief Bool inserter.
        ///
        /// \param  n A variable of builtin bool type.
        /// \return  This output stream.
        basic_ostream&
        operator<<(bool n);

        /// \brief Short inserter.
        ///
        /// \param  n A variable of builtin short type.
        /// \return  This output stream.
        basic_ostream&
        operator<<(short n);

        /// \brief Unsigned short inserter.
        ///
        /// \param  n A variable of builtin unsigned short type.
        /// \return  This output stream.
        basic_ostream&
        operator<<(unsigned short n);

        /// \brief Int inserter.
        ///
        /// \param  n A variable of builtin int type.
        /// \return  This output stream.
        basic_ostream&
        operator<<(int n);

        /// \brief Unsigned int inserter.
        ///
        /// \param  n A variable of builtin unsigned int type.
        /// \return  This output stream.
        basic_ostream&
        operator<<(unsigned int n);

        /// \brief Long inserter.
        ///
        /// \param  n A variable of builtin long type.
        /// \return  This output stream.
        basic_ostream&
        operator<<(long n);

        /// \brief Unsigned long inserter.
        ///
        /// \param  n A variable of builtin unsigned long type.
        /// \return  This output stream.
        basic_ostream&
        operator<<(unsigned long n);

        /// \brief Long long inserter.
        ///
        /// \param  n A variable of builtin long long type.
        /// \return  This output stream.
        basic_ostream&
        operator<<(long long n);

        /// \brief Unsigned long long inserter.
        ///
        /// \param  n A variable of builtin unsigned long long type.
        /// \return  This output stream.
        basic_ostream&
        operator<<(unsigned long long n);

        /// \brief  Float inserter.
        ///
        /// \param  f A variable of builtin float type.
        /// \return  This output stream.
        /// \note This function is currently not implemented.
        basic_ostream&
        operator<<(float f);

        /// \brief  Double inserter.
        ///
        /// \param  f A variable of builtin double type.
        /// \return  This output stream.
        /// \note This function is currently not implemented.
        basic_ostream&
        operator<<(double f);

        /// \brief  Long double inserter.
        ///
        /// \param  f A variable of builtin long double type.
        /// \return  This output stream.
        /// \note This function is currently not implemented.
        basic_ostream&
        operator<<(long double f);

        /// \brief  Pointer inserter.
        ///
        /// \param  p A variable of pointer type.
        /// \return  This output stream.
        basic_ostream&
        operator<<(const void* p);

        /// \brief  streambuf insterter.
        ///
        /// \param  sb  A pointer to streambuf
        basic_ostream&
        operator<<(basic_streambuf<TChar_T, TTraits_T>* sb);

        /// @} end of name Inserter operators

        // 27.7.3.7 Unformatted output

        // Unformatted output functions

        /// \name Unformatted output member functions
        /// @{
        ///
        /// All the unformatted output functions have some common behaviour.
        /// Each unformatted output function begins execution by
        /// constructing an object of class sentry. If this object
        /// returns `true`, while converting to a value of type `bool`,
        /// the function endeavours to generate the requested output.
        /// If an exception is thrown during output, then `ios::badbit`
        /// is turned on in `*this`’s error state.
        /// If `(exceptions() & badbit) != 0` then the exception is
        /// rethrown. In any case, the unformatted output function
        /// ends by destroying the sentry object, then, if no
        /// exception was thrown, returning the value specified
        /// for the unformatted output function.

        /// \brief  Simple insertion.
        ///
        /// \param  c  The character to insert.
        /// \return  This output stream.
        basic_ostream&
        put(char_type c);

        /// \brief  Character string insertion.
        ///
        /// \param  str  The array of characters to insert.
        /// \param  n  Maximum number of characters to insert.
        /// \return  This output stream.
        basic_ostream&
        write(const char_type* str, streamsize n);

        /// \brief  Synchronise the stream buffer.
        ///
        /// \par Parameters
        ///     None.
        /// \return  This output stream.
        basic_ostream&
        flush();

        /// @} end of name Unformatted output member functions

        // 27.7.3.5 seeks

        // Seeks (27.7.3.5)

        /// \name Seek member functions
        /// @{

        /// \brief  Get the current write position.
        ///
        /// \par Parameters
        ///     None.
        /// \return  A file position object.
        pos_type
        tellp();

        /// \brief  Change the current write position.
        ///
        /// \param  pos  A file position object.
        /// \return  This output stream.
        basic_ostream&
        seekp(pos_type pos);

        /// \brief  Change the current write position.
        ///
        /// \param  off  A file offset object.
        /// \param  dir  The direction in which to seek.
        /// \return  This output stream.
        basic_ostream&
        seekp(off_type off, ios_base::seekdir dir);

        /// @} end of name Seek member functions

      protected:

        // Constructors/destructor (27.7.3.2)

        /// \name Constructors/destructor
        /// @{

        /// \brief Empty default constructor.
        ///
        /// \par Parameters
        ///     None.
        //_LIBCPP_ALWAYS_INLINE
        basic_ostream();

        /// \brief No copy constructor.
        ///
        /// \param [in] rhs A reference to basic_ostream.
        basic_ostream(const basic_ostream& rhs) = delete;

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
        _LIBCPP_INLINE_VISIBILITY
        basic_ostream(basic_ostream&& __rhs);
#endif

        /// @} end of name Constructors/destructor

        // 27.7.3.3 Assign/swap

        /// \name Assign/swap member functions
        /// @{

        /// \brief No assignment operator.
        ///
        /// \param [in] rhs A reference to basic_ostream.
        basic_ostream&
        operator=(basic_ostream& rhs) = delete;

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
        _LIBCPP_INLINE_VISIBILITY
        basic_ostream& operator=(const basic_ostream&& rhs);
#endif

        /// \brief  Swap all members.
        ///
        /// \param [in,out] rhs A reference to the right hand side basic_ios.
        /// \par Returns
        /// Nothing.
        void
        swap(basic_ostream& rhs);

        /// @} end of name Assign/swap member functions
      };

    // ========================================================================

    /// \addtogroup ostreamInserters
    /// @{
    /// \brief basic_ostream character and strings inserters.
    /// \note These are free functions, not a class member functions.

    // 27.7.3.6.4 character inserters

    /// \name  Character inserter operators
    /// @{
    /// \details
    /// All behave like formatted inserters (as described in 27.7.3.6.1)
    /// of `outs`.
    ///
    /// After a `sentry` object is constructed it inserts
    /// characters. In case `c` has type `char` and the character type
    /// of the stream is not `char`, then the character to be inserted
    /// is out.widen(c); otherwise the character is c. Padding is
    /// determined as described in 22.4.2.2.2. `width(0)` is called.
    /// The insertion character and any required padding are inserted
    /// into `outs`.
    ///
    /// In addition to the generic template, several specialisations
    /// are also provided.

    /// \brief Generic template, TChar_T ostream, char param.
    ///
    /// \param  outs  A reference to an output stream.
    /// \param  c  A generic character.
    /// \return  The output stream.
    template<class TChar_T, class TTraits_T>
      basic_ostream<TChar_T, TTraits_T>&
      operator<<(basic_ostream<TChar_T, TTraits_T>& outs, TChar_T c);

    /// \brief Template specialisation, TChar_T ostream, char param.
    ///
    /// \param  outs  A reference to an output stream.
    /// \param  c  A character.
    /// \return  The output stream.
    template<class TChar_T, class TTraits_T>
      basic_ostream<TChar_T, TTraits_T>&
      operator<<(basic_ostream<TChar_T, TTraits_T>& outs, char c);

    /// \brief Template specialisation, char ostream, char param.
    ///
    /// \param  outs  A reference to an output stream.
    /// \param  c  A character.
    /// \return  The output stream.
    template<class TTraits_T>
      basic_ostream<char, TTraits_T>&
      operator<<(basic_ostream<char, TTraits_T>& outs, char c);

    /// \brief Template specialisation, char ostream, signed char param.
    ///
    /// \param  outs  A reference to an output stream.
    /// \param  c  A signed character.
    /// \return  The output stream.
    template<class TTraits_T>
      basic_ostream<char, TTraits_T>&
      operator<<(basic_ostream<char, TTraits_T>& outs, signed char c);

    /// \brief Template specialisation, char ostream, unsigned char param.
    ///
    /// \param  outs  A reference to an output stream.
    /// \param  c  An unsigned character.
    /// \return  The output stream.
    template<class TTraits_T>
      basic_ostream<char, TTraits_T>&
      operator<<(basic_ostream<char, TTraits_T>& outs, unsigned char c);

    /// @} end of name  Character inserter operators

    // String inserters (27.7.3.6.4)

    /// \name  String inserter operators
    /// @{
    /// \details
    /// Behaves like a formatted inserter (as described in 27.7.3.6.1)
    /// of `outs`. After a `sentry` object is constructed it inserts `n`
    /// characters starting at `str`, where `n` is the number that would
    /// be computed as if by:
    /// - `traits::length(str)` for the overload where the first
    /// argument is of type `basic_ostream<charT, traits>&` and the
    /// second is of type `const charT*`, and also for the overload
    /// where the first argument is of type `basic_ostream<char, traits>&`
    /// and the second is of type `const char*`,
    /// - <code>char_traits<char>::length(str)</code> for the overload where
    /// the first argument is of type `basic_ostream<charT, traits>&`
    /// and the second is of type `const char*`,
    /// - `traits::length(reinterpret_cast<const char*>(str))` for the
    /// other two overloads.
    ///
    /// Padding is determined as described in 22.4.2.2.2.
    /// The `n` characters starting at `str` are widened using `out.widen`
    /// (27.5.5.3). The widened characters and any required padding
    /// are inserted into `outs`. Calls `width(0)`.

    /// \brief Generic template, <TChar_T, TTraits_T> ostream, TChar_T* param.
    ///
    /// \param  outs  A reference to an output stream.
    /// \param  str  A generic character string.
    /// \return  The output stream.
    /// \pre  `str` shall not be a null pointer.
    template<class TChar_T, class TTraits_T>
      basic_ostream<TChar_T, TTraits_T>&
      operator<<(basic_ostream<TChar_T, TTraits_T>& outs, const TChar_T* str);

    /// \brief Template specialisation,
    /// <TChar_T, TTraits_T> ostream, const char* param.
    ///
    /// \param  outs  A reference to an output stream.
    /// \param  str  A character string.
    /// \return  The output stream.
    /// \pre  `str` shall not be a null pointer.
    template<class TChar_T, class TTraits_T>
      basic_ostream<TChar_T, TTraits_T>&
      operator<<(basic_ostream<TChar_T, TTraits_T>& outs, const char* str);

    /// \brief Template specialisation,
    /// <char, TTraits_T> ostream, const char* param.
    ///
    /// \param  outs  A reference to an output stream.
    /// \param  str  A character string.
    /// \return  The output stream.
    /// \pre  `str` shall not be a null pointer.
    template<class TTraits_T>
      basic_ostream<char, TTraits_T>&
      operator<<(basic_ostream<char, TTraits_T>& outs, const char* str);

    /// \brief Template specialisation,
    /// <char, TTraits_T> ostream, const signed char* param.
    ///
    /// \param  outs  A reference to an output stream.
    /// \param  str  A signed character string.
    /// \return  The output stream.
    /// \pre  `str` shall not be a null pointer.
    template<class TTraits_T>
      basic_ostream<char, TTraits_T>&
      operator<<(basic_ostream<char, TTraits_T>& outs, const signed char* str);

    /// \brief Template specialisation,
    /// <char, TTraits_T> ostream, const unsigned char* param.
    ///
    /// \param  outs  A reference to an output stream.
    /// \param  str  An unsigned character string.
    /// \return  The output stream.
    /// \pre  `str` shall not be a null pointer.
    template<class TTraits_T>
      basic_ostream<char, TTraits_T>&
      operator<<(basic_ostream<char, TTraits_T>& outs,
          const unsigned char* str);

    /// @} end of name  String inserter operators

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

    template <class _Stream, class _Tp>
    typename enable_if
    <
    !is_lvalue_reference<_Stream>::value &&
    is_base_of<ios_base, _Stream>::value,
    _Stream&&
    >::type
    operator<<(_Stream&& __os, const _Tp& __x);

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

    template<class TChar_T, class TTraits_T>
    basic_ostream<TChar_T, TTraits_T>&
    operator<<(basic_ostream<TChar_T, TTraits_T>& __os, const error_code& __ec);

    template<class TChar_T, class TTraits_T, class _Yp>
    basic_ostream<TChar_T, TTraits_T>&
    operator<<(basic_ostream<TChar_T, TTraits_T>& __os,
        shared_ptr<_Yp> const& __p);

#endif

    /// @} end of addtogroup ostreamInserters

    // ========================================================================

    /// \brief  Perform setup work for output streams.
    ///
    /// \details
    /// The sentry class is used as a uniform method to check the status
    /// of the stream in order to skip action if not good, and to flush
    /// the output at the end if `unitbuf` is set.
    ///
    /// Objects of this class are created before all of the standard
    /// inserters are run.
    /// It is responsible for exception-safe prefix and
    /// suffix operations.
    template<class TChar_T, class TTraits_T>
      class _LIBCPP_VISIBLE basic_ostream<TChar_T, TTraits_T>::sentry
      {
        basic_ostream<TChar_T, TTraits_T>& m_ostream;
        bool m_ok;

        /// \brief No copy constructor.
        sentry(const sentry&) = delete;

        /// \brief No assignment operator.
        sentry&
        operator=(const sentry&) = delete;

      public:

        /// \brief  The constructor performs preparatory work.
        ///
        /// \param  outs  The output stream to guard.
        explicit
        sentry(basic_ostream<TChar_T, TTraits_T>& outs);

        /// \brief  Destructor.
        ///
        /// \details
        /// Possibly flushes the stream.
        ~sentry();

        /// \brief  Quick status check.
        ///
        /// \return  The sentry state.
        /// \details
        /// For ease of use, sentries can be converted to booleans.  The
        /// return value is that of the sentry state (true == okay).
        _LIBCPP_ALWAYS_INLINE
        _LIBCPP_EXPLICIT
        operator bool() const
        {
          return m_ok;
        }
      };

    // ========================================================================
    // inline member functions

    /// \details
    /// Extension, intentionally does not initialise members.
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_ALWAYS_INLINE
      basic_ostream<TChar_T, TTraits_T>::basic_ostream()
      {
      }

    /// \details
    /// This constructor is almost never called by the user directly,
    /// rather from
    /// derived classes' initialization lists, which pass a pointer to
    /// their own stream buffer.
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_ostream<TChar_T, TTraits_T>::basic_ostream(
          basic_streambuf<TChar_T, TTraits_T>* sb)
      {
        this->init(sb);
      }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

    template <class TChar_T, class TTraits_T>
    inline _LIBCPP_INLINE_VISIBILITY
    basic_ostream<TChar_T, TTraits_T>::basic_ostream(basic_ostream&& rhs)
      {
        this->move(rhs);
      }

    template <class TChar_T, class TTraits_T>
    inline _LIBCPP_INLINE_VISIBILITY
    basic_ostream<TChar_T, TTraits_T>&
    basic_ostream<TChar_T, TTraits_T>::operator=(basic_ostream&& rhs)
      {
        swap(rhs);
        return *this;
      }

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      void
      basic_ostream<TChar_T, TTraits_T>::swap(basic_ostream& rhs)
      {
        basic_ios<TChar_T, TTraits_T>::swap(rhs);
      }

    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_ostream<TChar_T, TTraits_T>&
      basic_ostream<TChar_T, TTraits_T>::operator<<(basic_ostream&
      (*pf)(basic_ostream&))
      {
        return pf(*this);
      }

    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_ostream<TChar_T, TTraits_T>&
      basic_ostream<TChar_T, TTraits_T>::operator<<(
          basic_ios<TChar_T, TTraits_T>&
          (*pf)(basic_ios<TChar_T, TTraits_T>&))
      {
        pf(*this);
        return *this;
      }

    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_ostream<TChar_T, TTraits_T>&
      basic_ostream<TChar_T, TTraits_T>::operator<<(ios_base&
      (*pf)(ios_base&))
      {
        pf(*this);
        return *this;
      }

    // ========================================================================
    // 27.7.3.8 Standard basic_ostream manipulators
    // Add a Doxygen page below Modules.

    /// \addtogroup ostreamManipulators
    /// @{
    // \brief  basic_ostream standard manipulators.

    // Standard basic_ostream manipulators (27.7.3.8)

    /// \name Standard basic_ostream manipulator functions
    /// @{

    /// \brief  Write a newline and flush the stream.
    /// \details
    /// Calls `os.put(os.widen(’\n’))`, then `os.flush()`.
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_ostream<TChar_T, TTraits_T>&
      endl(basic_ostream<TChar_T, TTraits_T>& outs)
      {
        outs.put(outs.widen('\n'));
        outs.flush();
        return outs;
      }

    /// \brief  Write a null character into the output sequence.
    ///
    /// \details
    /// Inserts a null character into the output sequence: calls `os.put(charT())`.
    ///
    /// The *null character* is `CharT` by definition.  For `CharT`
    /// of `char`, this correctly writes the ASCII `NUL` character
    /// string terminator.
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_ostream<TChar_T, TTraits_T>&
      ends(basic_ostream<TChar_T, TTraits_T>& outs)
      {
        outs.put(TChar_T());
        return outs;
      }

    /// \brief  Flushes the output stream.
    ///
    /// \details
    /// This manipulator simply calls the stream's `flush()` member function.
    template<class TChar_T, class TTraits_T>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_ostream<TChar_T, TTraits_T>&
      flush(basic_ostream<TChar_T, TTraits_T>& outs)
      {
        outs.flush();
        return outs;
      }

    /// @} end of name Standard basic_ostream manipulator functions

    /// @} end of addtogroup ostreamManipulators

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

    /// \brief  Generic inserter for rvalue stream.
    /// \param  outs  An input stream.
    /// \param  x  A reference to the object being inserted.
    /// \return  outs
    /// \details
    /// This is just a forwarding function to allow insertion to
    /// rvalue streams since they won't bind to the inserter functions
    /// that take an lvalue reference.
    template <class _Stream, class _Tp>
    inline _LIBCPP_INLINE_VISIBILITY
    typename enable_if
    <
    !is_lvalue_reference<_Stream>::value &&
    is_base_of<ios_base, _Stream>::value,
    _Stream&&
    >::type
    operator<<(_Stream&& outs, const _Tp& x)
      {
        outs << __x;
        return _VSTD::move(outs);
      }

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

    template<class TChar_T, class TTraits_T>
    inline _LIBCPP_INLINE_VISIBILITY
    basic_ostream<TChar_T, TTraits_T>&
    operator<<(basic_ostream<TChar_T, TTraits_T>& __os, const error_code& __ec)
      {
        return __os << __ec.category().name() << ':' << __ec.value();
      }

    template<class TChar_T, class TTraits_T, class _Yp>
    inline _LIBCPP_INLINE_VISIBILITY
    basic_ostream<TChar_T, TTraits_T>&
    operator<<(basic_ostream<TChar_T, TTraits_T>& __os,
        shared_ptr<_Yp> const& __p)
      {
        return __os << __p.get();
      }

#endif

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wweak-template-vtables"
#pragma clang diagnostic ignored "-Wpadded"
#endif

    extern template class basic_ostream<char> ;

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

  extern template class basic_ostream<wchar_t>;

#endif

#pragma GCC diagnostic pop

//_LIBCPP_END_NAMESPACE_STD
}
}

#endif // defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS)
#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_OSTREAM_H_
