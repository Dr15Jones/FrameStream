#if !defined(COMMANDPATTERN_NUMARGCOMPOSITE_H)
#define COMMANDPATTERN_NUMARGCOMPOSITE_H
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      NumArgComposite
// 
/**\class NumArgComposite NumArgComposite.h CommandPattern/Keyword/NumArgComposite.h

 Description: A Keyword that has sub-parts that are distinguished by the number of arguments they need

 Usage:
    This allows a user to build a multi-option keyword where the options are
     differentiated by the number of arguments

*/
//
// Author:      Chris D Jones
// Created:     Sun Jul 20 09:38:46 EDT 2003
// $Id: NumArgComposite.h,v 1.1 2003/09/19 20:45:42 cdj Exp $
//
// Revision history
//
// $Log: NumArgComposite.h,v $
// Revision 1.1  2003/09/19 20:45:42  cdj
// first submission
//

// system include files

// user include files
#include "CommandPattern/Keyword/Base.h"

#include "STLUtility/fwd_vector.h"
// forward declaration

namespace CommandPattern
{
namespace Keyword
{
class NumArgComposite : public Base
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      NumArgComposite(const string& iName);
      virtual ~NumArgComposite();

      // ---------- member functions ---------------------------

      virtual unsigned int minArgs() const {
	 return m_minArgs;
      }
      virtual unsigned int maxArgs() const {
	 return m_maxArgs;
      }
      // ---------- const member functions ---------------------

      /** takes ownership of the keyword object
	   The min and max number of arguments are not allowed to
	   overlap between different inserted Base's.
	   If an overlap occurs, it is a programming error and the
	   program will exit
	   */
      void add(Base* );
      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual int implementExecute( int argc, char** argv );

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      NumArgComposite( const NumArgComposite& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const NumArgComposite& operator=( const NumArgComposite& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      STL_VECTOR(Base*) m_keywords;

      unsigned int m_minArgs;
      unsigned int m_maxArgs;
      // ---------- static data members ------------------------

};

// inline function definitions

} //namespace Keyword
} //namespace CommandPattern

#endif /* COMMANDPATTERN_NUMARGCOMPOSITE_H */
