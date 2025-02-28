#if !defined(STORAGEMANAGEMENT_INSTANTIATE_FAPTRTABLEHELPER_H)
#define STORAGEMANAGEMENT_INSTANTIATE_FAPTRTABLEHELPER_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      instantiate_faptrtablehelper
// 
// Description: Code required to instantiate an FAPtrTableStorageHelper
//               and all the templated classes it depends on.
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Fri Jun 11 15:16:06 EDT 1999
// $Id: instantiate_faptrtablehelper.h,v 1.2 1999/10/18 18:27:32 cdj Exp $
//
// Revision history
//
// $Log: instantiate_faptrtablehelper.h,v $
// Revision 1.2  1999/10/18 18:27:32  cdj
// updated to work with new design of its class
//
// Revision 1.1.1.1  1999/09/13 21:21:42  cdj
// imported package
//

// system include files

// user include files
#include "FrameAccess/FAPtrTable.h"
#include "FrameAccess/FAPtrTableInsertItr.h"

// forward declarations


#include "StorageManagement/Template/SMProxyWriter.cc"
template class SMProxyWriter<FAPtrTable<_many_element_> >;

#include "StorageManagement/Template/SMContents.cc"
template class SMContents<FAPtrTable<_many_element_>::const_iterator >;

#include "StorageManagement/Template/SMMakeContents.cc"
template class SMMakeContents<FAPtrTableInsertItr<_many_element_ > >;

#include "StorageManagement/Template/SMFAPtrTableStorageHelper.cc"
template class SMFAPtrTableStorageHelper< _many_element_ > ;

SMSTORAGEHELPER_MAKE( _many_element_ )

#include "StorageManagement/Template/SMStorageHelper.cc"
template class SMStorageHelper<FAPtrTable<_many_element_> >;

#include "StorageManagement/Template/SMStorageProxyHelper.cc"
template class SMStorageProxyHelper<FAPtrTable<_many_element_> >;

#endif /* STORAGEMANAGEMENT_INSTANTIATE_FAPTRTABLEHELPER_H */
