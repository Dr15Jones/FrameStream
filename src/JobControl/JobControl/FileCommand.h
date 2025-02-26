#if !defined(JOBCONTROL_FILECOMMAND_H)
#define JOBCONTROL_FILECOMMAND_H
// -*- C++ -*-
//
// Package:     JobControl
// Module:      FileCommand
// 
// Description: Command executer for the "File" command for
//               the standard file module. 
//
//              See FileCommand.cc for a detailed description.
//
// Environment:
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Wed Aug 20 00:05:19 EST 1997
// $Id: FileCommand.h,v 1.4 2001/06/15 21:06:28 cdj Exp $
//
// Revision history
//
// $Log: FileCommand.h,v $
// Revision 1.4  2001/06/15 21:06:28  cdj
// can now specify data (not) to store in a sink
//
// Revision 1.3  1997/09/03 02:38:58  mkl
// restructuring suez libraries
//
// Revision 1.2  1997/08/29 04:22:12  mkl
// simplify JobControl: remove FileInput/Output files, bug flag changes, handling of suffix .gz etc.
//
// Revision 1.1  1997/08/20 06:23:40  mkl
// symmetrized sinks with sources in terms of user interface
//
//


// system include files

// user include files
#include "CommandPattern/Command.h"
#include "DataStorage/StreamToDataStringTagsToStoreMap.h"

// forward declarations
class StreamSet;

class FileCommand : public Command
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      FileCommand( const Name& name, Module* target );
      virtual ~FileCommand();

      // member functions
      virtual int execute( int argc, char* argv[] );  // executer

      // const member functions

      // static member functions

   protected:
      // protected member functions
      virtual int helpHandler  ();
      virtual int sourceHandler();
      virtual int addHandler   ();
      virtual int sinkHandler  ();

      // protected const member functions

   private:
      // Constructors and destructor
      FileCommand( const FileCommand& );

      // assignment operator(s)
      const FileCommand& operator=( const FileCommand& );

      // private member functions

      // private const member functions
      void parseStreams( StreamSet& readStreams, int index ) const;
      void parseStreamsAndData( StreamToDataStringTagsToStoreMap& iMap,
                                int index ) const;

      // data members

      // static data members

};

// inline function definitions

#endif /* JOBCONTROL_FILECOMMAND_H */
