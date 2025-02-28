// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      T_SMFillContents_double_ptr
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Sun Dec 24 11:12:53 EST 2000
// $Id: T_SMFillContents_double_ptr.cc,v 1.2 2000/12/25 21:11:17 cdj Exp $
//
// Revision history
//
// $Log: T_SMFillContents_double_ptr.cc,v $
// Revision 1.2  2000/12/25 21:11:17  cdj
// the last change now compiles on Solaris
//
// Revision 1.1  2000/12/24 17:03:01  cdj
// added instantiation of SMFillsContents<double*>
//

#include "Experiment/Experiment.h"

// system include files

// user include files
//#include "Experiment/report.h"
#include "STLUtility/iterator_traits_fix.h"
#include "StorageManagement/Template/SMFillContents.cc"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//

template class SMFillContents<double*>;
