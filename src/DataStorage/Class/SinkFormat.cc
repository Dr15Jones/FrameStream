// -*- C++ -*-
//
// Package:     <DataStorage>
// Module:      SinkFormat
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Mon May 25 18:23:05 EDT 1998
// $Id: SinkFormat.cc,v 1.3 2001/06/15 21:05:11 cdj Exp $
//
// Revision history
//
// $Log: SinkFormat.cc,v $
// Revision 1.3  2001/06/15 21:05:11  cdj
// can now specify data (not) to store in a sink
//
// Revision 1.2  1998/11/09 21:25:44  mkl
// loadable classes know their own factorySymbol string
//
// Revision 1.1  1998/06/17 18:20:10  mkl
// allow dynamic loading of source and sink formats
//

#include "Experiment/Experiment.h"

// system include files
#include <assert.h>

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <set>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "DataStorage/SinkFormat.h"

// STL classes
#include <string>
#include <set>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "DataStorage.SinkFormat" ;

//
// static data member definitions
//

//
// constructors and destructor
//
SinkFormat::SinkFormat()
   : m_extensions( *new _sinkformat_extensions_ )
{
   if( 0 == &m_extensions ) {
      report( ::EMERGENCY, kFacilityString )
	 << "out of memory" << endl;
      assert( false );
      ::exit( 1 );
   }
}

// SinkFormat::SinkFormat( const SinkFormat& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

SinkFormat::~SinkFormat()
{
   delete &m_extensions;
}

//
// assignment operators
//
// const SinkFormat& SinkFormat::operator=( const SinkFormat& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }

//
// member functions
//
void
SinkFormat::addExtension( const string& iExtension ) 
{
   m_extensions.insert( iExtension );
}   


DataSinkBinder*
SinkFormat::createBinder(
   const string& iName,
	const Stream::Set& iBindStreams,
   const StreamToDataStringTagsToStoreMap& iStreamTagsMap)
{
   return 0;
}

//
// const member functions
//
const _sinkformat_extensions_&
SinkFormat::extensions() const
{
   return m_extensions;
}

DABoolean
SinkFormat::canSpecifyDataToStore() const 
{
   return false;
}

//
// static member functions
//
string
SinkFormat::factorySymbol()
{
   return "makeSinkFormat";
}
