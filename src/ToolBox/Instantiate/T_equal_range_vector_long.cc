// -*- C++ -*-
//
// Package:     ToolBox
// Module:      T_equal_range_vector_long
// 
// Description: instantiate equal_range(vector<long>::iterator,...);
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Wed Jul 12 16:05:08 EDT 2000
// $Id: T_equal_range_vector_long.cc,v 1.1 2000/07/12 20:42:08 cdj Exp $
//
// Revision history
//
// $Log: T_equal_range_vector_long.cc,v $
// Revision 1.1  2000/07/12 20:42:08  cdj
// added T_equal_range_vector...cc files needed by new Lattice implementation
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "STLUtility/fwd_vector.h"

// STL classes
#include <vector>

//
// instantiate
//

typedef long _equal_range_value_type_; 
typedef STL_VECTOR(_equal_range_value_type_)::iterator _equal_range_iterator_ ;
#include "STLUtility/instantiate_equal_range.h"

