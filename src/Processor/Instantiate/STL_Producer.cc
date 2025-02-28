// -*- C++ -*-
//
// Package:     Producer
// Module:      STL_Producer
// 
// Description: Instantiate STL classes for Producer*
//
//
// Author:      Martin Lohner
// Created:     Thu Jan 15 12:20:00 EDT 1998
// $Id: STL_Producer.cc,v 1.3 1998/04/01 17:57:55 mkl Exp $
//
// Revision history
//
// $Log: STL_Producer.cc,v $
// Revision 1.3  1998/04/01 17:57:55  mkl
// switched to C++Std standard include area: fwd_string/istream/ostream
//
// Revision 1.2  1998/02/03 21:29:56  mkl
// switch over to STLUtility library
//
// Revision 1.1  1998/01/16 23:33:18  mkl
// added MasterProducer for selecting Producers at run time
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

class Producer ;

typedef string _map_key_;
typedef Producer* _map_contents_;
typedef less< _map_key_ > _map_compare_;

#include "STLUtility/instantiate_map.h"
