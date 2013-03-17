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
#include "portable/language/cpp/include/iosfwd.h"

namespace os
{
  namespace std
  {

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

    // 27.5.4 Class template fpos

    /// \class fpos _fpos.h "portable/language/cpp/include/internal/_fpos.h"
    /// \ingroup std_io
    ///
    /// \brief  Class representing stream positions.
    ///
    /// The standard places no requirements upon the template
    /// parameter `_StateT`.
    /// In this implementation `_StateT` must be DefaultConstructible,
    /// CopyConstructible and Assignable.  The standard only requires
    /// that `fpos`
    /// should contain a member of type `_StateT`. In this
    /// implementation it also
    /// contains an offset stored as a signed integer.
    ///
    /// @tparam  _StateT  Type passed to and returned from `state()`.

    template<class _StateT>
      class _LIBCPP_VISIBLE fpos
      {
      public:
        _LIBCPP_INLINE_VISIBILITY
        fpos(streamoff off = streamoff());

        // 27.5.4.1 Members
        _LIBCPP_INLINE_VISIBILITY
        _StateT
        state() const;

        /// \brief Remember the value of `st`.
        ///
        /// \param st State.
        /// \par Returns
        /// Nothing.
        _LIBCPP_INLINE_VISIBILITY
        void
        state(_StateT st);

        // 27.5.4.2 fpos requirements
        /// \brief Convert to streamoff.
        _LIBCPP_INLINE_VISIBILITY
        operator streamoff() const;

        /// \brief Add offset to this position.
        ///
        /// \param off Offset.
        _LIBCPP_INLINE_VISIBILITY
        fpos&
        operator+=(streamoff off);

        /// \brief Add position and offset.
        ///
        /// \param off Offset.
        _LIBCPP_INLINE_VISIBILITY
        fpos
        operator+(streamoff off) const;

        /// \brief Subtract offset from this position.
        ///
        /// \param off Offset.
        _LIBCPP_INLINE_VISIBILITY
        fpos&
        operator-=(streamoff off);

        /// \brief Subtract offset from position.
        ///
        /// \param off Offset.
        _LIBCPP_INLINE_VISIBILITY
        fpos
        operator-(streamoff off) const;

      private:
        /// \brief Member to store offset.
        streamoff m_off;
        /// \brief Member to store state.
        _StateT m_st;

      };
#pragma GCC diagnostic pop

    // ------------------------------------------------------------------------
    // inline members

    template<class _StateT>
      inline _LIBCPP_INLINE_VISIBILITY
      fpos<_StateT>::fpos(streamoff off)
          : m_off(off), m_st()
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
      fpos<_StateT>::state(_StateT st)
      {
        m_st = st;
      }

    template<class _StateT>
      inline _LIBCPP_INLINE_VISIBILITY
      fpos<_StateT>&
      fpos<_StateT>::operator+=(streamoff off)
      {
        m_off += off;
        return *this;
      }

    template<class _StateT>
      inline _LIBCPP_INLINE_VISIBILITY
      fpos<_StateT>
      fpos<_StateT>::operator+(streamoff off) const
      {
        fpos tpos(*this);
        tpos += off;
        return tpos;
      }

    template<class _StateT>
      inline _LIBCPP_INLINE_VISIBILITY
      fpos<_StateT>&
      fpos<_StateT>::operator-=(streamoff off)
      {
        m_off -= off;
        return *this;
      }

    template<class _StateT>
      inline _LIBCPP_INLINE_VISIBILITY
      fpos<_StateT>
      fpos<_StateT>::operator-(streamoff off) const
      {
        fpos tpos(*this);
        tpos -= off;
        return tpos;
      }

    // ========================================================================
    // Subtract two fpos<> and return a streamoff
    template<class _StateT>
      inline _LIBCPP_INLINE_VISIBILITY
      streamoff
      operator-(const fpos<_StateT>& x, const fpos<_StateT>& y)
      {
        return streamoff(x) - streamoff(y);
      }

    // Compare two fpos<> for equality
    template<class _StateT>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      operator==(const fpos<_StateT>& x, const fpos<_StateT>& y)
      {
        return streamoff(x) == streamoff(y);
      }

    // Compare two fpos<> for non equality
    template<class _StateT>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      operator!=(const fpos<_StateT>& x, const fpos<_StateT>& y)
      {
        return streamoff(x) != streamoff(y);
      }
  // ========================================================================

  }
}

#endif // defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS)
#endif // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INTERNAL_POSTYPE_H_
