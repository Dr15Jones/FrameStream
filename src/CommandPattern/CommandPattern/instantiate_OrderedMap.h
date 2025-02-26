#if !defined(COMMANDPATTERN_INSTANTIATE_ORDEREDMAP_H)
#define COMMANDPATTERN_INSTANTIATE_ORDEREDMAP_H
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      instantiate_OrderedMap
// 
// Description: Code required to explicilty instantiate OrderMap<>
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Wed Apr 14 17:00:35 EDT 1999
// $Id: instantiate_OrderedMap.h,v 1.1 1999/04/14 21:15:39 mkl Exp $
//
// Revision history
//
// $Log: instantiate_OrderedMap.h,v $
// Revision 1.1  1999/04/14 21:15:39  mkl
// ordered container used in Suez
//

// system include files

// user include files

#include <vector>
#include "CommandPattern/Template/OrderedMap.cc"

template class OrderedMap< _orderedmap_key_, _orderedmap_contents_ >;
typedef OrderedMap< _orderedmap_key_, _orderedmap_contents_ >::value_type
_vector_contents_;

#include "STLUtility/instantiate_vector.h"

#endif /* COMMANDPATTERN_INSTANTIATE_ORDEREDMAP_H */
