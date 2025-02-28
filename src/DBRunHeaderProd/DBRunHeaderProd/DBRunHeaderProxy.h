// -*- C++ -*-
//
// Package:     <DBRunHeaderProd>
// Module:      DBRunHeaderProxy
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Andreas Wolf
// Created:     
// $Id: DBRunHeaderProxy.h,v 1.1.1.1 1999/07/22 18:20:53 aw Exp $
//
// Revision history
//
// $Log: DBRunHeaderProxy.h,v $
// Revision 1.1.1.1  1999/07/22 18:20:53  aw
// Imported initial DBRunHeaderProd sources
//
//
//

#ifndef DBRUNHEADERPROD_DBRUNHEADERPROXY_H
#define DBRUNHEADERPROD_DBRUNHEADERPROXY_H
// system include files

// user include files
#include "DataHandler/DataField.h"
#include "CleoDB/DBRunHeader.h"

// forward declarations

class DBRunHeaderProxy : public DataField< DBRunHeader >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef DBRunHeader value_type;

      // Constructors and destructor
      DBRunHeaderProxy();
      virtual ~DBRunHeaderProxy();

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
      DBRunHeaderProxy( const DBRunHeaderProxy& );

      // assignment operator(s)
      const DBRunHeaderProxy& operator=( const DBRunHeaderProxy& );

      // private member functions

      // private const member functions

      // data members
      value_type* m_DBRunHeader ;

      // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "DBRunHeaderProd/Template/DBRunHeaderProxy.cc"
//#endif

#endif /* DBRUNHEADERPROD_DBRUNHEADERPROXY_H */
