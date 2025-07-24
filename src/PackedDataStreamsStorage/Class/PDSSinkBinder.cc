// -*- C++ -*-
//
// Package:     <PackedDataStreamsStorage>
// Module:      PDSSinkBinder
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri Sep 22 14:45:35 EDT 2000
// $Id: PDSSinkBinder.cc,v 1.4 2001/06/15 21:07:18 cdj Exp $
//
// Revision history
//
// $Log: PDSSinkBinder.cc,v $
// Revision 1.4  2001/06/15 21:07:18  cdj
// can now specify data (not) to store
//
// Revision 1.3  2000/10/08 17:00:47  cdj
// now only try to store those items that are actually in a Record
//
// Revision 1.2  2000/10/02 20:46:49  cdj
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
//#include "Experiment/report.h"
#include "PackedDataStreamsStorage/PDSSinkBinder.h"
#include "PackedDataStreamsStorage/PDSSinkController.h"
#include "StorageManagement/SMStorageHelperManager.h"

#include "JobControl/JobControl.h"
#include "DataDelivery/FrameDeliverer.h"
#include "DataHandler/RecordProvider.h"
#include "DataHandler/Record.h"
#include "DataHandler/RecordKeyItr.h"

#include "DataHandler/StreamSet.h"

#include "DataStorage/dataStringTagsToDataKeysUsingRecordContents.h"
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

static const char* const kFacilityString = "PackedDataStreamsStorage.PDSSinkBinder" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: PDSSinkBinder.cc,v 1.4 2001/06/15 21:07:18 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
PDSSinkBinder::PDSSinkBinder( const std::string& iFileName,
			      const Stream::Set& iBindStreams )
   : DataSinkBinder( iFileName, std::string(""), iBindStreams ),
   m_streamsDataMap(0)
{
   
}

PDSSinkBinder::PDSSinkBinder( const std::string& iFileName,
			      const Stream::Set& iBindStreams,
			      const StreamToDataStringTagsToStoreMap& iStreamsDataMap )
   : DataSinkBinder( iFileName, std::string(""), iBindStreams ),
   m_streamsDataMap( new StreamToDataStringTagsToStoreMap(iStreamsDataMap))
{
   
}

// PDSSinkBinder::PDSSinkBinder( const PDSSinkBinder& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

PDSSinkBinder::~PDSSinkBinder()
{
}

//
// assignment operators
//
// const PDSSinkBinder& PDSSinkBinder::operator=( const PDSSinkBinder& rhs )
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
DataSinkController*
PDSSinkBinder::createDataSinkController( void ) const
{
   if( 0 == m_streamsDataMap ) {
      return createUsingAll();
   }
   return createSpecifyingData();
}

string
PDSSinkBinder::fileName( void ) const
{
   return dataSinkID();
}


template<class KeyItr>
inline
void
fillDataKeysIfFactoryExists( KeyItr iKeyBegin, KeyItr iKeyEnd,
                             SMStorageHelperManager::factory_iterator iFactoryBegin,
                             SMStorageHelperManager::factory_iterator iFactoryEnd,
                             std::set<DurableDataKey>& iDataKeys )
{
   KeyItr itKey = iKeyBegin;
   SMStorageHelperManager::factory_iterator itFactory = iFactoryBegin;
   while( (itKey != iKeyEnd) &&
	  (itFactory != iFactoryEnd ) ) {

      if( (*itKey).type() == (*itFactory)->proxyTypeTag() ) {
         iDataKeys.insert( *itKey );
	 //advance only itRecordKey because we could have several
	 // keys with the same type
	 ++itKey;
      } else {
      	if( (*itKey).type() < (*itFactory)->proxyTypeTag() ) {
      	   ++itKey;
	} else {
	   ++itFactory;
	}
      }
   }
}
DataSinkController*
PDSSinkBinder::createUsingAll() const
{
   JobControl* jc = JobControl::instance();

   PDSDataToStore dataToStore;

   SMStorageHelperManager& shm = SMStorageHelperManager::instance();
      
   for(std::set<StreamType>::const_iterator itStream = boundStreams().begin();
       itStream != boundStreams().end();
       ++itStream ) {
      std::set<DurableDataKey>& dataKeys = dataToStore[*itStream]();

      const Record& record = 
	 jc->frameDeliverer().recordProvider(*itStream).unsynchronizedRecord();

      
      //Now put all the Keys in the Record into dataToStore IF the
      // proper factory exists
      SMStorageHelperManager& shm = SMStorageHelperManager::instance();
      
      fillDataKeysIfFactoryExists(record.begin_key(), record.end_key(),
                                  shm.factory_begin(), shm.factory_end(),
                                  dataKeys );
   }
   
   return new PDSSinkController( dataSinkID() , boundStreams(), dataToStore );
}

DataSinkController*
PDSSinkBinder::createSpecifyingData() const
{
   JobControl* jc = JobControl::instance();
   
   SMStorageHelperManager& shm = SMStorageHelperManager::instance();

   StreamToDataStringTagsToStoreMap::const_iterator itEnd
      = m_streamsDataMap->end();
   PDSDataToStore dataToStore;
   for( StreamToDataStringTagsToStoreMap::const_iterator itStreamData =
            m_streamsDataMap->begin();
        itStreamData != itEnd;
        ++itStreamData ) {
      const Record& record = 
	   jc->frameDeliverer().recordProvider((*itStreamData).first).unsynchronizedRecord();
      std::set<DurableDataKey> allKeys = 
      dataStringTagsToDataKeysUsingRecordContents( (*itStreamData).second,
                                                   record );      

      fillDataKeysIfFactoryExists(allKeys.begin(), allKeys.end(),
                                  shm.factory_begin(), shm.factory_end(),
                                  dataToStore[(*itStreamData).first ]() );
   }
   return new PDSSinkController( dataSinkID(), boundStreams(), dataToStore); 
}

//
// static member functions
//
