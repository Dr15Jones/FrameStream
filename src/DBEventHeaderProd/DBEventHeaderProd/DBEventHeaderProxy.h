#if !defined(DBEVENTHEADERPROD_DBEVENTHEADERPROXY_H)
#define DBEVENTHEADERPROD_DBEVENTHEADERPROXY_H
// -*- C++ -*-
//
// Package:     <DBEventHeaderProd>
// Module:      DBEventHeaderProxy
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Tue Jul 21 12:38:36 EDT 1998
// $Id: DBEventHeaderProxy.h,v 1.1.1.1 1999/06/01 18:58:32 mkl Exp $
//
// Revision history
//
// $Log: DBEventHeaderProxy.h,v $
// Revision 1.1.1.1  1999/06/01 18:58:32  mkl
// imported sources
//
//

// system include files

// user include files
#include "DataHandler/DataField.h"
#include "CleoDB/DBEventHeader.h"

// forward declarations

class DBEventHeaderProxy : public DataField< DBEventHeader >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef DBEventHeader value_type;

      // Constructors and destructor
      DBEventHeaderProxy();
      virtual ~DBEventHeaderProxy();

      // member functions
      virtual void invalidateCache() ;
      virtual const value_type* faultHandler( const Record& aRecord,
					      const IfdKey& aKey );

      // const member functions

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      DBEventHeaderProxy( const DBEventHeaderProxy& );

      // assignment operator(s)
      const DBEventHeaderProxy& operator=( const DBEventHeaderProxy& );

      // private member functions

      // private const member functions

      // data members
      value_type* m_DBEventHeader ;

      // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "DBEventHeaderProd/Template/DBEventHeaderProxy.cc"
//#endif

#endif /* DBEVENTHEADERPROD_DBEVENTHEADERPROXY_H */
