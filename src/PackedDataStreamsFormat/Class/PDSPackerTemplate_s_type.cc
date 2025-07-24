// -*- C++ -*-
//
// Package:     <PackedDataStreamsFormat>
// Module:      smpackertemplate::type_s_type
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri Sep 15 20:02:09 EDT 2000
// $Id: smpackertemplate::type_s_type.cc,v 1.1.1.1 2000/09/29 17:46:16 cdj Exp $
//
// Revision history
//
// $Log: smpackertemplate::type_s_type.cc,v $
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

template<> PDSPacking::Types smpackertemplate::type<char>() { return PDSPacking::kCharType;}
template<> PDSPacking::Types smpackertemplate::type<short>() {return PDSPacking::kShortType; }
template<> PDSPacking::Types smpackertemplate::type<int>() { return PDSPacking::kIntType; }
template<> PDSPacking::Types smpackertemplate::type<long>() { return PDSPacking::kLongType; }

template<> PDSPacking::Types smpackertemplate::type<unsigned char>() { return PDSPacking::kUCharType; }
template<> PDSPacking::Types smpackertemplate::type<unsigned short>() { return PDSPacking::kUShortType; }
template<> PDSPacking::Types smpackertemplate::type<unsigned int>() { return PDSPacking::kUIntType; }
template<> PDSPacking::Types smpackertemplate::type<unsigned long>() { return PDSPacking::kULongType; }

template<> PDSPacking::Types smpackertemplate::type<float>() { return PDSPacking::kFloatType; }
template<> PDSPacking::Types smpackertemplate::type<double>() { return PDSPacking::kDoubleType; }
//PDSPacking::Types smpackertemplate::type<bool>() { return PDSPacking::kBoolType;



