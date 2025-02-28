// -*- C++ -*-
//
// Package:     <Modname>
// Module:      ModnameInternalCommand
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      John Doe
// Created:     day-mon-xx
// RCS(Id)
//
// Revision history
//
// RCS(Log)
//

#include "Experiment/Experiment.h"

// system include files
#include <assert.h>

// user include files
#include "Experiment/report.h"
#include "Modname/ModnameInternalCommand.h"
#include "Modname/Modname.h"
#include "CommandPattern/Conversion.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "Modname.ModnameInternalCommand" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: internalcommand.cc,v 1.9 2000/12/04 19:11:08 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
ModnameInternalCommand::ModnameInternalCommand( const Command::Name& iName, 
						Modname* target )
   : Command( iName, target, true ) // "false" to make it external command
{
   // The arguments are: 
   // 1.) command name (what you will type at the Suez command line)
   // 2.) minimum number of arguments expected
   // 3.) maxiumu number of arguments expected
   // 4.) pointer to a member function which will handle the subcommand
   // 5.) the "this" pointer to point to this command object.
   addSubcommand( 
      new Subcommand< ModnameInternalCommand >(
         "help", 2, 2,
         &ModnameInternalCommand::helpHandler,
         this )
      );
   addSubcommand( 
      new Subcommand< ModnameInternalCommand >(
         "print", 3, 3,
         &ModnameInternalCommand::printHandler,
         this )
      );
}

// ModnameInternalCommand::ModnameInternalCommand( 
//      const ModnameInternalCommand& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

ModnameInternalCommand::~ModnameInternalCommand()
{
}

//
// assignment operators
//
// const ModnameInternalCommand& ModnameInternalCommand::operator=( 
//       const ModnameInternalCommand& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }

//
// member functions
//
// ---------------------------------------------------------------------
// This is one way of doing subcommand handling; but it's easier to 
// use the "Subcommand" class, as shown in an example above in the ctor.
//int
//int
//ModnameInternalCommand::execute( int argc, char* argv[] )
//{
//   int result = COMMAND_OK;
//
//   // expect two arguments: "print" or "help"
//   setArgs( argc, argv );
//   if( 2 == argc )
//   {
//      if( 0 == strcmp( argv[1], "help" ) )
//      {
//         result = helpHandler();
//      } else
//      if( 0 == strcmp( argv[1], "do" ) )
//      {
//	 result = doHandler();
//      }
//      else { // bad command argument!
//         report( SYSTEM, kFacilityString ) << "invalid command arg" << endl;
//	 helpHandler();
//         result = COMMAND_ERROR;
//      }
//   }
//   else // number of arguments
//   {
//      report( SYSTEM, kFacilityString ) << "wrong # args" << endl;
//      helpHandler();
//      result = COMMAND_ERROR;
//   }
//
//   return result;
//}

int
ModnameInternalCommand::helpHandler()
{
   int returnValue = COMMAND_OK;

   // print help from header
   static const string helpMessage =
      string( " calls Modname.\n" )+
      string( "                    \n" )+
      string( " Subcommands are:   \n" )+
      string( "    help            \n" )+
      string( "    print <number>  \n" );

   report( SYSTEM, kFacilityString )
      << "\n\nDescription: " << name() << "\n\n"
      << helpMessage
      << endl;

   return returnValue;
}

int
ModnameInternalCommand::printHandler()
{
   int returnValue = COMMAND_OK;

   // to get access to arguments use: 
   // unsigned int m_argc; --> number of arguments including the main command:
   // Suez> arg0 arg1 arg2 ...
   // char* m_argv[]; --> actual argument
   assert( m_argc == 3 );

   // to do conversion to a number:
   DABoolean isNumber;
   int number = Conversion::stringToDigit( m_argv[2], isNumber );
   if( true == isNumber )
   {
      target()->printNumber( number );
   }
   else
   {
      report( SYSTEM, kFacilityString ) << "bad numerical value" << endl;
      returnValue = COMMAND_ERROR;
   }

   return returnValue;
}

Modname*
ModnameInternalCommand::target()
{
   return (Modname*)Command::target();
}

//
// const member functions
//
const Modname*
ModnameInternalCommand::target() const
{
   return (const Modname*)Command::target();
}

//
// static member functions
//
