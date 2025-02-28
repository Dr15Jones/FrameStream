#if !defined(UTILITY_UTIDENTIFIER_CC)
#define UTILITY_UTIDENTIFIER_CC
// -*- C++ -*-
//
// Package:     Utility
// Module:      UTIdentifier
// 
// Description: <one line class summary>
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Chris D. Jones
// Created:     Mon Apr 28 12:09:12 EDT 1997
// $Id: UTIdentifier.cc,v 1.20 2002/12/05 21:40:53 cleo3 Exp $
//
// Revision history
//
// $Log: UTIdentifier.cc,v $
// Revision 1.20  2002/12/05 21:40:53  cleo3
// added missing typename
//
// Revision 1.19  2002/08/21 19:41:41  cleo3
// added missing C++Std/iostream.h
//
// Revision 1.18  1997/09/18 21:35:55  cdj
// changed Boolean to DABoolean
//
// Revision 1.17  1997/09/03 20:06:04  sjp
// Uses CPP macros for STL containers
//
// Revision 1.15  1997/09/03 03:26:13  mkl
// fixed typo
//
// Revision 1.14  1997/09/02 15:58:35  sjp
// Fixed error in CPP macro naming
//
// Revision 1.13  1997/09/01 16:23:13  sjp
// Moved TBIdentifier to UTIdentifier
//
// Revision 1.12  1997/08/30 18:57:24  cdj
// Bug fixes: 1) #define vector looks for NO_ALLOCATOR_IN_STL_DECLARATION_BUG
//            2) methods taking UTIdentifier's use TBIdentifer<ID, T>
//
// Revision 1.11  1997/08/28 06:23:36  sjp
// Updated the bug flag for forward declarations
//
// Revision 1.10  1997/08/27 03:41:36  sjp
// Updated to new name for bug flags
//
// Revision 1.9  1997/08/20 18:18:41  sjp
// Updated bug flags
//
// Revision 1.8  1997/08/14 11:42:37  sjp
// Mods to run under CW Pro 1
//
// Revision 1.7  1997/07/21 18:37:05  sjp
// put in CPP flags to stop double inclusion
//
// Revision 1.6  1997/07/17 18:42:28  sjp
// Cleaned up problem with static data in template class
//
// Revision 1.5  1997/07/10 16:22:04  sjp
// fix spelling error in bug flag
//
// Revision 1.4  1997/07/08 14:34:10  sjp
// removed obselete bug file include
//
// Revision 1.3  1997/07/07 16:15:31  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.2  1997/05/07 19:54:50  sjp
// Added "read from stream" function
//
// Revision 1.1  1997/04/30 13:43:44  sjp
// New file to speed up matching identifiers
//

#include "Experiment/Experiment.h"
// system include files
#include "C++Std/iostream.h"

// user include files
#include "Utility/UTIdentifier.h"


// STL classes
#include <map>
#include <vector>

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
template< class ID, class T >
UTIdentifier< ID , T >::UTIdentifier( void ):
   m_index(0)
{
   m_index = findIndex( ID() );
}

template< class ID, class T >
UTIdentifier< ID , T >::UTIdentifier( const ID& iID ) :
   m_index(0)
{
   m_index = findIndex( iID );
}

template< class ID, class T >
UTIdentifier< ID , T >::UTIdentifier( const UTIdentifier<ID, T>& iIdentifier)
{
   m_index = iIdentifier.m_index;
}

template< class ID, class T >
UTIdentifier< ID , T >::~UTIdentifier()
{
}

//
// assignment operators
//
template< class ID, class T >
const UTIdentifier< ID , T >& 
UTIdentifier< ID , T >::operator=( const UTIdentifier< ID , T >& iRHS )
{
   m_index = iRHS.m_index;
   return *this;
}

//
// member functions
//

//
// const member functions
//
template< class ID, class T >
DABoolean
UTIdentifier< ID , T >::operator==( const UTIdentifier< ID, T >& iRHS ) const
{
   return (m_index == iRHS.m_index );
}

template< class ID, class T >
DABoolean
UTIdentifier< ID , T >::operator!=( const UTIdentifier< ID, T >& iRHS ) const
{
   return (m_index != iRHS.m_index );
}

template< class ID, class T >
 Count
UTIdentifier< ID , T >::index( void ) const
{
   return m_index;
}

template< class ID, class T >
const ID&
UTIdentifier< ID , T >::value( void ) const
{
#if defined(FORWARD_DECLARATION_NOT_BOUND_TO_DEFINITION_BUG)
   typedef _utidentifier_ids_ _tmp_ ;
#endif /* FORWARD_DECLARATION_NOT_BOUND_TO_DEFINITION_BUG */
   return idList()[ m_index ];
}

//
// static member functions
//

template< class ID, class T >
_utidentifier_counts_&
UTIdentifier< ID , T >::idToIndexMap( void ) 
{
   static _utidentifier_counts_ m_idToIndexMap ;

   return ( m_idToIndexMap ) ;
}

template< class ID, class T >
_utidentifier_ids_&
UTIdentifier< ID , T >::idList( void ) 
{
   static _utidentifier_ids_ m_idList ;

   return ( m_idList ) ;
}

template< class ID, class T >
Count
UTIdentifier< ID , T >::findIndex( const ID& iID )
{
   Count returnValue;
   
   typename _utidentifier_counts_::const_iterator itEnd = 
      idToIndexMap().end();
   typename _utidentifier_counts_::const_iterator itFind = 
      idToIndexMap().find( iID );

   if( itFind != itEnd ){
      returnValue = (*itFind).second;
   } else {
      //Have to add
      returnValue = idToIndexMap().size();
      
      idToIndexMap().insert( _utidentifier_counts_::value_type(
	 iID, returnValue ));

      idList().push_back( iID );
   }

   return returnValue;
}

template< class ID, class T >
ostream&
operator<<( ostream& iOStream , const UTIdentifier< ID , T >& iIdentifier )
{
   return ( iOStream << iIdentifier.value());
}

template< class ID, class T >
istream&
operator>>( istream& iIStream , UTIdentifier< ID , T >& iIdentifier )
{
   ID tmp ;
   iIStream >> tmp ;
   iIdentifier = UTIdentifier< ID , T >( tmp ) ;
   return ( iIStream );
}

#endif /* UTILITY_UTIDENTIFIER_CC */
