#if !defined(COMMANDPATTERN_LOADERCOMMAND_CC)
#define COMMANDPATTERN_LOADERCOMMAND_CC
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      ModuleCommand
// 
//   See HelpMessage below for description!
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Mon Nov 9 12:37:14 EST 1998
// $Id: LoaderCommand.cc,v 1.12 2003/09/19 20:38:59 cdj Exp $
//
// Revision history
//
// $Log: LoaderCommand.cc,v $
// Revision 1.12  2003/09/19 20:38:59  cdj
// report problems to Tcl
//
// Revision 1.11  2002/08/16 14:15:21  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.10  2002/01/03 20:17:04  cdj
// code clean up from last check in
//
// Revision 1.9  2002/01/03 19:58:29  cdj
// fixed bugs in Tcl command handling
//
// Revision 1.8  1999/05/12 20:36:34  mkl
// change Error to all uppercase
//
// Revision 1.7  1999/04/30 18:16:57  mkl
// prettyfying Loader output; setting resultString for interpreter
//
// Revision 1.6  1999/02/22 23:40:54  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.5  1998/12/02 06:03:00  mkl
// towards interacting with Source- and SinkFormats
//
// Revision 1.4  1998/11/12 02:23:57  mkl
// minor cleanup
//
// Revision 1.3  1998/11/10 23:48:48  mkl
// make Solaris CC happy: FILESCOPE_blabla bug
//
// Revision 1.2  1998/11/10 19:55:45  mkl
// more comprehensible error messages
//
// Revision 1.1  1998/11/10 03:54:03  mkl
// unify producer/processor/module/source_format/sink_format commands
//
//

#include "Experiment/Experiment.h"
// system include files
#include "C++Std/iostream.h"
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "CommandPattern/LoaderCommand.h"
#include "CommandPattern/Interpreter.h"

// STL classes
#include <vector>
#include <cstring>

//
// constants, enums and typedefs
//
FILESCOPE_IN_TEMPLATE_CC_BUG const char* const kLoaderCommandString 
= "CommandPattern.LoaderCommand";

//
// static data member definitions
//

//
// constructors and destructor
//
template< class T >
LoaderCommand< T >::LoaderCommand( const Command::Name& commandName,  
                                   T* target,
                                   DABoolean iInternalCommand )
   : Command( commandName, target, iInternalCommand )
{
}

// template< class T >
// LoaderCommand< T >::LoaderCommand( const LoaderCommand& )
// {
// }

template< class T >
LoaderCommand< T >::~LoaderCommand()
{
}

//
// assignment operators
//
// template< class T >
// const LoaderCommand& LoaderCommand< T >::operator=( const LoaderCommand& )
// {
// }

//
// member functions
//
template< class T >
int
LoaderCommand< T >::execute( int argc, char* argv[] )
{
    int returnValue = COMMAND_OK;

    setArgs( argc, argv );
    if ( 2 <= argc ) 
    {
       if ( 0 == strcmp( argv[1], "help" ) ) 
       {
	  returnValue = helpHandler();
       } else 
       if ( 0 == strcmp( argv[1], "list" ) ) 
       {
	  returnValue = listHandler();
       } else 
       if ( 0 == strcmp( argv[1], "ls" ) ) 
       {
	  returnValue = listHandler();
       } else 
       if ( 0 == strcmp( argv[1], "listsel" ) ) 
       {
	  returnValue = listSelectedHandler();
       } else 
       if ( 0 == strcmp( argv[1], "lss" ) ) 
       {
	  returnValue = listSelectedHandler();
       } else 
       if ( 0 == strcmp( argv[1], "select" ) ) 
       {
	  returnValue = loadHandler();
       } else
       if ( 0 == strcmp( argv[1], "sel" ) ) 
       {
	  returnValue = loadHandler();
       } else
       if ( 0 == strcmp( argv[1], "deselect" ) ) 
       {
	  returnValue = unloadHandler();
       } else
       if ( 0 == strcmp( argv[1], "desel" ) ) 
       {
	  returnValue = unloadHandler();
       } else
       if ( 0 == strcmp( argv[1], "clear" ) ) 
       {
	  returnValue = clearHandler();
       } else
       if ( 0 == strcmp( argv[1], "interact" ) ) 
       {
	  returnValue = interactHandler();
       } else
       if ( 0 == strcmp( argv[1], "inter" ) ) 
       {
	  returnValue = interactHandler();
       }
       else
       {
	  string result( "ERROR: invalid command arg" );
	  setResult( result );
	  helpHandler();
	  returnValue = COMMAND_ERROR;
       }
    }
    else
    {
       string result( "ERROR: wrong # args" );
       setResult( result );
       helpHandler();
       returnValue = COMMAND_ERROR;
    }
    

    return returnValue;
}

