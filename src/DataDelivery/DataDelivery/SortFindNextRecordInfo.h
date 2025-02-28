#if !defined(DATADELIVERY_SORTFINDNEXTRECORDINFO_H)
#define DATADELIVERY_SORTFINDNEXTRECORDINFO_H
// -*- C++ -*-
//
// Package:     DataDelivery
// Module:      SortFindNextRecordInfo
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Simon Patton
// Created:     Wed Jul  2 10:37:33 EDT 1997
// $Id: SortFindNextRecordInfo.h,v 1.3 1997/09/18 21:07:20 cdj Exp $
//
// Revision history
//
// $Log: SortFindNextRecordInfo.h,v $
// Revision 1.3  1997/09/18 21:07:20  cdj
// changed Boolean to DABoolean
//
// Revision 1.2  1997/07/09 18:01:04  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.1  1997/07/02 19:27:05  sjp
// New cless to be used by FrameDeliverer
//


// system include files

// user include files
#include "DataDelivery/FindNextRecordInfo.h"
#include "DataHandler/StreamPriorityGreater.h"


// forward declarations

class SortFindNextRecordInfo
{
   public:
      DABoolean operator()( const FindNextRecordInfo& iLHS,
			  const FindNextRecordInfo& iRHS ) const
        {
	   if( iLHS.syncValue != iRHS.syncValue ){
	      if( iLHS.syncValue < iRHS.syncValue ){
		 return true;
	      } else {
		 return false;
	      }
	   }
	   return StreamPriorityGreater().operator()( iLHS.stream,
						      iRHS.stream );
	};

};

// inline function definitions

#endif /* DATADELIVERY_SORTFINDNEXTRECORDINFO_H */
