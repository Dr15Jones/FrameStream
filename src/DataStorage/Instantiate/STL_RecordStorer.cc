// -*- C++ -*-
//
// Package:     DataStorage
// Module:      STL_RecordStorer
// 
// Description: Instantiate STL classes for RecordStorer*
//
//
// Author:      Martin Lohner
// Created:     Fri Jul 11 12:45:29 EDT 1997
// $Id: STL_RecordStorer.cc,v 1.5 1998/06/17 22:18:23 mkl Exp $
//
// Revision history
//
// $Log: STL_RecordStorer.cc,v $
// Revision 1.5  1998/06/17 22:18:23  mkl
// replaced one-sided c-comment with cpp uncomment
//
// Revision 1.4  1998/02/03 21:28:51  mkl
// switch over to STLUtility library
//
// Revision 1.3  1997/09/04 15:16:29  mkl
// moved to new bug flags
//
// Revision 1.2  1997/08/16 17:45:43  cdj
// Modified to work with Proxies
//
// Revision 1.1  1997/07/11 16:53:26  mkl
// added STL instantiation files
//
//


#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "DataHandler/Stream.h"


class RecordStorer ;

#include <map>

typedef Stream::Type _map_key_ ;
typedef RecordStorer* _map_contents_ ;
typedef less< _map_key_ > _map_compare_ ;

#include "STLUtility/instantiate_map.h"


#if 0 /* don't use no more */

#if ( defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX) )
// for AXP
//
// required for map
#  pragma define_template map< Stream::Type ,  RecordStorer* , less< Stream::Type > >
#  pragma define_template rb_tree<Stream::Type, pair<const Stream::Type,  RecordStorer*>, select1st<pair<const Stream::Type,  RecordStorer*>, Stream::Type>, less<Stream::Type> >
//
// Have to define the functions here as 'cxx' does not allow you to "pick"
//   which template to use when there are multiple ones on offer!
void __distance(rb_tree<Stream::Type, pair<const Stream::Type,  RecordStorer*>, select1st<pair<const Stream::Type,  RecordStorer*>, Stream::Type>, less<Stream::Type> >::iterator first,
		rb_tree<Stream::Type, pair<const Stream::Type,  RecordStorer*>, select1st<pair<const Stream::Type,  RecordStorer*>, Stream::Type>, less<Stream::Type> >::iterator last, 
		unsigned long& n,
		bidirectional_iterator_tag) {
   while (first != last) { ++first; ++n; }
}

void __distance(rb_tree<Stream::Type, pair<const Stream::Type,  RecordStorer*>, select1st<pair<const Stream::Type,  RecordStorer*>, Stream::Type>, less<Stream::Type> >::const_iterator first,
		rb_tree<Stream::Type, pair<const Stream::Type,  RecordStorer*>, select1st<pair<const Stream::Type,  RecordStorer*>, Stream::Type>, less<Stream::Type> >::const_iterator last, 
		unsigned long& n,
		bidirectional_iterator_tag) {
   while (first != last) { ++first; ++n; }
}
#else
template class map< Stream::Type , RecordStorer*, less< Stream::Type > > ;
#endif /* (defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX)) */

#endif /* don't use no more */
