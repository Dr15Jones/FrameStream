#if !defined(DATASTORAGE_RECORDSTORER_H)
#define DATASTORAGE_RECORDSTORER_H
// -*- C++ -*-
//
// Package:     DataStorage
// Module:      RecordStorer
// 
// Description: Manages the storing of Records.
//
// Usage:
//    // A RecordStorer is responsible for knowing which DataSinks
//    // want to write out the RecordStorer's particular Record.
//    // RecordStorer is used exclusively by FrameStorer.  This is one
//    // RecordStorer for each output Stream in a program.
//
//    // FrameStorer determines which sinks want to store information
//    // about a type of Record.  For each of these sinks there is an
//    // associated ProxyStorer which must be handed to RecordStorer
//    // using the 'add' method.  When a ProxyStorer is no longer
//    // required for the type of Record a RecordStorer saves, the it
//    // should be removed from the RecordStorer with the 'remove' method.
//    // If no sinks want to save the Record controlled by RecordStorer
//    // then all its ProxyStorers should be removed using the
//    // 'removeAll' function.  It is possible to check if the RecordStorer
//    // is using any ProxyStorers by using the 'isEmpty' function.
//
//    eventStorer.add( driverProxyStorer ) ;
//    //  ...  use driver sink until no longer needed ...
//    eventStorer.remove( driverProxyStorer ) ;
//    //  ...  continue until written everything
//    eventStorer.removeAll() ;
//    if ( eventStorer.isEmpty() ) {
//       // ... this section should always execute because of the
//       //     preceeding `removeAll' call
//    }
//
//
//    // A FrameStorer uses a RecordStorer to save Records from a
//    // Frame.  It does this by handing the Frame to the
//    // RecordStorer so that it can save the Record using the `store'
//    // function.
//
//    eventStorer.store( frame ) ;
//
//
// Author:      Chris D. Jones
// Created:     Sun May 25 14:45:27 EDT 1997
// $Id: RecordStorer.h,v 1.7 1998/02/03 21:28:48 mkl Exp $
//
// Revision history
//
// $Log: RecordStorer.h,v $
// Revision 1.7  1998/02/03 21:28:48  mkl
// switch over to STLUtility library
//
// Revision 1.6  1997/09/18 21:13:21  cdj
// Changed Boolean to DABoolean
//
// Revision 1.5  1997/08/18 18:00:11  mkl
// changed vector to list, because of problems with return type 'list<>::iterator' of function
//
// Revision 1.4  1997/08/16 17:45:41  cdj
// Modified to work with Proxies
//
// Revision 1.3  1997/07/11 06:20:16  mkl
// // New <Package>/<File>.h structure
// // Modified so can also compile under cxx v5.5
//
// Revision 1.2  1997/05/31 20:51:27  cdj
// store now returns a status code
//
// Revision 1.1.1.1  1997/05/30 15:41:37  cdj
// First submission
//


// system include files

// user include files
#include "DataHandler/Stream.h"


// forward declarations
class ProxyStorer ;
class Frame;

#include "STLUtility/fwd_vector.h"


class RecordStorer
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      enum StoreStatus { kStoreNoError=0,
			 kStoreProblemWithASink,
			 kStoreUnknownSinkError,
			 kStoreUnknownError
      };

      // Constructors and destructor
      RecordStorer( const Stream::Type& iStream );
      virtual ~RecordStorer();

      // member functions
      void add( ProxyStorer& iStorer ) ;
      void remove( ProxyStorer& iStorer ) ;
      void removeAll() ;

      RecordStorer::StoreStatus store( const Frame& iFrame ) ;

      // const member functions

      DABoolean isEmpty( void ) const;

      // static member functions

   protected:
      // protected member functions
      const vector< ProxyStorer* >& storers( void ) const ;

      // protected const member functions

   private:
      // Constructors and destructor
      RecordStorer( void );
      RecordStorer( const RecordStorer& );

      // assignment operator(s)
      const RecordStorer& operator=( const RecordStorer& );

      // private member functions

      // private const member functions

      // data members

      // static data members
      Stream::Type m_stream ;
      vector< ProxyStorer* >& m_storers ;

};

// inline function definitions

#endif /* DATASTORAGE_RECORDSTORER_H */
