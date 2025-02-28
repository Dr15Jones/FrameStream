#if !defined(STORAGEMANAGEMENT_INSTANTIATE_SMPTRHOLDERHELPER_H)
#define STORAGEMANAGEMENT_INSTANTIATE_SMPTRHOLDERHELPER_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      instantiate_smptrholderhelper
// 
// Description: Code required to instantiate an SMPtrHolderStorageHelper
//               and all the templated classes it depends on.
//
// Usage:
//    <usage>
//
// Author:      Konstantin Bukin
// Created:     Mon Oct 23 23:02:01 EDT 2000
// $Id:
//
// Revision history

// system include files
//#include "STLUtility/fwd_vector.h"

// user include files
#include "StorageManagement/SMPtrHolder.h"
#include "ToolBox/TBDerefItr.h"

// forward declarations
#define HETEROCONTAINER_HCTYPETAGTEMPLATE_CC

#include "ToolBox/Template/TBDerefItr.cc"
template class TBDerefItr<_ptr_element_ const*, _val_element_, _val_element_>;
template class TBDerefItr<_ptr_element_ const*, const _val_element_, _val_element_>;

#include "StorageManagement/Template/SMPtrHolder.cc"
template class SMPtrHolder<_ptr_element_,_val_element_>;

#include "StorageManagement/Template/SMPtrHolderStorageHelper.cc"
template class SMPtrHolderStorageHelper< _ptr_element_,_val_element_ > ;

#include "StorageManagement/Template/SMProxyWriter.cc"
template class SMProxyWriter<SMPtrHolder<_ptr_element_,_val_element_> >;

#include "StorageManagement/Template/SMContents.cc"
template class SMContents<TBDerefItr<_ptr_element_ const*, _val_element_, _val_element_> >;
template class SMContents<SMPtrHolder<_ptr_element_,_val_element_>* >;

#include "StorageManagement/Template/SMMakeContents.cc"
template class SMMakeContents<setPointer_insert_iterator<SMPtrHolder<_ptr_element_,_val_element_> > >;

#include "StorageManagement/Template/SMFillContents.cc"
template class SMFillContents<back_insert_iterator<vector<SMPtrHolder<_ptr_element_,_val_element_> > > >;

SMSTORAGEHELPER_MAKE_PTR( _ptr_element_,_val_element_ )

#include "StorageManagement/Template/SMStorageHelper.cc"
template class SMStorageHelper<SMPtrHolder<_ptr_element_,_val_element_> >;

#include "StorageManagement/Template/SMStorageProxyHelper.cc"
template class SMStorageProxyHelper<SMPtrHolder<_ptr_element_,_val_element_> >;

#include "DataHandler/Template/RecordMethods.cc"

#include "HeteroContainer/Template/HCMethods.cc"

#include "HeteroContainer/Template/HCTypeTagTemplate.cc"

#include "DataHandler/Template/ProxyTemplate.cc"
template class ProxyTemplate<SMPtrHolder<_ptr_element_, _val_element_> >;

template SMSourceStream& operator>>(SMSourceStream& iSource, SMPtrHolder<_ptr_element_,_val_element_>&);

#include "FrameAccess/instantiate_macros.h"
//INSTANTIATE_SMPTRHOLDER( RichHypAveAngle*, RichHypAveAngle )
//typedef SMPtrHolder<RichHypAveAngle*, RichHypAveAngle> __one_element_;
//HCTYPETAGTEMPLATE_CLASSNAME(__one_element_, DataKey) 
//#include "StorageManagement/instantiate_one_typetag.h"


#endif /* STORAGEMANAGEMENT_INSTANTIATE_SMPTRHOLDERHELPER_H */



