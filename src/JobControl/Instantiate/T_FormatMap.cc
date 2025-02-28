// -*- C++ -*-
//
// Package:     JobControl
// Module:      T_FormatMap
// 
// Description: Instantiate different FormatMaps
//
//
// Author:      Martin Lohner
// Created:     Fri Oct 26 12:20:00 EDT 1998
// $Id: T_FormatMap.cc,v 1.3 2003/02/20 18:45:01 cdj Exp $
//
// Revision history
//
// $Log: T_FormatMap.cc,v $
// Revision 1.3  2003/02/20 18:45:01  cdj
// fixed improper casting of Source(Sink)Format to Source(Sink)FormatModule
//
// Revision 1.2  1998/12/02 05:55:18  mkl
// towards interacting with Source- and SinkFormats
//
// Revision 1.1  1998/11/09 19:33:20  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <map>
#include <set>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "JobControl/FormatMap.h"
#include "DataDelivery/SourceFormat.h"
#include "DataStorage/SinkFormat.h"

// stl includes
#include <string>
#include <map>
#include <set>

template class FormatMap< SourceFormat >;
template class FormatMap< SinkFormat >;
