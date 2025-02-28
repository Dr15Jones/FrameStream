// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      T_vector_CompositeModule_ModuleInfo.cc
// 
// Description: Instantiate STL classes for Command
//
//
// Author:      Martin Lohner
// Created:     Thu Nov 11 12:00:00 EDT 1998
// $Id: T_vector_CompositeModule_ModuleInfo.cc,v 1.1 1998/11/12 22:24:03 mkl Exp $
//
// Revision history
//
// $Log: T_vector_CompositeModule_ModuleInfo.cc,v $
// Revision 1.1  1998/11/12 22:24:03  mkl
// finish new module loading and unloading
//
//

#include "Experiment/Experiment.h"
// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "CommandPattern/CompositeModule.h"

// stl includes
#include <vector>

typedef CompositeModule::ModuleInfo _vector_contents_;

#include "STLUtility/instantiate_vector.h"
