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

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_OSTREAM_CPP_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_OSTREAM_CPP_H_

#include "portable/core/include/OS_Defines.h"

#include "portable/language/cpp/include/ostream.h"
#include "portable/language/cpp/include/iterator.h"

namespace os
{
  namespace std
  {

    // The sentry class is used as a uniform method to check the status
    // of the stream in order to skip action if not good, and to flush
    // the output at the end if unitbuf is set.

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>::sentry::sentry(
          basic_ostream<_CharT, _Traits>& __os)
          : m_ostream(__os), m_ok(false)
      {
        if (__os.good())
          {
            if (__os.tie())
              __os.tie()->flush();
            m_ok = true;
          }
      }

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>::sentry::~sentry()
      {
        if ((m_ostream.rdbuf() != nullptr) && m_ostream.good()
            && (m_ostream.flags() & ios_base::unitbuf)
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
            && !uncaught_exception()
#endif
            )
          {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
            try
              {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
            if (m_ostream.rdbuf()->pubsync() == -1)
              {
                m_ostream.setstate(ios_base::badbit);
              }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
          }
        catch (...)
          {
          }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
          }
      }

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>::~basic_ostream()
      {
      }

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      basic_ostream<_CharT, _Traits>::operator<<(
          basic_streambuf<char_type, traits_type>* __sb)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        sentry __s(*this);
        if (__s)
          {
            if (__sb)
              {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
                try
                  {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

                typedef istreambuf_iterator<_CharT, _Traits> _Ip;
                typedef ostreambuf_iterator<_CharT, _Traits> _Op;
                _Ip __i(__sb);
                _Ip __eof;
                _Op __o(*this);
                size_t __c = 0;
                for (; __i != __eof; ++__i, ++__o, ++__c)
                  {
                    *__o = *__i;
                    if (__o.failed())
                    break;
                  }
                if (__c == 0)
                  {
                    this->setstate(ios_base::failbit);
                  }
#else
                this->setstate(ios_base::failbit);
#endif

#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
              }
            catch (...)
              {
                this->__set_failbit_and_consider_rethrow();
              }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
              }
            else
              {
                this->setstate(ios_base::badbit);
              }
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        this->__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return *this;
      }

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      basic_ostream<_CharT, _Traits>::operator<<(bool __n)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        sentry __s(*this);
        if (__s)
          {
            typedef num_put<char_type,
                ostreambuf_iterator<char_type, traits_type> > _Fp;

            const _Fp& __f = use_facet<_Fp>(this->getloc());

            if (__f.put(*this, *this, this->fill(), __n).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        this->__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return *this;
      }

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      basic_ostream<_CharT, _Traits>::operator<<(short __n)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        sentry __s(*this);
        if (__s)
          {
            typedef num_put<char_type,
                ostreambuf_iterator<char_type, traits_type> > _Fp;

            const _Fp& __f = use_facet<_Fp>(this->getloc());

#if !defined(OS_INCLUDE_LIBCPP_16BIT_OPTIMISATIONS)

            ios_base::fmtflags __flags = ios_base::flags()
                & ios_base::basefield;
            if (__f.put(*this, *this, this->fill(),
                __flags == ios_base::oct || __flags == ios_base::hex ?
                    static_cast<long>(static_cast<unsigned short>(__n)) :
                    static_cast<long>(__n)).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }

#else
            // optimise for 16 bit
            if (__f.put(*this, *this, this->fill(), __n).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }
#endif
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        this->__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return *this;
      }

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      basic_ostream<_CharT, _Traits>::operator<<(unsigned short __n)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        sentry __s(*this);
        if (__s)
          {
            typedef num_put<char_type,
                ostreambuf_iterator<char_type, traits_type> > _Fp;
            const _Fp& __f = use_facet<_Fp>(this->getloc());

#if !defined(OS_INCLUDE_LIBCPP_16BIT_OPTIMISATIONS)

            if (__f.put(*this, *this, this->fill(),
                static_cast<unsigned long>(__n)).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }

#else
            // optimise for 16 bit
            if (__f.put(*this, *this, this->fill(), __n).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }
#endif
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        this->__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return *this;
      }

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      basic_ostream<_CharT, _Traits>::operator<<(int __n)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        sentry __s(*this);
        if (__s)
          {
            typedef num_put<char_type,
                ostreambuf_iterator<char_type, traits_type> > _Fp;
            const _Fp& __f = use_facet<_Fp>(this->getloc());

#if !defined(OS_INCLUDE_LIBCPP_16BIT_OPTIMISATIONS)

            ios_base::fmtflags __flags = ios_base::flags()
                & ios_base::basefield;
            if (__f.put(*this, *this, this->fill(),
                __flags == ios_base::oct || __flags == ios_base::hex ?
                    static_cast<long>(static_cast<unsigned int>(__n)) :
                    static_cast<long>(__n)).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }

#else
            // optimise for 16 bit
            if (__f.put(*this, *this, this->fill(), __n).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }
#endif
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        this->__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return *this;
      }

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      basic_ostream<_CharT, _Traits>::operator<<(unsigned int __n)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        sentry __s(*this);
        if (__s)
          {
            typedef num_put<char_type,
                ostreambuf_iterator<char_type, traits_type> > _Fp;
            const _Fp& __f = use_facet<_Fp>(this->getloc());

#if !defined(OS_INCLUDE_LIBCPP_16BIT_OPTIMISATIONS)

            if (__f.put(*this, *this, this->fill(),
                static_cast<unsigned long>(__n)).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }

#else
            // optimise for 16 bit
            if (__f.put(*this, *this, this->fill(), __n).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }
#endif
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        this->__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return *this;
      }

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      basic_ostream<_CharT, _Traits>::operator<<(long __n)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        sentry __s(*this);
        if (__s)
          {
            typedef num_put<char_type,
                ostreambuf_iterator<char_type, traits_type> > _Fp;
            const _Fp& __f = use_facet<_Fp>(this->getloc());
            if (__f.put(*this, *this, this->fill(), __n).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        this->__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return *this;
      }

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      basic_ostream<_CharT, _Traits>::operator<<(unsigned long __n)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        sentry __s(*this);
        if (__s)
          {
            typedef num_put<char_type,
                ostreambuf_iterator<char_type, traits_type> > _Fp;
            const _Fp& __f = use_facet<_Fp>(this->getloc());
            if (__f.put(*this, *this, this->fill(), __n).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        this->__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return *this;
      }

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      basic_ostream<_CharT, _Traits>::operator<<(long long __n)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        sentry __s(*this);
        if (__s)
          {
            typedef num_put<char_type,
                ostreambuf_iterator<char_type, traits_type> > _Fp;
            const _Fp& __f = use_facet<_Fp>(this->getloc());
            if (__f.put(*this, *this, this->fill(), __n).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        this->__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return *this;
      }

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      basic_ostream<_CharT, _Traits>::operator<<(unsigned long long __n)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        sentry __s(*this);
        if (__s)
          {
            typedef num_put<char_type,
                ostreambuf_iterator<char_type, traits_type> > _Fp;

            const _Fp& __f = use_facet<_Fp>(this->getloc());
            if (__f.put(*this, *this, this->fill(), __n).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        this->__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return *this;
      }

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      basic_ostream<_CharT, _Traits>::operator<<(float __n)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        sentry __s(*this);
        if (__s)
          {
            typedef num_put<char_type,
                ostreambuf_iterator<char_type, traits_type> > _Fp;
            const _Fp& __f = use_facet<_Fp>(this->getloc());
            if (__f.put(*this, *this, this->fill(), static_cast<double>(__n)).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        this->__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return *this;
      }

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      basic_ostream<_CharT, _Traits>::operator<<(double __n)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        sentry __s(*this);
        if (__s)
          {
            typedef num_put<char_type,
                ostreambuf_iterator<char_type, traits_type> > _Fp;
            const _Fp& __f = use_facet<_Fp>(this->getloc());
            if (__f.put(*this, *this, this->fill(), __n).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        this->__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return *this;
      }

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      basic_ostream<_CharT, _Traits>::operator<<(long double __n)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        sentry __s(*this);
        if (__s)
          {
            typedef num_put<char_type,
                ostreambuf_iterator<char_type, traits_type> > _Fp;
            const _Fp& __f = use_facet<_Fp>(this->getloc());
            if (__f.put(*this, *this, this->fill(), __n).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        this->__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return *this;
      }

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      basic_ostream<_CharT, _Traits>::operator<<(const void* __n)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        sentry __s(*this);
        if (__s)
          {
            typedef num_put<char_type,
                ostreambuf_iterator<char_type, traits_type> > _Fp;
            const _Fp& __f = use_facet<_Fp>(this->getloc());
            if (__f.put(*this, *this, this->fill(), __n).failed())
              {
                this->setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        this->__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return *this;
      }

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      basic_ostream<_CharT, _Traits>::put(char_type __c)
      {
        basic_streambuf<_CharT, _Traits>* sb;
        sb = this->rdbuf();
        if (sb != nullptr)
          {

#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
            try
              {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
            sentry __s(*this);
            if (__s)
              {
#if 0
                // TODO: implement without iterator, with sputc(c)
                // (beware that streambuf may be 0)
#else
                typedef ostreambuf_iterator<_CharT, _Traits> _Op;
                _Op __o(*this);
                *__o = __c;
                if (__o.failed())
                  {
                    this->setstate(ios_base::badbit);
                  }
#endif
              }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
          }
        catch (...)
          {
            this->__set_badbit_and_consider_rethrow();
          }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
          }
        return *this;
      }

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      basic_ostream<_CharT, _Traits>::write(const char_type* __s,
          streamsize __n)
      {
        basic_streambuf<_CharT, _Traits>* sb;
        sb = this->rdbuf();
        if (sb != nullptr)
          {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
            try
              {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
            sentry __sen(*this);
            if (__sen)
              {
                if (__n != 0)
                  {
                    if (sb->sputn(__s, __n) != __n)
                      {
                        this->setstate(ios_base::badbit);
                      }
                  }
              }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
          }
        catch (...)
          {
            this->__set_badbit_and_consider_rethrow();
          }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
          }
        return *this;
      }

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      basic_ostream<_CharT, _Traits>::flush()
      {
        basic_streambuf<_CharT, _Traits>* sb;
        sb = this->rdbuf();
        if (sb != nullptr)
          {

#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
            try
              {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
            sentry __s(*this);
            if (__s)
              {
                if (sb->pubsync() == -1)
                  this->setstate(ios_base::badbit);
              }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
          }
        catch (...)
          {
            this->__set_badbit_and_consider_rethrow();
          }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
          }
        return *this;
      }

    template<class _CharT, class _Traits>
      typename basic_ostream<_CharT, _Traits>::pos_type
      basic_ostream<_CharT, _Traits>::tellp()
      {
        basic_streambuf<_CharT, _Traits>* sb;
        sb = this->rdbuf();
        // if no streambuf, error
        if (sb == nullptr || this->fail())
          {
            return pos_type(-1);
          }
        return sb->pubseekoff(0, ios_base::cur, ios_base::out);
      }

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      basic_ostream<_CharT, _Traits>::seekp(pos_type __pos)
      {
        basic_streambuf<_CharT, _Traits>* sb;
        sb = this->rdbuf();
        // if no streambuf, skip
        if (sb != nullptr && !this->fail())
          {
            if (sb->pubseekpos(__pos, ios_base::out) == pos_type(-1))
              this->setstate(ios_base::failbit);
          }
        return *this;
      }

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      basic_ostream<_CharT, _Traits>::seekp(off_type __off,
          ios_base::seekdir __dir)
      {
        basic_streambuf<_CharT, _Traits>* sb;
        sb = this->rdbuf();
        // if no streambuf, skip
        if (sb != nullptr && !this->fail())
          {
            sb->pubseekoff(__off, __dir, ios_base::out);
          }
        return *this;
      }

    // ========================================================================
    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      operator<<(basic_ostream<_CharT, _Traits>& __os, _CharT __c)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        typename basic_ostream<_CharT, _Traits>::sentry __s(__os);
        if (__s)
          {
            typedef ostreambuf_iterator<_CharT, _Traits> _Ip;

            const _CharT* pBeg = &__c;
            const _CharT* pEnd = &__c + 1;
            const _CharT* pPad;
            if ((__os.flags() & ios_base::adjustfield) == ios_base::left)
              {
                pPad = pEnd;
              }
            else
              {
                pPad = pBeg;
              }

            if (__padAndOutput(_Ip(__os), pBeg, pPad, pEnd, __os, __os.fill()).failed())
              {
                __os.setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        __os.__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return __os;
      }

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      operator<<(basic_ostream<_CharT, _Traits>& __os, char __cn)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        typename basic_ostream<_CharT, _Traits>::sentry __s(__os);
        if (__s)
          {
            _CharT __c = __os.widen(__cn);
            typedef ostreambuf_iterator<_CharT, _Traits> _Ip;

            const _CharT* pBeg = &__c;
            const _CharT* pEnd = &__c + 1;
            const _CharT* pPad;

            if ((__os.flags() & ios_base::adjustfield) == ios_base::left)
              {
                pPad = pEnd;
              }
            else
              {
                pPad = pBeg;
              }

            if (__padAndOutput(_Ip(__os), pBeg, pPad, pEnd, __os, __os.fill()).failed())
              {
                __os.setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        __os.__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return __os;
      }

    template<class _Traits>
      basic_ostream<char, _Traits>&
      operator<<(basic_ostream<char, _Traits>& __os, char __c)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        typename basic_ostream<char, _Traits>::sentry __s(__os);
        if (__s)
          {
            typedef ostreambuf_iterator<char, _Traits> _Ip;

            const char* pBeg = &__c;
            const char* pEnd = &__c + 1;
            const char* pPad;

            if ((__os.flags() & ios_base::adjustfield) == ios_base::left)
              {
                pPad = pEnd;
              }
            else
              {
                pPad = pBeg;
              }

            if (__padAndOutput(_Ip(__os), pBeg, pPad, pEnd, __os, __os.fill()).failed())
              {
                __os.setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        __os.__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return __os;
      }

    template<class _Traits>
      basic_ostream<char, _Traits>&
      operator<<(basic_ostream<char, _Traits>& __os, signed char __c)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        typename basic_ostream<char, _Traits>::sentry __s(__os);
        if (__s)
          {
            typedef ostreambuf_iterator<char, _Traits> _Ip;

            const char* pBeg = (char*) &__c;
            const char* pEnd = (char*) &__c + 1;
            const char* pPad;

            if ((__os.flags() & ios_base::adjustfield) == ios_base::left)
              {
                pPad = pEnd;
              }
            else
              {
                pPad = pBeg;
              }

            if (__padAndOutput(_Ip(__os), pBeg, pPad, pEnd, __os, __os.fill()).failed())

              {
                __os.setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        __os.__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return __os;
      }

    template<class _Traits>
      basic_ostream<char, _Traits>&
      operator<<(basic_ostream<char, _Traits>& __os, unsigned char __c)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        typename basic_ostream<char, _Traits>::sentry __s(__os);
        if (__s)
          {
            typedef ostreambuf_iterator<char, _Traits> _Ip;

            const char* pBeg = (char*) &__c;
            const char* pEnd = (char*) &__c + 1;
            const char* pPad;

            if ((__os.flags() & ios_base::adjustfield) == ios_base::left)
              {
                pPad = pEnd;
              }
            else
              {
                pPad = pBeg;
              }

            if (__padAndOutput(_Ip(__os), pBeg, pPad, pEnd, __os, __os.fill()).failed())
              {
                __os.setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        __os.__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return __os;
      }

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      operator<<(basic_ostream<_CharT, _Traits>& __os, const _CharT* __str)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        typename basic_ostream<_CharT, _Traits>::sentry __s(__os);
        if (__s)
          {
            typedef ostreambuf_iterator<_CharT, _Traits> _Ip;
            size_t __len = _Traits::length(__str);

            const _CharT* pBeg = __str;
            const _CharT* pEnd = __str + __len;
            const _CharT* pPad;

            if ((__os.flags() & ios_base::adjustfield) == ios_base::left)
              {
                pPad = pEnd;
              }
            else
              {
                pPad = pBeg;
              }

            if (__padAndOutput(_Ip(__os), pBeg, pPad, pEnd, __os, __os.fill()).failed())

              {
                __os.setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        __os.__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return __os;
      }

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      operator<<(basic_ostream<_CharT, _Traits>& __os, const char* __strn)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        typename basic_ostream<_CharT, _Traits>::sentry __s(__os);
        if (__s)
          {
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
            typedef ostreambuf_iterator<_CharT, _Traits> _Ip;
            size_t __len = char_traits<char>::length(__strn);
            const int __bs = 100;
            _CharT __wbb[__bs];
            _CharT* __wb = __wbb;
            unique_ptr<_CharT, void
            (*)(void*)> __h(0, free);
            if (__len > __bs)
              {
                __wb = (_CharT*) malloc(__len * sizeof(_CharT));
                if (__wb == 0)
                __throw_bad_alloc();
                __h.reset(__wb);
              }
            for (_CharT* __p = __wb; *__strn != '\0'; ++__strn, ++__p)
            *__p = __os.widen(*__strn);
            if (__pad_and_output(_Ip(__os), __wb,
                    (__os.flags() & ios_base::adjustfield) == ios_base::left ?
                    __wb + __len : __wb, __wb + __len, __os, __os.fill()).failed())
              {
                __os.setstate(ios_base::badbit | ios_base::failbit);
              }
#else
            __os.setstate(ios_base::badbit | ios_base::failbit);
#endif
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        __os.__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return __os;
      }
#endif

    template<class _Traits>
      basic_ostream<char, _Traits>&
      operator<<(basic_ostream<char, _Traits>& __os, const char* __str)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        typename basic_ostream<char, _Traits>::sentry __s(__os);
        if (__s)
          {
            typedef ostreambuf_iterator<char, _Traits> _Ip;
            size_t __len = _Traits::length(__str);

            const char* pBeg = __str;
            const char* pEnd = __str + __len;
            const char* pPad;

            if ((__os.flags() & ios_base::adjustfield) == ios_base::left)
              {
                pPad = pEnd;
              }
            else
              {
                pPad = pBeg;
              }

            if (__padAndOutput(_Ip(__os), pBeg, pPad, pEnd, __os, __os.fill()).failed())
              {
                __os.setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        __os.__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return __os;
      }

    template<class _Traits>
      basic_ostream<char, _Traits>&
      operator<<(basic_ostream<char, _Traits>& __os, const signed char* __str)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        typename basic_ostream<char, _Traits>::sentry __s(__os);
        if (__s)
          {
            typedef ostreambuf_iterator<char, _Traits> _Ip;
            size_t __len = _Traits::length((const char*) __str);

            const char* pBeg = (const char*)(__str);
            const char* pEnd = (const char*)(__str + __len);
            const char* pPad;

            if ((__os.flags() & ios_base::adjustfield) == ios_base::left)
              {
                pPad = pEnd;
              }
            else
              {
                pPad = pBeg;
              }

            if (__padAndOutput(_Ip(__os), pBeg, pPad, pEnd, __os, __os.fill()).failed())
              {
                __os.setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        __os.__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return __os;
      }

    template<class _Traits>
      basic_ostream<char, _Traits>&
      operator<<(basic_ostream<char, _Traits>& __os, const unsigned char* __str)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        typename basic_ostream<char, _Traits>::sentry __s(__os);
        if (__s)
          {
            typedef ostreambuf_iterator<char, _Traits> _Ip;
            size_t __len = _Traits::length((const char*) __str);

            const char* pBeg = (const char*)(__str);
            const char* pEnd = (const char*)(__str + __len);
            const char* pPad;

            if ((__os.flags() & ios_base::adjustfield) == ios_base::left)
              {
                pPad = pEnd;
              }
            else
              {
                pPad = pBeg;
              }

            if (__padAndOutput(_Ip(__os), pBeg, pPad, pEnd, __os, __os.fill()).failed())
              {
                __os.setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        __os.__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return __os;
      }

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
  template<class _CharT, class _Traits, class _Allocator>
  basic_ostream<_CharT, _Traits>&
  operator<<(basic_ostream<_CharT, _Traits>& __os,
      const basic_string<_CharT, _Traits, _Allocator>& __str)
    {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      try
        {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
          typename basic_ostream<_CharT, _Traits>::sentry __s(__os);
          if (__s)
            {
              typedef ostreambuf_iterator<_CharT, _Traits> _Ip;
              size_t __len = __str.size();
              if (__pad_and_output(_Ip(__os), __str.data(),
                      (__os.flags() & ios_base::adjustfield) == ios_base::left ?
                      __str.data() + __len : __str.data(), __str.data() + __len,
                      __os, __os.fill()).failed())
                {
                  __os.setstate(ios_base::badbit | ios_base::failbit);
                }
            }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        }
      catch (...)
        {
          __os.__set_badbit_and_consider_rethrow();
        }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
      return __os;
    }
#endif

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
  template<class _CharT, class _Traits, size_t _Size>
  basic_ostream<_CharT, _Traits>&
  operator<<(basic_ostream<_CharT, _Traits>& __os, const bitset<_Size>& __x)
    {
      return __os
      << __x.template to_string<_CharT, _Traits>(
          use_facet < ctype<_CharT> > (__os.getloc()).widen('0'),
          use_facet < ctype<_CharT> > (__os.getloc()).widen('1'));
    }
#endif
}
}

#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_OSTREAM_CPP_H_
