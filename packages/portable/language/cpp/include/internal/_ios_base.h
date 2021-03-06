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
/// \brief I/O stream base.

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INTERNAL_IOS_BASE_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INTERNAL_IOS_BASE_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS) || defined(__DOXYGEN__)

#include "portable/language/cpp/include/internal/__config.h"
#include "portable/language/cpp/include/internal/_locale.h"
#include "portable/language/cpp/include/cstddef.h"

namespace os
{
  namespace std
  {

    // 27.5.2 Types
    typedef ptrdiff_t streamsize;

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

    // 27.5.3 Class ios_base
    /// \class ios_base _ios_base.h "portable/language/cpp/include/internal/_ios_base.h"
    /// \ingroup std_io
    /// \nosubgrouping
    ///
    /// \brief  The base of the I/O class hierarchy.
    ///
    /// \details
    /// This class defines everything that can be defined about I/O that does
    /// not depend on the type of characters being input or output.  Most
    /// people will only see \c ios_base when they need to specify the full
    /// name of the various I/O flags (e.g., the \c openmodes).
    /// It maintains several kinds of data:
    /// - state information that reflects the integrity of the stream bu ffer;
    /// - control information that influences how to interpret (format) input
    /// sequences and how to generate (format) output sequences;
    /// - additional information that is stored by the program for its
    /// private use.
    ///
    /// \sa iosManipulators
    ///
    /// \example portable/language/cpp/tests/src/ios_base.cpp

    class ios_base
    {
    public:
      // actual definitions in _ios_base_failure.h
      class failure;

      // 27.5.3.1.2 fmtflags
      /// \name ios_base fmtflags definitions
      /// The format flags type and definitions.
      /// @{

      /// \brief The format flags (a bitmask type).
      ///
      /// \details
      /// The definition of `fmtflags` is implementation-defined,
      /// but it is valid to
      /// perform bitwise operations on these values and expect the Right
      /// Thing to happen.  Defined objects of type fmtflags are:
      /// - boolalpha
      /// - dec
      /// - fixed
      /// - hex
      /// - internal
      /// - left
      /// - oct
      /// - right
      /// - scientific
      /// - showbase
      /// - showpoint
      /// - showpos
      /// - skipws
      /// - unitbuf
      /// - uppercase
      /// - adjustfield
      /// - basefield
      /// - floatfield
      typedef unsigned int fmtflags;

      /// \brief
      /// Insert and extract bool type in alphabetic format.
      static const fmtflags boolalpha = 0x0001;
      /// \brief
      /// Convert integer input or generate integer output in decimal base.
      static const fmtflags dec = 0x0002;
      /// \brief
      /// Generate floating-point output in fixed-point notation.
      static const fmtflags fixed = 0x0004;
      /// \brief
      /// Convert integer input or generate integer output in hexadecimal base.
      static const fmtflags hex = 0x0008;
      /// \brief
      /// Add fill characters at a designated internal point in certain
      /// generated output, or identical to \c right if no such point is
      /// designated.
      static const fmtflags internal = 0x0010;
      /// \brief
      /// Add fill characters on the right (final positions) of certain
      /// generated output.  (I.e., the thing you print is justified left.)
      static const fmtflags left = 0x0020;
      /// \brief
      /// Convert integer input or generate integer output in octal base.
      static const fmtflags oct = 0x0040;
      /// \brief
      /// Add fill characters on the left (initial positions) of certain
      /// generated output.  (I.e., the thing you print is justified right.)
      static const fmtflags right = 0x0080;
      /// \brief
      /// Generate floating-point output in scientific notation.
      static const fmtflags scientific = 0x0100;
      /// \brief
      /// Generate a prefix indicating the numeric base of generated integer
      /// output (hex or oct).
      static const fmtflags showbase = 0x0200;
      /// \brief
      /// Generate a decimal-point character unconditionally in generated
      /// floating-point output.
      static const fmtflags showpoint = 0x0400;
      /// \brief
      /// Generate a + sign in non-negative generated numeric output.
      static const fmtflags showpos = 0x0800;
      /// \brief
      /// Skip leading white space before certain input operations.
      static const fmtflags skipws = 0x1000;
      /// \brief
      /// Flush output after each output operation.
      static const fmtflags unitbuf = 0x2000;
      /// \brief
      /// Replace certain lowercase letters with their uppercase equivalents
      /// in generated output (for example hex digits).
      static const fmtflags uppercase = 0x4000;

