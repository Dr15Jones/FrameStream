#if !defined(COMMANDPATTERN_MULTILOADERCOMMAND_CC)
#define COMMANDPATTERN_MULTILOADERCOMMAND_CC
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      ModuleCommand
// 
//   See HelpMessage below for description and LoaderCommand for more info
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Valentine Kouznetsov
// Created:     Tue Mar  4 09:43:21 EST 2003
// $Id: MultiLoaderCommand.cc,v 1.2 2003/08/13 15:11:31 vk Exp $
//
// Revision history
//
// $Log: MultiLoaderCommand.cc,v $
// Revision 1.2  2003/08/13 15:11:31  vk
// Change help output to be consistence with request, e.g. prod help will Example for producers.
//
// Revision 1.1  2003/03/12 21:34:09  vk
// Redesign loader class into LoaderBase, Loader (single loader) and MultiLoader
//
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
#include "CommandPattern/MultiLoaderCommand.h"
#include "CommandPattern/Interpreter.h"

// STL classes
#include <vector>

//
// constants, enums and typedefs
//
FILESCOPE_IN_TEMPLATE_CC_BUG const char* const kMultiLoaderCommandString 
= "CommandPattern.MultiLoaderCommand";

//
// static data member definitions
//

//
// constructors and destructor
//
template< class T >
MultiLoaderCommand< T >::MultiLoaderCommand( const Command::Name& commandName,  
                                   T* target,
                                   DABoolean iInternalCommand )
   : LoaderCommand<T>( commandName, target, iInternalCommand )
{
}

// template< class T >
// MultiLoaderCommand< T >::MultiLoaderCommand( const MultiLoaderCommand& )
// {
// }

template< class T >
MultiLoaderCommand< T >::~MultiLoaderCommand()
{
}

//
// assignment operators
//
// template< class T >
// const MultiLoaderCommand& MultiLoaderCommand< T >::operator=( const MultiLoaderCommand& )
// {
// }

//
// member functions
//
template< class T >
int
MultiLoaderCommand< T >::execute( int argc, char* argv[] )
{
    int returnValue = Command::COMMAND_OK;

    this->setArgs( argc, argv );
    if ( 2 <= argc ) 
    {
       if ( 0 == strcmp( argv[1], "help" ) ) 
       {
	  returnValue = this->helpHandler();
       } else 
       if ( 0 == strcmp( argv[1], "list" ) ) 
       {
	  returnValue = this->listHandler();
       } else 
       if ( 0 == strcmp( argv[1], "ls" ) ) 
       {
	  returnValue = this->listHandler();
       } else 
       if ( 0 == strcmp( argv[1], "listsel" ) ) 
       {
	  returnValue = this->listSelectedHandler();
       } else 
       if ( 0 == strcmp( argv[1], "lss" ) ) 
       {
	  returnValue = this->listSelectedHandler();
       } else 
       if ( 0 == strcmp( argv[1], "select" ) ) 
       {
	  returnValue = this->loadHandler();
       } else
       if ( 0 == strcmp( argv[1], "sel" ) ) 
       {
	  returnValue = this->loadHandler();
       } else
       if ( 0 == strcmp( argv[1], "deselect" ) ) 
       {
	  returnValue = this->unloadHandler();
       } else
       if ( 0 == strcmp( argv[1], "desel" ) ) 
       {
	  returnValue = this->unloadHandler();
       } else
       if ( 0 == strcmp( argv[1], "clear" ) ) 
       {
	  returnValue = this->clearHandler();
       } else
       if ( 0 == strcmp( argv[1], "interact" ) ) 
       {
	  returnValue = this->interactHandler();
       } else
       if ( 0 == strcmp( argv[1], "inter" ) ) 
       {
	  returnValue = this->interactHandler();
       }
       else
       {
	  string result( "ERROR: invalid command arg" );
	  this->setResult( result );
	  this->helpHandler();
	  returnValue = Command::COMMAND_ERROR;
       }
    }
    else
    {
       string result( "ERROR: wrong # args" );
       this->setResult( result );
       helpHandler();
       returnValue = Command::COMMAND_ERROR;
    }
    

    return returnValue;
}

