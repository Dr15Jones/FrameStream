// -*- C++ -*-
//
// Package:     <BinaryDelivery>
// Module:      BinarySourceFormatFactory
// 
// Description: factory function to create BinarySourceFormat
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Mon Nov 16 18:23:05 EDT 1998
// $Id: BinarySourceFormatFactory.cc,v 1.1 1998/11/16 16:51:23 mkl Exp $
//
// Revision history
//
// $Log: BinarySourceFormatFactory.cc,v $
// Revision 1.1  1998/11/16 16:51:23  mkl
// additions necessary to load BinarySourceFormat and chain binary files
//
//

#include "Experiment/Experiment.h"

// system include files

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <set>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "BinaryDelivery/BinarySourceFormat.h"

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
   return new BinarySourceFormat;
}
// ------------------------ end factory method ------------------
