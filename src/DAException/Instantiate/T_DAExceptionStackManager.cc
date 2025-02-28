// -*- C++ -*-
//
// Package:     DAException
// Module:      T_DAExceptionStackManager
//
// Description: Instantiate DAExceptionStackManager<T>
//
//
// Author:      Valentine Kouznetsov
// Created:     Thu Apr 24 09:35:30 EDT 2003
// $Id: T_DAExceptionStackManager.cc,v 1.2 2003/08/21 17:13:34 vk Exp $
//
// Revision history
//
// $Log: T_DAExceptionStackManager.cc,v $
// Revision 1.2  2003/08/21 17:13:34  vk
// Add instantiation of STL_VECTOR(T) with T=DataKey
//
// Revision 1.1  2003/04/25 15:20:04  vk
// Reorginize package, add new stack class
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <vector>
#include <map>
#include <set>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "DataHandler/DurableDataKey.h"
#include "DAException/DAExceptionStack.h"
#include "DAException/Template/DAExceptionStackManager.cc"

// stl includes
#include <string>
#include <vector>
#include <map>
#include <set>

template class DAExceptionStackManager< DataKey >;
template class DAExceptionStackManager< DAExceptionStack::StackPair >;

// typedef vector contents and instantiate vector //
typedef DataKey _vector_contents_ ;
#include "STLUtility/instantiate_vector.h"
