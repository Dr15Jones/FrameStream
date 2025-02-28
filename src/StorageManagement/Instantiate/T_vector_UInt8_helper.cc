// -*- C++ -*-
//
// Package:     <package>
// Module:      T_vector_UInt8_helper
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Konstantin Bukin
// Created:     Wed Oct 18 11:23:59 EDT 2000
// $Id: T_vector_UInt8_helper.cc,v 1.1 2000/11/01 02:21:03 kbukin Exp $
//
// Revision history
//
// $Log: T_vector_UInt8_helper.cc,v $
// Revision 1.1  2000/11/01 02:21:03  kbukin
// added T_vector_UInt8_helper.cc and added SMPtrHolder with it's storage helper
//

#include "Experiment/Experiment.h"

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

#include "STLUtility/fwd_vector.h"

#include <vector>

// user include files

typedef STL_VECTOR( UInt8 ) _container_type_ ;
#include "StorageManagement/instantiate_contents_builtin.h"

