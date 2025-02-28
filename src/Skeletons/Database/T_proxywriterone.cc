// -*- C++ -*-
//
// Package:     DBObjects
// Module:      T_DBYourItemHere
// 
// Description: Instantiate Classes for YourItemHere
//
// Implementation:
//     <Notes on implementation>
//
// Author:      John Doe
// Created:     day-mon-xx
// RCS(Id)
//
// Revision history at end of file
//

#include "Experiment/Experiment.h"
// system include files

// user include files
#include "YourLibrary/YourItemHere.h"
#include "DBObjects/Template/DBOneWriter.cc"

// STL classes

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "DBObjects.YourItemHere";

template class DBOneWriter< YourItemHere >;

// ------------------------------------------------------------------
// Revision history
//
// RCS(Log)
//

