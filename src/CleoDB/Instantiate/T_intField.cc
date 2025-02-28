// -*- C++ -*-
//
// Package:     CleoDB
// Module:      int
// 
// Description: Instantiate Classes for int
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Simon Patton
// Created:     Sat May 25 14:32:44 EDT 1996
// $Id: T_intField.cc,v 1.9 1998/09/29 19:00:22 cdj Exp $
//
// Revision history
//
// $Log: T_intField.cc,v $
// Revision 1.9  1998/09/29 19:00:22  cdj
// switched to new instantiation macro
//
// Revision 1.8  1998/07/28 20:44:04  mkl
// bug flag for dereferencing ops for built-in types
//
// Revision 1.7  1998/06/24 21:03:06  cdj
// C++ standard does not allow template specialization and explicit
// instantiation using the same template arguments (cxx 6.0 enforces this)
//
// Revision 1.6  1997/12/09 01:12:16  mkl
// Extractor --> extract
//
// Revision 1.5  1997/12/05 04:15:34  mkl
// moved DH to FA for FrameAccess
//
// Revision 1.4  1997/09/01 15:35:27  sjp
// Changed report include to be in Experiment
//
// Revision 1.3  1997/08/22 18:12:24  sjp
// Added output message
//
// Revision 1.2  1997/08/14 16:33:53  sjp
// Mods to run under CW Pro 1
//

#include "Experiment/Experiment.h"
#define DEREF_OP_FOR_BUILTIN_TYPES_BUG

// user include files
#include "Experiment/report.h" // for warning report

#include "FrameAccess/instantiate_macros.h" 
INSTANTIATE_ONE( int ) 

#if defined(THIS_WILL_NEVER_BE_DEFINED)
// Standard does not allow both template specialization and explicit 
//  instantiation to be done with the same template arguments.
// If we really need to do the specialization that is begin attempted
//  below, then we need a way to turn off instantiations within
//  FrameAccess/instantiate_one.h

// the following stops the standard extract for being instantiated

#include "FrameAccess/extract.h"
#include "DataHandler/Record.h"
#include "FrameAccess/FAItem.h"

#if (defined(INCLUDE_TEMPLATE_DEFINITIONS) && defined(AUTO_INSTANTIATION_WITH_TEMPLATE_AS_ARGS_BUG))
inline
#endif /*INCLUDE_TEMPLATE_DEFINITIONS && AUTO_INSTANTIATION_WITH_TEMPLATE_AS_ARGS_BUG */
#if !defined(NO_IMPLICIT_RESOLUTION_FOR_GLOBAL_TEMPLATE_FUNCTION_BUG)
void extract( const Record& ,
		FAItem< int >& )
{
   report( WARNING ,
	   "CleoDB.intField" )
	      << "extract of FAItem< int > requires label!"
	      << endl ;
}
#endif /* NO_IMPLICIT_RESOLUTION_FOR_GLOBAL_TEMPLATE_FUNCTION_BUG */

#endif /* THIS_WILL_NEVER_BE_DEFINED */

//

#include "FrameAccess/instantiate_one.h"
