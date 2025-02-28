// -*- C++ -*-
//
// Package:     <package>
// Module:      T_set_PDSTypeToUnpackingInfoMap
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Thu May 31 15:07:11 EDT 2001
// $Id: T_set_PDSTypeToUnpackingInfoMap.cc,v 1.1 2001/05/31 19:44:36 cdj Exp $
//
// Revision history
//
// $Log: T_set_PDSTypeToUnpackingInfoMap.cc,v $
// Revision 1.1  2001/05/31 19:44:36  cdj
// changes needed for chaining now work on OSF
//

#include "Experiment/Experiment.h"

// system include files
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

// user include files
//#include "Experiment/report.h"


//
// constants, enums and typedefs
//
class PDSTypeToUnpackingInfoMap;
typedef PDSTypeToUnpackingInfoMap* _set_contents_;
typedef less<_set_contents_> _set_compare_;
#include "STLUtility/instantiate_set.h"
