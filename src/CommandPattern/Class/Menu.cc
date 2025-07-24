// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      Menu
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Wed Mar 11 12:30:02 EST 1998
// $Id: Menu.cc,v 1.7 2003/09/05 18:14:04 cdj Exp $
//
// Revision history
//
// $Log: Menu.cc,v $
// Revision 1.7  2003/09/05 18:14:04  cdj
// fixed problem when call a menu without an argument from the param command
//
// Revision 1.6  1999/02/04 23:06:01  mkl
// fixed up Menu and Parameter commands to work together
//
// Revision 1.5  1998/03/28 20:16:10  mkl
// do implicit bind of Parameter/Command to Module
//
// Revision 1.4  1998/03/28 18:12:39  mkl
// forward protected Module::bind
//
// Revision 1.3  1998/03/23 23:32:59  mkl
// first implementation of Menu
//
// Revision 1.2  1998/03/16 23:17:42  mkl
// use bind instead of commands().push_back()
//
// Revision 1.1  1998/03/14 01:52:55  mkl
// added default value
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>
#include <assert.h>
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "CommandPattern/Menu.h"
#include "CommandPattern/Module.h"
#include "CommandPattern/Interpreter.h"

// STL classes
#include <vector>
#include <cstring>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "CommandPattern.Menu" ;

static const std::string helpMessage = 
std::string( "                                                            \n" )+
std::string( "// Description: Menu                                        \n" )+
std::string( "                                                            \n" )+
std::string( "    <menu> help                   prints this help          \n" )+
std::string( "    <menu>                        enters menu               \n" )+
std::string( "    <menu> ls                     list parameters in menu   \n" )+
std::string( "    <menu> <parm> [<value> ...]   access parms w/o entering \n" )+
std::string( "                                                            \n" );

//
// static data member definitions
//

//
// constructors and destructor
//
Menu::Menu( const Command::Name& iName, Module* iTarget )
   : Command( iName, iTarget ),
     Module ( iName, "Menu" )
{
}

// Menu::Menu( const Menu& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

Menu::~Menu()
{
}

//
// assignment operators
//
// const Menu& Menu::operator=( const Menu& rhs )
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
int
Menu::execute( int argc, char* argv[] )
{
   int result = COMMAND_OK;

   setArgs( argc, argv );         

   if( 1 == argc )
   {
      menuInterHandler();
   } else
   if( 2 <= argc )
   {
      if ( 0 == strcmp( argv[1], "help" ) )
      {
	 result = helpHandler();
      } else
      if ( 0 == strcmp( argv[1], "ls" ) )
      {
	 result = listParmsHandler();
      }
      else
      {
         result = menuHandler();
      }
   }
   else // number of arguments
   {
      report( ERROR, kFacilityString ) << "wrong # args" << std::endl;
      helpHandler();
      result = COMMAND_ERROR;
   }
   
   return result;
}

int
Menu::helpHandler()
{
   // print help from header
   report( INFO, kFacilityString ) << "\n" << helpMessage << std::endl;

   return COMMAND_OK;
}

/*
void
Menu::exit()
{
   disableCommands();
   target()->enableCommands( );

   // reset prompt to old
   Interpreter* interp = Interpreter::interpreter();
   interp->setCommandPrompt( m_parentPrompt.c_str() );
}
*/

int 
Menu::menuInterHandler()
{
   //target()->disableCommands( );
   //enableCommands( );

   // save original prompt
   Interpreter* interp = Interpreter::interpreter();
   interp->pushActiveModule(this);
   //Interpreter::Name savedName = interp->commandPrompt();
   //m_parentPrompt = interp->commandPrompt();
   
   // set new prompt
   //string newPrompt = target()->name() + "." + Module::name() + "> ";
   //interp->setCommandPrompt( newPrompt.c_str() );

   return COMMAND_OK;
}

int 
Menu::menuHandler()
{
   //target()->disableCommands( );
   //enableCommands( );

   Interpreter::interpreter()->pushActiveModule(this);
   // pass in arguments with index+1
   int returnValue = Interpreter::interpreter()->runCommand( m_argc-1, &m_argv[1] );
   Interpreter::interpreter()->popActiveModule();
   //disableCommands();
   //target()->enableCommands();

   return returnValue;
}

int 
Menu::listParmsHandler()
{
   Interpreter::interpreter()->pushActiveModule(this);
   //target()->disableCommands( );
   //enableCommands( );

   // pass in arguments with index+2
   Interpreter::interpreter()->runCommand( "help" );
   
   Interpreter::interpreter()->popActiveModule();
   //disableCommands();
   //target()->enableCommands();

   return COMMAND_OK;
}

//
// const member functions
//

//
// static member functions
//
