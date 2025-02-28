// -*- C++ -*-
//
// Package:     <package>
// Module:      T_map_StreamType_DataKeySet
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon Oct  2 13:46:26 EDT 2000
// $Id: T_map_StreamType_DataKeySet.cc,v 1.1 2000/10/02 20:46:54 cdj Exp $
//
// Revision history
//
// $Log: T_map_StreamType_DataKeySet.cc,v $
// Revision 1.1  2000/10/02 20:46:54  cdj
// now compiles and links using cxx
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "DataHandler/StreamType.h"
#include "PackedDataStreamsStorage/PDSDataToStore.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "package.T_map_StreamType_DataKeySet" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: T_map_StreamType_DataKeySet.cc,v 1.1 2000/10/02 20:46:54 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

typedef StreamType _map_key_;
typedef DataKeySet _map_contents_;
typedef less<StreamType> _map_compare_;

#include "STLUtility/instantiate_map.h"
