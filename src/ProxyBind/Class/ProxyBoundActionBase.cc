// -*- C++ -*-
//
// Package:     <ProxyBind>
// Module:      ProxyBoundActionBase
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Sat Feb 27 10:40:58 EST 1999
// $Id: ProxyBoundActionBase.cc,v 1.3 2003/05/31 23:49:21 cdj Exp $
//
// Revision history
//
// $Log: ProxyBoundActionBase.cc,v $
// Revision 1.3  2003/05/31 23:49:21  cdj
// use new Record::cacheIdentifier() instead of Record::syncValue() to deterimine if the Record has changed since the last time a bound method was called.
//
// Revision 1.2  2000/05/22 18:52:14  cdj
// made ProxyBoundActionBase exception safe
//
// Revision 1.1.1.1  1999/03/04 19:11:57  cdj
// first submission
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "ProxyBind/ProxyBoundActionBase.h"
#include "DataHandler/Frame.h"
#include "DataHandler/Record.h"

// STL classes
#include <vector>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "ProxyBind.ProxyBoundActionBase" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: ProxyBoundActionBase.cc,v 1.3 2003/05/31 23:49:21 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
ProxyBoundActionBase::ProxyBoundActionBase( const Stream::Type& iStream ) :
   m_stream( iStream ),
   m_lastCacheIdentifier(Record::kCacheIdentifierNotSet)
{
}

// ProxyBoundActionBase::ProxyBoundActionBase( const ProxyBoundActionBase& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

ProxyBoundActionBase::~ProxyBoundActionBase()
{
}

//
// assignment operators
//
// const ProxyBoundActionBase& ProxyBoundActionBase::operator=( const ProxyBoundActionBase& rhs )
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
ProxyBoundActionBase::execute( const Frame& iFrame )
{
   //This throws an exception if record is not in the Frame
   const Record& record = iFrame.record( m_stream );

   if( record.cacheIdentifier() != m_lastCacheIdentifier ) {
      implementExecute( record );

      //update m_lastCacheIdentifier only after implementExecute in case
      // implementExecute throws an exception
      m_lastCacheIdentifier = record.cacheIdentifier() ;
   }
}

//
// const member functions
//

//
// static member functions
//
