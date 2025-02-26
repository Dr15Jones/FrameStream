// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      Binder_makeChainNotChainable
// 
// Description: <one line class summary>
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Mon May 25 17:32:09 EDT 1998
// $Id: Binder_makeChainNotChainable.cc,v 1.1 1998/06/17 18:18:05 mkl Exp $
//
// Revision history
//
// $Log: Binder_makeChainNotChainable.cc,v $
// Revision 1.1  1998/06/17 18:18:05  mkl
// allow dynamic loading of source and sink formats
//
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "Experiment/report.h"

#include "JobControl/Binder_makeChainNotChainable.h"
#include "DataDelivery/DataSourceBinder.h"

// STL classes

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "JobControl.Binder_makeChain";

//
// static data member definitions
//

DataSourceBinder*
makeChain( NotChainable,
	   const string&,
	   const Stream::Set& )
{
   return 0;
}

void
addSourceToChain( NotChainable,
		  DataSourceBinder& ioChainBinder,
		  DataSourceBinder& iDataBinder )
{
}


