#if !defined(STORAGEMANAGEMENT_INSTANTIATE_LATTICELINKHELPER_H)
#define STORAGEMANAGEMENT_INSTANTIATE_LATTICELINKHELPER_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      instantiate_latticelinkhelper
// 
// Description: instantiate classes used by SMStorageLatticeLinkHelper
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Mon Oct  4 10:38:25 EDT 1999
// $Id: instantiate_latticelinkhelper.h,v 1.3 2002/06/12 20:09:13 cleo3 Exp $
//
// Revision history
//
// $Log: instantiate_latticelinkhelper.h,v $
// Revision 1.3  2002/06/12 20:09:13  cleo3
// updated to new template specialization syntax
//
// Revision 1.2  1999/10/18 18:27:34  cdj
// updated to work with new design of its class
//
// Revision 1.1  1999/10/11 22:00:45  cdj
// added Lattice storage code
//

// system include files

// user include files
#include "StorageManagement/SMLatticeLinkInfoBase.h"
#include "StorageManagement/SMLatticeLinkInfoIn.h"
// forward declarations

//forward decleration to stop autoinstantiation
template<>
SMLatticeLinkInfoBase< _lattice_element_ >*
SMStorageHelper<SMLatticeLinkInfoBase< _lattice_element_ > >::make( const SMLatticeLinkInfoBase< _lattice_element_ >& iTable ) const {
   //copy one to the other
   assert(false);
   return new SMLatticeLinkInfoIn<_lattice_element_>;
}

#include "StorageManagement/Template/SMStorageHelper.cc"
template class SMStorageHelper<SMLatticeLinkInfoBase< _lattice_element_ > >;

#endif /* STORAGEMANAGEMENT_INSTANTIATE_LATTICELINKHELPER_H */
