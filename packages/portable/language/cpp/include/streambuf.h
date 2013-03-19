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

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_STEAMBUF_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_STEAMBUF_H_

#include "portable/core/include/OS_Defines.h"

#include "portable/language/cpp/include/internal/__config.h"
#include "portable/language/cpp/include/iosfwd.h"
#include "portable/language/cpp/include/ios.h"
//#include "portable/language/cpp/include/internal/_locale.h"
#include "portable/language/cpp/include/internal/_fpos.h"

//_LIBCPP_BEGIN_NAMESPACE_STD
namespace os
{
  namespace std
  {

    /// \class basic_streambuf streambuf.h "portable/language/cpp/include/streambuf.h"
    /// \ingroup std_io
    /// \nosubgrouping
    ///
    /// \brief  The actual work of input and output (interface).
    ///
    /// \tparam _CharT  Type of character stream.
    /// \tparam _Traits Traits for character type, defaults to
    ///                  char_traits<_CharT>.
    ///
    /// The class template `basic_streambuf<_CharT,_Traits>` serves
    /// as an abstract base class for deriving various stream buffers
    /// whose objects each control two sequences:
    /// one for input, and one for output.
    ///
    /// Section [27.6.1] of the standard describes the requirements and
    /// behaviour of stream buffer classes.  That section (three paragraphs)
    /// is reproduced here, for simplicity and accuracy.
    ///
    /// -# Stream buffers can impose various constraints on the sequences
    ///    they control.  Some constraints are:
    ///    - The controlled input sequence can be not readable.
    ///    - The controlled output sequence can be not writable.
    ///    - The controlled sequences can be associated with the contents of
    ///      other representations for character sequences, such as external
    ///      files.
    ///    - The controlled sequences can support operations directly to or
    ///      from associated sequences.
    ///    - The controlled sequences can impose limitations on how the
    ///      program can read characters from a sequence, write characters to
    ///      a sequence, put characters back into an input sequence, or alter
    ///      the stream position.
    ///    .
    /// -# Each sequence is characterised by three pointers which, if non-null,
    ///    all point into the same `charT` array object.  The array object
    ///    represents, at any moment, a (sub)sequence of characters from the
    ///    sequence.  Operations performed on a sequence alter the values
    ///    stored in these pointers, perform reads and writes directly to or
    ///    from associated sequences, and alter *the stream position* and
    ///    conversion state as needed to maintain this subsequence relationship.
    ///    The three pointers are:
    ///    - the *beginning pointer*, or lowest element address in the
    ///      array (called `xbeg` here);
    ///    - the *next pointer*, or next element address that is a
    ///      current candidate for reading or writing (called `xnext` here);
    ///    - the *end pointer*, or first element address beyond the
    ///      end of the array (called `xend` here).
    ///    .
    /// -# The following semantic constraints shall always apply for any set
    ///    of three pointers for a sequence, using the pointer names given
    ///    immediately above:
    ///    - If `xnext` is not a null pointer, then `xbeg` and `xend` shall
    ///      also be non-null pointers into the same `charT` array, as
    ///      described above; otherwise, `xbeg` and `xend` shall also be null.
    ///    - If `xnext` is not a null pointer and `xnext < xend` for an
    ///      output sequence, then a *write position* is available.
    ///      In this case, `*xnext` shall be assignable as the next element
    ///      to write (to put, or to store a character value, into the sequence).
    ///    - If `xnext` is not a null pointer and `xbeg < xnext` for an
    ///      input sequence, then a *putback position* is available.
    ///      In this case, `xnext[-1]` shall have a defined value and is the
    ///      next (preceding) element to store a character that is put back
    ///      into the input sequence.
    ///    - If `xnext` is not a null pointer and `xnext< xend` for an
    ///      input sequence, then a *read position* is available.
    ///      In this case, `*xnext` shall have a defined value and is the
    ///      next element to read (to get, or to obtain a character value,
    ///      from the sequence).

    template<class _CharT, class _Traits>
      class _LIBCPP_VISIBLE basic_streambuf
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
        typedef _CharT char_type;
        typedef _Traits traits_type;
        typedef typename traits_type::int_type int_type;
        typedef typename traits_type::pos_type pos_type;
        typedef typename traits_type::off_type off_type;
        /// @}
        // end of \name Standard template types

        /// \name Constructors/destructor
        /// @{

