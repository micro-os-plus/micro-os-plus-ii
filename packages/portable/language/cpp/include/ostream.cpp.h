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
/// \brief Output stream function definitions.

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_OSTREAM_CPP_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_OSTREAM_CPP_H_

#include "portable/core/include/ConfigDefines.h"

#include "portable/language/cpp/include/ostream.h"
#include "portable/language/cpp/include/iterator.h"

namespace os
{
  namespace std
  {

    /// \details
    /// If the stream state is good (\a os.good() is true), then if the
    /// stream is tied to another output stream, `is.tie()->flush()`
    /// is called to synchronize the output sequences.
    ///
    /// If the stream state is still good, then the sentry state becomes
    /// true (*okay*).
    template<class TChar_T, class TTraits_T>
      basic_ostream<TChar_T, TTraits_T>::sentry::sentry(
          basic_ostream<TChar_T, TTraits_T>& outs) :
          m_ostream(outs), m_ok(false)
      {
        if (outs.good())
          {
            if (outs.tie())
              outs.tie()->flush();
            m_ok = true;
          }
      }

    /// \details
    /// If `ios_base::unitbuf` is set in `os.flags()`, and
    /// `std::uncaught_exception()` is true, the sentry destructor calls
    /// `flush()` on the output stream.
    template<class TChar_T, class TTraits_T>
      basic_ostream<TChar_T, TTraits_T>::sentry::~sentry()
      {
        if ((m_ostream.rdbuf() != nullptr) && m_ostream.good()
            && (m_ostream.flags() & ios_base::unitbuf)
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
            && !uncaught_exception()
#endif
            )
          {
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
            try
              {
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
            if (m_ostream.rdbuf()->pubsync() == -1)
              {
                m_ostream.setstate(ios_base::badbit);
              }
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
          }
        catch (...)
          {
          }
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
          }
      }

    /// \details
    /// This does very little apart from providing a virtual base dtor.
    template<class TChar_T, class TTraits_T>
      basic_ostream<TChar_T, TTraits_T>::~basic_ostream()
      {
      }

    /// \details
    /// This function behaves as an unformatted output function
    /// (as described in 27.7.3.7, paragraph 1). After the `sentry`
    /// object is constructed, if `sb` is null calls `setstate(badbit)`
    /// (which may throw `ios_base::failure`).
    ///
    /// Gets characters from `sb` and inserts them in `*this`.
    /// Characters are read from `sb` and inserted until any
    /// of the following occurs:
    /// — end-of-file occurs on the input sequence;
    /// — inserting in the output sequence fails (in which
    /// case the character to be inserted is not extracted);
    /// — an exception occurs while getting a character from `sb`.
    ///
    /// If the function inserts no characters, it calls `setstate(failbit)`
    /// (which may throw `ios_base:: failure` (27.5.5.4)).
    /// If an exception was thrown while extracting a character,
    /// the function sets `failbit` in error state, and if `failbit`
    /// is on in `exceptions()` the caught exception is rethrown.

    template<class TChar_T, class TTraits_T>
      basic_ostream<TChar_T, TTraits_T>&
      basic_ostream<TChar_T, TTraits_T>::operator<<(
          basic_streambuf<TChar_T, TTraits_T>* sb)
      {
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
        sentry se(*this);
        if (se)
          {
            if (sb)
              {
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
                try
                  {
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

                typedef istreambuf_iterator<TChar_T, TTraits_T> _Ip;
                typedef ostreambuf_iterator<TChar_T, TTraits_T> _Op;
                _Ip ii(sb);
                _Ip __eof;
                _Op oi(*this);
                size_t __c = 0;
                for (; ii != __eof; ++ii, ++oi, ++__c)
                  {
                    *oi = *ii;
                    if (oi.failed())
                    break;
                  }
                if (__c == 0)
                  {
                    this->setstate(ios_base::failbit);
                  }
#else
                this->setstate(ios_base::failbit);
#endif

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
              }
            catch (...)
              {
                this->__set_failbit_and_consider_rethrow();
              }
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
              }
            else
              {
                this->setstate(ios_base::badbit);
              }
          }
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
      }
    catch (...)
      {
        this->__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
        return *this;
      }

