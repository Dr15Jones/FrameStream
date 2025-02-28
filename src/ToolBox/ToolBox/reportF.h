// -*- C++ -*-
//
// Package:     ToolBox
// Module:      report_
// 
// Description: Interface report_ to report()
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Tue Aug  4 16:38:53 EDT 1998
// $Id: reportF.h,v 1.2 1998/09/24 21:52:14 bkh Exp $
//
// Revision history
//
// $Log: reportF.h,v $
// Revision 1.2  1998/09/24 21:52:14  bkh
// Fix argument spec
//
// Revision 1.1  1998/09/24 20:34:54  bkh
// redesigned fortran reporting code, again
//
// Revision 1.2  1998/09/24 14:54:47  bkh
// move severities from report.inc to reportMessage.inc; remove int arg
// from reportMessage.
//
// Revision 1.1  1998/09/23 21:32:10  bkh
// forward declare of templated Triplet
// C++ interface between fortran report_ and C++ report()
//

// user include files
#include "Experiment/fortran_types.h"

// STL classes

extern "C" 
void report_( const FInteger& aSever  ,
	      const FChar*    aCrName ,
	      const FChar*    aMes    ,
	      const FInteger  aClen   ,
	      const FInteger  aMlen     ) ;

