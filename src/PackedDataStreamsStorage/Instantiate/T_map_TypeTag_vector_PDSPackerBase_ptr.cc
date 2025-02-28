// -*- C++ -*-
//
// Package:     <package>
// Module:      T_map_TypeTag_vector_PDSPackerBase_ptr
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon Oct  2 13:19:34 EDT 2000
// $Id: T_map_TypeTag_vector_PDSPackerBase_ptr.cc,v 1.1 2000/10/02 20:46:56 cdj Exp $
//
// Revision history
//
// $Log: T_map_TypeTag_vector_PDSPackerBase_ptr.cc,v $
// Revision 1.1  2000/10/02 20:46:56  cdj
// now compiles and links using cxx
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
//#include <set>
#include <map>
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
#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
class PDSPackerBase;
#include "STLUtility/fwd_vector.h"

typedef TypeTag _map_key_;
typedef STL_VECTOR(PDSPackerBase*) _map_contents_;
typedef less<_map_key_> _map_compare_;

#include "STLUtility/instantiate_map.h"
