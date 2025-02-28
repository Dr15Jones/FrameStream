// -*- C++ -*-
//
// Package:     Scaffold
// Module:      CombinatoricList
// 
// Description: Instantiate the vector< const int* >
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Simon Patton
// Created:     Wed Sep 11 21:45:29 EDT 1996
// $Id: STL_int.cc,v 1.5 1998/02/03 21:30:40 mkl Exp $
//
// Revision history
//
// $Log: STL_int.cc,v $
// Revision 1.5  1998/02/03 21:30:40  mkl
// switch over to STLUtility library
//
// Revision 1.4  1997/08/06 14:23:06  sjp
// Converted to use instantiation include files
//
// Revision 1.3  1997/07/10 20:24:46  sjp
// Added extra instantiations for cxx
//
// Revision 1.2  1997/07/07 16:15:08  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.1  1997/07/01 20:00:29  sjp
// New file to instantiate STL classes
//

#include "Experiment/Experiment.h"
// system include files

// user include files

// STL include files
#include <vector>

typedef int _vector_contents_ ;

#include "STLUtility/instantiate_vector.h"
