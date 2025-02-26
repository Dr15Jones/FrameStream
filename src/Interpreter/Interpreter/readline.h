#if !defined(INTERPRETER_READLINE_C_H)
#define INTERPRETER_READLINE_C_H
// -*- C++ -*-
//
// Package:     <Interpreter>
// Module:      readline
// 
// Description: c interface to gnu readline
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Wed Mar 25 14:43:15 EST 1998
// $Id: readline.h,v 1.5 1999/04/19 18:02:22 mkl Exp $
//
// Revision history
//
// $Log: readline.h,v $
// Revision 1.5  1999/04/19 18:02:22  mkl
// added info on tcl via web pages
//
// Revision 1.4  1998/05/20 01:59:13  mkl
// fixed memory leak in history expansion
//
// Revision 1.3  1998/05/07 21:42:28  mkl
// clean up of code changes for history mechism
//
// Revision 1.2  1998/05/07 15:34:14  mkl
// implement history mechanism; implement proper tcl_source command
//
// Revision 1.1  1998/03/26 20:01:17  mkl
// added gnu readline support
//

// system include files

// user include files

// forward declarations

#if defined(__cplusplus)
extern "C"
{
#endif

void  readline_init( const char* iInputRcName = "" );
char* readline_readline( const char* iPrompt );
void  readline_using_history();
void  readline_read_history( const char* file );
void  readline_write_history( const char* file );
void  readline_history_truncate_file( const char* file, unsigned int nLines );
void  readline_print_history_list();
void  readline_add_history( const char* iLine );
char* readline_history_expand( const char* iLine );
void  readline_register_command  ( const char* iCommand ); 
void  readline_deregister_command( const char* iCommand ); 
void  readline_delete_line( const char* iLine );

#if defined(__cplusplus)
}
#endif


#endif /* INTERPRETER_READLINE_H */
