// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSProxyDeliverer
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon Sep 18 16:59:29 EDT 2000
// $Id: PDSProxyDeliverer.cc,v 1.13 2003/12/15 16:58:38 cdj Exp $
//
// Revision history
//
// $Log: PDSProxyDeliverer.cc,v $
// Revision 1.13  2003/12/15 16:58:38  cdj
// moved file header reading and data caching to new object to be shared with event store
//
// Revision 1.12  2003/12/11 21:38:22  cdj
// added changeIStream method needed for EventStore
//
// Revision 1.11  2003/01/24 19:51:41  cdj
// use UnixFileHandleStream when reading gzipped files
//
// Revision 1.10  2002/09/06 20:52:03  cdj
// fixed bug that affected chains where sources have different ordering of data types
//
// Revision 1.9  2001/12/17 21:14:02  cdj
// properly handle case where could crash if fewer items in Record than specified in header
//
// Revision 1.8  2001/05/31 19:44:32  cdj
// changes needed for chaining now work on OSF
//
// Revision 1.6  2001/04/10 19:48:09  cdj
// can now store strings
//
// Revision 1.5  2001/01/15 21:07:55  cdj
// Now properly reads Tags when doing byteSwapping
//
// Revision 1.4  2000/10/07 18:24:23  cdj
// can now read files that were written from a different endian machine
//
// Revision 1.3  2000/10/04 18:52:16  cdj
// PDSProxyDeliverer.cc
//
// Revision 1.2  2000/10/02 20:42:16  cdj
// now compiles and links using cxx
//
// Revision 1.1.1.1  2000/09/29 17:48:05  cdj
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
#include <assert.h>

// user include files
//#include "Experiment/report.h"
#include "PackedDataStreamsDelivery/PDSProxyDeliverer.h"
#include "PackedDataStreamsDelivery/PDSSourceController.h"
#include "PackedDataStreamsDelivery/PDSTypeUnpackingInfo.h"
#include "PackedDataStreamsDelivery/PDSTypeToUnpackingInfoMap.h"
#include "PackedDataStreamsDelivery/PDSRecordReadBuffer.h"
#include "PackedDataStreamsDelivery/PDSSourceStream.h"

#include "PackedDataStreamsDelivery/PDSDUnexpectedlyReadEOFException.h"
#include "PackedDataStreamsDelivery/PDSDReadFailedException.h"

#include "PackedDataStreamsDelivery/PDSIstreamWordReader.h"
#include "PackedDataStreamsDelivery/PDSIstreamSwapBytesWordReader.h"

#include "PackedDataStreamsFormat/pds_file_header.h"

#include "StorageManagement/SMStorageHelperManager.h"
#include "StorageManagement/SMProxyBase.h"

#include "BinaryDelivery/ByteSwapping.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
#include <set>
//#include <map>
#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "PackedDataStreamsDelivery.PDSProxyDeliverer" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: PDSProxyDeliverer.cc,v 1.13 2003/12/15 16:58:38 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//
/*
class PDSTypeToUnpackingInfoMap : public std::map<TypeTag, PDSTypeUnpackingInfo *>
{
   public:
   ~PDSTypeToUnpackingInfoMap() {
      iterator itEnd = end();
      for( iterator itEntry = begin(); itEntry != itEnd;
	        ++itEntry ) {
	        	//cout <<"deleting packerInfo"<<(*itEntry).second<<std::endl;
	      delete (*itEntry).second;
      }
   }
      
};
*/

//
// constructors and destructor
//
PDSProxyDeliverer::PDSProxyDeliverer(istream& iIStream ) :
   ProxyDeliverer("PDSProxyDeliverer"),
   m_headerInfo(iIStream),
   m_haveRecordsFromPreviousFiles(false)
{
   //cout <<"constructing PDSProxyDeliverer"<<std::endl;
   //cout << "  m_typeToUnpackingInfoMap="<<m_typeToUnpackingInfoMap <<std::endl;
   initializeStreams();
}

