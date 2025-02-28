// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSIstreamSwapBytesWordReader
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri Oct  6 15:01:46 EDT 2000
// $Id: PDSIstreamSwapBytesWordReader.cc,v 1.4 2002/08/16 15:42:40 cleo3 Exp $
//
// Revision history
//
// $Log: PDSIstreamSwapBytesWordReader.cc,v $
// Revision 1.4  2002/08/16 15:42:40  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.3  2002/02/08 16:47:01  cdj
// fixed header reading problem due to incorrect bit mask used to count zeros in strings
//
// Revision 1.2  2001/01/15 21:07:55  cdj
// Now properly reads Tags when doing byteSwapping
//
// Revision 1.1  2000/10/07 18:24:22  cdj
// can now read files that were written from a different endian machine
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
#include "C++Std/iostream.h"

// user include files
//#include "Experiment/report.h"
#include "PackedDataStreamsDelivery/PDSIstreamSwapBytesWordReader.h"
#include "BinaryDelivery/ByteSwapping.h"

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

static const char* const kFacilityString = "PackedDataStreamsDelivery.PDSIstreamSwapBytesWordReader" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: PDSIstreamSwapBytesWordReader.cc,v 1.4 2002/08/16 15:42:40 cleo3 Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
//PDSIstreamSwapBytesWordReader::PDSIstreamSwapBytesWordReader()
//{
//}

// PDSIstreamSwapBytesWordReader::PDSIstreamSwapBytesWordReader( const PDSIstreamSwapBytesWordReader& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//PDSIstreamSwapBytesWordReader::~PDSIstreamSwapBytesWordReader()
//{
//}

//
// assignment operators
//
// const PDSIstreamSwapBytesWordReader& PDSIstreamSwapBytesWordReader::operator=( const PDSIstreamSwapBytesWordReader& rhs )
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
PDSIstreamSwapBytesWordReader::readWords( UInt32* iBuffer,
					  unsigned int iNumberOfWords,
					  const char* iActivity )
{
   DABoolean returnValue = PDSIstreamWordReader::readWords(
      iBuffer, iNumberOfWords, iActivity );
   
   if( returnValue ) {
      for( UInt32* itBuffer = iBuffer; 
	   itBuffer != iBuffer + iNumberOfWords;
	   ++itBuffer ) {
	 *itBuffer = swapBytesInUInt32(*itBuffer );
      }
   }
   return returnValue;
}


void
PDSIstreamSwapBytesWordReader::unswapString( UInt32* iBegin,
					     UInt32 iNumberOfStrings )
{
   UInt32 numberOfNulls = 0;
   UInt32* itBuffer = iBegin;
   while( numberOfNulls < iNumberOfStrings ) {
      *itBuffer = swapBytesInUInt32(*itBuffer );
     
      //Check for 0's
      if( 0 == (*itBuffer & 0x000000FF) ) { ++numberOfNulls; }
      if( 0 == (*itBuffer & 0x0000FF00) ) { ++numberOfNulls; }
      if( 0 == (*itBuffer & 0x00FF0000) ) { ++numberOfNulls; }
      if( 0 == (*itBuffer & 0xFF000000) ) { ++numberOfNulls; }
      ++itBuffer;
   }
}

void
PDSIstreamSwapBytesWordReader::unswapStringArray( UInt32* iBegin,
						  UInt32* iEnd )
{
   for( UInt32* itBuffer = iBegin; 
	itBuffer != iEnd;
	++itBuffer ) {
      *itBuffer = swapBytesInUInt32(*itBuffer );
   }
}

//
// const member functions
//

//
// static member functions
//
