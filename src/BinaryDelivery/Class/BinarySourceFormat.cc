// -*- C++ -*-
//
// Package:     <BinaryDelivery>
// Module:      BinarySourceFormat
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Mon May 25 18:23:05 EDT 1998
// $Id: BinarySourceFormat.cc,v 1.2 2003/02/20 14:27:22 cdj Exp $
//
// Revision history
//
// $Log: BinarySourceFormat.cc,v $
// Revision 1.2  2003/02/20 14:27:22  cdj
// made beginrun startrun event and endrun the default streams
//
// Revision 1.1  1998/11/16 16:51:19  mkl
// additions necessary to load BinarySourceFormat and chain binary files
//
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
#include "BinaryDelivery/BinarySourceFormat.h"
#include "BinaryDelivery/BinarySourceBinder.h"
#include "JobControl/Binder.h"
#include "DataHandler/StreamSet.h"


// STL classes
#include <string>
#include <set>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "BinaryDelivery.BinarySourceFormat" ;

//
// static data member definitions
//

//
// constructors and destructor
//
BinarySourceFormat::BinarySourceFormat()
   : SourceFormat( BinderBase::kBinary )
{
   // add extensions that this format recognizes
   addExtension( string( ".bin" ) );

   StreamSet defaults;
   defaults.insert(Stream::kBeginRun);
   defaults.insert(Stream::kStartRun);
   defaults.insert(Stream::kEvent);
   defaults.insert(Stream::kEndRun);

   setDefaultStreams( defaults);
}

// BinarySourceFormat::BinarySourceFormat( const BinarySourceFormat& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

BinarySourceFormat::~BinarySourceFormat()
{
}

//
// assignment operators
//
// const BinarySourceFormat& BinarySourceFormat::operator=( const BinarySourceFormat& rhs )
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
BinderBase*
BinarySourceFormat::createBinder( const string& iName, 
				  const Stream::Set& iBindStreams ) 
{
   BinderBase* returnValue 
      = new Binder< BinarySourceBinder >(
	 new BinarySourceBinder( iName.c_str(), iBindStreams ),
	 type()
	 );

   if( 0 == returnValue ) {
      report( EMERGENCY, kFacilityString )
	 << "out of memory" << endl;
      assert( false );
      ::exit( 1 );
   }

   return returnValue;
}   

//
// const member functions
//

//
// static member functions
//
