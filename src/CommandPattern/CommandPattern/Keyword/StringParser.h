#if !defined(COMMANDPATTERN_STRINGPARSER_H)
#define COMMANDPATTERN_STRINGPARSER_H
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      StringParser
// 
/**\class StringParser StringParser.h CommandPattern/StringParser.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris Jones
// Created:     Thu Aug 28 10:31:57 EDT 2003
// $Id: StringParser.h,v 1.1 2003/09/19 20:45:43 cdj Exp $
//
// Revision history
//
// $Log: StringParser.h,v $
// Revision 1.1  2003/09/19 20:45:43  cdj
// first submission
//

// system include files
#include <string>
// user include files

// forward declarations
namespace CommandPattern
{
namespace Keyword
{
class StringParser
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      StringParser() {}
      //virtual ~StringParser();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      unsigned int minArgs() const {
         return 1;
      }
      unsigned int maxArgs() const {
         return 1;
      }
      string parse(int iArgC, char** iArgV) {
         return iArgV[0];
      }
   // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      //StringParser( const StringParser& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const StringParser& operator=( const StringParser& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

}
}
#endif /* COMMANDPATTERN_STRINGPARSER_H */
