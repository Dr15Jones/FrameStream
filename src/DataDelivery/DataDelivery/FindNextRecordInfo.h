#if !defined(DATADELIVERY_FINDNEXTRECORDINFO_H)
#define DATADELIVERY_FINDNEXTRECORDINFO_H
// -*- C++ -*-
//
// Package:     DataDelivery
// Module:      FindNextRecordInfo
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Simon Patton
// Created:     Wed Jul  2 10:37:16 EDT 1997
// $Id: FindNextRecordInfo.h,v 1.3 1997/09/18 21:07:16 cdj Exp $
//
// Revision history
//
// $Log: FindNextRecordInfo.h,v $
// Revision 1.3  1997/09/18 21:07:16  cdj
// changed Boolean to DABoolean
//
// Revision 1.2  1997/07/09 18:00:58  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.1  1997/07/02 19:27:03  sjp
// New cless to be used by FrameDeliverer
//


// system include files

// user include files
#include "DataHandler/Stream.h"
#include "DataHandler/SyncValue.h"


// forward declarations
class DataSourceController ;

struct FindNextRecordInfo
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      FindNextRecordInfo( void ) :
	 controller(0),
	 stream( Stream::kNone),
	 syncValue(),
	 recordIsFromActiveStream(false)
{ };
      FindNextRecordInfo( DataSourceController* iController,
			  const SyncValue& iSyncValue,
			  const Stream::Type& iStream,
			  DABoolean iRecordIsFromActiveStream ) :
	 controller(iController),
	 stream( iStream ),
	 syncValue( iSyncValue),
	 recordIsFromActiveStream( iRecordIsFromActiveStream )
{};
//      virtual ~FindNextRecordInfo();  use default

      // data members

      DataSourceController* controller;
      Stream::Type stream;
      SyncValue syncValue;
      DABoolean recordIsFromActiveStream;

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
//      FindNextRecordInfo( const FindNextRecordInfo& ); // use default

      // assignment operator(s)
const FindNextRecordInfo& operator=( const FindNextRecordInfo& ); // stop default

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

#endif /* DATADELIVERY_FINDNEXTRECORDINFO_H */
