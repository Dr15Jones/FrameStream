// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      CPCommandWithKeywords
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri Jul 18 15:53:04 EDT 2003
// $Id: CPCommandWithKeywords.cc,v 1.1 2003/09/19 20:45:33 cdj Exp $
//
// Revision history
//
// $Log: CPCommandWithKeywords.cc,v $
// Revision 1.1  2003/09/19 20:45:33  cdj
// first submission
//

#include "Experiment/Experiment.h"

// system include files
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#include <assert.h>

// user include files
//#include "Experiment/report.h"
#include "CommandPattern/CPCommandWithKeywords.h"

#include "CommandPattern/Keyword/ExceptionBase.h"
#include "CommandPattern/Keyword/Composite.h"

#include "CommandPattern/Keyword/NoArg.h"

using namespace CommandPattern::Keyword;
//
// constants, enums and typedefs
//

static const char* const kFacilityString = "CommandPattern.CPCommandWithKeywords" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: CPCommandWithKeywords.cc,v 1.1 2003/09/19 20:45:33 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
CPCommandWithKeywords::CPCommandWithKeywords(
   const string& iName,
   Module* iModule,
   DABoolean iInternalCommand,
   const string& iHelpString) :
   Command(iName, iModule, iInternalCommand)
{
   setHelpString(iHelpString);

   m_keywords = new Composite( name() );

   m_keywords->add( new NoArg<CPCommandWithKeywords>(
      "help",
      this,
      &CPCommandWithKeywords::helpHandler ) );
}

// CPCommandWithKeywords::CPCommandWithKeywords( const CPCommandWithKeywords& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

CPCommandWithKeywords::~CPCommandWithKeywords()
{
   delete m_keywords;
}

//
// assignment operators
//
// const CPCommandWithKeywords& CPCommandWithKeywords::operator=( const CPCommandWithKeywords& rhs )
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
CPCommandWithKeywords::add( CommandPattern::Keyword::Base* iKeyword )
{
   m_keywords->add(iKeyword);
}

int
CPCommandWithKeywords::execute(int argc, char* argv[] ) 
{
   assert( 0 < argc );

   try {
      //strip of the first argument since it is the name of the command
      return m_keywords->execute(argc-1, argv+1 );
   } catch(ExceptionBase& iException ) {
      string userCommand( argv[0] );

      const string kSpace(" ");
      for( int index = 1; index < argc; ++ index ) {
	 userCommand += kSpace;
	 userCommand += argv[index];
      }
      report(ERROR,name().c_str()) << "command \""
				   << userCommand <<"\"\n"
				   << "had the error "<<"\n"
				   <<iException.what() <<endl;
   }
   return COMMAND_ERROR;
}


int
CPCommandWithKeywords::helpHandler() 
{
   report(SYSTEM, name().c_str() ) << "\n" << helpString() << endl;
   return COMMAND_OK;
}

//
// const member functions
//

//
// static member functions
//