// PDSProxyDeliverer::PDSProxyDeliverer( const PDSProxyDeliverer& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

PDSProxyDeliverer::~PDSProxyDeliverer()
{
   //cout <<"deleting PDSProxyDeliverer"<<std::endl;

   {
      std::map<StreamType, PDSRecordReadBuffer*>::iterator itEnd = 
	 m_streamToBufferMap.end();
      for( std::map<StreamType, PDSRecordReadBuffer*>::iterator itEntry =
	      m_streamToBufferMap.begin();
	   itEntry != itEnd;
	   ++itEntry ) {
	 delete (*itEntry).second;
      }
   }

   {
      StreamToSourcesMap::iterator itEnd = m_streamToSourcesMap.end();
      for( StreamToSourcesMap::iterator itStreamSources = 
	      m_streamToSourcesMap.begin();
	   itStreamSources != itEnd;
	   ++itStreamSources ) {
	 SourceStreams& sourceStreams = (*itStreamSources).second;

	 for( SourceStreams::iterator itSourceStream = sourceStreams.begin();
	      itSourceStream != sourceStreams.end();
	      ++itSourceStream ) {
	    delete *itSourceStream;
	 }
      }
   }

   {
   	std::set<TypeToUnpackingInfoMap*> infoSet;
   	std::map<StreamType, TypeToUnpackingInfoMap*>::iterator itEnd = 
   	   m_presentPackingInfo.end();
   	for( std::map<StreamType, TypeToUnpackingInfoMap*>::iterator itEntry
   	         = m_presentPackingInfo.begin();
   	      itEntry != itEnd;
   	      ++itEntry ) {
   	    if( m_headerInfo.typeToUnpackingInfoMap() != (*itEntry).second ) {
   	      infoSet.insert( (*itEntry).second );  	   
   	    }
   	}
   	
   	std::set<TypeToUnpackingInfoMap*>::iterator itSetEnd = infoSet.end();
   	for( std::set<TypeToUnpackingInfoMap*>::iterator itSet = infoSet.begin();
   	     itSet != itSetEnd;
   	     ++itSet ) {
   	   //cout <<"   deleting "<< *itSet<<std::endl;
         delete *itSet;
      }
   }
   //cout <<"deleting m_typeToUnpackingInfoMap "<<m_typeToUnpackingInfoMap <<std::endl;
}

//
// assignment operators
//
// const PDSProxyDeliverer& PDSProxyDeliverer::operator=( const PDSProxyDeliverer& rhs )
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

void
PDSProxyDeliverer::initializeStreams()
{

   for( std::vector<StreamType>::const_iterator itStream = m_headerInfo.indexToStreamType().begin();
	itStream != m_headerInfo.indexToStreamType().end();
	++itStream ) {

      if( m_streamToBufferMap.end() == m_streamToBufferMap.find(*itStream ) ) {
         m_streamToBufferMap[*itStream] = new PDSRecordReadBuffer;   
         registerStream( *itStream );
      }
   }
}

void 
PDSProxyDeliverer::disable( const Stream::Type& aStream ) 
{
}
void 
PDSProxyDeliverer::enable( const Stream::Type& aStream ) 
{
}

