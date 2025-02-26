// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      STL_vecDouble
// 
// Description: Instantiate STL classes for simple types: double
//
//
// Author:      Martin Lohner
// Created:     Fri March 14 18:48:00 EDT 1998
// $Id: STL_vecDouble.cc,v 1.1 1998/03/15 00:07:23 mkl Exp $
//
// Revision history
//
// $Log: STL_vecDouble.cc,v $
// Revision 1.1  1998/03/15 00:07:23  mkl
// instantiation for all Parameter< vector< T > > templates
//
//

#include "Experiment/Experiment.h"
// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files

typedef double _vector_contents_;
#include "STLUtility/instantiate_vector.h"
