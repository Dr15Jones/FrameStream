// -*- C++ -*-
//
// Package:     <package>
// Module:      PDSFileHeaderInfo
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon Dec 15 09:12:48 EST 2003
// $Id: PDSFileHeaderInfo.cc,v 1.1 2003/12/15 17:04:15 cdj Exp $
//
// Revision history
//
// $Log: PDSFileHeaderInfo.cc,v $
// Revision 1.1  2003/12/15 17:04:15  cdj
// first submission
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

#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
#include <strstream.h>
#define DEFINE_OSTR(_arg_) ostrstream _arg_; 
#define GET_STR(_var_) _var_.str()
#else
#include <sstream>
#define DEFINE_OSTR(_arg_) ostringstream _arg_; 
#define GET_STR(_var_) _var_.str().c_str()
#endif

// user include files
//#include "Experiment/report.h"
#include "PackedDataStreamsDelivery/PDSFileHeaderInfo.h"
#include "PackedDataStreamsDelivery/PDSTypeUnpackingInfo.h"
#include "PackedDataStreamsDelivery/PDSTypeToUnpackingInfoMap.h"

#include "PackedDataStreamsDelivery/PDSDUnexpectedlyReadEOFException.h"
#include "PackedDataStreamsDelivery/PDSDReadFailedException.h"

#include "PackedDataStreamsDelivery/PDSIstreamWordReader.h"
#include "PackedDataStreamsDelivery/PDSIstreamSwapBytesWordReader.h"

#include "PackedDataStreamsFormat/pds_file_header.h"

#include "BinaryDelivery/ByteSwapping.h"

//
// constants, enums and typedefs
//



static const char* const kFacilityString = "PackedDataStreamsDelivery.PDSFileHeaderInfo" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: PDSFileHeaderInfo.cc,v 1.1 2003/12/15 17:04:15 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
PDSFileHeaderInfo::PDSFileHeaderInfo(istream& iIStream ) :
      m_wordReader(0),
      m_typeToUnpackingInfoMap( new TypeToUnpackingInfoMap )
{
   readHeader( iIStream );
}

// PDSFileHeaderInfo::PDSFileHeaderInfo( const PDSFileHeaderInfo& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

PDSFileHeaderInfo::~PDSFileHeaderInfo()
{
   delete m_wordReader;
   delete m_typeToUnpackingInfoMap;
}

//
// assignment operators
//
// const PDSFileHeaderInfo& PDSFileHeaderInfo::operator=( const PDSFileHeaderInfo& rhs )
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
static
inline
void check_for_exceptions( std::istream& iIStream, 
			   const char* iHappenedWhile ) 
{
   if( iIStream.eof() ) {
      throw PDSDUnexpectedlyReadEOFException(iHappenedWhile);
   }
   if( iIStream.fail() ) {
      throw PDSDReadFailedException(iHappenedWhile);
   }
}

PDSFileHeaderInfo::TypeToUnpackingInfoMap* 
PDSFileHeaderInfo::dropOwnershipOfTypeToUnpackingInfoMap() {
   TypeToUnpackingInfoMap* temp = m_typeToUnpackingInfoMap;
   m_typeToUnpackingInfoMap = new TypeToUnpackingInfoMap;
   return temp;
}

void
PDSFileHeaderInfo::readNameList( const UInt32* & ioHeader, 
				 std::vector<string>& oNames )
{
   //First entry is the size (in UInt32s) of the name list
   UInt32 numberOfWords = *ioHeader;
   ++ioHeader; 
   
   //create a temporary buffer that we can modify
   UInt32* buffer = new UInt32[numberOfWords];
   memcpy( buffer, ioHeader, sizeof(UInt32)*numberOfWords );

   //Now unswap the buffer
   m_wordReader->unswapStringArray( buffer,
				    buffer+numberOfWords );

   UInt32 numberOfChars = numberOfWords * sizeof(UInt32)/sizeof(char);

   if( numberOfWords != 0 ) {
      DABoolean foundNullString = false;
      const char* pBeginningOfName = reinterpret_cast<const char*>(buffer);
      const char* pEndOfNames = pBeginningOfName + numberOfChars;
      while( !foundNullString && 
	     (pBeginningOfName < pEndOfNames ) ){
	 std::string name(pBeginningOfName);
	 //The +1 is to get rid of the terminating '\0'
	 pBeginningOfName += name.size() +1;
	 if( 0 != name.size() ) {
	    oNames.push_back(name);
	 } else {
	    foundNullString = true;
	 }
      }
   }
   delete [] buffer;
   ioHeader += numberOfWords;
}


