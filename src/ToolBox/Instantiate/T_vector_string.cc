// -*- C++ -*-
//
// Package:     ToolBox
// Module:      T_vector_string
// 
// Description: Instantiate vector< string >
//
// Author:      Martin Lohner
// Created:     Tue Dec 8 18:20:23 EDT 1998
// $Id: T_vector_string.cc,v 1.1 1998/12/09 00:14:40 mkl Exp $
//
// Revision history
//
// $Log: T_vector_string.cc,v $
// Revision 1.1  1998/12/09 00:14:40  mkl
// split STL_string.cc into three files which do one and only instantiation
// (else "multiply-defined symbols" link errors could occur when a user
// instantiated one piece, but need to pull in STL_string.o for another).
//
//

#include "Experiment/Experiment.h"

// system include files

// STL include files
#include <string>
#include <vector>

typedef string _vector_contents_ ;
#include "STLUtility/instantiate_vector.h"

