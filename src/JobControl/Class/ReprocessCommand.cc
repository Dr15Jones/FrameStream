// -*- C++ -*-
//
// Package:     JobControl
// Module:      ReprocessCommand
// 
//   See HelpMessage below for description!
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Mon May 5 15:52:59 EST 1997
// $Id: ReprocessCommand.cc,v 1.21 2003/09/19 21:11:36 cdj Exp $
//
// Revision history
//
// $Log: ReprocessCommand.cc,v $
// Revision 1.21  2003/09/19 21:11:36  cdj
// disabled the command for now, will probably remove later
//
// Revision 1.20  2000/10/11 19:45:02  mkl
// turn error code from JobControl::eventLoop into interpreter return code
//
// Revision 1.19  2000/06/01 17:48:44  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.18  1999/06/04 18:05:47  mkl
// fix up processStop() function to allow skimming
//
// Revision 1.17  1999/02/22 23:41:38  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.16  1998/07/28 15:53:16  mkl
// ripple effect: needed to include set
//
// Revision 1.15  1998/01/23 05:10:11  mkl
// reprocess requires clearing transient proxies
//
// Revision 1.14  1997/10/07 19:25:20  mkl
// cout --> report( INFO ) and kFacilityString update
//
// Revision 1.13  1997/09/10 01:52:33  mkl
// replaced \n by end
//
// Revision 1.12  1997/09/05 02:36:02  mkl
// tried to unify error handling with tcl way
//
// Revision 1.11  1997/09/03 05:57:47  mkl
// moved from 'const string kFacilityString' to 'static const char* const'
//
// Revision 1.10  1997/09/03 02:38:48  mkl
// restructuring suez libraries
//
// Revision 1.9  1997/08/22 04:21:52  mkl
// standardize error messages from commands
//
// Revision 1.8  1997/08/13 07:10:47  mkl
// Chains of Sources, new activation of streams, and ProxyDict
//
// Revision 1.7  1997/07/11 06:55:40  mkl
// // New <Package>/<File>.h structure
// // Modified so can also compile under cxx v5.5
//
// Revision 1.6  1997/07/02 02:49:01  mkl
// and a few fixes to make g++ happy again
//
// Revision 1.5  1997/07/02 01:40:34  mkl
// fixes to allow CXX version 5.4
//
// Revision 1.4  1997/06/06 06:18:16  mkl
// handle --> execute and other minor stuff
//
// Revision 1.3  1997/06/04 05:23:52  mkl
// misc
//
// Revision 1.2  1997/06/03 18:41:21  mkl
// changed over to kFacilityString
//
// Revision 1.1  1997/05/06 18:35:53  mkl
// added GotoCommand and ReprocessCommand
//
//

#include "Experiment/Experiment.h"
// system include files

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <set>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "JobControl/ReprocessCommand.h"
#include "CommandPattern/Module.h"
#include "JobControl/JobControl.h"
#include "Experiment/report.h"
#include "DataDelivery/FrameDeliverer.h"

// STL classes
#include <vector>
#include <set>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "JobControl.ReprocessCommand";

const string helpMessage = 
string( "                                                        \n" )+
string( "// Description: Reprocess Command                       \n" )+
string( "//              \"reprocess\" reprocesses current stop. \n" )+
string( "//                                                      \n" )+
string( "//   Please be aware that results of a reprocess command\n" )+
string( "//      are NOT written to storage media!               \n" );

//
// static data member definitions
//

//
// constructors and destructor
//
//ReprocessCommand::ReprocessCommand()
//{
//}
ReprocessCommand::ReprocessCommand( const Command::Name& iCommand, 
			  Module* iTarget )
   : Command( iCommand, iTarget )
{
}

// ReprocessCommand::ReprocessCommand( const ReprocessCommand& )
// {
// }

ReprocessCommand::~ReprocessCommand()
{
}

//
// assignment operators
//
// const ReprocessCommand& ReprocessCommand::operator=( const ReprocessCommand& )
// {
// }

//
// member functions
//
int
ReprocessCommand::execute( int argc, char* argv[] )
{
   int result = COMMAND_OK;
/*

   JobControl* jobControl = (JobControl*)target();

   // expect one or two arguments: "Reprocess" or "Reprocess help"
   setArgs( argc, argv );
   if( 1 == argc )
   {
      // force reconfigure of proxies, then process stop again
      jobControl->frameDeliverer().reconfigureCurrentStop(); 
      DABoolean oShallSinkIt = true;
      DABoolean returnStatus = jobControl->processStop( oShallSinkIt );
      result = (true==returnStatus)?COMMAND_OK:COMMAND_ERROR;
      // oShallSinkIt ignored; no sinking done
      // give warning that no sinking is done for "reprocess" command?
   } else
   if( 2 == argc ) 
   {
      if ( 0 == strcmp( argv[1], "help" ) )
      {
	 result = helpHandler();
      } 
      else { // bad command argument!
	 report( SYSTEM, kFacilityString ) << "invalid command arg" << endl;
	 helpHandler();
	 result = COMMAND_ERROR;
      }
   }
   else // number of arguments 
   {
      report( SYSTEM, kFacilityString ) << "wrong # args" << endl;
      helpHandler();
      result = COMMAND_ERROR;
   }

   */
   return result;
}

int
ReprocessCommand::helpHandler()
{
   // print help from header
   report( SYSTEM, kFacilityString ) << "\n" << helpMessage << endl;

   return COMMAND_OK;
}

//
// const member functions
//

//
// static member functions
//
