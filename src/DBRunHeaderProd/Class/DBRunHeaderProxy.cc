// -*- C++ -*-
//
// Package:     <DBRunHeaderProd>
// Module:      DBRunHeaderProxy
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Thu Jul 22 12:18:25 EDT 1999
// $Id: DBRunHeaderProxy.cc,v 1.1.1.1 1999/07/22 18:20:51 aw Exp $
//
// Revision history
//
// $Log: DBRunHeaderProxy.cc,v $
// Revision 1.1.1.1  1999/07/22 18:20:51  aw
// Imported initial DBRunHeaderProd sources
//
//
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>   // for ::exit
#include <assert.h>

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"

#include "DataHandler/Record.h"
#include "FrameAccess/extract.h"           
#include "FrameAccess/FATable.h"

#include "DBRunHeaderProd/DBRunHeaderProxy.h"

// STL classes

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "DBRunHeaderProd.DBRunHeaderProxy" ;

//
// static data member definitions
//

//
// constructors and destructor
//
DBRunHeaderProxy::DBRunHeaderProxy()
   : m_DBRunHeader( 0 )
{
}

// DBRunHeaderProxy::DBRunHeaderProxy( const DBRunHeaderProxy& iproxy )
// {
//   *this = iproxy;
// }

DBRunHeaderProxy::~DBRunHeaderProxy()
{
   delete m_DBRunHeader ;
}

//
// assignment operators
//
// const DBRunHeaderProxy& DBRunHeaderProxy::operator=( const DBRunHeaderProxy& iproxy )
// {
//   if( this != &iproxy ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iproxy );
//   }
//
//   return *this;
// }

//
// member functions
//
void
DBRunHeaderProxy::invalidateCache()
{
   delete m_DBRunHeader ;
   m_DBRunHeader = 0 ;
}

const DBRunHeaderProxy::value_type*
DBRunHeaderProxy::faultHandler( const Record& iRecord,
				const IfdKey& iKey )
{
   // be assertive: there should be no cached data at this point, else
   // it's a programming error
   assert( 0 == m_DBRunHeader );

   // ---------- create the new object --------------------

   const SyncValue& syncValue = iRecord.syncValue();
   m_DBRunHeader = new DBRunHeader( syncValue.runNumber());
   if( 0 == m_DBRunHeader )
   {
      report( EMERGENCY, kFacilityString )
	 << "can't allocate memory; aborting" << std::endl;
      assert( false );
      ::exit( 1 );
   }
   
   return ( m_DBRunHeader ) ;
}

//
// const member functions
//

//
// static member functions
//


