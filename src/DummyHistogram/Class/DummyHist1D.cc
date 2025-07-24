// -*- C++ -*-
//
// Package:     <DummyHistogram>
// Module:      DummyHist1D
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Bill McCloskey
// Created:     Sat Mar  6 23:05:44 EST 1999
// $Id: DummyHist1D.cc,v 1.3 2000/06/19 18:46:56 bkh Exp $
//
// Revision history
//
// $Log: DummyHist1D.cc,v $
// Revision 1.3  2000/06/19 18:46:56  bkh
// Implement new virtual fcns
//
// Revision 1.2  1999/12/23 23:30:08  cdj
// updated to new histogram interface
//
// Revision 1.1.1.1  1999/05/12 00:10:09  billm
// imported DummyHistogram sources
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "DummyHistogram/DummyHist1D.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "DummyHistogram.DummyHist1D" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: DummyHist1D.cc,v 1.3 2000/06/19 18:46:56 bkh Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
DummyHist1D::DummyHist1D( unsigned int  iId,
			  const std::string& iTitle,
			  unsigned int  iNChannels,
			  float         iLowEdge,
			  float         iHighEdge,
			  float         iBitsPerChannel) :
   HIHist1D( iId,
	     iTitle,
	     iNChannels,
	     iLowEdge,
	     iHighEdge,
	     iBitsPerChannel)
{
}

// DummyHist1D::DummyHist1D( const DummyHist1D& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

DummyHist1D::~DummyHist1D()
{
}

//
// assignment operators
//
// const DummyHist1D& DummyHist1D::operator=( const DummyHist1D& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }

//
// member functions
//
// Fill a 1D histogram
void DummyHist1D::fill( float iEntry,
			float iWeight )
{
}

// Scale
void DummyHist1D::scale( const float iScale )
{
}

// Add two 1D histograms
void DummyHist1D::add( const HIHist1D&,
		       const HIHist1D&,
		       const float,
		       const float )
{
}

// Subtract two 1D histograms
void DummyHist1D::sub( const HIHist1D&,
		       const HIHist1D&,
		       const float,
		       const float )
{
}

// Multiply two 1D histograms
void DummyHist1D::mult( const HIHist1D&,
			const HIHist1D&,
			const float,
			const float )
{
}

// Divide two 1D histograms
void DummyHist1D::div( const HIHist1D&,
		       const HIHist1D&,
		       const float,
		       const float )
{
}

void DummyHist1D::copy( const HIHist1D& )
{
}

void DummyHist1D::reset()
{
}

void DummyHist1D::fillChannelValue( unsigned int iChannel, float iWeight )
{
}

void 
DummyHist1D::setErrors( const float*  )
{
}
//
// const member functions
//
float DummyHist1D::channelValue( unsigned int iChannel ) const
{
  return -1;
}

float DummyHist1D::channelError( unsigned int iChannel ) const
{
  return -1;
}

float 
DummyHist1D::sumWithinLimits() const 
{
   return -1. ;
}

float 
DummyHist1D::maxValue()        const
{
   return -1. ;
}

float 
DummyHist1D::minValue()        const
{
   return -1. ;
}

float 
DummyHist1D::underflow() const
{
   return -1. ;
}

float 
DummyHist1D::overflow()  const
{
   return -1. ;
}

//
// static member functions
//