        /// \brief Virtual destructor.
        virtual
        ~basic_streambuf();

        /// @}
        // end of \name Constructors/destructor

        // \name Public locale functions (27.6.3.2.1)
        /// \name Locale methods
        /// @{

        /// \brief  Public entry point for `imbue()`, to set new `locale`.
        ///
        /// \param [in]  loc  The new locale.
        /// \return  The previous locale.
        locale
        pubimbue(const locale& loc);

        /// \brief  Get `locale`.
        ///
        /// \return  The current locale in effect.
        locale
        getloc() const;

        /// @}

        // \name Public buffer management and positioning functions (27.6.3.2.2)
        /// \name Buffer management and positioning methods
        /// @{

        /// \brief  Public entry points for `setbuf()`, to define a buffer.
        ///
        /// \param [in] s The address of an array of characters.
        /// \param [in] n The size of the array.
        /// \return Pointer to streambuf.
        basic_streambuf*
        pubsetbuf(char_type* s, streamsize n);

        /// \brief  Public entry point for `seekoff()`, to change
        /// the stream position.
        ///
        /// \param [in]  off  Offset.
        /// \param [in]  way  Value for ios_base::seekdir.
        /// \param [in]  which Value for ios_base::openmode.
        /// \return A position.
        pos_type
        pubseekoff(off_type off, ios_base::seekdir way,
            ios_base::openmode which = ios_base::in | ios_base::out);

        /// \brief  Public entry point for `seekpos()`, to change
        /// the stream position.
        ///
        /// \param [in]  pos  The new position.
        /// \param [in]  which Value for ios_base::openmode.
        /// \return A position.
        pos_type
        pubseekpos(pos_type pos,
            ios_base::openmode which = ios_base::in | ios_base::out);

        /// \brief  Public entry point for `sync()`, to synchronise
        /// the stream.
        ///
        /// \par Parameters
        /// None.
        /// \return -1 on failure.
        int
        pubsync();

        /// @}

        // \name Public get area functions (27.6.3.2.3)
        /// \name Get area methods
        /// @{

        /// \brief  Public look ahead into the input stream.
        ///
        /// \par Parameters
        /// None.
        /// \return  The number of available characters.
        streamsize
        in_avail();

        /// \brief  Public get the next character using `sbumpc()` or `sgetc()`.
        ///
        /// \par Parameters
        /// None.
        /// \return  The next character, or `traits::eof()`.
        int_type
        snextc();

        /// \brief  Public get the next character from the buffer, or `uflow()`.
        ///
        /// \par Parameters
        /// None.
        /// \return  The next character, or `traits::eof()`.
        int_type
        sbumpc();

        /// \brief  Public get the next character from the buffer or `underflow()`.
        ///
        /// \par Parameters
        /// None.
        /// \return  The next character, or `traits::eof()`.
        int_type
        sgetc();

        /// \brief  Public entry point for xsgetn(), to get
        /// an array of characters.
        ///
        /// \param [in]  s  The address of an array of characters.
        /// \param [in]  n  The maximum number of characters to get.
        /// \return  The number of characters actually copied .
        streamsize
        sgetn(char_type* s, streamsize n);

        /// @}

        // \name Public putback (27.6.3.2.4)
        /// \name Putback methods
        /// @{

        /// \brief  Public push one character back into the input stream.
        ///
        /// \param [in]  c  The character to push back.
        /// \return  The previous character, if possible.
        int_type
        sputbackc(char_type c);

        /// \brief  Public move backwards into the input stream.
        ///
        /// \par Parameters
        /// None.
        /// \return  The previous character, if possible.
        int_type
        sungetc();

        /// @}

        // \name Put area (27.6.3.2.5)
        /// \name Put area methods
        /// @{

        /// \brief  Public put a single-character to the output stream.
        ///
        /// \param [in]  c  A character to write.
        /// \return  c, if possible.
        int_type
        sputc(char_type c);

        /// \brief  Public entry point for `xsputn()`, to put
        /// an array of characters into the output stream.
        ///
        /// \param [in]  s  The address of an array of characters.
        /// \param [in]  n  The number of characters to write.
        /// \return  The number of characters actually written.
        streamsize
        sputn(const char_type* s, streamsize n);

        /// @}

      protected:

        /// \name Constructors/destructor
        /// @{

        /// \brief  Base constructor.
        ///
        /// \par Parameters
        /// None.
        basic_streambuf();

