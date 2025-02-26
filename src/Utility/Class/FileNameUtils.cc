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
FileNameUtils::path( const string& sourceName )
{
   string::size_type lastSlash = sourceName.find_last_of( "/" );
   // includes trailing '/'
   string newString = sourceName.substr( 0, lastSlash+1 ); 

   return newString;
} 

string
FileNameUtils::filename( const string& sourceName )
{
   string::size_type lastSlash = sourceName.find_last_of( "/" );
   string newString = sourceName.substr( lastSlash+1, string::npos );

   return newString;
} 

string
FileNameUtils::basename( const string& sourceName, 
		      const char whichChar )
{
   // find filename for vecName
   string filenameString = filename( sourceName );

   string::size_type lastWhichChar = filenameString.find_last_of( whichChar );
   string newString = filenameString.substr( 0, lastWhichChar );

   return newString;
} 

string
FileNameUtils::extension( const string& sourceName, const char whichChar )
{
   // find filename for vecName
   string filenameString = filename( sourceName );

   // includes "whichChar"
   string::size_type lastWhichChar = filenameString.find_last_of( whichChar );
   if( string::npos == lastWhichChar ) return string( "" );
   string newString = filenameString.substr( lastWhichChar, string::npos );

   return newString;
}

