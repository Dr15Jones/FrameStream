// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      LoaderMultiFactoryChooser
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Wed Nov 29 16:07:47 EST 2000
// $Id: LoaderMultiFactoryChooser.cc,v 1.1 2000/12/01 20:23:19 cdj Exp $
//
// Revision history
//
// $Log: LoaderMultiFactoryChooser.cc,v $
// Revision 1.1  2000/12/01 20:23:19  cdj
// now uses DynamicLoader package
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "CommandPattern/LoaderMultiFactoryChooser.h"
#include "CommandPattern/DefaultModule.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "CommandPattern.LoaderMultiFactoryChooser" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: LoaderMultiFactoryChooser.cc,v 1.1 2000/12/01 20:23:19 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
//LoaderMultiFactoryChooser::LoaderMultiFactoryChooser()
//{
//}

// LoaderMultiFactoryChooser::LoaderMultiFactoryChooser( const LoaderMultiFactoryChooser& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//LoaderMultiFactoryChooser::~LoaderMultiFactoryChooser()
//{
//}

//
// assignment operators
//
// const LoaderMultiFactoryChooser& LoaderMultiFactoryChooser::operator=( const LoaderMultiFactoryChooser& rhs )
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
std::vector<std::string>::iterator 
LoaderMultiFactoryChooser::choose( const std::string& iShortName,
				   std::vector<std::string>::iterator itBegin,
				   std::vector<std::string>::iterator itEnd ) 
{
   std::vector<std::string>::iterator returnValue = itBegin;
   unsigned int howManySuppliers = itEnd - itBegin;

   if( Switch::kOn == DefaultModule::instance()->usePrompting() 
       &&  1 < howManySuppliers ) // if more than one path
   {
      // ask user which one
     std::ostream& reportStream = report( SYSTEM, kFacilityString );
      
	reportStream << "\"" << iShortName
	 << "\" is present in more than one path!\n"
	 << "Please advise as to which one to use (by number):" 
	 << "\n";
      Count count = 0;
      for( std::vector<std::string>::iterator itObject = itBegin;
	   itObject != itEnd;
	   ++itObject )
      {
	 reportStream
	    << "  " << ++count << ") " 
	    << (*itObject) << iShortName
	    << "\n";
      }
      reportStream << std::endl;
      
      Count whichOne=1;
      DABoolean validChoice = false;
      do
      {
	 DABoolean badInput = false;
	 std::cin >> whichOne;
	 if(std::cin.fail() ) {
	    badInput = true;
	    std::cin.clear(); // reset bad state
	    std::cin.ignore( 80, '\n' ); // throw away the input (up to 80chars)
	 }
	 validChoice = 
	    ( true == badInput 
	      || whichOne < 1 || whichOne > count ) ? false : true;
	 if( false == validChoice )
	 {
	    report( ERROR, kFacilityString ) 
	       << "Bad choice. Try again!" << std::endl;
	 }
      } 
      while( false == validChoice );

      returnValue += (whichOne - 1 );
   }
   return returnValue;
}
//
// const member functions
//

//
// static member functions
//
