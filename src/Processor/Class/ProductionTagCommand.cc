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
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "Processor/ProductionTagCommand.h"

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
         << "wrong # args" << endl;
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
         << "too few arguments" << endl;
   }
   else {

   if( 2 < m_argc ) {
      report( SYSTEM, kFacilityString )
	 << "will ignore extra arguments!" << endl;
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
   
   cout << producer()->productionTag().value() << endl;

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
   const string helpMessage = 
      string( "                                                          \n" )+
      string( " Description: " ) + name() + string( "                    \n" )+
      string( "                                                          \n" )+
      string( "  Valid subcommands are:                                  \n" )+
      string( "                                                          \n" )+
      string( "  " ) + name() + string( " help      prints this help page\n" )+
      string( "  " ) + name() + string( " <value>   " ) 
      + name() + string( " = <value>       \n" )+
      string( "  " ) + name() + string( "           list value           \n" )+
      string( "  " ) + name() + string( " def       " )
      + name() + string( " = default       \n" )+
      string( "                                                          \n" );

   // print help
   report( SYSTEM, kFacilityString )
      << "\n" << helpMessage 
      << "\n" << helpString() << endl;
      
   return COMMAND_OK;
}

//
// const member functions
//

//
// static member functions
//
