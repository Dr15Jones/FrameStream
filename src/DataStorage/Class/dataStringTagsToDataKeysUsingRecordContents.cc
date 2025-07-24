// -*- C++ -*-
//
// Package:     <DataStorage>
// Module:      dataStringTagsToDataKeysUsingRecordContents
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon Jun 11 14:50:38 EDT 2001
// $Id: dataStringTagsToDataKeysUsingRecordContents.cc,v 1.2 2002/12/09 16:03:55 cleo3 Exp $
//
// Revision history
//
// $Log: dataStringTagsToDataKeysUsingRecordContents.cc,v $
// Revision 1.2  2002/12/09 16:03:55  cleo3
// work around g++ instantiation bug
//
// Revision 1.1  2001/06/15 21:05:11  cdj
// can now specify data (not) to store in a sink
//

#include "Experiment/Experiment.h"

// system include files
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
#include <algorithm>
#include <iterator>
//#include <utility>

// user include files
#include "Experiment/report.h"
#include "DataStorage/dataStringTagsToDataKeysUsingRecordContents.h"
#include "DataHandler/Record.h"
#include "DataHandler/RecordKeyItr.h"

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "DataStorage.dataStringTagsToDataKeysUsingRecordContents" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: dataStringTagsToDataKeysUsingRecordContents.cc,v 1.2 2002/12/09 16:03:55 cleo3 Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//


//
// constructors and destructor
//
static 
void 
stringToTags( const DataStringTagsToStore::Tags& iStringTags,
              std::set<DurableDataKey>& oTags )
{
   DataStringTagsToStore::Tags::const_iterator itEnd 
      = iStringTags.end();
   for( DataStringTagsToStore::Tags::const_iterator it 
           = iStringTags.begin();
        it != itEnd;
        ++it ) {
      TypeTag typeTag = TypeTag::findType( (*it).type() );
      if( TypeTag::kDefaultValue != typeTag.value() ) {
         // now create DataKey
         DurableDataKey key( 
                  DataKey( typeTag, 
                           UsageTag( (*it).usage().c_str() ),
                           ProductionTag( (*it).production().c_str() ) )
                  );
               // and insert into set
         oTags.insert( key );
      } else {
         report( ERROR, kFacilityString )
                  << "unknown TypeTag( " << (*it).type() << " )" << std::endl;
      }
   }
}

std::set<DurableDataKey>
dataStringTagsToDataKeysUsingRecordContents( const DataStringTagsToStore& iStore,
                                             const Record& iRecord )
{
   std::set<DurableDataKey> returnValue; 
   if( iStore.storeThese() ) {
   	//this is a list of things to store
   	std::set<DurableDataKey> storeKeys;
   	stringToTags(iStore(), storeKeys );

      //only store the stuff that is actually in the record
      std::insert_iterator<std::set<DurableDataKey> > insertItr(returnValue, returnValue.begin());
      set_intersection( storeKeys.begin(), storeKeys.end(), 
                        iRecord.begin_key(), iRecord.end_key(), insertItr );

      //warn user if there was some data item they wanted to store that isn't available
      std::set<DurableDataKey> missingStuff;
      std::insert_iterator<std::set<DurableDataKey> > insertItr2(missingStuff, missingStuff.begin());
      set_difference( storeKeys.begin(), storeKeys.end(), 
                        iRecord.begin_key(), iRecord.end_key(), insertItr2 );
      
     std::ostream& reportWarning = report(WARNING, kFacilityString);
      for( std::set<DurableDataKey>::iterator itDataKey = missingStuff.begin();
           itDataKey != missingStuff.end();
           ++itDataKey ) {
         reportWarning <<" will not store \""
            <<(*itDataKey).type().name()<<"\" \""
            <<(*itDataKey).usage().value()<<"\" \""
            <<(*itDataKey).production().value()<<"\" since not available in Record "
            <<iRecord.stream().value()<<"\n";
      }
      if( 0 != missingStuff.size() ) {
         reportWarning <<std::flush;
      }
   } else {
   	//this is a list of things not to store
   	std::set<DurableDataKey> doNotStore;
   	stringToTags(iStore(), doNotStore );
   	
   	//keep only stuff that is in Record that is NOT also in doNotStore
      std::insert_iterator<std::set<DurableDataKey> > insertItr(returnValue, returnValue.begin());
      set_difference( iRecord.begin_key(), iRecord.end_key(), 
                      doNotStore.begin(), doNotStore.end(), insertItr );

   }
   return returnValue;
}
 
