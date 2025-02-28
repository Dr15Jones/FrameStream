#if !defined(PACKEDDATASTREAMSFORMAT_PDS_RECORD_HEADER_H)
#define PACKEDDATASTREAMSFORMAT_PDS_RECORD_HEADER_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsFormat>
// Module:      pds_record_header
// 
/**\class pds_record_header pds_record_header.h PackedDataStreamsFormat/pds_record_header.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Sun Sep 24 13:42:44 EDT 2000
// $Id: pds_record_header.h,v 1.1.1.1 2000/09/29 17:46:15 cdj Exp $
//
// Revision history
//
// $Log: pds_record_header.h,v $
// Revision 1.1.1.1  2000/09/29 17:46:15  cdj
// imported
//

// system include files

// user include files

// forward declarations
class PDSRecordHeader 
{
   public:
      enum { kRecordTypeWord,
	     kRunNumberWord,
	     kEventNumberWord,
	     kTimeLowerWord,
	     kTimeUpperWord,
	     kSizeOfBodyWord,
	     kNumberOfWords };
};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsFormat/Template/pds_record_header.cc"
//#endif

#endif /* PACKEDDATASTREAMSFORMAT_PDS_RECORD_HEADER_H */
