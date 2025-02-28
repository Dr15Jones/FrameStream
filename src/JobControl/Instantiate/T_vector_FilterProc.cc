// -*- C++ -*-
//
// Package:     <package>
// Module:      T_vector_FilterProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri Sep  5 10:40:05 EDT 2003
// $Id: T_vector_FilterProc.cc,v 1.1 2003/09/19 21:26:50 cdj Exp $
//
// Revision history
//
// $Log: T_vector_FilterProc.cc,v $
// Revision 1.1  2003/09/19 21:26:50  cdj
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
#include "JobControl/FilterProc.h"

typedef JobControlNS::Holder<JobControlNS::FilterProc> _vector_contents_;
#include "STLUtility/instantiate_vector.h"
