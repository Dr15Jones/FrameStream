// -*- C++ -*-
//
// Package:     <package>
// Module:      T_copy_set_TypeTag
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Sun Nov 24 09:39:35 EST 2002
// $Id: T_copy_set_TypeTag.cc,v 1.2 2003/01/27 20:36:23 cleo3 Exp $
//
// Revision history
//
// $Log: T_copy_set_TypeTag.cc,v $
// Revision 1.2  2003/01/27 20:36:23  cleo3
// make instantiation compile under g++
//
// Revision 1.1  2002/11/24 15:04:57  cdj
// fixed missing symbol on OSF by removing autoinstantiations from PDSProxyStorer.cc to own files
//

#include "Experiment/Experiment.h"

// system include files
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
#include <set>
#include <iterator>
//#include <map>
//#include <algorithm>
//#include <utility>

// user include files
//#include "Experiment/report.h"
#include "DataHandler/DataKeyTags.h"
#include "STLUtility/fwd_set.h"

typedef insert_iterator< STL_SET(TypeTag) > _copy_out_iterator_;
typedef STL_SET( TypeTag )::const_iterator _copy_in_iterator_;

#include "STLUtility/instantiate_copy.h"