template< class T >
int
MultiLoaderCommand< T >::helpHandler()
{
   static const string helpMessage = 
      string( "                                                                      \n" )+
      string( " Description:                                                         \n" )+
      string( "      " ) + this->name() +
      string( " command.                                                             \n" )+
      string( "                                                                      \n" )+
      string( "      Valid subcommands are:                                          \n" )+
      string( "                                                                      \n" )+
      string( "  " ) + this->name() +
      string( " help                                            see this help page   \n" )+
      string( "  " ) + this->name() +
      string( " list                                            List available mods  \n" )+
      string( "  " ) + this->name() +
      string( " ls                                              Synonym: \"list\"    \n" )+
      string( "  " ) + this->name() +
      string( " listsel                                         List selected mods   \n" )+
      string( "  " ) + this->name() +
      string( " lss                                             Synonym: \"listsel\" \n" )+
      string( "  " ) + this->name() +
      string( " select   <mod1> [<mod2>..]                      Select mods          \n" )+
      string( "       select   <mod1> [<mod2>..] production <tag>     with production tag\n" )+
      string( "                                                       New name: <mod>@<tag>\n" )+
      string( "  " ) + this->name() +
      string( " sel      <mod1> [<mod2>..]                      Synonym: \"select\"  \n" )+
      string( "       sel      <mod1> [<mod2>..] production <tag>                    \n" )+
      string( "                                                                      \n" )+
      string( "  " ) + this->name() +
      string( " deselect <mod1> [<mod2>..]                      Deselect mods        \n" )+
      string( "  " ) + this->name() +
      string( " desel    <mod1> [<mod2>..]                      Synonym: \"deselect\"\n" )+
      string( "  " ) + this->name() +
      string( " clear                                           Empty the mod list   \n" )+
      string( "                                                                      \n" )+
      string( "  " ) + this->name() +
      string( " interact <mod>                                  interact w/ mod      \n" )+
      string( "  " ) + this->name() +
      string( " inter    <mod>                                  Synonym: \"interact\"\n");

   static string helpMessageExample;
   if(this->name()=="proc") {
      helpMessageExample = 
      string( "                                                                      \n" )+
      string( "  Example: \n" )+
      string( "  proc sel MyProc YourProc production com                             \n" )+
      string( "  proc lss\n" )+
      string( "    MyProc@com : <full_path_to_shared_MyProc>/libMyProc.so            \n" )+
      string( "    YourProc@com : <full_path_to_shared_YourProc>/libYourProc.so      \n" )+
      string( "  proc desel MyProc@com                                               \n" )+
      string( "                                                                      \n" );
  } else if(this->name()=="prod") {
      helpMessageExample =
      string( "                                                                      \n" )+
      string( "  Example: \n" )+
      string( "  prod sel MyProd YourProd production com                             \n" )+
      string( "  prod lss\n" )+
      string( "    MyProd@com : <full_path_to_shared_MyProd>/libMyProd.so            \n" )+
      string( "    YourProd@com : <full_path_to_shared_YourProd>/libYourProd.so      \n" )+
      string( "  prod desel MyProd@com                                               \n" )+
      string( "                                                                      \n" );
  } else {
      helpMessageExample =
      string( "                                                                      \n");
  }

   report( INFO, kMultiLoaderCommandString ) << "\n" 
      << helpMessage << helpMessageExample << endl;
   return Command::COMMAND_OK;
}

template< class T >
int
MultiLoaderCommand< T >::loadHandler()
{
   int returnValue = Command::COMMAND_OK;

   if( this->m_argc <= 2 )
   {
      //report( ERROR, kMultiLoaderCommandString ) << "wrong # args" << endl;
      string result( "ERROR: wrong # arguments" );
      this->setResult( result );

      return returnValue = Command::COMMAND_ERROR;
   }
   // correct number of args

   const char* arg;
   int index = 3;

   // loop over all supplied names and check for "production" keyword
   string tag="";
   while ( 0 != ( arg = this->getArgument( index ) ) ) {
     string name{ arg };

     if( name=="production" ) {
     // special keyword to load multiple times same object
       const char* inst;
       int ii = index+1;

       if( 0 != ( inst = this->getArgument( ii ) ) ) {
         tag = string(inst);

         break;
       } 
     }
     index++;
   }

   index = 2;
   while ( 0 != ( arg = this->getArgument( index++ ) ) )
   {
     string name{ arg };
      
      // if found "production" tag keyword stop looping
      if(name=="production") break; 
      
      DABoolean res=false;
      if(tag.size()) {
        res = target()->load( name, tag );
      } else {
        res = target()->load( name );
      }

      if( res ) 
      {
	 returnValue = Command::COMMAND_OK;
      }
      else 
      {
	 //report( ERROR, kMultiLoaderCommandString )
	 //  << "Cannot load " << name << "." << endl;
	 string result( "ERROR: cannot load " );
	 result += name + ".";
	 this->setResult( result );
	 returnValue = Command::COMMAND_ERROR;
      }
   }

   return returnValue;
}

template< class T >
T*
MultiLoaderCommand< T >::target()
{
   return (T*)Command::target();
}

//
// const member functions
//
template< class T >
const T*
MultiLoaderCommand< T >::target() const
{
   return (const T*)Command::target();
}

//
// static member functions
//


#endif /*COMMANDPATTERN_MULTILOADERCOMMAND_CC*/
