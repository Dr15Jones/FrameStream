#if !defined(COMMANDPATTERN_FACTORYBASE_H)
#define COMMANDPATTERN_FACTORYBASE_H
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      FactoryBase
// 
// Description: FactoryBase class for FactoryTemplate, used by the Loader
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Tue Nov 9 11:35:09 EST 1998
// $Id: FactoryBase.h,v 1.1 1998/11/10 23:21:42 mkl Exp $
//
// Revision history
//
// $Log: FactoryBase.h,v $
// Revision 1.1  1998/11/10 23:21:42  mkl
// static linking of proc/ducers/source-/sink-formats/modules whatever; and cleanup
//
//

// system include files

// user include files

// forward declarations

class FactoryBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      FactoryBase() {}
      virtual ~FactoryBase() {}

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      virtual void* make() const = 0;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      FactoryBase( const FactoryBase& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const FactoryBase& operator=( const FactoryBase& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "CommandPattern//FactoryBase.cc"
//#endif

#endif /* COMMANDPATTERN_FACTORYBASE_H */
