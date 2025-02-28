// -*- C++ -*-
//
// Package:     CleoDB
// Module:      DBEventHeader
// 
// Description: <one line class summary>
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Simon Patton
// Created:     Mon Apr  7 16:52:09 EDT 1997
// $Id: DBEventHeader.cc,v 1.10 2003/10/16 21:01:30 vk Exp $
//
// Revision history
//
// $Log: DBEventHeader.cc,v $
// Revision 1.10  2003/10/16 21:01:30  vk
// Fix MonteCarlo function. From now on monte carlo carry time stamp > 1.
//
// Revision 1.9  2001/05/23 16:47:41  bkh
// Add time word
//
// Revision 1.8  1997/08/27 03:39:50  sjp
// Updated to new name for bug flags
//
// Revision 1.7  1997/08/06 18:08:12  sjp
// Removed dependence on DataField
//
// Revision 1.6  1997/07/28 17:59:47  sjp
// Fixed to work under cxx 5.6
//
// Revision 1.5  1997/07/09 18:01:24  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.4  1997/06/03 17:33:43  sjp
// Ammended Documentation
//
// Revision 1.3  1997/05/07 20:12:47  sjp
// Used correct constructor for constants
//
// Revision 1.2  1997/04/14 19:52:55  sjp
// First working version
//
// Revision 1.1  1997/04/10 02:11:32  sjp
// Add filename only includes.
// Prepared for templated DataField system
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "CleoDB/DBEventHeader.h"

// STL classes
#if defined(OLD_CXX_STRING_CLASS_BUG)
#include <String.h>
#else
#include <string>
#endif /* OLD_CXX_STRING_CLASS_BUG */

//
// constants, enums and typedefs
//

//
// static data member definitions
//

const Stream::Type& DBEventHeader::kStream = Stream::kEvent ;

//
// constructors and destructor
//
DBEventHeader::DBEventHeader( Count   aRun       ,
			      Count   aEvent     ,
			      UInt32  aTimeMost  ,
			      UInt32  aTimeLeast  ) :
   m_run   ( aRun   ) ,
   m_event ( aEvent ) ,
   m_time  ( ( ( UInt64 ( aTimeMost ) )<<32 ) + aTimeLeast )
{
}

DBEventHeader::DBEventHeader( Count   aRun       ,
			      Count   aEvent     ,
			      UInt64  aTime        ) :
   m_run   ( aRun   ) ,
   m_event ( aEvent ) ,
   m_time  ( aTime  )
{
}

// DBEventHeader::DBEventHeader( const DBEventHeader& )
// {
// }

DBEventHeader::~DBEventHeader()
{
}

//
// assignment operators
//
// const DBEventHeader& DBEventHeader::operator=( const DBEventHeader& )
// {
// }

//
// member functions
//

//
// const member functions
//

Count
DBEventHeader::run() const
{
   return ( m_run ) ;
}

Count
DBEventHeader::number() const
{
   return ( m_event ) ;
}

UInt64
DBEventHeader::time() const
{
   return ( m_time ) ;
}

DABoolean
DBEventHeader::monteCarlo() const
{
   if(m_time>1) return true;
   return false;
}

UInt32
DBEventHeader::timeMost() const
{
   return ( ( m_time>>32 ) & ( ~ ( UInt32 ) 0 ) ) ;
}

UInt32
DBEventHeader::timeLeast() const
{
   return ( m_time & ( ~ ( UInt32 ) 0 ) ) ;
}

//
// static member functions
//
