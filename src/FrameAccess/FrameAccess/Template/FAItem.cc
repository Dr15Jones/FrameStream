#if !defined(FRAMEACCESS_FAITEM_CC)
#define FRAMEACCESS_FAITEM_CC
// -*- C++ -*-
//
// Package:     FrameAccess
// Module:      FAItem
// 
// Description: Smart pointer to data object
//
// Implimentation:
//     Currently this is just a placehold of a memoery pointer.
//
// Author:      Simon Patton
// Created:     Tue Mar 18 13:23:11 EST 1997
// $Id: FAItem.cc,v 1.5 1999/12/10 14:18:08 cdj Exp $
//
// Revision history
//
// $Log: FAItem.cc,v $
// Revision 1.5  1999/12/10 14:18:08  cdj
// inlined commonly used functions
//
// Revision 1.4  1998/09/16 21:36:31  mkl
// use new bug flag for static/extern linkage of kFacilityStrings in Template .cc files
//
// Revision 1.3  1998/07/29 02:28:08  mkl
// new bug flag for bad deref ops for built-in types
//
// Revision 1.2  1998/07/18 19:47:08  mkl
// solaris comp. doesnt allow -> op for built-in types --> new bug flag
//
// Revision 1.1  1997/12/05 03:04:18  mkl
// moved sources from DataHandler
//
// Revision 1.10  1997/09/18 21:10:39  cdj
// changed Boolean to DABoolean
//
// Revision 1.9  1997/09/01 15:35:44  sjp
// Changed report include to be in Experiment
//
// Revision 1.8  1997/07/09 18:00:21  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.7  1997/05/09 18:15:42  sjp
// Changed function name setPointer to setContents
//
// Revision 1.6  1997/04/20 18:37:40  sjp
// Renamed DD handling classes to FA classes
//
// Revision 1.5  1997/04/19 20:42:43  sjp
// Fixed return type for ->
//
// Revision 1.4  1997/04/11 18:58:04  sjp
// Cleaned up message issuing
//
// Revision 1.3  1997/04/10 01:08:56  sjp
// Added c-preprocessor flags to stop multiple includes
//
// Revision 1.2  1997/04/04 16:59:19  sjp
// Made const functions actually const
//
// Revision 1.1  1997/03/19 22:21:22  sjp
// New definitions for class
//

#include "Experiment/Experiment.h"
// system include files
#include <stdlib.h>  // For 'exit'

// user include files
#include "Experiment/report.h" // For error report
#include "FrameAccess/FAItem.h"


// STL classes

//
// constants, enums and typedefs
//

static const char* const kFAItemFacilityString 
= "FrameAccess.FAItem" ;

//
// static data member definitions
//

//
// constructors and destructor
//

template < class T >
FAItem< T >::FAItem() :
   m_pointer( 0 )
{
}

template < class T >
FAItem< T >::FAItem( const FAItem& aOtherPtr ) :
   m_pointer( aOtherPtr.m_pointer )
{
}

template < class T >
FAItem< T >::FAItem( const T* aPointer ) :
   m_pointer( aPointer )
{
}

template < class T >
FAItem< T >::~FAItem()
{
}

//
// assignment operators
//

template < class T >
const FAItem< T >&
FAItem< T >::operator=( const FAItem< T >& aOtherPtr )
{
   setContents( aOtherPtr.m_pointer ) ;
   return( *this ) ;
}

//
// member functions
//

//
// const member functions
//

template < class T >
DABoolean
FAItem< T >::operator==( const FAItem< T >& aOtherPtr ) const
{
   return ( m_pointer == aOtherPtr.m_pointer ) ;
}

//
// static member functions
//

#endif /* FRAMEACCESS_FAITEM_CC */
