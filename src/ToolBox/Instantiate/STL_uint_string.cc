// -*- C++ -*-
//
// Package:     ToolBox
// Module:      STL_int_string
// 
// Description: Instantiate classes for string paired with unsigned int
//
//
// Author:      Simon Patton
// Created:     Wed Sep 11 21:45:29 EDT 1996
// $Id: STL_uint_string.cc,v 1.4 1998/04/01 15:41:04 mkl Exp $
//
// Revision history
//
// $Log: STL_uint_string.cc,v $
// Revision 1.4  1998/04/01 15:41:04  mkl
// switched to C++Std standard include area: fwd_string/istream/ostream
//
// Revision 1.3  1998/02/03 21:30:41  mkl
// switch over to STLUtility library
//
// Revision 1.2  1997/08/06 14:42:55  sjp
// fixed a few typos
//
// Revision 1.1  1997/08/06 14:23:13  sjp
// Converted to use instantiation include files
//

#include "Experiment/Experiment.h"

// STL include files
#if defined(OLD_CXX_STRING_CLASS_BUG)
#include <string>
#include <String.h>
#else
#include <string>
#endif /* OLD_CXX_STRING_CLASS_BUG */
#include <map>

typedef std::string _map_key_ ;
typedef unsigned int _map_contents_ ;
typedef less< _map_key_ > _map_compare_ ;

#include "STLUtility/instantiate_map.h"
