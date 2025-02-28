#if !defined(TOOLBOX_HISTOGRAMPACKAGE_H)
#define TOOLBOX_HISTOGRAMPACKAGE_H
// -*- C++ -*-
//
// Package:     ToolBox
// Module:      HistogramPackage
// 
// Description: Typedef the components of selected Hisogram package
//
// Usage:
//    <Usage>
//
// Author:      Simon Patton
// Created:     Thu May 16 10:58:31 EDT 1996
// $Id: HistogramPackage.h,v 1.5 1999/09/07 14:50:36 mkl Exp $
//
// Revision history
//
// $Log: HistogramPackage.h,v $
// Revision 1.5  1999/09/07 14:50:36  mkl
// move to new Histogram Interface (for now leave histogram typedefs for backwards compatibility
//
// Revision 1.4.2.2  1999/05/28 21:41:59  billm
// Added CharList definition.
//
// Revision 1.4.2.1  1999/05/21 08:02:31  billm
// Changed typedefs to point to new Histogram interface.
//
// Revision 1.4  1998/07/24 18:34:16  cdj
// Includes header for TBNTupleVarNames class
//
// Revision 1.3  1997/12/02 17:57:05  mkl
// changed CLHEP typedefs for HistogramPackage.h to match our Hbook typedefs
//
// Revision 1.2  1997/09/07 22:36:21  sjp
// Fixed include file name
//
// Revision 1.1  1997/09/07 21:14:10  sjp
// New file to choose Histogram Manager
//

//
// HistogramManager is simply a typedef of a libraries manager class,
//   currently it is the one in sjp's Utility library.
//

#include "HistogramInterface/HIHist1D.h"
typedef HIHist1D TB1DHisto ;
#include "HistogramInterface/HIHist2D.h"
typedef HIHist2D TB2DHisto ;
#include "HistogramInterface/HIHistProf.h"
typedef HIHistProf TBProfileHisto ;
typedef HIHistProf TBProfHisto ;
#include "HistogramInterface/HINtuple.h"
typedef HINtuple TBNtuple ;
#include "HistogramInterface/HIHistoManager.h"
typedef HIHistoManager TBHistoManager ;

typedef const char* CharList ;

#endif /* TOOLBOX_HISTOGRAMMANAGER_H */
