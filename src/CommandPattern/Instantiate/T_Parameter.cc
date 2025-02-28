// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      T_RawHitProxy
// 
// Description: Instantiate all Parameter<T> specializations
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Tue Mar 10 11:32:44 EDT 1998
// $Id: T_Parameter.cc,v 1.9 2002/08/16 14:15:24 cleo3 Exp $
//
// Revision history
//
// $Log: T_Parameter.cc,v $
// Revision 1.9  2002/08/16 14:15:24  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.8  2000/07/28 17:03:49  mkl
// preserve tcl grouping with curly brackets in vector parameters
//
// Revision 1.7  2000/01/04 20:53:37  mkl
// now print type with parameter value
//
// Revision 1.6  1999/10/25 18:50:06  mkl
// fixed wrong logic for Parameter< bool > instantiation
//
// Revision 1.5  1999/06/24 20:19:56  mkl
// added Parameter< short > and Parameter< unsigned short > instantiations
//
// Revision 1.4  1998/11/12 22:23:45  mkl
// finish new module loading and unloading
//
// Revision 1.3  1998/03/15 00:08:18  mkl
// Parameter< vector< T > >
//
// Revision 1.2  1998/03/12 15:03:45  mkl
// typo in g++ template instantiation
//
// Revision 1.1  1998/03/11 19:10:44  mkl
// new Parameter sources
//
//

#include "Experiment/Experiment.h"
#include "Experiment/types.h"

// system include files
#include "C++Std/iostream.h"
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "CommandPattern/Template/Parameter.cc"
#include "CommandPattern/Template/Parameter_special.cc"

// STL classes
#include <string>
#include <vector>

INSTANTIATE_PARAMETER( float )
INSTANTIATE_PARAMETER( double )
INSTANTIATE_PARAMETER( char )
INSTANTIATE_PARAMETER( short )
INSTANTIATE_PARAMETER( unsigned short )
INSTANTIATE_PARAMETER( int )
INSTANTIATE_PARAMETER( unsigned int )
INSTANTIATE_PARAMETER( long )
INSTANTIATE_PARAMETER( unsigned long )
INSTANTIATE_PARAMETER( string )
#if !defined(BOOL_NOT_DEFINED_BUG)
INSTANTIATE_PARAMETER( DABoolean )
#endif
INSTANTIATE_PARAMETER_VECTOR( float )
INSTANTIATE_PARAMETER_VECTOR( double )
INSTANTIATE_PARAMETER_VECTOR( char )
INSTANTIATE_PARAMETER_VECTOR( short )
INSTANTIATE_PARAMETER_VECTOR( unsigned short )
INSTANTIATE_PARAMETER_VECTOR( int )
INSTANTIATE_PARAMETER_VECTOR( unsigned int )
INSTANTIATE_PARAMETER_VECTOR( long )
INSTANTIATE_PARAMETER_VECTOR( unsigned long )
INSTANTIATE_PARAMETER_VECTOR_STRING
#if !defined(BOOL_NOT_DEFINED_BUG)
INSTANTIATE_PARAMETER_VECTOR( DABoolean )
#endif

