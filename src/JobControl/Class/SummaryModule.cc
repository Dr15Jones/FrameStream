// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      SummaryModule
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Fri Jul 24 10:43:06 EDT 1998
// $Id: SummaryModule.cc,v 1.10 2003/09/19 21:03:50 cdj Exp $
//
// Revision history (at end of file)
//

#include "Experiment/Experiment.h"

// system include files
#include <assert.h>
#include <stdlib.h>
#if defined(OSTRSTREAM_NO_TERMINATION_BUG)
#include <stdio.h>
#endif
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
#include <strstream.h>
#else
#include <sstream>
#endif

// user include files
#include "Experiment/report.h"
#include "JobControl/SummaryModule.h"

#include "CommandPattern/Keyword/NoArgNoReturn.h"
#include "CommandPattern/Keyword/NoArgReturnResult.h"

using namespace CommandPattern::Keyword;

// STL classes
#include <map>
#include "STLUtility/fwd_map.h"

//
// constants, enums and typedefs
//
typedef _summarymodule_counter_ Counter;

static const char* const kFacilityString = "JobControl.SummaryModule" ;

//
// static data member definitions
//
static const string helpMessage = 
string( "                                                                \n" )+
string( "// Description: SummaryCommand                                  \n" )+
string( "//                                                              \n" )+
string( "//  Valid subcommands are:                                      \n" )+
string( "//                                                              \n" )+
string( "//                                         print statistics     \n" )+
string( "//  help                                   see this help page   \n" )+
string( "//  reset                                  reset counters       \n" );

//
// constructors and destructor
//
SummaryModule::SummaryModule()
   : Module( "SummaryModule", "SummaryModule" ),
     m_command( "summary", this, false, helpMessage ),
     m_counter( *new Counter )
{
   m_command.add( new NoArgReturnResult<SummaryModule, string>(
      "", this, &SummaryModule::list, &m_command) );
   m_command.add( new NoArgNoReturn<SummaryModule>(
      "reset",this, &SummaryModule::reset ) );
}

// SummaryModule::SummaryModule( const SummaryModule& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

SummaryModule::~SummaryModule()
{
   // print out final statistics
   report( INFO, kFacilityString ) << list() << endl;

   delete &m_counter;
}

//
// assignment operators
//
// const SummaryModule& SummaryModule::operator=( const SummaryModule& rhs )
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
SummaryModule::reset()
{
   m_counter.erase( m_counter.begin(), m_counter.end() );
}

Count&
SummaryModule::operator[]( const Stream::Type& iStreamType )
{
   return m_counter[ iStreamType ];
}

//
// const member functions
//
string
SummaryModule::list()
{
   string resultString( "\n ***** Summary Info *****\n\n" );

   Counter::const_iterator itEnd = m_counter.end();
   Count sumAll=0;
   for( Counter::const_iterator it = m_counter.begin();
	it != itEnd;
	++it )
   {
// buggy ostrstream implementation and no stringstream in sight 
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
#if defined(OSTRSTREAM_NO_TERMINATION_BUG)
      const unsigned int kSize=100;
      char number[kSize];
      snprintf( number, kSize, "%d", (*it).second );
      resultString += string( " Stream " ) + (*it).first.value() 
	 + string( " : " ) + string( number ) + string(  "\n" );
#else
      //ostringstream number; // not yet available: <sstream>
      ostrstream number;
      number << (*it).second;
      resultString += string( " Stream " ) + (*it).first.value() 
	 + string( " : " ) + number.str() + string(  "\n" );
#endif
#else
      ostringstream number;
      number << (*it).second;
      resultString += string( " Stream " ) + (*it).first.value() 
	 + string( " : " ) + number.str() + string(  "\n" );
#endif
      sumAll += (*it).second;
   }
// buggy ostrstream implementation and no stringstream in sight 
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
#if defined(OSTRSTREAM_NO_TERMINATION_BUG)
   const unsigned int kSize=100;
   char summaryNumber[kSize];
   snprintf( summaryNumber, kSize, "%d", sumAll );
   resultString += string( "   Processed " ) + string( summaryNumber )
      + string( " stops.\n\n" );
#else
   //ostringstream summaryNumber; // not yet available: <sstream>
   ostrstream summaryNumber;
   summaryNumber << sumAll;
   resultString += string( "   Processed " ) + summaryNumber.str()
      + string( " stops.\n\n" );
#endif
#else
   ostringstream summaryNumber;
   summaryNumber << sumAll;
   resultString += string( "   Processed " ) + summaryNumber.str()
      + string( " stops.\n\n" );
#endif   
   return resultString;
}

//
// static member functions
//

// ----------------------------------------------------------------
// Revision history
//
// $Log: SummaryModule.cc,v $
// Revision 1.10  2003/09/19 21:03:50  cdj
// use new Keyword Command method
//
// Revision 1.9  2002/12/06 16:36:46  cleo3
// deal with strstream/stringstream
//
// Revision 1.8  1999/08/25 21:23:22  mkl
// ReportModule allows setting of report level and logging to files
//
// Revision 1.7  1999/02/23 16:56:22  mkl
// removed ./-i file
//
// Revision 1.6  1999/02/23 05:07:38  mkl
// new SunOS CC bug: dynamic-alloc version of (io)strstream ctor does not terminate properly
//
// Revision 1.5  1999/02/22 23:41:43  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.4  1998/11/17 21:56:41  mkl
// use cout instead of report( INFO...) to get rid of absurd error at suez exit time on Solaris (have no clue why)
//
// Revision 1.3  1998/11/09 19:33:14  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.2  1998/07/29 20:06:49  mkl
// new summary command implemented
//
// Revision 1.1  1998/07/28 15:53:19  mkl
// ripple effect: needed to include set
//
