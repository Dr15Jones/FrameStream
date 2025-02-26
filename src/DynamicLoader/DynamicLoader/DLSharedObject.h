#if !defined(DYNAMICLOADER_DLSHAREDOBJECT_H)
#define DYNAMICLOADER_DLSHAREDOBJECT_H
// -*- C++ -*-
//
// Package:     <DynamicLoader>
// Module:      DLSharedObject
// 
/**\class DLSharedObject DLSharedObject.h DynamicLoader/DLSharedObject.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Mon Nov 20 13:29:16 EST 2000
// $Id: DLSharedObject.h,v 1.1.1.1 2000/11/30 20:51:30 cdj Exp $
//
// Revision history
//
// $Log: DLSharedObject.h,v $
// Revision 1.1.1.1  2000/11/30 20:51:30  cdj
// imported DynamicLoader source
//

// system include files
#include <string>

// user include files

// forward declarations
using namespace std;

class DLSharedObject
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      DLSharedObject(const string& iName, void* iHandle ) :
	 m_name(iName), m_handle(iHandle) {}
      //virtual ~DLSharedObject();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      //can throw a DLSymbolNotFoundException
      void* getSymbol( const string& symbolName ) const; 

      const string& name() const { return m_name; }
      void* handle() const { return m_handle; }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      DLSharedObject( const DLSharedObject& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const DLSharedObject& operator=( const DLSharedObject& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      string m_name;
      void* m_handle;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "DynamicLoader/Template/DLSharedObject.cc"
//#endif

#endif /* DYNAMICLOADER_DLSHAREDOBJECT_H */
