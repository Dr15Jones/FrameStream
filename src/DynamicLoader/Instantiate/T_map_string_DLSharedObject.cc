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
// $Id: T_map_string_DLSharedObject.cc,v 1.1.1.1 2000/11/30 20:51:31 cdj Exp $
//
// Revision history
//
// $Log: T_map_string_DLSharedObject.cc,v $
// Revision 1.1.1.1  2000/11/30 20:51:31  cdj
// imported DynamicLoader source
//
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

// user include files

#include <map>
#include <string>

class DLSharedObject ;

typedef std::string _map_key_ ;
typedef DLSharedObject* _map_contents_ ;
typedef less< _map_key_ > _map_compare_ ;

#include "STLUtility/instantiate_map.h"
