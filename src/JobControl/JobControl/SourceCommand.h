#if !defined(JOBCONTROL_SOURCECOMMAND_H)
#define JOBCONTROL_SOURCECOMMAND_H
// -*- C++ -*-
//
// Package:     JobControl
// Module:      SourceCommand
// 
// Description: Command executer for the "source" command for
//              the SourceManager.
//
//              See SourceCommand.cc for a detailed description.
//
// Environment:
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Tue Jul 22 17:05:19 EST 1997
// $Id: SourceCommand.h,v 1.7 1999/12/11 19:07:38 mkl Exp $
//
// Revision history
//
// $Log: SourceCommand.h,v $
// Revision 1.7  1999/12/11 19:07:38  mkl
// added 'source status' command; use bug flag for linux string compare function problem
//
// Revision 1.6  1999/04/24 16:22:58  mkl
// keep track of DataSourceDescriptors, not just names of files
//
// Revision 1.5  1999/02/22 23:41:48  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.4  1997/09/03 02:39:09  mkl
// restructuring suez libraries
//
// Revision 1.3  1997/08/13 07:11:11  mkl
// Chains of Sources, new activation of streams, and ProxyDict
//
// Revision 1.2  1997/08/08 05:21:30  mkl
// first attempt at chains-of-files
//
// Revision 1.1  1997/07/24 04:59:55  mkl
// adding chains of sources
//
//


// system include files

// user include files
#include "CommandPattern/Command.h"


// forward declarations
class SourceManager;

class SourceCommand : public Command
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      SourceCommand( const Name& name, SourceManager* target );
      virtual ~SourceCommand();

      // member functions
      virtual int execute( int argc, char* argv[] );  // executer

      // const member functions

      // static member functions

   protected:
      // protected member functions
      virtual int helpHandler       ();
      virtual int createTokenHandler();
      virtual int listHandler       ();
      virtual int listTokensHandler ();
      virtual int editHandler       ();
      virtual int removeHandler     ();
      virtual int clearHandler      ();
      virtual int renameTokenHandler();
      virtual int bindHandler       ();
      virtual int useHandler        (); // undocumented feature; for testing only
      virtual int activeHandler     ();
      virtual int clearActiveHandler();
      virtual int statusHandler();

      inline SourceManager& sourceManager();
      
      // protected const member functions
      inline const SourceManager& sourceManager() const;

   private:
      // Constructors and destructor
      SourceCommand( const SourceCommand& );

      // assignment operator(s)
      const SourceCommand& operator=( const SourceCommand& );

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions
inline
SourceManager&
SourceCommand::sourceManager()
{
   return *(SourceManager*)target();
}

inline
const SourceManager&
SourceCommand::sourceManager() const
{
   return *(SourceManager*)target();
}

#endif /* JOBCONTROL_SOURCECOMMAND_H */
