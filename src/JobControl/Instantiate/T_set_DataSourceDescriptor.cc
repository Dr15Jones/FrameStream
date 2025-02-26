// -*- C++ -*-
//
// Package:     JobControl
// Module:      T_set_DataSourceDescriptor
// 
// Description: Instantiate set of DataSourceDescriptors
//
//
// Author:      Martin Lohner
// Created:     Fri April 23 12:20:00 EDT 1999
// $Id: T_set_DataSourceDescriptor.cc,v 1.1 1999/04/24 16:22:52 mkl Exp $
//
// Revision history
//
// $Log: T_set_DataSourceDescriptor.cc,v $
// Revision 1.1  1999/04/24 16:22:52  mkl
// keep track of DataSourceDescriptors, not just names of files
//
//
//


#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <set>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "JobControl/CompareDataSourceDescriptors.h"

#include <vector>
#include <set>

typedef DataSourceDescriptor DSD ;
typedef DataSourceDescriptor _set_contents_ ;
typedef CompareDataSourceDescriptors _set_compare_ ;

#include "STLUtility/instantiate_set.h"