      // As per Table 123 — fmtflags constants
      /// \brief
      /// A mask of left|right|internal.  Useful for the 2-arg form of `setf()`.
      static const fmtflags adjustfield = left | right | internal;
      /// \brief
      /// A mask of dec|oct|hex.  Useful for the 2-arg form of `setf()`.
      static const fmtflags basefield = dec | oct | hex;
      /// \brief
      /// A mask of scientific|fixed.  Useful for the 2-arg form of `setf()`.
      static const fmtflags floatfield = scientific | fixed;

      /// @}

      // 27.5.3.1.3 iostate
      /// \name ios_base iostate definitions
      /// The I/O state flags type and definitions.
      /// @{

      /// \brief The I/O state flags (a bitmask type).
      ///
      /// \details
      /// The definition of `iostate` is implementation-defined,
      /// but it is valid to
      /// perform bitwise operations on these values and expect the Right
      /// Thing to happen.  Defined objects of type `iostate` are:
      /// - badbit
      /// - eofbit
      /// - failbit
      /// - goodbit
      typedef unsigned int iostate;

      /// \brief
      /// Indicate a loss of integrity in an input or output sequence (such
      /// as an irrecoverable read error from a file).
      static const iostate badbit = 0x1;
      /// \brief
      /// Indicate that an input operation reached the end of an input sequence.
      static const iostate eofbit = 0x2;
      /// \brief
      /// Indicate that an input operation failed to read the expected
      /// characters, or that an output operation failed to generate the
      /// desired characters.
      static const iostate failbit = 0x4;
      /// \brief
      /// Indicate that all is well.
      static const iostate goodbit = 0x0;

      /// @}

      // 27.5.3.1.4 openmode
      /// \name ios_base openmode definitions
      /// The open mode flags type and definitions.
      /// @{

      /// \brief The open mode flags (a bitmask type).
      ///
      /// \details
      /// The definition of \c openmode is implementation-defined,
      /// but it is valid to
      /// perform bitwise operations on these values and expect the Right
      /// Thing to happen.  Defined objects of type \c openmode are:
      /// - app
      /// - ate
      /// - binary
      /// - in
      /// - out
      /// - trunc
      typedef unsigned int openmode;

      /// \brief
      /// Seek to end before each write (append).
      static const openmode app = 0x01;
      /// \brief
      /// Open and seek to end immediately after opening.
      static const openmode ate = 0x02;
      /// \brief
      /// Perform input and output in binary mode (as opposed to text mode).
      static const openmode binary = 0x04;
      /// \brief
      /// Open for input.  Default for \c ifstream and \c fstream.
      static const openmode in = 0x08;
      /// \brief
      /// Open for output.  Default for \c ofstream and \c fstream.
      static const openmode out = 0x10;
      /// \brief
      /// Open for input.  Default for \c ofstream.
      static const openmode trunc = 0x20;

      /// @}

      // 27.5.3.1.5 seekdir

      /// \name ios_base seekdir definitions
      /// The seek direction flags type and definitions.
      /// @{

      /// \brief The seek direction flags (an enumerated type).
      ///
      /// \details
      /// The definition of `seekdir` is implementation-defined.
      /// Defined values of type `seekdir` are:
      /// - beg, relative to beginning
      /// - cur, relative to current, equivalent to `SEEK_CUR` in the C standard library.
      /// - end, relative to end, equivalent to `SEEK_END` in the C standard library.
      enum seekdir
      {
        /// Request a seek relative to the beginning of the stream.
        beg,
        /// Request a seek relative to the current position within the sequence.
        cur,
        /// Request a seek relative to the current end of the sequence.
        end
      };

      /// @}

      class Init;

      // 27.5.3.2 fmtflags state:
      /// \name ios_base state member functions
      /// @{

      /// \brief  Get the format flags.
      ///
      /// \par Parameters
      /// None.
      /// \return  The format control flags for both input and output.
      fmtflags
      flags() const;

      /// \brief  Set the new format flags all at once.
      ///
      /// \param [in] fmtfl  The new flags to set.
      /// \return  The previous format control flags.
      fmtflags
      flags(fmtflags fmtfl);

      /// \brief  Set new format flags.
      ///
      /// \param [in]  fmtfl  Additional flags to set.
      /// \return  The previous format control flags.
      fmtflags
      setf(fmtflags fmtfl);

