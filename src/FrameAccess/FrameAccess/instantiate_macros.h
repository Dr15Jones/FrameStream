#if !defined(FRAMEACCESS_INSTANTIATE_MACROS_H)
#define FRAMEACCESS_INSTANTIATE_MACROS_H
// -*- C++ -*-
//
// Package:     FrameAccess
// Module:      instantiate_macros
// 
// Description: cpp macros useful for instantiating One and Many
//
// Usage:
//    These macros facilitate the manual instantiation of all the 
//   templates needed to 'insert' and 'extract' data from the 
//   Data Access System.
//
// Author:      Chris D. Jones
// Created:     Mon Sep 28 16:36:08 EDT 1998
// $Id: instantiate_macros.h,v 1.4 2002/06/12 20:27:41 cleo3 Exp $
//
// Revision history
//
// $Log: instantiate_macros.h,v $
// Revision 1.4  2002/06/12 20:27:41  cleo3
// updated to new template specialization syntax
//
// Revision 1.3  1999/05/07 01:26:32  cdj
// Added smart pointers for Constants access
//
// Revision 1.2  1998/09/30 20:04:45  cdj
// fixed typo in macro
//
// Revision 1.1  1998/09/30 14:14:41  cdj
// first submission
//

// system include files

// user include files
#include "HeteroContainer/HCTypeTagTemplate.h"

// forward declerations
class DataKey;
template< class T > class FAPtrTable;
template< class T > class CLEOConstants;

#define INSTANTIATE_ONE( _instantiate_one_type_ ) \
typedef _instantiate_one_type_ _one_element_ ; \
HCTYPETAGTEMPLATE_CLASSNAME( _instantiate_one_type_ , DataKey )

#define INSTANTIATE_ONE_1_COMMA( _instantiate_one_type_1, _instantiate_one_type_2 ) \
typedef _instantiate_one_type_1,_instantiate_one_type_2 _one_element_ ; \
HCTYPETAGTEMPLATE_CLASSNAME_1_COMMA( _instantiate_one_type_1, _instantiate_one_type_2 , DataKey )

#define INSTANTIATE_MANY( _instantiate_many_type_ ) \
typedef _instantiate_many_type_ _many_element_ ; \
template<> \
const char* \
HCTypeTagTemplate< FAPtrTable< _instantiate_many_type_ > , DataKey >::className() \
{ return "FATable<" #_instantiate_many_type_ ">" ; }

#define INSTANTIATE_MANY_1_COMMA( _instantiate_many_type_1, _instantiate_many_type_2 ) \
typedef _instantiate_many_type_1,_instantiate_many_type_2 _many_element_ ; \
template<> \
const char* \
HCTypeTagTemplate< FAPtrTable< _instantiate_many_type_1, _instantiate_many_type_2 > , DataKey >::className() \
{ return "FATable<" #_instantiate_many_type_1 "," #_instantiate_many_type_2 ">" ; }

#define INSTANTIATE_CONSTANTS( _instantiate_const_type_ ) \
typedef _instantiate_const_type_ _constant_element_ ; \
template<> \
const char* \
HCTypeTagTemplate< CLEOConstants< _instantiate_const_type_ > , DataKey >::className() \
{ return "Constants<" #_instantiate_const_type_ ">" ; }

#define INSTANTIATE_NONSEQCONSTANTS( _instantiate_const_type_ ) \
INSTANTIATE_CONSTANTS( _instantiate_const_type_ )

#endif /* FRAMEACCESS_INSTANTIATE_MACROS_H */
