#if !defined(DYNAMICLOADER_DLFACTORYBASE_H)
#define DYNAMICLOADER_DLFACTORYBASE_H
// -*- C++ -*-
//
// Package:     <DynamicLoader>
// Module:      DLFactoryBase
// 
/**\class DLFactoryBase DLFactoryBase.h DynamicLoader/DLFactoryBase.h

 Description: Base class for all object Factories

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Fri Nov 24 10:02:57 EST 2000
// $Id: DLFactoryBase.h,v 1.1.1.1 2000/11/30 20:51:30 cdj Exp $
//
// Revision history
//
// $Log: DLFactoryBase.h,v $
// Revision 1.1.1.1  2000/11/30 20:51:30  cdj
// imported DynamicLoader source
//

// system include files

// user include files

// forward declarations

class DLFactoryBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      DLFactoryBase() {}
      virtual ~DLFactoryBase() {}

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      virtual void* make() const = 0;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      DLFactoryBase( const DLFactoryBase& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const DLFactoryBase& operator=( const DLFactoryBase& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "DynamicLoader/Template/DLFactoryBase.cc"
//#endif

#endif /* DYNAMICLOADER_DLFACTORYBASE_H */