      /// \brief  Set the selected format flags.
      ///
      /// \param [in]  fmtfl  Additional flags to set.
      /// \param [in]  mask  The flags mask for \c fmtfl.
      /// \return  The previous format control flags.
      fmtflags
      setf(fmtflags fmtfl, fmtflags mask);

      /// \brief  Clear the selected format flags.
      ///
      /// \param [in]  mask  The flags to unset.
      void
      unsetf(fmtflags mask);

      /// \brief Get precision.
      ///
      /// \par Parameters
      /// None.
      /// \return  The precision to generate on certain output operations.
      streamsize
      precision() const;

      /// \brief  Set the precision.
      ///
      /// \param [in]  prec  The new precision value.
      /// \return  The previous value of precision().
      streamsize
      precision(streamsize prec);

      /// \brief  Get field width.
      ///
      /// \par Parameters
      /// None.
      /// \return  The minimum field width (number of characters) to
      /// generate on certain output conversions.
      streamsize
      width() const;

      /// \brief  Set the field width.
      ///
      /// \param [in]  wide  The new width value.
      /// \return  The previous value of width().
      streamsize
      width(streamsize wide);

      /// @}

      // 27.5.3.3 locales:
      /// \name ios_base locale member functions
      /// @{

      /// \brief  Set a new locale.
      ///
      /// \param [in]  newloc  The new locale.
      /// \return  The previous locale.
      locale
      imbue(const locale& newloc);

      /// \brief  Get locale.
      ///
      /// \par Parameters
      /// None.
      /// \return  A copy of the current locale.
      locale
      getloc() const;

      /// @}

#if defined(OS_INCLUDE_STD_IOS_BASE_STORAGE)
      // 27.5.3.5 storage:
      /// \name ios_base storage member functions
      /// @{

      /// \brief  Access to unique indices.
      ///
      /// \return  An integer different from all previous calls.
      static int xalloc();

      /// \brief  Access to integer array.
      ///
      /// \param  idx  Index into the array.
      /// \return  A reference to an integer associated with the index.
      long& iword(int idx);

      /// \brief  Access to void pointer array.
      ///
      /// \param  idx  Index into the array.
      /// \return  A reference to a void* associated with the index.
      void*& pword(int idx);

      /// @}

#endif

      // \name ios_base constructors/destructor (27.5.3.7)
      /// \name Constructors/destructor
      /// @{

      /// \brief Destructor
      virtual
      ~ios_base();

      /// @}

#if defined(OS_INCLUDE_STD_IOS_BASE_CALLBACKS)
      // 27.5.3.6 callbacks;

      /// \brief  The set of events that may be passed to an event callback.
      enum event
        {
          /// event used during \c ~ios() and \c copyfmt()
          erase_event,
          /// event used during \c imbue()
          imbue_event,
          /// event used during \c copyfmt()
          copyfmt_event
        };

      /// \brief  The type of an event callback function.
      ///
      /// \param [in]  event  One of the members of the event enum.
      /// \param [in]  iob  Reference to the ios_base object.
      /// \param [in]  index  The integer provided when the callback was registered.
      /// \return Nothing
      ///
      /// \details
      /// Event callbacks are user defined functions that get called during
      /// several \c ios_base and \c basic_ios functions, specifically \c imbue(),
      /// \c copyfmt(), and \c ~ios().
      typedef void
      (*event_callback)(event, ios_base& iob, int index);

      /// \brief  Add the callback \c fn with parameter index.
      ///
      /// \param [in]  fn  The function to add.
      /// \param [in]  index  The integer to pass to the function when invoked.
      void
      register_callback(event_callback fn, int index);
#endif

    private:

      // \name ios_base constructors/destructor (27.5.3.7)
      /// \name Constructors/destructor
      /// @{

      /// \brief No copy constructor.
      ios_base(const ios_base&) = delete;

      /// @}

      /// \name Assign/swap/move member functions
      /// @{

      /// \brief No assignment operator.
      ios_base&
      operator=(const ios_base&) = delete;

      /// @}

    public:

      /// \name Static member functions
      /// @{

      /// \brief  Interaction with the standard C I/O objects.
      ///
      /// \param [in] sync      Whether to synchronise or not.
      /// \retval  true         The standard streams were previously synchronised.
      /// \retval  false        Otherwise.
      static bool
      sync_with_stdio(bool sync = true);

      /// @}

    protected:

      // \name ios_base constructors/destructor (27.5.3.7)
      /// \name Constructors/destructor
      /// @{

      /// \brief Default constructor.
      ios_base();

      /// @}

      /// \name Assign/swap/move member functions
      /// @{

