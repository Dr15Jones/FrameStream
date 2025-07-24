// -*- C++ -*-
//
// Package:     <package>
// Module:      DataSourceDescriptor
// 
// Description: <one line class summary>
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Chris D. Jones
// Created:     Mon Apr 21 12:10:13 EDT 1997
// $Id: DataSourceDescriptor.cc,v 1.4 1997/09/18 21:07:08 cdj Exp $
//
// Revision history
//
// $Log: DataSourceDescriptor.cc,v $
// Revision 1.4  1997/09/18 21:07:08  cdj
// changed Boolean to DABoolean
//
// Revision 1.3  1997/08/27 03:39:24  sjp
// Updated to new name for bug flags
//
// Revision 1.2  1997/07/09 18:00:40  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.1  1997/04/21 19:16:09  cdj
// First submission
//

#include "Experiment/Experiment.h"

// system include files
#include <string>
#include <cassert>

// user include files
#include "DataDelivery/DataSourceDescriptor.h"
#include "DataDelivery/DataSourceController.h"
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
DataSourceDescriptor::DataSourceDescriptor( const std::string& iDataSourceID,
					    const std::string& iParameters,
					    const Stream::Type& iBindStream) :
   m_boundStreamList( *(new Stream::Set ) ),
   m_dataSourceID(iDataSourceID),
   m_parameters(iParameters)
{

   Stream::Set boundStreams;
   boundStreams.insert( iBindStream );

   bindStreams( boundStreams );
}

DataSourceDescriptor::DataSourceDescriptor( const std::string& iDataSourceID,
					    const std::string& iParameters,
					    const Stream::Set& iBindStreams ) :
   m_boundStreamList( *(new Stream::Set ) ),
   m_dataSourceID(iDataSourceID),
   m_parameters(iParameters)
{

   bindStreams( iBindStreams );
}

DataSourceDescriptor::DataSourceDescriptor( const DataSourceController& 
					    iController):
   m_boundStreamList( *(new Stream::Set) ),
   m_dataSourceID(""),
   m_parameters("")
{

   bindStreams( iController.recordsToRetrieve() );
   setDataSourceID( iController.dataSourceID() );
   setParameters( iController.parameters() );
}

DataSourceDescriptor::DataSourceDescriptor( const DataSourceDescriptor&
   iDescriptor ) :
   m_boundStreamList( *(new Stream::Set ) ),
   m_dataSourceID( iDescriptor.dataSourceID() ),
   m_parameters( iDescriptor.parameters() )
{

   bindStreams( iDescriptor.boundStreams() );
}


DataSourceDescriptor::~DataSourceDescriptor()
{
   delete &m_boundStreamList;
}

//
// assignment operators
//
const DataSourceDescriptor& 
DataSourceDescriptor::operator=( const DataSourceDescriptor& iDescriptor )
{
   if( &iDescriptor != this ){
      clearStreams();
      bindStreams( iDescriptor.boundStreams() );
      setDataSourceID( iDescriptor.dataSourceID() );
      setParameters( iDescriptor.parameters() );
   }

   return *this;
}

//
// member functions
//
void
DataSourceDescriptor::bindStreams( const Stream::Set& iBindStreams )
{
   m_boundStreamList = iBindStreams; 
}

void
DataSourceDescriptor::clearStreams( void )
{
   m_boundStreamList.erase( m_boundStreamList.begin(),
			    m_boundStreamList.end());
}


void
DataSourceDescriptor::setDataSourceID( std::string iDataSourceID )
{
   m_dataSourceID = iDataSourceID;
}

void
DataSourceDescriptor::setParameters( std::string iParameters )
{
   m_parameters = iParameters;
}
//
// const member functions
//
const Stream::Set&
DataSourceDescriptor::boundStreams( void ) const
{
   return m_boundStreamList;
}

const std::string&
DataSourceDescriptor::dataSourceID( void ) const
{
   return m_dataSourceID;
}

const std::string&
DataSourceDescriptor::parameters( void ) const
{
   return m_parameters;
}

DABoolean
DataSourceDescriptor::operator==( 
   const DataSourceController& iController ) const
{
   DABoolean returnValue(false);
   if( iController.dataSourceID() == (*this).dataSourceID() ){
      if( iController.parameters() == (*this).parameters() ) {
	 returnValue = true;
      }
   }
   return returnValue;
}

DABoolean
DataSourceDescriptor::operator==(const DataSourceDescriptor& iDescriptor) const
{
   DABoolean returnValue(false);
   if( iDescriptor.dataSourceID() == (*this).dataSourceID() ){
      if( iDescriptor.parameters() == (*this).parameters() ) {
	 returnValue = true;
      }
   }
   return returnValue;
}

//
// static member functions
//
