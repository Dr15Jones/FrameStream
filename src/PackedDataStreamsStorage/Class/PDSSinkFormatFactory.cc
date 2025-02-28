// -*- C++ -*-
//
// Package:     <PDSStorage>
// Module:      PDSSinkFormatFactory
// 
// Description: factory to create PDSSinkFormat
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri Sep 22 15:32:53 EDT 2000
// $Id: PDSSinkFormatFactory.cc,v 1.1.1.1 2000/09/29 17:49:41 cdj Exp $
//
// Revision history
//
// $Log: PDSSinkFormatFactory.cc,v $
// Revision 1.1.1.1  2000/09/29 17:49:41  cdj
// imported
//
//

#include "Experiment/Experiment.h"

// system include files

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <set>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "PackedDataStreamsStorage/PDSSinkFormat.h"

// STL classes
#include <set>

//
// constants, enums and typedefs
//

// --------------------------- factory method -------------------
extern "C" {
   SinkFormat* makeSinkFormat( void );
}

SinkFormat* 
makeSinkFormat( void )
{
   return new PDSSinkFormat;
}
// ------------------------ end factory method ------------------
