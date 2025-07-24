/* // -*- C++ -*-
//
// Package:     <Interpreter>
// Module:      readline
// 
// Description: c interface to gnu readline
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Wed Mar 25 14:45:14 EST 1998
// $Id: readline_c.c,v 1.1 2003/03/31 21:15:43 cdj Exp $
//
// Revision history
//
// $Log: readline_c.c,v $
// Revision 1.1  2003/03/31 21:15:43  cdj
// made files names more unique to avoid problems on OS X (Darwin)
//
// Revision 1.9  2002/12/10 18:20:55  cdj
// bug fix: no longer get erroneous xalloc out of memory error on OSF when multiple suez jobs trying to use .suez_history file.  No longer write history if this is a batch job OR there is no history to write.
//
// Revision 1.8  1999/04/19 18:02:19  mkl
// added info on tcl via web pages
//
// Revision 1.7  1998/07/18 20:16:46  mkl
// switch to c-style comments in c file
//
// Revision 1.6  1998/06/30 19:54:23  mkl
// fixed bug when using Ctrl-d at command-prompt
//
// Revision 1.5  1998/06/23 23:07:57  mkl
// fix memory leak in cli expansion
//
// Revision 1.4  1998/05/20 01:59:08  mkl
// fixed memory leak in history expansion
//
// Revision 1.3  1998/05/07 21:42:24  mkl
// clean up of code changes for history mechism
//
// Revision 1.2  1998/05/07 15:34:06  mkl
// implement history mechanism; implement proper tcl_source command
//
// Revision 1.1  1998/03/26 20:01:11  mkl
// added gnu readline support
//
// */

/* system include files */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* gnu readline support */
#include <readline/readline.h>
#include <readline/history.h>


/* Generator function for command completion.  STATE lets us know whether
   to start from scratch; without any state (i.e. STATE == 0), then we
   start at the top of the list. */
extern 
char*
command_matches( const char* text, int state );

/* Attempt to complete on the contents of TEXT.  START and END bound the
   region of rl_line_buffer that contains the word to complete.  TEXT is
   the word to complete.  We can use the entire contents of rl_line_buffer
   in case we want to do some simple parsing.  Return the array of matches\
   ,
   or NULL if there aren't any. */
static
char**
command_completion( const char* text, int start, int end )
{
   char **matches;
   
   matches = (char **)NULL;
   
   /* If this word is at the start of the line, then it is a command
      to complete.  Otherwise it is the name of a file in the current
      directory. */
   if( 0 == start ) {
      matches = rl_completion_matches( text, command_matches );
   }

   return( matches );
}


void
readline_init( const char* iInputRcName )
{
  /* Allow conditional parsing of the ~/.inputrc file. */
  rl_readline_name = strdup( iInputRcName );
  
  /* Tell the completer that we want a crack first. */
  rl_attempted_completion_function = command_completion;
}

char*
readline_readline( const char* iPrompt )
{
  return readline( iPrompt );
}

void
readline_using_history()
{
  using_history();
}

void
readline_read_history( const char* file )
{
  read_history( file );
}

void
readline_write_history( const char* file )
{
  write_history( file );
}

void
readline_history_truncate_file( const char* file, unsigned int nLines )
{
  history_truncate_file( file, nLines );
}

void
readline_print_history_list()
{
   int i;
   HIST_ENTRY **the_list = history_list();
   if( the_list != 0 ) {
      for( i = 0; the_list[i]; ++i ) {
	 printf( "%d %s\n", i + history_base, the_list[i]->line );
      }
   }
}

void
readline_add_history( const char* iLine )
{
  add_history( iLine );
}

int
readline_history_length()
{
   return history_length;
}

char*
readline_history_expand( const char* iLine )
{
   char *expansion;
   int result;

   /* protect against expanding null */
   if( 0 == iLine ) return 0;

   result = history_expand( iLine, &expansion);

   if (result < 0 || result == 2) /*  error */
   {
      free (expansion);
      expansion = 0;
   }
   else if( result == 1 ) { /* expansion did take place */
      ;
   }
   else { /* default */
      free (expansion);
      expansion = (char*)iLine;
   }

   return expansion;
}

void 
readline_delete_line( const char* iLine )
{
   free (iLine);
}
