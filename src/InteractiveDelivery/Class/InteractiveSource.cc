// -*- C++ -*-
//
// Package:     InteractiveDelivery
// Module:      InteractiveSource
// 
// Description: <one line class summary>
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Chris D. Jones
// Created:     Sat Apr 19 14:31:37 EDT 1997
// $Id: InteractiveSource.cc,v 1.6 2003/11/22 20:22:25 cdj Exp $
//
// Revision history
//
// $Log: InteractiveSource.cc,v $
// Revision 1.6  2003/11/22 20:22:25  cdj
// can now specify what stream should be used
//
// Revision 1.5  1997/09/18 21:25:22  cdj
// changed Boolean to DABoolean
//
// Revision 1.4  1997/07/09 19:22:01  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.3  1997/05/06 20:26:18  mkl
// got rid of runNumber(), eventNumber() methods
//
// Revision 1.2  1997/05/06 18:33:51  mkl
// replaced run, event with SyncValue
//
// Revision 1.1.1.1  1997/04/21 19:30:11  cdj
// First submission
//

#include "Experiment/Experiment.h"
// system include files

// user include files
#include "InteractiveDelivery/InteractiveSource.h"
#include "DataHandler/SyncValue.h"
#include "DataHandler/Stream.h"

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
InteractiveSource::InteractiveSource( void ):
   m_syncValue( 0, 0 ),
   m_isSequentiallyAccessing(false),
   m_streamType(Stream::kEvent)
{
}

// InteractiveSource::InteractiveSource( const InteractiveSource& )
// {
// }

InteractiveSource::~InteractiveSource()
{
}

//
// assignment operators
//
// const InteractiveSource& InteractiveSource::operator=( const InteractiveSource& )
// {
// }

//
// member functions
//
DABoolean
InteractiveSource::setSyncValue( const SyncValue& iSyncValue )
{
   if(isSequentiallyAccessing()){
      if( iSyncValue < m_syncValue ) {
	 return false;
      }
   }
   m_syncValue = iSyncValue;
   return true;
}

void
InteractiveSource::resetSyncValue( const SyncValue& iSyncValue )
{
   m_syncValue = iSyncValue;
}

void
InteractiveSource::setStream( const Stream::Type& iStream )
{
   m_streamType = iStream;
}

void
InteractiveSource::setSequentialAccess( DABoolean iSetValue )
{
   m_isSequentiallyAccessing = iSetValue;
}

//
// const member functions
//
SyncValue
InteractiveSource::syncValue( void ) const
{
   return m_syncValue;
}

DABoolean 
InteractiveSource::isSequentiallyAccessing( void ) const
{
   return m_isSequentiallyAccessing;
}
//
// static member functions
//