void
PDSProxyDeliverer::readBody( const Stream::Type& iStream,
			     std::istream& iIFStream,
			     UInt32 iWordsToRead )
{
   //When chaining, we have to keep around the old PackingInfo until
   // a new record appears
   if( m_haveRecordsFromPreviousFiles ) {
   	std::map<StreamType, TypeToUnpackingInfoMap*>::iterator itFound =
   	   m_presentPackingInfo.find( iStream );

   	std::map<StreamType, TypeToUnpackingInfoMap*>::iterator itEnd =
   	   m_presentPackingInfo.end();
   	 
   	assert( itFound != itEnd );  
   	if( (*itFound).second != m_headerInfo.typeToUnpackingInfoMap() ) {
   		//see if this is the last one in our list to see if we must delete
         DABoolean isLast = true;
         DABoolean onlyTwoInfos = true;
			for( std::map<StreamType, TypeToUnpackingInfoMap*>::iterator itInfo =
   			   m_presentPackingInfo.begin();
   		      itInfo != itEnd;
   		      ++itInfo ) {
            if( itInfo != itFound && (*itInfo).second == (*itFound).second ) {
                  isLast = false;
                  break;
            }
            if( (*itInfo).second != (*itFound).second &&
                (*itInfo).second != m_headerInfo.typeToUnpackingInfoMap() ) {
                	onlyTwoInfos = false;
            }
   		}
         if( isLast ) { 
            //cout <<"deleting last instance of old TypeToUnpackingInfoMap " <<(*itFound).second<<std::endl;

         	delete (*itFound).second;
         	if( onlyTwoInfos ) {
             		m_haveRecordsFromPreviousFiles = false;
         	}	
         }
         // <<" changing to new packing info from "<<(*itFound).second<<" to "<<m_typeToUnpackingInfoMap<<std::endl;
         (*itFound).second = m_headerInfo.typeToUnpackingInfoMap();
         //Now reset all the SourceStreams' packing info
         
         SourceStreams& sourceStreams = m_streamToSourcesMap[iStream];
         for( SourceStreams::iterator itSource = sourceStreams.begin();
              itSource != sourceStreams.end();
              ++itSource ) {
                 (*itSource )->setUnpackingInfoMap( m_headerInfo.typeToUnpackingInfoMap() );
         }
   	}
   }

   PDSRecordReadBuffer* pBuffer = m_streamToBufferMap[iStream];
   assert(pBuffer != 0);

   pBuffer->read( *wordReader(), iWordsToRead );


   //cout <<" # words in Record " << iWordsToRead << std::endl;
   
   SourceStreams& sourceStreams = m_streamToSourcesMap[ iStream ];
   const PDSRecordReadBuffer* buffer = m_streamToBufferMap[iStream];
   assert( buffer != 0);
   //buffer->end() is beyond the end of the buffer, which means it is just
   // beyond the final buffer size value.  For looping over ProxyBuffers, 
   // I want the end to be ON the address of the 'final buffer size' value.
   PDSRecordReadBuffer::const_iterator itBufferEnd = buffer->end() - 1;

   PDSRecordReadBuffer::const_iterator itBuffer = buffer->begin();

   SourceStreams::iterator itSourceEnd = sourceStreams.end();
   SourceStreams::iterator itSource = sourceStreams.begin();

   if ( iWordsToRead != 1 ) {
      //This is record has data and therefore we need to parse the buffer
      while( itBuffer != itBufferEnd && itSource != itSourceEnd ) {
	 
	 //cout << "    buffer index " << (*itBuffer).index();
	 if( (*itBuffer).index() == (*itSource)->index() ) {
	    (*itSource)->setBuffer( (*itBuffer) );
	    //cout <<" found source" <<std::endl;
	    ++itBuffer;
	    ++itSource;
	    continue;
	 }
	 
	 //cout << " no source found" << std::endl;
	 if( (*itBuffer).index() > (*itSource)->index() ) {
	    (*itSource)->invalidate();
	    ++itSource;
	 } else {
	    ++itBuffer;
	 }
      }
   }

   //any 'left over' SourceStreams need to be invalidated
   for( ; itSource != itSourceEnd; ++itSource ) {
      (*itSource)->invalidate();
   }

}

void 
PDSProxyDeliverer::resetCache( const Stream::Type& aStream ) 
{
}

