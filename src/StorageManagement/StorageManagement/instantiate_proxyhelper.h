#if !defined(STORAGEMANAGEMENT_INSTANTIATE_PROXYHELPER_H)
#define STORAGEMANAGEMENT_INSTANTIATE_PROXYHELPER_H
// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      instantiate_proxyhelper
// 
/**\file instantiate_proxyhelper.h StorageManagement/instantiate_proxyhelper.h

 Description: instantiate templates needed by a SMStorageProxyHelper

 Usage:
    Before including this file, the symbol _store_element_ must be defined
    as either a typedef of a #define. 

    This file is included by *StorageHelper.cc file generated by mkstoreone

*/
//
// Author:      Chris D Jones
// Created:     Mon Oct 18 10:09:29 EDT 1999
// $Id: instantiate_proxyhelper.h,v 1.1 1999/10/18 18:29:22 cdj Exp $
//
// Revision history
//
// $Log: instantiate_proxyhelper.h,v $
// Revision 1.1  1999/10/18 18:29:22  cdj
// first submission
//

// system include files

// user include files

// forward declarations

#include "StorageManagement/Template/SMStorageHelper.cc"
template class SMStorageHelper<_store_element_>;

#include "StorageManagement/Template/SMStorageProxyHelper.cc"
template class SMStorageProxyHelper<_store_element_>;

#include "StorageManagement/Template/SMProxyWriter.cc"
template class SMProxyWriter<_store_element_>;

#endif /* STORAGEMANAGEMENT_INSTANTIATE_PROXYHELPER_H */
