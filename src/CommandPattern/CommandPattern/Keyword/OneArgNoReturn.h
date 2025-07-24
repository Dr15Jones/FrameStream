#if !defined(COMMANDPATTERN_ONEARGNORETURN_H)
#define COMMANDPATTERN_ONEARGNORETURN_H
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      OneArgNoReturn
// 
/**\class OneArgNoReturn OneArgNoReturn.h CommandPattern/Keyword/OneArgNoReturn.h

 Description: Keyword to call member method that takes one argument and returns no status value

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Fri Jul 18 15:11:53 EDT 2003
// $Id: OneArgNoReturn.h,v 1.1 2003/09/19 20:45:43 cdj Exp $
//
// Revision history
//
// $Log: OneArgNoReturn.h,v $
// Revision 1.1  2003/09/19 20:45:43  cdj
// first submission
//

// system include files

// user include files
#include "CommandPattern/Keyword/Base.h"

// forward declarations

namespace CommandPattern
{
namespace Keyword
{
  template <class T, class ArgT, class ParserT>
class OneArgNoReturn : public Base
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      OneArgNoReturn( const std::string& iName,
			      T* iTarget,
			      void (T::* iMethod)(ArgT),
                              const ParserT& iParser = ParserT(),
			      int iReturn = Command::COMMAND_OK):
	 Base(iName),
	 m_target(iTarget),
	 m_method( iMethod ),
         m_parser(iParser),
	 m_return(iReturn ){}

      //virtual ~OneArgNoReturn();

      // ---------- member functions ---------------------------
      // ---------- const member functions ---------------------
      virtual unsigned int minArgs() const {
	 return m_parser.minArgs();
      }

      virtual unsigned int maxArgs() const {
	 return m_parser.maxArgs();
      }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual int implementExecute( int iArgC, char**  iArgV) {
	 (m_target->*m_method)( m_parser.parse(iArgC, iArgV) );
	 return m_return;
      }


      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      OneArgNoReturn( const OneArgNoReturn& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const OneArgNoReturn& operator=( const OneArgNoReturn& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      T* m_target;
      void (T::* m_method)(ArgT);
      ParserT m_parser;
      int m_return;

      // ---------- static data members ------------------------

};

// inline function definitions

} //namespace Keyword
} //namespace CommandPattern

#endif /* COMMANDPATTERN_ONEARGNORETURN_H */
