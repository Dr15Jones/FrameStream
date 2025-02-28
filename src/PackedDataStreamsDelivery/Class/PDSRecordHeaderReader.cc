// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSRecordHeaderReader
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon Sep 25 11:01:36 EDT 2000
// $Id: PDSRecordHeaderReader.cc,v 1.4 2000/10/07 18:24:23 cdj Exp $
//
// Revision history
//
// $Log: PDSRecordHeaderReader.cc,v $
// Revision 1.4  2000/10/07 18:24:23  cdj
// can now read files that were written from a different endian machine
//
// Revision 1.3  2000/10/04 18:52:16  cdj
// PDSProxyDeliverer.cc
//
// Revision 1.2  2000/10/02 20:42:16  cdj
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
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#include <unistd.h>  // Must do standard C read on SUN
#include <errno.h>
#include <string.h>

// user include files
#include "Experiment/report.h"
#include "PackedDataStreamsDelivery/PDSRecordHeaderReader.h"
#include "PackedDataStreamsDelivery/PDSIstreamWordReader.h"

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

static const char* const kFacilityString = "PackedDataStreamsDelivery.PDSRecordHeaderReader" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: PDSRecordHeaderReader.cc,v 1.4 2000/10/07 18:24:23 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
//PDSRecordHeaderReader::PDSRecordHeaderReader()
//{
//}

// PDSRecordHeaderReader::PDSRecordHeaderReader( const PDSRecordHeaderReader& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//PDSRecordHeaderReader::~PDSRecordHeaderReader()
//{
//}

//
// assignment operators
//
// const PDSRecordHeaderReader& PDSRecordHeaderReader::operator=( const PDSRecordHeaderReader& rhs )
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
DABoolean
PDSRecordHeaderReader::read( PDSIstreamWordReader& iReader )
{
// Read the record header
   UInt32 headerBuffer[PDSRecordHeader::kNumberOfWords];

   if( ! iReader.readWords(headerBuffer, 
			   sizeof(headerBuffer)/sizeof(UInt32),
			   "reading record header") ) {
      //saw end of file
      return false;
   }

   //now decode the header
   UInt64 time = UInt64(headerBuffer[kTimeLowerWord]) | 
      ( UInt64(headerBuffer[kTimeUpperWord]) << 32 ) ;
   m_syncValue = SyncValue( headerBuffer[kRunNumberWord],
			    headerBuffer[kEventNumberWord],
			    time );
   m_recordType = headerBuffer[kRecordTypeWord];
   m_bodyLength = headerBuffer[kSizeOfBodyWord];

   return true ;   
}

//
// const member functions
//

//
// static member functions
//