      /// \brief  Copy fields of rhs into this.
      ///
      /// \param [in] rhs  The source values for the copies.
      /// \par Returns
      /// Nothing.
      void
      copyfmt(const ios_base& rhs);

      /// \brief  Move all members.
      ///
      /// \param [in] rhs A reference to the right hand side ios_base.
      /// \par Returns
      /// Nothing.
      void
      move(ios_base& rhs);

      /// \brief  Swap all members.
      ///
      /// \param [in,out] rhs A reference to the right hand side ios_base.
      /// \par Returns
      /// Nothing.
      void
      swap(ios_base& rhs) _NOEXCEPT;

      // implementation specifics

#if defined(OS_INCLUDE_STD_IOS_BASE_CALLBACKS)
      /// \brief Internal callback processing.
      void
      __call_callbacks(event);
#endif

      /// \brief Internal initialisation.
      ///
      /// \par Parameters
      /// None.
      /// \par Returns
      /// Nothing.
      void
      __init();

      // end of implementation specifics

      /// @}

    private:

      // All data members must be scalars

      /// \name Private members
      /// @{

      /// \brief Format flags.
      fmtflags m_fmtflags;

      /// \brief Float precision.
      streamsize m_precision;

      /// \brief Field width.
      streamsize m_width;

      /// \brief Pointer to locales.
      void* m_locale;

#if defined(OS_INCLUDE_STD_IOS_BASE_CALLBACKS)
      event_callback* __fn_;
      int* __index_;
      size_t __event_size_;
      size_t __event_cap_;
#endif
#if defined(OS_INCLUDE_STD_IOS_BASE_STORAGE)
      long* __iarray_;
      size_t __iarray_size_;
      size_t __iarray_cap_;
      void** __parray_;
      size_t __parray_size_;
      size_t __parray_cap_;
#endif

#if defined(OS_INCLUDE_STD_IOS_BASE_STORAGE)
      static int ms_xindex;
#endif

      /// @}

    };

#pragma GCC diagnostic pop

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
    // ------------------------------------------------------------------------
    // 27.5.3.1.6 Class ios_base::Init

    /// \brief Initialisation instances counter.
    ///
    /// \details
    /// The class Init describes an object whose construction ensures the
    /// construction of the eight objects declared in <iostream> (27.4)
    /// that associate file stream bu ers with the standard C streams
    /// provided for by the functions declared in <cstdio> (27.9.2).
    ///
    /// For the sake of exposition, the maintained data is presented here as:
    /// — <code>static int init_cnt</code>, counts the number of constructor
    /// and destructor calls for class Init, initialized
    /// to zero.
    class ios_base::Init
      {
      public:
        Init();
        ~Init();

      private:
        static int init_cnt; // exposition only
      };
#endif

    // ------------------------------------------------------------------------
    // fmtflags

    inline ios_base::fmtflags
    __attribute__((always_inline))
    ios_base::flags() const
    {
      return m_fmtflags;
    }

    /// \details
    /// This function overwrites all the format flags with \c fmtfl.
    inline ios_base::fmtflags
    __attribute__((always_inline))
    ios_base::flags(fmtflags fmtfl)
    {
      fmtflags __r = m_fmtflags;
      m_fmtflags = fmtfl;
      return __r;
    }

    /// \details
    /// This function sets additional flags in format control.  Flags that
    /// were previously set remain set.
    inline ios_base::fmtflags
    __attribute__((always_inline))
    ios_base::setf(fmtflags fmtfl)
    {
      fmtflags __r = m_fmtflags;
      m_fmtflags |= fmtfl;
      return __r;
    }

    /// \details
    /// This function clears `mask` bits in the format flags.
    inline void
    __attribute__((always_inline))
    ios_base::unsetf(fmtflags mask)
    {
      m_fmtflags &= ~mask;
    }

    /// \details
    /// This function clears `mask` bits in the format flags, then sets
    /// `fmtfl & mask`.  An example mask is `ios_base::adjustfield`.
    inline ios_base::fmtflags
    __attribute__((always_inline))
    ios_base::setf(fmtflags fmtfl, fmtflags mask)
    {
      fmtflags __r = m_fmtflags;
      unsetf(mask);
      m_fmtflags |= fmtfl & mask;
      return __r;
    }

    // precision

    inline streamsize
    __attribute__((always_inline))
    ios_base::precision() const
    {
      return m_precision;
    }

