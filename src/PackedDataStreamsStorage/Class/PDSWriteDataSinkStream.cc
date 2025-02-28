// -*- C++ -*-
//
// Package:     <PackedDataStreamsStorage>
// Module:      PDSWriteDataSinkStream
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon Sep 25 17:41:26 EDT 2000
// $Id: PDSWriteDataSinkStream.cc,v 1.10 2002/08/09 18:11:16 cdj Exp $
//
// Revision history
//
// $Log: PDSWriteDataSinkStream.cc,v $
// Revision 1.10  2002/08/09 18:11:16  cdj
// removed inappropriate use of reinterpret_cast
//
// Revision 1.9  2001/05/24 18:42:08  cdj
// removed unused variable
//
// Revision 1.6  2001/05/23 19:54:23  cdj
// yet another try
//
// Revision 1.5  2001/05/23 18:02:19  cdj
// second attempt at fixing string storage bug
//
// Revision 1.4  2001/05/23 17:14:58  cdj
// fixed bug in writing out strings: packing needs number of bits not number of bytes
//
// Revision 1.3  2001/04/10 19:49:30  cdj
// can now store strings
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
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "PackedDataStreamsStorage/PDSWriteDataSinkStream.h"
#include "PackedDataStreamsFormat/PDSPackerTemplate.h"
#include "PackedDataStreamsFormat/PDSContainerPackedPacker.h"
#include "StorageManagement/Compression/SMContainerSizePacker.h"
#include "StorageManagement/Compression/SMIntNoPackPacker.h"
#include "StorageManagement/SMContentsBase.h"

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

static const char* const kFacilityString = "PackedDataStreamsStorage.PDSWriteDataSinkStream" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: PDSWriteDataSinkStream.cc,v 1.10 2002/08/09 18:11:16 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
PDSWriteDataSinkStream::PDSWriteDataSinkStream() :
   m_container(0),
   m_typeToPackersMap(0)
{
}

// PDSWriteDataSinkStream::PDSWriteDataSinkStream( const PDSWriteDataSinkStream& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

PDSWriteDataSinkStream::~PDSWriteDataSinkStream()
{
}

//
// assignment operators
//
// const PDSWriteDataSinkStream& PDSWriteDataSinkStream::operator=( const PDSWriteDataSinkStream& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }

template<class T>
static
inline
void
compress_data( T iData, PDSPackerBase* iPacker,
	       UInt32& ioStartWord, UInt32& oOverflowWord, 
	       unsigned char& ioStartBit )
{
   //NOTE: CC 4.2 can not handle static_cast here
   ((PDSPackerTemplate<T>*)(iPacker))->packer().pack(
      iData,
      ioStartWord,
      oOverflowWord,
      ioStartBit);
}

#define COMPRESS_DATA \
   UInt32 overflowWord = 0; \
   compress_data( iData, m_presentPacker.packer(),\
		  m_packWord, overflowWord,\
		  m_startBit);\
   addToContainerIfPackWordFull( overflowWord);
//
// member functions
//
void 
PDSWriteDataSinkStream::put( const char * iFieldName, char iData )
{
   COMPRESS_DATA
}
void 
PDSWriteDataSinkStream::put( const char * iFieldName, short iData )
{
   COMPRESS_DATA
}
void 
PDSWriteDataSinkStream::put( const char * iFieldName, int iData )
{
   COMPRESS_DATA
}
void 
PDSWriteDataSinkStream::put( const char * iFieldName, long iData )
{
   COMPRESS_DATA
}

