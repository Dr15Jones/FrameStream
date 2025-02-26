// -*- C++ -*-
//
// Package:     JobControl
// Module:      T_LoaderCommand_SinkFormatMap.cc
// 
// Description: Instantiate LoaderCommand<>
//
//
// Author:      Martin Lohner
// Created:     Mon Nov 9 12:20:00 EDT 1998
// $Id: T_LoaderCommand_SinkFormatMap.cc,v 1.3 1998/12/02 05:55:25 mkl Exp $
//
// Revision history
//
// $Log: T_LoaderCommand_SinkFormatMap.cc,v $
// Revision 1.3  1998/12/02 05:55:25  mkl
// towards interacting with Source- and SinkFormats
//
// Revision 1.2  1998/11/12 02:25:01  mkl
// minor cleanup
//
// Revision 1.1  1998/11/10 03:52:26  mkl
// unify producer/processor/module/source_format/sink_format commands
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <set>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "JobControl/SinkFormatMap.h"
#include "CommandPattern/Template/LoaderCommand.cc"

// stl includes
#include <vector>
#include <set>

// override interactHandler()
static const char* const kFacilityString 
= "JobControl::LoaderCommand< SinkFormatMap >";

template<> int
LoaderCommand< SinkFormatMap >::interactHandler()
{
   report( ERROR, kFacilityString ) 
      << "Sorry -- can't interact yet (soon)!" << endl;
   return COMMAND_OK;
}

template class LoaderCommand< SinkFormatMap >;
