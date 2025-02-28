#if !defined(JOBCONTROL_BLANKRECORDCOMMAND_H)
#define JOBCONTROL_BLANKRECORDCOMMAND_H
// -*- C++ -*-
//
// Package:     Jobcontrol
// Module:      BlankRecordCommand
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Chris D. Jones
// Created:     Sun Mar 29 17:33:38 EST 1998
// $Id: BlankRecordCommand.h,v 1.4 2003/10/20 20:43:57 vk Exp $
//
// Revision history
//
// $Log: BlankRecordCommand.h,v $
// Revision 1.4  2003/10/20 20:43:57  vk
// Modify emptysource to accept optional time parameter. Example: emptysource one vk 113000 10 -time 22222 physics. Time value can  be any positive number (UInt64).
//
// Revision 1.3  1998/12/02 20:01:23  cdj
// added the 'manyTime' subcommand
//
// Revision 1.2  1998/11/09 19:33:24  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.1  1998/04/01 19:43:18  mkl
// added Chris' BlankRecordDelivery handling
//

// system include files

// user include files
#include "CommandPattern/Command.h"

// forward declarations
class StreamSet;
class SyncValue;
class BlankRecordModule;

class BlankRecordCommand : public Command
{
      // friend classes and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      BlankRecordCommand( const Command::Name& iName, 
			  BlankRecordModule* target );
      virtual ~BlankRecordCommand();

      // member functions
      virtual int execute( int argc, char* argv[] );  // executer

      // const member functions

      // static member functions

   protected:
      // protected member functions
      virtual int helpHandler  ();
      virtual int defaultTimeSourceHandler();
      virtual int oneTimeSourceHandler();
      virtual int manyTimeSourceHandler();

      // protected const member functions

   private:
      // Constructors and destructor
      BlankRecordCommand( const BlankRecordCommand& );

      // assignment operator(s)
      const BlankRecordCommand& operator=( const BlankRecordCommand& );

      // private member functions

      // private const member functions
      void parseStreams( StreamSet& readStreams, int index ) const;
      DABoolean parseSyncValue( SyncValue& oSyncValue, int iIndex,
                                DABoolean readTime=false ) const;
      DABoolean parseLong( long& oValue, int index ) const;

      // data members

      // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "Jobcontrol/Template/BlankRecordCommand.cc"
//#endif

#endif /* JOBCONTROL_BLANKRECORDCOMMAND_H */
