#if !defined(COMMANDPATTERN_LOADER_CC)
#define COMMANDPATTERN_LOADER_CC
// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      Loader
// 
// Description: 
//
// Implementation: 
//
// Author:      Valentine Kouznetsov
// Created:     Fri Feb 28 09:41:27 EST 2003
// $Id: Loader.cc,v 1.21 2003/03/14 17:43:02 vk Exp $
//
// $Log: Loader.cc,v $
// Revision 1.21  2003/03/14 17:43:02  vk
// Fix sstream for OSF using USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG & strstream.h
//
// Revision 1.20  2003/03/12 21:34:07  vk
// Redesign loader class into LoaderBase, Loader (single loader) and MultiLoader
//
//
// See LoaderBase class for more detail

// system include files
#include <stdlib.h> // for exit
#include <assert.h>
#include <iostream>
#include <utility>
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
#include <strstream.h>
#else
#include <sstream>
#endif

#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/Experiment.h"
#include "Experiment/report.h"

#include "CommandPattern/Template/LoaderBase.cc"
#include "CommandPattern/Loader.h"
#include "CommandPattern/LoaderMultiFactoryChooser.h"
#include "CommandPattern/StringUtilities.h"

#include "DynamicLoader/DLSharedObjectHandler.h"
#include "DynamicLoader/DLFactoryBase.h"
#include "Utility/StringTokenizer.h"

// STL classes
#include <vector>
#include <map>

//
// constants, enums and typedefs
//
//FILESCOPE_IN_TEMPLATE_CC_BUG const char* const kLoaderFacilityString
static const char* const kLoaderFacilityString
 = "CommandPattern.Loader";

//
// static data member definitions
//

//
// constructors and destructor
//
template< class T >
Loader< T >::Loader( const string& environment ) 
   :  LoaderBase<T>(environment)
{
}

//
// static member functions
//
template< class T >
DABoolean
Loader< T >::load( const string& iName )
{
  return LoaderBase<T>::load(iName);
}

template< class T >
pair<string,string>
Loader< T >::disassembleName(const string& iName) const
{

   // first disassemble <full_path_to_object>/ part and return remaining string
   string shortName = LoaderBase<T>::shortName(iName);
   string blank = "";
   return pair<string,string>(shortName,blank);

}

template< class T >
string
Loader< T >::makeErrorMesg( const string& iName ) const
{
   string returnValue = string( "Loader " ) + LoaderBase<T>::makeErrorMesg(iName);
   return returnValue;
}



#endif /* COMMANDPATTERN_LOADER_CC */
