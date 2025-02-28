#if !defined(JOBCONTROL_FORMATCOMMAND_H)
#define JOBCONTROL_FORMATCOMMAND_H
// -*- C++ -*-
//
// Package:     JobControl
// Module:      FormatCommand
// 
// Description: Command executer for the "Format" command
//
//              See FormatCommand.cc for a detailed description.
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Fri June 12 17:05:19 EST 1998
// $Id: FormatCommand.h,v 1.4 1998/11/10 03:52:27 mkl Exp $$
//
// Revision history
//
// $Log: FormatCommand.h,v $
// Revision 1.4  1998/11/10 03:52:27  mkl
// unify producer/processor/module/source_format/sink_format commands
//
// Revision 1.3  1998/11/09 19:33:25  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.2  1998/07/29 02:16:00  mkl
// disallow explicit extension setting for source/sink formats; formats know their extensions
//
// Revision 1.1  1998/06/17 18:18:21  mkl
// allow dynamic loading of source and sink formats
//
//

// system include files

// user include files
#include "CommandPattern/LoaderCommand.h"

// forward declarations

template< class T >
class FormatCommand : public LoaderCommand< T >
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      FormatCommand( const Command::Name& name, 
		     T* target );
      virtual ~FormatCommand();

      // member functions

      // const member functions

      // static member functions

   protected:
      // protected member functions

   private:
      // Constructors and destructor
      FormatCommand( const FormatCommand& );

      // assignment operator(s)
      const FormatCommand& operator=( const FormatCommand& );

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

// Uncomment the following lines, if your class is templated
// and has an implementation file (in the Template directory)
#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
# include "JobControl/Template/FormatCommand.cc"
#endif                                

#endif /* JOBCONTROL_FORMATCOMMAND_H */
