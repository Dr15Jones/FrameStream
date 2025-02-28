#if !defined(DATASTORAGE_PROXYSTORER_H)
#define DATASTORAGE_PROXYSTORER_H
// -*- C++ -*-
//
// Package:     DataStorage
// Module:      ProxyStorer
// 
// Description: Manages writing out Proxys to a Data Sink.
//
// Usage:
//    // The ProxyStorer class is used by RecordStorer to
//    // write out Proxys from a Record.  RecordStorer and
//    // DataSourceController are the only two classes that should
//    // interact directly with ProxyStorer.
//
//    // The set of Streams that a concrete subclass of
//    // ProxyStorer can store is created by the subclass
//    // calling the `registerStream' function for each stream it can
//    // store while it is being constructed.
//
//    JunkFieldStorer::JunkFieldStorer()
//    {
//       registerStream( Stream::kBeginRun ) ;
//       registerStream( Stream::kEvent ) ;
//    }
//    
//    // When a RecordStorer wishes to store a Record it hands the
//    // Record to each relevant ProxyStorer who write out the
//    // Proxys appropriate to that type of Record.
//
//    proxyStorer.store( record ) ;
//
//    // RecordStorer uses the `canStore' command to check that a
//    // ProxyStorer can store Proxys for a particluar
//    // Stream.  If there has been no call to `registerStream' then
//    // `canStore' will return `false'.  After the call to `canStore'
//    // it is assumed that any call made with that Stream::Type is
//    // valid for the ProxyStorer and so it is NOT tested again!
//
// Author:      Chris D. Jones
// Created:     Sun May 25 14:52:40 EDT 1997
// $Id: ProxyStorer.h,v 1.3 2003/04/25 15:32:20 vk Exp $
//
// Revision history
//
// $Log: ProxyStorer.h,v $
// Revision 1.3  2003/04/25 15:32:20  vk
// Add identifiers to the ProxyServer. Add entry to the DAExceptionStack.
//
// Revision 1.2  1997/09/18 21:13:20  cdj
// Changed Boolean to DABoolean
//
// Revision 1.1  1997/08/16 17:47:20  cdj
// Changed name of class to use Proxy instead of DataField
//
// Revision 1.4  1997/07/11 06:20:12  mkl
// // New <Package>/<File>.h structure
// // Modified so can also compile under cxx v5.5
//
// Revision 1.3  1997/05/31 21:16:14  cdj
// store() now calls implementStore() and uses the return value to set its
//  status
//
// Revision 1.2  1997/05/31 20:49:11  cdj
// 1) store now returns a status code
// 2) DataFieldStorer now knows its status based on the last store operation
//
// Revision 1.1.1.1  1997/05/30 15:41:37  cdj
// First submission
//


// system include files

// user include files
#include "DataHandler/Stream.h"


// forward declarations
class Record ;

class ProxyStorer
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      typedef string Identifier;
      enum StoreStatus { kStoreNoError=0,
			 kStoreProblemWithSink,
			 kStoreUnknownError
      };

      // Constructors and destructor
      ProxyStorer( const Identifier& aId="ProxyStorer" );
      virtual ~ProxyStorer();

      // member functions
      void setDataSinkId(const string& sId);
      void setParamId(const string& sParam);

      // const member functions
      const Identifier& identifier() const;
      DABoolean canStore( const Stream::Type& aStream ) const ;
      Stream::Set stores( void ) const;
      ProxyStorer::StoreStatus 
                      store( const Record& aRecord ) const ;

      StoreStatus status( void ) const;
      // static member functions

   protected:
      // protected member functions
      void registerStream( const Stream::Type& aStream ) ;

      // protected const member functions
      virtual ProxyStorer::StoreStatus 
                      implementStore( const Record& aRecord ) const = 0 ;


   private:
      // Constructors and destructor
      ProxyStorer( const ProxyStorer& );

      // assignment operator(s)
      const ProxyStorer& operator=( const ProxyStorer& );

      // private member functions
      void setStatus( const StoreStatus& iStoreStatus ); 

      // private const member functions

      // data members
      Identifier m_id;
      Identifier m_paramId;
      Identifier m_sinkId;
      Stream::Set& m_records;
      StoreStatus m_status;

      // static data members

};

// inline function definitions

#endif /* DATASTORAGE_PROXYSTORER_H */

