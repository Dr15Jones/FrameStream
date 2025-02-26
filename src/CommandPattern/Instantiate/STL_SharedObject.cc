// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      STL_SharedObject
// 
// Description: Instantiate STL classes for SharedObject*
//
//
// Author:      Martin Lohner
// Created:     Fri Jul 11 12:20:00 EDT 1997
// $Id: STL_SharedObject.cc,v 1.1 1998/06/17 18:17:26 mkl Exp $
//
// Revision history
//
// $Log: STL_SharedObject.cc,v $
// Revision 1.1  1998/06/17 18:17:26  mkl
// allow dynamic loading of source and sink formats
//
// Revision 1.3  1998/04/01 17:57:56  mkl
// switched to C++Std standard include area: fwd_string/istream/ostream
//
// Revision 1.2  1998/02/03 21:29:56  mkl
// switch over to STLUtility library
//
// Revision 1.1  1997/09/04 06:34:57  mkl
// moved JobControl/STL_SharedObject here
//
//


#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#if defined(OLD_CXX_STRING_CLASS_BUG)
#include "C++Std/fwd_string.h"
#include <String.h>
#else
#include <string>
#endif /* OLD_CXX_STRING_CLASS_BUG */

// user include files

#include <map>

class SharedObject ;

typedef string _map_key_ ;
typedef SharedObject* _map_contents_ ;
typedef less< _map_key_ > _map_compare_ ;

#include "STLUtility/instantiate_map.h"
