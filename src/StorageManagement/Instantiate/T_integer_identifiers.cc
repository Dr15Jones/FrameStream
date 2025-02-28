// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      T_integer_identifiers
// 
// Description: Instantiate the classes needed to store the Left and Right
//        class Identifiers of a Lattice
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Thu Oct  7 17:05:21 EDT 1999
// $Id: T_integer_identifiers.cc,v 1.3 2000/01/06 22:13:14 cdj Exp $
//
// Revision history
//
// $Log: T_integer_identifiers.cc,v $
// Revision 1.3  2000/01/06 22:13:14  cdj
// made it easier to instantiate templates used by sm_contents_builtin
//
// Revision 1.2  1999/10/18 17:42:19  cdj
// now instantiates a mismatch
//
// Revision 1.1  1999/10/11 22:00:34  cdj
// added Lattice storage code
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#include <iterator>

// user include files
//#include "Experiment/report.h"
#include "STLUtility/fwd_vector.h"

#include <vector>

typedef STL_VECTOR(unsigned int) _container_type_;

#include "StorageManagement/instantiate_contents_builtin.h"

