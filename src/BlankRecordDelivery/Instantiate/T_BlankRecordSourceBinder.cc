// -*- C++ -*-
//
// Package:     BlankRecordDelivery
// Module:      STL_BlankRecordSourceBinder
// 
// Description: Instantiate STL classes for Binder
//
//
// Author:      Martin Lohner
// Created:     Wed June 16 12:20:00 EDT 1998
// $Id: T_BlankRecordSourceBinder.cc,v 1.1 1998/06/17 20:29:37 mkl Exp $
//
// Revision history
//
// $Log: T_BlankRecordSourceBinder.cc,v $
// Revision 1.1  1998/06/17 20:29:37  mkl
// added instantiation files for Not/Chainable Binders
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "BlankRecordDelivery/BlankRecordSourceBinder.h"

// stl includes
#include <string>
#include <map>

typedef BlankRecordSourceBinder _binder_;
#include "DataDelivery/instantiateNotChainableBinder.h"

