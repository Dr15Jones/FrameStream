#if !defined(COMMANDPATTERN_PARAMETERBASE_H)
#define COMMANDPATTERN_PARAMETERBASE_H
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      ParameterBase
// 
// Description: Base class for all Parameters
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Wed Jan 28 15:54:48 EST 1998
// $Id: ParameterBase.h,v 1.6 2003/02/13 21:03:28 ajm36 Exp $
//
// Revision history
//
// $Log: ParameterBase.h,v $
// Revision 1.6  2003/02/13 21:03:28  ajm36
// parameters now return their value to tcl when they are changed or checked
//
// Revision 1.5  2000/08/04 15:15:10  mkl
// call-back function now returns DABoolean (if false, value gets reset to default)
//
// Revision 1.4  2000/08/03 22:05:26  mkl
// parameters now have optional call-back mechanism
//
// Revision 1.3  2000/01/04 20:53:30  mkl
// now print type with parameter value
//
// Revision 1.2  1998/03/14 01:52:59  mkl
// added default value
//
// Revision 1.1  1998/03/11 19:10:39  mkl
// new Parameter sources
//

// system include files

// user include files
#include "CommandPattern/Command.h"

// forward declarations

class ParameterBase : public Command
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      // parameter change call back
      class ParameterChangeCallBackBase {
	 public:
	    virtual DABoolean operator()() = 0;
      };

      // ---------- Constructors and destructor ----------------
      ParameterBase( const Name& iName, 
		     Module* iTarget );
      virtual ~ParameterBase();

      // ---------- member functions ---------------------------

      // forwarded from CommandPattern/Command
      virtual int execute( int argc, char* argv[] ); // template method
      virtual int helpHandler();

      // register call back for parameter changes
      void setParameterChangeCallBack( ParameterChangeCallBackBase* iCallBack );

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------
      virtual const char* typeName();

   protected:
      // ---------- protected member functions -----------------
      virtual int setHandler();              // used by template execute
      virtual int implementSetHandler() = 0; // call by setHandler
      virtual int setDefaultHandler();              // used by template execute
      virtual int implementSetDefaultHandler() = 0; // call by setHandler
      virtual int listHandler() = 0;         // used by template execute

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      ParameterBase( const ParameterBase& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const ParameterBase& operator=( const ParameterBase& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      ParameterChangeCallBackBase* m_parmChangeCallBack;

      // ---------- static data members ------------------------

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "Parameter/Template/ParameterBase.cc"
//#endif

#endif /* COMMANDPATTERN_PARAMETERBASE_H */
