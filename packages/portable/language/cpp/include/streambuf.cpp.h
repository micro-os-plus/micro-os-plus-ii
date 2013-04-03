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

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_STEAMBUF_CPP_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_STEAMBUF_CPP_H_

#include "portable/core/include/ConfigDefines.h"

#include "portable/language/cpp/include/streambuf.h"
#include "portable/language/cpp/include/internal/_fpos.h"

#if 0
#include <__config>
#include <iosfwd>
#include <ios>
#endif

namespace os
{
  namespace std
  {

    /// \details
    /// It does nothing, not even deallocate any buffer space.
    template<class TChar_T, class TTraits_T>
      basic_streambuf<TChar_T, TTraits_T>::~basic_streambuf()
      {
      }

    /// \details
    /// Construct an object of class `basic_streambuf`
    /// and initialise:
    /// - all its pointer member objects to null pointers,
    /// - the `getloc()` member to a copy the global `locale`,
    /// `locale()`, at the time of construction.
    ///
    /// Remarks: Once the `getloc()` member is initialised,
    /// results of calling the locale member functions, and of
    /// members of facets so obtained, can safely be cached
    /// until the next time the member `imbue()` is called.
    template<class TChar_T, class TTraits_T>
      basic_streambuf<TChar_T, TTraits_T>::basic_streambuf()
          : //
          m_binp(nullptr), //
          m_ninp(nullptr), //
          m_einp(nullptr), //
          m_bout(nullptr), //
          m_nout(nullptr), //
          m_eout(nullptr), //
          m_locale()
      {
        // TODO: initialise locales to a copy of the global locales.
      }

    /// \details
    /// Construct an object based on a reference to another object.
    template<class TChar_T, class TTraits_T>
      basic_streambuf<TChar_T, TTraits_T>::basic_streambuf(
          const basic_streambuf& rhs)
          : //
          m_binp(rhs.m_binp), //
          m_ninp(rhs.m_ninp), //
          m_einp(rhs.m_einp), //
          m_bout(rhs.m_bout), //
          m_nout(rhs.m_nout), //
          m_eout(rhs.m_eout), //
          m_locale(rhs.m_locale)
      {
      }

    /// \details
    /// Assigns the data members of the object referred by `rhs` to `*this`.
    template<class TChar_T, class TTraits_T>
      basic_streambuf<TChar_T, TTraits_T>&
      basic_streambuf<TChar_T, TTraits_T>::operator=(const basic_streambuf& rhs)
      {
        m_locale = rhs.m_locale;
        m_binp = rhs.m_binp;
        m_ninp = rhs.m_ninp;
        m_einp = rhs.m_einp;
        m_bout = rhs.m_bout;
        m_nout = rhs.m_nout;
        m_eout = rhs.m_eout;

        return *this;
      }

    /// \details
    /// Swaps the data members of the object referred by `rhs` and `*this`.
    template<class TChar_T, class TTraits_T>
      void
      basic_streambuf<TChar_T, TTraits_T>::swap(basic_streambuf& rhs)
      {
        os::std::swap(m_locale, rhs.m_locale);

        os::std::swap(m_binp, rhs.m_binp);
        os::std::swap(m_ninp, rhs.m_ninp);
        os::std::swap(m_einp, rhs.m_einp);
        os::std::swap(m_bout, rhs.m_bout);
        os::std::swap(m_nout, rhs.m_nout);
        os::std::swap(m_eout, rhs.m_eout);
      }

    /// \details
    /// Translations done during I/O which depend on the current
    /// `locale` are changed by this call.
    /// Allows the derived class to be informed of changes in
    /// locale at the time they occur. Between invocations of
    /// this function a class derived from streambuf can safely
    /// cache results of calls to locale functions and to members
    /// of facets so obtained.
    ///
    /// \note  The base class version does nothing.
    template<class TChar_T, class TTraits_T>
      void
      basic_streambuf<TChar_T, TTraits_T>::imbue(const locale&)
      {
      }

    /// \details
    /// Influences stream buffering in a way that is defined
    /// separately for each class derived from basic_streambuf
    /// in this Clause (27.8.2.4, 27.9.1.5).
    ///
    /// \note  The base class version does nothing, returns `this`.
    template<class TChar_T, class TTraits_T>
      basic_streambuf<TChar_T, TTraits_T>*
      basic_streambuf<TChar_T, TTraits_T>::setbuf(
          char_type* s __attribute__((unused)),
          streamsize n __attribute__((unused)))
      {
        return this;
      }

