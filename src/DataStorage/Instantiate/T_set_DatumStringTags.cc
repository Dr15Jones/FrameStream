// -*- C++ -*-
//
// Package:     <package>
// Module:      T_set_DatumStringTags
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri Jun 15 15:29:07 EDT 2001
// $Id: T_set_DatumStringTags.cc,v 1.1 2001/06/15 21:05:18 cdj Exp $
//
// Revision history
//
// $Log: T_set_DatumStringTags.cc,v $
// Revision 1.1  2001/06/15 21:05:18  cdj
// can now specify data (not) to store in a sink
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
#include "DataStorage/DataStringTagsToStore.h"


//
// constants, enums and typedefs
//

typedef DataStringTagsToStore::DatumStringTags _set_contents_;
typedef less<_set_contents_> _set_compare_;
#include "STLUtility/instantiate_set.h"

