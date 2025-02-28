#if !defined(INTERACTIVEDELIVERY_INTERACTIVEPROXYDELIVERER_H)
#define INTERACTIVEDELIVERY_INTERACTIVEPROXYDELIVERER_H
// -*- C++ -*-
//
// Package:     InteractiveDelivery
// Module:      InteractiveProxyDeliverer
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Chris D. Jones
// Created:     Sat Apr 19 12:29:27 EDT 1997
// $Id: InteractiveProxyDeliverer.h,v 1.5 2003/11/22 20:22:28 cdj Exp $
//
// Revision history
//
// $Log: InteractiveProxyDeliverer.h,v $
// Revision 1.5  2003/11/22 20:22:28  cdj
// can now specify what stream should be used
//
// Revision 1.4  1997/08/14 11:43:33  sjp
// Mods to run under CW Pro 1
//
// Revision 1.3  1997/08/06 16:30:30  sjp
// Modified to use ProxyDeliverer
//
// Revision 1.2  1997/07/09 19:22:09  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.1.1.1  1997/04/21 19:30:11  cdj
// First submission
//


// system include files

// user include files
#include "DataDelivery/ProxyDeliverer.h"


// forward declarations

class InteractiveProxyDeliverer : public ProxyDeliverer
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      InteractiveProxyDeliverer(const Stream::Type& iStream );
      virtual ~InteractiveProxyDeliverer();

      // member functions
      virtual void disable( const Stream::Type& aStream );
      virtual void enable( const Stream::Type& aStream );

      // const member functions

      // static member functions

   protected:
      // protected member functions
      virtual void resetCache( const Stream::Type& aStream );
      virtual void registerProxies( const Stream::Type& aStream ,
				    KeyedProxies& aProxyList ) ;

      // protected const member functions

   private:
      // Constructors and destructor
      InteractiveProxyDeliverer( const InteractiveProxyDeliverer& );

      // assignment operator(s)
      const InteractiveProxyDeliverer& operator=( const InteractiveProxyDeliverer& );

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

#endif /* INTERACTIVEDELIVERY_INTERACTIVEPROXYDELIVERER_H */
