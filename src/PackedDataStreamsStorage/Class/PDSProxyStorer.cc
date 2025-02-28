// -*- C++ -*-
//
// Package:     <PackedDataStreamsStorage>
// Module:      PDSProxyStorer
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Wed Sep 13 09:42:47 EDT 2000
// $Id: PDSProxyStorer.cc,v 1.8 2003/06/11 18:37:43 cdj Exp $
//
// Revision history
//
// $Log: PDSProxyStorer.cc,v $
// Revision 1.8  2003/06/11 18:37:43  cdj
// now checks to see if write was successful
//
// Revision 1.7  2003/01/27 20:35:53  cleo3
// deal with vector iterator not being a pointer under g++
//
// Revision 1.6  2002/11/24 15:04:54  cdj
// fixed missing symbol on OSF by removing autoinstantiations from PDSProxyStorer.cc to own files
//
// Revision 1.5  2002/11/21 20:12:15  cleo3
// only instantiate set difference template if not using auto-instantiation
//
// Revision 1.4  2001/09/07 19:34:29  cleo3
// no use NO_STL_TEMPLATED_MEMBER_FUNCTIONS_BUG
//
// Revision 1.3  2000/10/08 17:00:20  cdj
// now use pds_file_header.h constants
//
// Revision 1.2  2000/10/02 20:46:48  cdj
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

#include <algorithm>
#include <string>
#include <string.h>

// user include files
//#include "Experiment/report.h"
#include "PackedDataStreamsStorage/PDSProxyStorer.h"

#include "PackedDataStreamsFormat/PDSPackerBase.h"
#include "PackedDataStreamsStorage/PDSDataToStore.h"
#include "PackedDataStreamsStorage/PDSSchemaProbeSinkStream.h"
#include "PackedDataStreamsStorage/PDSWriteDataSinkStream.h"

#include "DataHandler/StreamSet.h"
#include "DataHandler/Record.h"

#include "StorageManagement/SMStorageHelperManager.h"
#include "StorageManagement/SMProxyWriterBase.h"
#include "StorageManagement/Compression/SMContainerSizePacker.h"

#include "PackedDataStreamsFormat/pds_record_header.h"
#include "PackedDataStreamsFormat/pds_file_header.h"

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

static const char* const kFacilityString = "PackedDataStreamsStorage.PDSProxyStorer" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: PDSProxyStorer.cc,v 1.8 2003/06/11 18:37:43 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
PDSProxyStorer::PDSProxyStorer(ostream& iOStream,
			       const Stream::Set& iStreams,
			       const PDSDataToStore& iDataToStore ) :
   m_ostream( iOStream),
   m_dataToStore(iDataToStore),
   m_dataBuffer(PDSRecordHeader::kNumberOfWords,
		UInt32(0) )
{
   Stream::Set::const_iterator itEnd = iStreams.end();
   for( Stream::Set::const_iterator itStream = iStreams.begin();
	itStream != itEnd; ++itStream ) {
      registerStream( *itStream );
   }

   writeHeader( iDataToStore );
}

// PDSProxyStorer::PDSProxyStorer( const PDSProxyStorer& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

PDSProxyStorer::~PDSProxyStorer()
{
   {
      PackersForTypeMap::iterator itEnd = m_packersForTypeMap.end();
      for( PackersForTypeMap::iterator itPackers = m_packersForTypeMap.begin();
	   itPackers != itEnd;
	   ++itPackers ) {
	 
	 STL_VECTOR(PDSPackerBase*)& packers = (*itPackers).second;
	 for( STL_VECTOR(PDSPackerBase*)::iterator itPacker = packers.begin();
	      itPacker != packers.end();
	      ++itPacker ) {
	    delete (*itPacker);
	 }
      }  
   }
   { 
      WriterMap::iterator itEnd = m_writers.end();
      for( WriterMap::iterator itWriter = m_writers.begin();
	   itWriter != itEnd;
	   ++itWriter ) {
	 delete (*itWriter).second ;
      }
   }

}