void 
PDSWriteDataSinkStream::put( const char * iFieldName, unsigned char iData )
{
   COMPRESS_DATA
}
void 
PDSWriteDataSinkStream::put( const char * iFieldName, unsigned short iData )
{
   COMPRESS_DATA
}
void 
PDSWriteDataSinkStream::put( const char * iFieldName, unsigned int iData )
{
   COMPRESS_DATA
}
void 
PDSWriteDataSinkStream::put( const char * iFieldName, unsigned long iData )
{
   COMPRESS_DATA
}
void 
PDSWriteDataSinkStream::put( const char * iFieldName, float iData )
{
   COMPRESS_DATA
}
void 
PDSWriteDataSinkStream::put( const char * iFieldName, double iData )
{
   COMPRESS_DATA
}
void 
PDSWriteDataSinkStream::put( const char * iFieldName, const string& iData )
{
   m_presentPacker.packer();

   //pad string to 32bit boundary, this allows us to quickly read the
   // string back
   UInt32 pad =0;
   if( m_startBit != 0 ) {
      SMFixedPacker<UInt32> padPacker( 32 - (m_startBit%32), 1, 0);
      UInt32 overflow = 0;
      padPacker.pack(pad, m_packWord, overflow, m_startBit );
      addToContainerIfPackWordFull(overflow);
   }


   const unsigned int numberOfBytesToStore = iData.size() + 1;
   const unsigned int numberFullWordsToStore =  numberOfBytesToStore/(sizeof(UInt32)/sizeof(char));
   const unsigned int numberOfBytesAtEnd = numberOfBytesToStore - numberFullWordsToStore*(sizeof(UInt32)/sizeof(char));

   SMIntNoPackPacker<UInt32> wordPacker;

   const char* itString = iData.c_str();
   const char* itEnd = itString + numberFullWordsToStore*sizeof(UInt32);
   for(;
       itString < itEnd;
       ) {
      UInt32 overflow=0;
      wordPacker.pack( *reinterpret_cast<const UInt32*>(itString), 
		       m_packWord, 
		       overflow, 
		       m_startBit);
      addToContainerIfPackWordFull(overflow);      
      itString +=sizeof(UInt32)/sizeof(char); 
   }

   //deal with the end of the string which doesn't fit into an entire word
   if( 0 != numberOfBytesAtEnd ) {
   	//need to be sure to use unsigned char packer to avoid using 128 as offset 
      SMIntNoPackPacker<unsigned char> lastCharPacker;

      const char* itEnd = itString + numberOfBytesAtEnd;
      
      UInt32 packingWord = 0;
      UInt32 overflow=0;
      for( ; itString != itEnd; ++itString ) {

         lastCharPacker.pack( *reinterpret_cast<const unsigned char*>(itString), 
			                     packingWord, 
			                     overflow, 
			                     m_startBit);
      }
      //see if we need to swap bytes
      if( 0 != AC_BIGENDIAN) { 
           packingWord = swapBytesInUInt32(packingWord);
      }     
      m_packWord = packingWord;
      //we actually will store the entire last word
      m_startBit = 32;
   	addToContainerIfPackWordFull(overflow);      
   }
}

void 
PDSWriteDataSinkStream::put( const char * iFieldName, 
			      const SMContentsBase& iData )
{
   //Store the size of the container
   static SMContainerSizePacker sizePacker;
   
   UInt32 overflowWord = 0;
   sizePacker.pack( iData.size(), m_packWord,overflowWord, m_startBit);
   
   addToContainerIfPackWordFull(overflowWord);

   //Now store the contents
   PDSPackerBase* packer = m_presentPacker.packer();
   if( iData.strategy() == SMContentsBase::kBuiltin ) {
      static STL_VECTOR(PDSPackerBase*) packers( 1, static_cast<PDSPackerBase*>(0) );
      packers[0] = static_cast<PDSContainerPackedPacker*>( packer )->packer();
      
      //Need to switch to a packer that does not increment
      PackerHolder previousPackerHolder = m_presentPacker;
      
      m_presentPacker = PackerHolder( &packers, false);
      
      iData.store( *this );

      m_presentPacker = previousPackerHolder;
   } else {
      iData.store( *this );
   }
}

void 
PDSWriteDataSinkStream::beginObject( const TypeTag& iTypeTag )
{
   m_packerStack.push_back(m_presentPacker);
   m_presentPacker = PackerHolder( &((*(m_typeToPackersMap->find(iTypeTag))).second) );

   if( 1 == m_packerStack.size() ) {
      //need to write object header info

      m_container->push_back(m_typeIndex);
      //placeholder for size
      m_container->push_back(0);
      m_startSizeOfContainer = m_container->size();

      m_packWord = 0;
      m_startBit = 0;
   }
}

void 
PDSWriteDataSinkStream::endObject()
{
   m_presentPacker = m_packerStack.back();
   m_packerStack.pop_back();   


   if( m_packerStack.empty() ) {
      //we are at the top level object
      if( m_startBit != 0 ) {
	 m_container->push_back(m_packWord);
      }

      //write length of our block
      (*m_container)[ m_startSizeOfContainer - 1 ] 
	 = m_container->size() - m_startSizeOfContainer;
   }
}

//
// const member functions
//

//
// static member functions
//