        /// \brief Copy constructor.
        ///
        /// \param [in] rhs Reference to the object to copy from.
        basic_streambuf(const basic_streambuf& rhs);

        /// @}
        // end of \name Constructors/destructor

        // \name Assignment (27.6.3.3.1)
        /// \name Assign/swap/move methods
        /// @{

        /// \brief Protected assignment operator.
        ///
        /// \param [in] rhs Reference to the object to copy from.
        basic_streambuf&
        operator=(const basic_streambuf& rhs);

        /// \brief Protected swap data members.
        ///
        /// \param [in,out] rhs Reference to the object to swap members with.
        /// \par Returns
        /// Nothing
        void
        swap(basic_streambuf& rhs);

        /// @}

        // \name Get area access (27.6.3.3.2)
        /// \name Get area access methods
        /// @{

        /// \brief  Protected get the read beginning pointer.
        ///
        /// \par Parameters
        /// None.
        /// \return The beginning pointer for the input sequence.
        _LIBCPP_ALWAYS_INLINE
        char_type*
        eback() const;

        /// \brief  Protected get the read next pointer.
        ///
        /// \par Parameters
        /// None.
        /// \return The next pointer for the input sequence.
        _LIBCPP_ALWAYS_INLINE
        char_type*
        gptr() const;

        /// \brief  Protected get the read end pointer.
        ///
        /// \par Parameters
        /// None.
        /// \return The end pointer for the input sequence.
        _LIBCPP_ALWAYS_INLINE
        char_type*
        egptr() const;

        /// \brief  Protected move the read position forward or backward.
        ///
        /// \param [in]  n  The delta by which to move.
        /// \par Returns
        /// Nothing.
        void
        gbump(int n);

        /// \brief  Protected set all read area pointers.
        ///
        /// \param [in]  gbeg  A pointer to the beginning.
        /// \param [in]  gnext  A pointer to the next.
        /// \param [in]  gend  A pointer to the end.
        /// \par Returns
        /// Nothing.
        void
        setg(char_type* gbeg, char_type* gnext, char_type* gend);

        /// @}

        // \name Put area access (27.6.3.3.3)
        /// \name Put area access methods
        /// @{

        /// \brief  Protected get the write beginning pointer.
        ///
        /// \par Parameters
        /// None.
        /// \return The beginning pointer for the output sequence.
        _LIBCPP_ALWAYS_INLINE
        char_type*
        pbase() const;

        /// \brief  Protected get the write next pointer.
        ///
        /// \par Parameters
        /// None.
        /// \return The next pointer for the output sequence.
        _LIBCPP_ALWAYS_INLINE
        char_type*
        pptr() const;

        /// \brief  Protected get the write end pointer.
        ///
        /// \par Parameters
        /// None.
        /// \return The end pointer for the output sequence.
        _LIBCPP_ALWAYS_INLINE
        char_type*
        epptr() const;

        /// \brief  Protected move the write position forward or backward.
        ///
        /// \param [in]  n  The delta by which to move.
        /// \par Returns
        /// Nothing.
        void
        pbump(int n);

        /// \brief  Protected set all write area pointers.
        ///
        /// \param [in]  pbeg  A pointer to the beginning.
        /// \param [in]  pend  A pointer to the end.
        /// \par Returns
        /// Nothing.
        void
        setp(char_type* pbeg, char_type* pend);

        /// @}

        // 27.6.3.4 virtual functions

        // \name Locales (27.6.3.4.1)
        /// \name Locale methods
        /// @{

        /// \brief  Protected set a new `locale`.
        ///
        /// \param [in]  loc  A new locale.
        /// \par Returns
        /// Nothing.
        virtual void
        imbue(const locale& loc);

        /// @}

        // \name Buffer management and positioning (27.6.3.4.2)
        /// \name Buffer management and positioning methods
        /// @{

        /// \brief  Protected manipulate the buffer.
        ///
        virtual basic_streambuf*
        setbuf(char_type* s, streamsize n);

        /// \brief  Protected change the stream positions.
        ///
        /// \param [in]  off  Offset.
        /// \param [in]  way  Value for ios_base::seekdir.
        /// \param [in]  which Value for ios_base::openmode.
        /// \return A stream position.
        virtual pos_type
        seekoff(off_type off, ios_base::seekdir way,
            ios_base::openmode which = ios_base::in | ios_base::out);

