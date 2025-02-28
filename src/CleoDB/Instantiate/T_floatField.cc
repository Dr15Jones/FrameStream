// -*- C++ -*-
//
// Package:     CleoDB
// Module:      T_floatField
// 
// Description: Instantiate Classed for float
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Chris D. Jones
// Created:     Tue Aug 19 18:44:40 EDT 1997
// $Id: T_floatField.cc,v 1.10 1998/09/29 19:00:21 cdj Exp $
//
// Revision history
//
// $Log: T_floatField.cc,v $
// Revision 1.10  1998/09/29 19:00:21  cdj
// switched to new instantiation macro
//
// Revision 1.9  1998/07/28 20:44:03  mkl
// bug flag for dereferencing ops for built-in types
//
// Revision 1.8  1998/06/24 21:03:04  cdj
// C++ standard does not allow template specialization and explicit
// instantiation using the same template arguments (cxx 6.0 enforces this)
//
// Revision 1.7  1997/12/09 01:12:15  mkl
// Extractor --> extract
//
// Revision 1.6  1997/12/05 04:15:33  mkl
// moved DH to FA for FrameAccess
//
// Revision 1.5  1997/09/01 15:35:26  sjp
// Changed report include to be in Experiment
//
// Revision 1.4  1997/08/29 14:30:08  sjp
// Added include file
//
// Revision 1.3  1997/08/22 18:13:33  sjp
// Removed extraineous identifiers
//
// Revision 1.2  1997/08/22 18:10:35  sjp
// Added output message
//
// Revision 1.1  1997/08/20 17:13:46  cdj
// First submission
//

#include "Experiment/Experiment.h"
#define DEREF_OP_FOR_BUILTIN_TYPES_BUG

// user include files
#include "Experiment/report.h" // for warning report

#include "FrameAccess/instantiate_macros.h" 
INSTANTIATE_ONE( float ) 

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
		FAItem< float >& )
{
   report( WARNING ,
	   "CleoDB.floatField" )
	      << "extract of FAItem< float > requires label!"
	      << endl ;
}
#endif /* NO_IMPLICIT_RESOLUTION_FOR_GLOBAL_TEMPLATE_FUNCTION_BUG */

#endif /* THIS_WILL_NEVER_BE_DEFINED */

//

#include "FrameAccess/instantiate_one.h"
