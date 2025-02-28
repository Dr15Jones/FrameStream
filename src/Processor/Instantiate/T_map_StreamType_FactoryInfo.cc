// -*- C++ -*-
//
// Package:     Producer
// Module:      T_map_StreamType_FactoryInfo
// 
// Description: 
//
//
// Author:      Martin Lohner, Chris Jones
// Created:     Thu Jan 15 12:20:00 EDT 1998
// $Id: T_map_StreamType_FactoryInfo.cc,v 1.1 1998/11/01 20:14:45 mkl Exp $
//
// Revision history
//
// $Log: T_map_StreamType_FactoryInfo.cc,v $
// Revision 1.1  1998/11/01 20:14:45  mkl
// switched to new proxy factory registration scheme
//
//


#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "DataHandler/Stream.h"
#include "Processor/Producer.h"

// STL includes
#include <vector>
#include <map>

typedef Stream::Type _map_key_;
typedef Producer::FactoryInfo _map_contents_;
typedef less< _map_key_ > _map_compare_;

#include "STLUtility/instantiate_map.h"
