// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      StringUtilities
// 
// Description: <one line class summary>
//
// Implimentation:
//
// Author:      Martin Lohner
// Created:     Wed Jul 23 12:31:01 EDT 1997
// $Id: StringUtilities.cc,v 1.10 2000/12/02 19:19:27 cdj Exp $
//
// Revision history
//
// $Log: StringUtilities.cc,v $
// Revision 1.10  2000/12/02 19:19:27  cdj
// removed file name related functions (now in Utility/FileNameUtils)
//
// Revision 1.9  1999/11/10 22:22:59  cdj
// fixed writing off end of array and memory leak in StringUtil::toUppercase
//
// Revision 1.8  1999/09/10 01:04:38  mkl
// 1) new smarter history command.
// 2) new "uppercase" function, since our compilers don't support it yet.
// 3) moved "Conversion" class to CommandPattern (needed by HistoryCommand).
//
// Revision 1.7  1999/01/27 22:54:49  mkl
// rewrote StringUtil utility functions
//
// Revision 1.6  1998/11/09 19:31:10  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.5  1998/03/11 19:10:35  mkl
// new Parameter sources
//
// Revision 1.4  1997/10/15 02:20:37  mkl
// generalize find functions for different characters
//
// Revision 1.3  1997/10/07 19:25:34  mkl
// cout --> report( INFO ) and kFacilityString update
//
// Revision 1.2  1997/10/02 22:36:12  mkl
// now have string utility functions for path, filename, basename, and extension
//
// Revision 1.1  1997/09/04 06:37:29  mkl
// moved JobControl/StringUtilities here
//
//

#include "Experiment/Experiment.h"

// system include files
#include <ctype.h>
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "CommandPattern/StringUtilities.h"

// STL classes
#include <string>
#include <cstring>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "CommandPattern.StringUtilities";

//
// static data member definitions
//

//
// constructors and destructor
//
//StringUtilities::StringUtilities()
//{
//}

// StringUtilities::StringUtilities( const StringUtilities& )
// {
// }

//StringUtilities::~StringUtilities()
//{
//}

//
// assignment operators
//
// const StringUtilities& StringUtilities::operator=( const StringUtilities& )
// {
// }

//
// member functions
//

//
// const member functions
//

//
// static member functions
//


std::string
StringUtil::toUppercase( const std::string& iString )
{
   size_t length = iString.length();
   char* charArray = new char[ length +1 ];
   strncpy( charArray, iString.data(), length );
   charArray[length] = '\0';
   for( size_t i = 0; i < length; ++i )
   {
      char& c = charArray[i];
      c = (isascii(c) && islower(c)) ? toupper(c) : c;
   }
   std::string returnValue( charArray );
   delete [] charArray;
   return returnValue;
}
