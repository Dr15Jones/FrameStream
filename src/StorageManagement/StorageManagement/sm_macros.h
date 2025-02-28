#if !defined(STORAGEMANAGEMENT_SM_MACROS_H)
#define STORAGEMANAGEMENT_SM_MACROS_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      sm_macros
// 
// Description: C pre-processor macros to make it easier to write code
//              for the storage system
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Thu Sep  2 17:37:11 EDT 1999
// $Id: sm_macros.h,v 1.1.1.1 1999/09/13 21:21:41 cdj Exp $
//
// Revision history
//
// $Log: sm_macros.h,v $
// Revision 1.1.1.1  1999/09/13 21:21:41  cdj
// imported package
//

// system include files

// user include files
#include "StorageManagement/SMField.h"

// forward declarations
#define SM_VAR( object_, field_ ) sm_field( #field_ , object_.field_() )

#endif /* STORAGEMANAGEMENT_SM_MACROS_H */
