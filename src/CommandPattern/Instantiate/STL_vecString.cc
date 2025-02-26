// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      STL_vecString
// 
// Description: Instantiate STL classes for simple types: string
//
//
// Author:      Martin Lohner
// Created:     Fri March 14 18:48:00 EDT 1998
// $Id: STL_vecString.cc,v 1.1 1998/03/15 00:07:26 mkl Exp $
//
// Revision history
//
// $Log: STL_vecString.cc,v $
// Revision 1.1  1998/03/15 00:07:26  mkl
// instantiation for all Parameter< vector< T > > templates
//
//

#include "Experiment/Experiment.h"
// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files

// already defined in ToolBox
#if 0
typedef string _vector_contents_;
#include "STLUtility/instantiate_vector.h"
#endif
