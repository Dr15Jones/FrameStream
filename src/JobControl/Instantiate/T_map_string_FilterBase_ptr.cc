// -*- C++ -*-
//
// Package:     <package>
// Module:      T_map_string_FilterBase_ptr
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri Sep  5 11:24:04 EDT 2003
// $Id: T_map_string_FilterBase_ptr.cc,v 1.1 2003/09/19 21:26:49 cdj Exp $
//
// Revision history
//
// $Log: T_map_string_FilterBase_ptr.cc,v $
// Revision 1.1  2003/09/19 21:26:49  cdj
// first submission of Path code
//

#include "Experiment/Experiment.h"

// system include files
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
//#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>

// user include files
//#include "Experiment/report.h"

namespace JobControlNS
{
   class FilterBase;
}

typedef string _map_key_;
typedef JobControlNS::FilterBase* _map_contents_;
typedef less< string > _map_compare_;

#include "STLUtility/instantiate_map.h"
