#if !defined(PACKEDDATASTREAMSDELIVERY_PDSTYPETOUNPACKINGINFOMAP_H)
#define PACKEDDATASTREAMSDELIVERY_PDSTYPETOUNPACKINGINFOMAP_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSTypeToUnpackingInfoMap
// 
/**\class PDSTypeToUnpackingInfoMap PDSTypeToUnpackingInfoMap.h PackedDataStreamsDelivery/PDSTypeToUnpackingInfoMap.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Mon Dec 15 10:38:40 EST 2003
// $Id: PDSTypeToUnpackingInfoMap.h,v 1.1 2003/12/15 17:04:17 cdj Exp $
//
// Revision history
//
// $Log: PDSTypeToUnpackingInfoMap.h,v $
// Revision 1.1  2003/12/15 17:04:17  cdj
// first submission
//

// system include files

// user include files
#include "PackedDataStreamsDelivery/PDSTypeUnpackingInfo.h"

// forward declarations

class PDSTypeToUnpackingInfoMap : public std::map<TypeTag, PDSTypeUnpackingInfo *>
{
   public:
   ~PDSTypeToUnpackingInfoMap() {
      iterator itEnd = end();
      for( iterator itEntry = begin(); itEntry != itEnd;
	        ++itEntry ) {
	        	//cout <<"deleting packerInfo"<<(*itEntry).second<<std::endl;
	      delete (*itEntry).second;
      }
   }
      
};

#endif /* PACKEDDATASTREAMSDELIVERY_PDSTYPETOUNPACKINGINFOMAP_H */
