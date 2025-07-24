// -*- C++ -*-
//
// Package:     JobControl
// Module:      T_OrderedMap_string_DataSourceBinderP.cc
// 
// Description: Instantiate OrderedMap for (string, DataSourceBinder* )
//
//
// Author:      Martin Lohner
// Created:     Wed April 14 12:20:00 EDT 1999
// $Id: T_OrderedMap_string_DataSinkBinderP.cc,v 1.1 1999/04/14 21:16:27 mkl Exp $
//
// Revision history
//
// $Log: T_OrderedMap_string_DataSinkBinderP.cc,v $
// Revision 1.1  1999/04/14 21:16:27  mkl
// ordered container used in Suez
//
//
//


#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "CommandPattern/Template/OrderedMap.cc"

// STL include files
#include <string>
#include <vector>

class DataSinkBinder ;

typedef std::string _orderedmap_key_;
typedef DataSinkBinder* _orderedmap_contents_;

#include "CommandPattern/instantiate_OrderedMap.h"