    /// \details
    /// Alters the stream positions within one or more of the
    /// controlled sequences in a way that is defined separately
    /// for each class derived from basic_streambuf in this
    /// Clause (27.8.2.4, 27.9.1.5).
    ///
    /// Each derived class provides its own appropriate behaviour.
    ///
    /// \note  The base class version does nothing, returns
    /// `pos_type(off_type(-1))`
    /// that represents an invalid stream position.
    template<class TChar_T, class TTraits_T>
      typename basic_streambuf<TChar_T, TTraits_T>::pos_type
      basic_streambuf<TChar_T, TTraits_T>::seekoff(off_type, ios_base::seekdir,
          ios_base::openmode)
      {
        return pos_type(off_type(-1));
      }

    /// \details
    /// Alters the stream positions within one or more of the
    /// controlled sequences in a way that is defined separately
    /// for each class derived from basic_streambuf in this
    /// Clause (27.8.2, 27.9.1.1).
    ///
    /// Each derived class provides its own appropriate behavior.
    /// \note  The base class version does nothing, returns
    /// `pos_type(off_type(-1))`
    /// that represents an invalid stream position.
    template<class TChar_T, class TTraits_T>
      typename basic_streambuf<TChar_T, TTraits_T>::pos_type
      basic_streambuf<TChar_T, TTraits_T>::seekpos(pos_type, ios_base::openmode)
      {
        return pos_type(off_type(-1));
      }

    /// \details
    /// Synchronise the controlled sequences with the arrays.
    /// That is, if `pbase()` is non-null the characters between
    /// `pbase()` and `pptr()` are written to the controlled
    /// sequence. The pointers may then be reset as appropriate.
    ///
    /// Each derived class provides its own appropriate behavior,
    /// including the definition of \a failure.
    ///
    /// \note  The base class version does nothing, returns zero.
    template<class TChar_T, class TTraits_T>
      int
      basic_streambuf<TChar_T, TTraits_T>::sync()
      {
        return 0;
      }

    /// \details
    /// Return an estimate of the number of characters available in
    /// the input sequence, or -1. If it returns a positive value, then
    /// successive calls to `underflow()` will not return
    /// `traits::eof()` until at least that number of
    /// characters have been extracted from the stream.
    /// If `showmanyc()` returns -1, then calls to
    /// `underflow()` or `uflow()` will fail.
    ///
    /// \note The morphemes of showmanyc are
    /// “es-how-many-see”, not “show-manic”.
    ///
    /// \note  The base class version does nothing, returns zero.
    template<class TChar_T, class TTraits_T>
      streamsize
      basic_streambuf<TChar_T, TTraits_T>::showmanyc()
      {
        return 0;
      }

    /// \details
    /// Assign up to `n` characters to successive elements of the
    /// array whose first element is designated by `s`. The
    /// characters assigned are read from the input sequence
    /// as if by repeated calls to `sbumpc()`. Assigning stops
    /// when either n characters have been assigned or a
    /// call to `sbumpc()` would return `traits::eof()`.
    ///
    /// \note It is expected that derived classes provide a more efficient
    /// implementation by overriding this definition.
    ///
    /// \note Classes derived from `basic_streambuf` can
    /// provide more efficient ways to implement `xsgetn()`
    /// and `xsputn()` by overriding these definitions
    /// from the base class.
    template<class TChar_T, class TTraits_T>
      streamsize
      basic_streambuf<TChar_T, TTraits_T>::xsgetn(char_type* s, streamsize n)
      {
        const int_type eof = traits_type::eof();
        int_type c;
        streamsize i = 0;
        for (; i < n; ++i, ++s)
          {
            if (m_ninp < m_einp)
              {
                *s = *m_ninp++;
              }
            else if ((c = uflow()) != eof)
              {
                *s = traits_type::to_char_type(c);
              }
            else
              break;
          }
        return i;
      }