//
// assignment operators
//
// const PDSProxyStorer& PDSProxyStorer::operator=( const PDSProxyStorer& rhs )
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
PDSProxyStorer::writeHeader( const PDSDataToStore& iDataToStore )
{
   STL_VECTOR(UInt32) headerData;
   headerData.reserve(1000);

   createStreamList( headerData );

   STL_SET(TypeTag) factoryTypeTags;
   createTypesInfo( headerData, iDataToStore, factoryTypeTags );
   createProxyWriters( factoryTypeTags );

   createProxiesInRecordsInfo( headerData, iDataToStore, factoryTypeTags );

   //output the header
   //Upper 3 bytes are the PDSTypeIdentifier
   const UInt32 kPDSTypeIdentifier = PDSHeaderConstants::kFileTypeID;
   const UInt32 kPDSVersion = PDSHeaderConstants::kPresentVersion;
   const UInt32 kPDSTypeVersionIdentifier = 
      kPDSTypeIdentifier<<PDSHeaderConstants::kBitsForVersion + kPDSVersion;
   m_ostream.write( reinterpret_cast<const char*>(&kPDSTypeVersionIdentifier),
		    sizeof(UInt32) );

   //next word is used to 'uniquely' identify this file
   const UInt32 kFileIdentifier = 0;
   m_ostream.write( reinterpret_cast<const char*>(&kFileIdentifier),
		    sizeof(UInt32) );

   UInt32 headerDataSizePlusEndLength = headerData.size() +1;
   m_ostream.write( reinterpret_cast<char*>(&headerDataSizePlusEndLength) , 
		    sizeof(UInt32) ) ;
   m_ostream.write( reinterpret_cast<char*>( &(*(headerData.begin())) ), 
		    sizeof(UInt32)*headerData.size() );
   m_ostream.write( reinterpret_cast<char*>(&headerDataSizePlusEndLength), 
		    sizeof(UInt32) );

}


template<class Iterator >
static
inline
void
fillNameList(STL_VECTOR(UInt32)& iContainer,
	     Iterator itBegin,
	     Iterator itEnd )
{
   unsigned int length = 0;

   Iterator itNameHolder;
   for( itNameHolder = itBegin;
	itNameHolder != itEnd;
	++itNameHolder ) {
      length += (*itNameHolder).size() + 1;
   }

   //Pad the length so it is a multiple of the size of UInt32
   length = (length + sizeof(UInt32)-1 ) /sizeof(UInt32);

   //create a character array that has UInt32 alignment restrictions
   UInt32* pNamesUInt32 = new UInt32[length];
   char* pNames = reinterpret_cast<char*>( pNamesUInt32 );

   memset(pNames, 0, length*sizeof(UInt32));

   char* pStartOfNextName = pNames;
   for( itNameHolder = itBegin;
	itNameHolder != itEnd;
	++itNameHolder ) {
      strcpy( pStartOfNextName, (*itNameHolder).c_str() );
      pStartOfNextName += (*itNameHolder).size()+1;
   }

   //Format is
   //  all the names seperated by '\0'

   iContainer.insert(iContainer.end(), 
		     pNamesUInt32,
		     pNamesUInt32 + length );

   delete [] pNamesUInt32;
}


template<class Iterator, class NameExtractor>
static
inline
void fillNameList( STL_VECTOR(UInt32)& iContainer,
		   Iterator itBegin,
		   Iterator itEnd,
		   const NameExtractor& iNameExtractor )
{
   unsigned int length = 0;

   Iterator itNameHolder;
   for( itNameHolder = itBegin;
	itNameHolder != itEnd;
	++itNameHolder ) {
      length += iNameExtractor.name( (itNameHolder) ).size() + 1;
   }

   //Pad the length so it is a multiple of the size of UInt32
   length = (length + sizeof(UInt32)-1 ) /sizeof(UInt32);

   //create a character array that has UInt32 alignment restrictions
   UInt32* pNamesUInt32 = new UInt32[length] ;

   char* pNames = reinterpret_cast<char*>( pNamesUInt32 );

   memset(pNames, 0, length*sizeof(UInt32));

   char* pStartOfNextName = pNames;
   for( itNameHolder = itBegin;
	itNameHolder != itEnd;
	++itNameHolder ) {
      string temp( iNameExtractor.name(itNameHolder) );
      strcpy( pStartOfNextName, temp.c_str() );
      pStartOfNextName += temp.size()+1;
   }

   //Format is
   //  # of 32 bit words
   //  all the names seperated by '\0'
   iContainer.push_back( length );

   iContainer.insert(iContainer.end(), 
		   pNamesUInt32,
		   pNamesUInt32 + length );

   delete [] pNamesUInt32;

}


