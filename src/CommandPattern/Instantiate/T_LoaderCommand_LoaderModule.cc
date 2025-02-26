// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      T_LoaderCommand_LoaderModule
// 
// Description: Instantiate Loader<>
//
//
// Author:      Martin Lohner
// Created:     Mon Oct 26 12:20:00 EDT 1998
// $Id: T_LoaderCommand_LoaderModule.cc,v 1.2 2000/12/01 20:23:29 cdj Exp $
//
// Revision history
//
// $Log: T_LoaderCommand_LoaderModule.cc,v $
// Revision 1.2  2000/12/01 20:23:29  cdj
// now uses DynamicLoader package
//
// Revision 1.1  1998/11/10 03:54:20  mkl
// unify producer/processor/module/source_format/sink_format commands
//
// Revision 1.1  1998/11/09 19:32:09  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "CommandPattern/LoaderModule.h"
#include "CommandPattern/Template/LoaderCommand.cc"

// stl includes
#include <vector>

template class LoaderCommand< LoaderModule >;

