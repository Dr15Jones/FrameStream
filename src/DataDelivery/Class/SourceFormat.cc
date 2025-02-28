// -*- C++ -*-
//
// Package:     <DataDelivery>
// Module:      SourceFormat
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Mon May 25 18:23:05 EDT 1998
// $Id: SourceFormat.cc,v 1.5 2002/06/11 17:53:46 cdj Exp $
//
// Revision history
//
// $Log: SourceFormat.cc,v $
// Revision 1.5  2002/06/11 17:53:46  cdj
// added ability to set the default streams differently for each source name
//
// Revision 1.4  2001/02/26 00:45:09  cdj
// StartRun is now a default stream
//
// Revision 1.3  1999/06/12 00:03:27  mkl
// allow to specify default streams per source format
//
// Revision 1.2  1998/11/09 21:25:34  mkl
// loadable classes know their own factorySymbol string
//
// Revision 1.1  1998/06/17 18:19:54  mkl
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
#include "DataDelivery/SourceFormat.h"
#include "DataHandler/StreamSet.h"

// STL classes
#include <string>
#include <set>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "DataDelivery.SourceFormat" ;

//
// static data member definitions
//

//
// constructors and destructor
//
SourceFormat::SourceFormat( BinderType iType )
   : m_type( iType ),
     m_extensions( *new _sourceformat_extensions_ ),
     m_defaultStreams( *( new Stream::Set ) )
{
   assert( 0 != &m_extensions );
   assert( 0 != &m_defaultStreams );

   // set default streams, unless somebody changes it
   Stream::Set streams;
   streams.insert( Stream::kBeginRun );
   streams.insert( Stream::kStartRun );
   streams.insert( Stream::kEvent );
   setDefaultStreams( streams );
}

// SourceFormat::SourceFormat( const SourceFormat& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

SourceFormat::~SourceFormat()
{
   delete &m_defaultStreams;
   delete &m_extensions;
}

//
// assignment operators
//
// const SourceFormat& SourceFormat::operator=( const SourceFormat& rhs )
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
SourceFormat::addExtension( const string& iExtension ) 
{
   m_extensions.insert( iExtension );
}   

void
SourceFormat::setDefaultStreams( const Stream::Set& iStreamSet ) 
{
   m_defaultStreams = iStreamSet;
}   

//
// const member functions
//
const _sourceformat_extensions_&
SourceFormat::extensions() const
{
   return m_extensions;
}

const Stream::Set&
SourceFormat::defaultStreams() const
{
   return m_defaultStreams;
}

const Stream::Set&
SourceFormat::defaultStreams( const string& iName)
{
   return defaultStreams();
}

//
// static member functions
//
string
SourceFormat::factorySymbol()
{
   return "makeSourceFormat";
}