class StreamNameExtractor
{
   public:
      const string& name(Stream::Set::const_iterator iIterator ) const {
	 return (*iIterator).value(); }
};

void
PDSProxyStorer::createStreamList( STL_VECTOR(UInt32)& iContainer )
{
   Stream::Set streams = stores();

   Stream::Set::const_iterator itStream ;
   unsigned int streamIndex = 0;
   for( itStream = streams.begin();
	itStream != streams.end();
	++itStream ) {
      m_streamToIndexMap[(*itStream).index() ] = streamIndex++;
   }


   fillNameList( iContainer,
		 streams.begin(),
		 streams.end(),
		 StreamNameExtractor() );
}

class TypeTagNameExtractor {
   public:
      string name( const STL_SET(TypeTag)::const_iterator& iIterator ) const { 
	 return (*iIterator).name();
      }
};

void
PDSProxyStorer::createTypesInfo( STL_VECTOR(UInt32)& iContainer,
				 const PDSDataToStore& iDataToStore,
				 STL_SET(TypeTag)& oFactoryTypes )
{
   //create a set of all the types that have factories
   PDSDataToStore::const_iterator itEndStreamData = iDataToStore.end();
   for( PDSDataToStore::const_iterator itStreamData = iDataToStore.begin();
	itStreamData != itEndStreamData;
	++itStreamData ) {
      
      const STL_SET(DurableDataKey)& keys = (*itStreamData).second();

      STL_SET(DurableDataKey)::const_iterator itEndKey = keys.end();
      for( STL_SET(DurableDataKey)::const_iterator itKey = keys.begin();
	   itKey != itEndKey;
	   ++itKey ) {
	 oFactoryTypes.insert( (*itKey).type() );
      }
   }
   
   //Now that we have a unique list of all the proxy types, we need
   // to obtain the schema for those types so we can get the 
   //  1) packing info
   //  2) the other types we need to store
   
   STL_SET(TypeTag) subtypeTags;
   probeSchema( oFactoryTypes, subtypeTags );

   fillNameList( iContainer,
		 oFactoryTypes.begin(),
		 oFactoryTypes.end(),
		 TypeTagNameExtractor() );

   fillNameList( iContainer,
		 subtypeTags.begin(),
		 subtypeTags.end(),
		 TypeTagNameExtractor() );


   //First we store the factory types, then the subtypes
   fillPackingInfo( iContainer, oFactoryTypes.begin(), oFactoryTypes.end() );
   fillPackingInfo( iContainer, subtypeTags.begin(),   subtypeTags.end() );

}

