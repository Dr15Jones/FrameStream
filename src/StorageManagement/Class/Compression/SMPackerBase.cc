// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      SMPackerBase
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Thu Aug 15 12:53:31 EDT 2002
// $Id: SMPackerBase.cc,v 1.1 2002/08/15 18:08:21 cleo3 Exp $
//
// Revision history
//
// $Log: SMPackerBase.cc,v $
// Revision 1.1  2002/08/15 18:08:21  cleo3
// added missing virtual destructor to SMPackerBase
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
#include "StorageManagement/Compression/SMPackerBase.h"


//
// constants, enums and typedefs
//

static const char* const kFacilityString = "StorageManagement.SMPackerBase" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: SMPackerBase.cc,v 1.1 2002/08/15 18:08:21 cleo3 Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//

SMPackerBase::~SMPackerBase()
{
}
