// -*- C++ -*-
//
// Package:     JobControl
// Module:      T_DummySourceBinder
// 
// Description: Instantiate Binder template for DummySourceBinder
//
//
// Author:      Martin Lohner
// Created:     Wed June 16 12:20:00 EDT 1998
// $Id: T_DummySourceBinder.cc,v 1.2 1998/11/09 19:33:20 mkl Exp $
//
// Revision history
//
// $Log: T_DummySourceBinder.cc,v $
// Revision 1.2  1998/11/09 19:33:20  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.1  1998/06/17 20:20:28  mkl
// fanned out instantiation files for Not/Chainable Binders
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "JobControl/BinderBase.h"

// stl includes
#include <string>
#include <map>

typedef DummySourceBinder _binder_;
#include "DataDelivery/instantiateNotChainableBinder.h"

