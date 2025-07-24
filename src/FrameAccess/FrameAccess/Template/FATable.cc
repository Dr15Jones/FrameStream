#if !defined(FRAMEACCESS_FATABLE_CC)
#define FRAMEACCESS_FATABLE_CC
// -*- C++ -*-
//
// Package:     FrameAccess
// Module:      FATable
// 
// Description: <one line class summary>
//
// Implimentation:
//    // The FATable<T> is really just a access system to a table of
//    // pointers to objects.  To save high overhead on copying
//    // FATable<T> is implemented as a wrapped for the FAPtrTable<T>
//    // class.
//
// Author:      Simon Patton
// Created:     Tue Mar 18 13:23:19 EST 1997
// $Id: FATable.cc,v 1.6 1999/04/13 13:53:33 bkh Exp $
//
// Revision history
//
// $Log: FATable.cc,v $
// Revision 1.6  1999/04/13 13:53:33  bkh
// Make FATable<>::find() a const_iterator
//
// Revision 1.5  1998/09/16 21:36:32  mkl
// use new bug flag for static/extern linkage of kFacilityStrings in Template .cc files
//
// Revision 1.4  1998/05/07 21:27:43  mkl
// elevate FATable/Itr to stl container/iterator status
//
// Revision 1.3  1998/05/07 19:46:21  mkl
// check for null labels
//
// Revision 1.2  1998/04/09 23:19:41  cleo3
// port to egcs
//
// Revision 1.1  1997/12/05 03:04:21  mkl
// moved sources from DataHandler
//
// Revision 1.15  1997/09/10 14:14:55  sjp
// Changed FAItr to be FATableItr
//
// Revision 1.14  1997/09/01 15:35:45  sjp
// Changed report include to be in Experiment
//
// Revision 1.13  1997/08/28 06:23:39  sjp
// Updated the bug flag for forward declarations
//
// Revision 1.12  1997/08/27 03:41:39  sjp
// Updated to new name for bug flags
//
// Revision 1.11  1997/08/27 03:16:15  sjp
// Updated to new name for bug flag
//
// Revision 1.10  1997/07/09 18:00:25  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.9  1997/06/27 18:39:31  sjp
// Fixed an occurance of bug11_g++
//
// Revision 1.8  1997/06/03 17:10:34  sjp
// fixed copy constructor error
//
// Revision 1.7  1997/05/09 18:16:53  sjp
// Added operator[] function
//
// Revision 1.6  1997/04/20 18:37:43  sjp
// Renamed DD handling classes to FA classes
//
// Revision 1.5  1997/04/19 20:43:24  sjp
// activated begin and end functions
//
// Revision 1.4  1997/04/11 18:58:06  sjp
// Cleaned up message issuing
//
// Revision 1.3  1997/04/10 01:08:57  sjp
// Added c-preprocessor flags to stop multiple includes
//
// Revision 1.2  1997/03/29 16:28:32  sjp
// Added size function
//
// Revision 1.1  1997/03/19 22:21:24  sjp
// New definitions for class
//

#include "Experiment/Experiment.h"
// system include files

// user include files
#include "Experiment/report.h" // For error report
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FAPtrTable.h"

#include "FrameAccess/FATable.h"


// STL classes

//
// constants, enums and typedefs
//

static const char* const kFATableFacilityString 
= "FrameAccess.FATable" ;

//
// static data member definitions
//

//
// constructors and destructor
//

template < class T >
FATable< T >::FATable() :
   m_ptrTable( 0 )
{
}

template < class T >
FATable< T >::FATable( const FATable& aOther ) :
   m_ptrTable( aOther.m_ptrTable )
{
}

template < class T >
FATable< T >::FATable( const FAPtrTable< T >* pTable ) :
   m_ptrTable( pTable )
{
}

template < class T >
FATable< T >::~FATable()
{
}

//
// assignment operators
//
// const FATable& FATable::operator=( const FATable& )
// {
// }

template < class T >
const FATable< T >&
FATable< T >::operator=( const FATable< T >& aTable )
{
   setContents( aTable.m_ptrTable ) ;
   return ( *this ) ;
}

//
// member functions
//

template < class T >
void
FATable< T >::setContents( const FAPtrTable< T >* pTable )
{
   m_ptrTable = pTable ;
}

//
// const member functions
//

template < class T >
Count
FATable< T >::size() const
{
#if defined(CLEO_DEBUG)
   if ( !valid() ) {
      report( ERROR ,
	      kFATableFacilityString )
		 << "De-referencing invalid data"
		 << std::endl ;
      exit( 1 ) ;
   }
#endif
   return (*m_ptrTable).size() ;
}

template < class T >
DABoolean
FATable< T >::empty() const
{
   return( 0==size() ) ? true : false;
}

template < class T >
FATableItr<T>
FATable< T >::begin() const
{
   return ( (*m_ptrTable).begin() ) ;
}

template < class T >
FATableItr<T>
FATable< T >::end() const
{
   return ( (*m_ptrTable).end() ) ;
}

template < class T >
const T&
//FATableItr<T>::const_reference
FATable< T >::front() const
{
   return ( *(*m_ptrTable).begin() ) ;
}

template < class T >
const T&
//FATable<T>::const_reference
FATable< T >::back() const
{
   return ( *((*m_ptrTable).end()-1) ) ;
}

template < class T >
#if defined(TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG)
//----------------------------------------------------------------
// Note: g++ has a deficiecy in that is can only parse some arguments
//   that contain class::typedef constructs. This is a work around.
//
typename FATable< T >::const_iterator
FATable< T >::find_fixGnu() const 
{
//----------------------------------------------------------------
#else
typename FATable< T >::const_iterator
FATable< T >::find( const typename T::Identifier& aIdentifier ) const
{
#endif /* TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG */
#if defined(CLEO_DEBUG)
   if ( !valid() ) {
      report( ERROR ,
	      kFATableFacilityString )
		 << "De-referencing invalid data"
		 << std::endl ;
      exit( 1 ) ;
   }
#endif
#if !defined(TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG)
   return ( (*m_ptrTable).find( aIdentifier ) ) ;
}
#else
//----------------------------------------------------------------
// Note: g++ has a deficiecy in that is can only parse some arguments
//   that contain class::typedef constructs. This is a work around.
#if defined(FORWARD_DECLARATION_NOT_BOUND_TO_DEFINITION_BUG)
   typedef FAPtrTable< T > _tmp_ ;
#endif /* FORWARD_DECLARATION_NOT_BOUND_TO_DEFINITION_BUG */
   return ( (*m_ptrTable).find( m_fixGnuIdentifier ) ) ;
}
//----------------------------------------------------------------
#endif /* TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG */

#if !defined(TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG)
template < class T >
const T&
FATable< T >::operator[]( const typename T::Identifier& aIdentifier ) const
{
   return ( *find( aIdentifier ) ) ;
}
#endif /* TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG */

//
// static member functions
//

#endif /* FRAMEACCESS_FATABLE_CC */
