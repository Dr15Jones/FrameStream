// -*- C++ -*-
//
// Package:     <package>
// Module:      T_vector_int_helper
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri May  5 14:48:06 EDT 2000
// $Id: T_vector_int_helper.cc,v 1.1 2000/05/05 20:05:36 cdj Exp $
//
// Revision history
//
// $Log: T_vector_int_helper.cc,v $
// Revision 1.1  2000/05/05 20:05:36  cdj
// added T_vector_int_helper.cc needed by MCInfo
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

#include "STLUtility/fwd_vector.h"

#include <vector>

// user include files

typedef STL_VECTOR( int ) _container_type_ ;
#include "StorageManagement/instantiate_contents_builtin.h"

