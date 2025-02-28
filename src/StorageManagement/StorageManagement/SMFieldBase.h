#if !defined(STORAGEMANAGEMENT_SMFIELDBASE_H)
#define STORAGEMANAGEMENT_SMFIELDBASE_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMFieldBase
// 
// Description: Base class for objects that write fields to a sink
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Thu Sep  2 15:26:15 EDT 1999
// $Id: SMFieldBase.h,v 1.1.1.1 1999/09/13 21:21:40 cdj Exp $
//
// Revision history
//
// $Log: SMFieldBase.h,v $
// Revision 1.1.1.1  1999/09/13 21:21:40  cdj
// imported package
//

// system include files

// user include files

// forward declarations
class SMSinkStream;

class SMFieldBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------

      ///Does not take ownership of iFieldName
      SMFieldBase( const char * iFieldName ) : m_name( iFieldName ) {}
      //virtual ~SMFieldBase();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      virtual void store( SMSinkStream& iSink ) const = 0;
      const char* name() const { return m_name; }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      //SMFieldBase( const SMFieldBase& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const SMFieldBase& operator=( const SMFieldBase& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      const char* m_name;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMFieldBase.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMFIELDBASE_H */
