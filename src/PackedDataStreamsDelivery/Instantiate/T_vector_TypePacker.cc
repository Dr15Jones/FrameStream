// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      T_vector_TypePacker
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Thu Apr  4 13:38:23 EST 2002
// $Id: T_vector_TypePacker.cc,v 1.1 2002/04/04 19:13:34 cdj Exp $
//
// Revision history
//
// $Log: T_vector_TypePacker.cc,v $
// Revision 1.1  2002/04/04 19:13:34  cdj
// speed optimization: use SMPackerBase instead of PDSPackerBase when reading back
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
#include "PackedDataStreamsDelivery/PDSTypeUnpackingInfo.h"


//
// constants, enums and typedefs
//
typedef PDSTypeUnpackingInfo::TypePacker _vector_contents_;
#include "STLUtility/instantiate_vector.h"
