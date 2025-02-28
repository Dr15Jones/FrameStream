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
// $Id: STL_vecUShort.cc,v 1.1 1999/06/28 02:15:05 mkl Exp $
//
// Revision history
//
// $Log: STL_vecUShort.cc,v $
// Revision 1.1  1999/06/28 02:15:05  mkl
// had to add instantiation for vector< unsigned short > as well
//
//

#include "Experiment/Experiment.h"
// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files

typedef unsigned short _vector_contents_;
#include "STLUtility/instantiate_vector.h"
