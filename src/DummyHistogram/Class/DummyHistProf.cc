// -*- C++ -*-
//
// Package:     <DummyHistogram>
// Module:      DummyHistProf
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Bill McCloskey
// Created:     Sat Mar  6 23:05:53 EST 1999
// $Id: DummyHistProf.cc,v 1.4 2002/05/06 17:49:05 mccann Exp $
//
// Revision history
//
// $Log: DummyHistProf.cc,v $
// Revision 1.4  2002/05/06 17:49:05  mccann
// added weighted profiles and the HIHistProf option kWeightedError
//
// Revision 1.3  2001/08/03 17:39:16  bkh
// Implement pure virtual base class function with dummy
//
// Revision 1.2  2000/06/19 18:46:56  bkh
// Implement new virtual fcns
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
#include "DummyHistogram/DummyHistProf.h"

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

static const char* const kFacilityString = "DummyHistogram.DummyHistProf" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: DummyHistProf.cc,v 1.4 2002/05/06 17:49:05 mccann Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
DummyHistProf::DummyHistProf( unsigned int   iId,
			      const std::string&  iTitle,
			      unsigned int   iNChannels,
			      float          iLowEdgeX,
			      float          iHighEdgeX,
			      float          iLowEdgeY,
			      float          iHighEdgeY,
			      HIHistProf::DisplayErrorsAs iDisplayErrorsAs ) :
  HIHistProf(
	      iId,
	      iTitle,
	      iNChannels,
	      iLowEdgeX,
	      iHighEdgeX,
	      iLowEdgeY,
	      iHighEdgeY,
	      iDisplayErrorsAs )
{
}

// DummyHistProf::DummyHistProf( const DummyHistProf& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

DummyHistProf::~DummyHistProf()
{
}

//
// assignment operators
//
// const DummyHistProf& DummyHistProf::operator=( const DummyHistProf& rhs )
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
void DummyHistProf::fill ( float iXEntry,
			   float iYEntry,
			   float iWeight )
{
}
// Add two profile plots
void DummyHistProf::add ( const HIHistProf&,
			  const HIHistProf& )
{
}
// Subtract two profile plots
void DummyHistProf::sub ( const HIHistProf&,
			  const HIHistProf& )
{
}
// Multiply two profile plots
void DummyHistProf::mult ( const HIHistProf&,
			   const HIHistProf& )
{
}
// Divide two profile plots
void DummyHistProf::div ( const HIHistProf&,
			  const HIHistProf& )
{
}

void DummyHistProf::reset()
{
}

//
// const member functions
//

float 
DummyHistProf::sumWithinLimits() const
{
   return -1. ;
}

float 
DummyHistProf::maxValue()        const
{
   return -1. ;
}

float 
DummyHistProf::minValue()        const
{
   return -1. ;
}

float 
DummyHistProf::channelValue( unsigned int iChan )        const
{
   return -1. ;
}

float 
DummyHistProf::channelError( unsigned int iChan )        const
{
   return -1. ;
}

//
// static member functions
//
