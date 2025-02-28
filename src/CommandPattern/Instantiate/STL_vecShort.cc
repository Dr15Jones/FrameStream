// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      STL_vecShort
// 
// Description: Instantiate STL classes for simple types: short
//
//
// Author:      Martin Lohner
// Created:     Fri March 14 18:48:00 EDT 1998
// $Id: STL_vecShort.cc,v 1.1 1999/06/27 16:24:04 lkg Exp $
//
// Revision history
//
// $Log: STL_vecShort.cc,v $
// Revision 1.1  1999/06/27 16:24:04  lkg
// Add instantiation file for vector< short >, presumably needed for the
// new Parameter< short > type
//
// Revision 1.1  1998/03/15 00:07:25  mkl
// instantiation for all Parameter< vector< T > > templates
//
//

#include "Experiment/Experiment.h"
// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files

typedef short _vector_contents_;
#include "STLUtility/instantiate_vector.h"
