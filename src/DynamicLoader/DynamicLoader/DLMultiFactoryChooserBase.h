#if !defined(DYNAMICLOADER_DLMULTIFACTORYCHOOSERBASE_H)
#define DYNAMICLOADER_DLMULTIFACTORYCHOOSERBASE_H
// -*- C++ -*-
//
// Package:     DynamicLoader
// Module:      DLMultiFactoryChooserBase
// 
/**\class DLMultiFactoryChooserBase DLMultiFactoryChooserBase.h DynamicLoader/DLMultiFactoryChooserBase.h

 Description: Base class for classes that resolve which Factory to use if 
     multiple choices are available

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Wed Nov 29 13:04:31 EST 2000
// $Id: DLMultiFactoryChooserBase.h,v 1.1.1.1 2000/11/30 20:51:30 cdj Exp $
//
// Revision history
//
// $Log: DLMultiFactoryChooserBase.h,v $
// Revision 1.1.1.1  2000/11/30 20:51:30  cdj
// imported DynamicLoader source
//

// system include files
#include <vector>
#include <string>

// user include files
#include <vector>

// forward declarations

class DLMultiFactoryChooserBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      DLMultiFactoryChooserBase() {}
      virtual ~DLMultiFactoryChooserBase() {}

      // ---------- member functions ---------------------------
      
      virtual std::vector<std::string>::iterator 
           choose( const std::string& iShortName,
		   std::vector<std::string>::iterator itBegin,
		   std::vector<std::string>::iterator itEnd ) = 0;

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      DLMultiFactoryChooserBase( const DLMultiFactoryChooserBase& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const DLMultiFactoryChooserBase& operator=( const DLMultiFactoryChooserBase& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "DynamicLoader/Template/DLMultiFactoryChooserBase.cc"
//#endif

#endif /* DYNAMICLOADER_DLMULTIFACTORYCHOOSERBASE_H */
