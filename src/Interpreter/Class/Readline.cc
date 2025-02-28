// -*- C++ -*-
//
// Package:     <Readline>
// Module:      Readline
// 
// Description: <one line class summary>
//
// Implementation:
//
// Author:      Martin Lohner
// Created:     Wed Mar 25 12:17:23 EST 1998
// $Id: Readline.cc,v 1.7 2002/12/10 18:20:54 cdj Exp $
//
// Revision history
//
// $Log: Readline.cc,v $
// Revision 1.7  2002/12/10 18:20:54  cdj
// bug fix: no longer get erroneous xalloc out of memory error on OSF when multiple suez jobs trying to use .suez_history file.  No longer write history if this is a batch job OR there is no history to write.
//
// Revision 1.6  2001/02/23 01:39:52  cleo3
// protect against trying to delete 0 or NULL
//
// Revision 1.5  1999/04/19 18:02:17  mkl
// added info on tcl via web pages
//
// Revision 1.4  1998/05/20 01:59:07  mkl
// fixed memory leak in history expansion
//
// Revision 1.3  1998/05/07 21:42:23  mkl
// clean up of code changes for history mechism
//
// Revision 1.2  1998/05/07 15:34:05  mkl
// implement history mechanism; implement proper tcl_source command
//
// Revision 1.1  1998/03/26 20:01:09  mkl
// added gnu readline support
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <set>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "Interpreter/Readline.h"

// STL classes
#include <string>
#include <set>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "Readline.Readline" ;

//
// static data member definitions
//
Readline::Commands Readline::s_commands;

//
// constructors and destructor
//
Readline::Readline()
{
}

// Readline::Readline( const Readline& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

Readline::~Readline()
{
}

//
// assignment operators
//
// const Readline& Readline::operator=( const Readline& rhs )
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

void
Readline::init()
{
   readline_init();
}

char*
Readline::readline( const char* iPrompt )
{
   return readline_readline( iPrompt );
}

void
Readline::using_history()
{
   readline_using_history();
}

void
Readline::read_history( const char* file )
{
   readline_read_history( file );
}

void
Readline::write_history( const char* file )
{
   readline_write_history( file );
}

void
Readline::history_truncate_file( const char* file, unsigned int nLines )
{
   readline_history_truncate_file( file, nLines );
}

void
Readline::print_history_list()
{
   readline_print_history_list();
}

void
Readline::addHistory( const char* iLine )
{
   if( iLine && *iLine ) 
   {
      readline_add_history( iLine );
   }
}

int
Readline::history_length()
{
   return readline_history_length();
}

char*
Readline::history_expand( const char* iLine )
{
   int c_expansionFlag;
   char* returnValue = readline_history_expand( iLine );

   return returnValue;
}

void
Readline::registerCommand( const char* iCommand )
{
   commands().insert( iCommand );
}

void
Readline::deregisterCommand( const char* iCommand )
{
   Commands::iterator it = commands().find( iCommand );
   if( it != commands().end() )
   {
      commands().erase( it );
   }
}

void
Readline::deleteLine( const char* iLine )
{
   if( 0 != iLine && NULL != iLine ) { 
      readline_delete_line( iLine );
   }
}

//
// const member functions
//

//
// static member functions
//
Readline::Commands&
Readline::commands()
{
   return s_commands;
}


// ------------------------
// externalized c-functions
// ------------------------

extern "C" {

// Generator function for command completion.  STATE lets us know whether
//   to start from scratch; without any state (i.e. STATE == 0), then we
//   start at the top of the list.
char*
command_matches( char* text, int state )
{
   // convenience
   typedef Readline::Commands Commands;
   const Commands& commands = Readline::commands();

   static Commands::const_iterator index = commands.begin();
   static unsigned int length=0;

   // If this is a new word to complete, initialize now.  This includes
   // saving the length of TEXT for efficiency, and initializing the index
   // variable to 0.
   if( !state ) {
      index  = commands.begin();
      length = strlen( text );
   }

   // Return the next name which partially matches from the command list.
   while( !(index == commands.end() ) )
   {
      const char* name = (*index).c_str(); 
      
      ++index;

      if( 0 == strncmp( name , text, length ) ) {
	 //return (char *)name;
	 return strdup( name );
      }
   }
   
   // If no names matched, then return NULL.
   // IMPORTANT: this is the break condition necessary to get 
   // out of infinite loop!
   return( (char *)NULL );
}

} // extern "C"
