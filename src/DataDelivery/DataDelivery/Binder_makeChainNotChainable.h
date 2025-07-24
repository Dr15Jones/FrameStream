#if !defined(JOBCONTROL_BINDER_MAKECHAINNOTCHAINABLE_H)
#define JOBCONTROL_BINDER_MAKECHAINNOTCHAINABLE_H
// -*- C++ -*-
//
// Package:     JobControl
// Module:      Binder_makeChainNotChainable
// 
// Description: external makeChain function -- NotChainable version
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Mon May 25 17:31:59 EDT 1998
// $Id: Binder_makeChainNotChainable.h,v 1.1 1998/06/17 18:18:19 mkl Exp $
//
// Revision history
//
// $Log: Binder_makeChainNotChainable.h,v $
// Revision 1.1  1998/06/17 18:18:19  mkl
// allow dynamic loading of source and sink formats
//
//

// system include files

// user include files
#include "DataDelivery/Chainability.h"
#include "DataHandler/Stream.h"

// forward declarations
class DataSourceBinder;

DataSourceBinder*
makeChain( NotChainable,
	   const std::string&,
	   const Stream::Set& );

void
addSourceToChain( NotChainable,
		  DataSourceBinder& ioChainBinder,
		  DataSourceBinder& iDataBinder );

#endif /* JOBCONTROL_BINDER_MAKECHAINNOTCHAINABLEH */