    /// \details
    /// Informally, this function is called when the input buffer is
    /// exhausted (or does not exist, as buffering need not actually be
    /// done).  If a buffer exists, it is *refilled*.  In either case, the
    /// next available character is returned, or `traits::eof()` to
    /// indicate a null pending sequence.
    ///
    /// A functioning input streambuf can be created by overriding only
    /// this function (no buffer area will be used).
    ///
    /// Formally, the public members of `basic_streambuf` call this virtual
    /// function only if `gptr()` is null or `gptr() >= egptr()`.
    ///
    /// It returns `traits::to_int_type(c)`, where `c` is the first
    /// character of the pending sequence, without moving the
    /// input sequence position past it. If the pending sequence
    /// is null then the function returns `traits::eof()` to
    /// indicate failure.
    ///
    /// The *pending sequence* of characters is defined
    /// as the concatenation of:
    /// - If `gptr()` is non-`NULL`, then the `egptr() - gptr()`
    /// characters starting at `gptr()`, otherwise the
    /// empty sequence.
    /// - Some sequence (possibly empty) of characters
    /// read from the input sequence.
    ///
    /// The *result character* is:
    /// - If the pending sequence is non-empty, the
    /// first character of the sequence.
    /// - If the pending sequence is empty then the
    /// next character that would be read from the
    /// input sequence.
    ///
    /// The backup sequence is defined as the concatenation of:
    /// - If `eback()` is null then empty,
    /// - Otherwise the `gptr() - eback()` characters
    /// beginning at `eback()`.
    ///
    /// Effects: The function sets up the `gptr()` and `egptr()`
    /// satisfying one of:
    /// - If the pending sequence is non-empty, `egptr()` is
    /// non-null and `egptr() - gptr()` characters
    /// starting at `gptr()` are the characters in the
    /// pending sequence
    /// - If the pending sequence is empty, either `gptr()`
    /// is null or `gptr()` and `egptr()` are set to the
    /// same non-`NULL` pointer.
    ///
    /// If `eback()` and `gptr()` are non-null then the
    /// function is not constrained as to their contents, but the
    /// “usual backup condition” is that either:
    /// - If the backup sequence contains at least `gptr() - eback()`
    /// characters, then the `gptr() - eback()` characters starting
    /// at `eback()` agree with the last `gptr() - eback()` characters
    /// of the backup sequence.
    /// - Or the `n` characters starting at `gptr() - n` agree with
    /// the backup sequence (where `n` is the length of the backup
    /// sequence).
    ///
    /// \note  The base class version does nothing,
    /// returns `traits::eof()`.
    template<class TChar_T, class TTraits_T>
      typename basic_streambuf<TChar_T, TTraits_T>::int_type
      basic_streambuf<TChar_T, TTraits_T>::underflow()
      {
        return traits_type::eof();
      }

    /// \details
    /// Informally, this function does the same thing as `underflow()`,
    /// and in fact is required to call that function.  It also returns
    /// the new character, like `underflow()` does.  However, this
    /// function also moves the read position forward by one.
    ///
    /// Formally, the constraints are the same as for underflow(), except
    /// that the result character shall be transferred from the
    /// pending sequence to the backup sequence, and the pending
    /// sequence shall not be empty before the transfer.
    ///
    /// The default behavior is to call `underflow()`. If
    /// `underflow()` returns `traits::eof()`, return
    /// `traits::eof()`. Otherwise, return the value of
    /// `traits::to_int_type(*gptr())` and increment the
    /// value of the next pointer for the input sequence.
    template<class TChar_T, class TTraits_T>
      typename basic_streambuf<TChar_T, TTraits_T>::int_type
      basic_streambuf<TChar_T, TTraits_T>::uflow()
      {
        if (underflow() == traits_type::eof())
          {
            return traits_type::eof();
          }
        return traits_type::to_int_type(*m_ninp++);
      }

    /// \details
    /// The public functions of basic_streambuf calls this virtual
    /// function only when `gptr()` is null, `gptr() == eback()`,
    /// or `traits::eq(traits::to_char_type(c),gptr()[-1])` returns
    /// false. Other calls shall also satisfy that constraint.
    ///
    /// The *pending sequence* is defined as for `underflow()`,
    /// with the modifications that:
    /// - If `traits::eq_int_type(c,traits::eof())` returns true,
    /// then the input sequence is backed up
    /// one character before the pending sequence is determined.
    /// - If `traits::eq_int_type(c,traits::eof())` return false,
    /// then `c` is prepended. Whether the input sequence is
    /// backed up or modified in any other way is unspecified.
    ///
    /// It returns `traits::eof()` to indicate failure. Failure
    /// may occur because the input sequence could not be
    /// backed up, or if for some other reason the pointers
    /// could not be set consistent with the constraints.
    /// `pbackfail()` is called only when put back has really failed.
    ///
    /// \post On return, the constraints of `gptr()`, `eback()`,
    /// and `pptr()` are the same as for `underflow()`.
    ///
    /// \note  The base class version does nothing,
    /// returns `traits::eof()`.
    template<class TChar_T, class TTraits_T>
      typename basic_streambuf<TChar_T, TTraits_T>::int_type
      basic_streambuf<TChar_T, TTraits_T>::pbackfail(int_type)
      {
        return traits_type::eof();
      }