void 
PDSProxyDeliverer::registerProxies( const Stream::Type& aStream ,
				    KeyedProxies& aProxyList ) 
{
   const std::vector<DurableDataKey>& dataKeys = 
      m_headerInfo.streamProxyFactoryInfoMap()[aStream];

   //get the SourceStream container we need to fill
   SourceStreams& sourceStreams = m_streamToSourcesMap[ aStream ];

   SMStorageHelperManager& shm = SMStorageHelperManager::instance();

   SMStorageHelperManager::factory_iterator itFactoryEnd = shm.factory_end();

   unsigned int index = PDSFileHeaderInfo::kFirstProxyIndex;
   for( std::vector<DurableDataKey>::const_iterator itKey = dataKeys.begin();
	itKey != dataKeys.end();
	++itKey ) {

      //see if the storage manager has a StorageHelper for this type

      SMStorageHelperManager::factory_iterator itFactory = 
	 shm.factory_find( itKey->type() );

      if( itFactory != itFactoryEnd ) {
/*      	cout <<"   creating proxy for "<<itKey->type().name() <<"+"
      	   <<itKey->usage().value() << itKey->production().value() << std::endl; */
	 PDSSourceStream* pSourceStream = 
	    new PDSSourceStream(m_headerInfo.typeToUnpackingInfoMap(), index);
	 sourceStreams.push_back( pSourceStream );

	 SMProxyBase* tmp = (*itFactory)->makeProxy();
	 assert( 0 != tmp);
	 if( 0 != tmp ) {  
	    tmp->setSourceStream( pSourceStream );
	    //put in our proxy
	    aProxyList.push_back( KeyedProxy( *itKey,tmp->proxyBase() ) );
	 }
      }
      ++index;
   }
   //cout <<" adding "<<m_typeToUnpackingInfoMap<<" to m_presentPackingInfo"<<std::endl;
   m_presentPackingInfo[aStream] = m_headerInfo.typeToUnpackingInfoMap();
}

struct SourceStreamCompare {
   DABoolean operator()( const PDSSourceStream* iLHS,
            	          const PDSSourceStream* iRHS ) {
      return iLHS->index() < iRHS->index() ; 
   }
};

void
PDSProxyDeliverer::changeSourceController( PDSSourceController& iController )
{
   changeIStream(iController.fileStream() );
}

