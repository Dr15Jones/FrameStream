// -*- C++ -*-
//
// Package:     JobControl
// Module:      STL_SummaryCounter
// 
// Description: Instantiate STL classes for SummaryCounter
//
//
// Author:      Martin Lohner
// Created:     Fri July 28 17:20:00 EDT 1998
// $Id: STL_SummaryCounter.cc,v 1.1 1998/07/29 20:06:51 mkl Exp $
//
// Revision history
//
// $Log: STL_SummaryCounter.cc,v $
// Revision 1.1  1998/07/29 20:06:51  mkl
// new summary command implemented
//
//


#include "Experiment/Experiment.h"
#include "Experiment/types.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "DataHandler/Stream.h"

// stl files
#include <map>

typedef Stream::Type _map_key_ ;
typedef Count _map_contents_ ;
typedef less< _map_key_ > _map_compare_;

#include "STLUtility/instantiate_map.h"
