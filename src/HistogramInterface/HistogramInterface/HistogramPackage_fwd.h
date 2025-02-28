#if !defined(PACKAGE_HISTOGRAMPACKAGE_FWD_H)
#define PACKAGE_HISTOGRAMPACKAGE_FWD_H
// -*- C++ -*-
//
// Package:     <package>
// Module:      HistogramPackage_fwd
// 
/**\class HistogramPackage_fwd HistogramPackage_fwd.h package/HistogramPackage_fwd.h

 Description: Makes it easier to forward declare classes in the HistogramInterface package

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Wed Mar 12 12:39:17 EST 2003
// $Id: HistogramPackage_fwd.h,v 1.1 2003/03/12 19:05:22 cdj Exp $
//
// Revision history
//
// $Log: HistogramPackage_fwd.h,v $
// Revision 1.1  2003/03/12 19:05:22  cdj
// added HistogramPackage_fwd.h file to make it easier to forward declare classes when dealing with the namespace
//
#if !defined(NO_KOENIG_LOOKUP_RULE_BUG)
namespace HistogramInterface {
#endif
class HIHist1D;
class HIHist2D;
#if !defined(NO_KOENIG_LOOKUP_RULE_BUG)
};
using HistogramInterface::HIHist1D;
using HistogramInterface::HIHist2D;
#endif
class HIHistProf;
class HINtuple;
class HIHistoManager;
class HIDirSwitch;
class HIHistDir;

#endif /* PACKAGE_HISTOGRAMPACKAGE_FWD_H */
