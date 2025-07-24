// -*- C++ -*-
//
// Package:     <DynamicLoader>
// Module:      T_map_string_DLFactoryBase
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Tue Nov 28 14:32:02 EST 2000
// $Id: T_map_string_DLFactoryBase.cc,v 1.1.1.1 2000/11/30 20:51:31 cdj Exp $
//
// Revision history
//
// $Log: T_map_string_DLFactoryBase.cc,v $
// Revision 1.1.1.1  2000/11/30 20:51:31  cdj
// imported DynamicLoader source
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#include <map>
#include <string>

// user include files
//#include "Experiment/report.h"
//#include "DynamicLoader/DLFactoryBase.h"

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
class DLFactoryBase;

typedef std::string _map_key_;
typedef DLFactoryBase* _map_contents_;
typedef less<string> _map_compare_;

#include "STLUtility/instantiate_map.h"
