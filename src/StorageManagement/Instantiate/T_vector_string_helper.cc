// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      T_vector_float_helper
// 
// Description:
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Fri Apr 23 14:15:34 EDT 1999
// $Id: T_vector_string_helper.cc,v 1.1 2001/06/08 13:52:15 cdj Exp $
//
// Revision history
//
// $Log: T_vector_string_helper.cc,v $
// Revision 1.1  2001/06/08 13:52:15  cdj
// added instantiation needed to handle vector of strings
//
// Revision 1.1  2000/01/20 19:23:17  bkh
// instantiations for general use
//
// Revision 1.1  2000/01/17 22:20:01  bkh
// Changes for storage helpers
//
//
//

#include "Experiment/Experiment.h"

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#include <string>

#include "STLUtility/fwd_vector.h"

#include <vector>

// user include files
#include "FrameAccess/instantiate_macros.h"
INSTANTIATE_ONE(string)

#include "STLUtility/iterator_traits_fix.h"
#if defined(NO_ITERATOR_TRAITS_BUG)
template<>
struct iterator_traits<const string*> {
   typedef string value_type;
};
template<>
struct iterator_traits<string*> {
   typedef string value_type;
};
#endif

typedef STL_VECTOR( string ) _container_type_ ;
#include "StorageManagement/instantiate_contents_builtin.h"