void
PDSFileHeaderInfo::readTypeNames(const UInt32*& ioHeader, 
				 std::vector<string>& oNames )
{
   readNameList( ioHeader, oNames);
   readNameList( ioHeader, oNames);
}
	      


void
PDSFileHeaderInfo::readHeader( std::istream& iIStream )
{
   //check to see if this is the proper type
   UInt32 pdsTypeVersionInfo;
   m_wordReader = new PDSIstreamWordReader( iIStream );

   if( ! m_wordReader->readWords( &pdsTypeVersionInfo,
				  1,
				  "reading TypeVersion info" ) ) {
      throw PDSDUnexpectedlyReadEOFException("reading TypeVersion info");
   }

   UInt32 pdsFileTypeID = pdsTypeVersionInfo 
      >> PDSHeaderConstants::kBitsForVersion;
   if( pdsFileTypeID != PDSHeaderConstants::kFileTypeID ) {

      //see if different endian
      pdsTypeVersionInfo = swapBytesInUInt32( pdsTypeVersionInfo );

      pdsFileTypeID = pdsTypeVersionInfo 
	 >> PDSHeaderConstants::kBitsForVersion;
      if( pdsFileTypeID != PDSHeaderConstants::kFileTypeID ) {
	 throw PDSDExceptionBase("First word in file is not PDS ID code");
      } else {
	 //will need to swap bytes
	 delete m_wordReader;
	 m_wordReader = new PDSIstreamSwapBytesWordReader(iIStream );
      }
   }

   const UInt32 kFileTypeIDWord = PDSHeaderConstants::kFileTypeID << PDSHeaderConstants::kBitsForVersion;
   const UInt32 pdsVersion = pdsTypeVersionInfo - kFileTypeIDWord;

   if( pdsVersion != PDSHeaderConstants::kInitialVersion ) {
      DEFINE_OSTR(versionNumberStream)
      versionNumberStream << pdsVersion << '\0';
      std::string iErrorMessage = std::string("Unknown version of PDS file format ")
	 + GET_STR(versionNumberStream);
      throw PDSDExceptionBase( iErrorMessage.c_str() );
   }

   UInt32 fileIdentifier;
   if( ! m_wordReader->readWords( &fileIdentifier,
				  1,
				  "reading file identifier" ) ) {
      throw PDSDUnexpectedlyReadEOFException("reading file identifier");
   }

   //Read the entire buffer
   UInt32 sizeOfHeaderInWords;
   if( ! m_wordReader->readWords( &sizeOfHeaderInWords,
				  1,
				  "reading header size" ) ) {
      throw PDSDUnexpectedlyReadEOFException("reading header size");
   }

   UInt32* pStartOfHeaderUInt32 = new UInt32 [sizeOfHeaderInWords];
   const UInt32* pHeaderUInt32 = pStartOfHeaderUInt32;

   if( ! m_wordReader->readWords( pStartOfHeaderUInt32,
				  sizeOfHeaderInWords,
				  "reading header data" ) ) {
      throw PDSDUnexpectedlyReadEOFException("reading header data");
   }

   //check to see if buffer is consistent
   if( sizeOfHeaderInWords != *(pHeaderUInt32 + sizeOfHeaderInWords -1 ) ) {
      throw PDSDExceptionBase("Beginning and end header size do not agree");
   }
   //cout <<"header size :" << sizeOfHeaderInWords << std::endl;

   readStreams(pHeaderUInt32);

   std::vector<string> typeNames;

   readTypeNames(pHeaderUInt32, typeNames);

   /*
   for(std::vector<string>::iterator itTypeName = typeNames.begin();
       itTypeName != typeNames.end();
       ++itTypeName ) {
      cout <<"type " <<"\""<<*itTypeName<<"\""<<std::endl;
   }
    */

   //Read unpacking info
   const TypeTag kNoType ;
   for(unsigned int typeIndex = kFirstProxyIndex;
       typeIndex < typeNames.size(); ++typeIndex) {
      TypeTag typeTag = TypeTag::findType( typeNames[typeIndex] );
      if( kNoType != typeTag ) {
    //NOTE: there is a memory leak associated with this new
	 PDSTypeUnpackingInfo* pTemp = new PDSTypeUnpackingInfo;
	 pTemp->readPackingInfo( pHeaderUInt32,
				 m_wordReader->isByteSwapping() );
	 //cout <<"  add packing for type " << typeNames[typeIndex] << " "<<pTemp << std::endl;
	 (*m_typeToUnpackingInfoMap)[typeTag] = pTemp;	 
      } else {
	 //Need to read (and then discard) the info
	 //cout <<"  NO packing for type " << typeNames[typeIndex] << std::endl;
	 PDSTypeUnpackingInfo temp;
	 temp.readPackingInfo( pHeaderUInt32, false );
      }
   }

   //Read proxy info for each stream
   for( std::vector<StreamType>::iterator itStream =m_indexToStreamType.begin();
	itStream != m_indexToStreamType.end();
	++itStream ) {

      const unsigned int numberOfProxies = (*pHeaderUInt32);
      ++pHeaderUInt32;

      //cout <<"stream: " << (*itStream).value() << "# proxies:"<<numberOfProxies<<std::endl;
      std::vector<DurableDataKey>& dataKeys = 
	 m_streamProxyFactoryInfoMap[*itStream];

      if( dataKeys.size() != 0 ) {
      	   dataKeys.erase( dataKeys.begin(), dataKeys.end() );
      }
      for( unsigned int proxyIndex = 0; 
	   proxyIndex != numberOfProxies;
	   ++proxyIndex ) {
	 unsigned int typeIdentifier = (*pHeaderUInt32);
	 ++pHeaderUInt32;

	 const char* pHeaderChar = 
	    reinterpret_cast<const char*>(pHeaderUInt32);
	 m_wordReader->unswapString( const_cast<UInt32*>(pHeaderUInt32), 2 );

	 std::string usageTag( pHeaderChar);
	 std::string productionTag( pHeaderChar + usageTag.size() + 1);

	 dataKeys.push_back(
	    DataKey( TypeTag::findType( typeNames[typeIdentifier] ),
		     usageTag.c_str(),
		     productionTag.c_str() ) );
	 
	 unsigned int numberOfCharsRead = usageTag.size() + 
	    productionTag.size() + 2;

	 pHeaderUInt32 += (numberOfCharsRead/sizeof(UInt32)) + 
	    ( (numberOfCharsRead % sizeof(UInt32)) ==0 ? 0 : 1 );

	 /*
	 cout <<" proxy: \""<< dataKeys.back().type().name() <<"\" \""
	      <<dataKeys.back().usage().value()<<"\" \""
	      <<dataKeys.back().production().value()<<"\""<<std::endl;
	 */     
      }
   }


   delete [] pStartOfHeaderUInt32;

   //check to see if we read all the word (and no more) from the buffer
   if( pHeaderUInt32 != pStartOfHeaderUInt32 + sizeOfHeaderInWords -1 ) {
      throw PDSDExceptionBase("Read wrong number of words from header");
   }

}


void
PDSFileHeaderInfo::readStreams( const UInt32* &iHeader )
{
   std::vector<string> streamNames;
   readNameList( iHeader, streamNames );

   //Create the streams
   m_indexToStreamType.erase( m_indexToStreamType.begin(), 
                              m_indexToStreamType.end() );
   m_indexToStreamType.reserve(streamNames.size());

   for( std::vector<string>::iterator itStreamName = streamNames.begin();
	itStreamName != streamNames.end();
	++itStreamName ) {
      //cout <<"stream " <<"\""<<*itStreamName<<"\""<< std::endl;

      StreamType stream( *itStreamName );

      m_indexToStreamType.push_back(stream);

//Need to allow this to be filled externally
/*      if( m_streamToBufferMap.end() == m_streamToBufferMap.find(stream ) ) {
         m_streamToBufferMap[stream] = new PDSRecordReadBuffer;   
         registerStream( stream );
      }
   */
   }
}

void
PDSFileHeaderInfo::changeFile(istream& iIStream ) {
   delete m_wordReader;
   m_wordReader = 0;
   readHeader(iIStream);
}

//
// const member functions
//

//
// static member functions
//
