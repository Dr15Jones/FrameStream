#if !defined(FRAMEACCESS_FATABLEITR_CC)
#define FRAMEACCESS_FATABLEITR_CC
// -*- C++ -*-
//
// Package:     FrameAccess
// Module:      FATableItr
// 
// Description: A forward-iterator to access the contents of a FATable
//
// Implimentation:
//     Currently this is just a placehold of a memoery pointer.
//
// Author:      Simon Patton
// Created:     Tue Mar 18 13:23:11 EST 1997
// $Id: FATableItr.cc,v 1.12 2003/01/29 21:41:23 cleo3 Exp $
//
// Revision history
//
// $Log: FATableItr.cc,v $
// Revision 1.12  2003/01/29 21:41:23  cleo3
// minor changes to allow compilation by g++
//
// Revision 1.11  2000/12/26 21:10:21  cdj
// FAPtrTable now uses a vector when then Identifier is an integral type
//
// Revision 1.10  2000/04/21 17:50:16  cdj
// FAPtrTable now holds a map<Identifer,void*> to reduce number of map instantiations
//
// Revision 1.9  1999/12/10 14:16:23  cdj
// inlined operator++ because it was showing up in profier
//
// Revision 1.8  1999/04/13 13:53:35  bkh
// Make FATable<>::find() a const_iterator
//
// Revision 1.7  1999/02/14 18:21:58  lkg
// Fixed typos in postfix versions of "--" and "++" operators:  returned
// object was inc/decremented, rather than "*this".
//
// Fixed typo in -= operator: (*this) was incremented "n" times rather than
// decremented.
//
// Revision 1.6  1998/09/16 21:36:33  mkl
// use new bug flag for static/extern linkage of kFacilityStrings in Template .cc files
//
// Revision 1.5  1998/07/18 19:47:49  mkl
// solaris comp. has trouble parsing typedefs in templates; workaround
//
// Revision 1.4  1998/05/07 22:15:42  mkl
// g++ doesnt like typedefs as parameters to functions
//
// Revision 1.3  1998/05/07 19:46:22  mkl
// check for null labels
//
// Revision 1.2  1998/01/30 18:14:33  mkl
// added --operators
//
// Revision 1.1  1997/12/05 03:04:21  mkl
// moved sources from DataHandler
//
// Revision 1.11  1997/09/18 21:10:40  cdj
// changed Boolean to DABoolean
//
// Revision 1.10  1997/09/10 14:20:41  sjp
// Finished name changes for FAItr to FATableItr
//
// Revision 1.9  1997/09/10 14:14:51  sjp
// Changed FAItr to be FATableItr
//
// Revision 1.8  1997/09/01 15:35:45  sjp
// Changed report include to be in Experiment
//
// Revision 1.7  1997/08/27 03:16:11  sjp
// Updated to new name for bug flag
//
// Revision 1.6  1997/08/14 11:43:01  sjp
// Mods to run under CW Pro 1
//
// Revision 1.5  1997/07/09 18:00:22  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.4  1997/05/09 18:15:43  sjp
// Changed function name setPointer to setContents
//
// Revision 1.3  1997/04/20 19:09:32  sjp
// Added missing return call
//
// Revision 1.2  1997/04/20 18:37:38  sjp
// Renamed DD handling classes to FA classes
//
// Revision 1.1  1997/04/19 20:44:34  sjp
// First working version of iterator
//

#include "Experiment/Experiment.h"
// system include files
#include <stdlib.h>  // For 'exit'

// user include files
#include "Experiment/report.h" // For error report
#include "FrameAccess/FATableItr.h"


// STL classes

//
// constants, enums and typedefs
//

FILESCOPE_IN_TEMPLATE_CC_BUG const char* const kFATableItrFacilityString 
= "FrameAccess.FATableItr" ;

//
// static data member definitions
//

//
// constructors and destructor
//

template < class T >
FATableItr< T >::FATableItr()
{
}

template < class T >
FATableItr< T >::FATableItr( const FATableItr& aOtherPtr ) :
   FAItem< T >( aOtherPtr ) ,
   m_element( aOtherPtr.m_element )
{
}

#if !defined(TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG)
template < class T >
FATableItr< T >::FATableItr( const typename _fatableitr_map_::const_iterator& aElement) :
	 m_element( aElement )
{
   setContents( static_cast<T*>((*m_element).second ) ) ;
}

template < class T >
FATableItr< T >::FATableItr( // this one used to use default FAItem c'tor
   const typename _fatableitr_map_::const_iterator& aElement, int ) :
   m_element( aElement )
{
}
#endif /* TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG */

//template < class T >
//FATableItr< T >::~FATableItr()
//{
//}

//
// assignment operators
//

template < class T >
const FATableItr< T >&
FATableItr< T >::operator=( const FATableItr< T >& aOtherPtr )
{
   FAItem< T >::operator=( aOtherPtr ) ;
   m_element = aOtherPtr.m_element ;
   return( *this ) ;
}

//
// member functions
//

template < class T >
FATableItr< T >
FATableItr< T >::operator++(int)
{
   FATableItr< T > tmp( *this ) ;
   ++(*this); //operator++() ;
   return( tmp ) ;
}

template < class T >
FATableItr< T >&
FATableItr< T >::operator--()
{
   --m_element ;
   setContents( static_cast<T*>( (*m_element).second ) ) ;
   return( *this ) ;
}

template < class T >
FATableItr< T >
FATableItr< T >::operator--(int)
{
   FATableItr< T > tmp( *this ) ;
   --(*this); //operator--() ;
   return( tmp ) ;
}

template < class T >
FATableItr< T >
FATableItr< T >::operator+( FATableItr_Distance n )
{
   FATableItr< T > tmp( *this ) ;
   tmp += n;
   return( tmp ) ;
}

template < class T >
FATableItr< T >&
FATableItr< T >::operator+=( FATableItr_Distance n )
{
   advance( m_element, n );
   setContents( static_cast<T*>( (*m_element).second ) ) ;
   return( *this ) ;
}

template < class T >
FATableItr< T >
FATableItr< T >::operator-( FATableItr_Distance n )
{
   FATableItr< T > tmp( *this ) ;
   tmp -= n;
   return( tmp ) ;
}

template < class T >
FATableItr< T >&
FATableItr< T >::operator-=( FATableItr_Distance n )
{
   advance( m_element, -n );
   setContents( static_cast<T*>( (*m_element).second ) ) ;
   return( *this ) ;
}

template < class T >
FATableItr_Distance
FATableItr< T >::operator-( const FATableItr< T >& aPtr )
{
#if defined(NO_ITERATOR_TRAITS_BUG)
   FATableItr_Distance tDistance=0;
   distance( aPtr.m_element, m_element, tDistance);
   return tDistance;
#else
   return distance(aPtr.m_element, m_element);
#endif
}

//
// const member functions
//

template < class T >
DABoolean
FATableItr< T >::operator==( const FATableItr< T >& aOtherPtr ) const
{
   return ( m_element == aOtherPtr.m_element ) ;
}

template < class T >
DABoolean
FATableItr< T >::operator!=( const FATableItr< T >& aOtherPtr ) const
{
   return !( m_element == aOtherPtr.m_element ) ;
}

//
// static member functions
//

//
// non-member functions
//
template < class T >
FATableItr< T >
operator+( FATableItr_Distance n, const FATableItr< T >& aPtr )
{
   return( aPtr+n );
}

#endif /* FRAMEACCESS_FATABLEITR_CC */
