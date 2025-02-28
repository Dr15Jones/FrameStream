// -*- C++ -*-
//
// Package:     <PDSDelivery>
// Module:      PDSSourceFormatFactory
// 
// Description: factory function to create PDSSourceFormat
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon Sep 25 15:38:37 EDT 2000
// $Id: PDSSourceFormatFactory.cc,v 1.1.1.1 2000/09/29 17:48:06 cdj Exp $
//
// Revision history
//
// $Log: PDSSourceFormatFactory.cc,v $
// Revision 1.1.1.1  2000/09/29 17:48:06  cdj
// imported
//
//

#include "Experiment/Experiment.h"

// system include files

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <set>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "PackedDataStreamsDelivery/PDSSourceFormat.h"

// STL classes
#include <set>

//
// constants, enums and typedefs
//

// --------------------------- factory method -------------------
extern "C" { 
   SourceFormat* makeSourceFormat( void ); 
}

SourceFormat* 
makeSourceFormat( void )
{
   return new PDSSourceFormat;
}
// ------------------------ end factory method ------------------
