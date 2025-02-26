#if !defined(DATASTORAGE_DATASTRINGTAGSTODATAKEYSUSINGRECORDCONTENTS_H)
#define DATASTORAGE_DATASTRINGTAGSTODATAKEYSUSINGRECORDCONTENTS_H
// -*- C++ -*-
//
// Package:     <DataStorage>
// Module:      dataStringTagsToDataKeysUsingRecordContents
// 
/**\class dataStringTagsToDataKeysUsingRecordContents dataStringTagsToDataKeysUsingRecordContents.h DataStorage/dataStringTagsToDataKeysUsingRecordContents.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Mon Jun 11 14:31:49 EDT 2001
// $Id: dataStringTagsToDataKeysUsingRecordContents.h,v 1.1 2001/06/15 21:05:15 cdj Exp $
//
// Revision history
//
// $Log: dataStringTagsToDataKeysUsingRecordContents.h,v $
// Revision 1.1  2001/06/15 21:05:15  cdj
// can now specify data (not) to store in a sink
//

// system include files

// user include files
#include "DataHandler/DurableDataKey.h"
#include "DataStorage/DataStringTagsToStore.h"

#include "STLUtility/fwd_set.h"

// forward declarations
class DataStringTagsToStore;
class Record;

STL_SET(DurableDataKey)
dataStringTagsToDataKeysUsingRecordContents( const DataStringTagsToStore&,
                                             const Record& );
#endif /* DATASTORAGE_DATASTRINGTAGSTODATAKEYSUSINGRECORDCONTENTS_H */
