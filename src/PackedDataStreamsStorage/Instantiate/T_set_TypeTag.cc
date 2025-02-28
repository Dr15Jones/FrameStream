// -*- C++ -*-
//
// Package:     <package>
// Module:      T_set_TypeTag
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon Oct  2 11:34:31 EDT 2000
// $Id: T_set_TypeTag.cc,v 1.1 2000/10/02 20:46:58 cdj Exp $
//
// Revision history
//
// $Log: T_set_TypeTag.cc,v $
// Revision 1.1  2000/10/02 20:46:58  cdj
// now compiles and links using cxx
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "DataHandler/DataKey.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
typedef TypeTag _set_contents_;
typedef less<TypeTag> _set_compare_;

#include "STLUtility/instantiate_set.h"
