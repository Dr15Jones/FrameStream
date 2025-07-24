// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      Composite
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri Jul 18 15:23:57 EDT 2003
// $Id: Composite.cc,v 1.1 2003/09/19 20:45:35 cdj Exp $
//
// Revision history
//
// $Log: Composite.cc,v $
// Revision 1.1  2003/09/19 20:45:35  cdj
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

// user include files
//#include "Experiment/report.h"
#include "CommandPattern/Keyword/Composite.h"

#include "CommandPattern/Keyword/keyword_exceptions.h"

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "CommandPattern.Composite" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: Composite.cc,v 1.1 2003/09/19 20:45:35 cdj Exp $";
static const char* const kTagString = "$Name:  $";

namespace CommandPattern
{
namespace Keyword
{
//
// static data member definitions
//

//
// constructors and destructor
//
Composite::Composite(const std::string& iName) :
   Base(iName),
   m_minArgs(Base::kInfiniteMaxArgs),
   m_maxArgs(0)
{
}

// Composite::Composite( const Composite& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

Composite::~Composite()
{
   for(std::map<std::string,Base*>::iterator itWords =
	  m_keywords.begin();
       itWords != m_keywords.end(); ++itWords ) {
      delete (*itWords).second;
   }
}

//
// assignment operators
//
// const Composite& Composite::operator=( const Composite& rhs )
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
Composite::add(Base* iKeyword ) {
   std::map<std::string,Base*>::iterator itFound = 
      m_keywords.find( iKeyword->name() );

   unsigned int kwMinArg = iKeyword->minArgs();
   unsigned int kwMaxArg = iKeyword->maxArgs();

   unsigned int argSizeAdd = 0;
   if( iKeyword->name() != "" ) {
      //need to add to size of args to account for the keyword itself
      ++kwMinArg;
      ++kwMaxArg;
      ++argSizeAdd;
   }

   if( m_keywords.end() != itFound ) {
      //already have this keyword

      //need to do some checks on args
      unsigned int oldMinArg = iKeyword->minArgs()+argSizeAdd;
      unsigned int oldMaxArg = iKeyword->maxArgs()+argSizeAdd;

      if( (*itFound).second != iKeyword) {
	 delete (*itFound).second ;
      }
      (*itFound).second = iKeyword;

      if (oldMinArg < kwMinArg &&
	  oldMinArg == m_minArgs ) {
	 //must search for true min number of args
	 m_minArgs = kwMinArg;
	 for(std::map<std::string,Base*>::iterator itWords =
		m_keywords.begin();
	     itWords != m_keywords.end(); ++itWords ) {
	    if( (*itWords).second->minArgs() +argSizeAdd< m_minArgs ) {
	       m_minArgs = (*itWords).second->minArgs()+argSizeAdd;
	    }
	 }

      }
      if( oldMaxArg > kwMaxArg &&
	  oldMaxArg == m_maxArgs ) {
	 //must search for true max number of args
	 m_maxArgs = kwMaxArg;
	 for(std::map<std::string,Base*>::iterator itWords =
		m_keywords.begin();
	     itWords != m_keywords.end();
	     ++itWords ) {
	    if( (*itWords).second->maxArgs() +argSizeAdd > m_maxArgs ) {
	       m_maxArgs = (*itWords).second->maxArgs() + argSizeAdd;
	    }
	 }
      }
   } else {
      m_keywords.insert( make_pair(iKeyword->name(), iKeyword ) );
   }

   if( m_minArgs > kwMinArg ) {
      m_minArgs = kwMinArg;
   }

   if( m_maxArgs < kwMaxArg ) {
      m_maxArgs = kwMaxArg;
   }

}

int 
Composite::implementExecute( int argc, char** argv )
{
   std::string keywordChoosen = name();
   int startArg = 1;

   std::map<std::string,Base*>::iterator itKeyword;
   if( argc == 0 ) {
      //no arguments to the command
      itKeyword = m_keywords.find(std::string(""));
      startArg = 0;

      if( itKeyword == m_keywords.end() ) {
	 throw TooFewArgsException(name(), minArgs(), 0 );
      }
   } else {
      itKeyword = m_keywords.find(argv[0]);
      if( itKeyword == m_keywords.end() ) {
	 //try falling back to no argument
	 itKeyword = m_keywords.find(std::string(""));
	 startArg = 0;
	 
	 if( itKeyword == m_keywords.end() ) {
	    throw UnknownArgException(name(), argv[0] );
	 }
	 if( (*itKeyword).second->maxArgs() == 0 ) {
	    //our non-keyword doesn't take any arguments
	    // but arguments were given.
	    throw UnknownArgException(name(),argv[0] );
	 }
      }
   }
   //found a good keyword
   
   return (*itKeyword).second->execute(argc-startArg, argv+startArg);
}

//
// const member functions
//

//
// static member functions
//
} //namespace Keyword
} //namespace CommandPattern
