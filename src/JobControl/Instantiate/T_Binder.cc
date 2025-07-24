// -*- C++ -*-
//
// Package:     JobControl
// Module:      STL_Binder
// 
// Description: Instantiate STL classes for Binder
//
//
// Author:      Martin Lohner
// Created:     Wed June 16 12:20:00 EDT 1998
// $Id: T_Binder.cc,v 1.3 2002/12/06 16:31:25 cleo3 Exp $
//
// Revision history
//
// $Log: T_Binder.cc,v $
// Revision 1.3  2002/12/06 16:31:25  cleo3
// removed old g++ cpp switch
//
// Revision 1.2  1998/09/23 19:01:17  mkl
// typename; protect against multiple inclusion. All the make egcs happy
//
// Revision 1.1  1998/06/17 20:20:28  mkl
// fanned out instantiation files for Not/Chainable Binders
//
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "JobControl/SourceManager.h"
#include "DataDelivery/BinderBase.h"

// stl includes
#include <string>
#include <map>


