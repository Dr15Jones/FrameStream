// -*- C++ -*-
//
// Package:     DataStorage
// Module:      DataSinkDescriptor
// 
// Description: <one line class summary>
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Chris D. Jones
// Created:     Sun May 25 16:55:40 EDT 1997
// $Id: DataSinkDescriptor.cc,v 1.3 1997/09/18 21:13:11 cdj Exp $
//
// Revision history
//
// $Log: DataSinkDescriptor.cc,v $
// Revision 1.3  1997/09/18 21:13:11  cdj
// Changed Boolean to DABoolean
//
// Revision 1.2  1997/07/11 06:20:10  mkl
// // New <Package>/<File>.h structure
// // Modified so can also compile under cxx v5.5
//
// Revision 1.1.1.1  1997/05/30 15:41:37  cdj
// First submission
//

#include "Experiment/Experiment.h"
// system include files
#include <assert.h>

// user include files
#include "DataStorage/DataSinkDescriptor.h"
#include "DataStorage/DataSinkController.h"
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
DataSinkDescriptor::DataSinkDescriptor( const string& iDataSinkID ,
					const string& iParameters ,
					const Stream::Type& iBindStream ) :
   m_boundStreamList( *(new Stream::Set ) ),
   m_dataSinkID(iDataSinkID),
   m_parameters(iParameters)
{
   assert( 0 != &m_boundStreamList );

   Stream::Set boundStreams;
   boundStreams.insert( iBindStream );

   bindStreams( boundStreams );
}

DataSinkDescriptor::DataSinkDescriptor( const string& iDataSinkID,
					const string& iParameters,
					const Stream::Set& iBindStreams ) :
   m_boundStreamList( *(new Stream::Set ) ),
   m_dataSinkID(iDataSinkID),
   m_parameters(iParameters)
{
   assert( 0 != &m_boundStreamList );

   bindStreams( iBindStreams );
}

DataSinkDescriptor::DataSinkDescriptor( const DataSinkController& 
					iController):
   m_boundStreamList( *(new Stream::Set) ),
   m_dataSinkID(""),
   m_parameters("")
{
   assert( 0 != &m_boundStreamList );

   bindStreams( iController.recordsToStore() );
   setDataSinkID( iController.dataSinkID() );
   setParameters( iController.parameters() );
}


DataSinkDescriptor::DataSinkDescriptor( const DataSinkDescriptor& 
					iDescriptor) :
   m_boundStreamList( *(new Stream::Set ) ),
   m_dataSinkID( iDescriptor.dataSinkID() ),
   m_parameters( iDescriptor.parameters() )
{
   assert( 0 != &m_boundStreamList );

   bindStreams( iDescriptor.boundStreams() );
}


DataSinkDescriptor::~DataSinkDescriptor()
{
   delete &m_boundStreamList;
}

//
// assignment operators
//
 const DataSinkDescriptor& 
DataSinkDescriptor::operator=( const DataSinkDescriptor& iDescriptor )
{
   if( &iDescriptor != this ){
      clearStreams();
      bindStreams( iDescriptor.boundStreams() );
      setDataSinkID( iDescriptor.dataSinkID() );
      setParameters( iDescriptor.parameters() );
   }

   return *this;
}


//
// member functions
//
void 
DataSinkDescriptor::bindStreams( const Stream::Set& iBindStreams )
{
   m_boundStreamList = iBindStreams; 
}

void 
DataSinkDescriptor::clearStreams( void )
{
   m_boundStreamList.erase( m_boundStreamList.begin(),
			    m_boundStreamList.end());
}

void 
DataSinkDescriptor::setDataSinkID( string iDataSinkID )
{
   m_dataSinkID = iDataSinkID;
}

void 
DataSinkDescriptor::setParameters( string iParameters ) 
{
   m_parameters = iParameters;
}
//
// const member functions
//
const Stream::Set& 
DataSinkDescriptor::boundStreams( void ) const
{
   return m_boundStreamList;
}

const string& 
DataSinkDescriptor::dataSinkID( void ) const
{
   return m_dataSinkID;
}

const string& 
DataSinkDescriptor::parameters( void ) const
{
   return m_parameters;
}

DABoolean 
DataSinkDescriptor::operator==( const DataSinkController& iController ) const
{
   DABoolean returnValue(false);
   if( iController.dataSinkID() == (*this).dataSinkID() ){
      if( iController.parameters() == (*this).parameters() ) {
	 returnValue = true;
      }
   }
   return returnValue;
}

DABoolean 
DataSinkDescriptor::operator==( const DataSinkDescriptor& iDescriptor ) const
{
   DABoolean returnValue(false);
   if( iDescriptor.dataSinkID() == (*this).dataSinkID() ){
      if( iDescriptor.parameters() == (*this).parameters() ) {
	 returnValue = true;
      }
   }
   return returnValue;
}

//
// static member functions
//


