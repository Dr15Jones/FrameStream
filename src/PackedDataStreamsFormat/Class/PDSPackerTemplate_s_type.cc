// -*- C++ -*-
//
// Package:     <PackedDataStreamsFormat>
// Module:      PDSPackerTemplate_s_type
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri Sep 15 20:02:09 EDT 2000
// $Id: PDSPackerTemplate_s_type.cc,v 1.1.1.1 2000/09/29 17:46:16 cdj Exp $
//
// Revision history
//
// $Log: PDSPackerTemplate_s_type.cc,v $
// Revision 1.1.1.1  2000/09/29 17:46:16  cdj
// imported
//

#include "Experiment/Experiment.h"

// system include files

// user include files
//#include "Experiment/report.h"
#include "PackedDataStreamsFormat/PDSPackerTemplate.h"

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

PDSPacking::Types PDSPackerTemplate<char>::s_type = PDSPacking::kCharType;
PDSPacking::Types PDSPackerTemplate<short>::s_type = PDSPacking::kShortType;
PDSPacking::Types PDSPackerTemplate<int>::s_type = PDSPacking::kIntType;
PDSPacking::Types PDSPackerTemplate<long>::s_type = PDSPacking::kLongType;

PDSPacking::Types PDSPackerTemplate<unsigned char>::s_type = PDSPacking::kUCharType;
PDSPacking::Types PDSPackerTemplate<unsigned short>::s_type = PDSPacking::kUShortType;
PDSPacking::Types PDSPackerTemplate<unsigned int>::s_type = PDSPacking::kUIntType;
PDSPacking::Types PDSPackerTemplate<unsigned long>::s_type = PDSPacking::kULongType;

PDSPacking::Types PDSPackerTemplate<float>::s_type = PDSPacking::kFloatType;
PDSPacking::Types PDSPackerTemplate<double>::s_type = PDSPacking::kDoubleType;
//PDSPacking::Types PDSPackerTemplate<bool>::s_type = PDSPacking::kBoolType;



