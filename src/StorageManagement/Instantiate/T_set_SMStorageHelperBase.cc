// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      T_set_SMStorageHelperBase
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon May 17 13:55:27 EDT 1999
// $Id: T_set_SMStorageHelperBase.cc,v 1.1.1.1 1999/09/13 21:21:44 cdj Exp $
//
// Revision history
//
// $Log: T_set_SMStorageHelperBase.cc,v $
// Revision 1.1.1.1  1999/09/13 21:21:44  cdj
// imported package
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <set>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "StorageManagement/SMCompareHelpers.h"

// STL classes
#include <set>

//
// constants, enums and typedefs
//

typedef SMStorageHelperBase* _set_contents_;
typedef SMCompareHelpers _set_compare_;

#include "STLUtility/instantiate_set.h"
