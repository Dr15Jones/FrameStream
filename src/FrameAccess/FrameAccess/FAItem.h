#if !defined(FRAMEACCESS_FAITEM_H)
#define FRAMEACCESS_FAITEM_H
// -*- C++ -*-
//
// Package:     FrameAccess
// Module:      FAItem
// 
/**\class FAItem FAItem.h FrameAccess/FAItem.h

 Description: Smart pointer to data object

 Usage:
     A FAItem is a smart pointer to a CLEO data object.  It is used
     either to return data from an extract call or to access data in a
     CLEO Proxy.  Only extract needs to know how to use a FAItem
     with respect to Proxies.

     To access the data pointed to by a FAItem the user de-references
     it.

     \code
     FAItem<GeV> energy ;
     extract( record , energy ) ;
     report( INFO ) << "The energy is " << *energy ;
     \endcode

     For those unfamilar with de-referencing, this simply means
     adding a `*' before the identifier to indicate that you require
     the contents of the object.

     If the data requested does not exist then an exception is thrown
     and the program exits.  If the user wishes to avoid this
     behaviour then they need to check the state of the data, by
     catching the exception.

     \code
     ...
     #include "DAException/DANoDataException.h"
     ...
     FAItem<GeV> energy ;
     try {
        extract( record , energy ) ;
        report( INFO ) << "The energy is " << *energy ;
     } catch( NO_ITEM_EXCEPTION(GeV)& iException ) {
       //print a nice diagnostic message
       report(WARNING ) << iException.what() << std::endl;
     }
     
     //want to know if the extract call worked
     if( energy.valid() ) {
        ...
     }
     \endcode

     The user need only check the validity of the data if they 
     caught the exception and then later want to make sure the extract
     call succeeded.

     See DAExceptionBase for other exceptions that can be thrown.
*/
//
// Author:      Simon Patton
// Created:     Mon Mar 17 14:42:40 EST 1997
// $Id: FAItem.h,v 1.6 1999/12/10 14:17:47 cdj Exp $
//
// Revision history
//
// $Log: FAItem.h,v $
// Revision 1.6  1999/12/10 14:17:47  cdj
// added exception macro and inlined commonly used functions
//
// Revision 1.5  1999/11/07 02:19:04  cdj
// fixed outdated documentation
//
// Revision 1.4  1999/10/31 15:39:23  cdj
// doxygenated the comments
//
// Revision 1.3  1998/07/29 02:28:07  mkl
// new bug flag for bad deref ops for built-in types
//
// Revision 1.2  1998/07/18 19:46:56  mkl
// solaris comp. doesnt allow -> op for built-in types --> new bug flag
//
// Revision 1.1  1997/12/05 03:03:59  mkl
// moved sources from DataHandler
//
// Revision 1.11  1997/09/18 21:10:24  cdj
// changed Boolean to DABoolean
//
// Revision 1.10  1997/08/06 15:27:32  sjp
// Updated documentation to deal with Proxies
//
// Revision 1.9  1997/08/06 14:57:39  sjp
// Added new typedef used by Extractor
//
// Revision 1.8  1997/07/11 16:44:41  sjp
// Added INCLUDE_TEMPLATE_DEFINITIONS flag
//
// Revision 1.7  1997/07/09 17:59:35  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.6  1997/05/09 18:15:37  sjp
// Changed function name setPointer to setContents
//
// Revision 1.5  1997/04/20 18:37:29  sjp
// Renamed DD handling classes to FA classes
//
// Revision 1.4  1997/04/19 20:42:42  sjp
// Fixed return type for ->
//
// Revision 1.3  1997/04/10 01:06:40  sjp
// Added value_type typedef for new DataField system
//
// Revision 1.2  1997/04/04 16:44:35  sjp
// Made const functions actually const
//
// Revision 1.1  1997/03/19 22:18:12  sjp
// New header file for class
//

#define NO_ITEM_EXCEPTION(_type_) DANoDataException<FAItem<_type_>::contents>

// system include files

// user include files


// forward declarations

template < class T >
class FAItem
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      typedef T value_type ;
      typedef T contents ;

      // Constructors and destructor
      FAItem() ;
      FAItem( const FAItem< T >& aOtherPtr ) ;
      FAItem( const T* aPointer ) ;
      virtual ~FAItem() ;

      // assignment operator(s)
      const FAItem& operator=( const FAItem< T >& aPtr ) ;

      // member functions
      void setContents( const T* aPointer ) { m_pointer = aPointer; }

      // const member functions
      DABoolean valid() const ;
      DABoolean operator==( const FAItem< T >& aOtherPtr ) const ;
      const T& operator*() const { return ( *m_pointer ); }

#if !defined(DEREF_OP_FOR_BUILTIN_TYPES_BUG)
      const T* operator->() const { return m_pointer; }
#endif

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor

      // private member functions

      // private const member functions

      // data members
      const T* m_pointer ;

      // static data members

};

// inline function definitions

template < class T >
inline DABoolean
FAItem< T >::valid() const
{
   return ( 0 != m_pointer ) ;
}

#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// function definitions
# include "FrameAccess/Template/FAItem.cc"
#endif

#endif /* FRAMEACCESS_FAITEM_H */
