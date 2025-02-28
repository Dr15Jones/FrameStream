#if !defined(FRAMEACCESS_FAPTRTABLE_CC)
#define FRAMEACCESS_FAPTRTABLE_CC
// -*- C++ -*-
//
// Package:     FrameAccess
// Module:      FATable
// 
// Description: Table to hold a set of pointer as a single unit
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Simon Patton
// Created:     Mon Apr 14 15:19:10 EDT 1997
// $Id: FAPtrTable.cc,v 1.11 2003/01/29 21:41:23 cleo3 Exp $
//
// Revision history
//
// $Log: FAPtrTable.cc,v $
// Revision 1.11  2003/01/29 21:41:23  cleo3
// minor changes to allow compilation by g++
//
// Revision 1.10  2001/01/02 22:20:33  cdj
// insert now returns an iterator
//
// Revision 1.9  2000/12/26 21:10:21  cdj
// FAPtrTable now uses a vector when then Identifier is an integral type
//
// Revision 1.8  2000/06/02 18:53:49  cdj
// optimized FAPtrTable insert method
//
// Revision 1.7  2000/04/21 17:50:16  cdj
// FAPtrTable now holds a map<Identifer,void*> to reduce number of map instantiations
//
// Revision 1.6  1999/12/03 15:01:59  bkh
// Add empty() member function
//
// Revision 1.5  1999/04/13 13:53:32  bkh
// Make FATable<>::find() a const_iterator
//
// Revision 1.4  1998/09/16 21:36:31  mkl
// use new bug flag for static/extern linkage of kFacilityStrings in Template .cc files
//
// Revision 1.3  1998/07/07 19:26:02  mkl
// FAPtrTable::dtor deletes its internal table of pointers; added 'eraseWithoutDeleteAll' which deletes table entries, but pointed-to memory
//
// Revision 1.2  1998/04/09 23:19:40  cleo3
// port to egcs
//
// Revision 1.1  1997/12/05 03:04:20  mkl
// moved sources from DataHandler
//
// Revision 1.10  1997/09/10 14:22:32  sjp
// Finished name changes for FAItr to FATableItr
//
// Revision 1.9  1997/09/10 14:14:53  sjp
// Changed FAItr to be FATableItr
//
// Revision 1.8  1997/08/27 03:16:13  sjp
// Updated to new name for bug flag
//
// Revision 1.7  1997/08/14 11:43:03  sjp
// Mods to run under CW Pro 1
//
// Revision 1.6  1997/07/09 18:00:23  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.5  1997/06/03 17:09:50  sjp
// Modified to contain map rather than inherit from
//
// Revision 1.4  1997/05/09 18:20:09  sjp
// Removed rogue space
//
// Revision 1.3  1997/04/20 18:37:42  sjp
// Renamed DD handling classes to FA classes
//
// Revision 1.2  1997/04/19 20:43:57  sjp
// activated begin and end functions
//
// Revision 1.1  1997/04/14 19:49:16  sjp
// Take code out of header file
//

#include "Experiment/Experiment.h"
// system include files
#include <assert.h>

// user include files
#include "FrameAccess/FAPtrTable.h"


// STL classes

#include <map>

//
// constants, enums and typedefs
//

FILESCOPE_IN_TEMPLATE_CC_BUG const char* const kFAPtrTableFacilityString 
= "DataDelivery.FAPtrTable" ;

//
// static data member definitions
//

//
// constructors and destructor
//

template < class T >
FAPtrTable< T >::FAPtrTable() :
   m_map( *(new _fatableitr_map_) )
{
   if ( 0 == &m_map ) {
      assert(false);
      exit( 1 ) ;
   }
}

// FAPtrTable::FAPtrTable( const FAPtrTable& )
// {
// }

template < class T >
FAPtrTable< T >::~FAPtrTable()
{
   FAPtrTable< T >::eraseAll();
   delete &m_map ;
}

//
// assignment operators
//
// const FAPtrTable& FAPtrTable::operator=( const FAPtrTable& )
// {
// }

//
// member functions
//

template < class T >
FATableItr<T>
FAPtrTable< T >::insert( T* aEntry )
{
   //optimization try inserting the entry at the end of the table
   // since most people insert items in order
   if( ! m_map.empty() ) {
      return FATableItr<T>( m_map.insert( m_map.end() ,
	 _fatableitr_map_::value_type( (*aEntry).identifier() , aEntry ) 
	 ) );
   } 
   return FATableItr<T>( ( m_map.insert( 
      _fatableitr_map_::value_type( (*aEntry).identifier() , aEntry ) 
      ) ).first );
}

template < class T >
void
FAPtrTable< T >::eraseAll()
{
   typename _fatableitr_map_::iterator start( m_map.begin() ) ;
   typename _fatableitr_map_::iterator finished( m_map.end() ) ;
   for ( typename _fatableitr_map_::iterator entry( start ) ;
	 entry != finished ;
	 ++entry ) {
      delete static_cast<T*>( (*entry).second );
   }
   m_map.erase( start ,
		finished ) ;
}

template < class T >
void
FAPtrTable< T >::eraseWithoutDeleteAll()
{
   m_map.erase( m_map.begin(), m_map.end() );
}

//
// const member functions
//


//
// static member functions
//

#endif /* FRAMEACCESS_FAPTRTABLE_CC */