template< class T >
int
LoaderCommand< T >::helpHandler()
{
   static const string helpMessage = 
      string( "                                                             \n" )+
      string( "// Description:                                              \n" )+
      string( "//      " ) + name() +
      string( " command.         \n" )+
      string( "//                                                           \n" )+
      string( "//      Valid subcommands are:                               \n" )+
      string( "//                                                           \n" )+
      string( "//  " ) + name() +
      string( " help                         see this help page   \n" )+
      string( "//  " ) + name() +
      string( " list                         List available mods  \n" )+
      string( "//  " ) + name() +
      string( " ls                           Synonym: \"list\"    \n" )+
      string( "//  " ) + name() +
      string( " listsel                      List selected mods   \n" )+
      string( "//  " ) + name() +
      string( " lss                          Synonym: \"listsel\" \n" )+
      string( "//  " ) + name() +
      string( " select   <mod1> [<mod2>..]   Select mods          \n" )+
      string( "//  " ) + name() +
      string( " sel      <mod1> [<mod2>..]   Synonym: \"select\"  \n" )+
      string( "//  " ) + name() +
      string( " deselect <mod1> [<mod2>..]   Deselect mods        \n" )+
      string( "//  " ) + name() +
      string( " desel    <mod1> [<mod2>..]   Synonym: \"deselect\"\n" )+
      string( "//  " ) + name() +
      string( " clear                        Empty the mod list   \n" )+
      string( "//                                                 \n" )+
      string( "//  " ) + name() +
      string( " interact <mod>               interact w/ mod      \n" )+
      string( "//  " ) + name() +
      string( " inter    <mod>               Synonym: \"interact\"\n" )+
      string( "//                                                 \n" ); 


   report( INFO, kLoaderCommandString ) << "\n" << helpMessage << endl;
   return COMMAND_OK;
}

template< class T >
int
LoaderCommand< T >::listHandler()
{
   DABoolean returnValue = COMMAND_OK;

   //ostream& os = report( INFO, kLoaderCommandString );
   string result = target()->listAvailable();
   setResult( result );

   return returnValue;
}

template< class T >
int
LoaderCommand< T >::listSelectedHandler()
{
   DABoolean returnValue = COMMAND_OK;

   //ostream& os = report( INFO, kLoaderCommandString );
   string result = target()->listLoaded();
   setResult( result );

   return returnValue;
}

template< class T >
int
LoaderCommand< T >::loadHandler()
{
   int returnValue = COMMAND_OK;

   if( m_argc <= 2 )
   {
      //report( ERROR, kLoaderCommandString ) << "wrong # args" << endl;
      string result( "ERROR: wrong # arguments" );
      setResult( result );

      return returnValue = COMMAND_ERROR;
   }
   // correct number of args

   const char* arg;
   int index = 2;
   while ( 0 != ( arg = getArgument( index++ ) ) )
   {
      string name( arg );
      
      if( target()->load( name ) ) 
      {
	 returnValue = COMMAND_OK;
      }
      else 
      {
	 //report( ERROR, kLoaderCommandString )
	 //  << "Cannot load " << name << "." << endl;
	 string result( "ERROR: cannot load " );
	 result += name + ".";
	 setResult( result );
	 returnValue = COMMAND_ERROR;
      }
   }

   return returnValue;
}

template< class T >
int
LoaderCommand< T >::unloadHandler()
{
   int returnValue = COMMAND_OK;

   if( m_argc <= 2 )
   {
      //report( ERROR, kLoaderCommandString ) << "wrong # args" << endl;
      string result( "ERROR: wrong # arguments" );
      setResult( result );
      return returnValue = COMMAND_ERROR;
   }
   // correct number of args

   const char* arg;
   int index = 2;
   while ( 0 != ( arg = getArgument( index++ ) ) )
   {
      string name( arg );
      
      if( !target()->unload( name ) ) 
      {
	 //report( ERROR, kLoaderCommandString ) 
	 //  << "Cannot unload " << name << "." << endl;
	 string result( "ERROR: cannot unload " );
	 result += name + ".";
	 setResult( result );
	 returnValue = COMMAND_ERROR;
      }
   }

   return returnValue;
}

template< class T >
int
LoaderCommand< T >::clearHandler()
{
   int returnValue = COMMAND_OK;

   target()->unloadAll();

   return returnValue;
}

template< class T >
int
LoaderCommand< T >::interactHandler()
{
   int returnValue = COMMAND_OK;

   if( m_argc != 3 )
   {
      //report( ERROR, kLoaderCommandString ) << "wrong # args" << endl;
      string result( "ERROR: wrong # arguments" );
      setResult( result );
      return returnValue = COMMAND_ERROR;
   }
   // correct number of args

   string name( getArgument( 2 ) );
   
   Module* module=0;
   
   // find module with that name
   if( 0 != ( module = target()->fetch( name ) ) ) 
   {
      Interpreter::interpreter()->pushActiveModule( module );
      //popActiveModule happens when user types 'exit' or 'quit'
      returnValue = COMMAND_OK;
   } 
   else 
   {
      //report( ERROR, kLoaderCommandString ) 
      // << name << " unknown." << endl;
      string result( "ERROR: " );
      result += name + " unknown.";
      setResult( result );
      returnValue = COMMAND_ERROR;
   }

   return returnValue;
}

template< class T >
T*
LoaderCommand< T >::target()
{
   return (T*)Command::target();
}

//
// const member functions
//
template< class T >
const T*
LoaderCommand< T >::target() const
{
   return (const T*)Command::target();
}

//
// static member functions
//


#endif /*COMMANDPATTERN_LOADERCOMMAND_CC*/
