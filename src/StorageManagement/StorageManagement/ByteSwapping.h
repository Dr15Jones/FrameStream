#if !defined(BINARYDELIVERY_BYTESWAPPING_H)
#define BINARYDELIVERY_BYTESWAPPING_H
// -*- C++ -*-
//
// Package:     <BinaryDelivery>
// Module:      ByteSwapping
// 
// Description: Inline function to swap bytes within a 32-bit word
//
// Usage:
//    UInt32 Original
//    UInt32 Swapped
//    Swapped = swapBytesInWord( Original ) ;
//
// Author:      David L. Kreinick
// Created:     Wed Apr 21 11:08:15 EDT 1999
// $Id: ByteSwapping.h,v 1.1 1999/04/23 19:10:02 dlk Exp $
//
// Revision history
//
// $Log: ByteSwapping.h,v $
// Revision 1.1  1999/04/23 19:10:02  dlk
// DLK: Contains inline byte swapping code for running on little endian
//      machines
//

// system include files

// user include files

// forward declarations

// inline function definitions
inline
UInt32
swapBytesInUInt32( UInt32 iInput )
{
   return ( (  iInput << 24              ) |
	    ( (iInput << 8) & 0x00ff0000 ) |
	    ( (iInput >> 8) & 0x0000ff00 ) |
	    (  iInput >> 24              ) ) ;
}

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "BinaryDelivery/Template/ByteSwapping.cc"
//#endif

#endif /* BINARYDELIVERY_BYTESWAPPING_H */