    inline streamsize
    __attribute__((always_inline))
    ios_base::precision(streamsize prec)
    {
      streamsize __r = m_precision;
      m_precision = prec;
      return __r;
    }

    // width

    /// \details
    /// <em>Minimum field width</em> refers to the number of characters.
    inline streamsize
    __attribute__((always_inline))
    ios_base::width() const
    {
      return m_width;
    }

    inline streamsize
    __attribute__((always_inline))
    ios_base::width(streamsize wide)
    {
      streamsize __r = m_width;
      m_width = wide;
      return __r;
    }

    /// \details
    /// Each ios_base member has an indeterminate value after construction.
    /// The object’s members shall be initialized by calling
    /// `basic_ios::init()` before the object’s first use or before
    /// it is destroyed, whichever comes first; otherwise the
    /// behavior is undefined.
    inline
    __attribute__((always_inline))
    ios_base::ios_base()
    {
    }

    /// \details
    /// It is required in order to keep members private.
    inline void
    __attribute__((always_inline))
    ios_base::__init()
    {
      m_fmtflags = skipws | dec;
      m_width = 0;
      m_precision = 6;

#if defined(OS_INCLUDE_STD_IOS_BASE_CALLBACKS)
      __fn_ = 0;
      __index_ = 0;
      __event_size_ = 0;
      __event_cap_ = 0;
#endif
#if defined(OS_INCLUDE_STD_IOS_BASE_STORAGE)
      __iarray_ = 0;
      __iarray_size_ = 0;
      __iarray_cap_ = 0;
      __parray_ = 0;
      __parray_size_ = 0;
      __parray_cap_ = 0;
#endif

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      ::new (&m_locale) locale;
#endif
    }

    // ========================================================================

    // Add a Doxygen page below Modules.

    /// \addtogroup iosManipulators
    /// @{
    /// \brief `fmtflags`, `adjustfield`, `basefield` and `floatfield` manipulators.
    /// \details
    /// These functions set/clear various flags in the `ios_base` class.

    // 27.5.6 ios_base manipulators

    // 27.5.6.1 fmtflags manipulators
    /// \name fmtflags manipulators (27.5.6.1)
    /// @{

    /// \brief Call base.setf(ios_base::boolalpha).
    inline ios_base&
    __attribute__((always_inline))
    boolalpha(ios_base& str)
    {
      str.setf(ios_base::boolalpha);
      return str;
    }

    /// \brief Call base.unsetf(ios_base::boolalpha).
    inline ios_base&
    __attribute__((always_inline))
    noboolalpha(ios_base& str)
    {
      str.unsetf(ios_base::boolalpha);
      return str;
    }

    /// \brief Call base.setf(ios_base::showbase).
    inline ios_base&
    __attribute__((always_inline))
    showbase(ios_base& str)
    {
      str.setf(ios_base::showbase);
      return str;
    }

    /// \brief Call base.unsetf(ios_base::showbase).
    inline ios_base&
    __attribute__((always_inline))
    noshowbase(ios_base& str)
    {
      str.unsetf(ios_base::showbase);
      return str;
    }

    /// \brief Call base.setf(ios_base::showpoint).
    inline ios_base&
    __attribute__((always_inline))
    showpoint(ios_base& str)
    {
      str.setf(ios_base::showpoint);
      return str;
    }

    /// \brief Call base.unsetf(ios_base::showpoint).
    inline ios_base&
    __attribute__((always_inline))
    noshowpoint(ios_base& str)
    {
      str.unsetf(ios_base::showpoint);
      return str;
    }

    /// \brief Call base.setf(ios_base::showpos).
    inline ios_base&
    __attribute__((always_inline))
    showpos(ios_base& str)
    {
      str.setf(ios_base::showpos);
      return str;
    }

    /// \brief Call base.unsetf(ios_base::showpos).
    inline ios_base&
    __attribute__((always_inline))
    noshowpos(ios_base& str)
    {
      str.unsetf(ios_base::showpos);
      return str;
    }

    /// \brief Call base.setf(ios_base::skipws).
    inline ios_base&
    __attribute__((always_inline))
    skipws(ios_base& str)
    {
      str.setf(ios_base::skipws);
      return str;
    }

    /// \brief Call base.unsetf(ios_base::skipws).
    inline ios_base&
    __attribute__((always_inline))
    noskipws(ios_base& str)
    {
      str.unsetf(ios_base::skipws);
      return str;
    }

