// -*- C++ -*-
//
// Package:     CleoDB
// Module:      DBTrackerValues
// 
// Description: Instantiate Classes for DBTrackerValues
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Simon Patton
// Created:     Sat May 25 14:32:44 EDT 1996
// $Id: T_DBTrackerValues.cc,v 1.3 2000/03/01 00:39:36 cdj Exp $
//
// Revision history
//
// $Log: T_DBTrackerValues.cc,v $
// Revision 1.3  2000/03/01 00:39:36  cdj
// registered StorageHelper
//
// Revision 1.2  1998/09/29 19:00:16  cdj
// switched to new instantiation macro
//
// Revision 1.1  1997/12/11 07:05:06  mkl
// new addition to instantiate extras for COCandidateMaster which aren't covered by COPion/KaonFitMaster
//
// Revision 1.2  1997/12/05 04:15:31  mkl
// moved DH to FA for FrameAccess
//
// Revision 1.1  1997/09/17 16:16:05  sjp
// New file to instantiate in the composite fit scheme
//
// Revision 1.1  1997/09/10 13:57:28  sjp
// File to handle DBTrackerValues
//

#include "Experiment/Experiment.h"

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <set>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "CleoDB/DBTrackerValues.h"

#include "FrameAccess/instantiate_macros.h" 
INSTANTIATE_ONE( DBTrackerValues ) 

#include "FrameAccess/instantiate_one.h"

#include "CleoDB/DBTrackerValuesStorageHelper.h"
SM_REGISTER_STORAGE(DBTrackerValuesStorageHelper)
