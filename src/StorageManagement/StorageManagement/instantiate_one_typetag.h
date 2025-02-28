#if !defined(STORAGEMANAGEMENT_INSTANTIATE_ONE_TYPETAG_H)
#define STORAGEMANAGEMENT_INSTANTIATE_ONE_TYPETAG_H
// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      instantiate_one_typetag
// 
/**\file instantiate_one_typetag instantiate_one_typetag.h StorageManagement/instantiate_one_typetag.h

 Description: Instantiate templates necessary to use a TypeTag

 Usage:
    Assumes _one_element_ has been defined prior to including this file

*/
//
// Author:      Chris D Jones
// Created:     Fri Oct 15 13:31:24 EDT 1999
// $Id: instantiate_one_typetag.h,v 1.1 1999/10/18 18:29:21 cdj Exp $
//
// Revision history
//
// $Log: instantiate_one_typetag.h,v $
// Revision 1.1  1999/10/18 18:29:21  cdj
// first submission
//

// instantiations

#include "DataHandler/Template/RecordMethods.cc"
template class RecordMethods< _one_element_ > ;
#include "HeteroContainer/Template/HCMethods.cc"
template class HCMethods< _one_element_,
                          ProxyTemplate< _one_element_ >,
                          Record,
                          DataKey,
                          IdTags > ;

#endif /* STORAGEMANAGEMENT_INSTANTIATE_ONE_TYPETAG_H */
