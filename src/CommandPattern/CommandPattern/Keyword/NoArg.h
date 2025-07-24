#if !defined(COMMANDPATTERN_NOARG_H)
#define COMMANDPATTERN_NOARG_H
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      NoArg
// 
/**\class NoArg NoArg.h CommandPattern/Keyword/NoArg.h

 Description: Keyword for methods that take no argument but return status

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Fri Jul 18 15:11:53 EDT 2003
// $Id: NoArg.h,v 1.1 2003/09/19 20:45:41 cdj Exp $
//
// Revision history
//
// $Log: NoArg.h,v $
// Revision 1.1  2003/09/19 20:45:41  cdj
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
class NoArg : public Base
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      NoArg( const std::string& iName,
		      T* iTarget,
		      int (T::* iMethod)() ):
	 Base(iName),
	 m_target(iTarget),
	 m_method( iMethod ) {}

      //virtual ~NoArg();

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
	 return (m_target->*m_method)();
      }

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      NoArg( const NoArg& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const NoArg& operator=( const NoArg& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      T* m_target;
      int (T::* m_method)();

      // ---------- static data members ------------------------

};

} //namespace Keyword
} //namespace CommandPattern

#endif /* COMMANDPATTERN_NOARG_H */
