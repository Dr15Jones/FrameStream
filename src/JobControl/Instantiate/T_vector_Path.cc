// -*- C++ -*-
//
// Package:     <package>
// Module:      T_vector_Path
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri Sep  5 10:40:05 EDT 2003
// $Id: T_vector_Path.cc,v 1.1 2003/09/19 21:26:51 cdj Exp $
//
// Revision history
//
// $Log: T_vector_Path.cc,v $
// Revision 1.1  2003/09/19 21:26:51  cdj
// first submission of Path code
//

#include "Experiment/Experiment.h"

// system include files
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

// user include files
//#include "Experiment/report.h"
namespace JobControlNS {
   class Path;
}

typedef JobControlNS::Path* _vector_contents_;
#include "STLUtility/instantiate_vector.h"
