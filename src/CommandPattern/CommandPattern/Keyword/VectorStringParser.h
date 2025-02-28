#if !defined(COMMANDPATTERN_VECTORSTRINGPARSER_H)
#define COMMANDPATTERN_VECTORSTRINGPARSER_H
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      VectorStringParser
// 
/**\class VectorStringParser VectorStringParser.h CommandPattern/VectorStringParser.h

 Description: Keyword parser that returns a vector of strings

 Usage:
    The default requires at least one entry and not maximum number of entries

*/
//
// Author:      Chris Jones
// Created:     Thu Aug 28 10:31:57 EDT 2003
// $Id: VectorStringParser.h,v 1.1 2003/09/19 20:45:43 cdj Exp $
//
// Revision history
//
// $Log: VectorStringParser.h,v $
// Revision 1.1  2003/09/19 20:45:43  cdj
// first submission
//

// system include files
#include <string>
#include <vector>

// user include files

// forward declarations
namespace CommandPattern
{
namespace Keyword
{
class VectorStringParser
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      VectorStringParser(unsigned int iMin=1, unsigned int iMax=4000) :
       m_min(iMin), m_max(iMax) {}
      //virtual ~VectorStringParser();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      unsigned int minArgs() const {
         return m_min;
      }
      unsigned int maxArgs() const {
         return m_max;
      }
      vector<string> parse(int iArgC, char** iArgV) {
         vector<string> returnValue;
         returnValue.reserve(iArgC);
         for(int itArg= 0; itArg != iArgC; ++itArg) {
            returnValue.push_back(iArgV[itArg]);
         }
         return returnValue;
      }
   // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      //VectorStringParser( const VectorStringParser& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const VectorStringParser& operator=( const VectorStringParser& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      unsigned int m_min;
      unsigned int m_max;
   
      // ---------- static data members ------------------------

};

}
}
#endif /* COMMANDPATTERN_VECTORSTRINGPARSER_H */
