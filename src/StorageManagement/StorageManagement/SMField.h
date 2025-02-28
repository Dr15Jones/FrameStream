#if !defined(STORAGEMANAGEMENT_SMFIELD_H)
#define STORAGEMANAGEMENT_SMFIELD_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMField
// 
// Description: Calls the appropriate put method of the sink
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Thu Sep  2 15:33:49 EDT 1999
// $Id: SMField.h,v 1.3 2003/02/05 21:08:56 cleo3 Exp $
//
// Revision history
//
// $Log: SMField.h,v $
// Revision 1.3  2003/02/05 21:08:56  cleo3
// added includes needed for cxx 6.5
//
// Revision 1.2  1999/11/03 17:53:46  cdj
// added compression hints code
//
// Revision 1.1.1.1  1999/09/13 21:21:40  cdj
// imported package
//

// system include files

// user include files
#include "StorageManagement/SMFieldBase.h"
#include "StorageManagement/SMSinkStream.h"

// forward declarations

template< class T >
class SMField : public SMFieldBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef T field_type;

      // ---------- Constructors and destructor ----------------
      SMField( const char* iFieldName,
	       const T& iValue ) : 
	 SMFieldBase( iFieldName ), m_value( iValue ) {}
	 //virtual ~SMField();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      void store( SMSinkStream& iSink ) const {
	 iSink.put( name(), value() ); }

      const T& value() const { return m_value; }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      //SMField( const SMField& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const SMField& operator=( const SMField& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      const T m_value;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMField.cc"
//#endif
template< class T >
inline
SMField<T >
sm_field( const char* iName, const T& iValue ) {
   return SMField<T>( iName, iValue ); 
}

#endif /* STORAGEMANAGEMENT_SMFIELD_H */
