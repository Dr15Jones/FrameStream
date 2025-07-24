#if !defined(COMMANDPATTERN_STRINGUTILITIES_H)
#define COMMANDPATTERN_STRINGUTILITIES_H
// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      StringUtilities
// 
// Description: <one line class summary>
//
// Usage:
//
// Author:      Martin Lohner
// Created:     Wed Jul 23 12:56:54 EDT 1997
// $Id: StringUtilities.h,v 1.9 2000/12/02 19:19:30 cdj Exp $
//
// Revision history
//
// $Log: StringUtilities.h,v $
// Revision 1.9  2000/12/02 19:19:30  cdj
// removed file name related functions (now in Utility/FileNameUtils)
//
// Revision 1.8  1999/09/10 01:04:57  mkl
// 1) new smarter history command.
// 2) new "uppercase" function, since our compilers don't support it yet.
// 3) moved "Conversion" class to CommandPattern (needed by HistoryCommand).
//
// Revision 1.7  1999/01/27 22:54:52  mkl
// rewrote StringUtil utility functions
//
// Revision 1.6  1998/04/01 18:08:00  mkl
// switched to C++Std standard include area: fwd_string/istream/ostream
//
// Revision 1.5  1998/02/03 21:28:03  mkl
// switch over to STLUtility library
//
// Revision 1.4  1997/10/15 02:20:38  mkl
// generalize find functions for different characters
//
// Revision 1.3  1997/10/04 21:29:12  mkl
// new Stringutil functions
//
// Revision 1.2  1997/10/02 22:36:13  mkl
// now have string utility functions for path, filename, basename, and extension
//
// Revision 1.1  1997/09/04 06:37:30  mkl
// moved JobControl/StringUtilities here
//
//

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files

// STL include
#include <string>

// forward declarations

      
class StringUtil
{
      // ---------- friend classes and functions ---------------
      friend class Dummy;

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------
      // uppercase, since not all iomanip implementations support it yet
      static std::string toUppercase( const std::string& iString );

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      StringUtil();                    // stop default
      ~StringUtil();                   // stop default
      StringUtil( const StringUtil& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const StringUtil& operator=( const StringUtil& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "package/Template/StringUtil.cc"
//#endif

#endif /* COMMANDPATTERN_STRINGUTILITIES_H */

