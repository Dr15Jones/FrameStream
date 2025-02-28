// -*- C++ -*-
//
// Package:     DataStorage
// Module:      DataSinkController
// 
// Description: <one line class summary>
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Chris D. Jones
// Created:     Sun May 25 16:55:23 EDT 1997
// $Id: DataSinkController.cc,v 1.5 2003/04/25 15:32:16 vk Exp $
//
// Revision history
//
// $Log: DataSinkController.cc,v $
// Revision 1.5  2003/04/25 15:32:16  vk
// Add identifiers to the ProxyServer. Add entry to the DAExceptionStack.
//
// Revision 1.4  1997/09/18 21:13:09  cdj
// Changed Boolean to DABoolean
//
// Revision 1.3  1997/08/16 17:45:33  cdj
// Modified to work with Proxies
//
// Revision 1.2  1997/07/11 06:20:09  mkl
// // New <Package>/<File>.h structure
// // Modified so can also compile under cxx v5.5
//
// Revision 1.1.1.1  1997/05/30 15:41:36  cdj
// First submission
//

#include "Experiment/Experiment.h"
// system include files
#include <assert.h>

// user include files
#include "DataStorage/DataSinkController.h"
#include "DataStorage/ProxyStorer.h"
#include "DataHandler/StreamSet.h"


// STL classes

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
DataSinkController::DataSinkController( void ):
   m_storeStreams( *(new Stream::Set) ),
   m_initializationStatus(DataSinkController::kInitNoError),
   m_proxyStorer(0)
{
}

// DataSinkController::DataSinkController( const DataSinkController& )
// {
// }

DataSinkController::~DataSinkController()
{
   delete &m_storeStreams;
   delete m_proxyStorer;
}

//
// assignment operators
//
// const DataSinkController& DataSinkController::operator=( const DataSinkController& )
// {
// }

//
// member functions
//
DABoolean 
DataSinkController::setRecordsToStore( const Stream::Set& iStore )
{
   //Check to make sure that the sink can deliver all the records that
   //  are being requested
   DABoolean isOK( potentialRecordsToStore().contains( iStore ) );

   if( isOK ){
      m_storeStreams = iStore;
   } else {
      clearRecordsToStore();
   }

   return isOK;
}
void 
DataSinkController::clearRecordsToStore( void )
{
   m_storeStreams.erase( m_storeStreams.begin(),
			m_storeStreams.end());
   m_storeStreams.insert( Stream::kNone );
}

void 
DataSinkController::setInitializationStatus( 
   DataSinkController::InitializationStatus iStatus )
{
   m_initializationStatus = iStatus;
}
//
// const member functions
//

const Stream::Set
DataSinkController::potentialRecordsToStore( void ) const
{
   //Get this info from the ProxyStorer
   return (*(proxyStorer())).stores();
}

const Stream::Set& 
DataSinkController::recordsToStore( void ) const
{
   return m_storeStreams;
}


DataSinkController::InitializationStatus
DataSinkController::initializationStatus( void ) const
{
   return m_initializationStatus;
}

ProxyStorer*
DataSinkController::proxyStorer( void ) const
{
   if( 0 == m_proxyStorer ){
      //until mutable, we need to cast away the const
      (*((DataSinkController*) this)).m_proxyStorer =
	 createProxyStorer();
      // assign id & parameters
      m_proxyStorer->setDataSinkId(dataSinkID());
      m_proxyStorer->setParamId(parameters());
      assert( 0 != m_proxyStorer);
   }
   return m_proxyStorer;
}

//
// static member functions
//
