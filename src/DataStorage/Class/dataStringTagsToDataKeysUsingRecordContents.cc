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
              STL_SET(DurableDataKey)& oTags )
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
                  << "unknown TypeTag( " << (*it).type() << " )" << endl;
      }
   }
}

STL_SET(DurableDataKey)
dataStringTagsToDataKeysUsingRecordContents( const DataStringTagsToStore& iStore,
                                             const Record& iRecord )
{
   STL_SET(DurableDataKey) returnValue; 
   if( iStore.storeThese() ) {
   	//this is a list of things to store
   	STL_SET(DurableDataKey) storeKeys;
   	stringToTags(iStore(), storeKeys );

      //only store the stuff that is actually in the record
      insert_iterator<STL_SET(DurableDataKey) > insertItr(returnValue, returnValue.begin());
      set_intersection( storeKeys.begin(), storeKeys.end(), 
                        iRecord.begin_key(), iRecord.end_key(), insertItr );

      //warn user if there was some data item they wanted to store that isn't available
      STL_SET(DurableDataKey) missingStuff;
      insert_iterator<STL_SET(DurableDataKey) > insertItr2(missingStuff, missingStuff.begin());
      set_difference( storeKeys.begin(), storeKeys.end(), 
                        iRecord.begin_key(), iRecord.end_key(), insertItr2 );
      
      ostream& reportWarning = report(WARNING, kFacilityString);
      for( STL_SET(DurableDataKey)::iterator itDataKey = missingStuff.begin();
           itDataKey != missingStuff.end();
           ++itDataKey ) {
         reportWarning <<" will not store \""
            <<(*itDataKey).type().name()<<"\" \""
            <<(*itDataKey).usage().value()<<"\" \""
            <<(*itDataKey).production().value()<<"\" since not available in Record "
            <<iRecord.stream().value()<<"\n";
      }
      if( 0 != missingStuff.size() ) {
         reportWarning <<flush;
      }
   } else {
   	//this is a list of things not to store
   	STL_SET(DurableDataKey) doNotStore;
   	stringToTags(iStore(), doNotStore );
   	
   	//keep only stuff that is in Record that is NOT also in doNotStore
      insert_iterator<STL_SET(DurableDataKey) > insertItr(returnValue, returnValue.begin());
      set_difference( iRecord.begin_key(), iRecord.end_key(), 
                      doNotStore.begin(), doNotStore.end(), insertItr );

   }
   return returnValue;
}

#if !defined(NO_STD_NAMESPACE_BUG)
#define STD_PREFIX std::
#else
#define STD_PREFIX
#endif

#if defined(NEED_TO_BE_IN_NAMESPACE_TO_INSTANTIATE_TEMPLATE_BUG)
#if defined(STD_PREFIX)
#undef STD_PREFIX
#define STD_PREFIX
#endif
namespace std {
#endif
template 
insert_iterator<STL_SET(DurableDataKey) > 
STD_PREFIX set_difference( Record::const_key_iterator, Record::const_key_iterator,
 STL_SET(DurableDataKey)::iterator, STL_SET(DurableDataKey)::iterator,
 insert_iterator<STL_SET(DurableDataKey) > );  
 
template 
insert_iterator<STL_SET(DurableDataKey) > 
STD_PREFIX set_difference( STL_SET(DurableDataKey)::iterator, STL_SET(DurableDataKey)::iterator,
Record::const_key_iterator, Record::const_key_iterator,
  insert_iterator<STL_SET(DurableDataKey) > );  

template 
insert_iterator<STL_SET(DurableDataKey) > 
STD_PREFIX set_intersection( STL_SET(DurableDataKey)::iterator, STL_SET(DurableDataKey)::iterator,
 Record::const_key_iterator, Record::const_key_iterator,
 insert_iterator<STL_SET(DurableDataKey) > );  
#if defined(NEED_TO_BE_IN_NAMESPACE_TO_INSTANTIATE_TEMPLATE_BUG)
#undef STD_PREFIX
}
#endif
 
//copy is used by difference
#define _copy_in_iterator_ STL_SET(DurableDataKey)::iterator 
typedef insert_iterator<STL_SET(DurableDataKey) > _copy_out_iterator_;
#include "STLUtility/instantiate_copy.h"

#undef STLUTILITY_INSTANTIATE_COPY_H
#undef _copy_in_iterator_

#define _copy_in_iterator_ Record::const_key_iterator 
#include "STLUtility/instantiate_copy.h"
