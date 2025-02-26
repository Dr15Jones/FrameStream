// -*- C++ -*-
//
// Package:     Processor
// Module:      T_LoaderCommand_MasterProducer.cc
// 
// Description: Instantiate LoaderCommand<>
//
//
// Author:      Martin Lohner
// Created:     Mon Nov 9 12:20:00 EDT 1998
// $Id: T_LoaderCommand_MasterProducer.cc,v 1.1 1998/11/10 03:52:34 mkl Exp $
//
// Revision history
//
// $Log: T_LoaderCommand_MasterProducer.cc,v $
// Revision 1.1  1998/11/10 03:52:34  mkl
// unify producer/processor/module/source_format/sink_format commands
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Processor/MasterProducer.h"
#include "CommandPattern/Template/LoaderCommand.cc"

// stl includes
#include <vector>

template class LoaderCommand< MasterProducer >;

