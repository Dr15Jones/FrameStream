// -*- C++ -*-
//
// Package:     <PackedDataStreamsStorage>
// Module:      PDSSinkFormat
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri Sep 22 15:35:44 EDT 2000
// $Id: PDSSinkFormat.cc,v 1.3 2001/06/15 21:07:18 cdj Exp $
//
// Revision history
//
// $Log: PDSSinkFormat.cc,v $
// Revision 1.3  2001/06/15 21:07:18  cdj
// can now specify data (not) to store
//
// Revision 1.2  2000/10/02 20:46:50  cdj
// now compiles and links using cxx
//
// Revision 1.1.1.1  2000/09/29 17:49:41  cdj
// imported
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "PackedDataStreamsStorage/PDSSinkFormat.h"
#include "PackedDataStreamsStorage/PDSSinkBinder.h"

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

static const char* const kFacilityString = "PackedDataStreamsStorage.PDSSinkFormat" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: PDSSinkFormat.cc,v 1.3 2001/06/15 21:07:18 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
PDSSinkFormat::PDSSinkFormat()
{
   // add extensions that this format recognizes
   addExtension( string( ".pds" ) );
}

// PDSSinkFormat::PDSSinkFormat( const PDSSinkFormat& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

PDSSinkFormat::~PDSSinkFormat()
{
}

//
// assignment operators
//
// const PDSSinkFormat& PDSSinkFormat::operator=( const PDSSinkFormat& rhs )
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
DataSinkBinder* 
PDSSinkFormat::createBinder( const string& iName,
			     const Stream::Set& iBindStreams )
{
   return new PDSSinkBinder( iName.c_str(), iBindStreams );
}

DataSinkBinder* 
PDSSinkFormat::createBinder( const string& iName,
			     const Stream::Set& iBindStreams,
			     const StreamToDataStringTagsToStoreMap& iStreamTagsMap )
{
   return new PDSSinkBinder( iName.c_str(), iBindStreams,
                             iStreamTagsMap );
}

DABoolean 
PDSSinkFormat::canSpecifyDataToStore() const 
{
   return true;
}

//
// const member functions
//

//
// static member functions
//
