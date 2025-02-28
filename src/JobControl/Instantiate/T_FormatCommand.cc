// -*- C++ -*-
//
// Package:     JobControl
// Module:      T_FormatCommand
// 
// Description: Instantiate different FormatCommands
//
//
// Author:      Martin Lohner
// Created:     Fri Oct 26 12:20:00 EDT 1998
// $Id: T_FormatCommand.cc,v 1.2 1998/11/10 03:52:25 mkl Exp $
//
// Revision history
//
// $Log: T_FormatCommand.cc,v $
// Revision 1.2  1998/11/10 03:52:25  mkl
// unify producer/processor/module/source_format/sink_format commands
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
#include "JobControl/Template/FormatCommand.cc"
#include "JobControl/SourceFormatMap.h"
#include "JobControl/SinkFormatMap.h"

// stl includes
#include <string>
#include <map>
#include <set>

template class FormatCommand< SourceFormatMap >;
template class FormatCommand< SinkFormatMap >;
