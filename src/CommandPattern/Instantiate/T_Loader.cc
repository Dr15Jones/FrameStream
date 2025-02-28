// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      T_Loader
// 
// Description: Instantiate Loader<>
//
//
// Author:      Martin Lohner
// Created:     Mon Oct 26 12:20:00 EDT 1998
// $Id: T_Loader.cc,v 1.1 1998/11/09 19:32:09 mkl Exp $
//
// Revision history
//
// $Log: T_Loader.cc,v $
// Revision 1.1  1998/11/09 19:32:09  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <vector>
#include <map>
#include <set>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "CommandPattern/Module.h"
#include "CommandPattern/Template/Loader.cc"

// stl includes
#include <string>
#include <vector>
#include <map>
#include <set>

template class Loader< Module >;