        /// \brief  Protected change the stream positions.
        ///
        /// \param [in]  off  Offset.
        /// \param [in]  which Value for ios_base::openmode.
        /// \return A stream position.
        virtual pos_type
        seekpos(pos_type off,
            ios_base::openmode which = ios_base::in | ios_base::out);

        /// \brief  Protected synchronise (usually flush the output buffer).
        ///
        /// \par Parameters
        /// None.
        /// \return  -1 on failure.
        virtual int
        sync();

        /// @}

        // \name Get area (27.6.3.4.3)
        /// \name Get area methods
        /// @{

        /// \brief  Protected check if any input data available.
        ///
        /// \par Parameters
        /// None.
        /// \return  An estimate of the number of characters available in the
        ///          input sequence, or -1.
        virtual streamsize
        showmanyc();

        /// \brief  Protected get an array of characters.
        ///
        /// \param [in]  s  The address of an array of characters.
        /// \param [in]  n  The maximum number of characters to get.
        /// \return  The number of characters actually copied .
        virtual streamsize
        xsgetn(char_type* s, streamsize n);

        /// \brief  Protected fetch more data from the input stream.
        ///
        /// \par Parameters
        /// None.
        /// \return  The first character from the *pending sequence*.
        virtual int_type
        underflow();

        /// \brief  Protected fetch more data from the input stream.
        ///
        /// \par Parameters
        /// None.
        /// \return  The first character from the *pending sequence* or
        /// `traits::eof()` to indicate failure.
        virtual int_type
        uflow();

        /// @}

        // \name Putback (27.6.3.4.4)
        /// \name Putback methods
        /// @{

        /// \brief  Protected try to back up the input stream.
        ///
        /// \param [in]  c  The character to be inserted back into the sequence.
        /// \return  `traits::eof()` on failure, *some other value* on success
        virtual int_type
        pbackfail(int_type c = traits_type::eof());

        /// @}

        // \name Put area (27.6.3.4.5)
        /// \name Put area methods
        /// @{

        /// \brief  Protected put an array of characters to the output stream.
        ///
        /// \param [in]  s  The address of an array of characters.
        /// \param [in]  n  The number of characters to write.
        /// \return  The number of characters actually written.
        virtual streamsize
        xsputn(const char_type* s, streamsize n);

        /// \brief  Protected consume data from the buffer and write to the
        ///         output stream.
        ///
        /// \param [in]  c  An additional character to consume.
        /// \return  `traits::eof()` to indicate failure, something
        /// else (usually `c`, or not_eof())
        virtual int_type
        overflow(int_type c = traits_type::eof());

        /// @}

      private:

        /// \name Private input buffer pointer members
        /// @{

        /// Start of get area.
        char_type* m_binp;
        /// Current get area.
        char_type* m_ninp;
        /// End of get area.
        char_type* m_einp;

        /// @}

        /// \name Private output buffer pointer members
        /// @{

        /// Start of put area.
        char_type* m_bout;
        /// Current put area.
        char_type* m_nout;
        /// End of put area.
        char_type* m_eout;

        /// @}

        /// \name Private locale member
        /// @{

        /// Current locale setting.
        locale m_locale;

        /// @}

      };

    // ------------------------------------------------------------------------
    // inline methods

    /// \details
    /// Call the virtual private `imbue(loc)` and return its value.
    /// The effect is to set a new `locale`.
    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      locale
      basic_streambuf<_CharT, _Traits>::pubimbue(const locale& loc)
      {
        imbue(loc);
        locale r = m_locale;
        m_locale = loc;

        return r;
      }

    /// \details
    /// It returns, if `pubimbue()` has ever been called, then the last value
    /// of `m_locale` supplied, otherwise the current global locale,
    /// `locale()`, in eff ect at the time of construction. If
    /// called after `pubimbue()` has been called but before
    /// `pubimbue()` has returned (i.e., from within the call
    /// of `imbue()`) then it returns the previous value.
    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      locale
      basic_streambuf<_CharT, _Traits>::getloc() const
      {
        // Simple implementation, always return the member value
        return m_locale;
      }

    /// \details
    /// Call the virtual private `setbuf(s, n)` and return its value.
    /// The effect is usually to set a new buffer.
    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_streambuf<_CharT, _Traits>*
      basic_streambuf<_CharT, _Traits>::pubsetbuf(char_type* s, streamsize n)
      {
        return setbuf(s, n);
      }

