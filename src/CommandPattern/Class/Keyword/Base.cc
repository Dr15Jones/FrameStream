// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      Base
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri Jul 18 23:45:51 EDT 2003
// $Id: Base.cc,v 1.1 2003/09/19 20:45:34 cdj Exp $
//
// Revision history
//
// $Log: Base.cc,v $
// Revision 1.1  2003/09/19 20:45:34  cdj
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
#include "CommandPattern/Keyword/Base.h"

#include "CommandPattern/Keyword/keyword_exceptions.h"

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "CommandPattern.Base" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: Base.cc,v 1.1 2003/09/19 20:45:34 cdj Exp $";
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
//Base::Base()
//{
//}

// Base::Base( const Base& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//Base::~Base()
//{
//}

//
// assignment operators
//
// const Base& Base::operator=( const Base& rhs )
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
int 
Base::execute(int argc, char** argv )
{
   if( argc < minArgs() ) {
      throw TooFewArgsException(name(), minArgs(), argc);
   }
   if( argc > maxArgs() ) {
      throw TooManyArgsException(name(),maxArgs(),argc);
   }

   return implementExecute(argc, argv);
}

//
// const member functions
//

//
// static member functions
//
} //namespace Keyword
} //namespace CommandPattern
