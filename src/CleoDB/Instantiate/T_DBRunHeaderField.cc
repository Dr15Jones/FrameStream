// -*- C++ -*-
//
// Package:     CleoDB
// Module:      DBRunHeader
// 
// Description: Instantiate Classes for DBRunHeader
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Simon Patton
// Created:     Sat May 25 14:32:44 EDT 1996
// $Id: T_DBRunHeaderField.cc,v 1.4 1999/11/04 14:43:18 mkl Exp $
//
// Revision history
//
// $Log: T_DBRunHeaderField.cc,v $
// Revision 1.4  1999/11/04 14:43:18  mkl
// added storage helpers for DBRunHeader and DBEventHeader
//
// Revision 1.3  1998/09/29 19:00:13  cdj
// switched to new instantiation macro
//
// Revision 1.2  1997/12/05 04:15:28  mkl
// moved DH to FA for FrameAccess
//
// Revision 1.1  1997/09/10 13:57:28  sjp
// File to handle DBRunHeader
//

#include "Experiment/Experiment.h"
#include <vector>

// user include files
#include "CleoDB/DBRunHeader.h"

#include "FrameAccess/instantiate_macros.h" 
INSTANTIATE_ONE( DBRunHeader ) 

#include "CleoDB/DBRunHeaderStorageHelper.h"
SM_REGISTER_STORAGE( DBRunHeaderStorageHelper )

#include "FrameAccess/instantiate_one.h"

