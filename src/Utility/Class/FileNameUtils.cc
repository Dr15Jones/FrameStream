// -*- C++ -*-
//
// Package:     Utility
// Module:      FileNameUtils
// 
// Description: <one line class summary>
//
// Implimentation:
//
// Author:      Martin Lohner
// Created:     Wed Jul 23 12:31:01 EDT 1997
// $Id: FileNameUtils.cc,v 1.1 2000/11/30 19:58:57 cdj Exp $
//
// Revision history
//
// $Log: FileNameUtils.cc,v $
// Revision 1.1  2000/11/30 19:58:57  cdj
// added FileNameUtils (from StringUtils in CommandPattern)
//
//
//

#include "Experiment/Experiment.h"

// system include files
#include <ctype.h>
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Utility/FileNameUtils.h"

// STL classes
#include <string>

using namespace std;
//
// constants, enums and typedefs
//
static const char* const kFacilityString = "Utility.FileNameUtils";

//
// static data member definitions
//

//
// static member functions
//

string
FileNameUtils::path( const std::string& sourceName )
{
   std::string::size_type lastSlash = sourceName.find_last_of( "/" );
   // includes trailing '/'
   std::string newString = sourceName.substr( 0, lastSlash+1 ); 

   return newString;
} 

string
FileNameUtils::filename( const std::string& sourceName )
{
   std::string::size_type lastSlash = sourceName.find_last_of( "/" );
   std::string newString = sourceName.substr( lastSlash+1, std::string::npos );

   return newString;
} 

string
FileNameUtils::basename( const std::string& sourceName, 
		      const char whichChar )
{
   // find filename for vecName
   std::string filenameString = filename( sourceName );

   std::string::size_type lastWhichChar = filenameString.find_last_of( whichChar );
   std::string newString = filenameString.substr( 0, lastWhichChar );

   return newString;
} 

string
FileNameUtils::extension( const std::string& sourceName, const char whichChar )
{
   // find filename for vecName
   std::string filenameString = filename( sourceName );

   // includes "whichChar"
   std::string::size_type lastWhichChar = filenameString.find_last_of( whichChar );
   if( std::string::npos == lastWhichChar ) return std::string( "" );
   std::string newString = filenameString.substr( lastWhichChar, std::string::npos );

   return newString;
}

