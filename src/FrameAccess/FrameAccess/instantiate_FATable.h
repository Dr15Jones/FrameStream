#if !defined(FRAMEACCESS_INSTANTIATE_FATABLE_H)
#define FRAMEACCESS_INSTANTIATE_FATABLE_H
// -*- C++ -*-
//
// Package:     FrameAccess
// Module:      Instantiation
// 
// Description: Code required to explicilty instantiate a "FATable" Data element
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Simon Patton, Martin Lohner
// Created:     Wed Apr 21 14:32:44 EDT 1998
// $Id: instantiate_FATable.h,v 1.4 2002/04/03 19:08:33 cleo3 Exp $
//
// Revision history
//
// $Log: instantiate_FATable.h,v $
// Revision 1.4  2002/04/03 19:08:33  cleo3
// provide more control on extactly what gets instantiated
//
// Revision 1.3  2000/12/26 21:10:18  cdj
// FAPtrTable now uses a vector when then Identifier is an integral type
//
// Revision 1.2  2000/04/21 17:50:13  cdj
// FAPtrTable now holds a map<Identifer,void*> to reduce number of map instantiations
//
// Revision 1.1  1998/04/22 20:24:01  mkl
// extracted out FAItem/Table instantiations into their own file
//
//

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */

#include "FrameAccess/Template/FAItem.cc"
#include "FrameAccess/Template/FATableItr.cc"
#if !defined(DO_NOT_INSTANTIATE_FAPTRTABLE)
#include "FrameAccess/Template/FAPtrTable.cc"
#else
#include "FrameAccess/FAPtrTable.h"
#endif
#include "FrameAccess/Template/FATable.cc"

typedef FAPtrTable< _many_element_ > _ptrTable_element_ ;
typedef FATable< _many_element_ > _table_element_ ;

#if ( defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX) )
// for AXP
#  pragma define_template FAItem< _many_element_ >
#  pragma define_template FATable< _many_element_ >
#  pragma define_template FATableItr< _many_element_ >
#if !defined(DO_NOT_INSTANTIATE_FAPTRTABLE)
#  pragma define_template FAPtrTable< _many_element_ >
#endif
#else
template class FAItem< _many_element_ > ;
template class FATable< _many_element_ > ;
template class FATableItr< _many_element_ > ;
#if !defined(DO_NOT_INSTANTIATE_FAPTRTABLE)
template class FAPtrTable< _many_element_ > ;
#endif
#endif /* (defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX)) */

#if defined(INSTANTIATE_FATABLE_MAP)
#include <map>

typedef _many_element_::Identifier _map_key_ ;
typedef void * _map_contents_ ;
typedef less< _map_key_ > _map_compare_ ;

#include "STLUtility/instantiate_map.h"

#if defined(__DECCXX)
//FATableItr uses advance
template void std::_RWadvance (
     STL_MAP_COMP(_map_key_,_map_contents_,_map_compare_) ::const_iterator&
   , FATableItr_Distance
   , bidirectional_iterator_tag );
#endif

#endif

#endif /* FRAMEACCESS_INSTANTIATE_FATABLE_H */
