// -*- C++ -*-
//
// Package:     BinaryDelivery
// Module:      T_Binder_BinarySourceBinder.cc
// 
// Description: Instantiate Binder
//
//
// Author:      Martin Lohner
// Created:     Mon Nov 16 12:20:00 EDT 1998
// $Id: T_Binder_BinarySourceBinder.cc,v 1.1 1998/11/16 16:51:35 mkl Exp $
//
// Revision history
//
// $Log: T_Binder_BinarySourceBinder.cc,v $
// Revision 1.1  1998/11/16 16:51:35  mkl
// additions necessary to load BinarySourceFormat and chain binary files
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "BinaryDelivery/BinarySourceBinder.h"

// stl includes
#include <string>
#include <map>

typedef BinarySourceBinder _binder_;
#include "DataDelivery/instantiateChainableBinder.h"

