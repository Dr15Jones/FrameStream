// -*- C++ -*-
#if !defined(MODNAME_MODNAME_H)
#define MODNAME_MODNAME_H
//
// Package:     Modname
// Module:      Modname
//
/**\class Modname Modname.h Modname/Modname.h
 
 Description: Suez Module that allows you to control the "event" loop

 Usage:
    <usage>

*/
//
// Author:      John Doe
// Created:     day-mon-xx
// RCS(Id)
//
// Revision history
//
// RCS(Log)
//

// system include files

// user include files
#include "CommandPattern/Module.h"
#include "FrameIterate/FrameIteratorModuleBase.h"
#include "FrameIterate/FIHolder.h"
//The data object you wish to change on each iteration
//#include "CleoDB/DBRunHeader.h"  

// forward declarations

class Modname : public FrameIteratorModuleBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      Modname();
      virtual ~Modname();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      ///override this function to do the actual iterations
      virtual void iterate( const FIFrameIterator& iBegin,
			    const FIFrameIterator& iEnd );

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      Modname( const Modname& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const Modname& operator=( const Modname& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      //This is the object you change every iteration
      //DBRunHeader m_header;
      //Holds the value and passes it onto the Proxy
      //FIHolder<DBRunHeader> m_headerHolder;
      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "Modname/Template/Modname.cc"
//#endif

#endif /* MODNAME_MODNAME_H */
