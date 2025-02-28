#if !defined(FRAMEACCESS_INSTANTIATE_FAITEM_H)
#define FRAMEACCESS_INSTANTIATE_FAITEM_H
// -*- C++ -*-
//
// Package:     FrameAccess
// Module:      Instantiation
// 
// Description: Code required to explicilty instantiate a "FAItem" Data element
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Simon Patton, Martin Lohner
// Created:     Wed Apr 21 14:32:44 EDT 1998
// $Id: instantiate_FAItem.h,v 1.1 1998/04/22 20:24:00 mkl Exp $
//
// Revision history
//
// $Log: instantiate_FAItem.h,v $
// Revision 1.1  1998/04/22 20:24:00  mkl
// extracted out FAItem/Table instantiations into their own file
//
//

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */

#include "FrameAccess/Template/FAItem.cc"

#if ( defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX) )
// for AXP
#  pragma define_template FAItem< _one_element_ >

#else

template class FAItem< _one_element_ > ;

#endif /* (defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX)) */

#endif /* FRAMEACCESS_INSTANTIATE_FAITEM_H */
