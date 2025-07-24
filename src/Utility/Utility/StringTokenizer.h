#if !defined(UTILITY_STRINGTOKENIZER_H)
#define UTILITY_STRINGTOKENIZER_H
// -*- C++ -*-
//
// Package:     <Utility>
// Module:      StringTokenizer
// 
// Description: Allow easy parsing of strings, given a delimiter
//              
// Usage:
//
//   StringTokenizer myString( "hello how are you" );
//   while( myString.hasMoreElements() ) {
//      cout << myString.nextElement() << std::endl;
//   }
//
//   will print: hello
//               how
//               are
//               you
//
//   StringTokenizer myString( "hello how are you", 'l' );
//   while( myString.hasMoreElements() ) {
//      cout << myString.nextElement() << std::endl;
//   }
//
//   will print: he
//               o how are you
//
// Author:      Martin Lohner
// Created:     Sat Aug 22 16:25:42 EDT 1998
// $Id: StringTokenizer.h,v 1.5 2000/03/02 16:59:35 mkl Exp $
//
// Revision history (at end of file)
//

// system include files
#include <string>
#include <deque>

// user include files

// forward declarations

class StringTokenizer
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef std::deque< std::string > Tokens;
      typedef Tokens (*ParsingFunction)( const std::string& aString,
					 char aDelimiter );

      // ---------- Constructors and destructor ----------------
      StringTokenizer( const std::string& aString, 
		       char aDelimiter = ' ',
		       ParsingFunction iParsingFunction=
		       &StringTokenizer::parseString );
      virtual ~StringTokenizer();

      // ---------- member functions ---------------------------
      std::string nextElement();

      // ---------- const member functions ---------------------
      DABoolean hasMoreElements() const;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      Tokens& tokens() { return m_tokens; }

      // ---------- protected const member functions -----------
      const Tokens& tokens() const { return m_tokens; }

   private:
      // ---------- Constructors and destructor ----------------
      StringTokenizer( const StringTokenizer& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const StringTokenizer& operator=( const StringTokenizer& ); // stop default
      
      // ---------- private member functions -------------------
      
      // ---------- private const member functions -------------
      
      // ---------- data members -------------------------------
      Tokens m_tokens;

      // ---------- static data members ------------------------
      static Tokens parseString( const std::string& aString, char aDelimiter );

};

// inline function definitions

// -------------------------------------------------------------
// Revision history
//
// $Log: StringTokenizer.h,v $
// Revision 1.5  2000/03/02 16:59:35  mkl
// new StringTokenizer parse handling
//
// Revision 1.4  1999/11/18 20:02:07  mkl
// go back to previous implementation of StringTokenizer; new NoSkipStringTokenizer uses new implementation
//
// Revision 1.3  1999/11/16 14:20:50  mkl
// StringTokenizer: allow specifying if multiple separators should be counted or skipped
//
// Revision 1.2  1998/08/24 15:51:02  mkl
// handle null string properly
//
// Revision 1.1  1998/08/22 21:58:28  mkl
// new StringTokenizer to parse strings into substrings based on a delimiter


#endif /* UTILITY_STRINGTOKENIZER_H */
