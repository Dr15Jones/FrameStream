// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      NumArgComposite
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Sun Jul 20 09:49:47 EDT 2003
// $Id: NumArgComposite.cc,v 1.1 2003/09/19 20:45:35 cdj Exp $
//
// Revision history
//
// $Log: NumArgComposite.cc,v $
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
#include <assert.h>

// user include files
//#include "Experiment/report.h"
#include "CommandPattern/Keyword/NumArgComposite.h"
#include "CommandPattern/Keyword/keyword_exceptions.h"


//
// constants, enums and typedefs
//
namespace CommandPattern
{
namespace Keyword
{

static const char* const kFacilityString = "CommandPattern.NumArgComposite" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: NumArgComposite.cc,v 1.1 2003/09/19 20:45:35 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
NumArgComposite::NumArgComposite(const string& iName) :
   Base(iName)
{
}

// NumArgComposite::NumArgComposite( const NumArgComposite& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

NumArgComposite::~NumArgComposite()
{
   for(STL_VECTOR(Base*)::iterator itBase = m_keywords.begin();
       itBase != m_keywords.end();
       ++itBase ) {
      delete (*itBase);
   }
}

//
// assignment operators
//
// const NumArgComposite& NumArgComposite::operator=( const NumArgComposite& rhs )
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
NumArgComposite::add(Base* iKeyword)
{
   //check where this should be added to our list
   for(STL_VECTOR(Base*)::iterator itBase = m_keywords.begin();
       itBase != m_keywords.end();
       ++itBase ) {
      if( (*itBase)->minArgs() > iKeyword->minArgs() ) {
	 if( (*itBase)->minArgs() > iKeyword->maxArgs() ) {
	    //check that next item doesn't overlap
	    STL_VECTOR(Base*)::iterator itNext = itBase+1;
	    if( itNext == m_keywords.end() ) {
	       break;
	    }

	    if( iKeyword->maxArgs() < (*itNext)->minArgs() ) {
	       m_keywords.insert(itBase, iKeyword);
	       return;
	    } else {
	       report(EMERGENCY, kFacilityString)
		  <<"keyword "<<name()
		  <<" has improper keyword inserted whose num args "
		  <<iKeyword->minArgs() <<" "<<iKeyword->maxArgs()
		  <<" overlaps with a previous insert that uses "
		  <<(*itNext)->minArgs() <<" "<<(*itNext)->maxArgs()
		  << endl;
	       assert(false);
	       ::exit(-1);
	    }
	 } else {
	    report(EMERGENCY, kFacilityString)
	       <<"keyword "<<name()
	       <<" has improper keyword inserted whose num args "
	       <<iKeyword->minArgs() <<" "<<iKeyword->maxArgs()
	       <<" overlaps with a previous insert that uses "
	       <<(*itBase)->minArgs() <<" "<<(*itBase)->maxArgs()
	       << endl;
	    assert(false);
	    ::exit(-1);
	 }
      }
   }

   m_keywords.push_back(iKeyword);
}

int 
NumArgComposite::implementExecute( int argc, char** argv )
{
   for(STL_VECTOR(Base*)::iterator itBase = m_keywords.begin();
       itBase != m_keywords.end();
       ++itBase ) {
      if( argc >= (*itBase)->minArgs() && argc <= (*itBase)->maxArgs() ) {
	 return (*itBase)->execute(argc, argv);
      }
   }

   if( m_keywords.size() != 0 ) {
      if( m_keywords.front()->minArgs() > argc ) {
	 throw TooFewArgsException(name(), m_keywords.front()->minArgs(),
				   argc );
      }
      if( m_keywords.back()->maxArgs() < argc ) {
	 throw TooFewArgsException(name(), m_keywords.back()->maxArgs(),
				   argc );
      }
   }

   throw WrongNumberArgsException(name(),argc );

   return 0;
}

//
// const member functions
//

//
// static member functions
//

} //namespace Keyword
} //namespace CommandPattern
