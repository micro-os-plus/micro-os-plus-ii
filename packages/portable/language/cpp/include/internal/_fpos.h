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
/// \brief File position.

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INTERNAL_FPOS_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INTERNAL_FPOS_H_

#include "portable/core/include/ConfigDefines.h"

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
    /// @tparam  TState_T  Type passed to and returned from `state()`.
    ///
    /// The standard places no requirements upon the template
    /// parameter `TState_T`.
    /// In this implementation `TState_T` must be DefaultConstructible,
    /// CopyConstructible and Assignable.  The standard only requires
    /// that `fpos`
    /// should contain a member of type `TState_T`. In this
    /// implementation it also
    /// contains an offset stored as a signed integer.
    ///
    /// \example portable/language/cpp/tests/src/fpos.cpp

    template<class TState_T>
      class fpos
      {
      public:
        fpos(streamoff off = streamoff());

        // 27.5.4.1 Members
        TState_T
        state() const;

        /// \brief Remember the value of `st`.
        ///
        /// \param st State.
        /// \par Returns
        /// Nothing.
        void
        state(TState_T st);

        // 27.5.4.2 fpos requirements
        /// \brief Convert to streamoff.
        operator streamoff() const;

        /// \brief Add offset to this position.
        ///
        /// \param off Offset.
        fpos&
        operator+=(streamoff off);

        /// \brief Add position and offset.
        ///
        /// \param off Offset.
        fpos
        operator+(streamoff off) const;

        /// \brief Subtract offset from this position.
        ///
        /// \param off Offset.
        fpos&
        operator-=(streamoff off);

        /// \brief Subtract offset from position.
        ///
        /// \param off Offset.
        fpos
        operator-(streamoff off) const;

      private:
        /// \brief Member to store offset.
        streamoff m_off;
        /// \brief Member to store state.
        TState_T m_st;

      };
#pragma GCC diagnostic pop

    // ------------------------------------------------------------------------
    // inline members

    template<class TState_T>
      inline
      __attribute__((always_inline))
      fpos<TState_T>::fpos(streamoff off)
          : m_off(off), m_st()
      {
      }

    template<class TState_T>
      inline
      __attribute__((always_inline))
      fpos<TState_T>::operator streamoff() const
      {
        return m_off;
      }

    template<class TState_T>
      inline TState_T
      __attribute__((always_inline))
      fpos<TState_T>::state() const
      {
        return m_st;
      }

    template<class TState_T>
      inline void
      __attribute__((always_inline))
      fpos<TState_T>::state(TState_T st)
      {
        m_st = st;
      }

    template<class TState_T>
      inline fpos<TState_T>&
      __attribute__((always_inline))
      fpos<TState_T>::operator+=(streamoff off)
      {
        m_off += off;
        return *this;
      }

    template<class TState_T>
      inline fpos<TState_T>
      __attribute__((always_inline))
      fpos<TState_T>::operator+(streamoff off) const
      {
        fpos tpos(*this);
        tpos += off;
        return tpos;
      }

    template<class TState_T>
      inline fpos<TState_T>&
      __attribute__((always_inline))
      fpos<TState_T>::operator-=(streamoff off)
      {
        m_off -= off;
        return *this;
      }

    template<class TState_T>
      inline fpos<TState_T>
      __attribute__((always_inline))
      fpos<TState_T>::operator-(streamoff off) const
      {
        fpos tpos(*this);
        tpos -= off;
        return tpos;
      }

    // ========================================================================
    // Subtract two fpos<> and return a streamoff
    template<class TState_T>
      inline streamoff
      __attribute__((always_inline))
      operator-(const fpos<TState_T>& x, const fpos<TState_T>& y)
      {
        return streamoff(x) - streamoff(y);
      }

    // Compare two fpos<> for equality
    template<class TState_T>
      inline bool
      __attribute__((always_inline))
      operator==(const fpos<TState_T>& x, const fpos<TState_T>& y)
      {
        return streamoff(x) == streamoff(y);
      }

    // Compare two fpos<> for non equality
    template<class TState_T>
      inline bool
      __attribute__((always_inline))
      operator!=(const fpos<TState_T>& x, const fpos<TState_T>& y)
      {
        return streamoff(x) != streamoff(y);
      }
  // ========================================================================

  }// namespace std
} // namespace os

#endif // defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS)
#endif // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INTERNAL_FPOS_H_