void
PDSProxyStorer::probeSchema( const STL_SET(TypeTag)& iFactoryTypes,
			     STL_SET(TypeTag)& oSubTypes )
{
   //Obtain all the packing information
   STL_SET(TypeTag) typesLeftToCheck( iFactoryTypes );
   STL_SET(TypeTag) typesChecked;
   
   SMStorageHelperManager& sm = SMStorageHelperManager::instance();


   PDSSchemaProbeSinkStream schemaProbe;
   
   while( typesLeftToCheck.size() != 0 ) {
      TypeTag presentTag = *(typesLeftToCheck.begin());
      SMStorageHelperBase* pStorageHelper = *(sm.find( presentTag ));

      schemaProbe.setPackerContainer( &(m_packersForTypeMap[presentTag]) );

      if( 0 != pStorageHelper ) {
	 pStorageHelper->useDefault( schemaProbe );
      }
      
      typesLeftToCheck.erase( presentTag );
      typesChecked.insert(presentTag );

      //Add to the types left to check only those subtypes found 
      // entries that are not already in the types checked list
      insert_iterator<STL_SET(TypeTag)> 
	 typesLeftToCheckOutputIterator( typesLeftToCheck,
					 typesLeftToCheck.begin() );

      set_difference( schemaProbe.subtypesFound().begin(),
		      schemaProbe.subtypesFound().end(),
		      typesChecked.begin(),
		      typesChecked.end(),
		      typesLeftToCheckOutputIterator );

      insert_iterator<STL_SET(TypeTag)> 
	 subTypesOutputIterator( oSubTypes,
				 oSubTypes.begin());
      set_difference( schemaProbe.subtypesFound().begin(),
		      schemaProbe.subtypesFound().end(),
		      iFactoryTypes.begin(),
		      iFactoryTypes.end(),
		      subTypesOutputIterator );
      
      schemaProbe.clearSubtypes();
   }
   
}

void
PDSProxyStorer::fillPackingInfo( STL_VECTOR(UInt32)& ioContainer,
				 STL_SET(TypeTag)::const_iterator iBegin,
				 STL_SET(TypeTag)::const_iterator iEnd )
{
   SMContainerSizePacker sizePacker;

   
   for( STL_SET(TypeTag)::const_iterator itType = iBegin;
	itType != iEnd;
	++itType ) {
      //cout <<" fillPackingInfo for type " << (*itType).name() << endl;
      PackersForTypeMap::iterator itPackers = m_packersForTypeMap.find(*itType);
      assert( itPackers != m_packersForTypeMap.end() );
      const STL_VECTOR(PDSPackerBase*)& packers = m_packersForTypeMap[*itType];

      UInt32 packedWord = 0;
      unsigned char startBit = 0;
      UInt32 overflow = 0;

      //store version
      //ioContainer.push_back( 
      // (*SMStorageHelperManager::instance().find( *itType ))->versionToStore() );
      assert( SMStorageHelperManager::instance().find( *itType ) != 
	      SMStorageHelperManager::instance().end() );

      sizePacker.pack( 
	 (*SMStorageHelperManager::instance().find( *itType ))
	                  ->versionToStore(),
	 packedWord,
	 overflow,
	 startBit );

      if( startBit >= 32 ) {
	 ioContainer.push_back(packedWord);
	 startBit -= 32;
	 packedWord = overflow;
	 overflow = 0;
      }
      //cout <<"     packed versionToStore" <<endl;
      

      //store number of fields
      //ioContainer.push_back( packers.size() );

      sizePacker.pack( packers.size(), packedWord, overflow, startBit );

      if( startBit >= 32 ) {
	 ioContainer.push_back(packedWord);
	 startBit -= 32;
	 packedWord = overflow;
      }
      //cout <<"     packed number of fields" <<endl;

      for( STL_VECTOR(PDSPackerBase*)::const_iterator itPacker = packers.begin();
	   itPacker != packers.end();
	   ++itPacker ) {
	 //store field packing info
	 (*itPacker)->storePackingInfo( packedWord, startBit, ioContainer );
      }

      if(startBit != 0 ) {
	 ioContainer.push_back(packedWord);
      }

   }

}

void
PDSProxyStorer::createProxiesInRecordsInfo( 
   STL_VECTOR(UInt32)& ioContainer, 
   const PDSDataToStore& iDataToStore,
   const STL_SET(TypeTag)& iFactoryTypes )
{
   //Need to create a lookup table between TypeTag and index number
   STL_MAP(TypeTag, unsigned int ) typeToIndex;

   unsigned int index = 0;
   for( STL_SET(TypeTag)::const_iterator itType = iFactoryTypes.begin();
	itType != iFactoryTypes.end();
	++itType ) {

      typeToIndex[ *itType ] = index++;

   }


   for( PDSDataToStore::const_iterator itKeySet = iDataToStore.begin();
	itKeySet != iDataToStore.end();
	++itKeySet ) {

      const STL_SET(DurableDataKey)& keySet = (*itKeySet).second();
   
      //Number of Proxies in this record
      ioContainer.push_back( keySet.size() );
   
      for( STL_SET(DurableDataKey)::const_iterator itKey = keySet.begin();
	   itKey != keySet.end();
	   ++itKey ) {

	 ioContainer.push_back( typeToIndex[ (*itKey).type() ] );

	 //Essentially put usage and production tags into a container
	 // so we can use iterators to do the filling
	 string usageProductionTags[2];
	 usageProductionTags[0] = (*itKey).usage().value();
	 usageProductionTags[1] = (*itKey).production().value();

	 fillNameList( ioContainer, usageProductionTags,
		       usageProductionTags+2);
      }

   }
}


