// -*- C++ -*-
//
// Package:     ToolBox
// Module:      T_vector_uint
// 
// Description: Instantiate a vector< unsigned int >
//
// Implementation:
//     Call the instantiate_vector.h macro
//
// Author:      Chris D. Jones
// Created:     Mon Feb  9 15:37:38 EST 1998
// $Id: T_vector_uint8.cc,v 1.1 2000/11/01 21:06:55 cdj Exp $
//
// Revision history
//
// $Log: T_vector_uint8.cc,v $
// Revision 1.1  2000/11/01 21:06:55  cdj
// added T_vector_uint8.cc
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

typedef UInt8 _vector_contents_ ;

#include "STLUtility/instantiate_vector.h"
