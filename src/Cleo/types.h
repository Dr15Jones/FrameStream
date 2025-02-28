#if !defined(EXPERIMENT_TYPES_H)
#define EXPERIMENT_TYPES_H
// -*- C++ -*-
//
// Package:     <Experiment>
// Module:      types
// 
// Description: These types here are defined for several reasons:
//                1.) platform independence; if some type needs to work on
//                    different platforms in the same way (e.g. 
//                    UInt32 assures you that you're getting 32 bits 
//                    no matter what platform), by taking care of platform),
//                    taking care of the (in)dependence here makes 
//                    everybody's life easier
//                2.) Convenience: many people will want some common types
//                    defined, so that we avoid duplication of work.
//
// Usage:
//    <usage>
//
// Implementation:
//     Limits: can't include "limits" because 

// Author:      Chris Jones, Martin Lohner
// Created:     Tue Jul 29 18:33:15 EDT 1997
// $Id: types.h,v 1.12 1999/03/01 22:43:53 mkl Exp $
//
// Revision history
//
// $Log: types.h,v $
// Revision 1.12  1999/03/01 22:43:53  mkl
// use configured common types
//
// Revision 1.11  1998/11/24 19:35:44  mkl
// turned float into double for standard types and units
//
// Revision 1.10  1998/11/12 22:27:17  mkl
// renamed BOOLEAN_ALREADY_DEFINED_BUG to inverted BOO_NOT_DEFINED_BUG; new BOOL_IS_INT_BUG for Solaris
//
// Revision 1.9  1998/03/27 16:20:09  mkl
// added kMin* values for (U)Int<number> types
//
// Revision 1.8  1998/03/27 15:24:48  mkl
// gnu 2.7.2 doesnt understand <limits>; now include <limits.h>
//
// Revision 1.7  1998/03/26 19:41:31  mkl
// added kMax* values for (U)Int<number> types
//
// Revision 1.6  1998/03/06 16:03:21  mkl
// make convenience types Count, SmallCount etc dependent on bit-specific types
//
// Revision 1.5  1998/03/05 19:42:02  mkl
// nice formatting
//
// Revision 1.4  1998/03/05 19:15:20  mkl
// switch from C3(U)INT to (U)Int
//
// Revision 1.3  1998/03/05 18:31:12  mkl
// added C3(U)INT8,16,64
//
// Revision 1.2  1998/03/05 17:46:42  mkl
// moved typedefs out of Experiment.h into types.h; include types.h in Experiment.h for backwards compatibility
//
// Revision 1.1  1997/11/01 21:14:47  mkl
// new file for types
//
//

// system include files
#include <limits.h>

// user include files

// constants, enums and typedefs

#if defined(BOOL_NOT_DEFINED_BUG)
#if defined(BOOL_IS_INT_BUG)
typedef int  DABoolean ;
#else
typedef char DABoolean ;
#endif
#else
typedef bool DABoolean ;
#endif /* BOOLEAN_ALREADY_DEFINED_BUG */

// ---------- specific bit typedefs -----------
// Read sizes found by configure
#include <sc_config.h>
// Genereate (U)IntXX types
#include <cleo3_stdtypes.h>
// --------------------------------------------

// --------- max and min for various types ----
#define kMaxInt8     CHAR_MAX
#define kMaxInt16   SHORT_MAX
#define kMaxInt32     INT_MAX
#define kMaxInt64    LONG_MAX
#define kMaxUInt8   UCHAR_MAX
#define kMaxUInt16 USHORT_MAX
#define kMaxUInt32   UINT_MAX
#define kMaxUInt64  ULONG_MAX

#define kMinInt8     CHAR_MIN
#define kMinInt16   SHORT_MIN
#define kMinInt32     INT_MIN
#define kMinInt64    LONG_MIN
#define kMinUInt8   UCHAR_MIN
#define kMinUInt16 USHORT_MIN
#define kMinUInt32   UINT_MIN
#define kMinUInt64  ULONG_MIN

// ---------- convenience types ---------------

// the following types are bound to the bit-specific types above
typedef	UInt16 SmallCount ;
typedef	UInt32 Count ;
typedef	UInt64 LargeCount ;
typedef	Int16  SmallInteger ;
typedef	Int32  Integer ;
typedef	Int64  LargeInteger ;

typedef	float  Real ;
typedef	double Double ;


// unit types
typedef	double GeV ;
typedef	double Meters ;
typedef	double ElectronCharge ;
typedef	double Likelihood ;

#endif /* EXPERIMENT_TYPES_H */
