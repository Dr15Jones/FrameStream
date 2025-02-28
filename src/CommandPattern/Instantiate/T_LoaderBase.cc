// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      T_LoaderBase
// 
// Description: Instantiate LoaderBase<>
//
//
// Author:      Martin Lohner
// Created:     Mon Oct 26 12:20:00 EDT 1998
// $Id: T_LoaderBase.cc,v 1.3 2003/08/26 18:50:10 vk Exp $
//
// Revision history
//
// $Log: T_LoaderBase.cc,v $
// Revision 1.3  2003/08/26 18:50:10  vk
// Remove LoaderBase<SinkFormat>/LoaderBase<SourceFormat> since it cause multiple symbol definition on OSF. Those are defined in JobControl/Instantiate/T_LoaderBase.cc
//
// Revision 1.2  2003/08/25 17:16:20  vk
// Instantiate LoaderBase<SinkFormat>/LoaderBase<SourceFormat> to make OSF happy
//
// Revision 1.1  2003/03/12 21:38:50  vk
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
#include "DataStorage/SinkFormat.h"
#include "DataDelivery/SourceFormat.h"
#include "CommandPattern/Module.h"
#include "CommandPattern/Template/LoaderBase.cc"

// stl includes
#include <string>
#include <vector>
#include <map>
#include <set>

template class LoaderBase< Module >;

