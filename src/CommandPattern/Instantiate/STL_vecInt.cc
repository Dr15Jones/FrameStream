// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      STL_vecInt
// 
// Description: Instantiate STL classes for simple types: int
//
//
// Author:      Martin Lohner
// Created:     Fri March 14 18:48:00 EDT 1998
// $Id: STL_vecInt.cc,v 1.1 1998/03/15 00:07:25 mkl Exp $
//
// Revision history
//
// $Log: STL_vecInt.cc,v $
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

typedef int _vector_contents_;
#include "STLUtility/instantiate_vector.h"
