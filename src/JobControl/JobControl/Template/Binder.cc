#if !defined(JOBCONTROL_BINDER_CC)
#define JOBCONTROL_BINDER_CC

// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      Binder
// 
// Description: <one line class summary>
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Mon Aug  4 17:32:09 EDT 1997
// $Id: Binder.cc,v 1.8 1999/02/22 23:41:53 mkl Exp $
//
// Revision history
//
// $Log: Binder.cc,v $
// Revision 1.8  1999/02/22 23:41:53  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.7  1998/11/24 22:08:51  mkl
// introduce int-receiving ctor to allow for fake initialization to avoid compiler warnings
//
// Revision 1.6  1998/10/20 16:04:37  mkl
// more meaningful error message about unable to chain sources of type
//
// Revision 1.5  1998/09/23 19:01:19  mkl
// typename; protect against multiple inclusion. All the make egcs happy
//
// Revision 1.4  1998/09/16 21:36:24  mkl
// use new bug flag for static/extern linkage of kFacilityStrings in Template .cc files
//
// Revision 1.3  1998/09/11 18:45:56  mkl
// rename kFacilityString to avoid clashes
//
// Revision 1.2  1998/09/11 16:15:40  mkl
// g++ wants 'typename' hint
//
// Revision 1.1  1998/06/17 18:18:27  mkl
// allow dynamic loading of source and sink formats
//
// Revision 1.2  1997/10/07 19:25:12  mkl
// cout --> report( INFO ) and kFacilityString update
//
// Revision 1.1  1997/08/08 05:20:57  mkl
// first attempt at chains-of-files
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "Experiment/report.h"

#include "JobControl/Binder.h"
#include "JobControl/Binder_makeChain.h"
#include "JobControl/Binder_makeChainNotChainable.h"
#include "DataDelivery/DataSourceBinder.h"
#include "ChainDelivery/ChainSourceBinder.h"

// STL classes

//
// constants, enums and typedefs
//
FILESCOPE_IN_TEMPLATE_CC_BUG const char* const kBinderFacilityString 
= "JobControl.Binder";

//
// static data member definitions
//

//
// constructors and destructor
//
template< class DataBinder >
Binder<DataBinder>::Binder(  DataBinder* DSB, BinderBase::Type type )
   : BinderBase( DSB, type )
{
}

// Binder::Binder( const Binder& )
// {
// }

template< class DataBinder >
Binder<DataBinder>::~Binder()
{
}

//
// assignment operators
//
// const Binder& Binder::operator=( const Binder& )
// {
// }

//
// member functions
//
template< class DataBinder >
DABoolean
Binder<DataBinder>::addBinder( BinderBase* iBinder )
{
   DABoolean returnValue = false;

   // make sure the types of binders agree
   if( type() != iBinder->type() ) {
      report( ERROR, kBinderFacilityString )
	 << "can't combine binders of different types!" << endl;
      return returnValue = false;
   }

   // if we're already a chain, just add
   if( true == isChain() ) {
      addSourceToChain( dsBinder(), iBinder->dsBinder() );
      returnValue = true;
   }
   else { // need to make chain
      DataSourceBinder* csb = makeChain( dsBinder().dataSourceID(),
					 dsBinder().boundStreams() );
      if( 0 != csb ) {
	 addSourceToChain( *csb, dsBinder() );
	 addSourceToChain( *csb, iBinder->dsBinder() );
	 setDSBinder( csb );
	 setChainFlag( true );
	 returnValue = true;
      }
      else {
	 report( ERROR, kBinderFacilityString )
	    << "can't chain sources of this type" << endl;
	 returnValue = false;
      }
   }

   return returnValue;
}

template< class DataBinder >
DataSourceBinder*
Binder<DataBinder>::makeChain( const string& iName,
			       const Stream::Set& iBindStreams )
{
   // initialization to zero is only fake to avoid compiler warnings
   // type is only used to select proper overloaded function
   typename DataBinder::Chainability chainability = 0;
   return ::makeChain( chainability,
		       iName,
		       iBindStreams );
}

template< class DataBinder >
void
Binder<DataBinder>::addSourceToChain( DataSourceBinder& ioChainBinder,
				      DataSourceBinder& iDataBinder )
{
   // initialization to zero is only fake to avoid compiler warnings
   // type is only used to select proper overloaded function
   typename DataBinder::Chainability chainability = 0;
   ::addSourceToChain( chainability,
		       ioChainBinder,
		       iDataBinder );
}

//
// const member functions
//

//
// static member functions
//
#endif /* JOBCONTROL_BINDER_CC */
