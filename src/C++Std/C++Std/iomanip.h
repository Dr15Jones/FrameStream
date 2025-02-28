#if !defined(CPPSTD_IOMANIP_H)
#define CPPSTD_IOMANIP_H
// -*- C++ -*-
//
// Package:     <C++Std>
// Module:      iomanip
// 
/**\class iomanip iomanip.h C++Std/iomanip.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      CLEO DAQ testing
// Created:     Fri Aug 24 09:03:20 EDT 2001
// $Id: iomanip.h,v 1.3 2003/02/06 15:11:59 cdj Exp $
//
// Revision history
//
// $Log: iomanip.h,v $
// Revision 1.3  2003/02/06 15:11:59  cdj
// removed OManip declaration in iomanip.h since only used in one place
//
// Revision 1.2  2003/01/30 22:14:24  cdj
// include new iomanip header if available
//
// Revision 1.1  2001/09/07 16:49:43  cleo3
// first submission
//

// system include files

// user include files

// forward declarations
#if defined(USING_IOSTREAM_H_BUG)
#include <iomanip.h>
#else
#include <iomanip>
#endif
#endif /* C++STD_IOMANIP_H */
