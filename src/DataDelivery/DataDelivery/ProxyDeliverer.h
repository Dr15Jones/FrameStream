#if !defined(DATADELIVERY_PROXYDELIVERER_H)
#define DATADELIVERY_PROXYDELIVERER_H
// -*- C++ -*-
//
// Package:     DataHandler
// Module:      ProxyDeliverer
// 
// Description: Manages the creation of Proxies for DataSources
//
// Usage:
//    The ProxyDeliverer class is used by RecordDeliverer to attach
// Proxies to a Record.  RecordDeliverer and DataSourceController are
// the only two classes that should interact directly with
// ProxyDeliverer.
//
// ProxyDeliverer is a subclass of ProxyProvider which handles the
// registration of Proxies.  See its documentation for details.
//
// The ProxyProvider methods `latest' and `align' are overloaded as a
// ProxyDeliverer is tide to a particular SyncValue.  This means that
// RecordDeliverer needs to know if the ProxyDeliverer is tied to the
// most recent SyncValue.  Once the RecordDeliverer has decided which
// SyncValue is the "most recent", it aligns all ProxyProviders to that
// value.  For a ProxyDeliverer, which is tied to one SyncValue, if
// that aligned SyncValue does not match its own value then the
// `disable' member function is called, which should inform, by whatever
// mechanism the concrete subclass uses, that all its Proxies are
// invalid.  Otherwise the `enable' member function is called and all
// Proxies need to be informed they are able to provide data.
//
//    // ...junkFieldDeliverer does not have the most recent information
//    //   for the Event stream ...
//    junkFieldDeliverer.disable( Stream::kEvent ) ;
//    // ... now the proxyDeliverer has the "most recent"
//    //   information for event stream ..
//    junkFieldDeliverer.enable( Stream::kEvent ) ;
//
// The `reset' function is provided for use by the DataSourceController
// to inform the Proxies, via the ProxyDeliverer, that any cached
// information needs to be flushed and that there is a new information
// available, at a new SyncValue.
//
//    proxyDeliverer.reset( Stream::kEvent ,
//                              currentSyncValue ) ;
//
// The `reset' function changes the SyncValue for the relevent stream in
// the ProxyDeliverer and then calls `resetCache' and
// `invalidateProxies' respectively, for the particular stream, The
// `resetCache' function allows the concrete subclass should to change
// any internal states as necessary.  If the concrete subclass needs to
// know the new syncValue, it can simply use the `syncValue' function
// for that Stream.  The `invalidateProxies' function calls the
// `invalidate' function for all the Proxies in the particular Stream.
//
//    JunkFieldDeliverer::resetCache( const Stream::Type aStream )
//    {
//       if ( Stream::kEvent == aStream ) {
//       }
//       else if ( aStream == Stream::kBeginRun ) {
//          m_eventAvaliable = false ;
//       }
//    }
//
//
//
// Author:      Simon Patton
// Created:     Thu Mar 13 09:26:26 EST 1997
// $Id: ProxyDeliverer.h,v 1.18 1998/02/03 21:28:12 mkl Exp $
//
// Revision history
//
// $Log: ProxyDeliverer.h,v $
// Revision 1.18  1998/02/03 21:28:12  mkl
// switch over to STLUtility library
//
// Revision 1.17  1997/12/09 01:18:42  mkl
// minor fixes to typos in comments
//
// Revision 1.16  1997/09/03 20:06:39  sjp
// Uses CPP macros for STL containers
//
// Revision 1.15  1997/08/14 11:43:16  sjp
// Mods to run under CW Pro 1
//
// Revision 1.14  1997/08/06 15:57:23  sjp
// Modified to be a ProxyDeliverer
//
// Revision 1.13  1997/07/10 16:22:01  sjp
// fix spelling error in bug flag
//
// Revision 1.12  1997/07/09 18:00:47  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.11  1997/06/03 17:29:37  sjp
// Made to be a subclass of DataProvider
//
// Revision 1.10  1997/05/07 19:00:22  sjp
// Fixed less<Stream::Type> so can be used as usual
//
// Revision 1.9  1997/05/02 19:36:18  cdj
// Added supplies() method
//
// Revision 1.8  1997/04/29 20:05:50  cdj
// replaced less< Stream::Type> with Stream::TypeLess
//
// Revision 1.7  1997/04/19 20:45:39  sjp
// Fix pre-processor label
//
// Revision 1.6  1997/04/16 16:31:05  sjp
// Fixed typo in pre-processor flag
//
// Revision 1.5  1997/04/10 01:01:39  sjp
// Replaced resetSyncValue with extra argument in reset
//
// Revision 1.4  1997/04/04 16:36:25  sjp
// Moved generic functionality into Base class
//
// Revision 1.3  1997/03/29 16:18:54  sjp
// Complete first implementation
//
// Revision 1.2  1997/03/20 22:23:54  cdj
// Changed reset( void ) to reset( const Stream::Type& ) to match definition
// in DriverFieldDeliverer
//
// Revision 1.1  1997/03/19 22:18:21  sjp
// New header file for class
//

// system include files

// user include files
#if defined(CXX_IMPLIED_SPECIALIZATION_BUG)
#include "DataHandler/SyncValue.h"
#endif /* CXX_IMPLIED_SPECIALIZATION_BUG */
#include "DataHandler/ProxyProvider.h"

// STL include

// forward declarations
#include <map>
class SyncValue ;

#if !defined(_proxydeliverer_syncvalues_)
#  define _proxydeliverer_syncvalues_ std::map< Stream::Type , SyncValue >
#endif /* _proxydeliverer_syncvalues_ */


class ProxyDeliverer : public ProxyProvider
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      ProxyDeliverer( const ProxyProvider::Identifier& aId ) ;
      virtual ~ProxyDeliverer() ;

      // member functions
      void reset( const Stream::Type& aStream ,
		  const SyncValue& aSyncValue ) ;
      virtual void align( const Stream::Type& aStream ,
			  const SyncValue& aSyncValue ) ;
      virtual void disable( const Stream::Type& aStream ) = 0 ;
      virtual void enable( const Stream::Type& aStream ) = 0 ;

      // const member functions
      const SyncValue& syncValue( const Stream::Type& aStream ) const;
      virtual const SyncValue& latest( const Stream::Type& aStream ,
				       SyncValue& aCurrentLatest ,
				       const SyncValue& aLimit ) const ;

      // static member functions

   protected:
      // protected member functions
      virtual void registerStream( const Stream::Type& aStream ) ;
      virtual void resetCache( const Stream::Type& aStream ) = 0 ;

      // protected const member functions

   private:
      // Constructors and destructor
      ProxyDeliverer() ; // stop default
      ProxyDeliverer( const ProxyDeliverer& ) ; // stop default

      // assignment operator(s)
      const ProxyDeliverer& operator=( const ProxyDeliverer& ) ; // stop default

      // private member functions

      // private const member functions

      // data members
      _proxydeliverer_syncvalues_& m_syncValues ;

      // static data members

};

// inline function definitions

#endif /* DATADELIVERY_PROXYDELIVERER_H */
