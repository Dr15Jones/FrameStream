// -*- C++ -*-
//
// Package:     Processor
// Module:      T_MasterProducer
// 
// Description: Instantiate Loader< Producer >
//
//
// Author:      Martin Lohner
// Created:     Mon Oct 26 12:20:00 EDT 1998
// $Id: T_MasterProducer.cc,v 1.2 2000/12/01 20:32:38 cdj Exp $
//
// Revision history
//
// $Log: T_MasterProducer.cc,v $
// Revision 1.2  2000/12/01 20:32:38  cdj
// updated to work with DynamicLoader package
//
// Revision 1.1  1998/11/09 19:34:45  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <vector>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Processor/Producer.h"
#include "CommandPattern/Template/Loader.cc"
#include "DynamicLoader/Template/DLFactoryManager.cc"

// stl includes
#include <string>
#include <vector>
#include <map>

template class Loader< Producer >;
template class DLFactoryManager< Producer >;
