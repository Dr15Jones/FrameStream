#if !defined(PACKAGE_PDS_FILE_HEADER_H)
#define PACKAGE_PDS_FILE_HEADER_H
// -*- C++ -*-
//
// Package:     <package>
// Module:      pds_file_header
// 
/**\class pds_file_header pds_file_header.h package/pds_file_header.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Tue Oct  3 12:42:23 EDT 2000
// $Id: pds_file_header.h,v 1.1 2000/10/04 18:59:00 cdj Exp $
//
// Revision history
//
// $Log: pds_file_header.h,v $
// Revision 1.1  2000/10/04 18:59:00  cdj
// first submission
//

// system include files

// user include files

// forward declarations

struct PDSHeaderConstants
{
      enum {
	 kFileTypeID = 3141592
      };

      enum Version {
	 kBitsForVersion = 8,
	 kInitialVersion = 0,
	 kPresentVersion = kInitialVersion
      };
};

#endif /* PACKAGE_PDS_FILE_HEADER_H */
