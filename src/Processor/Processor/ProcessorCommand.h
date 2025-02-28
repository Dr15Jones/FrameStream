#if !defined(PROCESSOR_PROCESSORCOMMAND_H)
#define PROCESSOR_PROCESSORCOMMAND_H
// -*- C++ -*-
//
// Package:     Processor
// Module:      ProcessorCommand
// 
// Description: Command executer for the \"processor\" command
//              that talks with (Master)processor.
//
//              See ProcessorCommand.cc for description of available 
//              subcommands.
//
// Environment:
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Wed Mar 19 13:05:19 EST 1997
// $Id: ProcessorCommand.h,v 1.3 2003/03/14 20:10:45 vk Exp $
//
// Revision history
//
// $Log: ProcessorCommand.h,v $
// Revision 1.3  2003/03/14 20:10:45  vk
// Adjust Processor classes wrt to Loader/MultiLoader
//
// Revision 1.2  1998/11/10 03:52:36  mkl
// unify producer/processor/module/source_format/sink_format commands
//
// Revision 1.1  1998/11/09 19:34:47  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.6  1997/09/03 02:39:05  mkl
// restructuring suez libraries
//
// Revision 1.5  1997/07/11 06:55:53  mkl
// // New <Package>/<File>.h structure
// // Modified so can also compile under cxx v5.5
//
// Revision 1.4  1997/06/06 06:18:30  mkl
// handle --> execute and other minor stuff
//
// Revision 1.3  1997/05/15 17:40:54  mkl
// MasterProcessor now contains a SharedObjectHandler. Added "processor
// reorder" command.
//
// Revision 1.2  1997/05/14 17:14:25  mkl
// added capability to load/unload shared objects.
//
// Revision 1.1  1997/03/27 06:53:53  mkl
// imported sources.
//


// system include files

// user include files
#include "CommandPattern/MultiLoaderCommand.h"
#include "Processor/MasterProcessor.h"

// forward declarations

class ProcessorCommand : public MultiLoaderCommand< MasterProcessor >
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      ProcessorCommand( const Name& name, MasterProcessor* target );
      virtual ~ProcessorCommand();

      // member functions
      virtual int execute( int argc, char* argv[] );  // executer

      // const member functions

      // static member functions

   protected:
      // protected member functions
      virtual int helpHandler        ();
      virtual int reorderHandler();

      // protected const member functions

   private:
      // Constructors and destructor
      ProcessorCommand( const ProcessorCommand& );

      // assignment operator(s)
      const ProcessorCommand& operator=( const ProcessorCommand& );

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

#endif /* PROCESSOR_PROCESSORCOMMAND_H */
