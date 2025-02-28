// -*- C++ -*-
//
// Package:     <Interpreter>
// Module:      Interpreter
// 
// Description: <one line class summary>
//
// Implementation:
//              (based on BaBar/CDF Framework, Liz Sexton-Kennedy)
//
// Author:      Martin Lohner
// Created:     Thu Mar  5 18:13:38 GMT 1998
// $Id: Interpreter.cc,v 1.7 2003/09/05 18:13:51 cdj Exp $
//
// Revision history
//
// $Log: Interpreter.cc,v $
// Revision 1.7  2003/09/05 18:13:51  cdj
// made active module stack size accessible and const
//
// Revision 1.6  2002/01/03 20:17:00  cdj
// code clean up from last check in
//
// Revision 1.5  2002/01/03 19:58:23  cdj
// fixed bugs in Tcl command handling
//
// Revision 1.4  1998/11/09 19:30:58  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.3  1998/09/08 19:12:29  mkl
// removed superfluous const qualifier
//
// Revision 1.2  1998/03/16 14:43:28  mkl
// assert that interpreter has been initialized
//
// Revision 1.1  1998/03/11 19:11:49  mkl
// base class for all interpreters
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>
#include <assert.h>

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "CommandPattern/Interpreter.h"
#include "CommandPattern/Command.h"
#include "CommandPattern/Module.h"

// STL classes
#include <string>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "Interpreter.Interpreter" ;

//
// static data member definitions
//
Interpreter* Interpreter::m_interpreter = 0;

//
// constructors and destructor
//
Interpreter::Interpreter()
   : m_commandPrompt( NULL )
{
  setCommandPrompt("> ");
}

// Interpreter::Interpreter( const Interpreter& iInterpreter )
// {
//    *this = iInterpreter;
// }

Interpreter::~Interpreter()
{
   delete [] m_commandPrompt;
}

//
// assignment operators
//
// const Interpreter& Interpreter::operator=( const Interpreter& iInterpreter )
// {
//   if( this != &iInterpreter ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iInterpreter );
//   }
//
//   return *this;
// }

//
// member functions
//
void 
Interpreter::setCommandPrompt( const char* const iPrompt )
{
   if ( NULL != m_commandPrompt ) {
      delete [] m_commandPrompt;
      m_commandPrompt = NULL;
   }
   if ( NULL != iPrompt ) {
      m_commandPrompt = new char[strlen( iPrompt )+1];
      strcpy( m_commandPrompt, iPrompt );
   }
}

void
Interpreter::pushActiveModule( Module* iModule )
{
   if ( ! m_activeModuleStack.empty() ) {
      m_activeModuleStack.back()->disableCommands();
      string newPrompt( commandPrompt() );
      //the "-2" removes the old "> "
      newPrompt = newPrompt.substr(0,newPrompt.size() - 2) + "." +
        iModule->name() + "> ";
      setCommandPrompt( newPrompt.c_str() );
   } else {
      //no previous Module on the stack
      string newPrompt = iModule->name() + "> ";
      setCommandPrompt( newPrompt.c_str() );
   }
   m_activeModuleStack.push_back( iModule );
   iModule->enableCommands();
}

void
Interpreter::popActiveModule()
{
   Module* deactivate = m_activeModuleStack.back();
   m_activeModuleStack.pop_back();
   deactivate->disableCommands();

   if (m_activeModuleStack.empty() ) {
         setCommandPrompt("> ");
   } else {
      m_activeModuleStack.back()->enableCommands();
      //now reset the prompt
      if ( 1 == m_activeModuleStack.size() ) {
         string newPrompt = m_activeModuleStack.front()->name();
         newPrompt += "> ";
         setCommandPrompt(newPrompt.c_str() );
      } else {
         //3 because of the "." at the front and the "> " at the end
         string newPrompt( commandPrompt());
         newPrompt = newPrompt.substr(0, newPrompt.size() -1*( deactivate->name().size() + 3));
         newPrompt += "> ";
         setCommandPrompt(newPrompt.c_str() );
      }
   }
}


Module*
Interpreter::activeModule()
{
   if ( 0 == m_activeModuleStack.size() ) {
         return 0;
   } 
   return m_activeModuleStack.back();
}

const Module*
Interpreter::activeModule() const
{
   return const_cast<Interpreter*>(this)->activeModule();
}
unsigned int
Interpreter::activeModuleStackSize() const
{
   return m_activeModuleStack.size();
}
//
// const member functions
//
const char*
Interpreter::commandPrompt( ) const
{
   return m_commandPrompt;
}             

//
// static member functions
//
DABoolean 
Interpreter::isInitialized()
{
   return( m_interpreter != 0 );
}     

void
Interpreter::setInterpreter( Interpreter* interp )
{
   m_interpreter = interp;
}

Interpreter* 
Interpreter::interpreter()
{
   assert( 0 != m_interpreter );

   return m_interpreter;
}
