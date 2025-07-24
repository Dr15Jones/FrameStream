// -*- C++ -*-
//
// Package:     <PackedDataStreamsStorage>
// Module:      PDSSinkController
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri Sep 22 14:10:12 EDT 2000
// $Id: PDSSinkController.cc,v 1.2 2000/10/02 20:46:50 cdj Exp $
//
// Revision history
//
// $Log: PDSSinkController.cc,v $
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
#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "PackedDataStreamsStorage/PDSSinkController.h"
#include "PackedDataStreamsStorage/PDSProxyStorer.h"

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

static const char* const kFacilityString = "PackedDataStreamsStorage.PDSSinkController" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: PDSSinkController.cc,v 1.2 2000/10/02 20:46:50 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
PDSSinkController::PDSSinkController(const std::string& iFileName,
				     const Stream::Set& iWriteStreams,
				     const PDSDataToStore& iDataToStore ) :
   m_fileName(iFileName),
   m_oStream( *(new ofstream(iFileName.c_str()) ) )
{

//
// See if this source is good
//
   if (
#if defined(NO_IS_OPEN_FUNCTION_IN_FSTREAM_BUG)
      ! (*((*(ofstream*)&m_oStream).rdbuf())).is_open()
#else
      ! (*(ofstream*)&m_oStream).is_open()
#endif
      ) {
      report( ERROR ,
              kFacilityString )
                 << "\n\tUnable to open PDS file called "
                 << m_fileName
                 << std::endl ;
      setInitializationStatus( kInitSinkInaccessible ) ;

   } else {

      m_proxyStorer = new PDSProxyStorer( m_oStream,
					  iWriteStreams,
					  iDataToStore ) ;
//
// set up the Records to be supplied
//
      if ( ! setRecordsToStore( iWriteStreams ) ) {
         setInitializationStatus( 
            DataSinkController::kInitInvalidStopsForSink );
      }
   }
}

// PDSSinkController::PDSSinkController( const PDSSinkController& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

PDSSinkController::~PDSSinkController()
{
   delete (&m_oStream);
}

//
// assignment operators
//
// const PDSSinkController& PDSSinkController::operator=( const PDSSinkController& rhs )
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

//
// const member functions
//
ProxyStorer* 
PDSSinkController::createProxyStorer() const
{
   return m_proxyStorer;
}

//
// static member functions
//
