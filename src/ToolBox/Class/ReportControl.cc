// -*- C++ -*-
//
// Package:     ToolBox
// Module:      ReportControl
// 
// Description:
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Thu Dec  2 13:24:06 EST 1999
// $Id: ReportControl.cc,v 1.4 2003/01/20 19:55:38 cdj Exp $
//
// Revision history
//
// $Log: ReportControl.cc,v $
// Revision 1.4  2003/01/20 19:55:38  cdj
// using stringstream if available
//
// Revision 1.3  2002/08/16 19:33:57  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.2  1999/12/06 22:25:11  bkh
// Fix bugs
//
// Revision 1.1  1999/12/03 15:17:10  bkh
// New class to control prescaling of report messages
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

#if defined(USING_IOSTREAM_H_BUG)
   #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
   #include <strstream.h>
   #else
   #include <sstream>
   #endif
#else
   #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
   #include <strstream>
   #else
   #include <sstream>
   #endif
#endif

// user include files
#include "Experiment/report.h"
#include "ToolBox/ReportControl.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

using namespace std;
//
// constants, enums and typedefs
//

static const char* const kReport = "ToolBox.ReportControl" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: ReportControl.cc,v 1.4 2003/01/20 19:55:38 cdj Exp $";
static const char* const kTagString = "$Name:  $";

#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
static ostrstream k_myNullStream ;
#else
static ostringstream k_myNullStream;
#endif

//
// static data member definitions
//

//
// constructors and destructor
//
ReportControl::ReportControl( const Severity& aSeverity ,
			      const std::string&   aFacility ,
			      const std::string&   aPreface  ,
			      const UInt32    aFactor   ,
			      const UInt32    aPlateau    ) :
   m_severity ( aSeverity ) ,   
   m_facility ( aFacility ) ,
   m_preface  ( aPreface  ) ,
   m_factor   ( aFactor  > 0 ? aFactor  : 1 ) ,
   m_plateau  ( aPlateau > 0 ? aPlateau : 1 ) ,
   m_nCalls   ( 0         ) ,
   m_prescale ( 1         )
{
}

// ReportControl::ReportControl( const ReportControl& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

ReportControl::~ReportControl()
{
}

//
// assignment operators
//
// const ReportControl& ReportControl::operator=( const ReportControl& rhs )
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

ostream& 
ReportControl::operator()() 
{
   if( plateau() == nCalls()+1 ) 
   {
      report( severity(), facility() ) 
	 << "-----------------------------------------------------\n"
	 << "----------"
	 << "  The following message  ------------------"
	 << "--------------\n has reached"
	 << " its plateau of " << plateau()
	 << " and will not be repeated again\n" 
	 << "-----------------------------------------------"
	 << "--------------------\n"
	 << std::endl ;
   }
   ++m_nCalls ;
   if( nCalls() <= plateau() )
   {
      if( nCalls() <= factor()            ||
	  0        == nCalls()%prescale() ||
	  nCalls() == plateau()               )
      {
	 if( nCalls() >= prescale()*factor() )
	 {
	    m_prescale *= factor() ;
	    report( severity(), facility() ) 
	       << "Increasing prescale factor to " << prescale() << "\n" ;
	 }
	 report( severity(), facility() ) 
	    << "Instance #" << nCalls()<< " of the following message\n" 
	    << preface() ;
	 return report( severity(), facility() ) ;
      }
   }
   k_myNullStream.seekp( 0 , ios::beg ) ; // acc to dsr, this is a 'rewind'
   return k_myNullStream ;
}

//
// const member functions
//

const Severity& 
ReportControl::severity() 
{
   return m_severity ;
}

const std::string&   
ReportControl::facility()
{
   return m_facility ;
}

const std::string&   
ReportControl::preface()  
{
   return m_preface ;
}

UInt32          
ReportControl::factor()   
{
   return m_factor ;
}

UInt32          
ReportControl::plateau()  
{
   return m_plateau ;
}

UInt32          
ReportControl::nCalls()   
{
   return m_nCalls ;
}

UInt32          
ReportControl::prescale()
{
   return m_prescale ;
}

//
// static member functions
//
