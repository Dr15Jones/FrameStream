#if !defined(JOBCONTROL_BINDER_MAKECHAIN_H)
#define JOBCONTROL_BINDER_MAKECHAIN_H
// -*- C++ -*-
//
// Package:     JobControl
// Module:      Binder_MakeChain
// 
// Description: external makeChain functions
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Mon May 25 17:31:59 EDT 1998
// $Id: Binder_makeChain.h,v 1.3 2002/12/06 16:24:46 cleo3 Exp $
//
// Revision history
//
// $Log: Binder_makeChain.h,v $
// Revision 1.3  2002/12/06 16:24:46  cleo3
// added typename
//
// Revision 1.2  1998/07/18 20:20:48  mkl
// typedef-not-protected-by-class-name-space bug
//
// Revision 1.1  1998/06/17 18:18:18  mkl
// allow dynamic loading of source and sink formats
//
//

// system include files

// user include files
#include "DataDelivery/Chainability.h"
#include "DataHandler/Stream.h"
#include "ChainDelivery/ChainSourceBinder.h"

// forward declarations
class DataSourceBinder;

template< class T >
DataSourceBinder*
makeChain( Chainable<T>,
  	   const std::string& iName,
	   const Stream::Set& iBindStreams )
{
   typedef typename Chainable<T>::DataBinderType BinderType;
   return new ChainSourceBinder< BinderType >( iName, iBindStreams );
}

template< class T >
void
addSourceToChain( Chainable<T>,
		  DataSourceBinder& ioChainBinder,
		  DataSourceBinder& iDataBinder )
{
   typedef typename Chainable<T>::DataBinderType BinderType;
   ((ChainSourceBinder< BinderType >&)ioChainBinder).
      addSource( (BinderType&)iDataBinder );

}

#endif /* JOBCONTROL_BINDER_H */