    /// \details
    /// Write up to `n` characters to the
    /// output sequence as if by repeated calls to `sputc(c)`.
    /// The characters written are obtained from successive
    /// elements of the array whose first element is designated by `s`.
    /// Writing stops when either `n` characters have been written
    /// or a call to `sputc(c)` would return `traits::eof()`.
    /// Is is unspecified whether the function calls
    /// `overflow()` when `pptr() == epptr()` becomes true or
    /// whether it achieves the same e ects by other means.
    ///
    /// \note It is expected that derived classes provide a
    /// more efficient implementation by overriding this definition.
    template<class TChar_T, class TTraits_T>
      streamsize
      basic_streambuf<TChar_T, TTraits_T>::xsputn(const char_type* s, streamsize n)
      {
        streamsize i = 0;
        int_type eof = traits_type::eof();
        for (; i < n; ++s, ++i)
          {
            if (m_nout < m_eout)
              {
                *m_nout++ = *s;
              }
            else if (overflow(traits_type::to_int_type(*s)) == eof)
              {
                break;
              }
          }
        return i;
      }

    /// \details
    /// Informally, this function is called when the output buffer
    /// is full (or does not exist, as buffering need not actually
    /// be done).  If a buffer exists, it is \a consumed, with
    /// *some effect* on the controlled sequence.
    /// (Typically, the buffer is written out to the sequence
    /// verbatim.)  In either case, the character \a c is also
    /// written out, if \a c is not `eof()`.
    ///
    /// A functioning output streambuf can be created by overriding only
    /// this function (no buffer area will be used).
    ///
    /// Formally, this function consume some initial subsequence
    /// of the characters of the
    /// pending sequence. The pending sequence is defined as
    /// the concatenation of
    /// - if `pbase()` is `NULL` then the empty sequence otherwise,
    /// `pptr() - pbase()` characters beginning at `pbase()`.
    /// - if `traits::eq_int_type(c,traits::eof())` returns true,
    /// then the empty sequence otherwise, the sequence
    /// consisting of `c`.
    ///
    /// The member functions `sputc()` and `sputn()` call this
    /// function in case that no room can be found in the put
    /// buffer enough to accomodate the argument character sequence.
    ///
    /// It requires that every overriding definition of this
    /// virtual function shall obey the following constraints:
    /// - The effect of consuming a character on the associated
    /// output sequence is specified. That is for each class
    /// derived from an instance of basic_streambuf in this
    /// Clause (27.8.2, 27.9.1.1), a specification of how
    /// consuming a character effects the associated output
    /// sequence is given. There is no requirement on a
    /// program-defined class.
    /// - Let r be the number of characters in the pending
    /// sequence not consumed. If r is non-zero then
    /// `pbase()` and `pptr()` shall be set so that:
    /// `pptr() - pbase() == r` and the `r` characters
    /// starting at `pbase()` are the associated output stream.
    /// In case `r` is zero (all characters of the pending
    /// sequence have been consumed) then either `pbase()`
    /// is set to `NULL`, or `pbase()` and `pptr()` are
    /// both set to the same NULL non-value.
    /// - The function may fail if either appending some
    /// character to the associated output stream fails or
    /// if it is unable to establish pbase() and pptr()
    /// according to the above rules.
    ///
    /// It returns `traits::eof()` or throws an exception if
    /// the function fails. Otherwise, returns some value other
    /// than `traits::eof()` to indicate success.
    ///
    /// \note  The base class version does nothing,
    /// returns `traits::eof()`.
    template<class TChar_T, class TTraits_T>
      typename basic_streambuf<TChar_T, TTraits_T>::int_type
      basic_streambuf<TChar_T, TTraits_T>::overflow(int_type)
      {
        return traits_type::eof();
      }

  }
}

#endif // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_STEAMBUF_CPP_H_
