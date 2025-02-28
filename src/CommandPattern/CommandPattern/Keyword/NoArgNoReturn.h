#if !defined(COMMANDPATTERN_NOARGNORETURN_H)
#define COMMANDPATTERN_NOARGNORETURN_H
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      NoArgNoReturn
// 
/**\class NoArgNoReturn NoArgNoReturn.h CommandPattern/Keyword/NoArgNoReturn.h

 Description: Keyword to call member method that takes no arguments and returns no status value

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Fri Jul 18 15:11:53 EDT 2003
// $Id: NoArgNoReturn.h,v 1.1 2003/09/19 20:45:42 cdj Exp $
//
// Revision history
//
// $Log: NoArgNoReturn.h,v $
// Revision 1.1  2003/09/19 20:45:42  cdj
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
template <class T>
class NoArgNoReturn : public Base
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      NoArgNoReturn( const string& iName,
			      T* iTarget,
			      void (T::* iMethod)(),
			      int iReturn = Command::COMMAND_OK):
	 Base(iName),
	 m_target(iTarget),
	 m_method( iMethod ),
	 m_return(iReturn ){}

      //virtual ~NoArgNoReturn();

      // ---------- member functions ---------------------------
      // ---------- const member functions ---------------------
      virtual unsigned int minArgs() const {
	 return 0;
      }

      virtual unsigned int maxArgs() const {
	 return 0;
      }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual int implementExecute( int , char**  ) {
	 (m_target->*m_method)();
	 return m_return;
      }


      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      NoArgNoReturn( const NoArgNoReturn& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const NoArgNoReturn& operator=( const NoArgNoReturn& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      T* m_target;
      void (T::* m_method)();
      int m_return;

      // ---------- static data members ------------------------

};

// inline function definitions

} //namespace Keyword
} //namespace CommandPattern

#endif /* COMMANDPATTERN_NOARGNORETURN_H */
