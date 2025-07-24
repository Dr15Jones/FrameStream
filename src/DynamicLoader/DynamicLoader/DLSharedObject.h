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
// $Id: DLSharedObject.h,v 1.2 2003/03/31 19:42:55 cdj Exp $
//
// Revision history
//
// $Log: DLSharedObject.h,v $
// Revision 1.2  2003/03/31 19:42:55  cdj
// now works under OS X (Darwin)
//
// Revision 1.1.1.1  2000/11/30 20:51:30  cdj
// imported DynamicLoader source
//

// system include files
#include <string>
#if defined(Darwin)
#include <mach-o/dyld.h>
#endif

// user include files

// forward declarations

class DLSharedObject
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
#if !defined(Darwin)
      typedef void* Handle; 
#else
      typedef NSModule Handle;
#endif
      // ---------- Constructors and destructor ----------------
      DLSharedObject(const std::string& iName, void* iHandle ) :
	 m_name(iName), m_handle(iHandle) {}
      //virtual ~DLSharedObject();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      //can throw a DLSymbolNotFoundException
      void* getSymbol( const std::string& symbolName ) const; 

      const std::string& name() const { return m_name; }
      Handle handle() const { return m_handle; }

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
      std::string m_name;
      Handle m_handle;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "DynamicLoader/Template/DLSharedObject.cc"
//#endif

#endif /* DYNAMICLOADER_DLSHAREDOBJECT_H */
