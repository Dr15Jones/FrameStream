// -*- C++ -*-
//
// Package:     ToolBox
// Module:      T_vector_double
// 
// Description: Instantiate a vector< double >
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D. Jones
// Created:     Fri Feb 13 16:27:13 EST 1998
// $Id: T_vector_double.cc,v 1.1 1998/02/15 19:20:12 cdj Exp $
//
// Revision history
//
// $Log: T_vector_double.cc,v $
// Revision 1.1  1998/02/15 19:20:12  cdj
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

typedef double _vector_contents_ ;

#include "STLUtility/instantiate_vector.h"
