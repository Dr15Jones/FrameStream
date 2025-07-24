#if !defined(UTILITY_NOSKIPSTRINGTOKENIZER_H)
#define UTILITY_NOSKIPSTRINGTOKENIZER_H
// -*- C++ -*-
//
// Package:     <Utility>
// Module:      NoSkipStringTokenizer
// 
// Description: Allow easy parsing of strings, given a delimiter; 
//              In different to a StringTokenizer, it doesn't skip past
//              several delimiters, rather produces empty strings:
//              e.g. "a+b++c" --> "a", "b", "", "c".
//              
// Usage: Please read usage in StringTokenizer
//
// Author:      Martin Lohner
// Created:     Thu Nov 18 16:25:42 EDT 1999
// $Id: NoSkipStringTokenizer.h,v 1.2 2000/03/02 16:59:34 mkl Exp $
//
// Revision history (at end of file)
//

// system include files

// user include files
#include "Utility/StringTokenizer.h"

// forward declarations
#include <string>

class NoSkipStringTokenizer : public StringTokenizer
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef StringTokenizer::Tokens Tokens;

      // ---------- Constructors and destructor ----------------
      NoSkipStringTokenizer( const std::string& aString, 
			     char aDelimiter = ' ' );
      virtual ~NoSkipStringTokenizer();

      // ---------- member functions ---------------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      NoSkipStringTokenizer( const NoSkipStringTokenizer& ); // stop default

      // ---------- assignment operator(s) ---------------------
      // stop default
      const NoSkipStringTokenizer& operator=( const NoSkipStringTokenizer& ); 

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------
      
      // ---------- data members -------------------------------

      // ---------- static data members ------------------------
      static Tokens 
      parseString( const std::string& aString, char aDelimiter );
      
};

// inline function definitions

// -------------------------------------------------------------
// Revision history
//
// $Log: NoSkipStringTokenizer.h,v $
// Revision 1.2  2000/03/02 16:59:34  mkl
// new StringTokenizer parse handling
//
// Revision 1.1  1999/11/18 20:02:06  mkl
// go back to previous implementation of StringTokenizer; new NoSkipStringTokenizer uses new implementation
//
//

#endif /* UTILITY_NOSKIPSTRINGTOKENIZER_H */
