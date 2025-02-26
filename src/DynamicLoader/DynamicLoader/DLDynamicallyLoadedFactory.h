#if !defined(DYNAMICLOADER_DLDYNAMICALLYLOADEDFACTORY_H)
#define DYNAMICLOADER_DLDYNAMICALLYLOADEDFACTORY_H
// -*- C++ -*-
//
// Package:     <DynamicLoader>
// Module:      DLDynamicallyLoadedFactory
// 
/**\class DLDynamicallyLoadedFactory DLDynamicallyLoadedFactory.h DynamicLoader/DLDynamicallyLoadedFactory.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Fri Nov 24 17:23:51 EST 2000
// $Id: DLDynamicallyLoadedFactory.h,v 1.1.1.1 2000/11/30 20:51:30 cdj Exp $
//
// Revision history
//
// $Log: DLDynamicallyLoadedFactory.h,v $
// Revision 1.1.1.1  2000/11/30 20:51:30  cdj
// imported DynamicLoader source
//

// system include files

// user include files
#include "DynamicLoader/DLFactoryBase.h"

// forward declarations

class DLDynamicallyLoadedFactory : public DLFactoryBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef void* (*FactoryFcn)();

      // ---------- Constructors and destructor ----------------
      DLDynamicallyLoadedFactory( FactoryFcn iFunction ) :
	 m_function(iFunction) {}
      //virtual ~DLDynamicallyLoadedFactory();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      void* make() const { return (*m_function)() ; }
      
      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      //DLDynamicallyLoadedFactory( const DLDynamicallyLoadedFactory& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const DLDynamicallyLoadedFactory& operator=( const DLDynamicallyLoadedFactory& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      FactoryFcn m_function;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "DynamicLoader/Template/DLDynamicallyLoadedFactory.cc"
//#endif

#endif /* DYNAMICLOADER_DLDYNAMICALLYLOADEDFACTORY_H */
