// -*- C++ -*-
//
// Package:     package
// Module:      T_proxyname
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
// Revision history
//
// RCS(Log)
//

#include "Experiment/Experiment.h"

// user include files
#include "package/YourItemHere.h"

#include "FrameAccess/FAPtrTable.h"

#include "FrameAccess/instantiate_macros.h"
INSTANTIATE_MANY( YourItemHere )
//Use the following if 'YourItemHere' contains a ','
// also make sure there are no blank spaces within 'YourItemHere'
/* INSTANTIATE_MANY_1_COMMA( YourItemHere ) */

//Uncomment the following if YourItemHere ::Identifier is not
// some type of unsigned integer
//#define INSTANTIATE_FATABLE_MAP
#include "FrameAccess/instantiate_many.h"