    /// \details
    /// Call the virtual private `seekoff(off, way, which)`
    /// and return its value. The effect is usually to change the current
    /// position into the stream.
    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      typename basic_streambuf<_CharT, _Traits>::pos_type
      basic_streambuf<_CharT, _Traits>::pubseekoff(off_type off,
          ios_base::seekdir way,
          ios_base::openmode which)
        {
          return seekoff(off, way, which);
        }

      /// \details
      /// Call the virtual private `seekpos(pos, which)`
      /// and return its value. The effect is usually to change the current
      /// position into the stream.
    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      typename basic_streambuf<_CharT, _Traits>::pos_type
      basic_streambuf<_CharT, _Traits>::pubseekpos(pos_type pos,
          ios_base::openmode which)
        {
          return seekpos(pos, which);
        }

      /// \details
      /// Call the virtual private `sync()`
      /// and return its value. The effect is usually to synchronise/flush the
      /// output stream.
    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      int
      basic_streambuf<_CharT, _Traits>::pubsync()
      {
        return sync();
      }

    /// \details
    /// If some characters are available in the buffer,
    /// return `egptr() - gptr()` (the number of characters available)
    /// Otherwise return `showmanyc()` (27.6.3.4.3) to inspect the
    /// input stream.
    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      streamsize
      basic_streambuf<_CharT, _Traits>::in_avail()
      {
        if (m_ninp < m_einp)
          {
            return static_cast<streamsize>(m_einp - m_ninp);
          }
        return showmanyc();
      }

    /// \details
    /// Call `sbumpc()`, if it fails,
    /// return traits::eof(). Otherwise, return sgetc().
    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      typename basic_streambuf<_CharT, _Traits>::int_type
      basic_streambuf<_CharT, _Traits>::snextc()
        {
          if (sbumpc() == traits_type::eof())
            {
              return traits_type::eof();
            }
          return sgetc();
        }

      /// \details
      /// If the input sequence read position is not available
      /// (no characters in the input buffer),
      /// return `uflow()`. Otherwise, return
      /// `traits::to_int_type(*gptr())` and increment the next
      /// pointer for the input sequence.
    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      typename basic_streambuf<_CharT, _Traits>::int_type
      basic_streambuf<_CharT, _Traits>::sbumpc()
        {
          if (m_ninp == m_einp)
            {
              return uflow();
            }
          return traits_type::to_int_type(*m_ninp++);
        }

      /// \details
      /// If the input sequence read position is not available
      /// (no characters in the input buffer),
      /// return `underflow()`. Otherwise, return
      /// `traits::to_int_type(*gptr())`.
    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      typename basic_streambuf<_CharT, _Traits>::int_type
      basic_streambuf<_CharT, _Traits>::sgetc()
        {
          if (m_ninp == m_einp)
            {
              return underflow();
            }
          return traits_type::to_int_type(*m_ninp);
        }

      /// \details
      /// Call xsgetn(s,n) and return its value.
      /// The effect is usually to fill `s[0]` through
      /// `s[n-1]` with characters from the input sequence, if possible.
    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      streamsize
      basic_streambuf<_CharT, _Traits>::sgetn(char_type* s, streamsize n)
      {
        return xsgetn(s, n);
      }

    /// \details
    /// If the input sequence putback position is not available
    /// (or no more space in the input buffer),
    /// or if `traits::eq(c,gptr()[-1])` is false, return
    /// `pbackfail(traits::to_int_type(c))`. Otherwise,
    /// decrement the next pointer for the input sequence
    /// and return `traits::to_int_type(*gptr())`.
    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      typename basic_streambuf<_CharT, _Traits>::int_type
      basic_streambuf<_CharT, _Traits>::sputbackc(char_type c)
        {
          if (m_binp == m_ninp || !traits_type::eq(c, m_ninp[-1]))
            {
              return pbackfail(traits_type::to_int_type(c));
            }
          return traits_type::to_int_type(*--m_ninp);
        }

      /// \details
      /// If the input sequence putback position is not available
      /// (or no more space in the input buffer),
      /// return `pbackfail()`. Otherwise, decrement the next
      /// pointer for the input sequence and return
      /// `traits::to_int_type(*gptr())`. The effect is to *unget*
      /// the last character *gotten*.
    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      typename basic_streambuf<_CharT, _Traits>::int_type
      basic_streambuf<_CharT, _Traits>::sungetc()
        {
          if (m_binp == m_ninp)
            {
              return pbackfail();
            }
          return traits_type::to_int_type(*--m_ninp);
        }

