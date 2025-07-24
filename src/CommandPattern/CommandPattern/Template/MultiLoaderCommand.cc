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
#include <iostream>
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
static const char* const kMultiLoaderCommandString 
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
	  std::string result( "ERROR: invalid command arg" );
	  this->setResult( result );
	  this->helpHandler();
	  returnValue = Command::COMMAND_ERROR;
       }
    }
    else
    {
       std::string result( "ERROR: wrong # args" );
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
   static const std::string helpMessage = 
      std::string( "                                                                      \n" )+
      std::string( " Description:                                                         \n" )+
      std::string( "      " ) + this->name() +
      std::string( " command.                                                             \n" )+
      std::string( "                                                                      \n" )+
      std::string( "      Valid subcommands are:                                          \n" )+
      std::string( "                                                                      \n" )+
      std::string( "  " ) + this->name() +
      std::string( " help                                            see this help page   \n" )+
      std::string( "  " ) + this->name() +
      std::string( " list                                            List available mods  \n" )+
      std::string( "  " ) + this->name() +
      std::string( " ls                                              Synonym: \"list\"    \n" )+
      std::string( "  " ) + this->name() +
      std::string( " listsel                                         List selected mods   \n" )+
      std::string( "  " ) + this->name() +
      std::string( " lss                                             Synonym: \"listsel\" \n" )+
      std::string( "  " ) + this->name() +
      std::string( " select   <mod1> [<mod2>..]                      Select mods          \n" )+
      std::string( "       select   <mod1> [<mod2>..] production <tag>     with production tag\n" )+
      std::string( "                                                       New name: <mod>@<tag>\n" )+
      std::string( "  " ) + this->name() +
      std::string( " sel      <mod1> [<mod2>..]                      Synonym: \"select\"  \n" )+
      std::string( "       sel      <mod1> [<mod2>..] production <tag>                    \n" )+
      std::string( "                                                                      \n" )+
      std::string( "  " ) + this->name() +
      std::string( " deselect <mod1> [<mod2>..]                      Deselect mods        \n" )+
      std::string( "  " ) + this->name() +
      std::string( " desel    <mod1> [<mod2>..]                      Synonym: \"deselect\"\n" )+
      std::string( "  " ) + this->name() +
      std::string( " clear                                           Empty the mod list   \n" )+
      std::string( "                                                                      \n" )+
      std::string( "  " ) + this->name() +
      std::string( " interact <mod>                                  interact w/ mod      \n" )+
      std::string( "  " ) + this->name() +
      std::string( " inter    <mod>                                  Synonym: \"interact\"\n");

   static std::string helpMessageExample;
   if(this->name()=="proc") {
      helpMessageExample = 
      std::string( "                                                                      \n" )+
      std::string( "  Example: \n" )+
      std::string( "  proc sel MyProc YourProc production com                             \n" )+
      std::string( "  proc lss\n" )+
      std::string( "    MyProc@com : <full_path_to_shared_MyProc>/libMyProc.so            \n" )+
      std::string( "    YourProc@com : <full_path_to_shared_YourProc>/libYourProc.so      \n" )+
      std::string( "  proc desel MyProc@com                                               \n" )+
      std::string( "                                                                      \n" );
  } else if(this->name()=="prod") {
      helpMessageExample =
      std::string( "                                                                      \n" )+
      std::string( "  Example: \n" )+
      std::string( "  prod sel MyProd YourProd production com                             \n" )+
      std::string( "  prod lss\n" )+
      std::string( "    MyProd@com : <full_path_to_shared_MyProd>/libMyProd.so            \n" )+
      std::string( "    YourProd@com : <full_path_to_shared_YourProd>/libYourProd.so      \n" )+
      std::string( "  prod desel MyProd@com                                               \n" )+
      std::string( "                                                                      \n" );
  } else {
      helpMessageExample =
      std::string( "                                                                      \n");
  }

   report( INFO, kMultiLoaderCommandString ) << "\n" 
      << helpMessage << helpMessageExample << std::endl;
   return Command::COMMAND_OK;
}

template< class T >
int
MultiLoaderCommand< T >::loadHandler()
{
   int returnValue = Command::COMMAND_OK;

   if( this->m_argc <= 2 )
   {
      //report( ERROR, kMultiLoaderCommandString ) << "wrong # args" << std::endl;
      std::string result( "ERROR: wrong # arguments" );
      this->setResult( result );

      return returnValue = Command::COMMAND_ERROR;
   }
   // correct number of args

   const char* arg;
   int index = 3;

   // loop over all supplied names and check for "production" keyword
   std::string tag="";
   while ( 0 != ( arg = this->getArgument( index ) ) ) {
     std::string name{ arg };

     if( name=="production" ) {
     // special keyword to load multiple times same object
       const char* inst;
       int ii = index+1;

       if( 0 != ( inst = this->getArgument( ii ) ) ) {
         tag = std::string(inst);

         break;
       } 
     }
     index++;
   }

   index = 2;
   while ( 0 != ( arg = this->getArgument( index++ ) ) )
   {
     std::string name{ arg };
      
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
	 //  << "Cannot load " << name << "." << std::endl;
	 std::string result( "ERROR: cannot load " );
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
