// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSBuiltinContainerSourceStream
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri Apr  5 20:55:20 EST 2002
// $Id: PDSBuiltinContainerSourceStream.cc,v 1.2 2002/08/09 18:03:55 cdj Exp $
//
// Revision history
//
// $Log: PDSBuiltinContainerSourceStream.cc,v $
// Revision 1.2  2002/08/09 18:03:55  cdj
// removed inappropriate use of reinterpret_cast
//
// Revision 1.1  2002/04/06 19:03:15  cdj
// added a specialized SourceStream to handle containers of builtin types
//

#include "Experiment/Experiment.h"

// system include files
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

// user include files
//#include "Experiment/report.h"
#include "PackedDataStreamsDelivery/PDSBuiltinContainerSourceStream.h"

#include "PackedDataStreamsFormat/PDSPackerTemplate.h"
#include "PackedDataStreamsFormat/PDSStringPacker.h"
#include "BinaryDelivery/ByteSwapping.h"

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "PackedDataStreamsDelivery.PDSBuiltinContainerSourceStream" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: PDSBuiltinContainerSourceStream.cc,v 1.2 2002/08/09 18:03:55 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//

// PDSBuiltinContainerSourceStream::PDSBuiltinContainerSourceStream( const PDSBuiltinContainerSourceStream& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//
// assignment operators
//
// const PDSBuiltinContainerSourceStream& PDSBuiltinContainerSourceStream::operator=( const PDSBuiltinContainerSourceStream& rhs )
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
template< class T>
static
inline
void
unpack_data( SMPackerBase* iPacker, const UInt32* iBuffer,
	     unsigned char& ioStartBit, T& oData ) 
{
   //NOTE: CC 4.2 can not use static_cast here
   oData =((SMPackerTemplate<T>*)(iPacker))->unpack(
      *iBuffer, *(iBuffer+1), ioStartBit );
}

#define UNPACK_DATA \
unpack_data( m_packer, m_startWord, m_startBit, iData ); \
advanceStartWordIfNeeded();

SMSourceStream& 
PDSBuiltinContainerSourceStream::operator>>( char& iData )
{
   UNPACK_DATA
   return *this;
}

SMSourceStream& 
PDSBuiltinContainerSourceStream::operator>>( short& iData )
{
   UNPACK_DATA
   return *this;
}

SMSourceStream& 
PDSBuiltinContainerSourceStream::operator>>( int& iData )
{
   UNPACK_DATA
   return *this;
}

SMSourceStream& 
PDSBuiltinContainerSourceStream::operator>>( long& iData )
{
   UNPACK_DATA
   return *this;
}

SMSourceStream& 
PDSBuiltinContainerSourceStream::operator>>( unsigned char& iData )
{
   UNPACK_DATA
   return *this;
}

SMSourceStream& 
PDSBuiltinContainerSourceStream::operator>>( unsigned short& iData )
{
   UNPACK_DATA
   return *this;
}

SMSourceStream& 
PDSBuiltinContainerSourceStream::operator>>( unsigned int& iData )
{
   UNPACK_DATA
   return *this;
}

SMSourceStream& 
PDSBuiltinContainerSourceStream::operator>>( unsigned long& iData )
{
   UNPACK_DATA
   return *this;
}

SMSourceStream& 
PDSBuiltinContainerSourceStream::operator>>( float& iData )
{
   UNPACK_DATA
   return *this;
}
SMSourceStream& 
PDSBuiltinContainerSourceStream::operator>>( double& iData )
{
   UNPACK_DATA
   return *this;
}

SMSourceStream& 
PDSBuiltinContainerSourceStream::operator>>( string& iData )
{
   const DABoolean byteSwapped = 
      (reinterpret_cast<SMPackerBase*>(PDSStringPacker::kByteSwapped) == 
         m_packer);

   //the string has been padded so that it starts on a 32bit boundary
   if( m_startBit != 0 ) {
      SMFixedPacker<UInt32> padPacker( 32 - (m_startBit%32), 1, 0);
      padPacker.unpack(*m_startWord, *(m_startWord+1),m_startBit);
      advanceStartWordIfNeeded();
   }

   const char* startOfString = reinterpret_cast<const char*>(m_startWord) ;
   if( ! byteSwapped ) {
      iData = string( startOfString  );
   } else {
      //need to copy the buffer and then reswap the bytes
      unsigned int distanceToFirstZero = 
	 strlen( startOfString );

      
      //determine what word the first zero is on
      unsigned int numberOfWords = distanceToFirstZero /4 + 1;

      //create a temporary buffer for the words
      UInt32 * buffer = new UInt32[ numberOfWords ];

      memcpy( buffer, startOfString, 4*numberOfWords );

      for( UInt32* itBuffer = buffer; 
	   itBuffer < buffer + numberOfWords;
	   ++itBuffer ) {
	 *itBuffer = swapBytesInUInt32(*itBuffer  );
      }

      iData = string( reinterpret_cast<char*>(buffer) );

      delete [] buffer;
   }
   
   //now we need to advance our buffer pointers
   //The string actually takes up an even number of bytes (past the 

   unsigned int numberOfBytes = iData.size()+ 1;
   unsigned int paddingAtEnd = ( (0 == numberOfBytes%4) 
                                   ? 0 
                                   : 4 - numberOfBytes%4);
   unsigned int numberOfWords =  (numberOfBytes+paddingAtEnd)/ 4;
   m_startWord += numberOfWords;

   m_startBit = 0;

   return *this;
}

SMSourceStream& 
PDSBuiltinContainerSourceStream::operator>>( const SMMakeContentsBase& iContents )
{
   assert(false);
   return *this;
}

void 
PDSBuiltinContainerSourceStream::beginObject( const TypeTag& iType )
{
}

void 
PDSBuiltinContainerSourceStream::endObject()
{
}

//
// const member functions
//

//
// static member functions
//
