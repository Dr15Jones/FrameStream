// -*- C++ -*-
//
// Package:     DataDelivery
// Module:      ProxyDeliverer
// 
// Description: Manages the creation of DataFields
//
// Implimentation:
//     All the work is done in the concrete classes that inherit from
//     ProxyDeliverer
//
// Author:      Simon Patton
// Created:     Wed Oct 30 10:36:11 EST 1996
// $Id: ProxyDeliverer.cc,v 1.16 2000/03/22 16:24:37 mkl Exp $
//
// Revision history
//
// $Log: ProxyDeliverer.cc,v $
// Revision 1.16  2000/03/22 16:24:37  mkl
// when disabling stream: invalidate proxies in ProxyDeliverer, not in derived class
//
// Revision 1.15  1997/09/03 20:06:35  sjp
// Uses CPP macros for STL containers
//
// Revision 1.14  1997/09/01 15:35:21  sjp
// Changed report include to be in Experiment
//
// Revision 1.13  1997/08/27 03:39:30  sjp
// Updated to new name for bug flags
//
// Revision 1.12  1997/08/14 11:43:08  sjp
// Mods to run under CW Pro 1
//
// Revision 1.11  1997/08/06 15:57:21  sjp
// Modified to be a ProxyDeliverer
//
// Revision 1.10  1997/07/09 18:00:34  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.9  1997/06/03 17:29:35  sjp
// Made to be a subclass of DataProvider
//
// Revision 1.8  1997/05/07 19:00:28  sjp
// Fixed less<Stream::Type> so can be used as usual
//
// Revision 1.7  1997/05/02 19:36:17  cdj
// Added supplies() method
//
// Revision 1.6  1997/04/29 20:05:47  cdj
// replaced less< Stream::Type> with Stream::TypeLess
//
// Revision 1.5  1997/04/11 18:57:34  sjp
// Cleaned up message issuing
//
// Revision 1.4  1997/04/10 01:01:37  sjp
// Replaced resetSyncValue with extra argument in reset
//
// Revision 1.3  1997/04/04 16:36:24  sjp
// Moved generic functionality into Base class
//
// Revision 1.2  1997/03/29 16:16:50  sjp
// Complete first implementation
//
// Revision 1.1  1997/03/20 22:42:43  cdj
// First submission
//

#include "Experiment/Experiment.h"
// system include files
#include <stdlib.h>  // For 'exit'
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "DataHandler/StreamSet.h"
#include "DataHandler/SyncValue.h"
#include "DataHandler/Record.h"
#include "DataDelivery/ProxyDeliverer.h"


// STL classes
#include <vector>
#include <map>

//
// constants, enums and typedefs
//

const string kFacilityString = "DataDelivery.ProxyDeliverer" ;

typedef _proxydeliverer_syncvalues_ ValueMap ;

//
// static data member definitions
//

//
// constructors and destructor
//
ProxyDeliverer::ProxyDeliverer( const ProxyProvider::Identifier& aId ) :
   ProxyProvider( aId ) ,
   m_syncValues( *(new ValueMap ) )
{
   if ( 0 == &m_syncValues ) {
      report( EMERGENCY ,
	      kFacilityString )
		 << "Unable to allocate memory"
		 << endl ;
      delete &m_syncValues ;
      exit( 1 ) ;
   }
}

// ProxyDeliverer::ProxyDeliverer( const ProxyDeliverer& )
// {
// }

ProxyDeliverer::~ProxyDeliverer()
{
   delete &m_syncValues ;
}

//
// assignment operators
//
// const ProxyDeliverer& ProxyDeliverer::operator=( const ProxyDeliverer& )
// {
// }

//
// member functions
//

void
ProxyDeliverer::align( const Stream::Type& aStream ,
			   const SyncValue& aSyncValue )
{
   if ( aSyncValue == syncValue( aStream ) ) {
      enable( aStream ) ;
   }
   else {
      invalidateProxies( aStream );
      disable( aStream ) ;
   }
}

void
ProxyDeliverer::reset( const Stream::Type& aStream ,
			   const SyncValue& aSyncValue )
{
//
// set the new syncValue
//
   (*(m_syncValues.find( aStream ))).second = aSyncValue ;
//
// flush any cached information in DataFields and subclass of DataFieldDeliver
//
   resetCache( aStream ) ;
   invalidateProxies( aStream ) ;
}


void
ProxyDeliverer::registerStream( const Stream::Type& aStream )
{
   ProxyProvider::registerStream( aStream ) ;
   m_syncValues.insert( ValueMap::value_type( aStream , SyncValue() ) ) ;
}

//
// const member functions
//

const SyncValue&
ProxyDeliverer::syncValue( const Stream::Type& aStream ) const
{
   return ( (*(m_syncValues.find( aStream ))).second ) ;
}

const SyncValue&
ProxyDeliverer::latest( const Stream::Type& aStream ,
			    SyncValue& aCurrentLatest ,
			    const SyncValue& aLimit ) const
{
   const SyncValue& streamsSync( syncValue( aStream ) ) ;
   if ( ( aCurrentLatest < streamsSync ) &&
	( aLimit >= streamsSync ) ) {
      return ( streamsSync ) ;
   }
   else {
      return ( aCurrentLatest ) ;
   }
}

//
// static member functions
//
