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

#include "FrameAccess/instantiate_macros.h"
INSTANTIATE_ONE( YourItemHere )
//Use the following if 'YourItemHere' contains a ','
// also make sure there are no blank spaces within 'YourItemHere'
/* INSTANTIATE_ONE_1_COMMA( YourItemHere ) */
#include "FrameAccess/instantiate_one.h"

