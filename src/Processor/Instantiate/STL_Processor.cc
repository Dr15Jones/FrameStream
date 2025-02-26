// -*- C++ -*-
//
// Package:     Processor
// Module:      STL_Processor
// 
// Description: Instantiate STL classes for Processor*
//
//
// Author:      Martin Lohner
// Created:     Fri Jul 11 12:20:00 EDT 1997
// $Id: STL_Processor.cc,v 1.7 1998/04/01 17:57:55 mkl Exp $
//
// Revision history
//
// $Log: STL_Processor.cc,v $
// Revision 1.7  1998/04/01 17:57:55  mkl
// switched to C++Std standard include area: fwd_string/istream/ostream
//
// Revision 1.6  1998/02/03 21:29:55  mkl
// switch over to STLUtility library
//
// Revision 1.5  1997/08/29 04:19:36  mkl
// bug flag name change
//
// Revision 1.4  1997/08/17 03:09:49  mkl
// make g++ happy: add string header
//
// Revision 1.3  1997/08/15 08:27:24  mkl
// switched to *instantiate files
//
// Revision 1.2  1997/07/22 05:21:04  mkl
// use factory method for statically linked processors
//
// Revision 1.1  1997/07/11 20:40:03  mkl
// STL instantiation files added
//
//


#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#if defined(OLD_CXX_STRING_CLASS_BUG)
#include "C++Std/fwd_string.h"
#include <String.h>
#else
#include <string>
#endif /* OLD_CXX_STRING_CLASS_BUG */
#include <map>

// user include files

class Processor ;

typedef string _map_key_;
typedef Processor* _map_contents_;
typedef less< _map_key_ > _map_compare_;

#include "STLUtility/instantiate_map.h"
