// -*- C++ -*-
//
// Package:     CleoDB
// Module:      DBEventHeader
// 
// Description: Instantiate Classes for DBEventHeader
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Simon Patton
// Created:     Sat May 25 14:32:44 EDT 1996
// $Id: T_DBEventHeaderField.cc,v 1.11 1999/11/04 14:43:18 mkl Exp $
//
// Revision history
//
// $Log: T_DBEventHeaderField.cc,v $
// Revision 1.11  1999/11/04 14:43:18  mkl
// added storage helpers for DBRunHeader and DBEventHeader
//
// Revision 1.10  1998/09/29 19:00:00  cdj
// switched to new instantiation macro
//
// Revision 1.9  1997/12/09 01:12:12  mkl
// Extractor --> extract
//
// Revision 1.8  1997/12/05 04:15:24  mkl
// moved DH to FA for FrameAccess
//
// Revision 1.7  1997/08/06 18:06:55  sjp
// Converted to use instantiation include files
//
// Revision 1.6  1997/07/09 18:02:03  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.5  1997/06/03 17:34:19  sjp
// Modified to instantiate DataFieldextract
//
// Revision 1.4  1997/05/12 15:32:44  sjp
// Modified to handle extracts with Labels
//
// Revision 1.3  1997/04/21 20:49:08  sjp
// Cleaned up to run with CW10
//
// Revision 1.2  1997/04/20 18:37:52  sjp
// Renamed DD handling classes to FA classes
//
// Revision 1.1  1997/04/14 19:54:38  sjp
// New file to instantiate classes for DBEventHeader
//

#include "Experiment/Experiment.h"
#include <vector>

// user include files
#include "CleoDB/DBEventHeader.h"

#include "FrameAccess/instantiate_macros.h"
INSTANTIATE_ONE( DBEventHeader )

#include "CleoDB/DBEventHeaderStorageHelper.h"
SM_REGISTER_STORAGE(DBEventHeaderStorageHelper)

#include "FrameAccess/instantiate_one.h"
