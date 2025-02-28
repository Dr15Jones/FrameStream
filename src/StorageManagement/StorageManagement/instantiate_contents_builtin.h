#if !defined(STORAGEMANAGEMENT_INSTANTIATE_CONTENTS_BUILTIN_H)
#define STORAGEMANAGEMENT_INSTANTIATE_CONTENTS_BUILTIN_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      instantiate_contents_builtin
// 
/** \file StorageManagement/instantiate_contents_builtin.h
 Description: Used to instantiate classes needed to store a container of
              builtin types

 Usage:
    You need to set two typedef, _container_type_ .

    \code
       //want to be able to store a vector< double >
       typedef STL_VECTOR(double) _container_type_;
       #include "StorageManagement/instantiate_contents_builtin.h"
    \endcode

*/
//
// Author:      Chris D Jones
// Created:     Thu Jan  6 16:46:56 EST 2000
// $Id: instantiate_contents_builtin.h,v 1.1 2000/01/06 22:13:17 cdj Exp $
//
// Revision history
//
// $Log: instantiate_contents_builtin.h,v $
// Revision 1.1  2000/01/06 22:13:17  cdj
// made it easier to instantiate templates used by sm_contents_builtin
//

// system include files

// user include files

// forward declarations

//NOTE: in future need to set HCTypeTagTemplate's name

typedef _container_type_::value_type _contained_type_;

#include "StorageManagement/Template/SMFillContents.cc"
template class SMFillContents<back_insert_iterator<_container_type_ > >;

#include "DataHandler/Template/RecordMethods.cc"
#include "HeteroContainer/Template/HCMethods.cc"
#include "HeteroContainer/Template/HCTypeTagTemplate.cc"

//needed by sm_fill_contents
template class RecordMethods<_contained_type_>;
template class HCMethods<_contained_type_, 
                         ProxyTemplate<_contained_type_>,
                         Record, DataKey, IdTags>;
template class HCTypeTagTemplate<_contained_type_, DataKey>;

//needed by sm_contents_builtin
template class RecordMethods<const _contained_type_>;
template class HCMethods<const _contained_type_,
                         ProxyTemplate<const _contained_type_>, 
                         Record, DataKey, IdTags>;
template class HCTypeTagTemplate<const _contained_type_, DataKey>;

#include "StorageManagement/Template/SMContentsBuiltIn.cc"
template class SMContentsBuiltIn<_container_type_::const_iterator >;

//need to compare two vectors
typedef _container_type_::const_iterator _mismatch_iterator1_type_;
typedef _container_type_::const_iterator _mismatch_iterator2_type_;

#include "STLUtility/instantiate_mismatch.h"

#endif
