#if !defined(INTERPRETER_PYTHONINTERPRETER_H)
#define INTERPRETER_PYTHONINTERPRETER_H
// -*- C++ -*-
//
// Package:     <Interpreter>
// Module:      PythonInterpreter
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Thu Mar  5 19:10:55 GMT 1998
// $Id: PythonInterpreter.h,v 1.1.1.1 1998/03/11 18:52:18 mkl Exp $
//
// Revision history
//
// $Log: PythonInterpreter.h,v $
// Revision 1.1.1.1  1998/03/11 18:52:18  mkl
// imported Interpreter sources
//

// system include files

// user include files

// forward declarations

class PythonInterpreter
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      PythonInterpreter();
      virtual ~PythonInterpreter();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      PythonInterpreter( const PythonInterpreter& );

      // ---------- assignment operator(s) ---------------------
      const PythonInterpreter& operator=( const PythonInterpreter& );

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "CommandPattern/Template/PythonInterpreter.cc"
//#endif

#endif /* INTERPRETER_PYTHONINTERPRETER_H */
