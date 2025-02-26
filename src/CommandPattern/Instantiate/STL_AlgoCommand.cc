// -*- C++ -*-
//
// Package:     Module
// Module:      STL_Module
// 
// Description: Instantiate STL classes for Module
//
//
// Author:      Martin Lohner
// Created:     Thu Oct 30 12:00:00 EDT 1997
// $Id: STL_AlgoCommand.cc,v 1.2 1999/04/12 19:24:42 bkh Exp $
//
// Revision history
//
// $Log: STL_AlgoCommand.cc,v $
// Revision 1.2  1999/04/12 19:24:42  bkh
// Use new instantiate header for for_each
//
// Revision 1.1  1998/11/09 19:32:03  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.4  1998/03/15 00:07:22  mkl
// instantiation for all Parameter< vector< T > > templates
//
// Revision 1.3  1998/02/03 21:28:05  mkl
// switch over to STLUtility library
//
// Revision 1.2  1997/11/24 18:35:55  mkl
// new StringWrapper class to get around g++ proboem with map<string, string>
//
// Revision 1.1  1997/11/01 21:58:33  mkl
// delete vector<Command*> properly
//
//

#include "Experiment/Experiment.h"
// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <algorithm>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files

#include "CommandPattern/Command.h"

typedef Command*                 _for_each_element_type_  ;
typedef _for_each_element_type_* _for_each_iterator_      ;
typedef void                     _for_each_function_type_ ;

#include "STLUtility/instantiate_for_each.h"
