// -*- C++ -*-
//
// Package:     ToolBox
// Module:      T_find
// 
// Description: Instantiate find<>() function
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Michael Marsh
// Created:     Wed May 12 09:38:20 EDT 1999
// $Id: T_find.cc,v 1.4 2002/12/05 21:34:36 cleo3 Exp $
//
// Revision history
//
// $Log: T_find.cc,v $
// Revision 1.4  2002/12/05 21:34:36  cleo3
// deal with instantiation bug in g++ 3.2
//
// Revision 1.3  1999/10/30 12:36:47  cleo3
// updated to work with cxx 6.2
//
// Revision 1.2  1999/05/15 17:57:38  marsh
// Added const unsigned int
//
// Revision 1.1  1999/05/12 13:53:24  marsh
// New instantiation file for find<>()
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <algorithm>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"

// STL classes
#include <algorithm>

//
// constants, enums and typedefs
//
#if defined (NEED_TO_BE_IN_NAMESPACE_TO_INSTANTIATE_TEMPLATE_BUG)
#undef STD_PREFIX
#define STD_PREFIX
namespace std {
#endif
template
unsigned int*
STD_PREFIX find(unsigned int*, unsigned int*, const unsigned int&);

template
const unsigned int*
STD_PREFIX find(const unsigned int*, const unsigned int*, const unsigned int&);

template
unsigned short*
STD_PREFIX find(unsigned short*, unsigned short*, const unsigned short&);

template
const unsigned short*
STD_PREFIX find(const unsigned short*, const unsigned short*, const unsigned short&);

template
unsigned short*
STD_PREFIX find(unsigned short*, unsigned short*, const unsigned int&);

#if defined(NEED_TO_BE_IN_NAMESPACE_TO_INSTANTIATE_TEMPLATE_BUG)
}
#endif
