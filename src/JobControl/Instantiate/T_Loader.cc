// -*- C++ -*-
//
// Package:     JobControl
// Module:      T_Loader
// 
// Description: Instantiate Loader<>
//
//
// Author:      Martin Lohner
// Created:     Mon Oct 26 12:20:00 EDT 1998
// $Id: T_Loader.cc,v 1.4 2003/02/20 18:45:02 cdj Exp $
//
// Revision history
//
// $Log: T_Loader.cc,v $
// Revision 1.4  2003/02/20 18:45:02  cdj
// fixed improper casting of Source(Sink)Format to Source(Sink)FormatModule
//
// Revision 1.3  2000/12/01 20:30:54  cdj
// updated to work with DynamicLoader package
//
// Revision 1.2  1998/12/02 05:55:19  mkl
// towards interacting with Source- and SinkFormats
//
// Revision 1.1  1998/11/09 19:33:21  mkl
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
#include "DataDelivery/SourceFormat.h"
#include "DataStorage/SinkFormat.h"
#include "CommandPattern/Template/Loader.cc"

// stl includes
#include <string>
#include <vector>
#include <map>
#include <set>

template class Loader< SourceFormat >;
template class Loader< SinkFormat >;

#include "DynamicLoader/Template/DLFactoryManager.cc"
template class DLFactoryManager< SourceFormat >;
template class DLFactoryManager< SinkFormat >;