      /// \details
      /// If the output sequence write position is not available
      /// (or if the output buffer is full),
      /// return `overflow(traits::to_int_- type(c))`.
      /// Otherwise, store `c` at the next pointer for the
      /// output sequence, increments the pointer, and
      /// return `traits::to_int_type(c)`.
    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      typename basic_streambuf<_CharT, _Traits>::int_type
      basic_streambuf<_CharT, _Traits>::sputc(char_type c)
        {
          if (m_nout == m_eout)
            {
              return overflow(traits_type::to_int_type(c));
            }
          *m_nout++ = c;
          return traits_type::to_int_type(c);
        }

      /// \details
      /// Call `xsputn(s,n)` and return its value.
      /// The effect is usually to write `s[0]` through
      /// `s[n-1]` to the output sequence, if possible.
    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      streamsize
      basic_streambuf<_CharT, _Traits>::sputn(const char_type* s, streamsize n)
      {
        return xsputn(s, n);
      }

    /// \details
    template<class _CharT, class _Traits>
      inline _LIBCPP_ALWAYS_INLINE
      _CharT*
      basic_streambuf<_CharT, _Traits>::eback() const
      {
        return m_binp;
      }

    /// \details
    template<class _CharT, class _Traits>
      inline _LIBCPP_ALWAYS_INLINE
      _CharT*
      basic_streambuf<_CharT, _Traits>::gptr() const
      {
        return m_ninp;
      }

    /// \details
    template<class _CharT, class _Traits>
      inline _LIBCPP_ALWAYS_INLINE
      _CharT*
      basic_streambuf<_CharT, _Traits>::egptr() const
      {
        return m_einp;
      }

    /// \details
    /// Add `n` (signed value) to the next pointer for the input sequence.
    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      void
      basic_streambuf<_CharT, _Traits>::gbump(int n)
      {
        m_ninp += n;
      }

    /// \details
    /// Set all three read pointers.
    /// \post
    /// - `gbeg == eback()`
    /// - `gnext == gptr()`
    /// - `gend == egptr()`
    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      void
      basic_streambuf<_CharT, _Traits>::setg(char_type* gbeg, char_type* gnext,
          char_type* gend)
      {
        m_binp = gbeg;
        m_ninp = gnext;
        m_einp = gend;
      }

    /// \details
    template<class _CharT, class _Traits>
      inline _LIBCPP_ALWAYS_INLINE
      _CharT*
      basic_streambuf<_CharT, _Traits>::pbase() const
      {
        return m_bout;
      }

    /// \details
    template<class _CharT, class _Traits>
      inline _LIBCPP_ALWAYS_INLINE
      _CharT*
      basic_streambuf<_CharT, _Traits>::pptr() const
      {
        return m_nout;
      }

    /// \details
    template<class _CharT, class _Traits>
      inline _LIBCPP_ALWAYS_INLINE
      _CharT*
      basic_streambuf<_CharT, _Traits>::epptr() const
      {
        return m_eout;
      }

    /// \details
    /// Adds `n` (signed value) to the next pointer for the output sequence.
    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      void
      basic_streambuf<_CharT, _Traits>::pbump(int n)
      {
        m_nout += n;
      }

    /// \details
    /// Set all three write pointers, starting with the
    /// current pointer att he beginning. (`pptr() == pbase()`).
    /// \post
    /// - `pbeg == pbase()`
    /// - `pbeg == pptr()` (same as `pbeg`)
    /// - `pend == epptr()`
    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      void
      basic_streambuf<_CharT, _Traits>::setp(char_type* pbeg, char_type* pend)
      {
        m_bout = m_nout = pbeg;
        m_eout = pend;
      }

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wweak-template-vtables"
#pragma clang diagnostic ignored "-Wpadded"
#endif

    extern template class basic_streambuf<char> ;

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

  extern template class basic_streambuf<wchar_t>;

#endif

#pragma GCC diagnostic pop

//_LIBCPP_END_NAMESPACE_STD
}
}

#endif  /* OS_PORTABLE_LANGUAGE_CPP_INCLUDE_STEAMBUF_H_ */
