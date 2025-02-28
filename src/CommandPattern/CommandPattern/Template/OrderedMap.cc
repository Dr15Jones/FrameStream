#if !defined(COMMANDPATTERN_NAMEDORDEREDCONTAINER_CC)
#define COMMANDPATTERN_NAMEDORDEREDCONTAINER_CC
// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      OrderedMap
// 
// Description: 
//
// Implementation: 
//
// Author:      Martin  Lohner
// Created:     Wed April 14 15:53:40 EST 1999
// $Id: OrderedMap.cc,v 1.2 2002/12/09 15:25:13 cleo3 Exp $
//
// Revision history (at end of file)
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h> // for exit
#include <assert.h>
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "CommandPattern/OrderedMap.h"

// STL classes
#include <vector>

//
// constants, enums and typedefs
//
FILESCOPE_IN_TEMPLATE_CC_BUG const char* const 
kOrderedMapFacilityString = "CommandPattern.OrderedMap";

//
// static data member definitions
//

//
// constructors and destructor
//
template< class Key, class Item >
OrderedMap< Key, Item >::OrderedMap() 
   : m_items( *new _OrderedMap_items_ )
{
   if( 0 == &m_items )
   {
      report( EMERGENCY, kOrderedMapFacilityString )
	 << "Unable to allocate memory"
	 << endl ;
      assert(false);
      ::exit( 1 );
   }
}

// OrderedMap::OrderedMap( const OrderedMap& )
// {
// }

template< class Key, class Item >
OrderedMap< Key, Item >::~OrderedMap()
{
   erase( begin(), end() );
   delete &m_items;
}

//
// assignment operators
//
// const OrderedMap& OrderedMap::operator=( const OrderedMap& )
// {
// }

//
// member functions
//
template< class Key, class Item >
void
OrderedMap< Key, Item >::insert( const Key& iKey, 
					    const Item& iItem )
{
   m_items.push_back( value_type( iKey, iItem ) );
}

template< class Key, class Item >
void
OrderedMap< Key, Item >::insert( 
   const OrderedMap< Key, Item >::value_type& iValue )
{
   m_items.push_back( iValue );
}

template< class Key, class Item >
typename OrderedMap< Key, Item >::size_type
OrderedMap< Key, Item >::erase( const Key& iKey )
{
   size_type how_many = 0;

   // really would need to find all occurrences (for now only first)
   iterator which = find( iKey );
   if( which != m_items.end() )
   {
      m_items.erase( which );
      ++how_many;
   }
   
   return how_many;
}

template< class Key, class Item >
void
OrderedMap< Key, Item >::erase( 
   OrderedMap< Key, Item >::iterator iWhich )
{
   m_items.erase( iWhich );
}


template< class Key, class Item >
void
OrderedMap< Key, Item >::erase( 
   OrderedMap< Key, Item >::iterator iBegin, 
   OrderedMap< Key, Item >::iterator iEnd )
{
   m_items.erase( iBegin, iEnd );
}

template< class Key, class Item >
typename OrderedMap< Key, Item >::iterator
OrderedMap< Key, Item >::find( const Key& iKey )
{
   // really would need to find all occurrences (for now only first)
   iterator which = m_items.begin();
   iterator end = m_items.end();
   while( which != end && !( (*which).first == iKey ) ) ++which;

   return which;
}

template< class Key, class Item >
typename OrderedMap< Key, Item >::iterator
OrderedMap< Key, Item >::begin()
{
   return m_items.begin();
}

template< class Key, class Item >
typename OrderedMap< Key, Item >::iterator
OrderedMap< Key, Item >::end()
{
   return m_items.end();
}

//
// const member functions
//
template< class Key, class Item >
typename OrderedMap< Key, Item >::const_iterator
OrderedMap< Key, Item >::find( const Key& iKey ) const
{
   // really would need to find all occurrences (for now only first)
   const_iterator which = m_items.begin();
   const_iterator end = m_items.end();
   while( which != end && !( (*which).first == iKey ) ) ++which;

   return which;
}

template< class Key, class Item >
string
OrderedMap< Key, Item >::list() const
{
   string returnValue;

   const_iterator end( m_items.end() );
   for( const_iterator iter = m_items.begin();
        iter != end;
        ++iter )
   {
      // assemble return string
      returnValue += string( " " ) + (*iter).first + string( "\n" );
   }

   return returnValue;
}

template< class Key, class Item >
typename OrderedMap< Key, Item >::const_iterator
OrderedMap< Key, Item >::begin() const
{
   return m_items.begin();
}

template< class Key, class Item >
typename OrderedMap< Key, Item >::const_iterator
OrderedMap< Key, Item >::end() const
{
   return m_items.end();
}

template< class Key, class Item >
DABoolean
OrderedMap< Key, Item >::empty() const
{
   DABoolean returnValue = ( m_items.end() == m_items.begin() ) ? true : false;
   return returnValue;
}

//
// static member functions
//


// ------------------------------------------------------------------
// Revision history
//
// $Log: OrderedMap.cc,v $
// Revision 1.2  2002/12/09 15:25:13  cleo3
// added typename
//
// Revision 1.1  1999/04/14 21:15:43  mkl
// ordered container used in Suez
//
//
//

#endif /* COMMANDPATTERN_NAMEDORDEREDCONTAINER_CC */