void
PDSProxyStorer::createProxyWriters( const STL_SET(TypeTag)& iFactoryTypes )
{
   SMStorageHelperManager& shm = SMStorageHelperManager::instance();
   
   STL_SET(TypeTag)::const_iterator itEnd = iFactoryTypes.end();
   for( STL_SET(TypeTag)::const_iterator itType = iFactoryTypes.begin();
	itType != itEnd;
	++itType ) {

      SMStorageHelperManager::factory_iterator itFactory = shm.factory_find( *itType );
      //add this to our map
      m_writers.insert( WriterMap::value_type( 
	 *itType,
	 (*itFactory)->makeProxyWriter() ) );
      
   }
}
//
// const member functions
//
ProxyStorer::StoreStatus
PDSProxyStorer::implementStore( const Record& iRecord ) const
{
   STL_VECTOR(UInt32)& dataBuffer = const_cast<PDSProxyStorer*>(this)->m_dataBuffer;

   dataBuffer.clear();
   //reserve space for the header
   dataBuffer.insert(dataBuffer.begin(),
		     PDSRecordHeader::kNumberOfWords,
		     UInt32(0) );

   //Fill up the data buffer
   PDSWriteDataSinkStream sinkStream;
   sinkStream.setContainer( dataBuffer );
   sinkStream.setPackers( m_packersForTypeMap );

   const STL_SET(DurableDataKey)& keys = 
      const_cast<PDSProxyStorer*>(this)->m_dataToStore[iRecord.stream()]();

   STL_SET(DurableDataKey)::const_iterator itEnd = keys.end();
   unsigned int index = 0;
   for( STL_SET(DurableDataKey)::const_iterator itKey = keys.begin();
	itKey != itEnd;
	++itKey, ++index ) {

      sinkStream.setTypeIndex( index );
      WriterMap::const_iterator itWriter = m_writers.find( (*itKey).type() );
      if( itWriter != m_writers.end() ) {
	 (*itWriter).second->store( *itKey, iRecord, sinkStream );
      }
   }

   
   //fill in the header and footer information
   const UInt32 kBodySize = dataBuffer.size() + 1 - 
                            PDSRecordHeader::kNumberOfWords;
   dataBuffer.push_back(kBodySize);
   dataBuffer[PDSRecordHeader::kSizeOfBodyWord] = kBodySize ;

   dataBuffer[PDSRecordHeader::kRecordTypeWord] = 
      const_cast<PDSProxyStorer*>(this)->m_streamToIndexMap[ iRecord.stream().index() ];
   dataBuffer[PDSRecordHeader::kRunNumberWord] = 
      iRecord.syncValue().runNumber();
   dataBuffer[PDSRecordHeader::kEventNumberWord] = 
      iRecord.syncValue().eventNumber();

   UInt64 time = iRecord.syncValue().time();
   UInt64 lowerMask = ~(UInt32(0));
   dataBuffer[PDSRecordHeader::kTimeLowerWord ] = time & lowerMask;
   dataBuffer[PDSRecordHeader::kTimeUpperWord ] = time >> 32;
   
   //now write out the record
   m_ostream.write( reinterpret_cast<char*>(&(*(dataBuffer.begin()))), 
		    sizeof(UInt32)*(dataBuffer.size()) );

   //if write fails, return error
   return (m_ostream ? kStoreNoError : kStoreProblemWithSink);
}

//
// static member functions
//

