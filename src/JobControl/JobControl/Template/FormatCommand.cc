#if !defined(JOBCONTROL_FORMATCOMMAND_CC)
#define JOBCONTROL_FORMATCOMMAND_CC
// -*- C++ -*-
//
// Package:     JobControl
// Module:      FormatCommand
//
//   See HelpMessage below for description!
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Tue Aug 19 23:35:15 EST 1997
// $Id: FormatCommand.cc,v 1.2 1998/11/10 03:52:29 mkl Exp $
//
// Revision history (at end of file)
//

#include "Experiment/Experiment.h"
// system include files

// user include files
#include "Experiment/report.h"
#include "JobControl/FormatCommand.h"

// STL classes

//
// constants, enums and typedefs
//
static const char* const kFormatCommandString 
= "JobControl.FormatCommand";
 
//
// static data member definitions
//

//
// constructors and destructor
//
template< class T >
FormatCommand< T >::FormatCommand( const Command::Name& name,
				   T* target )
   : LoaderCommand< T >( name, target, false )
{
}

// template< class T >
// FormatCommand< T >::FormatCommand( const FormatCommand& )
// {
// }

template< class T >
FormatCommand< T >::~FormatCommand()
{
}

//
// assignment operators
//
// template< class T >
// const FormatCommand& FormatCommand< T >::operator=( const FormatCommand& )
// {
// }

//
// member functions
//
//
// static member functions
//

// -------------------------------------------------------
// Revision history
//
// $Log: FormatCommand.cc,v $
// Revision 1.2  1998/11/10 03:52:29  mkl
// unify producer/processor/module/source_format/sink_format commands
//
// Revision 1.1  1998/11/09 19:33:32  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.3  1998/07/29 02:15:57  mkl
// disallow explicit extension setting for source/sink formats; formats know their extensions
//
// Revision 1.2  1998/07/06 19:57:53  mkl
// simplify factory method; make it safer
//
// Revision 1.1  1998/06/17 18:18:07  mkl
// allow dynamic loading of source and sink formats
//
#endif /* JOBCONTROL_FORMATCOMMAND_CC */
