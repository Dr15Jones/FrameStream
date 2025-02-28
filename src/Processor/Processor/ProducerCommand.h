#if !defined(PROCESSOR_PRODUCERCOMMAND_H)
#define PROCESSOR_PRODUCERCOMMAND_H
// -*- C++ -*-
//
// Package:     Processor
// Module:      ProducerCommand
// 
// Description: Command executer for the \"producer\" command
//              that talks with (Master)producer.
//
//              See ProducerCommand.cc for description of available 
//              subcommands.
//
// Environment:
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Thu Jan 15 13:05:19 EST 1998
// $Id: ProducerCommand.h,v 1.3 2003/03/14 20:10:45 vk Exp $
//
// Revision history
//
// $Log: ProducerCommand.h,v $
// Revision 1.3  2003/03/14 20:10:45  vk
// Adjust Processor classes wrt to Loader/MultiLoader
//
// Revision 1.2  1998/11/10 03:52:36  mkl
// unify producer/processor/module/source_format/sink_format commands
//
// Revision 1.1  1998/11/09 19:34:48  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.1  1998/01/16 23:34:33  mkl
// added MasterProducer for selecting Producers at run time
//
//


// system include files

// user include files
#include "CommandPattern/MultiLoaderCommand.h"
#include "Processor/MasterProducer.h"

// forward declarations

class ProducerCommand : public MultiLoaderCommand< MasterProducer >
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      ProducerCommand( const Name& name, MasterProducer* target );
      virtual ~ProducerCommand();

      // member functions
      virtual int execute( int argc, char* argv[] );  // executer

      // const member functions

      // static member functions

   protected:
      // protected member functions
      virtual int helpHandler();
      virtual int reorderHandler();

      // protected const member functions

   private:
      // Constructors and destructor
      ProducerCommand( const ProducerCommand& );

      // assignment operator(s)
      const ProducerCommand& operator=( const ProducerCommand& );

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

#endif /* PROCESSOR_PRODUCERCOMMAND_H */