    /// \brief Call base.setf(ios_base::uppercase).
    inline ios_base&
    __attribute__((always_inline))
    uppercase(ios_base& str)
    {
      str.setf(ios_base::uppercase);
      return str;
    }

    /// \brief Call base.unsetf(ios_base::uppercase).
    inline ios_base&
    __attribute__((always_inline))
    nouppercase(ios_base& str)
    {
      str.unsetf(ios_base::uppercase);
      return str;
    }

    /// \brief Call base.setf(ios_base::unitbuf).
    inline ios_base&
    __attribute__((always_inline))
    unitbuf(ios_base& str)
    {
      str.setf(ios_base::unitbuf);
      return str;
    }

    /// \brief Call base.unsetf(ios_base::unitbuf).
    inline ios_base&
    __attribute__((always_inline))
    nounitbuf(ios_base& str)
    {
      str.unsetf(ios_base::unitbuf);
      return str;
    }

    /// @}

    // 27.5.6.2 adjustfield manipulators
    /// \name adjustfield manipulators (27.5.6.2)
    /// @{

    /// \brief Call base.setf(ios_base::internal, ios_base::adjustfield).
    inline ios_base&
    __attribute__((always_inline))
    internal(ios_base& str)
    {
      str.setf(ios_base::internal, ios_base::adjustfield);
      return str;
    }

    /// \brief Call base.setf(ios_base::left, ios_base::adjustfield).
    inline ios_base&
    __attribute__((always_inline))
    left(ios_base& str)
    {
      str.setf(ios_base::left, ios_base::adjustfield);
      return str;
    }

    /// \brief Call base.setf(ios_base::right, ios_base::adjustfield).
    inline ios_base&
    __attribute__((always_inline))
    right(ios_base& str)
    {
      str.setf(ios_base::right, ios_base::adjustfield);
      return str;
    }

    /// @}

    // 27.5.6.3 basefield manipulators
    /// \name basefield manipulators (27.5.6.3)
    /// @{

    /// \brief Call base.setf(ios_base::dec, ios_base::basefield).
    inline ios_base&
    __attribute__((always_inline))
    dec(ios_base& str)
    {
      str.setf(ios_base::dec, ios_base::basefield);
      return str;
    }

    /// \brief Call base.setf(ios_base::hex, ios_base::basefield).
    inline ios_base&
    __attribute__((always_inline))
    hex(ios_base& str)
    {
      str.setf(ios_base::hex, ios_base::basefield);
      return str;
    }

    /// \brief Call base.setf(ios_base::oct, ios_base::basefield).
    inline ios_base&
    __attribute__((always_inline))
    oct(ios_base& str)
    {
      str.setf(ios_base::oct, ios_base::basefield);
      return str;
    }

    /// @}

    // 27.5.6.4 floatfield manipulators
    /// \name floatfield manipulators (27.5.6.4)
    /// @{

    /// \brief Call base.setf(ios_base::fixed, ios_base::floatfield).
    inline ios_base&
    __attribute__((always_inline))
    fixed(ios_base& str)
    {
      str.setf(ios_base::fixed, ios_base::floatfield);
      return str;
    }

    /// \brief Call base.setf(ios_base::scientific, ios_base::floatfield).
    inline ios_base&
    __attribute__((always_inline))
    scientific(ios_base& str)
    {
      str.setf(ios_base::scientific, ios_base::floatfield);
      return str;
    }

    /// \brief Call base.setf(ios_base::fixed | ios_base::scientific, ios_base::floatfield).
    inline ios_base&
    __attribute__((always_inline))
    hexfloat(ios_base& str)
    {
      str.setf(ios_base::fixed | ios_base::scientific, ios_base::floatfield);
      return str;
    }

    /// \brief Call base.unsetf(ios_base::floatfield).
    inline ios_base&
    __attribute__((always_inline))
    defaultfloat(ios_base& str)
    {
      str.unsetf(ios_base::floatfield);
      return str;
    }

  /// @}

  /// @}

  // ------------------------------------------------------------------------

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

  // 27.5.6.5 Error reporting
  inline error_code
  __attribute__((always_inline))
  make_error_code(io_errc e)
    {
      return error_code(static_cast<int>(e), iostream_category());
    }

  inline error_condition
  __attribute__((always_inline))
  make_error_condition(io_errc e)
    {
      return error_condition(static_cast<int>(e), iostream_category());
    }

#endif

}
    // namespace std
}   // namespace os

#endif // defined( INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS)
#endif  /* OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INTERNAL_IOS_BASE_H_ */
