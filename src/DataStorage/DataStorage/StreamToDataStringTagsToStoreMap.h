#if !defined(DATASTORAGE_STREAMTODATASTRINGTAGSTOSTOREMAP_H)
#define DATASTORAGE_STREAMTODATASTRINGTAGSTOSTOREMAP_H
// -*- C++ -*-
//
// Package:     <DataStorage>
// Module:      StreamToDataStringTagsToStoreMap
// 
/**\class StreamToDataStringTagsToStoreMap StreamToDataStringTagsToStoreMap.h DataStorage/StreamToDataStringTagsToStoreMap.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Fri Jun  8 15:57:07 EDT 2001
// $Id: StreamToDataStringTagsToStoreMap.h,v 1.1 2001/06/15 21:05:15 cdj Exp $
//
// Revision history
//
// $Log: StreamToDataStringTagsToStoreMap.h,v $
// Revision 1.1  2001/06/15 21:05:15  cdj
// can now specify data (not) to store in a sink
//

// system include files

// user include files
#include <map>
#include "DataStorage/DataStringTagsToStore.h"
// forward declarations

typedef std::map<StreamType, DataStringTagsToStore> StreamToDataStringTagsToStoreMap;
#endif /* DATASTORAGE_STREAMTODATASTRINGTAGSTOSTOREMAP_H */
