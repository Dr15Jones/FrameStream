#if !defined(COMMANDPATTERN_COMPOSITE_H)
#define COMMANDPATTERN_COMPOSITE_H
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      Composite
// 
/**\class Composite Composite.h CommandPattern/Keyword/Composite.h

 Description: A Keyword that has sub-keywords

 Usage:
   This allows a user to build a multi-argument keyword where the extra 
     arguments are mostly prefixed by additional keywords

   You use the 'add' method to attach the various sub-keywords

   A Base with a blank ("") name will be used in the case where no
     no keyword matches the user's input

*/
//
// Author:      Chris D Jones
// Created:     Fri Jul 18 14:37:44 EDT 2003
// $Id: Composite.h,v 1.1 2003/09/19 20:45:40 cdj Exp $
//
// Revision history
//
// $Log: Composite.h,v $
// Revision 1.1  2003/09/19 20:45:40  cdj
// first submission
//

// system include files

// user include files
#include "CommandPattern/Keyword/Base.h"

#include "STLUtility/fwd_map.h"

// forward declarations

namespace CommandPattern
{
namespace Keyword
{
class Composite : public Base
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      Composite(const string& iName);
      virtual ~Composite();

      // ---------- member functions ---------------------------

      virtual unsigned int minArgs() const {
	 return m_minArgs;
      }
      virtual unsigned int maxArgs() const {
	 return m_maxArgs;
      }

      /** takes ownership of the keyword object
	   if a previous keyword has been registered with the same
	   name, the old keyword is deleted and the new one is added
	   */
      void add(Base* );

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual int implementExecute( int argc, char** argv );


      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      Composite( const Composite& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const Composite& operator=( const Composite& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      STL_MAP(string, Base*) m_keywords;

      unsigned int m_minArgs;
      unsigned int m_maxArgs;
      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "CommandPattern/Template/Composite.cc"
//#endif

} //namespace Keyword
} //namespace CommandPattern
#endif /* COMMANDPATTERN_COMPOSITE_H */
