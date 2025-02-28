// -*- C++ -*-
//
// Package:     <package>
// Module:      T_vector_StreamType
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Sun Oct  1 13:33:06 EDT 2000
// $Id: T_vector_StreamType.cc,v 1.1 2000/10/02 20:42:24 cdj Exp $
//
// Revision history
//
// $Log: T_vector_StreamType.cc,v $
// Revision 1.1  2000/10/02 20:42:24  cdj
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
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "DataHandler/StreamType.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
typedef StreamType _vector_contents_;
#include "STLUtility/instantiate_vector.h"
