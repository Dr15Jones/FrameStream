#if !defined(STLUTILITY_INSTANTIATE_MAP_OF_MAP_H)
#define STLUTILITY_INSTANTIATE_MAP_OF_MAP_H
// -*- C++ -*-
//
// Package:     STLUtility
// Module:      Instantiation
// 
// Description: Code required to explicilty instantiate STL map-of-map
//
// format:
// map< _map_of_map_key_, 
//      map< _map_key_, _map_contents_, _map_compare_ >, 
//      _map_of_map_compare_
//    >
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Tue Aug 12 23:32:44 EDT 1997
// $Id: instantiate_map_of_map.h,v 1.3 1998/02/03 22:13:24 mkl Exp $
//
// Revision history
//
// $Log: instantiate_map_of_map.h,v $
// Revision 1.3  1998/02/03 22:13:24  mkl
// changed *_COMPARE macros to *_COMP
//
// Revision 1.2  1998/02/02 23:31:54  sjp
// Fixed include files for new package
//
// Revision 1.1.1.1  1998/02/02 23:25:35  sjp
// New package for files that help STL usage
//
// Revision 1.2  1997/09/03 20:05:53  sjp
// Uses CPP macros for STL containers
//
// Revision 1.1  1997/08/13 04:05:34  mkl
// instantiation file for map of a map
//
//

#include <map>

// format:
// map< _map_of_map_key_, 
//      map< _map_key_, _map_contents_, _map_compare_ >, 
//      _map_of_map_compare_
//    >

#if ( defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX) )
// for AXP
//
// required for map
#  pragma define_template map< _map_key_ ,  _map_contents_ , _map_compare_ >
#  pragma define_template rb_tree<_map_key_, pair<const _map_key_, _map_contents_>, select1st<pair<const _map_key_, _map_contents_>, _map_key_>, _map_compare_ >

#  pragma define_template map< _map_of_map_key_, map< _map_key_ ,  _map_contents_ , _map_compare_ >, _map_of_map_compare_ >

// normal map
# pragma define_template rb_tree< _map_of_map_key_, pair< const
_map_of_map_key_, map< _map_key_, _map_contents_,
_map_compare_ > >, select1st< pair< const _map_of_map_key_, map<
_map_key_, _map_contents_, _map_compare_ > >,
_map_of_map_key_ >, _map_of_map_compare_ >

// map pointer
# pragma define_template rb_tree< _map_of_map_key_, pair< const
_map_of_map_key_, map< _map_key_, _map_contents_,
_map_compare_ >* >, select1st< pair< const _map_of_map_key_, map<
_map_key_, _map_contents_, _map_compare_ >* >,
_map_of_map_key_ >, _map_of_map_compare_ >

//
// Have to define the functions here as 'cxx' does not allow you to "pick"
//   which template to use when there are multiple ones on offer!

// ----------- map --------------
void __distance( rb_tree<_map_key_, pair<const _map_key_, _map_contents_>, select1st<pair<const _map_key_, _map_contents_>, _map_key_>, _map_compare_ >::iterator first,
		 rb_tree<_map_key_, pair<const _map_key_, _map_contents_>, select1st<pair<const _map_key_, _map_contents_>, _map_key_>, _map_compare_ >::iterator last,
		unsigned long& n,
		bidirectional_iterator_tag) {
   while (first != last) { ++first; ++n; }
}

void __distance( rb_tree<_map_key_, pair<const _map_key_, _map_contents_>, select1st<pair<const _map_key_, _map_contents_>, _map_key_>, _map_compare_ >::const_iterator first,
		 rb_tree<_map_key_, pair<const _map_key_, _map_contents_>, select1st<pair<const _map_key_, _map_contents_>, _map_key_>, _map_compare_ >::const_iterator last,
		unsigned long& n,
		bidirectional_iterator_tag) {
   while (first != last) { ++first; ++n; }
}

// --------- map of map ---------
// normal map
// iterator
void __distance( rb_tree< _map_of_map_key_, pair< const 
_map_of_map_key_, map< _map_key_, _map_contents_,
_map_compare_ > >, select1st< pair< const _map_of_map_key_, map<
_map_key_, _map_contents_, _map_compare_ > >,
_map_of_map_key_ >, _map_of_map_compare_ >::iterator first,
		 rb_tree< _map_of_map_key_, pair< const
_map_of_map_key_, map< _map_key_, _map_contents_,
_map_compare_ > >, select1st< pair< const _map_of_map_key_, map<
_map_key_, _map_contents_, _map_compare_ > >,
_map_of_map_key_ >, _map_of_map_compare_ >::iterator last, 
		unsigned long& n,
		bidirectional_iterator_tag) {
   while (first != last) { ++first; ++n; }
}

// normal map
// const iterator
void __distance( rb_tree< _map_of_map_key_, pair< const
_map_of_map_key_, map< _map_key_, _map_contents_,
_map_compare_ > >, select1st< pair< const _map_of_map_key_, map<
_map_key_, _map_contents_, _map_compare_ > >,
_map_of_map_key_ >, _map_of_map_compare_ >::const_iterator first,
		 rb_tree< _map_of_map_key_, pair< const
_map_of_map_key_, map< _map_key_, _map_contents_,
_map_compare_ > >, select1st< pair< const _map_of_map_key_, map<
_map_key_, _map_contents_, _map_compare_ > >,
_map_of_map_key_ >, _map_of_map_compare_ >::const_iterator last, 
		unsigned long& n,
		bidirectional_iterator_tag) {
   while (first != last) { ++first; ++n; }
}

// map pointer
// iterator
void __distance( rb_tree< _map_of_map_key_, pair< const 
_map_of_map_key_, map< _map_key_, _map_contents_,
_map_compare_ >* >, select1st< pair< const _map_of_map_key_, map<
_map_key_, _map_contents_, _map_compare_ >* >,
_map_of_map_key_ >, _map_of_map_compare_ >::iterator first,
		 rb_tree< _map_of_map_key_, pair< const
_map_of_map_key_, map< _map_key_, _map_contents_,
_map_compare_ >* >, select1st< pair< const _map_of_map_key_, map<
_map_key_, _map_contents_, _map_compare_ >* >,
_map_of_map_key_ >, _map_of_map_compare_ >::iterator last, 
		unsigned long& n,
		bidirectional_iterator_tag) {
   while (first != last) { ++first; ++n; }
}

// map pointer
// const iterator
void __distance( rb_tree< _map_of_map_key_, pair< const
_map_of_map_key_, map< _map_key_, _map_contents_,
_map_compare_ >* >, select1st< pair< const _map_of_map_key_, map<
_map_key_, _map_contents_, _map_compare_ >* >,
_map_of_map_key_ >, _map_of_map_compare_ >::const_iterator first,
		 rb_tree< _map_of_map_key_, pair< const
_map_of_map_key_, map< _map_key_, _map_contents_,
_map_compare_ >* >, select1st< pair< const _map_of_map_key_, map<
_map_key_, _map_contents_, _map_compare_ >* >,
_map_of_map_key_ >, _map_of_map_compare_ >::const_iterator last, 
		unsigned long& n,
		bidirectional_iterator_tag) {
   while (first != last) { ++first; ++n; }
}

#else

#include "STLUtility/fwd_map.h"
template class STL_MAP_COMP( _map_of_map_key_, STL_MAP_COMP( _map_key_ , _map_contents_, _map_compare_ ), _map_of_map_compare_ ) ;

#endif /* PRAGMA_TEMPLATE_INSTANTIATION_BUG && __DECCXX */

#endif /* STLUTILITY_INSTANTIATE_MAP_OF_MAP_H */

