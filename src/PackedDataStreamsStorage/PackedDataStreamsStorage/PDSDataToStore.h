#if !defined(PACKEDDATASTREAMSSTORAGE_PDSDATATOSTORE_H)
#define PACKEDDATASTREAMSSTORAGE_PDSDATATOSTORE_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsStorage>
// Module:      PDSDataToStore
// 
/**\class PDSDataToStore PDSDataToStore.h PackedDataStreamsStorage/PDSDataToStore.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Thu Sep 14 12:59:49 EDT 2000
// $Id: PDSDataToStore.h,v 1.1.1.1 2000/09/29 17:49:40 cdj Exp $
//
// Revision history
//
// $Log: PDSDataToStore.h,v $
// Revision 1.1.1.1  2000/09/29 17:49:40  cdj
// imported
//

// system include files
#include <set>
#include <map>

// user include file
#include "DataHandler/DurableDataKey.h"
#include "DataHandler/Stream.h"

// forward declarations
#include "STLUtility/fwd_map.h"
#include "STLUtility/fwd_set.h"


struct DataKeySet { // introduce utility class to 
      // ease map-of-set instantiation
      typedef STL_SET( DurableDataKey ) DataKeys;
      typedef DataKeys::const_iterator const_iterator;
      typedef DataKeys::iterator iterator;
      DataKeys& operator()() { return m_dataKeys; }
      const DataKeys& operator()() const { return m_dataKeys; }
      
      DataKeys m_dataKeys;
};

typedef STL_MAP( Stream::Type, DataKeySet ) PDSDataToStore;


// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsStorage/Template/PDSDataToStore.cc"
//#endif

#endif /* PACKEDDATASTREAMSSTORAGE_PDSDATATOSTORE_H */
