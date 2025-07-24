// -*- C++ -*-
//
// Package:     DataStorage
// Module:      ProxyStorer
// 
// Description: <one line class summary>
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Chris D. Jones
// Created:     Sun May 25 16:45:50 EDT 1997
// $Id: ProxyStorer.cc,v 1.5 2003/04/25 15:32:17 vk Exp $
//
// Revision history
//
// $Log: ProxyStorer.cc,v $
// Revision 1.5  2003/04/25 15:32:17  vk
// Add identifiers to the ProxyServer. Add entry to the DAExceptionStack.
//
// Revision 1.4  1997/09/18 21:13:13  cdj
// Changed Boolean to DABoolean
//
// Revision 1.3  1997/09/04 15:16:24  mkl
// moved to new bug flags
//
// Revision 1.2  1997/09/03 03:52:35  mkl
// renamed ToolBox/report to Experiment/report
//
// Revision 1.1  1997/08/16 17:47:18  cdj
// Changed name of class to use Proxy instead of DataField
//
// Revision 1.4  1997/07/11 06:20:07  mkl
// // New <Package>/<File>.h structure
// // Modified so can also compile under cxx v5.5
//
// Revision 1.3  1997/05/31 21:16:12  cdj
// store() now calls implementStore() and uses the return value to set its
//  status
//
// Revision 1.2  1997/05/31 20:49:09  cdj
// 1) store now returns a status code
// 2) DataFieldStorer now knows its status based on the last store operation
//
// Revision 1.1.1.1  1997/05/30 15:41:36  cdj
// First submission
//

#include "Experiment/Experiment.h"
// system include files
#include <stdlib.h>  // For 'exit'
#include <assert.h>
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <set>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "DataStorage/ProxyStorer.h"
#include "DataHandler/Record.h"
#include "DataHandler/StreamSet.h"
#include "DAException/DAExceptionStackNameEntry.h"

// STL classes

//
// constants, enums and typedefs
//
const std::string kFacilityString = "DataStorage.ProxyStorer" ;

//
// static data member definitions
//

//
// constructors and destructor
//
ProxyStorer::ProxyStorer( const Identifier& aId ) :
   m_records( *(new Stream::Set) ),
   m_id( aId ), m_paramId(""), m_sinkId("")
{
}

// ProxyStorer::ProxyStorer( const ProxyStorer& )
// {
// }

ProxyStorer::~ProxyStorer()
{
   delete &m_records;
}

//
// assignment operators
//
// const ProxyStorer& ProxyStorer::operator=( const ProxyStorer& )
// {
// }

//
// member functions
//
void 
ProxyStorer::setDataSinkId(const std::string& sId)
{
  m_sinkId = sId;
}

void 
ProxyStorer::setParamId(const std::string& sParam)
{
  m_paramId = sParam;
}

void 
ProxyStorer::registerStream( const Stream::Type& aStream )
{
   m_records.add( aStream );
}

void
ProxyStorer::setStatus( const ProxyStorer::StoreStatus& iStatus)
{
   m_status = iStatus;
}

//
// const member functions
//
const ProxyStorer::Identifier&
ProxyStorer::identifier() const
{
   return ( m_id );
}

DABoolean 
ProxyStorer::canStore( const Stream::Type& aStream ) const
{
   return m_records.contains( aStream );
}

Stream::Set 
ProxyStorer::stores( void ) const
{
   return m_records;
}

ProxyStorer::StoreStatus
ProxyStorer::store( const Record& aRecord ) const
{
   // add entry to the stack
   std::string sss = " file: \""+m_sinkId+"\" parameter: \""+m_paramId+"\"";
   DAExceptionStackNameEntry stackNameEntry(sss);

   StoreStatus temp = implementStore( aRecord );
   //Casting away the const
   (* ((ProxyStorer*) this) ).setStatus( temp );

   return temp;
}

ProxyStorer::StoreStatus
ProxyStorer::status( void ) const
{
   return m_status;
}

//
// static member functions
//
