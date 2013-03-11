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

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INTERNAL_POSTYPE_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INTERNAL_POSTYPE_H_

#include "portable/core/include/OS_Defines.h"

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS) || defined(__DOXYGEN__)

#include "portable/language/cpp/include/internal/__config.h"

namespace os
{
  namespace std
  {

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

    // 27.5.4 Class template fpos
    template<class _StateT>
      class _LIBCPP_VISIBLE fpos
      {
      public:
        _LIBCPP_INLINE_VISIBILITY
        fpos(streamoff __off = streamoff());

        // 27.5.4.1 Members
        _LIBCPP_INLINE_VISIBILITY
        _StateT
        state() const;

        _LIBCPP_INLINE_VISIBILITY
        void
        state(_StateT __st);

        // 27.5.4.2 fpos requirements
        _LIBCPP_INLINE_VISIBILITY
        operator streamoff() const;

        _LIBCPP_INLINE_VISIBILITY
        fpos&
        operator+=(streamoff __off);

        _LIBCPP_INLINE_VISIBILITY
        fpos
        operator+(streamoff __off) const;

        _LIBCPP_INLINE_VISIBILITY
        fpos&
        operator-=(streamoff __off);

        _LIBCPP_INLINE_VISIBILITY
        fpos
        operator-(streamoff __off) const;

      private:
        streamoff m_off;
        _StateT m_st;

      };
#pragma GCC diagnostic pop

    // ------------------------------------------------------------------------
    // inline members

    template<class _StateT>
      inline _LIBCPP_INLINE_VISIBILITY
      fpos<_StateT>::fpos(streamoff __off)
          : m_off(__off), m_st()
      {
      }

    template<class _StateT>
      inline _LIBCPP_INLINE_VISIBILITY
      fpos<_StateT>::operator streamoff() const
      {
        return m_off;
      }

    template<class _StateT>
      inline _LIBCPP_INLINE_VISIBILITY
      _StateT
      fpos<_StateT>::state() const
      {
        return m_st;
      }

    template<class _StateT>
      inline _LIBCPP_INLINE_VISIBILITY
      void
      fpos<_StateT>::state(_StateT __st)
      {
        m_st = __st;
      }

    template<class _StateT>
      inline _LIBCPP_INLINE_VISIBILITY
      fpos<_StateT>&
      fpos<_StateT>::operator+=(streamoff __off)
      {
        m_off += __off;
        return *this;
      }

    template<class _StateT>
      inline _LIBCPP_INLINE_VISIBILITY
      fpos<_StateT>
      fpos<_StateT>::operator+(streamoff __off) const
      {
        fpos __t(*this);
        __t += __off;
        return __t;
      }

    template<class _StateT>
      inline _LIBCPP_INLINE_VISIBILITY
      fpos<_StateT>&
      fpos<_StateT>::operator-=(streamoff __off)
      {
        m_off -= __off;
        return *this;
      }

    template<class _StateT>
      inline _LIBCPP_INLINE_VISIBILITY
      fpos<_StateT>
      fpos<_StateT>::operator-(streamoff __off) const
      {
        fpos __t(*this);
        __t -= __off;
        return __t;
      }

    // ========================================================================
    // Subtract two fpos<> and return a streamoff
    template<class _StateT>
      inline _LIBCPP_INLINE_VISIBILITY
      streamoff
      operator-(const fpos<_StateT>& __x, const fpos<_StateT>& __y)
      {
        return streamoff(__x) - streamoff(__y);
      }

    // Compare two fpos<> for equality
    template<class _StateT>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      operator==(const fpos<_StateT>& __x, const fpos<_StateT>& __y)
      {
        return streamoff(__x) == streamoff(__y);
      }

    // Compare two fpos<> for non equality
    template<class _StateT>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      operator!=(const fpos<_StateT>& __x, const fpos<_StateT>& __y)
      {
        return streamoff(__x) != streamoff(__y);
      }
  // ========================================================================

  }
}

#endif // defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS)
#endif // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INTERNAL_POSTYPE_H_