    template<class TChar_T, class TTraits_T>
      basic_ostream<TChar_T, TTraits_T>&
      basic_ostream<TChar_T, TTraits_T>::operator<<(bool n)
      {
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
        sentry se(*this);
        if (se)
          {
            typedef num_put<char_type, ostreambuf_iterator<TChar_T, TTraits_T> > num_put_t;

            const num_put_t& fnum = use_facet<num_put_t>(this->getloc());

            if (fnum.put(*this, *this, this->fill(), n).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
      }
    catch (...)
      {
        this->__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
        return *this;
      }

    template<class TChar_T, class TTraits_T>
      basic_ostream<TChar_T, TTraits_T>&
      basic_ostream<TChar_T, TTraits_T>::operator<<(short n)
      {
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
        sentry se(*this);
        if (se)
          {
            typedef num_put<char_type, ostreambuf_iterator<TChar_T, TTraits_T> > num_put_t;

            const num_put_t& fnum = use_facet<num_put_t>(this->getloc());

#if !defined(OS_INCLUDE_LIBCPP_16BIT_OPTIMISATIONS)

            ios_base::fmtflags flags = ios_base::flags() & ios_base::basefield;
            if (fnum.put(*this, *this, this->fill(),
                flags == ios_base::oct || flags == ios_base::hex ?
                    static_cast<long>(static_cast<unsigned short>(n)) :
                    static_cast<long>(n)).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }

#else
            // optimise for 16 bit
            if (fnum.put(*this, *this, this->fill(), n).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }
#endif
          }
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
      }
    catch (...)
      {
        this->__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
        return *this;
      }

    template<class TChar_T, class TTraits_T>
      basic_ostream<TChar_T, TTraits_T>&
      basic_ostream<TChar_T, TTraits_T>::operator<<(unsigned short n)
      {
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
        sentry se(*this);
        if (se)
          {
            typedef num_put<char_type, ostreambuf_iterator<TChar_T, TTraits_T> > num_put_t;
            const num_put_t& fnum = use_facet<num_put_t>(this->getloc());

#if !defined(OS_INCLUDE_LIBCPP_16BIT_OPTIMISATIONS)

            if (fnum.put(*this, *this, this->fill(),
                static_cast<unsigned long>(n)).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }

#else
            // optimise for 16 bit
            if (fnum.put(*this, *this, this->fill(), n).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }
#endif
          }
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
      }
    catch (...)
      {
        this->__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
        return *this;
      }

    template<class TChar_T, class TTraits_T>
      basic_ostream<TChar_T, TTraits_T>&
      basic_ostream<TChar_T, TTraits_T>::operator<<(int n)
      {
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
        sentry se(*this);
        if (se)
          {
            typedef num_put<char_type, ostreambuf_iterator<TChar_T, TTraits_T> > num_put_t;
            const num_put_t& fnum = use_facet<num_put_t>(this->getloc());

#if !defined(OS_INCLUDE_LIBCPP_16BIT_OPTIMISATIONS)

            ios_base::fmtflags flags = ios_base::flags() & ios_base::basefield;
            if (fnum.put(*this, *this, this->fill(),
                flags == ios_base::oct || flags == ios_base::hex ?
                    static_cast<long>(static_cast<unsigned int>(n)) :
                    static_cast<long>(n)).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }

#else
            // optimise for 16 bit
            if (fnum.put(*this, *this, this->fill(), n).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }
#endif
          }
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
      }
    catch (...)
      {
        this->__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
        return *this;
      }

    template<class TChar_T, class TTraits_T>
      basic_ostream<TChar_T, TTraits_T>&
      basic_ostream<TChar_T, TTraits_T>::operator<<(unsigned int n)
      {
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
        sentry se(*this);
        if (se)
          {
            typedef num_put<char_type, ostreambuf_iterator<TChar_T, TTraits_T> > num_put_t;
            const num_put_t& fnum = use_facet<num_put_t>(this->getloc());

#if !defined(OS_INCLUDE_LIBCPP_16BIT_OPTIMISATIONS)

            if (fnum.put(*this, *this, this->fill(),
                static_cast<unsigned long>(n)).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }

#else
            // optimise for 16 bit
            if (fnum.put(*this, *this, this->fill(), n).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }
#endif
          }
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
      }
    catch (...)
      {
        this->__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
        return *this;
      }

    template<class TChar_T, class TTraits_T>
      basic_ostream<TChar_T, TTraits_T>&
      basic_ostream<TChar_T, TTraits_T>::operator<<(long n)
      {
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
        sentry se(*this);
        if (se)
          {
            typedef num_put<char_type, ostreambuf_iterator<TChar_T, TTraits_T> > num_put_t;
            const num_put_t& fnum = use_facet<num_put_t>(this->getloc());
            if (fnum.put(*this, *this, this->fill(), n).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
      }
    catch (...)
      {
        this->__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
        return *this;
      }

    template<class TChar_T, class TTraits_T>
      basic_ostream<TChar_T, TTraits_T>&
      basic_ostream<TChar_T, TTraits_T>::operator<<(unsigned long n)
      {
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
        sentry se(*this);
        if (se)
          {
            typedef num_put<char_type, ostreambuf_iterator<TChar_T, TTraits_T> > num_put_t;
            const num_put_t& fnum = use_facet<num_put_t>(this->getloc());
            if (fnum.put(*this, *this, this->fill(), n).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
      }
    catch (...)
      {
        this->__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
        return *this;
      }

    template<class TChar_T, class TTraits_T>
      basic_ostream<TChar_T, TTraits_T>&
      basic_ostream<TChar_T, TTraits_T>::operator<<(long long n)
      {
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
        sentry se(*this);
        if (se)
          {
            typedef num_put<char_type, ostreambuf_iterator<TChar_T, TTraits_T> > num_put_t;
            const num_put_t& fnum = use_facet<num_put_t>(this->getloc());
            if (fnum.put(*this, *this, this->fill(), n).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
      }
    catch (...)
      {
        this->__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
        return *this;
      }

    template<class TChar_T, class TTraits_T>
      basic_ostream<TChar_T, TTraits_T>&
      basic_ostream<TChar_T, TTraits_T>::operator<<(unsigned long long n)
      {
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
        sentry se(*this);
        if (se)
          {
            typedef num_put<char_type, ostreambuf_iterator<TChar_T, TTraits_T> > num_put_t;

            const num_put_t& fnum = use_facet<num_put_t>(this->getloc());
            if (fnum.put(*this, *this, this->fill(), n).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
      }
    catch (...)
      {
        this->__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
        return *this;
      }

    template<class TChar_T, class TTraits_T>
      basic_ostream<TChar_T, TTraits_T>&
      basic_ostream<TChar_T, TTraits_T>::operator<<(float n)
      {
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
        sentry se(*this);
        if (se)
          {
            typedef num_put<char_type, ostreambuf_iterator<TChar_T, TTraits_T> > num_put_t;
            const num_put_t& fnum = use_facet<num_put_t>(this->getloc());
            if (fnum.put(*this, *this, this->fill(), static_cast<double>(n)).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
      }
    catch (...)
      {
        this->__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
        return *this;
      }

    template<class TChar_T, class TTraits_T>
      basic_ostream<TChar_T, TTraits_T>&
      basic_ostream<TChar_T, TTraits_T>::operator<<(double n)
      {
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
        sentry se(*this);
        if (se)
          {
            typedef num_put<char_type, ostreambuf_iterator<TChar_T, TTraits_T> > num_put_t;
            const num_put_t& fnum = use_facet<num_put_t>(this->getloc());
            if (fnum.put(*this, *this, this->fill(), n).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
      }
    catch (...)
      {
        this->__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
        return *this;
      }

    template<class TChar_T, class TTraits_T>
      basic_ostream<TChar_T, TTraits_T>&
      basic_ostream<TChar_T, TTraits_T>::operator<<(long double n)
      {
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
        sentry se(*this);
        if (se)
          {
            typedef num_put<char_type, ostreambuf_iterator<TChar_T, TTraits_T> > num_put_t;
            const num_put_t& fnum = use_facet<num_put_t>(this->getloc());
            if (fnum.put(*this, *this, this->fill(), n).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
      }
    catch (...)
      {
        this->__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
        return *this;
      }

    template<class TChar_T, class TTraits_T>
      basic_ostream<TChar_T, TTraits_T>&
      basic_ostream<TChar_T, TTraits_T>::operator<<(const void* n)
      {
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
        sentry se(*this);
        if (se)
          {
            typedef num_put<char_type, ostreambuf_iterator<TChar_T, TTraits_T> > num_put_t;
            const num_put_t& fnum = use_facet<num_put_t>(this->getloc());
            if (fnum.put(*this, *this, this->fill(), n).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
      }
    catch (...)
      {
        this->__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
        return *this;
      }

    /// \details
    /// Behaves as an unformatted output function (as described in
    /// 27.7.3.7, paragraph 1). After constructing a `sentry` object,
    /// inserts the character `c`, if possible.
    ///
    /// Otherwise, calls `setstate(badbit)` (which may throw
    /// `ios_base::failure` (27.5.5.4)).
    ///
    /// \note  This function is not overloaded on `signed char` and
    ///        `unsigned char`.
    template<class TChar_T, class TTraits_T>
      basic_ostream<TChar_T, TTraits_T>&
      basic_ostream<TChar_T, TTraits_T>::put(char_type c)
      {
        basic_streambuf<TChar_T, TTraits_T>* sb;
        sb = this->rdbuf();
        if (sb != nullptr)
          {

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
            try
              {
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
            sentry se(*this);
            if (se)
              {
#if 0
                // TODO: implement without iterator, with sputc(c)
                // (beware that streambuf may be 0)
#else
                typedef ostreambuf_iterator<TChar_T, TTraits_T> _Op;
                _Op oi(*this);
                *oi = c;
                if (oi.failed())
                  {
                    this->setstate(ios_base::badbit);
                  }
#endif
              }
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
          }
        catch (...)
          {
            this->__set_badbit_and_consider_rethrow();
          }
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
          }
        return *this;
      }

    /// \details
    /// Behaves as an unformatted output function (as described in
    /// 27.7.3.7, paragraph 1). After constructing a `sentry` object,
    /// obtains characters to insert from successive locations
    /// of an array whose first element is designated by `str`.
    /// Characters are inserted until either of the following occurs:
    /// - `n` characters are inserted;
    /// - inserting in the output sequence fails (in which case
    /// the function calls `setstate(badbit)`, which
    /// may throw `ios_base::failure` (27.5.5.4)).
    ///
    /// \note  This function is not overloaded on signed char and
    ///        unsigned char.
    template<class TChar_T, class TTraits_T>
      basic_ostream<TChar_T, TTraits_T>&
      basic_ostream<TChar_T, TTraits_T>::write(const char_type* str,
          streamsize n)
      {
        basic_streambuf<TChar_T, TTraits_T>* sb;
        sb = this->rdbuf();
        if (sb != nullptr)
          {
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
            try
              {
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
            sentry __sen(*this);
            if (__sen)
              {
                if (n != 0)
                  {
                    if (sb->sputn(str, n) != n)
                      {
                        this->setstate(ios_base::badbit);
                      }
                  }
              }
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
          }
        catch (...)
          {
            this->__set_badbit_and_consider_rethrow();
          }
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
          }
        return *this;
      }

    /// \details
    /// Behaves as an unformatted output function (as described in
    /// 27.7.3.6.1, paragraph 1). If `rdbuf()` is not a null pointer,
    /// constructs a `sentry` object. If this object returns `true`
    /// when converted to a value of type `bool` the function calls
    /// `rdbuf()->pubsync()`. If that function returns -1 calls
    /// `setstate(badbit)` (which may throw `ios_base::failure`
    /// (27.5.5.4)). Otherwise, if the `sentry` object returns
    /// `false`, does nothing.
    template<class TChar_T, class TTraits_T>
      basic_ostream<TChar_T, TTraits_T>&
      basic_ostream<TChar_T, TTraits_T>::flush()
      {
        basic_streambuf<TChar_T, TTraits_T>* sb;
        sb = this->rdbuf();
        if (sb != nullptr)
          {

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
            try
              {
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
            sentry se(*this);
            if (se)
              {
                if (sb->pubsync() == -1)
                  this->setstate(ios_base::badbit);
              }
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
          }
        catch (...)
          {
            this->__set_badbit_and_consider_rethrow();
          }
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
          }
        return *this;
      }

    /// \details
    /// If `fail()` is not false, returns `pos_type(-1)` to indicate
    /// failure.  Otherwise returns `rdbuf()->pubseekoff(0,cur,out)`.
    template<class TChar_T, class TTraits_T>
      typename basic_ostream<TChar_T, TTraits_T>::pos_type
      basic_ostream<TChar_T, TTraits_T>::tellp()
      {
        basic_streambuf<TChar_T, TTraits_T>* sb;
        sb = this->rdbuf();
        // if no streambuf, error
        if (sb == nullptr || this->fail())
          {
            return pos_type(-1);
          }
        return sb->pubseekoff(0, ios_base::cur, ios_base::out);
      }

    /// \details
    /// If `fail()` is not true, calls `rdbuf()->pubseekpos(pos)`.  If
    /// that function fails, sets `failbit`.
    template<class TChar_T, class TTraits_T>
      basic_ostream<TChar_T, TTraits_T>&
      basic_ostream<TChar_T, TTraits_T>::seekp(pos_type pos)
      {
        basic_streambuf<TChar_T, TTraits_T>* sb;
        sb = this->rdbuf();
        // if no streambuf, skip
        if (sb != nullptr && !this->fail())
          {
            if (sb->pubseekpos(pos, ios_base::out) == pos_type(-1))
              this->setstate(ios_base::failbit);
          }
        return *this;
      }

    /// \details
    /// If `fail()` is not true, calls `rdbuf()->pubseekoff(off,dir)`.
    /// If that function fails, sets failbit.
    template<class TChar_T, class TTraits_T>
      basic_ostream<TChar_T, TTraits_T>&
      basic_ostream<TChar_T, TTraits_T>::seekp(off_type off,
          ios_base::seekdir dir)
      {
        basic_streambuf<TChar_T, TTraits_T>* sb;
        sb = this->rdbuf();
        // if no streambuf, skip
        if (sb != nullptr && !this->fail())
          {
            sb->pubseekoff(off, dir, ios_base::out);
          }
        return *this;
      }

  }
}

#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_OSTREAM_CPP_H_
