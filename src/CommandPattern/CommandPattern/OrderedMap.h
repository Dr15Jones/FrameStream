#if !defined(COMMANDPATTERN_NAMEDORDEREDCONTAINER_H)
#define COMMANDPATTERN_NAMEDORDEREDCONTAINER_H
// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      OrderedMap
// 
// Description: Container similar to a map, but ordered!
//             
// Usage:

// Author:      Martin  Lohner
// Created:     Tue April 13 15:48:09 EST 1999
// $Id: OrderedMap.h,v 1.2 2002/12/09 15:25:12 cleo3 Exp $
//
// Revision history (at end of file)
//

// system include files

// user include files

// forward declarations
#include "C++Std/fwd_string.h"
#include "STLUtility/fwd_vector.h"
#include "STLUtility/fwd_map.h"
#if !defined(_OrderedMap_items_)
#define _OrderedMap_items_ STL_VECTOR( value_type )
#endif

template< class Key, class Item >
class OrderedMap
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      // an Item has a name and a content
      struct value_type {
	    value_type() {}
	    value_type( const Key& iKey, const Item& iItem )
	       : first( iKey ), second( iItem ) {}
	    Key first;
	    Item second;
      };
      typedef typename _OrderedMap_items_::iterator iterator;
      typedef typename _OrderedMap_items_::const_iterator const_iterator;
      typedef unsigned int size_type;

      // Constructors and destructor
      OrderedMap();
      ~OrderedMap();

      // member functions

      void insert( const Key& iKey, const Item& iItem );
      void insert( const value_type& iValue );
      size_type erase( const Key& iKey );
      void erase( iterator iWhich );
      void erase( iterator iBegin, iterator iEnd );

      iterator find( const Key& iKey );

      iterator begin();
      iterator end();

      // const member functions
      const_iterator find( const Key& iKey ) const;

      const_iterator begin() const;
      const_iterator end() const;

      DABoolean empty() const;

      // listings
      string list() const;

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:

      // Constructors and destructor
      OrderedMap( 
	 const OrderedMap& ); // stop default
      
      // assignment operator(s)
      const OrderedMap& 
      operator=( const OrderedMap& ); // stop default

      // private member functions

      // private const member functions

      // data members
      _OrderedMap_items_& m_items; 

      // static data members

};

// inline function definitions

// Uncomment the following lines, if your class is templated
// and has an implementation file (in the Template directory)
#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
# include "CommandPattern/Template/OrderedMap.cc"
#endif                                


// ---------------------------------------------------------------
// Revision history
//
// $Log: OrderedMap.h,v $
// Revision 1.2  2002/12/09 15:25:12  cleo3
// added typename
//
// Revision 1.1  1999/04/14 21:15:39  mkl
// ordered container used in Suez
//
//

#endif /* COMMANDPATTERN_NAMEDORDEREDCONTAINER_H */
