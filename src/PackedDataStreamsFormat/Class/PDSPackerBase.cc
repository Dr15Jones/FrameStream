// -*- C++ -*-
//
// Package:     <PackedDataStreamsFormat>
// Module:      PDSPackerBase
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon Sep 18 13:13:58 EDT 2000
// $Id: PDSPackerBase.cc,v 1.1.1.1 2000/09/29 17:46:16 cdj Exp $
//
// Revision history
//
// $Log: PDSPackerBase.cc,v $
// Revision 1.1.1.1  2000/09/29 17:46:16  cdj
// imported
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

// user include files
//#include "Experiment/report.h"
#include "PackedDataStreamsFormat/PDSPackerBase.h"

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

static const char* const kFacilityString = "PackedDataStreamsFormat.PDSPackerBase" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: PDSPackerBase.cc,v 1.1.1.1 2000/09/29 17:46:16 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//
SMFixedPacker<unsigned char> 
PDSPackerBase::s_typePacker
=
SMFixedPacker<unsigned char>::createFromMinMaxPrecision( 
   0,
   PDSPacking::kNumberOfTypes - 1,
   1 );

SMFixedPacker<unsigned char> 
PDSPackerBase::s_strategyPacker =
SMFixedPacker<unsigned char>::createFromMinMaxPrecision(
   0, 
   PDSPacking::kNumberOfStrategies - 1 ,
   1);

