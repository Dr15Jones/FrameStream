// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      HelpCommand
// 
// Description: <one line class summary>
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:       Martin  Lohner
// Created:     Tue Mar 18 15:52:59 EST 1997
// $Id: HelpCommand.cc,v 1.3 1997/10/27 19:25:45 mkl Exp $
//
// Revision history
//
// $Log: HelpCommand.cc,v $
// Revision 1.3  1997/10/27 19:25:45  mkl
// EchoCommand to echo messages
//
// Revision 1.2  1997/10/07 19:25:32  mkl
// cout --> report( INFO ) and kFacilityString update
//
// Revision 1.1.1.1  1997/09/03 02:39:57  mkl
// imported CommandPattern sources
//
//

#include "Experiment/Experiment.h"
// system include files

// user include files
#include "CommandPattern/HelpCommand.h"
#include "CommandPattern/Module.h"


// STL classes

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "CommandPattern.HelpCommand";

//
// static data member definitions
//

//
// constructors and destructor
//
//HelpCommand::HelpCommand()
//{
//}
HelpCommand::HelpCommand( const Command::Name& iCommand, 
			  Module* iTarget )
   : Command( iCommand, iTarget )
{
}

// HelpCommand::HelpCommand( const HelpCommand& )
// {
// }

HelpCommand::~HelpCommand()
{
}

//
// assignment operators
//
// const HelpCommand& HelpCommand::operator=( const HelpCommand& )
// {
// }

//
// member functions
//
int
HelpCommand::execute( int, char** )
{
   return helpHandler();
}

int
HelpCommand::helpHandler()
{
    target()->help( );
    return COMMAND_OK;
}

//
// const member functions
//

//
// static member functions
//
