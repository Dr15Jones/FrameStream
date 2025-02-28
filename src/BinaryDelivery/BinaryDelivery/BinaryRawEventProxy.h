#if !defined(BINARYDELIVERY_BINARYRAWEVENTPROXY_H)
#define BINARYDELIVERY_BINARYRAWEVENTPROXY_H
// -*- C++ -*-
//
// Package:     BinaryDelivery
// Module:      BinaryRawEventProxy
// 
// Description: Proxy for delivering RawEvents from binary files
//
// Usage:
//    <usage>
//
// Author:      David L. Kreinick
// Created:     Mon Nov  9 12:11:49 EST 1998
// $Id: BinaryRawEventProxy.h,v 1.2 1999/12/10 16:20:26 cdj Exp $
//
// Revision history
//
// $Log: BinaryRawEventProxy.h,v $
// Revision 1.2  1999/12/10 16:20:26  cdj
// updated to work with extract exceptions
//
// Revision 1.1  1998/12/01 19:50:37  dlk
// DLK: New proxy for creating RawEventData from a binary input file
//
//

// system include files

// user include files
#include "DataDelivery/DataSourceProxy.h"
#include "RawData/RawEventData.h"
#include "BinaryDelivery/BinaryProxyDeliverer.h"

// forward declarations

class BinaryRawEventProxy : public DataSourceProxy< RawEventData >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef RawEventData value_type;

      // Constructors and destructor
      BinaryRawEventProxy( BinaryProxyDeliverer& iDeliver );
      virtual ~BinaryRawEventProxy();

      // member functions

      // const member functions

      // static member functions

   protected:
      // protected member functions
      virtual void invalidateCache() ;
      virtual const value_type* faultHandler( const Record& aRecord,
					      const DataKey& aKey );

      // protected const member functions

   private:
      // Constructors and destructor
      BinaryRawEventProxy( const BinaryRawEventProxy& );

      // assignment operator(s)
      const BinaryRawEventProxy& operator=( const BinaryRawEventProxy& );

      // private member functions

      // private const member functions

      // data members
      value_type* m_BinaryRawEvent ;  // Pointer to the RawEvent we are making
      BinaryProxyDeliverer* m_BinaryProxyDeliverer ; // Pointer to the proxy
                                      // deliverer so we can access the buffer

      // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "BinaryDelivery/Template/BinaryRawEventProxy.cc"
//#endif

#endif /* BINARYDELIVERY_BINARYRAWEVENTPROXY_H */
