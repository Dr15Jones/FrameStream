#if !defined(INTERACTIVEDELIVERY_INTERACTIVESOURCECONTROLLER_H)
#define INTERACTIVEDELIVERY_INTERACTIVESOURCECONTROLLER_H
// -*- C++ -*-
//
// Package:     InteractiveDelivery
// Module:      InteractiveSourceController
// 
// Description: Creates empty Event Records at SyncValues specified
//              by the User
//
// Usage:
//    Used by framework developers to implement a "goto" ability.
//
// Author:      Chris D. Jones
// Created:     Sat Apr 19 12:27:09 EDT 1997
// $Id: InteractiveSourceController.h,v 1.5 1997/09/18 21:25:26 cdj Exp $
//
// Revision history
//
// $Log: InteractiveSourceController.h,v $
// Revision 1.5  1997/09/18 21:25:26  cdj
// changed Boolean to DABoolean
//
// Revision 1.4  1997/08/06 16:30:32  sjp
// Modified to use ProxyDeliverer
//
// Revision 1.3  1997/07/09 19:22:15  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.2  1997/05/02 20:32:48  cdj
// Conforms to new DataSourceController interface
//
// Revision 1.1.1.1  1997/04/21 19:30:10  cdj
// First submission
//


// system include files

// user include files
#include "DataDelivery/DataSourceController.h"

// forward declarations
class InteractiveSource;
class InteractiveFieldDeliverer;

class InteractiveSourceController : public DataSourceController
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      static const char* const kID;

      // Constructors and destructor
      InteractiveSourceController( InteractiveSource* iSource );
      virtual ~InteractiveSourceController();

      // member functions
      virtual DataSourceController::SyncStatus 
                synchronizeSource( const SyncValue& iSyncTo );

      virtual DataSourceController::SearchStatus
               findNextRecord(SyncValue& oSyncValueOfNextRecord,
			      Stream::Type& oRecordTypeOfNextRecord );

      virtual DataSourceController::SearchStatus gotoNextRecord( void );

      // const member functions
      virtual DABoolean canRandomAccess( void ) const;

      virtual std::string dataSourceID( void ) const;
      virtual std::string parameters( void ) const;
      // static member functions

   protected:
      // protected member functions
      virtual void implementSetForcedSequentialAccess( DABoolean iFlag );

      // protected const member functions
      virtual ProxyDeliverer*  createProxyDeliverer( void ) const;


   private:
      // Constructors and destructor
      InteractiveSourceController( const InteractiveSourceController& );

      // assignment operator(s)
      const InteractiveSourceController& operator=( const InteractiveSourceController& );

      // private member functions

      // private const member functions

      // data members
      InteractiveSource* m_source;

      // static data members

};

// inline function definitions

#endif /* INTERACTIVEDELIVERY_INTERACTIVESOURCECONTROLLER_H */
