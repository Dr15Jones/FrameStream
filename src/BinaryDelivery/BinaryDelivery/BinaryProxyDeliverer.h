#if !defined(BINARYDELIVERY_BINARYPROXYDELIVERER_H)
#define BINARYDELIVERY_BINARYPROXYDELIVERER_H
// -*- C++ -*-
//
// Package:     BinaryDelivery
// Module:      BinaryProxyDeliverer
// 
// Description: Delivers proxies for reading binary records
//
// Usage:
//    <usage>
//
// Author:      David L. Kreinick
// Created:     Mon Oct 19 13:21:31 EDT 1998
// $Id: BinaryProxyDeliverer.h,v 1.1.1.1 1998/11/03 20:46:42 dlk Exp $
//
// Revision history
//
// $Log: BinaryProxyDeliverer.h,v $
// Revision 1.1.1.1  1998/11/03 20:46:42  dlk
// importing new BinaryDelivery sources
//

// system include files

// user include files
#include "DataDelivery/ProxyDeliverer.h"
//#include "BinaryDelivery/BDRecordBuffer.h"

// forward declarations
class BDRecordBuffer ;
class BinarySourceController ;
#include <map>
#include <vector>

class BinaryProxyDeliverer : public ProxyDeliverer
{
      // friend classes and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      BinaryProxyDeliverer();
      virtual ~BinaryProxyDeliverer();

      // member functions
      virtual void disable( const Stream::Type& aStream );
      virtual void enable( const Stream::Type& aStream );

      void changeSourceController( BinarySourceController& iController );

      BDRecordBuffer* buffer( const Stream::Type& iStream );
      DABoolean finishedWritingToBuffer( const Stream::Type& iStream );

      // const member functions
      DABoolean available( const Stream::Type& aStream ) const ;      

      // static member functions

   protected:
      // protected member functions
      void registerProxies(const Stream::Type & iStream, 
                              std::vector< KeyedProxy > &iProxyList);
      virtual void resetCache( const Stream::Type& aStream );

      // protected const member functions

   private:
      // Constructors and destructor
      BinaryProxyDeliverer( const BinaryProxyDeliverer& );

      // assignment operator(s)
      const BinaryProxyDeliverer& operator=( const BinaryProxyDeliverer& );

      // private member functions

      // private const member functions

      // data members
      std::map< Stream::Type,BDRecordBuffer*>& m_streamToBufferMap;

      std::vector< DABoolean >& m_available ;

      // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "BinaryDelivery/Template/BinaryProxyDeliverer.cc"
//#endif

#endif /* BINARYDELIVERY_BINARYPROXYDELIVERER_H */
