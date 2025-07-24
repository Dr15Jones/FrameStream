//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSSourceFormat
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon Sep 25 15:42:15 EDT 2000
// $Id: PDSSourceFormat.cc,v 1.6 2002/11/21 21:16:57 cleo3 Exp $
//
// Revision history
//
// $Log: PDSSourceFormat.cc,v $
// Revision 1.6  2002/11/21 21:16:57  cleo3
// changed fstream.h to C++Std/fstream.h
//
// Revision 1.5  2002/09/19 18:06:31  cdj
// can now read gzipped files with extension .pds.gz
//
// Revision 1.4  2002/06/12 16:18:20  cdj
// previous change now compiles under OSF1
//
// Revision 1.3  2002/06/11 17:55:55  cdj
// added ability to set the default streams based on the contents of the source file
//
// Revision 1.2  2000/10/02 20:42:17  cdj
// now compiles and links using cxx
//
// Revision 1.1.1.1  2000/09/29 17:48:06  cdj
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
#include <fstream>

// user include files
#include "Experiment/report.h"
#include "PackedDataStreamsDelivery/PDSSourceFormat.h"
#include "PackedDataStreamsDelivery/PDSSourceBinder.h"
#include "PackedDataStreamsDelivery/PDSProxyDeliverer.h"
#include "PackedDataStreamsDelivery/PDSDExceptionBase.h"
#include "DataDelivery/Binder.h"

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

static const char* const kFacilityString = "PackedDataStreamsDelivery.PDSSourceFormat" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: PDSSourceFormat.cc,v 1.6 2002/11/21 21:16:57 cleo3 Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
PDSSourceFormat::PDSSourceFormat() :
   SourceFormat( BinderType("PackedDataStreams") )
{
   addExtension( ".pds" );
   addExtension( ".pds.gz" );
}

// PDSSourceFormat::PDSSourceFormat( const PDSSourceFormat& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

PDSSourceFormat::~PDSSourceFormat()
{
}

//
// assignment operators
//
// const PDSSourceFormat& PDSSourceFormat::operator=( const PDSSourceFormat& rhs )
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
BinderBase*
PDSSourceFormat::createBinder( const std::string& iName, 
			       const Stream::Set& iBindStreams ) 
{
   BinderBase* returnValue 
      = new Binder< PDSSourceBinder >(
         new PDSSourceBinder( iName.c_str(), iBindStreams ),
         type()
         );

   return returnValue;
}   

//
// const member functions
//
const Stream::Set&
PDSSourceFormat::defaultStreams( const std::string& iName )
{
   static Stream::Set s_set;
   s_set.erase(s_set.begin(), s_set.end());
   try {
      std::ifstream f(iName.c_str());
      if( not f) {
	 PDSProxyDeliverer reader( f );
	 s_set = reader.supplies();
      } else {
	 report(SYSTEM, kFacilityString) <<"Error openning file: "<<iName<<std::endl;
      }
   } catch( const PDSDExceptionBase& iException) {
      report(SYSTEM, kFacilityString) <<"Error while reading file: "<<iName<<"\n"<<iException.what() <<std::endl;
   }
   return s_set;
};

//
// static member functions
//
