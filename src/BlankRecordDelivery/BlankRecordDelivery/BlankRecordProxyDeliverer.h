#if !defined(BLANKRECORDDELIVERY_BLANKRECORDPROXYDELIVERER_H)
#define BLANKRECORDDELIVERY_BLANKRECORDPROXYDELIVERER_H
// -*- C++ -*-
//
// Package:     BlankRecordDelivery
// Module:      BlankRecordProxyDeliverer
// 
// Description: ProxyDeliverer needed by BlankRecordSourceController.  This
//              class does not register any Proxies.
//
// Usage:
//    <usage>
//
// Author:      Chris D. Jones
// Created:     Thu Mar 26 13:47:51 EST 1998
// $Id: BlankRecordProxyDeliverer.h,v 1.1.1.1 1998/03/31 21:21:18 cdj Exp $
//
// Revision history
//
// $Log: BlankRecordProxyDeliverer.h,v $
// Revision 1.1.1.1  1998/03/31 21:21:18  cdj
// first submission
//

// system include files

// user include files
#include "DataDelivery/ProxyDeliverer.h"

// forward declarations

class BlankRecordProxyDeliverer : public ProxyDeliverer
{
      // friend classes and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      BlankRecordProxyDeliverer( const Stream::Set& iStreamsToRegister );
      virtual ~BlankRecordProxyDeliverer();

      // member functions
      virtual void disable( const Stream::Type& aStream ) ;
      virtual void enable( const Stream::Type& aStream ) ;

      // const member functions

      // static member functions

   protected:
      // protected member functions
      virtual void resetCache( const Stream::Type& aStream ) ;
      virtual void registerProxies( const Stream::Type& aStream ,
				    KeyedProxies& aProxyList );

      // protected const member functions

   private:
      // Constructors and destructor
      BlankRecordProxyDeliverer( const BlankRecordProxyDeliverer& );

      // assignment operator(s)
      const BlankRecordProxyDeliverer& operator=( const BlankRecordProxyDeliverer& );

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "BlankRecordDelivery/Template/BlankRecordProxyDeliverer.cc"
//#endif

#endif /* BLANKRECORDDELIVERY_BLANKRECORDPROXYDELIVERER_H */
