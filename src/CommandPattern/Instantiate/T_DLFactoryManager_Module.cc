// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      T_DLFactoryManager_Module
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Tue Nov 28 08:58:28 EST 2000
// $Id: T_DLFactoryManager_Module.cc,v 1.1 2000/12/01 20:23:28 cdj Exp $
//
// Revision history
//
// $Log: T_DLFactoryManager_Module.cc,v $
// Revision 1.1  2000/12/01 20:23:28  cdj
// now uses DynamicLoader package
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "CommandPattern/Module.h"
#include "DynamicLoader/DLFactoryManager.h"

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
#include "DynamicLoader/Template/DLFactoryManager.cc"
template class DLFactoryManager<Module>;
