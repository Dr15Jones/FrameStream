// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      BinderBase
// 
// Description: <one line class summary>
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Mon May 21 17:32:09 EDT 1998
// $Id: BinderBase.cc,v 1.8 1999/10/22 15:10:02 mkl Exp $
//
// Revision history at end of file
//

#include "Experiment/Experiment.h"

// system include files
#include <assert.h>

// user include files
#include "Experiment/report.h"
#include "JobControl/BinderBase.h"
#include "DataDelivery/DataSourceBinder.h"
#include "DataHandler/StreamSet.h"

// STL classes

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "JobControl.BinderBase";

//
// static data member definitions
//
const BinderBase::Type
BinderBase::kNone( "none" );

const BinderBase::Type
BinderBase::kRoar( "roar", true );

const BinderBase::Type
BinderBase::kZFiles( "zfiles", true );

const BinderBase::Type
BinderBase::kAscii( "ascii", true );

const BinderBase::Type
BinderBase::kBinary( "binary", true );

const BinderBase::Type
BinderBase::kKarp( "karp", true );

const BinderBase::Type
BinderBase::kDB( "db", true );

const BinderBase::Type
BinderBase::kConstants( "constants", true );

const BinderBase::Type
BinderBase::kBlank( "blank", true );

//
// constructors and destructor
//
BinderBase::BinderBase( DataSourceBinder* dsb, 
			BinderBase::Type iType )
   : m_dsBinder( dsb), m_type( iType ), m_isChain( false ),
     m_toBeActiveStreams( *(new Stream::Set ) )
{
   assert( 0 != &m_toBeActiveStreams );
}

// BinderBase::BinderBase( const BinderBase& )
// {
// }

BinderBase::~BinderBase()
{
   delete &m_toBeActiveStreams;
   delete m_dsBinder;
}

//
// assignment operators
//
// const BinderBase& BinderBase::operator=( const BinderBase& )
// {
// }

//
// member functions
//
void BinderBase::setToken( const Token& iToken )
{
   m_token=iToken;
   if( 0 != m_dsBinder && isChain() ) {
      m_dsBinder->setDataSourceID( iToken );
   }
}

void
BinderBase::bindStreams( const Stream::Set& iBindStreams )
{
   if( 0 != m_dsBinder ) {
      m_dsBinder->bindStreams( iBindStreams );
   }
   else {
      report( ERROR, kFacilityString )
	 << "bindStreams: no real binder present" 
	 << endl;
   }
}

void
BinderBase::setToBeActiveStreams( const Stream::Set& iStreams )
{
   // start out with clean slate
   clearToBeActiveStreams();

   // only insert the ones which are bound to source!
   Stream::Set::const_iterator itEnd   = iStreams.end();
   for( Stream::Set::const_iterator it = iStreams.begin();
	it != itEnd;
	++it )
   {
      Stream::Set::const_iterator which = boundStreams().find( *it );
      if( which != boundStreams().end() ) 
      {
	 m_toBeActiveStreams.insert( *which );
      }
   }
}

void
BinderBase::clearToBeActiveStreams( void )
{
   m_toBeActiveStreams.erase( m_toBeActiveStreams.begin(),
			      m_toBeActiveStreams.end());
}

//
// const member functions
//
const Stream::Set&
BinderBase::boundStreams( void ) const
{
   return (*this)->boundStreams();
}

const string& 
BinderBase::parameters( void ) const
{
   return (*this)->parameters();
}

const string&
BinderBase::dataSourceID( void ) const
{
   return (*this)->dataSourceID();
}

DABoolean
BinderBase::isToBeActiveStream( const Stream::Type& iStream ) const
{
   DABoolean returnValue = false;

   Stream::Set::iterator which = m_toBeActiveStreams.find( iStream );
   if( which != m_toBeActiveStreams.end() )
   {
      returnValue = true;
   }

   return returnValue;
}

//
// static member functions
//


// Revision history
//
// $Log: BinderBase.cc,v $
// Revision 1.8  1999/10/22 15:10:02  mkl
// fix up BinderBase: iterator != const_iterator
//
// Revision 1.7  1999/10/08 21:46:43  mkl
// put in hooks for pattern searching in loading (if we ever decide to use it); fix bug with file chaining
//
// Revision 1.6  1999/04/30 18:15:18  mkl
// first version of source act command handling
//
// Revision 1.5  1999/04/24 16:22:37  mkl
// keep track of DataSourceDescriptors, not just names of files
//
// Revision 1.4  1998/11/16 21:57:29  mkl
// added official kConstants binder type
//
// Revision 1.3  1998/11/16 17:31:23  mkl
// added kBinary to official source formats
//
// Revision 1.2  1998/10/01 14:40:58  mkl
// delayed stream activation until after calling init on Proc/ducers
//
// Revision 1.1  1998/06/17 18:18:03  mkl
// allow dynamic loading of source and sink formats
//
//
