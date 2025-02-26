// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      T_NamingService_Module
// 
// Description: Instantiate NamingService< Module >
//
//
// Author:      Martin Lohner
// Created:     Mon Feb 21 12:20:00 EDT 1999
// $Id: T_NamingService_Module.cc,v 1.1 1999/02/22 23:40:57 mkl Exp $
//
// Revision history
//
// $Log: T_NamingService_Module.cc,v $
// Revision 1.1  1999/02/22 23:40:57  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "CommandPattern/Module.h"
#include "CommandPattern/Template/NamingService.cc"

// stl includes
#include <string>
#include <map>

template class NamingService< Module >;

