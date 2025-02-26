#if !defined(COMMANDPATTERN_FACTORYTEMPLATE_H)
#define COMMANDPATTERN_FACTORYTEMPLATE_H
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      FactoryTemplate
// 
// Description: templated factory used by the Loader
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Tue Nov 9 11:35:09 EST 1998
// $Id: FactoryTemplate.h,v 1.3 2000/12/04 18:47:15 cdj Exp $
//
// Revision history
//
// $Log: FactoryTemplate.h,v $
// Revision 1.3  2000/12/04 18:47:15  cdj
// FactoryTemplate now inherits from DLFactoryTemplate
//
// Revision 1.2  2000/05/12 15:44:12  mkl
// reorder instantiation directives for Parameter of vector of T to have className directive first
//
// Revision 1.1  1998/11/10 23:21:55  mkl
// static linking of proc/ducers/source-/sink-formats/modules whatever; and cleanup
//
//

// system include files

// user include files
#include "DynamicLoader/DLFactoryTemplate.h"

// forward declarations

template< class T >
class FactoryTemplate : public DLFactoryTemplate<T>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      FactoryTemplate() {}

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      FactoryTemplate( const FactoryTemplate& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const FactoryTemplate& operator=( const FactoryTemplate& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "CommandPattern/Template/FactoryTemplate.cc"
//#endif

#endif /* COMMANDPATTERN_FACTORYTEMPLATE_H */
