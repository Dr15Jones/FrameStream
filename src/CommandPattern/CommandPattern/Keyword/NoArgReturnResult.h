#if !defined(COMMANDPATTERN_NOARGRETURNRESULT_H)
#define COMMANDPATTERN_NOARGRETURNRESULT_H
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      NoArgReturnResult
// 
/**\class NoArgReturnResult NoArgReturnResult.h CommandPattern/Keyword/NoArgReturnResult.h

 Description: Keyword that calls a method that takes no argument but returns a resulting std::string

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Fri Jul 18 15:11:53 EDT 2003
// $Id: NoArgReturnResult.h,v 1.1 2003/09/19 20:45:42 cdj Exp $
//
// Revision history
//
// $Log: NoArgReturnResult.h,v $
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
template <class T, class ReturnT>
class NoArgReturnResult : public Base
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      NoArgReturnResult( const std::string& iName,
		      T* iTarget,
		      ReturnT (T::* iMethod)(),
		      const Command* iCommand,
		      int iStatus = Command::COMMAND_OK):
	 Base(iName),
	 m_target(iTarget),
	 m_method( iMethod ),
	 m_command( iCommand ),
	 m_status( iStatus ) {}

      //virtual ~NoArgReturnResult();

      // ---------- member functions ---------------------------
      virtual unsigned int minArgs() const {
	 return 0;
      }

      virtual unsigned int maxArgs() const {
	 return 0;
      }
      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual int implementExecute( int , char**  ) {
	 m_command->setResult( (m_target->*m_method)() );
	 return m_status;
      }

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      NoArgReturnResult( const NoArgReturnResult& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const NoArgReturnResult& operator=( const NoArgReturnResult& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      T* m_target;
      ReturnT (T::* m_method)();
      const Command* m_command;
      int m_status;

      // ---------- static data members ------------------------

};

// inline function definitions

} //namespace Keyword
} //namespace CommandPattern
#endif /* COMMANDPATTERN_NOARGRETURNRESULT_H */
