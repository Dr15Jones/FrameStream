// -*- C++ -*-
//
// Package:     <Processor>
// Module:      ProductionTagCommand
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri Oct  8 23:12:46 EDT 1999
// $Id: ProductionTagCommand.cc,v 1.2 2000/06/01 17:48:10 mkl Exp $
//
// Revision history
//
// $Log: ProductionTagCommand.cc,v $
// Revision 1.2  2000/06/01 17:48:10  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.1  1999/10/09 21:57:45  cdj
// added production_tag command to Producer
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "Experiment/report.h"
#include "Processor/ProductionTagCommand.h"

// STL classes

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "Processor.ProductionTagCommand" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: ProductionTagCommand.cc,v 1.2 2000/06/01 17:48:10 mkl Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
ProductionTagCommand::ProductionTagCommand( const Command::Name& iName,
					    Producer* iTarget) :
   Command( iName, iTarget)
{

}

// ProductionTagCommand::ProductionTagCommand( const ProductionTagCommand& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

ProductionTagCommand::~ProductionTagCommand()
{
}

//
// assignment operators
//
// const ProductionTagCommand& ProductionTagCommand::operator=( const ProductionTagCommand& rhs )
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
ProductionTagCommand::execute( int argc, char* argv[] )
{
   int result = COMMAND_ERROR;

   setArgs( argc, argv );
   if ( 1 <= argc ) {
      if( 2 == argc && 0 == strcmp( argv[1], "help" ) ) {
         result = helpHandler();
      } else
      if( 2 == argc && 0 == strcmp( argv[1], "def" ) ) {
         result = setDefaultHandler();
      } 
      else {
         if( 1 == argc ) {
            result = listHandler();
         } else
         if( 1 < argc ) {
            result = setHandler();
         }
      }
   } 
   else {
      report( SYSTEM, kFacilityString )
         << "wrong # args" << std::endl;
      result = COMMAND_ERROR;
   }
   
   return result;
}


int
ProductionTagCommand::setHandler()
{
   Command::Result returnValue = Command::COMMAND_OK;
   
   if ( m_argc < 2 ) {
      report( SYSTEM, kFacilityString )
         << "too few arguments" << std::endl;
   }
   else {

   if( 2 < m_argc ) {
      report( SYSTEM, kFacilityString )
	 << "will ignore extra arguments!" << std::endl;
   }
      producer()->setProductionTag( getArgument( 1 )  );

   }

   //echo back new value
   listHandler();

   return returnValue;
}

int
ProductionTagCommand::listHandler()
{
   Command::Result returnValue = Command::COMMAND_OK;
   
   std::cout << producer()->productionTag().value() << std::endl;

   return returnValue;
}


int
ProductionTagCommand::setDefaultHandler()
{
   Command::Result returnValue = Command::COMMAND_OK;
   
   producer()->setProductionTag( producer()->defaultProductionTag() );

   //echo the new value
   listHandler();

   return returnValue;
}

int
ProductionTagCommand::helpHandler()
{
   const std::string helpMessage = 
      std::string( "                                                          \n" )+
      std::string( " Description: " ) + name() + std::string( "                    \n" )+
      std::string( "                                                          \n" )+
      std::string( "  Valid subcommands are:                                  \n" )+
      std::string( "                                                          \n" )+
      std::string( "  " ) + name() + std::string( " help      prints this help page\n" )+
      std::string( "  " ) + name() + std::string( " <value>   " ) 
      + name() + std::string( " = <value>       \n" )+
      std::string( "  " ) + name() + std::string( "           list value           \n" )+
      std::string( "  " ) + name() + std::string( " def       " )
      + name() + std::string( " = default       \n" )+
      std::string( "                                                          \n" );

   // print help
   report( SYSTEM, kFacilityString )
      << "\n" << helpMessage 
      << "\n" << helpString() << std::endl;
      
   return COMMAND_OK;
}

//
// const member functions
//

//
// static member functions
//
