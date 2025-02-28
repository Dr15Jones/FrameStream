// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      T_MultiLoader
// 
// Description: Instantiate MultiLoader<>
//
//
// Author:      Martin Lohner
// Created:     Mon Oct 26 12:20:00 EDT 1998
// $Id: T_MultiLoader.cc,v 1.1 2003/03/12 21:38:51 vk Exp $
//
// Revision history
//
// $Log: T_MultiLoader.cc,v $
// Revision 1.1  2003/03/12 21:38:51  vk
// Redesign loader class into LoaderBase, Loader (single loader) and MultiLoader
//
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
#include "CommandPattern/Template/MultiLoader.cc"

// stl includes
#include <string>
#include <vector>
#include <map>
#include <set>

template class MultiLoader< Module >;

