// -*- C++ -*-
//
// Package:     <BinaryDelivery>
// Module:      BinarySourceBinder
// 
// Description: Binds event, beginRun, or endRun stream to a binary file
//
//  Implementation:
//     Cribbed from CDJ's RoarSourceBinder
//
// Author:      David L. Kreinick
// Created:     Tue Nov  3 12:48:56 EST 1998
// $Id: BinarySourceBinder.cc,v 1.4 1999/11/16 19:31:25 dlk Exp $
//
// Revision history
//
// $Log: BinarySourceBinder.cc,v $
// Revision 1.4  1999/11/16 19:31:25  dlk
// Suppress debug messages
//
// Revision 1.3  1998/11/18 19:48:57  dlk
// DLK: Intermediate update of BinaryDelivery code
//      The code has now been debugged to the point that it compiles,
//      and runs properly under Martin Lohner's test driver program.
//
//      There are still substantial problems:
//      1) BinaryRawEventProxy not yet written
//      2) Record types have not yet been defined
//      3) We haven't decided on BeginRun and EndRun record formats yet
//      and no doubt there are other problems I haven't discovered yet.
//
// Revision 1.2  1998/11/16 16:51:15  mkl
// additions necessary to load BinarySourceFormat and chain binary files
//
// Revision 1.1.1.1  1998/11/03 20:46:41  dlk
// importing new BinaryDelivery sources
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "BinaryDelivery/BinarySourceController.h"
#include "BinaryDelivery/BinarySourceBinder.h"

// STL classes

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "BinaryDelivery.BinarySourceBinder" ;

//
// static data member definitions
//

//
// constructors and destructor
//
BinarySourceBinder::BinarySourceBinder(const std::string& iFileName,
				       const Stream::Set& iBindStreams ) :
   DataSourceBinder( iFileName,std::string(""), iBindStreams )
{
   report( DEBUG, kFacilityString ) 
      << "here in BinarySourceBinder::ctor" << std::endl;
}

BinarySourceBinder::BinarySourceBinder()
{
}

BinarySourceBinder::BinarySourceBinder( const BinarySourceBinder& iBinder ) :
   DataSourceBinder( iBinder.dataSourceID(),
                     iBinder.parameters(),
                     iBinder.boundStreams())
{
}

BinarySourceBinder::~BinarySourceBinder()
{
}

//
// assignment operators
//
const BinarySourceBinder& BinarySourceBinder::operator=(
   const BinarySourceBinder& iBinder )
{
   if( this != &iBinder ) {
      setDataSourceID( iBinder.dataSourceID() );
      setParameters( iBinder.parameters() );
      bindStreams( iBinder.boundStreams() );
   }

   return *this;
}

//
// member functions
//

//
// const member functions
//
DataSourceController*
BinarySourceBinder::createDataSourceController() const
{
   return ( new BinarySourceController( fileName(),
					boundStreams() ) ) ;
}

BinarySourceController*
BinarySourceBinder::createSourceController( BinaryProxyDeliverer* 
					    iDeliverer ) const
{
   return ( new BinarySourceController( fileName(),
					boundStreams(),
					iDeliverer ) ) ;
}

const std::string&
BinarySourceBinder::fileName() const
{
   return dataSourceID();
}


//
// static member functions
//
