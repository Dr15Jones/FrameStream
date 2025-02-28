// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      T_vector_ModuleP
// 
// Description:
//
//
// Author:      Martin Lohner
// Created:     Sun Nov 1 12:00:00 EDT 1998
// $Id: T_vector_ModuleP.cc,v 1.1 1998/11/09 19:32:13 mkl Exp $
//
// Revision history
//
// $Log: T_vector_ModuleP.cc,v $
// Revision 1.1  1998/11/09 19:32:13  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
//

#include "Experiment/Experiment.h"
// system include files
#include <vector>

// user include files

class Module;
typedef Module* _vector_contents_;

#include "STLUtility/instantiate_vector.h"
