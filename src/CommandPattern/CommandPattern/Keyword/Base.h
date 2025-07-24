#if !defined(COMMANDPATTERN_BASE_H)
#define COMMANDPATTERN_BASE_H
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      Base
// 
/**\class Base Base.h CommandPattern/Keyword/Base.h

 Description: Base class for Keywords used by CPCommandWithKeywords

 Usage:
    Only in very rare cases should you inherit directly from this class.
     Instead you should just use one of the templated Keyword classes.

*/
//
// Author:      Chris D Jones
// Created:     Fri Jul 18 14:17:35 EDT 2003
// $Id: Base.h,v 1.1 2003/09/19 20:45:39 cdj Exp $
//
// Revision history
//
// $Log: Base.h,v $
// Revision 1.1  2003/09/19 20:45:39  cdj
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

class Base
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      Base(const std::string& iName) :
	 m_name(iName) {}
      virtual ~Base() {}

      enum {kInfiniteMaxArgs = 4000};
      // ---------- member functions ---------------------------
      /** Arguments are the characters following the keyword in the line.
          All the items in argv must be used, else this is an error.
	  Can throw exceptions of type CommandPattern::Keyword::ExceptionBase
	  */
      virtual int execute( int argc, char** argv );

      // ---------- const member functions ---------------------
      ///minimum number of arguments that can follow the keyword
      virtual unsigned int minArgs() const = 0;
      ///maximum number of arguments following keyword. Must be >= minArgs()
      virtual unsigned int maxArgs() const = 0;

      const std::string& name() { return m_name; }
      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      ///called by execute 
      virtual int implementExecute( int argc, char** argv ) =0;

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      Base( const Base& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const Base& operator=( const Base& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      std::string m_name;

      // ---------- static data members ------------------------

};

// inline function definitions

} //namespace Keyword
} //namespace CommandPattern
#endif /* COMMANDPATTERN_BASE_H */
