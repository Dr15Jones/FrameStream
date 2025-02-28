#if !defined(DYNAMICLOADER_DLFACTORYTEMPLATE_H)
#define DYNAMICLOADER_DLFACTORYTEMPLATE_H
// -*- C++ -*-
//
// Package:     <DynamicLoader>
// Module:      DLFactoryTemplate
// 
/**\class DLFactoryTemplate DLFactoryTemplate.h DynamicLoader/DLFactoryTemplate.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Fri Nov 24 10:03:04 EST 2000
// $Id: DLFactoryTemplate.h,v 1.2 2002/06/04 19:40:49 cleo3 Exp $
//
// Revision history
//
// $Log: DLFactoryTemplate.h,v $
// Revision 1.2  2002/06/04 19:40:49  cleo3
// void* to T* is NOT a covariant return type difference
//
// Revision 1.1.1.1  2000/11/30 20:51:30  cdj
// imported DynamicLoader source
//

// system include files

// user include files
#include "DynamicLoader/DLFactoryBase.h"

// forward declarations

template <class T>
class DLFactoryTemplate : public DLFactoryBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      DLFactoryTemplate() {}
      virtual ~DLFactoryTemplate() {}

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      virtual void* make() const { return new T; }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      DLFactoryTemplate( const DLFactoryTemplate<T>& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const DLFactoryTemplate<T>& operator=( const DLFactoryTemplate<T>& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "DynamicLoader/Template/DLFactoryTemplate.cc"
//#endif

#endif /* DYNAMICLOADER_DLFACTORYTEMPLATE_H */
