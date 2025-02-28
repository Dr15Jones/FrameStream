// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSSourceStream
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Wed Sep 27 14:40:25 EDT 2000
// $Id: PDSSourceStream.cc,v 1.7 2002/08/09 18:03:56 cdj Exp $
//
// Revision history
//
// $Log: PDSSourceStream.cc,v $
// Revision 1.7  2002/08/09 18:03:56  cdj
// removed inappropriate use of reinterpret_cast
//
// Revision 1.6  2002/04/06 19:03:15  cdj
// added a specialized SourceStream to handle containers of builtin types
//
// Revision 1.4  2001/05/24 15:43:52  cdj
// now store strings in an integral number of words
//
// Revision 1.3  2001/04/10 19:48:10  cdj
// can now store strings
//
// Revision 1.2  2000/10/02 20:42:17  cdj
// now compiles and links using cxx
//
// Revision 1.1.1.1  2#include "BinaryDelivery/ByteSwapping.h"
// imported#include "BinaryDelivery/ByteSwapping.h"
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "PackedDataStreamsDelivery/PDSSourceStream.h"
#include "PackedDataStreamsDelivery/PDSTypeUnpackingInfo.h"
#include "StorageManagement/SMMakeContentsBase.h"

#include "PackedDataStreamsFormat/PDSPackerTemplate.h"
#include "PackedDataStreamsFormat/PDSContainerPackedPacker.h"
#include "PackedDataStreamsFormat/PDSStringPacker.h"
#include "StorageManagement/Compression/SMContainerSizePacker.h"

#include "PackedDataStreamsDelivery/PDSBuiltinContainerSourceStream.h"

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

static const char* const kFacilityString = "PackedDataStreamsDelivery.PDSSourceStream" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: PDSSourceStream.cc,v 1.7 2002/08/09 18:03:56 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
//PDSSourceStream::PDSSourceStream()
//{
//}

// PDSSourceStream::PDSSourceStream( const PDSSourceStream& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

PDSSourceStream::~PDSSourceStream()
{
}

//
// assignment operators
//
// const PDSSourceStream& PDSSourceStream::operator=( const PDSSourceStream& rhs )
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
   //NOTE CC 4.2 can not use static_cast here
   oData =((SMPackerTemplate<T>*)(iPacker))->unpack(
      *iBuffer, *(iBuffer+1), ioStartBit );
}

#define UNPACK_DATA \
SMPackerBase* packer = m_unpackerHolder.unpacker().m_packer; \
unpack_data( packer, m_startWord, m_startBit, iData ); \
advanceStartWordIfNeeded();

SMSourceStream& 
PDSSourceStream::operator>>( char& iData )
{
   UNPACK_DATA
   return *this;
}

SMSourceStream& 
PDSSourceStream::operator>>( short& iData )
{
   UNPACK_DATA
   return *this;
}

SMSourceStream& 
PDSSourceStream::operator>>( int& iData )
{
   UNPACK_DATA
   return *this;
}

SMSourceStream& 
PDSSourceStream::operator>>( long& iData )
{
   UNPACK_DATA
   return *this;
}

SMSourceStream& 
PDSSourceStream::operator>>( unsigned char& iData )
{
   UNPACK_DATA
   return *this;
}

SMSourceStream& 
PDSSourceStream::operator>>( unsigned short& iData )
{
   UNPACK_DATA
   return *this;
}

SMSourceStream& 
PDSSourceStream::operator>>( unsigned int& iData )
{
   UNPACK_DATA
   return *this;
}

SMSourceStream& 
PDSSourceStream::operator>>( unsigned long& iData )
{
   UNPACK_DATA
   return *this;
}

SMSourceStream& 
PDSSourceStream::operator>>( float& iData )
{
   UNPACK_DATA
   return *this;
}
SMSourceStream& 
PDSSourceStream::operator>>( double& iData )
{
   UNPACK_DATA
   return *this;
}

SMSourceStream& 
PDSSourceStream::operator>>( string& iData )
{
   const DABoolean byteSwapped = 
      (reinterpret_cast<SMPackerBase*>(PDSStringPacker::kByteSwapped) == 
         m_unpackerHolder.unpacker().m_packer);

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
PDSSourceStream::operator>>( const SMMakeContentsBase& iContents )
{
   static SMContainerSizePacker sizePacker;

   unsigned int iNumberOfEntries = sizePacker.unpack( *m_startWord,
						      *(m_startWord+1),
						      m_startBit );
   advanceStartWordIfNeeded();

   PDSTypeUnpackingInfo::TypePacker& typePacker = m_unpackerHolder.unpacker();

   if( typePacker.m_type == PDSPacking::kContainerType ) {
      //use a specialized SourceStream to fill this container
      //  since containers of builtin types only use 1 packer
      static PDSBuiltinContainerSourceStream s_builtinSource;
      s_builtinSource.reset(m_startWord, m_startBit, typePacker.m_packer); 
      iContents.deliver( s_builtinSource, iNumberOfEntries );
      m_startWord = s_builtinSource.startWord();
      m_startBit = s_builtinSource.startBit();
   } else {
      //Since this container holds other objects, it is neccessary
      //  to hold onto our present packing info so that when we return
      //  we can pickup where we left off
      UnpackerHolder holdUnpackerHolder = m_unpackerHolder;
      iContents.deliver( *this, iNumberOfEntries );
      m_unpackerHolder = holdUnpackerHolder;
   }

   return *this;
}

void 
PDSSourceStream::beginObject( const TypeTag& iType )
{
   m_unpackerHolder = UnpackerHolder( (*(m_typePackingMap->find( iType ))).second );
}

void 
PDSSourceStream::endObject()
{
}
//
// const member functions
//
unsigned int 
PDSSourceStream::versionUsed( const TypeTag& iType ) const {
   return (*(m_typePackingMap->find(iType))).second->version();
}

//
// static member functions
//
