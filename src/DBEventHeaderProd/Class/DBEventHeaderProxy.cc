// -*- C++ -*-
//
// Package:     <DBEventHeaderProd>
// Module:      DBEventHeaderProxy
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Tue Jul 21 12:38:36 EDT 1998
// $Id: DBEventHeaderProxy.cc,v 1.2 2001/05/23 16:49:06 bkh Exp $
//
// Revision history
//
// $Log: DBEventHeaderProxy.cc,v $
// Revision 1.2  2001/05/23 16:49:06  bkh
// Get time from syncvalueand put it into the DBEventHeader
//
// Revision 1.1.1.1  1999/06/01 18:58:32  mkl
// imported sources
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

#include "DBEventHeaderProd/DBEventHeaderProxy.h"

// STL classes

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "DBEventHeaderProd.DBEventHeaderProxy" ;

//
// static data member definitions
//

//
// constructors and destructor
//
DBEventHeaderProxy::DBEventHeaderProxy()
   : m_DBEventHeader( 0 )
{
}

// DBEventHeaderProxy::DBEventHeaderProxy( const DBEventHeaderProxy& iproxy )
// {
//   *this = iproxy;
// }

DBEventHeaderProxy::~DBEventHeaderProxy()
{
   delete m_DBEventHeader ;
}

//
// assignment operators
//
// const DBEventHeaderProxy& DBEventHeaderProxy::operator=( const DBEventHeaderProxy& iproxy )
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
DBEventHeaderProxy::invalidateCache()
{
   delete m_DBEventHeader ;
   m_DBEventHeader = 0 ;
}

const DBEventHeaderProxy::value_type*
DBEventHeaderProxy::faultHandler( const Record& iRecord,
				  const IfdKey& iKey )
{
   // be assertive: there should be no cached data at this point, else
   // it's a programming error
   assert( 0 == m_DBEventHeader );

   // ---------- create the new object --------------------

   const SyncValue& syncValue = iRecord.syncValue() ;

   m_DBEventHeader = new DBEventHeader( syncValue.runNumber()   , 
					syncValue.eventNumber() ,
					syncValue.time()          ) ;
   
   return m_DBEventHeader ;
}

//
// const member functions
//

//
// static member functions
//


