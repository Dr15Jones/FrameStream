// -*- C++ -*-
//
// Package:     ToolBox
// Module:      T_vector_ptr_to_vector_long
// 
// Description: Instantiate a vector< vector<long>* >
//
// Implementation:
//     Call the instantiate_vector.h macro
//
// Author:      Chris D. Jones
// Created:     Mon Feb  9 15:37:38 EST 1998
// $Id: T_vector_ptr_to_vector_long.cc,v 1.1 2002/05/28 20:13:31 bkh Exp $
//
// Revision history
//
// $Log: T_vector_ptr_to_vector_long.cc,v $
// Revision 1.1  2002/05/28 20:13:31  bkh
// Add vector instantiations of ptrs to vectors of integer types
//
// Revision 1.1  1998/02/09 20:42:49  cdj
// First submission
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"

// STL classes
#include <vector>

//
// constants, enums and typedefs
//

typedef vector<long>* _vector_contents_ ;

#include "STLUtility/instantiate_vector.h"
