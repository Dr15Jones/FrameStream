#if !defined(CHAINDELIVERY_CHAINSOURCECONTROLLER_H)
#define CHAINDELIVERY_CHAINSOURCECONTROLLER_H
// -*- C++ -*-
//
// Package:     ChainDelivery
// Module:      ChainSourceController
// 
// Description: Templated class used to chain together DataSourceControllers
//
// Usage:
//    What Must Be True To Use ChainSourceController
//      XXXSourceController
//        - have a Constructor that takes a XXXProxyDeliverer* and passes
//          that pointer to DataSourceController's constructor
//        - make ChainSourceController a friend class
//            friend ChainSourceController<XXXSourceBinder>;
//          this allows ChainSourceController to call the protected
//            createProxyDeliverer()
//
//      XXXProxyDeliverer
//        - have method
//            void changeSourceController( XXXSourceController& )
//          which gets from the Controller all the info it needs to read
//          Records coming from that controller
//        - if any data from previous Records is cached, the cache must
//          be owned by XXXProxyDeliverer and not XXXSourceController.
//          The reason is ChainSourceController winds up owning a
//          XXXProxyDeliverer and when it switchs from one source to the
//          next it may still need access to data from a Record that was
//          read in by the previous source.
//
//      XXXSourceBinder
//        - typedef XXXSourceController Controller;
//        - typedef XXXProxyDeliverer Deliverer;
//        - have method
//            XXXSourceController* createSourceController( XXXProxyDeliverer*)
//          which creates a XXXSourceController by passing it the
//          pointer to the Deliverer
//        - must have
//            default constructor
//            copy constructor
//            assignment operator
//          because we store them in an STL container
//
// Author:      Chris D. Jones
// Created:     Fri Jul 25 13:35:03 EDT 1997
// $Id: ChainSourceController.h,v 1.12 2003/04/09 14:37:12 cdj Exp $
//
// Revision history
//
// $Log: ChainSourceController.h,v $
// Revision 1.12  2003/04/09 14:37:12  cdj
// cleaned up the code
//
// Revision 1.11  2003/04/08 14:10:10  cdj
// attempt to improve chaining of Driver sources
//
// Revision 1.10  2002/06/12 19:22:41  cleo3
// added missing typename
//
// Revision 1.9  1998/07/18 19:45:19  mkl
// use STL macros
//
// Revision 1.8  1998/04/09 23:18:28  cleo3
// port to egcs
//
// Revision 1.7  1998/02/06 20:38:18  mkl
// left-over edits for switch to STLUtility
//
// Revision 1.6  1997/09/18 20:50:56  cdj
// Changed Boolean to DABoolean
//
// Revision 1.5  1997/08/14 11:44:02  sjp
// Mods to run under CW Pro 1
//
// Revision 1.4  1997/08/13 18:59:41  sjp
// Fixed so ChainDelivery works under cxx
//
// Revision 1.3  1997/08/08 17:07:44  cdj
// Updated to work with Proxies
//
// Revision 1.2  1997/07/26 16:44:25  cdj
// forward declares deque
//
// Revision 1.1.1.1  1997/07/25 23:35:23  cdj
// First submission. Compiles but untested
//

// system include files

// user include files
#include "DataDelivery/DataSourceController.h"
#include "ChainDelivery/ChainSourceBinder.h"

// forward declarations
#include "STLUtility/fwd_deque.h"

#if !defined(_chainsourcecontroller_deque_)
#define _chainsourcecontroller_deque_ STL_DEQUE( Binder )
#endif /* _chainsourcecontroller_deque_ */

template< class Binder >
class ChainSourceController : public DataSourceController
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef typename Binder::Controller Controller;
      typedef typename Binder::Deliverer Deliverer;

      // Constructors and destructor
      ChainSourceController( const string& iName,
			     const typename ChainSourceBinder< Binder >::Binders& iBinders,
			     const Stream::Set& iReadStreams);

      virtual ~ChainSourceController();

      // member functions
      virtual DataSourceController::SyncStatus 
           synchronizeSource( const SyncValue& iSyncTo );

      virtual DataSourceController::SearchStatus
               findNextRecord(SyncValue& oSyncValueOfNextRecord,
			      Stream::Type& oRecordTypeOfNextRecord );

      virtual DataSourceController::SearchStatus 
               gotoNextRecord( void );

      void addSource( const Binder& iBinder );
      void removeSource( const DataSourceDescriptor& iDescriptor );

      // const member functions
      virtual DABoolean canRandomAccess( void ) const;

      virtual string dataSourceID( void ) const;
      virtual string parameters( void ) const;

      const string& name( void ) const;
      // static member functions

   protected:
      // protected member functions
      virtual void implementSetForcedSequentialAccess( DABoolean iFlag );

      // protected const member functions
      virtual ProxyDeliverer* createProxyDeliverer( void ) const;

   private:
      // Constructors and destructor
      ChainSourceController( const ChainSourceController& );

      // assignment operator(s)
      const ChainSourceController& operator=( const ChainSourceController& );

      // private member functions
      DABoolean switchToNextSource( void );

      // private const member functions

      // data members
      _chainsourcecontroller_deque_& m_binders;
      string m_name;
      Controller* m_controller;
      Deliverer* m_deliverer;
      DABoolean m_ownsDeliverer;

      DABoolean m_waitingToUseNextSource;
      SyncValue m_syncValueOfNextSource;
      Stream::Type m_recordTypeOfNextSource;

      // static data members

};

// inline function definitions

#endif /* CHAINDELIVERY_CHAINSOURCECONTROLLER_H */
