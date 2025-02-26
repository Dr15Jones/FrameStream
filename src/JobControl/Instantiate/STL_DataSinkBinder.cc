// -*- C++ -*-
//
// Package:     JobControl
// Module:      STL_DataSinkBinder
// 
// Description: Instantiate STL classes for DataSinkBinder*
//
//
// Author:      Martin Lohner
// Created:     Fri Jul 11 12:20:00 EDT 1997
// $Id: STL_DataSinkBinder.cc,v 1.5 1998/04/01 17:59:43 mkl Exp $
//
// Revision history
//
// $Log: STL_DataSinkBinder.cc,v $
// Revision 1.5  1998/04/01 17:59:43  mkl
// switched to C++Std standard include area: fwd_string/istream/ostream
//
// Revision 1.4  1998/02/03 21:29:34  mkl
// switch over to STLUtility library
//
// Revision 1.3  1997/08/29 04:22:05  mkl
// simplify JobControl: remove FileInput/Output files, bug flag changes, handling of suffix .gz etc.
//
// Revision 1.2  1997/08/13 07:10:58  mkl
// Chains of Sources, new activation of streams, and ProxyDict
//
// Revision 1.1  1997/07/11 20:40:24  mkl
// STL instantiation files added
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
#include "DataHandler/Stream.h"

#include <map>

class DataSinkBinder ;

typedef string _map_key_ ;
typedef DataSinkBinder* _map_contents_ ;
typedef less< _map_key_ > _map_compare_ ;

#include "STLUtility/instantiate_map.h"
