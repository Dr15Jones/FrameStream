// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSRecordReadBuffer
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon Sep 25 15:13:22 EDT 2000
// $Id: PDSRecordReadBuffer.cc,v 1.4 2001/08/16 21:10:46 cdj Exp $
//
// Revision history
//
// $Log: PDSRecordReadBuffer.cc,v $
// Revision 1.4  2001/08/16 21:10:46  cdj
// now check to make sure we do not reach end of file prematurely
//
// Revision 1.3  2000/10/07 18:24:24  cdj
// can now read files that were written from a different endian machine
//
// Revision 1.2  2000/10/04 18:52:17  cdj
// PDSProxyDeliverer.cc
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
#include "PackedDataStreamsDelivery/PDSRecordReadBuffer.h"
#include "PackedDataStreamsDelivery/PDSIstreamWordReader.h"
#include "PackedDataStreamsDelivery/PDSDReadFailedException.h"

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

static const char* const kFacilityString = "PackedDataStreamsDelivery.PDSRecordReadBuffer" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: PDSRecordReadBuffer.cc,v 1.4 2001/08/16 21:10:46 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
PDSRecordReadBuffer::PDSRecordReadBuffer() :
   m_buffer(0),
   m_sizeOfBuffer(0),
   m_wordsInBuffer(0)
{
}

// PDSRecordReadBuffer::PDSRecordReadBuffer( const PDSRecordReadBuffer& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

PDSRecordReadBuffer::~PDSRecordReadBuffer()
{
   delete [] m_buffer;
}

//
// assignment operators
//
// const PDSRecordReadBuffer& PDSRecordReadBuffer::operator=( const PDSRecordReadBuffer& rhs )
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
void
PDSRecordReadBuffer::read( PDSIstreamWordReader& iReader, UInt32 iWordsToRead )
{
   if( iWordsToRead > m_sizeOfBuffer ) {
      delete [] m_buffer;
      m_buffer = new UInt32[iWordsToRead];
      m_sizeOfBuffer = iWordsToRead;
   }

   m_wordsInBuffer = iWordsToRead;

   if(!iReader.readWords( m_buffer, iWordsToRead, "reading record body" ) ){
      throw PDSDReadFailedException("reached end of file while reading record body");
   }
}

//
// const member functions
//

//
// static member functions
//
