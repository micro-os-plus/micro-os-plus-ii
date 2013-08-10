//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Base for all named objects.

#ifndef OS_PORTABLE_CORE_NAMEDOBJECT_H_
#define OS_PORTABLE_CORE_NAMEDOBJECT_H_

namespace os
{
  namespace core
  {
    // ========================================================================

    constexpr char ANONYMOUS[] = "-";

    /// \headerfile NamedObject.h "portable/core/include/NamedObject.h"
    /// \ingroup core
    /// \nosubgrouping
    ///
    /// \brief Base for all classes that have a name.
    ///
    /// \details
    /// Provide common support for all objects that have a name,
    /// used mainly to identify the objects, for example during
    /// debugging sessions.
    class NamedObject
    {
    public:

      /// \name Constructors/destructor
      /// @{

      /// \brief Default constructor.
      ///
      /// \par Parameters
      ///    None.
      NamedObject(void);

      /// \brief Constructor.
      ///
      /// \param [in] pName Pointer to the null terminated name.
      NamedObject(const char* const pName);

      /// @} end of name Constructors/destructor

      /// \name Public member functions
      /// @{

      /// \brief Get the object name.
      ///
      /// \par Parameters
      ///    None.
      /// \return Pointer to the null terminated name.
      const char*
      getName(void) const;

      /// @} end of Public member functions

    private:
      /// \name Private member variables
      /// @{

      /// \brief Pointer to the null terminated name character array,
      /// filled in by the constructor.
      const char* const m_pName;

      /// @} end of Private member variables

    };

    // ------------------------------------------------------------------------

    /// \details
    /// Create an anonymous object. Provided for classes
    /// that require to be DefaultConstructible
    inline
    __attribute__((always_inline))
    NamedObject::NamedObject(void)
        : m_pName(ANONYMOUS)
    {
    }

    /// \details
    /// Store the pointer to the constant name
    /// in the private member variable.
    inline
    __attribute__((always_inline))
    NamedObject::NamedObject(const char* const pName)
        : m_pName(pName)
    {
    }

    /// \details
    /// Return the pointer to the constant name from the private
    /// member variable.
    inline
    const char*
    __attribute__((always_inline))
    NamedObject::getName(void) const
    {
      return m_pName;
    }

  // ==========================================================================

  }// namespace core
} // namespace os

#endif // OS_PORTABLE_CORE_NAMEDOBJECT_H_
