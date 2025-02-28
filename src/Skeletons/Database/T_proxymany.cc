// -*- C++ -*-
//
// Package:     DBObjects
// Module:      T_DBYourItemHere
// 
// Description: Instantiate Objy Database Proxy for YourItemHere
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
#include <stdlib.h>  // For 'exit'

// user include files
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// If necessary, change "YourLibrary" to the correct library
#include "YourLibrary/YourItemHere.h"
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#include "DBObjects/Template/DBMany.cc"

// STL classes

// 
// constants, enums and typedefs
//
static const char* const kFacilityString = "DBObjects.DBMany.YourItemHere";

template class DBMany< YourItemHere >;

// --------------------------------------------------------
// Revision history
//
// RCS(Log)
//
