// -*- C++ -*-
//
// Package:     JobControl
// Module:      BlankRecordModule
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D. Jones
// Created:     Sun Mar 29 19:22:00 EST 1998
// $Id: BlankRecordModule.cc,v 1.5 2000/12/01 20:26:03 cdj Exp $
//
// Revision history
//
// $Log: BlankRecordModule.cc,v $
// Revision 1.5  2000/12/01 20:26:03  cdj
// now includes map
//
// Revision 1.4  1999/06/14 15:55:42  mkl
// return token name as tcl resultString
//
// Revision 1.3  1998/11/09 19:33:06  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.2  1998/06/17 18:18:06  mkl
// allow dynamic loading of source and sink formats
//
// Revision 1.1  1998/04/01 19:43:13  mkl
// added Chris' BlankRecordDelivery handling
//

#include "Experiment/Experiment.h"

// system include files
#include <assert.h>
#include <stdlib.h>

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "JobControl/BlankRecordModule.h"
#include "BlankRecordDelivery/BlankRecordSourceBinder.h"
#include "BlankRecordDelivery/BlankRecordStopsBase.h"

#include "JobControl/JobControl.h"
#include "JobControl/SourceManager.h"
#include "JobControl/Binder.h"

// STL classes
#include <vector>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "JobControl.BlankRecordModule" ;

//
// static data member definitions
//

//
// constructors and destructor
//
BlankRecordModule::BlankRecordModule( SourceManager& iSourceManager )
   : Module( "EmptySourceModule", "BlankRecordModule"),
     m_command( "emptysource", this ),
     m_sourceManager( iSourceManager )
{
}

// BlankRecordModule::BlankRecordModule( const BlankRecordModule& )
// {
// }

BlankRecordModule::~BlankRecordModule()
{
}

//
// assignment operators
//
// const BlankRecordModule& BlankRecordModule::operator=( const BlankRecordModule& )
// {
// }

//
// member functions
//
DABoolean 
BlankRecordModule::addSource( const string& iSourceName, 
			      const StreamSet& iReadStreams,
			      BlankRecordStopsBase* iStops, 
			      string& ioToken )
{
   DABoolean success = true;

   BinderBase* binder 
      = createBinder( iSourceName, iReadStreams, iStops );
   if( 0 != binder ) {
      success = m_sourceManager.addSource( binder, ioToken );
   }

   return success;
}

BinderBase*
BlankRecordModule::createBinder( const string& sourceName,
				 const StreamSet& readStreams,
				 BlankRecordStopsBase* iStops )
{
   BlankRecordSourceBinder* BRSB =
      new BlankRecordSourceBinder( sourceName, readStreams, iStops );

   if( 0 == BRSB ){
      //since the binder was supposed to own iStops, we have to delete iStops
      delete iStops;

      return 0;
   }
   
   return new Binder< BlankRecordSourceBinder >( BRSB,
						 BinderBase::kBlank );
}

//
// const member functions
//

//
// static member functions
//
