// -*- C++ -*-
//
// Package:     <package>
// Module:      T_vector_ui_insert
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Sun Nov 24 09:40:21 EST 2002
// $Id: T_vector_ui_insert.cc,v 1.2 2003/01/27 20:36:24 cleo3 Exp $
//
// Revision history
//
// $Log: T_vector_ui_insert.cc,v $
// Revision 1.2  2003/01/27 20:36:24  cleo3
// make instantiation compile under g++
//
// Revision 1.1  2002/11/24 15:04:58  cdj
// fixed missing symbol on OSF by removing autoinstantiations from PDSProxyStorer.cc to own files
//

#include "Experiment/Experiment.h"

// system include files
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

// user include files
//#include "Experiment/report.h"
#include <vector>

#if defined(NO_IMPLICIT_INSTANTIATION)
#if !defined(NO_STL_TEMPLATED_MEMBER_FUNCTIONS_BUG)
template void std::vector<unsigned int>::insert(unsigned int*, unsigned int*, unsigned int*);
#endif
#endif