void
PDSProxyDeliverer::changeIStream( std::istream& iStream )
{
   //cout <<"Changing SourceController "<< iController.dataSourceID() << std::endl;
   
   if( m_presentPackingInfo.size() != 0 ) {
   	m_haveRecordsFromPreviousFiles = true;
	m_headerInfo.dropOwnershipOfTypeToUnpackingInfoMap();
   	//m_typeToUnpackingInfoMap = new TypeToUnpackingInfoMap;
      //cout <<"  made new " <<m_typeToUnpackingInfoMap<<std::endl;
   } else {
   	//Haven't yet created Proxies so we can get rid of the packing info
   	//  since it hasn't been used yet   	
      //cout <<"deleting m_typeToUnpackingInfoMap since hasn't been used " << m_typeToUnpackingInfoMap<<std::endl;

      delete m_headerInfo.dropOwnershipOfTypeToUnpackingInfoMap();
      //m_typeToUnpackingInfoMap = new TypeToUnpackingInfoMap;
      //cout <<"  made new " <<m_typeToUnpackingInfoMap<<std::endl;
   }

   //need to keep ahold of old m_headerInfo.streamProxyFactoryInfoMap so 
   //  we can reindex the SourceStreams
   typedef std::map<StreamType, std::vector<DurableDataKey> > StreamTypesMap;
   StreamTypesMap oldStreamTypesMap(
      m_headerInfo.streamProxyFactoryInfoMap() );

   m_headerInfo.changeFile(iStream);
   
   initializeStreams();

   //Reindex the SourceStreams
   StreamTypesMap::iterator itNewEnd = m_headerInfo.streamProxyFactoryInfoMap().end();
   StreamTypesMap::iterator itOldEnd = oldStreamTypesMap.end();
   StreamTypesMap::iterator itNew = m_headerInfo.streamProxyFactoryInfoMap().begin();
   StreamTypesMap::iterator itOld = oldStreamTypesMap.begin();

   //At the end, add Keys that are not in the new list but are in the
   // old list
   std::vector<DurableDataKey> keysToSave;

   while( itNew != itNewEnd && itOld != itOldEnd ) {
      if( (*itNew).first == (*itOld).first ) {
      	//found the same Stream

      	//Get source streams
         StreamToSourcesMap::iterator itFound = m_streamToSourcesMap.find((*itNew).first);
         if( itFound != m_streamToSourcesMap.end() ) {
	    keysToSave.reserve((*itOld).second.size());

	    //use this when adding Keys that were in old file but
	    // are not in the new file
	    unsigned int nextExtraIndex = (*itNew).second.size();
	    
	    //Optimize for the case that the indicies don't have to change
	    SourceStreams& sourceStreams = (*itFound).second;
            SourceStreams::iterator itSourceStream = sourceStreams.begin();
	    SourceStreams::iterator itSourceStreamEnd = sourceStreams.end();

            std::vector<DurableDataKey>::iterator itNewKeyBegin = (*itNew).second.begin();
            std::vector<DurableDataKey>::iterator itNewKey = itNewKeyBegin;
            std::vector<DurableDataKey>::iterator itNewKeyEnd = (*itNew).second.end();
            std::vector<DurableDataKey>::iterator itOldKey = (*itOld).second.begin();
            std::vector<DurableDataKey>::iterator itOldKeyEnd = (*itOld).second.end();
            
            DABoolean mustReorder = false;
	    unsigned int index = PDSFileHeaderInfo::kFirstProxyIndex;
            for( ; itOldKey != itOldKeyEnd && 
		   itSourceStream != itSourceStreamEnd; 
		 ++itOldKey, ++index ) {
	       if( (*itSourceStream)->index() != index ) {
		  //No source stream for this Key because no 
		  // available storage helper
		  ++itNewKey;
		  continue;
	       }
	       /*
		 cout <<"   key: "<< (*itOldKey).type().name() <<"+"
		 <<(*itOldKey).usage().value() <<"+"
		 <<(*itOldKey).production().value() <<" "; */
	       if( itNewKey == itNewKeyEnd || *itOldKey != *itNewKey ) {
		  //indicies do not agree
		  mustReorder = true;
		  //Try to find where this type lives in the new list
		  std::vector<DurableDataKey>::iterator itFound =
		     find( itNewKeyBegin, itNewKeyEnd, *itOldKey );
		  if( itFound != itNewKeyEnd ) {
		     /*	cout << (*itSourceStream)->index() <<" -> "
			<< itFound - itNewKeyBegin ; */
		     (*itSourceStream)->setIndex( itFound - itNewKeyBegin );
		  } else {
		     //This type is not in the file
		     // We want to preserve this info in case the NEXT
		     // file in the chain has this type
		     (*itSourceStream)->setIndex(nextExtraIndex++);
		     keysToSave.push_back( *itOldKey);
                     //cout << " no match";
		  }
	       } 
	       if( itNewKey != itNewKeyEnd ) {
		  ++itNewKey;
	       }
	       //cout << std::endl;
	       ++itSourceStream;
            }
	    if (mustReorder ) {
               sort( sourceStreams.begin(), sourceStreams.end(),  SourceStreamCompare() );
	    }
	    if( ! keysToSave.empty() ) {
	       //add these Keys to our list
	       for( std::vector<DurableDataKey>::iterator itKey = keysToSave.begin();
		    itKey != keysToSave.end();
		    ++itKey ) {
		  (*itNew).second.push_back( *itKey );
	       }
	       keysToSave.erase(keysToSave.begin(), keysToSave.end() );
	    }
         }
      ++itNew;
      ++itOld;
      } else if( (*itNew).first.index() > (*itOld).first.index() ) {
      	++itOld;
      } else {
      	++itNew;
      }
   }
}
//
// const member functions
//

//
// static member functions
//

typedef DurableDataKey* _find_iterator_;
typedef DurableDataKey _find_type_;
#include "STLUtility/instantiate_find.h"

typedef PDSSourceStream** _sort_iterator_ ;
typedef SourceStreamCompare _sort_compare_class_;
typedef PDSSourceStream* _sort_value_type_;
#include "STLUtility/instantiate_sort_compare.h"
