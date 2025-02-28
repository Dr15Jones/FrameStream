#if !defined(PACKEDDATASTREAMSFORMAT_PDS_PACKING_ENUMS_H)
#define PACKEDDATASTREAMSFORMAT_PDS_PACKING_ENUMS_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsFormat>
// Module:      pds_packing_enums
// 
/**\class pds_packing_enums pds_packing_enums.h PackedDataStreamsFormat/pds_packing_enums.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Thu Sep 14 16:56:36 EDT 2000
// $Id: pds_packing_enums.h,v 1.1.1.1 2000/09/29 17:46:15 cdj Exp $
//
// Revision history
//
// $Log: pds_packing_enums.h,v $
// Revision 1.1.1.1  2000/09/29 17:46:15  cdj
// imported
//

// system include files

// user include files

// forward declarations
struct PDSPacking
{
      enum Types {
	 kCharType,
	 kShortType,
	 kIntType,
	 kLongType,
	 kUCharType,
	 kUShortType,
	 kUIntType,
	 kULongType,
	 kFloatType,
	 kDoubleType,
	 kStringType,
	 kBoolType,
	 kContainerType,
	 kClassContainerType,
	 kNumberOfTypes
      };

      enum Strategies {
	 kNoPacking,
	 kFractionalPacking,
	 kFixedPacking,
	 kFixedTrueZeroPacking,
	 kNumberOfStrategies
      };
};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsFormat/Template/pds_packing_enums.cc"
//#endif

#endif /* PACKEDDATASTREAMSFORMAT_PDS_PACKING_ENUMS_H */
